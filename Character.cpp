#include <string>
#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"

using std::string;

//�v���g�^�C�v�錾
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Character::Character() : Creature() {}

bool Character::selectAction() {
	string msg = "�͉�����?\n\n1:���� 2:�Y�� 3:�z�� 4:�U�� 5:�R��\n�L�������E�N���b�N:��Ԃ�\��";
	int xClick = NULL;
	int yClick = NULL;
	int XBuf = -49;
	int YBuf = -49;
	int mouse = NULL;
	mainMsg = name + msg;
	exhibitScreen(x,y,TRUE);
	WaitKey();
	while (1) {

		mouse = GetMouseInput();
		if (mouse & MOUSE_INPUT_RIGHT) {
			GetMousePoint(&xClick, &yClick);
			xClick = xClick / 48;
			yClick = yClick / 48;

			if (xClick == XBuf && yClick == YBuf) {//���Ƃ��Ƃ̕\�����W�Ɠ����Ƃ�����N���b�N������
				exhibitScreen(x, y, TRUE);//�X�e�[�^�X�ڍׂ������B
				WaitTimer(250);
				XBuf = -1;
				YBuf = -1;
			}else if (xClick < FIELDSIZE && yClick < FIELDSIZE) {//���Ƃ��Ƃ̍��W�ƈႤ���A���W�����N���b�N������
				XBuf = xClick;
				YBuf = yClick;
				if (board[XBuf][YBuf].creature != NULL) {//�X�e�[�^�X�ڍׂ�\���B
					exhibitStatus(x, y, XBuf, YBuf, TRUE);
					WaitTimer(250);
				}
				if (board[XBuf][YBuf].creature == NULL) {
					exhibitScreen(x, y, TRUE);
				}
			}
		}


		if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//���������ς��:�E
			//directionX = 1;
			//directionY = 0;
			SETdirection(1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//���������ς��:�E��
				//directionY = -1;
				SETdirection(1, -1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//���������ς��:�E��
				//directionY = 1;
				SETdirection(1, 1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			exhibitScreen(x, y, TRUE);
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//���������ς��:��
			//directionX = -1;
			//directionY = 0;
			SETdirection(-1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//���������ς��:����
				//directionY = -1;
				SETdirection(-1, -1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//���������ς��:����
				//directionY = 1;
				SETdirection(-1, 1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			exhibitScreen(x, y, TRUE);
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//���������ς��:��
			//directionX = 0;
			//directionY = 1;
			SETdirection(0, 1);
			exhibitScreen(x, y, TRUE);
		}
		else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//���������ς��:��
			//directionX = 0;
			//directionY = -1;
			SETdirection(0, -1);
			exhibitScreen(x, y, TRUE);
		}




		//board[x][y].creature->directionX = this->directionX;
		//board[x][y].creature->directionY = this->directionY;




		if (CheckHitKey(KEY_INPUT_1) == TRUE) {
			if (walk(FIELDSIZE) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_2) == TRUE) {
			if (specialMovement1(FIELDSIZE) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_3) == TRUE) {
			if (specialMovement2(FIELDSIZE) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_4) == TRUE) {
			if (attack(FIELDSIZE) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_5) == TRUE) {
			if (kick(FIELDSIZE) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
	}

	stamina += 20;//�X�^�~�i��
	if (stamina > staminaLimit) {
		stamina = staminaLimit;//�X�^�~�i�����^���ɂȂ�Ƃ��B
	}

	HP += 8;//HP��
	if (HP > HP_Limit) {
		HP = HP_Limit;//HP�����^���ɂȂ�Ƃ��B
	}

	

	actionMsg = "�s���I���B�X�^�~�i���񕜂��܂��B";
	exhibitScreen(x, y, TRUE);
	WaitKey();
	mainMsg = "";
	return TRUE;
};


void Character::test() {
	DrawString(400, 300, "Character.test���\�b�h���s", WHITE);
	WaitKey();
}


void Character::changeDirection() {//�������Ɍ�����ς���
	WaitKey();
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//�Ȃ��㉺���E���t�Ȃ́H��B
		//directionX = 1;
		//directionY = 0;
		SETdirection(1, 0);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {
		//directionX = -1;
		//directionY = 0;
		SETdirection(-1, 0);
	}
	else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {
		//directionX = 0;
		//directionY = 1;
		SETdirection(0, 1);
	}
	else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {
		//directionX = 0;
		//directionY = -1;
		SETdirection(0, -1);
	}
	//board[x][y].creature->directionX = this->directionX;
	//board[x][y].creature->directionY = this->directionY;
	int tmpx, tmpy;
	this->GETdirectionXY(&tmpx, &tmpy);
	board[x][y].creature->SETdirection(tmpx, tmpy);
	exhibitScreen(x, y, TRUE);
};


bool Character::walk(int size) {//�����B�ՖʃT�C�Y(size)���󂯎��
	int distance = 3;
	int checkX;
	int checkY;
	int staminaNeed = 10;

	if (stamina < 20) {//�Œ�X�^�~�i����ł���20�ȉ������X�^�~�i���Ȃ��ꍇ�Awalk�ł������^�[���B
		return FALSE;
	}

	for (int i = 1; i <= distance; i++) {//1������

		if (stamina < staminaNeed) {//�X�^�~�i���K�v���ɖ����Ȃ��ꍇwalk���f�Ń��^�[���B
			actionMsg = "�X�^�~�i�؂ꂾ�I";
			exhibitScreen(x, y, TRUE);
			return TRUE;
		}

		actionMsg = "������!�@1:�ړ��I���@SHIFT:�΂߃T�|�[�g";
		exhibitScreen(x, y, TRUE);

		while (1) {
			checkX = this->x;//�����̂�����W�����B
			checkY = this->y;//checkX��checkY�Ői�߂�}�X���T�m�B
			WaitKey();
			if (CheckHitKey(KEY_INPUT_1) == TRUE) {//1������������s�I���B
				return TRUE;
			}




			if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {
				checkX -= 1;
				//directionX = -1;
				//directionY = 0;
				SETdirection(-1, 0);
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {
				checkX += 1;
				//directionX = 1;
				//directionY = 0;
				SETdirection(1, 0);
			}
			else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {
				checkY -= 1;
				//directionY = -1;
				//directionX = 0;
				SETdirection(0, -1);
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {
				checkY += 1;
				//directionY = 1;
				//directionX = 0;
				SETdirection(0, 1);
			}


			else if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE or CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) {//�΂ߕ⏕�V�t�g��������Ă�����
				while (1) {
					DrawString(800, 85, "�΂߈ړ����[�h�I��!", WHITE);
					WaitKey();
					if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//����
						checkX -= 1;
						checkY -= 1;
						//directionY = -1;
						SETdirection(-1, -1);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//�E��
						checkX += 1;
						checkY -= 1;
						//directionY = -1;
						SETdirection(1, -1);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//����
						checkX -= 1;
						checkY += 1;
						//directionY = -1;
						SETdirection(-1, +1);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//�E��
						checkX += 1;
						checkY += 1;
						//directionY = -1;
						SETdirection(1, +1);
						break;
					}

					else if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE or CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) {//�΂ߕ⏕����
						exhibitScreen(x, y, TRUE);
						DrawString(800, 70, "������! 1:�ړ��I���@SHIFT:�΂߃T�|�[�g", WHITE);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_1) == TRUE) {//1������������s�I���B
						return TRUE;
					}
				}
			}

			if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
				if (board[checkX][checkY].creature == NULL && board[checkX][checkY].state == VACANT) {//�������}�X�̕������󂢂Ă����烋�[�v����
					break;
				}
			}
		}


		board[checkX][checkY].creature = this;

		board[x][y].creature = NULL;

		x = checkX;//���ꏊ��V���ȃ}�X�ɐݒ�B
		y = checkY;


		stamina = stamina - staminaNeed;//�X�^�~�i�̏�������s�B
		staminaNeed = staminaNeed + i * 5;//���̕��݂Ō�������X�^�~�i������B


		exhibitScreen(x, y, TRUE);
	};


	actionMsg = "walk�̎��s���I��";
	exhibitScreen(x, y, TRUE);
	return TRUE;
}








bool Character::attack(int size) {

	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
		if (board[checkX][checkY].creature == NULL) {//�������ꏊ�ɒN�����Ȃ���΁AFALSE��Ԃ��āA�s���Ȃ�����B
			return FALSE;
		}
		damage(checkX, checkY);


		string msg1 = "�͍U�������B";
		//string msg2 = board[checkX][checkY].creature->name;//�Ȃ������s���G���[���o��B
		string msg3 = "�̓_���[�W���󂯂��B";
		actionMsg = name + msg1;




		exhibitScreen(x, y, TRUE);
		DrawString(800, 180, actionMsg.c_str(), GetColor(255, 200, 255));
		WaitKey();
		return TRUE;
	}
	return FALSE;
}
