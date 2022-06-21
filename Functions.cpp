#include "DxLib.h"
#include <string>
#include <iostream>
#include "DxLib.h"
#include "consts.h"
#include "externs.h"
#include "MyClasses.h"
#include <vector>

using std::to_string;






void exhibitStatusMsg(Emperor* handledCharacters) {//��������L�����N�^�̃X�e�[�^�X����\������B

	string CharacterStatusMsg;

	string HP_Msg = "";
	string staminaMsg = "";
	int exhibitY = 600;
	for (int i = 0; i < CHARACTERNUM; i++) {

		DrawBox(830, 300 + i * 100, 1150, 385 + i * 100, GetColor(240, 230, 140), TRUE);

		DrawGraph(832, 305 + i * 100, handle[handledCharacters[i].team][handledCharacters[i].status][5], TRUE);


		string numHP;
		numHP = (to_string(handledCharacters[i].HP));
		string numHP_Limit;
		numHP_Limit = (to_string(handledCharacters[i].HP_Limit));
		string numLevel;
		numLevel = (to_string(handledCharacters[i].levelUp));
		string numExp;
		numExp = (to_string(handledCharacters[i].expPoint));
		string atta;
		atta = (to_string(handledCharacters[i].attackPower));
		string defe;
		defe = (to_string(handledCharacters[i].defensePower));
		string neededExp;
		neededExp = (to_string(handledCharacters[i].levelUp * 100 / 3 + 150));

		CharacterStatusMsg = handledCharacters[i].name + "      Lv." + numLevel + "\n ��� HP : " + numHP + " / " + numHP_Limit + "\n �U���́F" + atta + "   �h��́F" + defe + "\n �o���l�F" + numExp + " / " + neededExp;




		DrawString(880, 305 + i * 100, CharacterStatusMsg.c_str(), GetColor(20, 0, 0));



		exhibitY = exhibitY + 90;
	}

}





void exhibitScreen(int markX, int markY, bool attention, Grid** board, Emperor* handledCharacters) {//�y���M����`��i�X�e�[�^�X�ƌ�������y���M���̓K�؂ȉ摜�̃n���h������肵�i�[���Ă���`��j
	int h;//�n���h���i�[�p
	string turn = "";
	bool HPexhibitOrNot;
	ClearDrawScreen();//��x��ʂ�S����
	//DrawGraph(0, 0, HandleBoard, TRUE);

	if (attention == TRUE) {//���ڑΏۃL�����̃}�X�ɒ��ڗp�̉~��\�����邩�ۂ�
		DrawBox(markX * 48 + 2, markY * 48 + 2, markX * 48 + 46, markY * 48 + 46, GetColor(255, 200, 0), TRUE);
	}



	for (int ix = 0; ix < FIELDSIZE + 1; ix++) {
		for (int iy = 0; iy < FIELDSIZE + 1; iy++) {
			/*if (board[ix][ iy].state == ROCK) {
				DrawBox(ix * SQUARESIZE, iy * SQUARESIZE, ix * SQUARESIZE + 47, iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}
			if (board[ix][iy].state == CASTLE) {
				DrawGraph( ix * SQUARESIZE,  iy * SQUARESIZE, HandleCastle, TRUE);
			}*/

			/*if (board[GameBuf->exhibitX / 48 + ix][GameBuf->exhibitY / 48 + iy].state == ROCK) {
				DrawBox(GameBuf->exhibitX / 48 + ix * SQUARESIZE, GameBuf->exhibitY / 48 + iy * SQUARESIZE, GameBuf->exhibitX / 48 + ix * SQUARESIZE + 47, GameBuf->exhibitY / 48 + iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}
			if (board[ix][iy].state == CASTLE) {
				DrawGraph(GameBuf->exhibitX / 48 + ix * SQUARESIZE, GameBuf->exhibitY / 48 + iy * SQUARESIZE, HandleCastle, TRUE);
			}*/

			if (board[ix][ iy].state == ROCK) {
				DrawBox(-GameBuf->exhibitX + ix * SQUARESIZE, -GameBuf->exhibitY+ iy * SQUARESIZE, -GameBuf->exhibitX+ ix * SQUARESIZE + 47, -GameBuf->exhibitY + iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}
			if (board[ix][iy].state == CASTLE) {
				DrawGraph(-GameBuf->exhibitX  + ix * SQUARESIZE, -GameBuf->exhibitY  + iy * SQUARESIZE, HandleCastle, TRUE);
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
	DrawString(FIELDSIZE * SQUARESIZE + 5, 20, mainMsg.c_str(), WHITE);
	DrawString(FIELDSIZE * SQUARESIZE + 5, 170, actionMsg.c_str(), GetColor(255, 200, 255));

	turn = "���݂̃^�[��:" + std::to_string(turnNum) + "   ���݂̃X�R�A:" + std::to_string(score);
	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turn.c_str(), GetColor(255, 200, 255));
	actionMsg = "";

	exhibitStatusMsg(handledCharacters);

	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 80, std::to_string(GameBuf->exhibitX).c_str(), GetColor(255, 200, 255));
	DrawString(FIELDSIZE * SQUARESIZE + 100, FIELDSIZE * SQUARESIZE - 80, std::to_string(GameBuf->exhibitY).c_str(), GetColor(255, 200, 255));
}
















void exhibitDamage(int markX, int markY, int damageX, int damageY, bool attention, int damageHP, Grid** board, Emperor* handledCharacters) {

	Creature* damaged = board[damageX][damageY].creature;//��_���[�W�����ꎞ�ۑ��B
	board[damageX][damageY].creature = NULL;//��U���̏�ɃL���������Ȃ����Ƃɂ���B

	Creature substitute = *damaged;//��_���[�W���̐g��������B
	substitute.HP += damageHP;//�g����́A�̗͖��^���Ƃ��Ĉ����B

	int damaging = 0;//�J��Ԃ��ɂ�茸�葱���郁�[�^�[��HP�l�B

	//int damagedHP = damaged->HP;//��_���[�W����HP���ꎞ�ۑ��B

	for (int i = 0; i < damageHP + 5; i++) {
		if (i % 5 == 0) {
			board[damageX][damageY].creature = NULL;//4�̔{�����ƂɃ`�J�`�J�؂�ւ��B
		}
		if (i % 5 == 3) {
			board[damageX][damageY].creature = &substitute;
		}


		if (damaging < damageHP) {
			damaging += 1;
		}
		exhibitScreen(markX, markY, TRUE, board, handledCharacters);
		DrawGraph(damageX * SQUARESIZE + 5, damageY * SQUARESIZE + 29, hHP, TRUE);
		DrawBox(damageX * SQUARESIZE + 16, damageY * SQUARESIZE + 31, damageX * SQUARESIZE + 16 + (substitute.HP - damaging) / 2, damageY * SQUARESIZE + 36, GetColor(45, 205, 50), TRUE);

		WaitTimer(30);

		if (substitute.HP - damaging < 0) {
			break;
		}
	}
	board[damageX][damageY].creature = damaged;
}











void exhibitStatus(int markX, int markY, int statusX, int statusY, bool attention, int color, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
	exhibitScreen(markX, markY, attention, board, handledCharacters);
	string Msg = "";
	string Bulls = "";

	if (statusX < FIELDSIZE && statusY < FIELDSIZE) {



		if (markX == statusX && markY == statusY) {//�X�e�[�^�X�\���L�����Ƒ���\�L�����������������ꍇ�A�s���I���̕\�����s���B


			string Msg1 = "";
			string Msg2 = "";

			DrawBox(markX * 48 + 40, markY * 48 + 2, markX * 48 + 360, markY * 48 + 46, GetColor(225, 200, 0), TRUE);//�O���̃{�b�N�X
			DrawBox(markX * 48 + 39, markY * 48 + 1, markX * 48 + 361, markY * 48 + 47, GetColor(125, 0, 0), FALSE);//�O���̃{�b�N�X�̉�

			for (int iii = 0; iii < 6; iii++) {
				DrawBox(markX * 48 + 50 + iii * 51, markY * 48 + 24, markX * 48 + 85 + iii * 51, markY * 48 + 43, GetColor(50 + ((color + iii * 3) / 10), 220 + iii * 5 - (color / 3), 100), TRUE);//�I���{�b�N�X


			}

			Msg1 = board[markX][markY].creature->name + "��HP:" + std::to_string(board[markX][markY].creature->HP) + "/" + std::to_string(board[markX][markY].creature->HP_Limit) + "   �f�����l:" + std::to_string(board[markX][markY].creature->speed);
			Msg2 = " �����@�Y���@�z���@�U���@�����@�p�X";

			DrawString(markX * 48 + 42, markY * 48 + 5, Msg1.c_str(), GetColor(0, 10, 55));
			DrawString(markX * 48 + 42, markY * 48 + 26, Msg2.c_str(), GetColor(0, 10, 55));

			WaitTimer(10);

		}
		else {

			DrawBox(statusX * 48 + 40, statusY * 48 + 5, statusX * 48 + 300, statusY * 48 + 43, GetColor(225, 200, 0), TRUE);
			DrawBox(statusX * 48 + 40, statusY * 48 + 5, statusX * 48 + 300, statusY * 48 + 43, GetColor(125, 000, 0), FALSE);

			Msg = board[statusX][statusY].creature->name + "  HP:" + to_string(board[statusX][statusY].creature->HP) + "/" + to_string(board[statusX][statusY].creature->HP_Limit) + "�@ Lv." + to_string(board[statusX][statusY].creature->levelUp) + "\n�f����:" + to_string(board[statusX][statusY].creature->speed) + "  �U��:" + (to_string(board[statusX][statusY].creature->attackPower)) + "  �h��:" + to_string(board[statusX][statusY].creature->defensePower);

			DrawString(statusX * 48 + 42, statusY * 48 + 7, Msg.c_str(), GetColor(0, 10, 55));


		}




		////�ȉ��A���u�z�񂪃o�O���Ă���̂Œ���
		//DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 235, "mobs_PenguinKids", GetColor(255, 200, 255));
		//for (int i = 0; i < 12; i++) {
		//	Bulls = std::to_string(mobs_PenguinKids[i].num) + " X:" + std::to_string(mobs_PenguinKids[i].x) + " Y:" + std::to_string(mobs_PenguinKids[i].y);
		//	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 220 + i*13, Bulls.c_str(), GetColor(255, 200, 255));
		//	DrawString(FIELDSIZE * SQUARESIZE + 100, FIELDSIZE * SQUARESIZE - 220 + i * 13, mobs_PenguinKids[i].name.c_str(), GetColor(255, 200, 255));
		//}
		//DrawString(FIELDSIZE * SQUARESIZE + 200, FIELDSIZE * SQUARESIZE - 235, "mobs_Bull", GetColor(255, 200, 255));
		//for (int i = 0; i < 12; i++) {
		//	Bulls = std::to_string(mobs_Bull[i].num) + " X:" + std::to_string(mobs_Bull[i].x) + " Y:" + std::to_string(mobs_Bull[i].y);
		//	DrawString(FIELDSIZE * SQUARESIZE + 200, FIELDSIZE * SQUARESIZE - 220 + i * 13, Bulls.c_str(), GetColor(255, 200, 255));
		//	DrawString(FIELDSIZE * SQUARESIZE + 295, FIELDSIZE * SQUARESIZE - 220 + i * 13, mobs_Bull[i].name.c_str(), GetColor(255, 200, 255));
		//}


	}
}







void exhibitRolling(int kickX, int kickY, int dx, int dy, int distance, Grid** board, Emperor* handledCharacters) {

	Creature* kicked = board[kickX + dx][kickY + dy].creature;//�R��ꂽ���̃|�C���^�����u����ɑ�����ێ��B
	int handleEgg = handle[board[kickX + dx][kickY + dy].creature->team][EGG][NW];
	board[kickX + dx][kickY + dy].creature = NULL;
	for (int i = 0; i < distance * SQUARESIZE / 4; i = i++) {

		exhibitScreen(kickX, kickY, TRUE, board, handledCharacters);
		DrawGraph((kickX + dx) * SQUARESIZE + (i * 4 * dx), (kickY + dy) * SQUARESIZE + (i * 4 * dy), handleEgg, TRUE);
		//WaitTimer(2);
		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}

	board[kickX + dx][kickY + dy].creature = kicked;//���̈ʒu�Ƀ|�C���^��߂��B
}





void exhibitRule() {

	string rule1 = "�y���M�����{�b�g�o�g���E���[���u�b�N\n\n �c��y���M�����𓮂����āA������I\n �G�ɏ���󂳂ꂽ��Q�[���I�[�o�[�I\n\n�^�[���ɂ��āF\n  �Ֆʏ�̑S�ẴL�����N�^�́A�f�������ɍs�����邼�I";
	string rule2 = "�s���ɂ���: \n  ����:\n�@�@�c��y���M����3���܂ŕ�����B\n�@�Y���F\n�@�@�����Ă�������ɃN���[���y���M���̗����Y�ށB";
	string rule3 = "�@�z���F\n�@�@�����Ă�������ɂ��闑��z��������B\n�@�@�N���[���͎����Ɠ����F�̗������z��������B\n�@�@���܂ꂽ�q�͛z���������y���M���Ɠ��������������B";
	string rule4 = "\n�@�U���F\n�@�@�����Ă�������ɂ���L�����N�^�Ƀ_���[�W��^����B\n�@�R��F\n�@�@�����R��ƃy���M���ɂԂ���܂Ő^�������]����B\n�@�@�N���[���y���M�����R��ƁA�R�������Ɠ��������������B";
	string rule5 = "�N���[���y���M���ɂ���:\n  �N���[���͕����Ȃ��B�Y���ƍU���ƛz�����s���B\n�@�N���[���y���M���ɂ́A�u���E��ҁE�V�l�v��3�̏�Ԃ�����B\n�@�@��ҁF�����Y�ޑO�̏�ԁB�����Ă�������ɎY�����悤�Ƃ���B\n�@�@�V�l�F�����Y�ނƘV�l�ɂȂ�B\n�@�@�@�@�@���͂ɓG������΍U�����A��������Λz��������B\n\n\n\nEsc:���[�������";


	DrawBox(550, 30, 1150, 1150, GetColor(173, 255, 47), TRUE);
	DrawBox(550, 30, 1150, 1150, GetColor(130, 0, 0), FALSE);
	DrawString(560, 50, rule1.c_str(), GetColor(0, 40, 55));
	DrawString(560, 250, rule2.c_str(), GetColor(0, 40, 55));
	DrawString(560, 340, rule3.c_str(), GetColor(0, 40, 55));
	DrawString(560, 400, rule4.c_str(), GetColor(0, 40, 55));
	DrawString(560, 550, rule5.c_str(), GetColor(0, 40, 55));
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