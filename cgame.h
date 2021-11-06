#ifndef C_GAME_H
#define C_GAME_H

//****************************************************************************************************
//����� ����
//****************************************************************************************************

//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include "ivideo.h"
#include "cfontprinter.h"
#include "csprite.h"
#include "ipart.h"
#include "iconditionalexpression.h"
#include "cgamestate.h"
#include "cdizzy.h"

//****************************************************************************************************
//����������������
//****************************************************************************************************

//****************************************************************************************************
//���������
//****************************************************************************************************

//****************************************************************************************************
//��������������� ����������
//****************************************************************************************************

//****************************************************************************************************
//����� ����
//****************************************************************************************************
class CGame
{
 public:
  //-������������---------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  static const uint16_t BLACK_COLOR=(0<<11)|(0<<5)|(0<<0);//������ ����
  static const uint16_t YELLOW_COLOR=(31<<11)|(63<<5)|(0<<0);//����� ����

  static const uint8_t BLEND_COLOR_B=81>>3;//���������� ����, ��������� R
  static const uint8_t BLEND_COLOR_G=162>>2;//���������� ����, ��������� G
  static const uint8_t BLEND_COLOR_R=243>>3;//���������� ����, ��������� B
  static const uint16_t SKY_COLOR=(BLEND_COLOR_R<<11)|(BLEND_COLOR_G<<5)|(BLEND_COLOR_B<<0);//���� ����
  static const uint16_t BLEND_COLOR=(BLEND_COLOR_R<<11)|(BLEND_COLOR_G<<5)|(BLEND_COLOR_B<<0);//���������� ����

  static const uint8_t NO_BARRIER_COLOR_R=0;//���� ���������� �����������, ��������� R
  static const uint8_t NO_BARRIER_COLOR_G=0;//���� ���������� �����������, ��������� G
  static const uint8_t NO_BARRIER_COLOR_B=0;//���� ���������� �����������, ��������� B
  static const uint32_t NO_BARRIER_COLOR=(NO_BARRIER_COLOR_R<<11)|(NO_BARRIER_COLOR_G<<5)|(NO_BARRIER_COLOR_B<<0);//���� ���������� �����������

  static const uint16_t ENERGY_GOOD_COLOR=(8<<11)|(63<<5)|(8<<0);//���� "�������"
  static const uint16_t ENERGY_NORMAL_COLOR=(8<<11)|(63<<5)|(31<<0);//���� "������"
  static const uint16_t ENERGY_BAD_COLOR=(8<<11)|(8<<5)|(31<<0);//���� "�����"

  static const int32_t TILES_ANIMATION_TICK_COUNTER_DIVIDER=7;//�������� ����� �������� ������
  static const int32_t FLASH_TICK_COUNTER_DIVIDER=6;//�������� ����� ��� ������� ���������
  static const int32_t DIZZY_ANIMATION_TICK_COUNTER_DIVIDER=3;//�������� ����� �������� �����
  static const int32_t MOVE_TICK_COUNTER_DIVIDER=7;//�������� ����� ����������� �����

  static const int32_t DIZZY_WIDTH=25;//������ ������� �����
  static const int32_t DIZZY_HEIGHT=22;//������ ������� �����

  static const int32_t SCREEN_WIDTH=320;//������ ������
  static const int32_t SCREEN_HEIGHT=240;//������ ������

  static const int32_t TILE_WIDTH=16;//������ �����
  static const int32_t TILE_HEIGHT=16;//������ �����
  static const int32_t TILE_BORDER_WIDTH=1;//������ �����
  static const int32_t TILE_BORDER_HEIGHT=1;//������ �����
  static const int32_t TILE_WITH_BORDER_WIDTH=TILE_WIDTH+TILE_BORDER_WIDTH+TILE_BORDER_WIDTH;//������ ����� � ������
  static const int32_t TILE_WITH_BORDER_HEIGHT=TILE_HEIGHT+TILE_BORDER_HEIGHT+TILE_BORDER_HEIGHT;//������ ����� � ������

  static const int32_t USE_DELAY_COUNTER_MAX_VALUE=5;//������������ ��������� �������� �������� �� ���������� ������� ������ "������������"

  static const int32_t MAX_INVENTORY_SIZE=3;//������������ ���������� ��������� � ���������

  static const int32_t SPEED_X=2;//�������� ����� �� X
  static const int32_t SPEED_Y=2;//�������� ����� �� Y

  static const size_t STRING_BUFFER_SIZE=255;//������ ������ ������
 private:
  //-����������-----------------------------------------------------------------------------------------
  CDizzy cDizzy;//�����

  CSprite cSprite_Dizzy;//������ �����
  CSprite cSprite_Frame;//�����
  CSprite cSprite_ScreenFrame;//����� ��� ������
  CSprite cSprite_Header;//��������� ������

  CSprite cSprite_Tiles;//�����
  CSprite cSprite_TilesBarrier;//��������������� ������

  int32_t dX;//�������� �����
  int32_t dY;

  bool MoveControl;//��������� �� Dizzy �������

  int32_t TilesAnimationTickCounter;//������� �������� ������
  int32_t DizzyAnimationTickCounter;//������� �������� �����
  int32_t FlashTickCounter;//������� ������� ������� � ���������
  int32_t MoveTickCounter;//������� ����������� �����

  std::shared_ptr<CFontPrinter> cFontPrinter_Ptr;//��������� �� ����� ������ �� ��������

  CGameState cGameState;//��������� ����

  uint32_t UseDelayCounter;//������� �� ���������� ������� ������ "������������"
 public:
  //-�����������----------------------------------------------------------------------------------------
  CGame(void);
  //-����������-----------------------------------------------------------------------------------------
  ~CGame();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  bool OnTimer(bool left,bool right,bool up,bool down,bool fire,IVideo *iVideo_Ptr);//��������� �������
  bool Init(IVideo *iVideo_Ptr);//�������������
 private:
  //-�������� �������-----------------------------------------------------------------------------------
  void OnPaint(IVideo *iVideo_Ptr);//���������� ��������
  void KeyboardControl(bool left,bool right,bool up,bool down,bool fire);//���������� �� ����������
  void PressUse(void);//������ ������ "������������"
  void DizzyAnimation(void);//��������� �������� �����
  void DizzyMoveProcessing(IVideo *iVideo_Ptr);//��������� �������� �����
  void TilesAnimation(void);//�������� ���� ������
  void ConditionalProcessing(void);//��������� ��������� �������
  void DizzyEnergyProcessing(IVideo *iVideo_Ptr);//��������� ��������� ������� �����
  void Processing(IVideo *iVideo_Ptr);//��������� �������� ����
  bool IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//��������� ������������ � ������� ��� �����
  bool IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//��������� ������������ � ������� ������� �����
  void DrawBarrier(IVideo *iVideo_Ptr);//���������� ��������
  void DrawMap(IVideo *iVideo_Ptr);//���������� �����
  void DrawFirstPlaneMap(IVideo *iVideo_Ptr);//���������� ����� ��������� �����
  void DrawBeforeBackgroundMap(IVideo *iVideo_Ptr);//���������� ����� ������ ����� �����
  void PutMessage(CGameState::SMessage &sMessage,IVideo *iVideo_Ptr);//����� ���������
  void PutFrame(int32_t x,int32_t y,int32_t text_width,int32_t text_height,IVideo *iVideo_Ptr);//���������� ����� � �������� ���������� ����� ��� ������ (x,y,text_width,text_height - ���� ������ ������)
  void PutInventory(IVideo *iVideo_Ptr);//������� ���������
  void SetDescription(const std::string &name,const std::string &description);//������ ��������
  void PushInventory(std::shared_ptr<IPart> iPart_Ptr);//�������� � ���������
  std::shared_ptr<IPart> PopInventory(size_t index);//������ �� ���������
  void DrawScreenFrame(IVideo *iVideo_Ptr);//���������� �������� �����
  void VisitTree(std::shared_ptr<CGameState::SQuadricTree> &sQuadricTree_Ptr,CGameState::SVisitTree &sVisitTree);//������� ������ ������
  bool LoadMap(const std::string &file_name);//��������� �����
  std::shared_ptr<CGameState::SQuadricTree> LoadQuadricTree(std::ifstream &file);//��������� ������������ ������
  bool LoadConditional(const std::string &path,std::vector<std::string> &log);//��������� ������� ����
  bool LoadConditionalFile(const std::string &file_name,std::vector<std::string> &log);//��������� ���� ������� ����
  void ChangeDizzyCoord(int32_t dx,int32_t dy,IVideo *iVideo_Ptr);//�������� ���������� �����, ����������� ����� � ������������ �������
  void MoveMap(IVideo *iVideo_Ptr);//��������� ����������� �����, ���� ���������
  bool MoveMapStep(int32_t width,int32_t height,int32_t offset_y);//��������� ����������� ����� �� ���� ���, ���� ���������
};

#endif
