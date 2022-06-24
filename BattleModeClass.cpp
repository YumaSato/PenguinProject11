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



//bool turnFinal(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);//�^�[���̍Ō�ɂ܂Ƃ߂čs���鑀��B

//void enemyEnter(int turn, int level, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);//�G���P�����铮��B
//void YieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
bool ending();




bool speedOrder(Creature* a, Creature* b);






BattleMode_GameManager::BattleMode_GameManager(int stageLevel, int xSize, int ySize) {//�R���X�g���N�^�B
	turnNum = 0;

	board = new Grid * [xSize];

	for (int xi = 0; xi < xSize; xi++) {
		Grid* yGrid = new Grid[ySize];
		board[xi] = yGrid;//Grid�����̏�����
	}
	this->sizeX = xSize;
	this->sizeY = ySize;
	GameBuf = this;

	//board = new Grid * [xSize];

	//for (int yi = 0; yi < ySize; yi++) {
	//	Grid* yGrid = new Grid[ySize];
	//	board[yi] = yGrid;//Grid�����̏�����
	//}
	//this->sizeX = xSize;
	//this->sizeY = ySize;
	//GameBuf = this;





	/*for (int i = 0; i < CHARACTERNUM; i++) {
		handledCharacters[i] = NULL;
	}*/
	
	






	exhibitX = (handledCharacters[0].x - (FIELDSIZE - (FIELDSIZE /2))) * 48;//�L����0����\���}�X�T�C�Y�̔����̋����������ォ��\���B�܂�L����0�𒆐S�ɉ�ʂ�`��B
	exhibitY = (handledCharacters[0].y - (FIELDSIZE - (FIELDSIZE /2))) * 48;
	if (exhibitX < 0) {
		exhibitX = 0;
	}
	if (exhibitX/48 + FIELDSIZE > sizeX) {
		exhibitX = (sizeX - FIELDSIZE)*48;
	}
	if (exhibitY < 0) {
		exhibitY = 0;
	}
	if (exhibitY/48 + FIELDSIZE > sizeY) {
		exhibitY = (sizeY - FIELDSIZE)*48;//�`��}�X�̍��������exhibitXY���Ֆʏ�ɂ�����}�C�i�X��A�`��}�X�̉E�����ՖʃT�C�Y���͂ݏo��ꍇ�A�͂ݏo�Ȃ��ꏊ�ɍĐݒ�B
	}
}










BattleMode_GameManager::~BattleMode_GameManager() {
	//delete[][] board;


	for (int xi = 0; xi < sizeX; xi++) {//�}�X�ڂ�����
		delete[] board[xi];
	}
	delete[] board;
	delete Emperor1;
	delete Emperor2;

	GameBuf = NULL;
};




int BattleMode_GameManager::BattleMode(int stageLevel) {

	//string turnF = "";



	castleX = sizeX / 2;
	castleY = sizeY / 2;

	for (int ix = 0; ix < sizeX; ix++) {
		for (int iy = 0; iy < sizeY; iy++) {
			board[ix][0].state = ROCK;
			board[ix][sizeY - 1].state = ROCK;
			board[0][iy].state = ROCK;
			board[sizeX - 1][iy].state = ROCK;
			board[castleX][castleY].state = CASTLE;
		}
	}
	Emperor1 = new Emperor();//�C���X�^���X��
	Emperor1->setMobs(red, 1, 0, 1, 0, 0, 0, board, handledCharacters);
	handledCharacters[0] = *Emperor1;
	board[Emperor1->x][Emperor1->y].creature = &handledCharacters[0];//�}�X�ڂɎ����̃|�C���^�����B


	Emperor2 = new Emperor();//�C���X�^���X��
	Emperor2->setMobs(blue, 2, 0, 0, 1, 0, 0, board, handledCharacters);
	handledCharacters[1] = *Emperor2;
	board[Emperor2->x][Emperor2->y].creature = &handledCharacters[1];







	int actionReturn = 1;//�����Ԃ��Ă��邩�B0�Ȃ�΃Q�[���I���B1�͐���ɍs���������������Ƃ����Ӗ��B2�̓^�C�g���ɖ߂�B
	gameMode = 1;
	while (gameMode == 1) {

		for (int i = 0; i < CHARACTERNUM; i++) {
			if (handledCharacters[i].HP > 0) {
				actionReturn = handledCharacters[i].selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);
				actionMsg = "";
				if (actionReturn == 0) {
					return 0;
				}
				if (actionReturn == 2) {
					return 2;
				}
			}
		}





		if ((handledCharacters[0].HP <= 0 && handledCharacters[1].HP <= 0) || board[castleX][castleY].state == VACANT) {
			if (GameOver() == 0) {//�Q�[���I�[�o�[
				return 0;
			}
		}

		if ((stageLevel == 0 && turnNum == 60) || (stageLevel == 1 && turnNum == 100)) {//�Q�[���N���A
			if (GameClear() == 0) {
				return 0;
			}
		}


		mainMsg = "";
		if (TurnFinal() == FALSE) {
			return FALSE;
		}

		if ((handledCharacters[0].HP <= 0 && handledCharacters[1].HP <= 0) || board[castleX][castleY].state == VACANT) {
			mainMsg = "�Q�[���I�[�o�[";
			actionMsg = "Esc�������ƁA�Q�[�����I�����܂��B";
			exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
			WaitKey();
			while (1) {
				if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
					return FALSE;
				}

				if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
					return FALSE;
				}
				WaitTimer(10);
			}
			return FALSE;
		}


		if (EnemyEnter(turnNum, stageLevel, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) {
			return 0;
		}
		turnNum += 1;
		exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
		

	}
}






int  BattleMode_GameManager::GameClear() {
	mainMsg = std::to_string(turnNum) + "�^�[���������т��I �Q�[���N���A�I \n���߂łƂ��I";
	actionMsg = "��킳�ꂽ�q�y���M���̐�:" + std::to_string(num_penguinKids) + "\n�����X�^�[�̑���:" + std::to_string(num_bull);
	exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
	WaitKey();
	if (ending() == FALSE) {
		return FALSE;
	}

	exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
	WaitKey();

}

int  BattleMode_GameManager::GameOver() {

	mainMsg = "�Q�[���I�[�o�[";
	actionMsg = "Esc�������ƁA�Q�[�����I�����܂��B";
	exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
	WaitKey();
	while (1) {
		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
			return FALSE;
		}

		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			return FALSE;
		}
		WaitTimer(10);
	}
	return FALSE;
}













int  BattleMode_GameManager::TurnFinal() {//�f��������mob���s�����Ă����֐��B
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

	for (int i = 0; i < mobNumberNow; i++) {

		

		//if (mobsSpeedOrder[i] == NULL) {//�X�s�[�h���z��ɂ��������Ȃ���ΏI���B
		//	return TRUE;
		//}
		//if (mobsSpeedOrder[i]->speed < 0) {//�X�s�[�h���}�C�i�X�A�܂莀��ł�����I���B
		//	return TRUE;
		//}
		if (mobsSpeedOrder[i] != NULL && mobsSpeedOrder[i]->speed >= 0) {//���u������Ƃ�
			actionMsg = "";
			if (mobsSpeedOrder[i]->status == NORMAL || mobsSpeedOrder[i]->status == ELDER) {//����or�V�l�y���M���Ȃ�y���M����selectAction���ĂԁB
				moveOrNot = reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);

			}
			if (mobsSpeedOrder[i]->status == BULL) {//���Ȃ狍��selectAction���ĂԁB
				moveOrNot = reinterpret_cast<Bull*>(mobsSpeedOrder[i])->selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}

			if (moveOrNot == TRUE) {
				/*exhibitScreen(mobsSpeedOrder[i]->x, mobsSpeedOrder[i]->y, TRUE, board, handledCharacters);
				ScreenMove(mobsSpeedOrder[i]->x, mobsSpeedOrder[i]->y);*/

				/*if (quitGame == TRUE) {
					return FALSE;
				}*/

				if (GoNext(mobsSpeedOrder[i]->x, mobsSpeedOrder[i]->y) ==FALSE) {
					return FALSE;
				}
			}
		}
		//WaitKey();

		

	}
	return TRUE;

}



int BattleMode_GameManager::GoNext(int markX, int markY) {
	{
		int mouse = NULL;
		int xClick = NULL;
		int yClick = NULL;
		int nextFlag = -1;
		while (1) {
			if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
				return 0;
			}
			exhibitScreen(markX, markY, TRUE, FALSE, board, handledCharacters);
			mouse = NULL;
			xClick = NULL;
			yClick = NULL;
			if (CheckHitKey(KEY_INPUT_1) == FALSE && CheckHitKey(KEY_INPUT_2) == FALSE && CheckHitKey(KEY_INPUT_3) == FALSE && CheckHitKey(KEY_INPUT_4) == FALSE && CheckHitKey(KEY_INPUT_5) == FALSE && CheckHitKey(KEY_INPUT_6) == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE && CheckHitKey(KEY_INPUT_RETURN) == FALSE && CheckHitKey(KEY_INPUT_SPACE) == FALSE) {
				pushingKey = 0;
			}

			ScreenMove(markX,markY);
			DrawBox(FIELDSIZE * SQUARESIZE + 120, 700, FIELDSIZE * SQUARESIZE + 320, 785, GetColor(255, 183, 0), TRUE);
			DrawString(FIELDSIZE * SQUARESIZE + 170, 720, "���֐i��\n(SPACE)",GetColor(20,0,40));

			//nextFlag = GetClickPlace(&xClick, &yClick);
			//actionMsg = "afew=" + std::to_string(nextFlag);
			//exhibitScreen(markX, markY, TRUE, board, handledCharacters);//�Ȃ�ŁH�H�H�H
			//WaitKey();

			if (GetClickPlace(&xClick, &yClick) == 1) {
				if (xClick > FIELDSIZE * SQUARESIZE + 100 && xClick < FIELDSIZE * SQUARESIZE + 250 && yClick > 700 && yClick < 770) {
					return 1;
				}
				
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == TRUE && pushingKey == FALSE) {//���݂̉�����Ԃ�FALSE�ŁA����Enter�������ꂽ�ꍇ
				pushingKey = 1;
				return 1;
			}

			ScreenFlip();
		}
	}

}



int  BattleMode_GameManager::ScreenMove(int markX, int markY) {
	if (CheckHitKey(KEY_INPUT_W) == TRUE) {//WASD�Ŏ��_�ړ�
		if (GameBuf->exhibitY > 0) {
			GameBuf->exhibitY -= 4;
			if (GameBuf->exhibitY < 0) {
				GameBuf->exhibitY = 0;
			}
			exhibitScreen(markX,markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);

		}
	}
	if (CheckHitKey(KEY_INPUT_S) == TRUE) {
		if (GameBuf->exhibitY < (GameBuf->sizeY - FIELDSIZE) * SQUARESIZE) {
			GameBuf->exhibitY += 4;
			if (GameBuf->exhibitY / 48 + FIELDSIZE >= GameBuf->sizeY) {//�`�撆�S������Ă���}�X�{�`��}�X���{�P(�`�扺�[�}�X)���A�񎟌��z��T�C�Y�𒴂��Ă�����
				GameBuf->exhibitY = (GameBuf->sizeY - FIELDSIZE) * 48;//�`��}�X�̍��������exhibitXY���Ֆʏ�ɂ�����}�C�i�X��A�`��}�X�̉E�����ՖʃT�C�Y���͂ݏo��ꍇ�A�͂ݏo�Ȃ��ꏊ�ɍĐݒ�B
			}

			exhibitScreen(markX,markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);
		}
	}
	if (CheckHitKey(KEY_INPUT_A) == TRUE) {//WASD�Ŏ��_�ړ�
		if (GameBuf->exhibitX > 0) {
			GameBuf->exhibitX -= 4;
			if (GameBuf->exhibitX < 0) {
				GameBuf->exhibitX = 0;
			}
			exhibitScreen(markX,markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);

		}
	}
	if (CheckHitKey(KEY_INPUT_D) == TRUE) {
		if (GameBuf->exhibitX < (GameBuf->sizeX - FIELDSIZE) * SQUARESIZE) {
			GameBuf->exhibitX += 4;
			if (GameBuf->exhibitX / 48 + FIELDSIZE >= GameBuf->sizeX) {
				GameBuf->exhibitX = (GameBuf->sizeX - FIELDSIZE) * 48;
			}
			exhibitScreen(markX, markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);
		}
	}
	return 0;
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












int BattleMode_GameManager::EnemyEnter(int turn, int level, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {//�ǂ̃^�[���œG���o�����邩�����߂�B
	int side = 0;
	int place = 0;
	int yieldReturnFlag = 0;

	if (turn == 0) {//�P�^�[���ڂ���A�G���o�����Ȃ��������肷��B
		randomSide = GetRand(3);
	}
	if (turn == 14) {//�G���o�����Ȃ��������肷��B
		randomSide = GetRand(3);
	}
	if (turn == 40) {//�G���o�����Ȃ��������肷��B
		randomSide = GetRand(3);
	}



	//if (GameBuf->sizeX == GameBuf->sizeY) {
	if ((1 < turn && turn < 25) || (36 < turn && turn < 50)) {
		if ((turn % 3 == 2 || turn % 3 == 0) || turn == 8) {

			side = GetRand(2);
			if (side >= randomSide) {//�����_���łƂ��Ă���side�̒l���A�G�o���Ȃ����A�܂�-1�ƒ�߂��Ă���A�����ԍ���1���₷�B
				side += 1;
			}

			place = GetRand(GameBuf->sizeX - 3);

			if (side == 0) {
				if (YieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
			if (side == 1) {
				if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
			if (side == 2) {
				if (YieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
			if (side == 3) {
				if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
		}
	}

	if ((turn % 2 == 0 && turn > 16 && turn < 25) || (turn % 3 == 2 && turn > 30)) {

		side = GetRand(3);
		place = GetRand(GameBuf->sizeX - 3);
		if (side == 0) {
			if (YieldEnemy(BULL, blue, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 1) {
			if (YieldEnemy(BULL, blue, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 2) {
			if (YieldEnemy(BULL, blue, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 3) {
			if (YieldEnemy(BULL, blue, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
	}




	if (turn % 8 == 6 && level == 1) {

		side = GetRand(3);
		place = GetRand(GameBuf->sizeX - 3);
		if (side == 0) {
			if (YieldEnemy(BULL, blue, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 1) {
			if (YieldEnemy(BULL, blue, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 2) {
			if (YieldEnemy(BULL, blue, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 3) {
			if (YieldEnemy(BULL, blue, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
	}




	if (turn == 28) {//�G���o�����鑤�����肷��B1�̕�������W���U�������邼�I
		randomSide = GetRand(3);
	}
	if ((28 < turn && turn < 34) || turn == 9) {

		place = GetRand(GameBuf->sizeX - 3);
		if (randomSide == 0) {
			if (YieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (randomSide == 1) {
			if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (randomSide == 2) {
			if (YieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (randomSide == 3) {
			if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
	}




	if ((turn % 5 == 0 && turn > 12) || turn == 16) {//���ʂɐԂ�����B�����̊m���Ŕ��Α����������B
		side = GetRand(3);
		place = GetRand(GameBuf->sizeX - 3);
		if (side == 0) {
			if (YieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			place = GetRand(GameBuf->sizeX - 3);
			if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 1) {
			if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 2) {
			if (YieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			place = GetRand(GameBuf->sizeX - 3);
				if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 3) {
			if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}

	}
	//}
	return 1;
	
}







int BattleMode_GameManager::YieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {

	if (enemyType == BULL) {


		if (board[cx][cy].creature != NULL) {
			int rand = GetRand(1);
			if (cx == 0 || cx == GameBuf->sizeX - 1) {
				if (rand == 0) {
					cy += 1;
				}
				if (rand == 1) {
					cy -= 1;
				}
			}
			if (cy == 0 || cy == GameBuf->sizeY - 1) {
				if (rand == 0) {
					cx += 1;
				}
				if (rand == 1) {
					cx -= 1;
				}
			}
		}
		if (board[cx][cy].creature == NULL) {

			Bull bull = Bull();
			bull.setMobs(enemyTeam, dx, dy, cx, cy, turnNum / 10 + 1, 400000, board, handledCharacters);
			mobs_Bull[num_bull] = bull;
			board[cx][cy].creature = &mobs_Bull[num_bull];
			mobNumber += 1;
			num_bull += 1;
			return GoNext(cx,cy);
		}


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
			DrawString(msgCenter - DrawWidth[i] / 2, height + i * 100, endingMsg[i].c_str(), GetColor(210, 255, 250));

			if (DrawWidth[i] != 0) {
				DrawGraph(msgCenter - DrawWidth[i] / 2 - 78, height + i * 100 - 15, handle[blue][EGG][NW], TRUE);
				DrawGraph(msgCenter + DrawWidth[i] / 2 + 30, height + i * 100 - 15, handle[red][EGG][NW], TRUE);
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
			height = height - 4;
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