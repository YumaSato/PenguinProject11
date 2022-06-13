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
	int levelUp;//���x��
	int expPoint;//�o���l��
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int num;//�L�����N�^���ʔԍ�
	bool skip;
	bool enemy;


	Creature();
	virtual void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual int selectAction(PenguinKids *mobs_PenguinKids, Bull *mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual bool walk(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual void changeDirection(Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual bool attack(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	bool kick(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual bool specialMovement2(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual int useItem(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	virtual void test();
	void killed(Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
	void DeleteCreature();
	void incubate(int checkX, int checkY, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	void damage(int checkX, int checkY, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
};




class Character : public Creature {//�}�X�ڂɂ���L�����N�^�[
public:
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters);
	void test();
	//void changeDirection();
	bool walk(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]) override;
	bool attack(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	Character();//�L�����N�^�̃R���X�g���N�^
};



class Bull : public Character {
public:
	Bull();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM])override;
	void test();
	bool walk(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	bool specialMovement2(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	bool attack(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
};



class PenguinKids : public Creature {
public:
	PenguinKids();
	void setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM])override;
	void test();
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]) override;
	bool specialMovement2(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]) override;
	bool attack(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]) override;
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
};













class Grid {//�e�}�X
public:
	State state = VACANT;//�}�X�ڂ̏�ԁB1:�n�ʁ@2:���@3:�ŏ�
	Creature* creature = NULL;//�}�X�ڂɂ��郂���X�^�[or�L�����N�^�[�̃|�C���^
};




class Emperor : public Character {
public:
	Emperor(Team team, int num);
	bool specialMovement1(int size, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
	bool specialMovement2(int size, Grid board[][FIELDSIZE], Character* handledCharacters[CHARACTERNUM]);
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

	Character* handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃A�h���X���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B


	//Grid* board = new Grid[FIELDSIZE][FIELDSIZE];

	Grid board[FIELDSIZE][FIELDSIZE];

};