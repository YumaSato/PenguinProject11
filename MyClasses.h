#pragma once
#include <string>
#include "externs.h"
#include "consts.h"

using std::string;








class BattleMode_GameManager {
public:
	int turnNum;
	BattleMode_GameManager();
	void BattleMode();



};




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
	virtual void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed);
	virtual bool selectAction();
	virtual bool walk(int size);
	virtual void changeDirection();
	virtual bool attack(int size);
	bool kick(int size);
	virtual bool specialMovement1(int size);
	virtual bool specialMovement2(int size);
	virtual int useItem(int size);
	virtual void test();
	void killed();
	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
	void DeleteCreature();
	void incubate(int checkX, int checkY);
	void damage(int checkX, int checkY);
};



class PenguinKids : public Creature {
public:
	PenguinKids();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed)override;
	void test();
	bool specialMovement1 (int size) override;
	bool specialMovement2(int size) override;
	bool attack(int size) override;
	bool selectAction() override;
};


class Grid {//各マス
public:
	char state = VACANT;//マス目の状態。1:地面　2:水　3:毒沼
	Creature* creature = NULL;//マス目にいるモンスターorキャラクターのポインタ
};


class Character : public Creature {//マス目にいるキャラクター
public:
	bool selectAction();
	void test();
	void changeDirection();
	bool walk(int size) override;
	bool attack(int size);
	Character();//キャラクタのコンストラクタ
};

class Emperor : public Character {
public:
	Emperor(Team team, int num);
	bool specialMovement1(int size);
	bool specialMovement2(int size);
};


class FireGod : public Character {

};


class LiquidGod : public Character {

};


class Bull : public Character {
public:
	Bull();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed)override;
	void test();
	bool specialMovement1(int size) override;
	bool specialMovement2(int size) override;
	bool attack(int size) override;
	bool selectAction() override;
};

class Item {//マス目に落ちてるアイテム

};

class Trap {

};