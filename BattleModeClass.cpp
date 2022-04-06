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

//bool speedOrder(Creature* a, Creature* b);




	

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


		}
	}















	void turnFinal() {//�f��������mob���s�����Ă����֐��B
		string mobStatusMsg;
		string numSpeed;
		string numX;
		string numY;
		int sortSpeedOrder[mobLimit];
		int mobNumberNow;

		mobNumberNow = mobNumber;

		for (int i = 0; i < mobNumber; i++) {
			sortSpeedOrder[i] = mobs_PenguinKids[i].speed;//�܂��f�������őf����������int�z��ɁAmobs��num���őf�����l�����B



			/*if (sortSpeedOrder[i] == NULL) {
				sortSpeedOrder[i] = -1;
			}*/
			/*numSpeed = (to_string(sortSpeedOrder[i]));
			DrawString(800, 560 + i*20, numSpeed.c_str(), WHITE);
			WaitKey();*/
		}	

		sort(sortSpeedOrder, sortSpeedOrder + mobNumber, greater<>());//�~���ŕ��בւ��B
		//�f�������őf����������int�z��̒��g���A�����Ƒf�������ɕ��בւ���B


		string s = "";
		for (int i = 0; i < mobNumber; i++) {
			s += " " + to_string(sortSpeedOrder[i]);
		}
		DrawString(800, 550, s.c_str(), WHITE);
		WaitKey();


		for (int sort_i = 0; sort_i < mobNumber; sort_i++) {//�f������int�z�񂲂ƂɁA

			if (sortSpeedOrder[sort_i] == NULL) {
				continue;
			}

			for (int mobs_i = 0; mobs_i < mobNumber; mobs_i++) {//�emobs�𒲂ׂāA


				//numSpeed = (to_string(mobs_PenguinKids[mobs_i].speed));
				//DrawString(800, 660 + mobs_i*20, numSpeed.c_str(), WHITE);
				//WaitKey();

				if (sortSpeedOrder[sort_i] == mobs_PenguinKids[mobs_i].speed) {//�f������int�̑f������mobs�̑f��������v������
					mobsSpeedOrder[sort_i] = &mobs_PenguinKids[mobs_i];//�f�������A�h���X�z��ɑ���B
				}
			}
		}

		//s = "";
		//for (int i = 0; i < mobNumber; i++) {
		//	s += "�A�h���X" + to_string(mobsSpeedOrder[i]->speed);//�f�������A�h���X�z��̃X�s�[�h��\���B
		//}
		//DrawString(800, 570, s.c_str(), WHITE);
		//WaitKey();








		for (int i = 0; i < mobNumberNow ; i++) {

			//if (mobsspeedorder[i] == null) {
			//	continue;
			//}
			if (mobsSpeedOrder[i] == NULL) {//�X�s�[�h���z��ɂ��������Ȃ���ΏI���B
				return;
			}

			//if (mobsSpeedOrder[i]->pass == TRUE) {//�L�����͋��邯�Ǎs�����Ȃ���Ԃł���΃R���e�B�j���[�B
			//	continue;
			//}
			
			if (mobsSpeedOrder[i]->status == NORMAL or mobsSpeedOrder[i]->status == ELDER) {
				reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction();
			}
			
			//mobsSpeedOrder[i]->specialMovement2(FIELDSIZE);
			//mobsSpeedOrder[i]->attack();

			exhibitScreen();

			numSpeed = (to_string(mobsSpeedOrder[i]->speed));
			numX = (to_string(mobsSpeedOrder[i]->x));
			numY = (to_string(mobsSpeedOrder[i]->y));
			mobStatusMsg = "X:" + numX + ",Y:" + numY + "�̃y���M���̏r�q���́A" + numSpeed;
			DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
			WaitKey();
		}

	}















	/*bool speedOrder(Creature* a, Creature* b) {

		if (a->speed == b->speed) {
			return a->speed < b->speed;
		}
		else {
			return a->speed > b->speed;
		}
		
	}*/



