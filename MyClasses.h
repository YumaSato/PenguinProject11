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




class Creature {//���ڂɂ��鐶��
private:
	int directionX;//�����Ă�������i����-1�A�E��1�j
	int directionY;//�����Ă�������i���-1�A����1�j
	Direction compass;

public:
	string name;
	Team team;//�y���M���s��:0�A�ԃy���M��:1�A�y���M��:2
	Status status;//��:1�A��l:2�A�V�l:3�A�c��:4
	int x;
	int y;
	int HP;
	int HP_Limit;
	int stamina;//���s�����̗̑�
	int staminaLimit;
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int num;//�L�����N�^���ʔԍ�
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


class Grid {//�e�}�X
public:
	char state = VACANT;//�}�X�ڂ̏�ԁB1:�n�ʁ@2:���@3:�ŏ�
	Creature* creature = NULL;//�}�X�ڂɂ��郂���X�^�[or�L�����N�^�[�̃|�C���^
};


class Character : public Creature {//�}�X�ڂɂ���L�����N�^�[
public:
	bool selectAction();
	void test();
	void changeDirection();
	bool walk(int size) override;
	bool attack(int size);
	Character();//�L�����N�^�̃R���X�g���N�^
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

class Item {//�}�X�ڂɗ����Ă�A�C�e��

};

class Trap {

};