#include <string>
#include <vector>
#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"

using std::string;
using std::vector;

bool debug_mode = FALSE;
int gameMode = 0;
int turnNum = 0;



//Creature mobs[1024];
//vector<PenguinKids> kids;//�y���M���L�b�Y�̃C���X�^���X�𐶐����ɓ���Ă����ϒ��z��B
//PenguinKids sampleKids;


PenguinKids mobs_PenguinKids[mobLimit];
Bull mobs_Bull[mobLimit];


int mobNumber = 0;
int num_penguinKids = 0;
int num_bull = 0;

Creature* mobsSpeedOrder[2048];

string mainMsg;
string actionMsg;
string statusMsg;

//�\���摜
int HandleBoard;//�Q�[���Ղ̉摜�n���h��
int HandleHP;
int HandleCastle;
int handle[3][5][8];//[team][status][direction]�Ńy���M���̉摜�̃n���h�����i�[����3�����z��B

Grid board[FIELDSIZE][FIELDSIZE];

Character* handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃|�C���^���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B
//vector<Character*> handledCharacters(CHARACTERNUM);



int yieldStopSide[4] = {0,1,2,3};//�G���o�����鑤�������B3�Ԗڂ̒l���łȂ��Ȃ�A�Ƃ����Ƃ��́A3�Ԗڂ̒l��3�ł͂Ȃ�-1�ɂȂ�B
int randomSide = 0;