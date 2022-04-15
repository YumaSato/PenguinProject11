#pragma once
#include <string>
#include <vector>
#include "consts.h"
#include "MyClasses.h"

using std::vector;
using std::string;

class PenguinKids;//�R���p�C���ɓ{���Ȃ����߂̂��܂��Ȃ��B�uPenguinKids���Ă����N���X������񂾂�B���e�͂��ƂŒ�`�����B�v�Ƃ����Ӗ��B
class Grid;
class Creature;
class Character;
class Bull;


extern bool debug_mode;
extern int gameMode;
extern int turnNum;

//extern Creature mobs[1024];
//extern vector<PenguinKids> kids;//�y���M���L�b�Y�̃C���X�^���X�𐶐����ɓ���Ă����ϒ��z��B


extern PenguinKids mobs_PenguinKids[mobLimit];
extern Bull mobs_Bull[mobLimit];

extern int mobNumber;
extern int num_penguinKids;
extern int num_bull;

extern Creature* mobsSpeedOrder[2048];
//extern Creature* mobsSpeedOrder[mobLimit];//�f�������Ƀ��u�L�����̃A�h���X���i�[����ϐ��B

extern string mainMsg;
extern string actionMsg;
extern string statusMsg;

extern int HandleBoard;
extern int HandleHP;
extern int HandleCastle;
extern int handle[3][5][8];

extern Grid board[FIELDSIZE][FIELDSIZE];//���̃}�X�ɉ������邩

extern Character* handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃A�h���X���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B
//extern vector<Character*> handledCharacters(CHARACTERNUM);



extern int yieldStopSide[4];//�G���o�����鑤�������B3�Ԗڂ̒l���łȂ��Ȃ�A�Ƃ����Ƃ��́A3�Ԗڂ̒l��3�ł͂Ȃ�-1�ɂȂ�B
extern int randomSide;


void exhibitScreen();
void exhibitStatusMsg();
