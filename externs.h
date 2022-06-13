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


extern bool quitGame;
extern int gameMode;
extern int turnNum;
extern int score;
extern int clicking;

//extern Creature mobs[1024];
//extern vector<PenguinKids> kids;//�y���M���L�b�Y�̃C���X�^���X�𐶐����ɓ���Ă����ϒ��z��B


//extern PenguinKids mobs_PenguinKids[mobLimit];
//extern Bull mobs_Bull[mobLimit];

extern int mobNumber;
extern int num_penguinKids;
extern int num_bull;

extern Creature* mobsSpeedOrder[2048];
//extern Creature* mobsSpeedOrder[mobLimit];//�f�������Ƀ��u�L�����̃A�h���X���i�[����ϐ��B

extern string mainMsg;
extern string actionMsg;
extern string statusMsg;

extern int HandleBoard;
extern int hHP;
extern int HandleCastle;
extern int handle[3][9][8];

//extern Grid board[FIELDSIZE][FIELDSIZE];//���̃}�X�ɉ������邩

//extern Character* handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃A�h���X���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B
//extern vector<Character*> handledCharacters(CHARACTERNUM);



extern int randomSide;


void exhibitScreen(int markX, int markY, bool attention, Grid board[][FIELDSIZE], Character *handledCharacters);
void exhibitStatusMsg(Character *handledCharacters);
void exhibitDamage(int markX, int markY, int damageX, int damageY, bool attention, int damageHP, Grid board[][FIELDSIZE], Character *handledCharacters);
void exhibitStatus(int markX, int markY, int statusX, int statusY, bool attention, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character *handledCharacters);
void exhibitRolling(int kickX, int kickY, int dx, int dy, int distance, Grid board[][FIELDSIZE], Character *handledCharacters);
void exhibitRule();
