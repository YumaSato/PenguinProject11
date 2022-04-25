#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>

using namespace std;

PenguinKids::PenguinKids() {
}








void PenguinKids::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {//�����I�ȃR���X�g���N�^�B
	//����������PenguinKids�z�����邽�߂ɂ̓R���X�g���N�^�ɉ��������Ă���ƃ_���炵���̂ŁA�R���X�g���N�^�ł��ׂ����Ƃ�ʂ̊֐��ɂ����B

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	name = "�y���M��";
	team = ParentTeam;
	status = EGG;//���ł���ӁB
	//directionX = DirectionX;
	//directionY = DirectionY;
	SETdirection(DirectionX, DirectionY);
	x = ix;
	y = iy;
	HP = 50;
	HP_Limit = 50;
	stamina = NULL;
	staminaLimit = NULL;
	attackPower = 30 + GetRand(3);
	defensePower = 1;

	int random = GetRand(100) + 30;
	speed = ((parentSpeed -1)*(random - GetRand(20)) / random)-1;//�f�����͐�����d�˂邲�Ƃɒቺ����B�����ʂ̓����_���B
	//
	if (speed < 1) { speed = 1; }
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = TRUE;//�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j
	score += 5;


	/*exhibitScreen();
	DrawString(800, 180, "�y���M���L�b�Y��SetMobs���s�B", GetColor(255, 200, 255));*/
	/*numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "�̃y���M���̑f�����́A" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();*/


}





bool PenguinKids::selectAction() {

	if (skip == TRUE) {//skip�����ԂȂ�A���I���B
		skip = FALSE;//skip��Ԃ������B
		return FALSE;//�s�����Ȃ���������ɂ���B���ꂪTRUE���ƁA�����̍s���ɂ��Đ������\������Ă��܂��B
	}

	if (status == EGG) {//skip�����ԂȂ�A���I���B
		return FALSE;
	}

	HP += 12;
	if (HP > HP_Limit) {//���R����
		HP = HP_Limit;
	}


	int iX = x;
	int iY = y;
	int tmpx, tmpy;
	GETdirectionXY(&tmpx, &tmpy);
	//ix = ix + directionX;
	//iy = iy + directionY;
	iX = iX + tmpx;
	iY = iY + tmpy;
	if (status == ELDER || status == NORMAL) {
		if (iX >= 0 && iX < FIELDSIZE && iY >= 0 && iY < FIELDSIZE) {
			if (board[iX][iY].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
				if (board[iX][iY].creature->status == EGG && board[iX][iY].creature->team == team) {//�����`�[���̗��������
					if (specialMovement1(FIELDSIZE) == TRUE) {//�D��s���Ƃ��ĎY���B
						return TRUE;
					}
				}
			}
		}
	}




	if (attack(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			quitGame = TRUE;
		}
		return TRUE;
	}
	if (specialMovement1(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			quitGame = TRUE;
		}
		return TRUE;
	}
	if (specialMovement2(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			quitGame = TRUE;
		}
		return TRUE;
	}
	return FALSE;
}





void PenguinKids::test() {
	string s;
	s = "";
	s = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "��test���\�b�h���s";
	exhibitScreen(x, y, TRUE);
	DrawString(800, 300, s.c_str(), WHITE);
	WaitKey();
}



bool PenguinKids::attack(int size) {

	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;
	int tmpx;
	int tmpy;
	bool attackPriority = FALSE;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {//�U���D�惂�[�h�ɓ��Ă͂܂邩�𒲂ׂ�B
		if (board[checkX][checkY].creature != NULL) {//�ڂ̑O�ɐ�����������
			if (board[checkX][checkY].creature->enemy == TRUE) {//�����ɂ������G�Ȃ�΍U���B
				damage(checkX, checkY);
				return TRUE;
			}
			if (status == NORMAL && (board[checkX][checkY].creature->status != EGG || board[checkX][checkY].creature->team != team)) {//�ڂ̑O�ɕʃ`�[���������͗��ȊO�����āA�������Y�݂�����Ԃ̂Ƃ�
				attackPriority = TRUE;//���G�J�n�B
			}
		}
	}
	if (board[checkX][checkY].state == ROCK) {//�U���D�惂�[�h�ɓ��Ă͂܂邩�𒲂ׂ�B���Ă͂܂����ꍇ�A�����Ă�������ȊO�����G����B
		attackPriority = TRUE;//���������Ă���ꍇ�B
	}
	if (status == ELDER || attackPriority == TRUE) {//�o�Y�Ƃ����d�����I����Ă���ꍇ���A�m�[�}����Ԃł��ڂ̑O�ɉ������ė����Y�߂Ȃ��Ƃ�

		int diCheck[8] = { 0,1,2,3,4,5,6,7 };//���ʂɓG������΂��ꂪ�D��I�ɛz������邪�A�ׂɂ�������������ꍇ�A����z������������������_���ɂ���B
		for (int i = 0; i < 7; i++) {
			int r = GetRand(7 - i) + i;
			int tmp = diCheck[i];
			diCheck[i] = diCheck[r];
			diCheck[r] = tmp;
		}

		for (int i = 0; i < 8; i++) {//�W�������ׂ�B����Ȃ��switch�g����i==7�̏ꍇ�����������Ȃ��́H���u���C�N�������Ă��Ȃ���������B

			switch (diCheck[i]) {
			case 0:
				tmpx = -1;
				tmpy = -1;
				break;
			case 1:
				tmpx = 0;
				tmpy = -1;
				break;
			case 2:
				tmpx = 1;
				tmpy = -1;
				break;
			case 3:
				tmpx = 1;
				tmpy = 0;
				break;
			case 4:
				tmpx = 1;
				tmpy = 1;
				break;
			case 5:
				tmpx = 0;
				tmpy = 1;
				break;
			case 6:
				tmpx = -1;
				tmpy = 1;
				break;
			case 7:
				tmpx = -1;
				tmpy = 0;
				break;
			}
			checkX = x + tmpx;
			checkY = y + tmpy;

			if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {

				if (board[checkX][checkY].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
					if (board[checkX][checkY].creature->enemy == TRUE) {//���ꂪ�G���Ɣ��肳�ꂽ��

						SETdirection(tmpx, tmpy);//�G�̕���������
						damage(checkX, checkY);//�U���B
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}




bool PenguinKids::specialMovement1(int size) {//�Y��
	if (status == NORMAL) {
		//exhibitScreen();
		//DrawString(800, 300, "PenguinKids.specialMovement1���\�b�h���s", WHITE);
		//WaitKey();
		int ix = x;
		int iy = y;
		int tmpx, tmpy;
		GETdirectionXY(&tmpx, &tmpy);
		//ix = ix + directionX;
		//iy = iy + directionY;
		ix = ix + tmpx;
		iy = iy + tmpy;

		if (ix >= 0 && ix < size && iy >= 0 && iy < size && board[ix][iy].creature == NULL && board[ix][iy].state == VACANT) {//�����Ă�������̃}�X���󂢂Ă�����



			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, tmpx, tmpy, ix, iy, speed);


			mobs_PenguinKids[num_penguinKids] = penguinKids;
			board[ix][iy].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;
			status = ELDER;//�V������



			actionMsg = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "���Y�������I";

			//board[ix][iy].creature = &penguinKids;

			return TRUE;//�����B
		}
	}
	return FALSE;
}




bool PenguinKids::specialMovement2(int size) {

	string s = "";
	string allS = "";
	int ix = x;
	int iy = y;
	int tmpx, tmpy;
	GETdirectionXY(&tmpx, &tmpy);
	//ix = ix + directionX;
	//iy = iy + directionY;
	ix = ix + tmpx;
	iy = iy + tmpy;


	if (status == NORMAL or status == ELDER) {
		if (ix >= 0 && ix < size && iy >= 0 && iy < size) {

			if (board[ix][iy].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
				if (board[ix][iy].creature->status == EGG && board[ix][iy].creature->team == team) {

					incubate(ix, iy);
					actionMsg = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "���z���������I";
					return TRUE;
				}
			}
		}


		int diCheck[8] = { 0,1,2,3,4,5,6,7 };//���ʂɗ�������΂��ꂪ�D��I�ɛz������邪�A�ׂɂ�������������ꍇ�A����z������������������_���ɂ���B
		for (int i = 0; i < 7; i++) {
			int r = GetRand(7 - i) + i;
			int tmp = diCheck[i];
			diCheck[i] = diCheck[r];
			diCheck[r] = tmp;
		}


		for (int i = 0; i < 8; i++) {//�W�������ׂ�B����Ȃ��switch�g����i==7�̏ꍇ�����������Ȃ��́H���u���C�N�������Ă��Ȃ���������B


			switch (diCheck[i]) {
			case 0:
				tmpx = -1;
				tmpy = -1;
				break;
			case 1:
				tmpx = 0;
				tmpy = -1;
				break;
			case 2:
				tmpx = 1;
				tmpy = -1;
				break;
			case 3:
				tmpx = 1;
				tmpy = 0;
				break;
			case 4:
				tmpx = 1;
				tmpy = 1;
				break;
			case 5:
				tmpx = 0;
				tmpy = 1;
				break;
			case 6:
				tmpx = -1;
				tmpy = 1;
				break;
			case 7:
				tmpx = -1;
				tmpy = 0;
				break;
			}

			ix = x + tmpx;
			iy = y + tmpy;



			/*s = "ix" + std::to_string(ix) + "iy" + std::to_string(iy) + " tmpx" + std::to_string(tmpx) + " tmpy" + std::to_string(tmpy);
			exhibitScreen();
			DrawString(800, 570, s.c_str(), WHITE);
			WaitKey();*/


			if (ix >= 0 && ix < size && iy >= 0 && iy < size) {




				if (board[ix][iy].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
					if (board[ix][iy].creature->status == EGG && board[ix][iy].creature->team == team) {//���ꂪ���ł������ꍇ

						SETdirection(tmpx, tmpy);
						incubate(ix, iy);
						actionMsg = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "���z���������I";
						return TRUE;
					}
				}

			}
		}

	}
	return FALSE;
}






