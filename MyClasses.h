#pragma once
#include <string>
#include "externs.h"
#include "consts.h"

using std::string;








class Bull;
class PenguinKids;
class Creature;
class Grid;


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
	virtual void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid board[][FIELDSIZE]);
	virtual int selectAction(PenguinKids *mobs_PenguinKids, Bull *mobs_Bull, Grid board[][FIELDSIZE]);
	virtual bool walk(int size, Grid board[][FIELDSIZE]);
	virtual void changeDirection(Grid board[][FIELDSIZE]);
	virtual bool attack(int size, Grid board[][FIELDSIZE]);
	bool kick(int size, Grid board[][FIELDSIZE]);
	virtual bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE]);
	virtual bool specialMovement2(int size, Grid board[][FIELDSIZE]);
	virtual int useItem(int size, Grid board[][FIELDSIZE]);
	virtual void test();
	void killed(Grid board[][FIELDSIZE]);
	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
	void DeleteCreature();
	void incubate(int checkX, int checkY, Grid board[][FIELDSIZE]);
	void damage(int checkX, int checkY, Grid board[][FIELDSIZE]);
};




class Character : public Creature {//�}�X�ڂɂ���L�����N�^�[
public:
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE]);
	void test();
	//void changeDirection();
	bool walk(int size, Grid board[][FIELDSIZE]) override;
	bool attack(int size, Grid board[][FIELDSIZE]);
	Character();//�L�����N�^�̃R���X�g���N�^
};



class Bull : public Character {
public:
	Bull();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid board[][FIELDSIZE])override;
	void test();
	bool walk(int size, Grid board[][FIELDSIZE]);
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE]);
	bool specialMovement2(int size, Grid board[][FIELDSIZE]);
	bool attack(int size, Grid board[][FIELDSIZE]);
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE]);
};



class PenguinKids : public Creature {
public:
	PenguinKids();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid board[][FIELDSIZE])override;
	void test();
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE]) override;
	bool specialMovement2(int size, Grid board[][FIELDSIZE]) override;
	bool attack(int size, Grid board[][FIELDSIZE]) override;
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE]);
};













class Grid {//�e�}�X
public:
	State state = VACANT;//�}�X�ڂ̏�ԁB1:�n�ʁ@2:���@3:�ŏ�
	Creature* creature = NULL;//�}�X�ڂɂ��郂���X�^�[or�L�����N�^�[�̃|�C���^
};




class Emperor : public Character {
public:
	Emperor(Team team, int num);
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE]);
	bool specialMovement2(int size, Grid board[][FIELDSIZE]);
};


class FireGod : public Character {

};


class LiquidGod : public Character {

};



class Item {//�}�X�ڂɗ����Ă�A�C�e��

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