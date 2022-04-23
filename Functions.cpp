#include "DxLib.h"
#include <string>
#include <iostream>
#include "DxLib.h"
#include "consts.h"
#include "externs.h"
#include "MyClasses.h"
#include <vector>

using std::to_string;






void exhibitStatusMsg() {//��������L�����N�^�̃X�e�[�^�X����\������B

	string CharacterStatusMsg;

	string HP_Msg = "";
	string staminaMsg = "";
	int exhibitY = 600;
	for (int i = 0; i < CHARACTERNUM; i++) {

		string numHP;
		numHP = (to_string(handledCharacters[i]->HP));
		string numHP_Limit;
		numHP_Limit = (to_string(handledCharacters[i]->HP_Limit));
		string numStamina;
		numStamina = (to_string(handledCharacters[i]->stamina));
		string numStaminaLimit;
		numStaminaLimit = (to_string(handledCharacters[i]->staminaLimit));

		CharacterStatusMsg = handledCharacters[i]->name + "�̏��\n HP :" + numHP + " / " + numHP_Limit + "\n�X�^�~�i" + numStamina + " / " + numStaminaLimit;

		//char HP_NumStr[BUFFER];
		//sprintf_s(HP_NumStr, BUFFER, "%d / %d\n", handledCharacters[i].HP, handledCharacters[i].HP_Limit);

		//char stamina_NumStr[BUFFER];
		//sprintf_s(stamina_NumStr, BUFFER, "%d / %d", handledCharacters[i].stamina, handledCharacters[i].staminaLimit);

	   // CharacterStatusMsg = handledCharacters[i].name +"�̏��\n HP :"+ (string)HP_NumStr +"�X�^�~�i:"+ (string)stamina_NumStr;

		//staminaMsg = "�X�^�~�i : % d / % d ", handledCharacters[i].stamina, handledCharacters[i].staminaLimit;
		//DrawString(800, exhibitY + 20 , HP_Msg.c_str(), GetColor(255, 200, 255));


		DrawString(FIELDSIZE * SQUARESIZE + 5, exhibitY, CharacterStatusMsg.c_str(), GetColor(255, 200, 255));



		exhibitY = exhibitY + 90;
	}

}





void exhibitScreen(int markX, int markY ,bool attention) {//�y���M����`��i�X�e�[�^�X�ƌ�������y���M���̓K�؂ȉ摜�̃n���h������肵�i�[���Ă���`��j
	int h;//�n���h���i�[�p
	string turn = "";
	bool HPexhibitOrNot;
	ClearDrawScreen();//��x��ʂ�S����
	DrawGraph(0, 0, HandleBoard, TRUE);

	if (attention == TRUE) {//���ڑΏۃL�����̃}�X�ɒ��ڗp�̉~��\�����邩�ۂ�
		DrawBox(markX * 48 + 2, markY * 48 + 2, markX * 48 + 46, markY * 48 + 46, GetColor(255, 200, 0), TRUE);
	}



	for (int ix = 0; ix < FIELDSIZE; ix++) {
		for (int iy = 0; iy < FIELDSIZE; iy++) {
			if (board[ix][iy].state == ROCK) {
				DrawBox(ix * SQUARESIZE, iy * SQUARESIZE, ix * SQUARESIZE + 47, iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}
			if (board[ix][iy].state == CASTLE) {
				DrawGraph(ix * SQUARESIZE, iy * SQUARESIZE, HandleCastle, TRUE);
			}


			HPexhibitOrNot = FALSE;//�̗͂����^���łȂ��ꍇ�A���ꂪTRUE�ɂȂ�A���[�^���\�������B

			if (board[ix][iy].creature == NULL) {
				continue;
			}
			else if (board[ix][iy].creature->status == EGG) {//���̏ꍇ�͕������������ߓ񎟌��z���2�ڂ�0�Ԗڂɂ����摜�������Ă��炸����ȊO��null(?)�B
				h = handle[board[ix][iy].creature->team][EGG][NW];
			}
			else if (board[ix][iy].creature->status != EGG) {
				//Func<int, int, bool> f = (i, j) = > board[ix][iy].directionX == i && board[ix][iy].directionY == j;
				//if (f(-1, -1)) directionNum = 0;
				//if (board[ix][iy].creature->directionX == -1 && board[ix][iy].creature->directionY == -1) {//�������΂ߍ���̂Ƃ�
				//	directionNum = NW;
				//}
				//if (board[ix][iy].creature->directionX == 0 && board[ix][iy].creature->directionY == -1) {//��������̂Ƃ�
				//	directionNum = NN;
				//}
				//if (board[ix][iy].creature->directionX == 1 && board[ix][iy].creature->directionY == -1) {//�������΂߉E��̂Ƃ�
				//	directionNum = NE;
				//}
				//if (board[ix][iy].creature->directionX == 1 && board[ix][iy].creature->directionY == 0) {//�������E�̂Ƃ�
				//	directionNum = EE;
				//}
				//if (board[ix][iy].creature->directionX == 1 && board[ix][iy].creature->directionY == 1) {//�������΂߉E���̂Ƃ�
				//	directionNum = SE;
				//}
				//if (board[ix][iy].creature->directionX == 0 && board[ix][iy].creature->directionY == 1) {//���������̂Ƃ�
				//	directionNum = SS;
				//}
				//if (board[ix][iy].creature->directionX == -1 && board[ix][iy].creature->directionY == 1) {//�������΂ߍ����̂Ƃ�
				//	directionNum = SW;
				//}
				//if (board[ix][iy].creature->directionX == -1 && board[ix][iy].creature->directionY == 0) {//���������̂Ƃ�
				//	directionNum = WW;
				//}
				Direction directionNum;
				directionNum = board[ix][iy].creature->GETdirection();
				h = handle[board[ix][iy].creature->team][board[ix][iy].creature->status][directionNum];


				if (board[ix][iy].creature->HP < board[ix][iy].creature->HP_Limit) {
					HPexhibitOrNot = TRUE;
				}
			}
			//LoadGraphScreen(0, 0, "back.png", TRUE);
			DrawGraph(ix * SQUARESIZE, iy * SQUARESIZE, h, TRUE);//��x�N���X�̕ϐ��Ɋi�[����Handle�ŕ`��
			//DrawString(450, 20, msg.c_str(), WHITE);

			if (HPexhibitOrNot == TRUE) {
				DrawGraph(ix * SQUARESIZE + 5, iy * SQUARESIZE + 29, hHP, TRUE);
				DrawBox(ix * SQUARESIZE + 16, iy * SQUARESIZE + 31, ix * SQUARESIZE + 16 + board[ix][iy].creature->HP / 2, iy * SQUARESIZE + 36, GetColor(45, 205, 50), TRUE);
			}

		}
	}
	//exhibitStatusMsg();//�L�����N�^0�̃��b�Z�[�W�����B
	DrawString(FIELDSIZE * SQUARESIZE + 5, 20, mainMsg.c_str(), WHITE);
	DrawString(FIELDSIZE * SQUARESIZE + 5, 380, actionMsg.c_str(), GetColor(255, 200, 255));

	turn = "���݂̃^�[��:" + std::to_string(turnNum);
	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20 ,turn.c_str(), GetColor(255, 200, 255));
	actionMsg = "";
}
















void exhibitDamage(int markX, int markY, int damageX, int damageY, bool attention, int damageHP) {
	
	Creature* damaged = board[damageX][damageY].creature;//��_���[�W�����ꎞ�ۑ��B
	board[damageX][damageY].creature = NULL;//��U���̏�ɃL���������Ȃ����Ƃɂ���B

	Creature substitute = *damaged;//��_���[�W���̐g��������B
	substitute.HP += damageHP;//�g����́A�̗͖��^���Ƃ��Ĉ����B

	int damaging = 0;//�J��Ԃ��ɂ�茸�葱���郁�[�^�[��HP�l�B

	//int damagedHP = damaged->HP;//��_���[�W����HP���ꎞ�ۑ��B
	
	for (int i = 0; i < damageHP+5; i++) {
		if (i % 5 == 0) {
			board[damageX][damageY].creature = NULL;//4�̔{�����ƂɃ`�J�`�J�؂�ւ��B
		}
		if (i % 5 == 3) {
			board[damageX][damageY].creature = &substitute;
		}
		

		if (damaging < damageHP) {
			damaging += 1;
		}
		exhibitScreen(markX, markY, TRUE);
		DrawGraph(damageX * SQUARESIZE + 5, damageY * SQUARESIZE + 29, hHP, TRUE);
		DrawBox(damageX * SQUARESIZE + 16, damageY * SQUARESIZE + 31, damageX * SQUARESIZE + 16 + (substitute.HP - damaging) / 2, damageY * SQUARESIZE + 36, GetColor(45, 205, 50), TRUE);
		
		WaitTimer(30);

		if (substitute.HP - damaging < 0) {
			break;
		}
	}
	board[damageX][damageY].creature = damaged;
}











void exhibitStatus(int markX, int markY, int statusX, int statusY, bool attention) {
	exhibitScreen(markX, markY, attention);
	string Msg = "";

	if (statusX < FIELDSIZE && statusY < FIELDSIZE) {

		DrawBox(statusX * 48 + 40, statusY * 48 + 5, statusX * 48 + 200, statusY * 48 + 43, GetColor(225, 200, 0), TRUE);
		DrawBox(statusX * 48 + 40, statusY * 48 + 5, statusX * 48 + 200, statusY * 48 + 43, GetColor(125, 000, 0), FALSE);

		Msg = board[statusX][statusY].creature->name + "��HP:" + to_string(board[statusX][statusY].creature->HP) + "/" + to_string(board[statusX][statusY].creature->HP_Limit) + "\n�f�����l:" + to_string(board[statusX][statusY].creature->speed);

		DrawString(statusX * 48 + 42, statusY * 48 + 7, Msg.c_str(), GetColor(0, 10, 55));
	}
}







void exhibitRolling(int kickX, int kickY, int dx, int dy, int distance) {
	
	Creature* kicked = board[kickX + dx][kickY + dy].creature;//�R��ꂽ���̃|�C���^�����u����ɑ�����ێ��B
	int handleEgg = handle[board[kickX + dx][kickY + dy].creature->team][EGG][NW];
	board[kickX + dx][kickY + dy].creature = NULL;
	for (int i = 0; i < distance * SQUARESIZE/2; i=i++) {

		exhibitScreen(kickX, kickY, TRUE);
		DrawGraph((kickX + dx) * SQUARESIZE + (i*2 * dx), (kickY + dy) * SQUARESIZE + (i*2 * dy), handleEgg, TRUE);
		WaitTimer(10);
	}

	board[kickX + dx][kickY + dy].creature = kicked;//���̈ʒu�Ƀ|�C���^��߂��B
}






















Direction GETdirectionBYxy(int x, int y) {
	if (x == -1) {
		if (y == -1)return NW;
		if (y == 0)return WW;
		if (y == 1)return SW;
	}
	if (x == 0) {
		if (y == -1)return NN;
		if (y == 1)return SS;
	}
	if (x == 1) {
		if (y == -1)return NE;
		if (y == 0)return EE;
		if (y == 1)return SE;
	}
}

void GETxyBYdirection(int* x, int* y, Direction drctn) {
	switch (drctn) {
	case NW:
		*x = -1;
		*y = -1;
		break;
	case NN:
		*x = 0;
		*y = -1;
		break;
	case NE:
		*x = 1;
		*y = -1;
		break;
	case EE:
		*x = 1;
		*y = 0;
		break;
	case SE:
		*x = 1;
		*y = 1;
		break;
	case SS:
		*x = 0;
		*y = 1;
		break;
	case SW:
		*x = -1;
		*y = 1;
		break;
	case WW:
		*x = -1;
		*y = 0;
		break;
	}
}










//
//void RandomDirection(int* tmpx, int* tmpy) {//����8�����𒲂ׂ�ۂ̏��Ԃ������_���ɂ���B�W����z��̓���ւ��B
//
//	for (int i = 0; i < 8; i++) {//�W�������ׂ�B����Ȃ��switch�g����i==7�̏ꍇ�����������Ȃ��́H���u���C�N�������Ă��Ȃ���������B
//
//		switch (i) {
//		case 0:
//			*tmpx = -1;
//			*tmpy = -1;
//			break;
//		case 1:
//			*tmpx = 0;
//			*tmpy = -1;
//			break;
//		case 2:
//			*tmpx = 1;
//			*tmpy = -1;
//			break;
//		case 3:
//			*tmpx = 1;
//			*tmpy = 0;
//			break;
//		case 4:
//			*tmpx = 1;
//			*tmpy = 1;
//			break;
//		case 5:
//			*tmpx = 0;
//			*tmpy = 1;
//			break;
//		case 6:
//			*tmpx = -1;
//			*tmpy = 1;
//			break;
//		case 7:
//			*tmpx = -1;
//			*tmpy = 0;
//			break;
//		}
//	}