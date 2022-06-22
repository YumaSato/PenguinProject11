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
	int giveExpPoint;//�|���ꂽ�Ƃ��ɗ^����o���l
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int num;//�L�����N�^���ʔԍ�
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




class Character : public Creature {//�}�X�ڂɂ���L�����N�^�[
public:
	int selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
	void test();
	//void changeDirection();
	bool walk( Grid** board, Emperor* handledCharacters) override;
	bool attack( Grid** board, Emperor* handledCharacters);
	Character();//�L�����N�^�̃R���X�g���N�^
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













class Grid {//�e�}�X
public:
	State state = VACANT;//�}�X�ڂ̏�ԁB1:�n�ʁ@2:���@3:�ŏ�
	Creature* creature = NULL;//�}�X�ڂɂ��郂���X�^�[or�L�����N�^�[�̃|�C���^
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



class Item {//�}�X�ڂɗ����Ă�A�C�e��

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

	Emperor handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃A�h���X���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B

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