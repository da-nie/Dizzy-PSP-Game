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
 //устанавливаем обработчики
 SetupCallbacks();
 //настраиваем управление
 sceCtrlSetSamplingCycle(0);
 sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
 //активируем видеорежим
 uint32_t ActivePage=0;//видимая видеостраница
 sceDisplayWaitVblankStart();
 uint16_t *VideoBuffer=(uint16_t *)(0x44000000UL+272UL*512UL*2UL*ActivePage);//адрес видеопамяти
 sceDisplaySetFrameBuf((void*)VideoBuffer,512,PSP_DISPLAY_PIXEL_FORMAT_565,PSP_DISPLAY_SETBUF_NEXTFRAME);
 sceDisplaySetMode(0,480,272);
 //очистим экран
 memset(VideoBuffer,0,272*512*sizeof(uint16_t));
 uint16_t *VideoBuffer_Page1=(uint16_t *)(0x44000000UL+272UL*512UL*2UL*1);//адрес видеопамяти
 memset(VideoBuffer_Page1,0,272*512*sizeof(uint16_t));


 CGame cGame;
 std::shared_ptr<IVideo> iVideo_Ptr;
 iVideo_Ptr.reset(IVideo::CreateNewCVideoSoftware(CGame::SCREEN_WIDTH,CGame::SCREEN_HEIGHT));
 iVideo_Ptr->Init();

 iVideo_Ptr->SetVideoPointer(VideoBuffer+(480-320)/2+512*(272-240)/2,512);
 bool enabled=cGame.Init(iVideo_Ptr.get());
 sceDisplayWaitVblankStart();
 sceDisplaySetFrameBuf((void*)VideoBuffer,512,PSP_DISPLAY_PIXEL_FORMAT_565,PSP_DISPLAY_SETBUF_IMMEDIATE);


 SceCtrlData pad;
 while(done==false)
 {
  iVideo_Ptr->SetVideoPointer(VideoBuffer+(480-320)/2+512*(272-240)/2,512);

  u64 tick_frequency=sceRtcGetTickResolution();
  u64 begin_tick;
  u64 current_tick;
  sceRtcGetCurrentTick(&begin_tick);//текущее значение частоты

  //сканируем клавиатуру
  sceCtrlReadBufferPositive(&pad,1);
  bool no_change_page=true;
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
   if (pad.Buttons&PSP_CTRL_CROSS) up=true;
   if (pad.Buttons&PSP_CTRL_DOWN) down=true;
   if (pad.Buttons&PSP_CTRL_CIRCLE) fire=true;
   if (pad.Buttons&PSP_CTRL_START) break;
   no_change_page=cGame.OnTimer(left,right,up,down,fire,iVideo_Ptr.get());
  }
  /*
  sceRtcGetCurrentTick(&current_tick);//текущее значение частоты
  long double delta_time=static_cast<long double>(current_tick-begin_tick);
  unsigned long fps=0;
  if (fabs(delta_time)>0.0001) fps=static_cast<unsigned long>(tick_frequency/delta_time);
  char fps_text[255];
  sprintf(fps_text,"FPS:%i",fps);
  iVideo_Ptr->PutString(0,100,fps_text,0xFFFF);
  */

  /* long bat_percent=scePowerGetBatteryLifePercent();
  long bat_time=scePowerGetBatteryLifeTime();
  */
  sceDisplayWaitVblankStart();
  sceDisplaySetFrameBuf((void*)VideoBuffer,512,PSP_DISPLAY_PIXEL_FORMAT_565,PSP_DISPLAY_SETBUF_IMMEDIATE);

  uint16_t *last_vptr=VideoBuffer;
  ActivePage++;
  ActivePage&=1;
  VideoBuffer=(uint16_t *)(0x44000000UL+272UL*512UL*2UL*ActivePage);//адрес видеопамяти
  if (no_change_page==true)
  {
   memcpy(VideoBuffer,last_vptr,272UL*512UL*2UL);
  }

  //синхронизируем по таймеру
  while(done==false)
  {
   sceRtcGetCurrentTick(&current_tick);//текущее значение частоты
   double time_span=((double)(current_tick-begin_tick))/(double)tick_frequency;//прошедшее время
   if (time_span>=1.0f/30.0f) break;//30 FPS
  }
 }
 //выходим из программы
 sceKernelExitGame();
 return(0);
}

