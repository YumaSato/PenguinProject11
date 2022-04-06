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



Creature mobs[1024];
vector<PenguinKids> kids;//ペンギンキッズのインスタンスを生成毎に入れていく可変長配列。
PenguinKids sampleKids;


PenguinKids mobs_PenguinKids[mobLimit];


int mobNumber = 0;
Creature* mobsSpeedOrder[mobLimit];

string mainMsg;
string actionMsg;
string statusMsg;

//表示画像
int HandleBoard;//ゲーム盤の画像ハンドル
int handle[3][5][8];//[team][status][direction]でペンギンの画像のハンドルを格納する3次元配列。

Grid board[FIELDSIZE][FIELDSIZE];

Character* handledCharacters[CHARACTERNUM];//操作可能なキャラクタのポインタを格納する変数。配列インデックスは、キャラ番号。
//vector<Character*> handledCharacters(CHARACTERNUM);