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



bool turnFinal();//�^�[���̍Ō�ɂ܂Ƃ߂čs���鑀��B

void enemyEnter(int turn, int level);//�G���P�����铮��B
void yieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy);
bool ending();

bool speedOrder(Creature* a, Creature* b);






BattleMode_GameManager::BattleMode_GameManager() {//�R���X�g���N�^�B
	turnNum = 0;
	

	for (int i = 0; i < FIELDSIZE; i++) {
		board[i][0].state = ROCK;
		board[i][FIELDSIZE -1].state = ROCK;
		board[0][i].state = ROCK;
		board[FIELDSIZE - 1][i].state = ROCK;

		board[CASTLE_X][CASTLE_Y].state = CASTLE;
	}
}



bool BattleMode_GameManager::BattleMode(int level) {

	//string turnF = "";

	Emperor Emperor1(red, 0);//�C���X�^���X��
	handledCharacters[0] = &Emperor1;
	Emperor Emperor2(blue, 1);//�C���X�^���X��
	handledCharacters[1] = &Emperor2;

	gameMode = 1;

	while (gameMode == 1) {

		

		if (Emperor1.HP > 0) {
			if (Emperor1.selectAction() == FALSE) {
				return FALSE;
			}
		}
		if (Emperor2.HP > 0) {
			if (Emperor2.selectAction() == FALSE) {
				return FALSE;
			}
		}

		if (Emperor1.HP <= 0 && Emperor2.HP <= 0 ) {
			mainMsg = "�Q�[���I�[�o�[";
			actionMsg = "�Q�[�����I�����܂��B";
			exhibitScreen(0, 0, FALSE);
			WaitKey();
			return FALSE;
		}

		if ((level == 0 && turnNum == 60)||(level == 1 && turnNum == 100)) {
			mainMsg = std::to_string(turnNum) + "�^�[���������т��I �Q�[���N���A�I \n���߂łƂ��I";
			actionMsg = "��킳�ꂽ�q�y���M���̐�:"+ std::to_string(num_penguinKids) + "\n�����X�^�[�̑���:" + std::to_string(num_bull);
			exhibitScreen(0, 0, FALSE);
			WaitKey();
			if (ending() == FALSE) {
				return FALSE;
			}
			
			exhibitScreen(0, 0, FALSE);
			WaitKey();
		}


		mainMsg = "";
		if (turnFinal() == FALSE) {
			return FALSE;
		}

		if (Emperor1.HP <= 0 && Emperor2.HP <= 0 || board[CASTLE_X][CASTLE_Y].state == VACANT) {
			mainMsg = "�Q�[���I�[�o�[";
			actionMsg = "�Q�[�����I�����܂��B";
			exhibitScreen(0, 0, FALSE);
			WaitKey();
			return FALSE;
		}
		

		enemyEnter(turnNum, level);
		turnNum += 1;
		exhibitScreen(0, 0, FALSE);
		/*turnF = "���݂̃^�[��:" + std::to_string(turnNum);
		DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turnF.c_str(), GetColor(255, 200, 255));
		WaitKey();*/


	}
}















bool turnFinal() {//�f��������mob���s�����Ă����֐��B
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





	//sort(mobsSpeedOrder, mobsSpeedOrder + mobNumber, speedOrder);

	//s = "";
	//for (int i = 0; i < mobNumber; i++) {
	//	if (mobsSpeedOrder[i]->speed > 0) {
	//		s = "X" + std::to_string(mobsSpeedOrder[i]->x) + "Y" + std::to_string(mobsSpeedOrder[i]->y) + "�̑f����:" + to_string(mobsSpeedOrder[i]->speed) + " \n";//�f�������A�h���X�z��̃X�s�[�h��\���B
	//		allS += s;
	//	}
	//}
	//exhibitScreen(0, 0, FALSE);
	//DrawString(FIELDSIZE * SQUARESIZE, 570, allS.c_str(), WHITE);
	//WaitKey();








	for (int i = 0; i < mobNumberNow; i++) {








		//if (mobsspeedorder[i] == null) {
		//	continue;
		//}
		if (mobsSpeedOrder[i] == NULL) {//�X�s�[�h���z��ɂ��������Ȃ���ΏI���B
			return TRUE;
		}
		if (mobsSpeedOrder[i]->speed < 0) {//�X�s�[�h���}�C�i�X�A�܂莀��ł�����I���B
			return TRUE;
		}


		//if (mobsSpeedOrder[i]->pass == TRUE) {//�L�����͋��邯�Ǎs�����Ȃ���Ԃł���΃R���e�B�j���[�B
		//	continue;
		//}

		if (mobsSpeedOrder[i]->status == NORMAL || mobsSpeedOrder[i]->status == ELDER) {//����or�V�l�y���M���Ȃ�y���M����selectAction���ĂԁB
			moveOrNot = reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction();
		}
		if (mobsSpeedOrder[i]->status == BULL) {//����or�V�l�y���M���Ȃ�y���M����selectAction���ĂԁB
			moveOrNot = reinterpret_cast<Bull*>(mobsSpeedOrder[i])->selectAction();
		}


		//if (moveOrNot == TRUE) {//�����s�����s���Ă�����
		//	exhibitScreen(mobsSpeedOrder[i]->x, mobsSpeedOrder[i]->y,TRUE);
		//	numSpeed = (to_string(mobsSpeedOrder[i]->speed));
		//	numX = (to_string(mobsSpeedOrder[i]->x));
		//	numY = (to_string(mobsSpeedOrder[i]->y));
		//	mobStatusMsg = "X:" + numX + ",Y:" + numY + "��" + mobsSpeedOrder[i]->name + "\n �s�����x:" + numSpeed + " �̗�:" + to_string(mobsSpeedOrder[i]->HP) + "/" + to_string(mobsSpeedOrder[i]->HP_Limit);
		//	DrawString(FIELDSIZE * SQUARESIZE, 160, mobStatusMsg.c_str(), WHITE);
		//	WaitKey();
		//}
		if (quitGame == TRUE) {
			return FALSE;
		}

	}
	return TRUE;

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












void enemyEnter(int turn, int level) {//�ǂ̃^�[���œG���o�����邩�����߂�B
	int side = 0;
	int place = 0;

	if (turn == 0) {//�P�^�[���ڂ���A�G���o�����Ȃ��������肷��B
		randomSide = GetRand(3);
	}
	if (turn == 14) {//�G���o�����Ȃ��������肷��B
		randomSide = GetRand(3);
	}
	if (turn == 40) {//�G���o�����Ȃ��������肷��B
		randomSide = GetRand(3);
	}


	if ((1 < turn && turn < 25) || (36 < turn && turn < 50)) {
		if ((turn % 3 == 2 || turn % 3 == 0) || turn == 8) {

			side = GetRand(2);
			if (side >= randomSide) {//�����_���łƂ��Ă���side�̒l���A�G�o���Ȃ����A�܂�-1�ƒ�߂��Ă���A�����ԍ���1���₷�B
				side += 1;
			}

			place = GetRand(FIELDSIZE - 3);

			if (side == 0) {
				yieldEnemy(BULL, red, 0, 1, place + 1, 0);
			}
			if (side == 1) {
				yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1);
			}
			if (side == 2) {
				yieldEnemy(BULL, red, 1, 0, 0, place + 1);
			}
			if (side == 3) {
				yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1);
			}
		}
	}

	if ((turn % 2 == 0 && turn > 16 && turn < 29) || (turn % 3 == 2 && turn > 34)) {
		
		side = GetRand(3);
		place = GetRand(FIELDSIZE - 3);
		if (side == 0) {
			yieldEnemy(BULL, blue, 0, 1, place + 1, 0);
		}
		if (side == 1) {
			yieldEnemy(BULL, blue, 0, -1, place + 1, FIELDSIZE - 1);
		}
		if (side == 2) {
			yieldEnemy(BULL, blue, 1, 0, 0, place + 1);
		}
		if (side == 3) {
			yieldEnemy(BULL, blue, -1, 0, FIELDSIZE - 1, place + 1);
		}
	}




	if (turn % 5 == 3 && level == 1) {

		side = GetRand(3);
		place = GetRand(FIELDSIZE - 3);
		if (side == 0) {
			yieldEnemy(BULL, blue, 0, 1, place + 1, 0);
		}
		if (side == 1) {
			yieldEnemy(BULL, blue, 0, -1, place + 1, FIELDSIZE - 1);
		}
		if (side == 2) {
			yieldEnemy(BULL, blue, 1, 0, 0, place + 1);
		}
		if (side == 3) {
			yieldEnemy(BULL, blue, -1, 0, FIELDSIZE - 1, place + 1);
		}
	}









	if (turn == 28) {//�G���o�����鑤�����肷��B1�̕�������W���U�������邼�I
		randomSide = GetRand(3);
	}
	if ((28 < turn && turn < 34) || turn == 9) {

		place = GetRand(FIELDSIZE - 3);
		if (randomSide == 0) {
			yieldEnemy(BULL, red, 0, 1, place + 1, 0);
		}
		if (randomSide == 1) {
			yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1);
		}
		if (randomSide == 2) {
			yieldEnemy(BULL, red, 1, 0, 0, place + 1);
		}
		if (randomSide == 3) {
			yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1);
		}
	}




	if ((turn % 5 == 0 && turn > 12) || turn == 16) {//���ʂɐԂ�����B�����̊m���Ŕ��Α����������B
		side = GetRand(3);
		place = GetRand(FIELDSIZE - 3);
		if (side == 0) {
			yieldEnemy(BULL, red, 0, 1, place + 1, 0);
			place = GetRand(FIELDSIZE - 3);
			yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1);
		}
		if (side == 1) {
			yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1);
		}
		if (side == 2) {
			yieldEnemy(BULL, red, 1, 0, 0, place + 1);
			place = GetRand(FIELDSIZE - 3);
			yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1);
		}
		if (side == 3) {
			yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1);
		}

	}



}







void yieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy) {

	if (enemyType == BULL) {
		Bull bull = Bull();
		bull.setMobs(enemyTeam, dx, dy, cx, cy, 400000);
		mobs_Bull[num_bull] = bull;
		board[cx][cy].creature = &mobs_Bull[num_bull];
		mobNumber += 1;
		num_bull += 1;

	}



}












bool ending() {
	

	int height = FIELDSIZE * SQUARESIZE + 40;
	const int msgNum = 8;
	int msgCenter = (FIELDSIZE * 48 + 384) / 2;
	string endingMsg[8];
	endingMsg[0] = "PENGUIN ROBOT BATTLE!";
	endingMsg[1] = "2022";
	endingMsg[2] = "";
	endingMsg[3] = "���:iwashi";
	endingMsg[4] = "�f�B���N�^�[:iwashi";
	endingMsg[5] = "���C���v���O����:iwashi";
	endingMsg[6] = "�f�U�C�i�[:�͂؂�";
	endingMsg[7] = "�X�y�V�����T���N�X:dolpast";
	
	int DrawWidth[msgNum];
	int StrLen[msgNum];

	string quitMsg = "";

	ClearDrawScreen();

	for (int i = 0; i < msgNum; i++) {
		StrLen[i] = strlen(endingMsg[i].c_str());//�������擾
		DrawWidth[i] = GetDrawStringWidth(endingMsg[i].c_str(), StrLen[i]);//�������擾
	}

	while (1) {
		ClearDrawScreen();
		for (int i = 0; i < msgNum; i++) {
			DrawString(msgCenter - DrawWidth[i] / 2, height + i*100, endingMsg[i].c_str(), GetColor(210, 255, 250));

			if(DrawWidth[i] != 0){
			DrawGraph(msgCenter - DrawWidth[i] / 2 - 78, height + i * 100-15, handle[blue][EGG][NW],TRUE);
			DrawGraph(msgCenter + DrawWidth[i] / 2 + 30, height + i * 100-15, handle[red][EGG][NW], TRUE);
			}
		}
		height--;
		WaitTimer(20);

		

		if (height < -720) {
			break;
		}
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������I��
			return FALSE;
		}
		if (CheckHitKey(KEY_INPUT_SPACE) == TRUE || CheckHitKey(KEY_INPUT_1) == TRUE) {
			height = height-4;
		}
		

		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}




	quitMsg = "�Q�[�����I�����܂����H 1:Yes 2:No";
	DrawString(FIELDSIZE * SQUARESIZE + 5, 20, quitMsg.c_str(), WHITE);
	WaitKey();
	while (1) {
		if (CheckHitKey(KEY_INPUT_1) == TRUE) {//�Ȃ��㉺���E���t�Ȃ́H��B
			quitMsg = "�{���ɃQ�[�����I�����Ă�낵���ł����H \n1:Yes 2:No";
			ClearDrawScreen();
			DrawString(FIELDSIZE * SQUARESIZE + 5, 20, quitMsg.c_str(), WHITE);
			WaitKey();
			while (1) {
				if (CheckHitKey(KEY_INPUT_1) == TRUE) {//�Ȃ��㉺���E���t�Ȃ́H��B
					return FALSE;
				}
				if (CheckHitKey(KEY_INPUT_2) == TRUE) {//�Ȃ��㉺���E���t�Ȃ́H��B
					break;
				}
				WaitTimer(10);
			}	
		}
		if (CheckHitKey(KEY_INPUT_2) == TRUE) {//�Ȃ��㉺���E���t�Ȃ́H��B
			break;
		}
		WaitTimer(10);
	}
	return TRUE;
}