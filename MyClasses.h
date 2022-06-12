#pragma once
#include <string>
#include "externs.h"
#include "consts.h"

using std::string;








class Bull;
class PenguinKids;
class Creature;
class Grid;


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
	int stamina;//歩行距離の体力
	int staminaLimit;
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int num;//キャラクタ識別番号
	bool skip;
	bool enemy;


	Creature();
	virtual void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid* board);
	virtual int selectAction(PenguinKids *mobs_PenguinKids, Bull *mobs_Bull, Grid *board);
	virtual bool walk(int size, Grid* board);
	virtual void changeDirection(Grid* board);
	virtual bool attack(int size, Grid* board);
	bool kick(int size, Grid* board);
	virtual bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid* board);
	virtual bool specialMovement2(int size, Grid* board);
	virtual int useItem(int size, Grid* board);
	virtual void test();
	void killed(Grid* board);
	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
	void DeleteCreature();
	void incubate(int checkX, int checkY, Grid* board);
	void damage(int checkX, int checkY, Grid* board);
};




class Character : public Creature {//マス目にいるキャラクター
public:
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid* board);
	void test();
	void changeDirection();
	bool walk(int size, Grid* board) override;
	bool attack(int size, Grid* board);
	Character();//キャラクタのコンストラクタ
};



class Bull : public Character {
public:
	Bull();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid* board)override;
	void test();
	bool walk(int size, Grid* board);
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid* board);
	bool specialMovement2(int size, Grid* board);
	bool attack(int size, Grid* board);
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid* board);
};



class PenguinKids : public Creature {
public:
	PenguinKids();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid* board)override;
	void test();
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid* board) override;
	bool specialMovement2(int size, Grid* board) override;
	bool attack(int size, Grid* board) override;
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid* board) override;
};













class Grid {//各マス
public:
	State state = VACANT;//マス目の状態。1:地面　2:水　3:毒沼
	Creature* creature = NULL;//マス目にいるモンスターorキャラクターのポインタ
};




class Emperor : public Character {
public:
	Emperor(Team team, int num);
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid* board);
	bool specialMovement2(int size, Grid* board);
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
	BattleMode_GameManager();
	int BattleMode(int level);

	PenguinKids mobs_PenguinKids[mobLimit];
	Bull mobs_Bull[mobLimit];



	Grid board[FIELDSIZE][FIELDSIZE];

};