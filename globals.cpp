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
//vector<PenguinKids> kids;//ペンギンキッズのインスタンスを生成毎に入れていく可変長配列。
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

//表示画像
int HandleBoard;//ゲーム盤の画像ハンドル
int hHP;
int HandleCastle;
int handle[3][9][8];//[team][status][direction]でペンギンの画像のハンドルを格納する3次元配列。
int handleMusic;
int handleField[64];
int handleBack[32];


//Grid board[FIELDSIZE][FIELDSIZE];

Character* handledCharacters[CHARACTERNUM];//操作可能なキャラクタのポインタを格納する変数。配列インデックスは、キャラ番号。
//vector<Character*> handledCharacters(CHARACTERNUM);



int randomSide = 0;

BattleMode_GameManager* GameBuf;