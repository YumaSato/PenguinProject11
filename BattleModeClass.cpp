#include "DxLib.h"
#include <iostream>
#include <string>
#include <vector>
#include "MyClasses.h"
#include "consts.h"
#include "externs.h"

#include <algorithm>
#include <functional>

#include <cstdlib>
#include <ctime>

using namespace std;



void turnFinal();//�^�[���̍Ō�ɂ܂Ƃ߂čs���鑀��B

void enemyEnter(int turn);//�G���P�����铮��B

bool speedOrder(Creature* a, Creature* b);




	

	BattleMode_GameManager::BattleMode_GameManager() {//�R���X�g���N�^�B
		turnNum = 0;
	}


	void BattleMode_GameManager::BattleMode() {

		Emperor Emperor1(red, 0);//�C���X�^���X��
		handledCharacters[0] = &Emperor1;
		Emperor Emperor2(blue, 1);//�C���X�^���X��
		handledCharacters[1] = &Emperor2;

		DrawGraph(0, 0, HandleBoard, TRUE);
		WaitKey();
		gameMode = 1;

		while (gameMode == 1) {

			Emperor1.selectAction();

			Emperor2.selectAction();

			
			turnFinal();
			enemyEnter(turnNum);
			
			turnNum += 1;



		}
	}















	void turnFinal() {//�f��������mob���s�����Ă����֐��B
		string mobStatusMsg;
		string numSpeed;
		string numX;
		string numY;
		string s = "";
		string allS = "";
		//Creature* mobsSpeedOrder[2048];
		bool moveOrNot = FALSE;

		int mobNumberNow;
		mobNumberNow = mobNumber;//���̃^�[���Ŏ��s����y���M���L�b�Y�s���̉񐔂����郍�[�J���ϐ��ɁA�^�[�������s���J�n���_�ł̃��u�������B
		//����ɂ����s���Ƀ��u���������ă��[�v���Ƀ��[�v�񐔂��ς��o�O���������邱�Ƃ�h����B�����B

		for (int i = 0; i < num_penguinKids; i++) {//��������������B
			mobsSpeedOrder[i] = &mobs_PenguinKids[i];

		}
		for (int i = 0; i < num_bull; i++) {
			mobsSpeedOrder[i + num_penguinKids] = &mobs_Bull[i];//mobs_PenguinKids�̒��g�����I�������A���̌���bull�|�C���^�z��̒��g������Ă����B
		}



		//
		//for (int i = 0; i < mobNumber; i++) {
		//	s += "�A�h���X" + to_string(mobsSpeedOrder[i]->speed);//�f�������A�h���X�z��̃X�s�[�h��\���B
		//}
		//DrawString(800, 570, s.c_str(), WHITE);
		//WaitKey();

		sort(mobsSpeedOrder, mobsSpeedOrder + mobNumber, speedOrder);

		s = "";
		for (int i = 0; i < mobNumber; i++) {
			if (mobsSpeedOrder[i]->speed > 0) {
				s = "X" + std::to_string(mobsSpeedOrder[i]->x) + "Y" + std::to_string(mobsSpeedOrder[i]->y) + "�̑f����:"+ to_string(mobsSpeedOrder[i]->speed) + " \n";//�f�������A�h���X�z��̃X�s�[�h��\���B
				allS += s;
			}
		}
		exhibitScreen();
		DrawString(800, 570, allS.c_str(), WHITE);
		WaitKey();








		for (int i = 0; i < mobNumberNow ; i++) {

			//if (mobsspeedorder[i] == null) {
			//	continue;
			//}
			if (mobsSpeedOrder[i] == NULL) {//�X�s�[�h���z��ɂ��������Ȃ���ΏI���B
				return;
			}
			if (mobsSpeedOrder[i]->speed < 0) {//�X�s�[�h���}�C�i�X�A�܂莀��ł�����I���B
				return;
			}


			//if (mobsSpeedOrder[i]->pass == TRUE) {//�L�����͋��邯�Ǎs�����Ȃ���Ԃł���΃R���e�B�j���[�B
			//	continue;
			//}
			
			if (mobsSpeedOrder[i]->status == NORMAL || mobsSpeedOrder[i]->status == ELDER) {//����or�V�l�y���M���Ȃ�y���M����selectAction���ĂԁB
				moveOrNot = reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction();
			}


			if (moveOrNot == TRUE) {//�����s�����s���Ă�����
				exhibitScreen();
				numSpeed = (to_string(mobsSpeedOrder[i]->speed));
				numX = (to_string(mobsSpeedOrder[i]->x));
				numY = (to_string(mobsSpeedOrder[i]->y));
				mobStatusMsg= "X:" +numX+ ",Y:" +numY + "��"+ mobsSpeedOrder[i]->name +"\n �s�����x:" +numSpeed+ " �̗�:" + to_string(mobsSpeedOrder[i]->HP) + "/" + to_string(mobsSpeedOrder[i]->HP_Limit);
				DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
				WaitKey();
			}
		}

	}












	bool speedOrder(Creature* a, Creature* b) {
		
		if (a->speed == NULL) {
			a->speed = -1;
		}
		if (b->speed == NULL) {
			b->speed = -1;
		}
		return a->speed > b->speed;
	}


	//bool speedOrder(Creature* a, Creature* b) {
	//	if (a->speed == b->speed) {
	//		return a->speed < b->speed;
	//	}
	//	else {
	//		return a->speed > b->speed;
	//	}	
	//}





	void enemyEnter(int turn) {
		if (turn > 0 && turn < 10 && turn % 2 == 1) {

			Bull bull = Bull();
			int checkX = 1 + turn;
			int checkY = 1;
			bull.setMobs(red, 1,1,checkX,checkY,400000);
			mobs_Bull[num_bull] = bull;
			board[checkX][checkY].creature = &mobs_Bull[num_bull];
			mobNumber += 1;
			num_bull += 1;
		}


	}