#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <pspdisplay.h>
#include <string.h>
#include <psprtc.h>
#include <psppower.h>
#include <math.h>
#include <stdio.h>

#include <memory>

#include "cgame.h"
#include "ivideo.h"

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
PSP_MODULE_INFO("Dizzy", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER|THREAD_ATTR_VFPU);

void dump_threadstatus(void);

bool done=false;

int exit_callback(int arg1,int arg2,void *common)
{
 done=true;
 return(0);
}
int CallbackThread(SceSize args, void *argp)
{
 int cbid;
 cbid=sceKernelCreateCallback("Exit Callback",exit_callback,NULL);
 sceKernelRegisterExitCallback(cbid);
 sceKernelSleepThreadCB();
 return(0);
}
int SetupCallbacks(void)
{
 int thid = 0;
 thid=sceKernelCreateThread("update_thread",CallbackThread,0x11,0xFA0,0,0);
 if(thid>=0) sceKernelStartThread(thid, 0, 0);
 return(thid);
}
//----------------------------------------------------------------------------------------
//начинаем программу
int main(int argc, char  **argv)
{
 int n;
 int argv_len=strlen(argv[0]);
 //отматываем до черты
 for(n=argv_len;n>0;n--)
 {
  if (argv[0][n-1]=='/')
  {
   argv[0][n]=0;//обрубаем строку
   break;
  }
 }
 //устанавливаем обработчики
 SetupCallbacks();
 //настраиваем управление
 sceCtrlSetSamplingCycle(0);
 sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
 //активируем видеорежим
 long ActivePage=0;//видимая видеостраница
 sceDisplayWaitVblankStart();
 uint32_t *VideoBuffer=(uint32_t *)(0x44000000UL+272UL*512UL*4UL*ActivePage);//адрес видеопамяти
 sceDisplaySetFrameBuf((void*)VideoBuffer,512,PSP_DISPLAY_PIXEL_FORMAT_8888,PSP_DISPLAY_SETBUF_NEXTFRAME);
 sceDisplaySetMode(0,480,272);
 sceDisplayWaitVblankStart();

 //CPSPVideo cPSPVideo;
 CGame cGame;
 std::shared_ptr<IVideo> iVideo_Ptr;
 iVideo_Ptr.reset(IVideo::CreateNewCVideoSoftware(CGame::SCREEN_WIDTH,CGame::SCREEN_HEIGHT));
 iVideo_Ptr->Init();

 iVideo_Ptr->SetVideoPointer(VideoBuffer+(480-320)/2,512);

 bool enabled=cGame.Init(iVideo_Ptr.get());

 SceCtrlData pad;
 while(done==false)
 {
  u64 tick_frequency=sceRtcGetTickResolution();
  u64 begin_tick;
  u64 current_tick;
  sceRtcGetCurrentTick(&begin_tick);//текущее значение частоты

  //сканируем клавиатуру
  sceCtrlReadBufferPositive(&pad,1);
  if (enabled==true)
  {
   bool left=false;
   bool right=false;
   bool up=false;
   bool down=false;
   bool fire=false;
   if (pad.Buttons&PSP_CTRL_LEFT) left=true;
   if (pad.Buttons&PSP_CTRL_RIGHT) right=true;
   if (pad.Buttons&PSP_CTRL_UP) up=true;
   if (pad.Buttons&PSP_CTRL_DOWN) down=true;
   if (pad.Buttons&PSP_CTRL_CIRCLE) fire=true;
   cGame.OnTimer(left,right,up,down,fire,iVideo_Ptr.get());
  }

  sceRtcGetCurrentTick(&current_tick);//текущее значение частоты
  long double delta_time=static_cast<long double>(current_tick-begin_tick);
  unsigned long fps=0;
  if (fabs(delta_time)>0.0001) fps=static_cast<unsigned long>(tick_frequency/delta_time);
  char fps_text[255];
  sprintf(fps_text,"FPS:%i",fps);
  iVideo_Ptr->PutString(0,100,fps_text,0xFFFFFFFF);

  //выводим FPS
  //cVideo.PutString(WINDOW_WIDTH-FONT_WIDTH*(strlen(fps_text)+4),0,fps_text,0x00ffffff);

  /* long bat_percent=scePowerGetBatteryLifePercent();
  long bat_time=scePowerGetBatteryLifeTime();
  */

  sceDisplayWaitVblankStart();
  sceDisplaySetFrameBuf((void*)VideoBuffer,512,PSP_DISPLAY_PIXEL_FORMAT_8888,PSP_DISPLAY_SETBUF_IMMEDIATE);
  ActivePage++;
  ActivePage&=1;
  VideoBuffer=(uint32_t *)(0x44000000UL+272UL*512UL*4UL*ActivePage);//адрес видеопамяти
  iVideo_Ptr->SetVideoPointer(VideoBuffer+(480-320)/2,512);
 }
 //выходим из программы
 sceKernelExitGame();
 return(0);
}

