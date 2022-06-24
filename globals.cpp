#include <string>
#include <vector>
#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"

using std::string;
using std::vector;

bool quitGame = FALSE;
int gameMode = 0;
int turnNum = 0;
int score = 0;
int clicking = 0;
int pushingKey = 0;


//Creature mobs[1024];
//vector<PenguinKids> kids;//�y���M���L�b�Y�̃C���X�^���X�𐶐����ɓ���Ă����ϒ��z��B
//PenguinKids sampleKids;


//PenguinKids mobs_PenguinKids[mobLimit];
//Bull mobs_Bull[mobLimit];


int mobNumber = 0;
int num_penguinKids = 0;
int num_bull = 0;

Creature* mobsSpeedOrder[2048];

string mainMsg;
string actionMsg;
string statusMsg;

//�\���摜
int HandleBoard;//�Q�[���Ղ̉摜�n���h��
int hHP;
int HandleCastle;
int handle[3][9][8];//[team][status][direction]�Ńy���M���̉摜�̃n���h�����i�[����3�����z��B
int handleMusic;
int handleField[64];
int handleBack[32];


//Grid board[FIELDSIZE][FIELDSIZE];

Character* handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃|�C���^���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B
//vector<Character*> handledCharacters(CHARACTERNUM);



int randomSide = 0;

BattleMode_GameManager* GameBuf;