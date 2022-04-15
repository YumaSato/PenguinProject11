#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>
#include <stdlib.h>

using namespace std;

Bull::Bull() {
}

void Bull::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {//�����I�ȃR���X�g���N�^�B
	//����������Bull�z�����邽�߂ɂ̓R���X�g���N�^�ɉ��������Ă���ƃ_���炵���̂ŁA�R���X�g���N�^�ł��ׂ����Ƃ�ʂ̊֐��ɂ����B

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	if (ParentTeam == red) {
		name = "�Ԃ�����";
		team = ParentTeam;
		status = BULL;//���ł���ӁB
		//directionX = DirectionX;
		//directionY = DirectionY;
		SETdirection(DirectionX, DirectionY);
		x = ix;
		y = iy;
		HP = 50;
		HP_Limit = 50;
		stamina = NULL;
		staminaLimit = NULL;
		attackPower = 38;
		defensePower = 100;
		speed = 500000 - GetRand(260);//�f�����̓����_���B
		staminaRecoverAbility = NULL;
		num = mobNumber;
		skip = FALSE;//TRUE�̂Ƃ��A�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j
		enemy = TRUE;//�����́A�G�B
	}

	if (ParentTeam == blue) {
		name = "���̓���";
		team = ParentTeam;
		status = BULL;//���ł���ӁB
		//directionX = DirectionX;
		//directionY = DirectionY;
		SETdirection(DirectionX, DirectionY);
		x = ix;
		y = iy;
		HP = 50;
		HP_Limit = 50;
		stamina = NULL;
		staminaLimit = NULL;
		attackPower = 46;
		defensePower = 100;
		speed = 500000 - GetRand(360);//�f�����̓����_���B
		staminaRecoverAbility = NULL;
		num = mobNumber;
		skip = FALSE;//TRUE�̂Ƃ��A�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j
		enemy = TRUE;//�����́A�G�B
	}



	exhibitScreen();
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "�ɓ��������ꂽ�I";
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();
}



bool Bull::selectAction() {

	if (skip == TRUE) {//skip�����ԂȂ�A���I���B
		skip = FALSE;
		return TRUE;
	}

	HP += 2;
	if (HP > HP_Limit) {//���R����
		HP = HP_Limit;
	}

	if (attack(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	if (walk(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	
	return FALSE;
}


void Bull::test() {
}


bool Bull::walk(int size) {
	int ix;
	int iy;
	int dx;
	int dy;
	GETdirectionXY(&dx, &dy);
	ix = x + dx;
	iy = y + dy;

	if (ix >= 0 && ix < size && iy >= 0 && iy < size) {//�}�X���Ֆʈȓ��Ȃ�
		if (board[ix][iy].creature == NULL && board[ix][iy].state != CASTLE) {//�}�X���󔒂Ȃ�

			board[ix][iy].creature = this;
			board[x][y].creature = NULL;



			x = ix;
			y = iy;
			int randDi = 0;//�����I����Ă��玟�ɍs��������������肷��B
			randDi = GetRand(1);
			if (CASTLE_X - x > 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {
				//x��������+(���荶)�ŁA����y��������+(�����)�ŁA����X���̏�Ƃ̋�����Y���̏�Ƃ̋�����蒷���ꍇ(���k��)
				if (randDi == 0) {
					SETdirection(EE);
				}
				if (randDi == 1) {
					SETdirection(SE);
				}
			}
			if (CASTLE_X - x > 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {
				//x��������+(���荶)�ŁA����y��������+(�����)�ŁA����X���̏�Ƃ̋�����Y���̏�Ƃ̋����Ɠ����ꍇ(�k��)
				SETdirection(SE);
			}
			if (CASTLE_X - x > 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {
				//x��������+(���荶)�ŁA����y��������+(�����)�ŁA����X���̏�Ƃ̋�����Y���̏�Ƃ̋������Z���ꍇ�i�k�k���j
				if (randDi == 0) {
					SETdirection(SS);
				}
				if (randDi == 1) {
					SETdirection(SE);
				}
			}
			if (CASTLE_X - x > 0 && CASTLE_Y == y) {
				//x��������+(���荶)�ŁA����y��������0(��Ɠ���)�ŁA����X���̏�Ƃ̋�����Y���̏�Ƃ̋�����蒷���ꍇ�i���j
				SETdirection(EE);
			}

			if (CASTLE_X - x > 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {
				//x��������+(���荶)�ŁA����y��������-(���艺)�ŁA����X���̏�Ƃ̋�����Y���̏�Ƃ̋�����蒷���ꍇ�i���쐼�j
				if (randDi == 0) {
					SETdirection(EE);
				}
				if (randDi == 1) {
					SETdirection(NE);
				}
			}
			if (CASTLE_X - x > 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {
				//x��������+(���荶)�ŁA����y��������-(���艺)�ŁA����X���̏�Ƃ̋�����Y���̏�Ƃ̋����������ꍇ�i�쐼�j
				SETdirection(NE);
			}

			if (CASTLE_X - x > 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {
				//x��������+(���荶)�ŁA����y��������-(���艺)�ŁA����X���̏�Ƃ̋�����Y���̏�Ƃ̋������Z���ꍇ�i��쐼�j
				if (randDi == 0) {
					SETdirection(NN);
				}
				if (randDi == 1) {
					SETdirection(NE);
				}
			}


			if (CASTLE_X - x < 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {//���k��
				if (randDi == 0) {
					SETdirection(WW);
				}
				if (randDi == 1) {
					SETdirection(SW);
				}
			}
			if (CASTLE_X - x < 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {//�k��
				SETdirection(SW);
			}
			if (CASTLE_X - x < 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {//�k�k��
				if (randDi == 0) {
					SETdirection(SS);
				}
				if (randDi == 1) {
					SETdirection(SW);
				}
			}
			if (CASTLE_X - x < 0 && CASTLE_Y == y) {//��
				SETdirection(WW);
			}

			if (CASTLE_X - x < 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {//���쓌
				if (randDi == 0) {
					SETdirection(WW);
				}
				if (randDi == 1) {
					SETdirection(NW);
				}
			}
			if (CASTLE_X - x < 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {//�쓌
				SETdirection(NW);
			}
			if (CASTLE_X - x < 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {//��쓌
				if (randDi == 0) {
					SETdirection(NN);
				}
				if (randDi == 1) {
					SETdirection(NW);
				}
			}

			if (CASTLE_X == x && CASTLE_Y - y < 0) {//��
				SETdirection(NN);
			}
			if (CASTLE_X == x && CASTLE_Y - y > 0) {//�k
				SETdirection(SS);
			}

			return TRUE;
		}
	}
	return FALSE;
}








bool Bull::specialMovement1(int size) {
	return TRUE;
}

bool Bull::specialMovement2(int size) {
	return TRUE;
}

bool Bull::attack(int size) {
	int ix;
	int iy;
	int dx;
	int dy;

	GETdirectionXY(&dx, &dy);
	ix = x + dx;
	iy = y + dy;
	if (ix >= 0 && ix < size && iy >= 0 && iy < size) {//�}�X���Ֆʈȓ��Ȃ�
		if (board[ix][iy].creature != NULL) {//�}�X���󔒂łȂ��A�܂艽������ꍇ
			if (board[ix][iy].creature->enemy == TRUE) {//�ł��G�����m��������
				return FALSE;
			}
			if (board[ix][iy].creature->enemy == FALSE) {//NULL����Ȃ��ă��{�b�g�ǂ���������U��
				damage(ix, iy);
				return TRUE;
			}
		}

		if (board[ix][iy].creature == NULL || team == blue) {//�}�X���󔒂ł���ꍇ













			int diCheck[8] = { 0,1,2,3,4,5,6,7 };//���ʂɓG������΂��ꂪ�D��I�ɍU������邪�A�ׂɂ������G������ꍇ�A�G���U����������������_���ɂ���B
			Direction di = GETdirection();
			for (int i = 0; i < 7; i++) {
				int r = GetRand(7 - i) + i;
				int tmp = diCheck[i];
				diCheck[i] = diCheck[r];
				diCheck[r] = tmp;
			}

			for (int i = 0; i < 8; i++) {//�W�������ׂ�B����Ȃ��switch�g����i==7�̏ꍇ�����������Ȃ��́H���u���C�N�������Ă��Ȃ���������B

				switch (diCheck[i]) {
				case 0:
					dx = -1;
					dy = -1;
					break;
				case 1:
					dx = 0;
					dy = -1;
					break;
				case 2:
					dx = 1;
					dy = -1;
					break;
				case 3:
					dx = 1;
					dy = 0;
					break;
				case 4:
					dx = 1;
					dy = 1;
					break;
				case 5:
					dx = 0;
					dy = 1;
					break;
				case 6:
					dx = -1;
					dy = 1;
					break;
				case 7:
					dx = -1;
					dy = 0;
					break;
				}
				ix = x + dx;
				iy = y + dy;

				if (ix >= 0 && ix < size && iy >= 0 && iy < size) {

					if (board[ix][iy].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
						if (board[ix][iy].creature->enemy == FALSE) {//���ꂪ�y���M������������
							SETdirection(ix, iy);//�G�̕���������
							damage(ix, iy);
							return TRUE;
						}
					}
				}
			}
		}



		if (board[ix][iy].state == CASTLE) {
			board[ix][iy].state = VACANT;
			actionMsg = "����󂳂�Ă��܂����B";
			return TRUE;
		}
	}
	return FALSE;
}