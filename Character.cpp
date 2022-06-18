#include <string>
#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"

using std::string;

//�v���g�^�C�v�錾
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Character::Character() : Creature() {}

int Character::selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid**board, Emperor* handledCharacters) {
	string msg = "�͉�����?\n\n���������N���b�N:�s����I��\n�ׂ̃}�X���E�N���b�N(�\���L�[):�����ύX\n\n1:���� 2:�Y�� 3:�z�� 4:�U�� 5:�R�� 6:�p�X\n\n�L�����N�^�����N���b�N:��Ԃ�\��\n\n\n\n\n�X�y�[�X�L�[:���[����\��";
	int xClick = 0;
	int yClick = 0;
	int XBuf = -49;//�X�e�[�^�X�\�����s���ۂɁA���N���b�N�����킯����Ȃ����ǃX�e�[�^�X�\����ԂƂ��Ď������Ă���}�X�̍��W��\���B
	int YBuf = -49;
	int mouse = NULL;
	bool clickStop = FALSE;
	bool ruleExhibit = FALSE;
	int dx = 0;
	int dy = 0;
	bool colorUpOrDown = TRUE;
	bool exhibitOrNot = FALSE;
	bool exhibitMyStatusOrNot = FALSE;
	int color = 10;

	clicking = 0;

	mainMsg = name + msg;
	exhibitScreen(x, y, TRUE, board, handledCharacters);
	WaitKey();

	while (1) {
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			return FALSE;
		}

		if (ruleExhibit == TRUE) {
			while (1) {
				WaitKey();
				if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE || CheckHitKey(KEY_INPUT_0) == TRUE) {
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
					exhibitScreen(x, y, TRUE, board, handledCharacters);//���̕����������B
				}
			}
		}



		if (mouse & MOUSE_INPUT_LEFT) {//���N���b�N���s��ꂽ�ۂ̏���


			if (clicking == 0) {
				clicking = 1;

				GetMousePoint(&xClick, &yClick);//�}�E�X�|�C���^���ǂ��ɂ��邩���擾

				if (exhibitMyStatusOrNot == TRUE) {//����\�L�����̏ڍׂ�\������t���O�������Ă����ꍇ
					bool turnFinish = FALSE;
					for (int iii = 0; iii < 6; iii++) {//�U�̑I�������N���b�N���󂯕t����B
						if (xClick > x * 48 + 50 + iii * 51 && xClick < x * 48 + 85 + iii * 51 && yClick > y * 48 + 24 && yClick < y * 48 + 43) {

							if (iii == 0) {//�L�����ڍו\���̊e�{�^���������ƍs�����s����
								if (walk( board, handledCharacters) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 1) {
								if (specialMovement1( mobs_PenguinKids, mobs_Bull, board, handledCharacters) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 2) {
								if (specialMovement2( board, handledCharacters) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 3) {
								if (attack( board, handledCharacters) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 4) {
								if (kick( board, handledCharacters) == TRUE) {
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
				//�������́A������󂯕t������e�B���̉��́A



				xClick = xClick / 48;//���̐�́AXClick��YClick���A�������}�X��\���B
				yClick = yClick / 48;
				if (xClick < GameBuf->xSize && yClick < GameBuf->ySize) {


					if (board[xClick][yClick].creature == NULL) {//�������}�X��NULL�Ȃ�A�X�e�[�^�X�\����Ԃ������B
						exhibitOrNot = FALSE;
						XBuf = -1;
						YBuf = -1;
						exhibitScreen(x, y, TRUE, board, handledCharacters);
					}
					
					if (board[xClick][yClick].creature != NULL) {//�L����������ꏊ���N���b�N������

						if (XBuf >= 0 && XBuf < GameBuf->xSize && YBuf >= 0 && YBuf < GameBuf->ySize) {//�X�e�[�^�X�\�����̃}�X������XBuf��YBuf���Ֆʏ�̍��W�������Ă����ꍇ
							if (board[xClick][yClick].creature == board[XBuf][YBuf].creature) {//�\�����̃}�X��G������X�e�[�^�X�\��������B
								exhibitOrNot = FALSE;
								XBuf = -1;
								YBuf = -1;
								exhibitScreen(x, y, TRUE, board, handledCharacters);
							}
						}
						else{
							exhibitOrNot = TRUE;
						}
						
					

						if (xClick == x && yClick == y) {
							exhibitMyStatusOrNot = TRUE;
						}
						else {
							exhibitMyStatusOrNot = FALSE;
						}
					}

				}
			}
		}




		if (exhibitOrNot == TRUE) {//�N���L�����N�^������}�X�����N���b�N�����Ƃ��̏ڍו\���B
			XBuf = xClick;
			YBuf = yClick;
			if (board[XBuf][YBuf].creature != NULL) {

				exhibitStatus(x, y, XBuf, YBuf, TRUE, color, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}
			if (board[XBuf][YBuf].creature == NULL) {
				exhibitScreen(x, y, TRUE, board, handledCharacters);
			}
		}




		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
			exhibitOrNot = FALSE;
			exhibitScreen(x, y, TRUE, board, handledCharacters);
		}





		if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//���������ς��:�E
			//directionX = 1;
			//directionY = 0;
			SETdirection(1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//���������ς��:�E��
				//directionY = -1;
				SETdirection(1, -1);
				exhibitScreen(x, y, TRUE, board, handledCharacters);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//���������ς��:�E��
				//directionY = 1;
				SETdirection(1, 1);
				exhibitScreen(x, y, TRUE, board, handledCharacters);
				WaitTimer(200);
			}
			exhibitScreen(x, y, TRUE, board, handledCharacters);
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//���������ς��:��
			//directionX = -1;
			//directionY = 0;
			SETdirection(-1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//���������ς��:����
				//directionY = -1;
				SETdirection(-1, -1);
				exhibitScreen(x, y, TRUE, board, handledCharacters);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//���������ς��:����
				//directionY = 1;
				SETdirection(-1, 1);
				exhibitScreen(x, y, TRUE, board, handledCharacters);
				WaitTimer(200);
			}
			exhibitScreen(x, y, TRUE, board, handledCharacters);
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//���������ς��:��
			//directionX = 0;
			//directionY = 1;
			SETdirection(0, 1);
			exhibitScreen(x, y, TRUE, board, handledCharacters);
		}
		else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//���������ς��:��
			//directionX = 0;
			//directionY = -1;
			SETdirection(0, -1);
			exhibitScreen(x, y, TRUE, board, handledCharacters);
		}




		//board[x][y].creature->directionX = this->directionX;
		//board[x][y].creature->directionY = this->directionY;




		if (CheckHitKey(KEY_INPUT_1) == TRUE) {
			WaitTimer(100);
			if (walk( board, handledCharacters) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_2) == TRUE) {
			if (specialMovement1( mobs_PenguinKids, mobs_Bull, board, &handledCharacters[0]) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_3) == TRUE) {
			if (specialMovement2( board, handledCharacters) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_4) == TRUE) {
			if (attack( board, handledCharacters) == TRUE) {
				break;//1���Ԃ��Ă���A�܂萬������΃��[�v�����Ń^�[���I��
			}
		}
		if (CheckHitKey(KEY_INPUT_5) == TRUE) {
			if (kick( board, handledCharacters) == TRUE) {
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

		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {

			while (1) {

				mainMsg = "�{���ɃQ�[�����I�����Ă�낵���ł����H \nEnter�L�[:Yes 0:No";
				ClearDrawScreen();
				exhibitScreen(x, y, TRUE, board, handledCharacters);




				if (CheckHitKey(KEY_INPUT_RETURN) == TRUE) {
					return 2;
				}
				if (CheckHitKey(KEY_INPUT_0) == TRUE || CheckHitKey(KEY_INPUT_SPACE) == TRUE) {
					break;
				}
				WaitTimer(10);
			}
		}




		WaitTimer(10);
		//ScreenFlip(); //����ʂ�\��ʂɔ��f
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
	exhibitScreen(x, y, TRUE, board, handledCharacters);
	WaitKey();

	return TRUE;
};
















void Character::test() {
	DrawString(400, 300, "Character.test���\�b�h���s", WHITE);
	WaitKey();
}


//void Character::changeDirection() {//�������Ɍ�����ς���
//	WaitKey();
//	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//�Ȃ��㉺���E���t�Ȃ́H��B
//		//directionX = 1;
//		//directionY = 0;
//		SETdirection(1, 0);
//	}
//	else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {
//		//directionX = -1;
//		//directionY = 0;
//		SETdirection(-1, 0);
//	}
//	else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {
//		//directionX = 0;
//		//directionY = 1;
//		SETdirection(0, 1);
//	}
//	else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {
//		//directionX = 0;
//		//directionY = -1;
//		SETdirection(0, -1);
//	}
//	//board[x][y].creature->directionX = this->directionX;
//	//board[x][y].creature->directionY = this->directionY;
//	int tmpx, tmpy;
//	this->GETdirectionXY(&tmpx, &tmpy);
//	board[x][y].creature->SETdirection(tmpx, tmpy);
//	exhibitScreen(x, y, TRUE);
//};












bool Character::walk( Grid**board, Emperor* handledCharacters) {//�����B�ՖʃT�C�Y(size)���󂯎��
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
		exhibitScreen(x, y, TRUE, board, handledCharacters);
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

		exhibitScreen(x, y, TRUE, board, handledCharacters);//������}�X�͕\���F�ύX�B
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


		if (xClick < GameBuf->xSize && yClick < GameBuf->ySize) {



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

							WaitTimer(10);//���̕��s�N���b�N�������ɍs���Ȃ��悤�A�N���b�N����ɍd�����Ԃ�݂���B

						}
					}
				}
				else if (dx == 0 && dy == 0) {//�Ȃ�ł���N���b�N�������ɂ��Ă�̂ɃJ�[�\���悹�邾���Ŕ��������Ⴄ�񂾂�`�I�I�H�I�H
					//mouse = GetMouseInput();
					if (mouse & MOUSE_INPUT_LEFT) {
						if (distance == 0) {
							return FALSE;
						}
					}
				}

			}
			if ((dx < -1 || dx > 1 || dy < -1 || dy > 1 || board[xClick][yClick].creature != NULL || board[xClick][yClick].state != VACANT) && (board[xClick][yClick].creature != this)) {//�u�i�߂Ȃ��}�X���N���b�N���Ă���i�����������j�ꍇ
				mouse = GetMouseInput();
				if (mouse & MOUSE_INPUT_LEFT) {

					if (clicking == 0) {
						clicking = 1;

						exhibitScreen(x, y, TRUE, board, handledCharacters);//���s�\�}�X�\���������B
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
					exhibitScreen(x, y, TRUE, board, handledCharacters);
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
				exhibitScreen(x, y, TRUE, board, handledCharacters);
				return FALSE;
			}
			else {
				return TRUE;
				WaitTimer(80);
			}
		}

		if (x + checkX >= 0 && x + checkX < GameBuf->xSize && y + checkY >= 0 && y + checkY < GameBuf->ySize) {
			if (board[x + checkX][y + checkY].creature == NULL && board[x + checkX][y + checkY].state == VACANT) {//�������}�X�̕������󂢂Ă����烋�[�v����

				SETdirection(checkX, checkY);

				board[x + checkX][y + checkY].creature = this;
				board[x][y].creature = NULL;

				x += checkX;//���ꏊ��V���ȃ}�X�ɐݒ�B
				y += checkY;



				distance += 1;

				WaitTimer(150);
			}
		}


		WaitTimer(20);
	}
	return TRUE;
	actionMsg = "�����I������I";

	exhibitScreen(x, y, TRUE, board, handledCharacters);


}








bool Character::attack( Grid**board, Emperor* handledCharacters) {

	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < GameBuf->xSize && checkY >= 0 && checkY < GameBuf->ySize) {
		if (board[checkX][checkY].creature == NULL) {//�������ꏊ�ɒN�����Ȃ���΁AFALSE��Ԃ��āA�s���Ȃ�����B
			return FALSE;
		}
		damage(checkX, checkY, board, handledCharacters);


		//string msg1 = "�͍U�������B";
		////string msg2 = board[checkX][checkY].creature->name;//�Ȃ������s���G���[���o��B
		//string msg3 = "�̓_���[�W���󂯂��B";
		//actionMsg = name + msg1;




		//exhibitScreen(x, y, TRUE, board, handledCharacters);
		//DrawString(800, 180, actionMsg.c_str(), GetColor(255, 200, 255));
		WaitKey();
		return TRUE;
	}
	return FALSE;
}
