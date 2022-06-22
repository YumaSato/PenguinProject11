#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>
#include <stdlib.h>

using namespace std;

Bull::Bull() {
}

void Bull::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, Grid** board, Emperor* handledCharacters) {//�����I�ȃR���X�g���N�^�B
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
		levelUp = initLevel;
		expPoint = NULL;
		attackPower = 30 + levelUp * 2;
		defensePower = 92 + levelUp * 2;//(92)
		giveExpPoint = 60 + levelUp * 15;
		speed = 999 - GetRand(760);//�f�����̓����_���B
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
		levelUp = initLevel;
		expPoint = NULL;
		attackPower = 50 + levelUp * 2;
		defensePower = 150 + levelUp * 2;
		speed = 999 - GetRand(960);//�f�����̓����_���B
		staminaRecoverAbility = NULL;
		num = mobNumber;
		skip = FALSE;//TRUE�̂Ƃ��A�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j
		enemy = TRUE;//�����́A�G�B
	}



	exhibitScreen(x, y, TRUE, board, handledCharacters);
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "�ɓ��������ꂽ�I";
	actionMsg = mobStatusMsg;
	WaitKey();
}



int Bull::selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {


	if (skip == TRUE) {//skip�����ԂȂ�A���I���B
		skip = FALSE;
		return FALSE;
	}

	HP += GetRand(2);
	if (HP > HP_Limit) {//���R����
		HP = HP_Limit;
	}

	if (attack( board, handledCharacters) == TRUE) {
		return TRUE;
	}
	if (walk( board, handledCharacters) == TRUE) {
		return TRUE;
	}
	return FALSE;
}


void Bull::test() {
}


bool Bull::walk( Grid** board, Emperor* handledCharacters) {
	int ix;
	int iy;
	int dx;
	int dy;
	GETdirectionXY(&dx, &dy);
	ix = x + dx;
	iy = y + dy;
	bool walkOrNot = FALSE;

	if (ix >= 0 && ix < GameBuf->sizeX && iy >= 0 && iy < GameBuf->sizeY) {//�������ۂ��𔻒肵�AwalkOrNot�ɔ��茋�ʂ��i�[�B
		if (board[ix][iy].creature != NULL) {
			if (board[ix][iy].creature->status == EGG) {//�}�X�ɗ��������
				board[ix][iy].creature->DeleteCreature();//�������ʁB
				actionMsg = name + "�͕������B���𓥂݂Ԃ����B";
				walkOrNot = TRUE;
			}
		}
		if (board[ix][iy].creature == NULL && board[ix][iy].state != CASTLE) {//�}�X���󔒂Ȃ�
			actionMsg = name + "�͕������B";
			walkOrNot = TRUE;
		}
	}

	if (walkOrNot == TRUE) {//��������TRUE�Ȃ�A���ׂ��}�X�Ɏ����̃A�h���X������B
		board[ix][iy].creature = this;
		board[x][y].creature = NULL;
		x = ix;//�����̈ʒu��xy�ɓ����B
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
	return FALSE;
}








bool Bull::specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
	return TRUE;
}

bool Bull::specialMovement2( Grid** board, Emperor* handledCharacters) {
	return TRUE;
}

bool Bull::attack( Grid** board, Emperor* handledCharacters) {
	int ix;
	int iy;
	int dx;
	int dy;

	GETdirectionXY(&dx, &dy);
	ix = x + dx;
	iy = y + dy;
	if (ix >= 0 && ix < GameBuf->sizeX && iy >= 0 && iy < GameBuf->sizeY) {//�}�X���Ֆʈȓ��Ȃ�
		if (board[ix][iy].creature != NULL) {//�}�X���󔒂łȂ��A�܂艽������ꍇ
			if (board[ix][iy].creature->enemy == TRUE || board[ix][iy].creature->status == EGG) {//�ł��G�����m������������
				return FALSE;
			}
			if (board[ix][iy].creature->enemy == FALSE) {//NULL����Ȃ��ă��{�b�g�ǂ���������U��
				damage(ix, iy, board, handledCharacters);
				return TRUE;
			}
		}



		if (board[ix][iy].creature == NULL && team == blue) {//�}�X���󔒂ł���ꍇ

			int diCheck[8] = { 0,1,2,3,4,5,6,7 };//���ʂɓG������΂��ꂪ�D��I�ɍU������邪�A�ׂɂ������G������ꍇ�A�G���U����������������_���ɂ���B
			Direction di = GETdirection();//�����f�[�^�����u���B
			for (int i = 0; i < 7; i++) {
				int r = GetRand(7 - i) + i;
				int tmp = diCheck[i];
				diCheck[i] = diCheck[r];
				diCheck[r] = tmp;
			}

			for (int i = 0; i < 8; i++) {

				switch (diCheck[i]) {
				case 0:
					SETdirection(NW);
					break;
				case 1:
					SETdirection(NN);
					break;
				case 2:
					SETdirection(NE);
					break;
				case 3:
					SETdirection(EE);
					break;
				case 4:
					SETdirection(SE);
					break;
				case 5:
					SETdirection(SS);
					break;
				case 6:
					SETdirection(SW);
					break;
				case 7:
					SETdirection(WW);
					break;
				}



				if ((GETdirection() - di <= 2 && GETdirection() - di >= -2) || (GETdirection() == 1 && di == 7) || (GETdirection() == 0 && di == 7) || (GETdirection() == 0 && di == 6)) {
					//���G�͈͂́A����+-2�܂ŁB��U������ς������Ƃɂ���B���G�͈͂����ׂč��G������ɁA������Ȃ���Ε��������ɖ߂��B
					GETdirectionXY(&dx, &dy);
					ix = x + dx;
					iy = y + dy;//���G�}�X��ݒ�B

					if (ix >= 0 && ix < GameBuf->sizeX && iy >= 0 && iy < GameBuf->sizeY) {

						if (board[ix][iy].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
							if (board[ix][iy].creature->enemy == FALSE && board[ix][iy].creature->status != EGG) {//���ꂪ�y���M�����ŁA������Ȃ����
								SETdirection(dx, dy);//�G�̕���������
								damage(ix, iy, board, handledCharacters);
								return TRUE;
							}
						}
					}
				}
				SETdirection(di);//���G���Ă�������Ȃ������猳�̕����ɖ߂�B
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