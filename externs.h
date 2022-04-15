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
extern int HandleHP;
extern int HandleCastle;
extern int handle[3][5][8];

extern Grid board[FIELDSIZE][FIELDSIZE];//そのマスに何がいるか

extern Character* handledCharacters[CHARACTERNUM];//操作可能なキャラクタのアドレスを格納する変数。配列インデックスは、キャラ番号。
//extern vector<Character*> handledCharacters(CHARACTERNUM);



extern int yieldStopSide[4];//敵が出現する側を示す。3番目の値がでなくなる、というときは、3番目の値が3ではなく-1になる。
extern int randomSide;


void exhibitScreen();
void exhibitStatusMsg();
