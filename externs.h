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
class Emperor;
class BattleMode_GameManager;


extern bool quitGame;
extern int gameMode;
extern int turnNum;
extern int score;
extern int clicking;

//extern Creature mobs[1024];
//extern vector<PenguinKids> kids;//ペンギンキッズのインスタンスを生成毎に入れていく可変長配列。


//extern PenguinKids mobs_PenguinKids[mobLimit];
//extern Bull mobs_Bull[mobLimit];

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
extern int handleMusic;

//extern Grid board[FIELDSIZE][FIELDSIZE];//そのマスに何がいるか

//extern Character* handledCharacters[CHARACTERNUM];//操作可能なキャラクタのアドレスを格納する変数。配列インデックスは、キャラ番号。
//extern vector<Character*> handledCharacters(CHARACTERNUM);

extern BattleMode_GameManager* GameBuf;

extern int randomSide;


void exhibitScreen(int markX, int markY, bool attention, Grid** board, Emperor* handledCharacters);
void exhibitStatusMsg(Emperor* handledCharacters);
void exhibitDamage(int markX, int markY, int damageX, int damageY, bool attention, int damageHP, Grid** board, Emperor* handledCharacters);
void exhibitStatus(int markX, int markY, int statusX, int statusY, bool attention, int color, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
void exhibitRolling(int kickX, int kickY, int dx, int dy, int distance, Grid** board, Emperor* handledCharacters);
void exhibitRule();
