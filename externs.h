#pragma once
#include <string>
#include <vector>
#include "consts.h"
#include "MyClasses.h"

using std::vector;
using std::string;

class PenguinKids;//コンパイラに怒られないためのおまじない。「PenguinKidsっていうクラスがあるんだよ。内容はあとで定義するよ。」という意味。
class Grid;
class Creature;
class Character;
class Bull;


extern bool debug_mode;
extern int gameMode;
extern int turnNum;

//extern Creature mobs[1024];
//extern vector<PenguinKids> kids;//ペンギンキッズのインスタンスを生成毎に入れていく可変長配列。


extern PenguinKids mobs_PenguinKids[mobLimit];
extern Bull mobs_Bull[mobLimit];

extern int mobNumber;
extern int num_penguinKids;
extern int num_bull;

extern Creature* mobsSpeedOrder[2048];
//extern Creature* mobsSpeedOrder[mobLimit];//素早さ順にモブキャラのアドレスを格納する変数。

extern string mainMsg;
extern string actionMsg;
extern string statusMsg;

extern int HandleBoard;
extern int hHP;
extern int HandleCastle;
extern int handle[3][9][8];

extern Grid board[FIELDSIZE][FIELDSIZE];//そのマスに何がいるか

extern Character* handledCharacters[CHARACTERNUM];//操作可能なキャラクタのアドレスを格納する変数。配列インデックスは、キャラ番号。
//extern vector<Character*> handledCharacters(CHARACTERNUM);



extern int randomSide;


void exhibitScreen(int markX, int markY, bool attention);
void exhibitStatusMsg();
void exhibitDamage(int markX, int markY, int damageX, int damageY, bool attention, int damageHP);
