#pragma once
#include <string>
#include "externs.h"
#include "consts.h"

using std::string;








class Bull;
class PenguinKids;
class Creature;
class Grid;
class Character;
class Emperor;


class Creature {//升目にいる生物
private:
	int directionX;//向いている方向（左は-1、右は1）
	int directionY;//向いている方向（上は-1、下は1）
	Direction compass;

public:
	string name;
	Team team;//ペンギン不在:0、赤ペンギン:1、青ペンギン:2
	Status status;//卵:1、大人:2、老人:3、皇帝:4
	int x;
	int y;
	int HP;
	int HP_Limit;
	int levelUp;//レベル
	int expPoint;//経験値量
	int giveExpPoint;//倒されたときに与える経験値
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int num;//キャラクタ識別番号
	bool skip;
	bool enemy;


	Creature();
	virtual void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, Grid** board, Emperor* handledCharacters);
	virtual int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
	virtual bool walk( Grid** board, Emperor* handledCharacters);
	virtual void changeDirection(Grid** board, Emperor* handledCharacters);
	virtual bool attack( Grid** board, Emperor* handledCharacters);
	bool kick( Grid** board, Emperor* handledCharacters);
	virtual bool specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
	virtual bool specialMovement2( Grid** board, Emperor* handledCharacters);
	virtual int useItem( Grid** board, Emperor* handledCharacters);
	virtual void test();
	void killed(Grid** board, Emperor* handledCharacters);
	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
	void DeleteCreature();
	void incubate(int checkX, int checkY, Grid** board, Emperor* handledCharacters);
	void damage(int checkX, int checkY, Grid** board, Emperor* handledCharacters);
};




class Character : public Creature {//マス目にいるキャラクター
public:
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
	void test();
	//void changeDirection();
	bool walk( Grid** board, Emperor* handledCharacters) override;
	bool attack( Grid** board, Emperor* handledCharacters);
	Character();//キャラクタのコンストラクタ
};



class Bull : public Character {
public:
	Bull();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, Grid** board, Emperor* handledCharacters)override;
	void test();
	bool walk( Grid** board, Emperor* handledCharacters);
	bool specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
	bool specialMovement2( Grid** board, Emperor* handledCharacters);
	bool attack( Grid** board, Emperor* handledCharacters);
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
};



class PenguinKids : public Creature {
public:
	PenguinKids();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, Grid** board, Emperor* handledCharacters)override;
	void test();
	bool specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) override;
	bool specialMovement2( Grid** board, Emperor* handledCharacters) override;
	bool attack( Grid** board, Emperor* handledCharacters) override;
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
};













class Grid {//各マス
public:
	State state = VACANT;//マス目の状態。1:地面　2:水　3:毒沼
	Creature* creature = NULL;//マス目にいるモンスターorキャラクターのポインタ
};




class Emperor : public Character {
public:
	Emperor();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, Grid** board, Emperor* handledCharacters)override;
	bool specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
	bool specialMovement2( Grid** board, Emperor* handledCharacters);
	int GetExpPoint(int expP);
};


class FireGod : public Character {

};


class LiquidGod : public Character {

};



class Item {//マス目に落ちてるアイテム

};

class Trap {

};




class BattleMode_GameManager {
public:
	BattleMode_GameManager(int xSize, int ySize);

	int BattleMode(int stageLevel);
	//const int FIELDSIZE;

	PenguinKids mobs_PenguinKids[mobLimit];
	Bull mobs_Bull[mobLimit];

	Emperor handledCharacters[CHARACTERNUM];//操作可能なキャラクタのアドレスを格納する変数。配列インデックスは、キャラ番号。

	int sizeX;
	int sizeY;

	int exhibitX;
	int exhibitY;

	Grid** board;
	Emperor* Emperor1;
	Emperor* Emperor2;


	int GameOver();
	int GameClear();
	int TurnFinal();
	int ScreenMove(int markX,int markY);
	int GoNext(int markX, int markY);

	~BattleMode_GameManager();

};




//class RoadMode_GameManager {
//public:
//	RoadMode_GameManager(int xSize, int ySize);
//
//	int RoadMode(int stageLevel);
//
//	PenguinKids mobs_PenguinKids[mobLimit];
//	Bull mobs_Bull[mobLimit];
//
//	Emperor handledCharacters[CHARACTERNUM];
//
//	Grid **board;
//
//};