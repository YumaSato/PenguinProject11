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
	string msg = "�͉�����?\n\n���������N���b�N:�s����I��\n�ׂ̃}�X���E�N���b�N(�\���L�[):�����ύX\n\n1:���� 2:�Y�� 3:�z�� 4:�U�� 5:�R�� 6:�p�X\n\n�L�����N�^�����N���b�N:��Ԃ�\��\n\n\n\n\n�X�y�[�X�L�[:���[����\��";
	int xClick = 0;
	int yClick = 0;
	int XBuf = -49;
	int YBuf = -49;
	int mouse = NULL;
	bool clickStop = FALSE;
	bool ruleExhibit = FALSE;
	int dx = 0;
	int dy = 0;
	bool colorUpOrDown = TRUE;
	bool exhibitOrNot = FALSE;
	int color = 10;

	clicking = 0;

	mainMsg = name + msg;
	exhibitScreen(x,y,TRUE);
	WaitKey();

	while (1) {
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			return FALSE;
		}

		if (ruleExhibit == TRUE) {
			while (1) {
				WaitKey();
				if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
					ruleExhibit = FALSE;
					break;
				}
			}
		}


		if (colorUpOrDown == TRUE) {
			color += 25;
		}
		if (colorUpOrDown == FALSE) {
			color -= 25;
		}
		if (color >= 225) {
			colorUpOrDown = FALSE;
		}
		if (color <= 26) {
			colorUpOrDown = TRUE;
		}




		//GetMousePoint(&xClick, &yClick);
		//xClick = xClick / 48;
		//yClick = yClick / 48;
		//if (xClick < FIELDSIZE && yClick < FIELDSIZE) {
		//	dx = xClick - x;
		//	dy = yClick - y;
		//	if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {//�����ׂ̗̃}�X���N���b�N���Ă���ꍇ

		//		//SETdirection(dx, dy);//���̕����������B
		//		//exhibitScreen(x, y, TRUE);

		//		if (board[xClick][yClick].creature == NULL && board[xClick][yClick].state == VACANT) {//����ɂ��̃}�X�ɐ��������Ȃ��A����VACANT�������ꍇ

		//			int StringColor = 0;
		//			string Msg = "";
		//			bool colorUpOrDown = TRUE;

		//			exhibitScreen(x, y, TRUE);
		//			DrawBox(xClick * 48, yClick * 48, xClick * 48 + 48, yClick * 48 + 48, GetColor(StringColor, 255, 50), TRUE);

		//			if (colorUpOrDown == TRUE) {
		//				StringColor += 9;
		//			}
		//			if (colorUpOrDown == FALSE) {
		//				StringColor -= 9;
		//			}
		//			if (StringColor >= 240) {
		//				colorUpOrDown = FALSE;
		//			}
		//			if (StringColor <= 10) {
		//				colorUpOrDown = TRUE;
		//			}
		//		}
		//	}
		//	else{
		//		exhibitScreen(x, y, TRUE);
		//	}

		//}

		//�����N���b�N���ꂽ��Aclicking=1�ɂȂ�B1�̊Ԃ͏����͍s���Ȃ��B




		mouse = GetMouseInput();


		if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//�E�������ǂ���̃N���b�N��������Ă��Ȃ�������A���̃N���b�N���󂯕t����B
			clicking = 0;
		}


		if (mouse & MOUSE_INPUT_RIGHT) {//�E�N���b�N���ꂽ��

			if (clicking == 0) {
				clicking = 1;

				GetMousePoint(&xClick, &yClick);
				xClick = xClick / 48;
				yClick = yClick / 48;

				dx = xClick - x;
				dy = yClick - y;
				if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {//�����ׂ̗̃}�X�̏�Ƀ}�E�X�|�C���^������ꍇ
					SETdirection(dx, dy);
					exhibitScreen(x, y, TRUE);//���̕����������B
				}
			}
		}
		


		if (mouse & MOUSE_INPUT_LEFT) {//���N���b�N���s��ꂽ�ۂ̏���


			if (clicking == 0) {
				clicking = 1;

				GetMousePoint(&xClick, &yClick);//�}�E�X�|�C���^���ǂ��ɂ��邩���擾

				if (exhibitOrNot == TRUE) {//�L�����ڍו\����\������t���O�������Ă����ꍇ
					bool turnFinish = FALSE;
					for (int iii = 0; iii < 6; iii++) {
						if (xClick > x * 48 + 50 + iii * 51 && xClick < x * 48 + 85 + iii * 51 && yClick > y * 48 + 24 && yClick < y * 48 + 43) {

							if (iii == 0) {//�L�����ڍו\���̊e�{�^���������ƍs�����s����
								if (walk(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 1) {
								if (specialMovement1(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 2) {
								if (specialMovement2(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 3) {
								if (attack(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 4) {
								if (kick(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 5) {
								if (turnFinish == FALSE) {
									turnFinish = TRUE;
									break;
								}
							}
						}
					}
					if (turnFinish == TRUE) {
						break;
					}
					
				}




				xClick = xClick / 48;
				yClick = yClick / 48;
				if (xClick < FIELDSIZE && yClick < FIELDSIZE) {
					//if (board[xClick][yClick].creature == NULL) {//�N���b�N�����ꏊ���󔒃}�X�Ȃ�΁A���s���\�b�h�����s
					//	dx = xClick - x;
					//	dy = yClick - y;
					//	if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {
					//		WaitTimer(120);
					//		if (walk(FIELDSIZE) == TRUE) {
					//			break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
					//		}
					//	}

					//	
					//}
					//if (board[xClick][yClick].creature != NULL) {
					//	if (xClick == XBuf && yClick == YBuf) {//���Ƃ��Ƃ̕\�����W�Ɠ����Ƃ�����N���b�N������
					//		exhibitScreen(x, y, TRUE);//�X�e�[�^�X�ڍׂ������B
					//		exhibitOrNot = FALSE;
					//		WaitTimer(70);
					//		XBuf = -1;
					//		YBuf = -1;
					//	}
					if (board[xClick][yClick].creature == NULL) {
						exhibitOrNot = FALSE;
						exhibitScreen(x, y, TRUE);
					}
					if (XBuf >= 0 && XBuf < FIELDSIZE && YBuf >= 0 && YBuf < FIELDSIZE) {//�X�e�[�^�X�\�����̃}�X������XBuf��YBuf���Ֆʏ�̍��W�������Ă����ꍇ
						if (board[xClick][yClick].creature == board[XBuf][YBuf].creature) {//�\�����̃}�X��G������X�e�[�^�X�\��������B
							exhibitOrNot = FALSE;
							exhibitScreen(x, y, TRUE);
						}
					}


					if (board[xClick][yClick].creature != NULL) {

						//if (xClick < FIELDSIZE && yClick < FIELDSIZE) {//���Ƃ��Ƃ̍��W�ƈႤ���A���W�����N���b�N������
						exhibitOrNot = TRUE;
						//}
					}

				}
			}
		}

		


		if (exhibitOrNot == TRUE) {//�N���L�����N�^������}�X�����N���b�N�����Ƃ��̏ڍו\���B
			XBuf = xClick;
			YBuf = yClick;
			if (board[XBuf][YBuf].creature != NULL) {//�X�e�[�^�X�ڍׂ�\���B
				if (board[XBuf][YBuf].creature == this) {//���ꂪ�����ł���΁A�I������\�����ăN���b�N���󂯕t����B

					

					exhibitScreen(x, y, TRUE);
					string Msg1 = "";
					string Msg2 = "";

					DrawBox(x * 48 + 40, y * 48 + 2, x * 48 + 360, y * 48 + 46, GetColor(225, 200, 0), TRUE);//�O���̃{�b�N�X
					DrawBox(x * 48 + 39, y * 48 + 1, x * 48 + 361, y * 48 + 47, GetColor(125, 0, 0), FALSE);//�O���̃{�b�N�X�̉�

					for (int iii = 0; iii < 6; iii++) {
						DrawBox(x * 48 + 50 + iii * 51, y * 48 + 24, x * 48 + 85 + iii * 51, y * 48 + 43, GetColor(50+((color + iii*3) / 10), 220 + iii*5 - (color / 3), 100), TRUE);//�I���{�b�N�X

						/*if (xClick > x * 48 + 50 + iii * 51 && xClick < x * 48 + 85 + iii * 51 && yClick > y * 48 + 24 && yClick < y * 48 + 43) {
							if (iii == 0) {
								if (specialMovement1(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 1) {
								if (specialMovement2(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 2) {
								if (attack(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 3) {
								if (kick(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 0) {
								return TRUE;
							}
						}*/
					}

					Msg1 = board[x][y].creature->name + "��HP:" + std::to_string(board[x][y].creature->HP) + "/" + std::to_string(board[x][y].creature->HP_Limit) + "   �f�����l:" + std::to_string(board[x][y].creature->speed);
					Msg2 = " �����@�Y���@�z���@�U���@�R��@�p�X";

					DrawString(x * 48 + 42, y * 48 + 5, Msg1.c_str(), GetColor(0, 10, 55));
					DrawString(x * 48 + 42, y * 48 + 26, Msg2.c_str(), GetColor(0, 10, 55));

					WaitTimer(10);

				}
				else {//�N���b�N�����̂����삵�Ă���L��������Ȃ��ꍇ�A���ʂɃX�e�[�^�X��\������B
					exhibitStatus(x, y, XBuf, YBuf, TRUE);
	/*				WaitTimer(10);*/
				}
			}
			if (board[XBuf][YBuf].creature == NULL) {
				exhibitScreen(x, y, TRUE);
			}
		}




		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
			exhibitOrNot = FALSE;
			exhibitScreen(x, y, TRUE);
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
			WaitTimer(100);
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
		if (CheckHitKey(KEY_INPUT_6) == TRUE) {
			break;
		}

		if (CheckHitKey(KEY_INPUT_SPACE) == TRUE) {
			ruleExhibit = TRUE;
			exhibitRule();
		}




		WaitTimer(10);
	}

	//stamina += staminaRecoverAbility;//�X�^�~�i��
	//if (stamina > staminaLimit) {
	//	stamina = staminaLimit;//�X�^�~�i�����^���ɂȂ�Ƃ��B
	//}

	HP += 8;//HP��
	if (HP > HP_Limit) {
		HP = HP_Limit;//HP�����^���ɂȂ�Ƃ��B
	}

	
	mainMsg = "";
	actionMsg = "�s���I���B�̗͂��񕜂��܂��B";
	exhibitScreen(x, y, TRUE);
	WaitKey();
	
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
	int distance = 0;
	int checkX = 0;
	int checkY = 0;
	int staminaNeed = 10;

	int xClick = 0;
	int yClick = 0;
	int dx = 0;
	int dy = 0;
	int StringColor = 0;
	int mouse = 0;
	string Msg = "";
	bool colorUpOrDown = TRUE;

	actionMsg = "������!�@Esc:�ړ��I���@SHIFT:�΂߃T�|�[�g";

	clicking = 1;





	while (distance < 3) {//�e���s�̓��͑ҋ@
		exhibitScreen(x, y, TRUE);
		checkX = 0;
		checkY = 0;
		mouse = 0;

		//if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//�����N���b�N����������Ă�����A���̃N���b�N���󂯕t����B
		//	clicking = 0;
		//}


		//if (stamina < staminaNeed) {//�X�^�~�i���K�v���ɖ����Ȃ��ꍇwalk���f�Ń��^�[���B
		//	actionMsg = "�X�^�~�i�؂ꂾ�I";
		//	exhibitScreen(x, y, TRUE);
		//	WaitKey();
		//	if (distance == 0) {
		//		return FALSE;
		//	}
		//	else {
		//		return TRUE;
		//	}
		//}

		exhibitScreen(x, y, TRUE);//������}�X�͕\���F�ύX�B
		for (int iix = -1; iix <= 1; iix++) {
			for (int iiy = -1; iiy <= 1; iiy++) {
				if (board[x + iix][y + iiy].creature == NULL && board[x + iix][y + iiy].state == VACANT) {
					DrawBox((x + iix) * 48 + 1, (y + iiy) * 48 + 1, (x + iix) * 48 + 47, (y + iiy) * 48 + 47, GetColor(StringColor + (iix + 1) * 5 + iiy * 5, 255, 120), TRUE);
				}
			}
		}



		GetMousePoint(&xClick, &yClick);
		xClick = xClick / 48;
		yClick = yClick / 48;


		if (xClick < FIELDSIZE && yClick < FIELDSIZE) {

			

			dx = xClick - x;
			dy = yClick - y;
			if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1)) {//�����ׂ̗̃}�X�̏�Ƀ}�E�X�|�C���^������ꍇ
				if (board[xClick][yClick].creature == NULL && board[xClick][yClick].state == VACANT) {//�󔒃}�X�ɃJ�[�\��������ꍇ�A�L���L���\��
					DrawBox(xClick * 48, yClick * 48, xClick * 48 + 48, yClick * 48 + 48, GetColor(10 + (StringColor / 5), 145 + (StringColor / 3), 0), TRUE);

					mouse = GetMouseInput();

					if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//�E�������ǂ���̃N���b�N��������Ă��Ȃ�������A���̃N���b�N���󂯕t����B
						clicking = 0;
					}

					
					if (mouse & MOUSE_INPUT_LEFT) {


				
						if (clicking == 0) {
							clicking = 1;

							board[xClick][yClick].creature = this;
							board[x][y].creature = NULL;

							x = xClick;//���ꏊ��V���ȃ}�X�ɐݒ�B
							y = yClick;
							SETdirection(dx, dy);


							distance++;

							stamina = stamina - staminaNeed;//�X�^�~�i�̏�������s�B
							staminaNeed = staminaNeed + distance * 3;//���̕��݂Ō�������X�^�~�i������B

							WaitTimer(10);//���̕��s�N���b�N�������ɍs���Ȃ��悤�A�N���b�N����ɍd�����Ԃ�݂���B

						}
					}
				}
				else if(dx == 0 && dy == 0){//�Ȃ�ł���N���b�N�������ɂ��Ă�̂ɃJ�[�\���悹�邾���Ŕ��������Ⴄ�񂾂�`�I�I�H�I�H
					//mouse = GetMouseInput();
					if (mouse & MOUSE_INPUT_LEFT) {
						if (distance == 0) {
							return FALSE;
						}
					}
				}
				
			}
			if((dx < -1 || dx > 1 || dy < -1 || dy > 1 || board[xClick][yClick].creature != NULL || board[xClick][yClick].state != VACANT) && (board[xClick][yClick].creature != this)) {//�u�i�߂Ȃ��}�X���N���b�N���Ă���i�����������j�ꍇ
				mouse = GetMouseInput();
				if (mouse & MOUSE_INPUT_LEFT) {

					if (clicking == 0) {
						clicking = 1;

						exhibitScreen(x, y, TRUE);//���s�\�}�X�\���������B
						WaitTimer(130);
						if (distance == 0) {
							return FALSE;//0���ڂȂ�s���͂Ȃ��������ƂɂȂ�
						}
						else if (distance > 0) {
							return TRUE;//1���ȏ�i��ł�����s����������ɂȂ�B
						}
					}
				}
			}

			mouse = GetMouseInput();
			if (mouse & MOUSE_INPUT_RIGHT) {//�E�N���b�N����āA�܂������Ă��Ȃ���Ε������L�����Z������̂ɐ����B
				if (distance == 0) {
					return FALSE;
					exhibitScreen(x, y, TRUE);
				}
			}

			
			
			


		}
				


		if (colorUpOrDown == TRUE) {
			StringColor += 9;
		}
		if (colorUpOrDown == FALSE) {
			StringColor -= 9;
		}
		if (StringColor >= 230) {
			colorUpOrDown = FALSE;
		}
		if (StringColor <= 11) {
			colorUpOrDown = TRUE;
		}














		if (CheckHitKey(KEY_INPUT_LSHIFT) == FALSE && CheckHitKey(KEY_INPUT_RSHIFT) == FALSE) {
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
		}
		if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE or CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) {//�΂ߕ⏕�V�t�g��������Ă�����
			DrawString(820, 85, "�΂߈ړ����[�h�I��!", WHITE);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//����
				checkX -= 1;
				checkY -= 1;
				//directionY = -1;
				SETdirection(-1, -1);
				
			}
			else if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//�E��
				checkX += 1;
				checkY -= 1;
				//directionY = -1;
				SETdirection(1, -1);
				
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//����
				checkX -= 1;
				checkY += 1;
				//directionY = -1;
				SETdirection(-1, +1);
				
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//�E��
				checkX += 1;
				checkY += 1;
				//directionY = -1;
				SETdirection(1, +1);
				
			}	
		}
	


		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {//1������������s�I���B
			if (distance == 0) {
				WaitTimer(100);
				exhibitScreen(x, y, TRUE);
				return FALSE;
			}
			else {
				return TRUE;
				WaitTimer(80);
			}
		}

		if (x + checkX >= 0 && x + checkX < size && y + checkY >= 0 && y + checkY < size) {
			if (board[x + checkX][y + checkY].creature == NULL && board[x + checkX][y + checkY].state == VACANT) {//�������}�X�̕������󂢂Ă����烋�[�v����

				SETdirection(checkX, checkY);

				board[x + checkX][y + checkY].creature = this;
				board[x][y].creature = NULL;

				x += checkX;//���ꏊ��V���ȃ}�X�ɐݒ�B
				y += checkY;



				distance += 1;

				stamina = stamina - staminaNeed;//�X�^�~�i�̏�������s�B
				staminaNeed = staminaNeed + distance * 3;//���̕��݂Ō�������X�^�~�i������B

				WaitTimer(150);
			}
		}

	
		WaitTimer(20);
	}
	return TRUE;
	actionMsg = "walk�̎��s���I��";
		
	exhibitScreen(x, y, TRUE);
	

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
