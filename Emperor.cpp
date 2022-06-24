#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//�v���g�^�C�v�錾
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor() {//�c��̃R���X�g���N�^

}


void Emperor::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, Grid** board, Emperor* handledCharacters) {
	this->status = EMPEROR;//�X�e�[�^�X���u�c��v���Ӗ�����4�ɕύX
	this->team = ParentTeam;

	giveExpPoint = 600;

	if (ParentTeam == red) {//�ԃ`�[��(=1)�̍c��ł���ΐԍc���Ֆʏ㕔�ɃX�|�[��
		this->name = "�ԍc��";
		this->x = GameBuf->castleX - 1;
		this->y = GameBuf->castleY - 1;
		//this->directionX = 0;
		//this->directionY = -1;
		SETdirection(0, -1);
		this->status = EMPEROR;
		this->HP = 50;
		this->HP_Limit = 50;
		this->levelUp = 1;
		this->expPoint = 0;
		this->attackPower = 20;
		this->defensePower = 35;
		this->speed = 1001;
		this->staminaRecoverAbility = 10;
		this->num = 0;


		//setCreature(num, x, y);



	}

	if (ParentTeam == blue) {//�`�[��(=2)�̍c��ł���ΐc���Ֆʉ����ɃX�|�[��
		this->name = "�c��";
		this->x = GameBuf->castleX + 1;
		this->y = GameBuf->castleY + 1;
		//this->directionX = 0;
		//this->directionY = 1;
		SETdirection(0, 1);
		this->status = EMPEROR;
		this->HP = 50;
		this->HP_Limit = 50;
		this->levelUp = 1;
		this->expPoint = 0;
		this->attackPower = 20;
		this->defensePower = 35;
		this->speed = 1000;
		this->staminaRecoverAbility = 5;
		this->num = 1;

		//setCreature(num, x, y);


	}

}





bool Emperor::specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {//����Z�F�Y��
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < GameBuf->sizeX && checkY >= 0 && checkY < GameBuf->sizeY) {
		if (board[checkX][checkY].creature == NULL && board[checkX][checkY].state == VACANT) {//�������}�X�̕������󂢂Ă�����C���X�^���X�������s
			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, drctnX, drctnY, checkX, checkY, levelUp, speed, board, handledCharacters);

			//kids.push_back(penguinKids);
			//board[checkX][checkY].creature = &kids.back();
			/*mobs_PenguinKids[mobNumber] = penguinKids;
			board[checkX][checkY].creature = &mobs_PenguinKids[mobNumber];
			mobNumber += 1;*/

			mobs_PenguinKids[num_penguinKids] = penguinKids;//���܂ꂽ�L�b�Y��z��ɓ����B
			board[checkX][checkY].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;




			exhibitScreen(x, y, TRUE, board, handledCharacters);
			return TRUE;
		}
		else {

			return FALSE;
		}
	}
	return FALSE;
}


bool Emperor::specialMovement2( Grid** board, Emperor* handledCharacters) {//����Z�F�z��
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < GameBuf->sizeX && checkY >= 0 && checkY < GameBuf->sizeY) {
		if (board[checkX][checkY].creature == NULL) {
			return FALSE;
		}
		if (board[checkX][checkY].creature->status == EGG) {//�������}�X�̕����ɗ�������Ώ��������s

			incubate(checkX, checkY, board, handledCharacters);
			//board[checkX][checkY].creature->directionX = this->directionX;
			//board[checkX][checkY].creature->directionY = this->directionY;
			exhibitScreen(x, y, TRUE, board, handledCharacters);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

bool Emperor::kick(Grid** board, Emperor* handledCharacters) {
	int cX = 0;
	int cY = 0;
	int drctnX, drctnY;
	string s;

	GETdirectionXY(&drctnX, &drctnY);
	cX = x + drctnX;
	cY = y + drctnY;

	if (cX > 0 && cX < GameBuf->sizeX && cY > 0 && cY < GameBuf->sizeY) {
		if (board[cX][cY].creature == NULL) {//�������}�X�̕����ɉ������Ȃ������珈�����I���B
			return FALSE;
		}

		if (status == EMPEROR) {
			if (board[cX][cY].creature->status == NORMAL || board[cX][cY].creature->status == ELDER) {//�������}�X�̕����ɑ�l��������
				board[cX][cY].creature->SETdirection(drctnX, drctnY);//�_���[�W�͖����B���������ς���B
				/*board[cX][cY].creature->HP -= 5;
				if (board[cX][cY].creature->HP <= 0) {
					board[cX][cY].creature->DeleteCreature();
				}*/
				return TRUE;
			}
			if (board[cX][cY].creature->status == EGG) {
				//exhibitScreen(x, y, TRUE);
				//DrawString(800, 180, "kick�J�n", WHITE);
				//WaitKey();
				int i = 0;
				while (1) {


					cX = cX + drctnX;//�]��������̃}�X���ЂƂÂ��ׂ�B
					cY = cY + drctnY;

					/*s = "";
					s = "X:" + std::to_string(cX) + "Y:" + std::to_string(cY);
					exhibitScreen(x, y, TRUE);
					DrawString(800, 570, s.c_str(), WHITE);
					WaitKey();*/

					if (cX < 0 || cX >= GameBuf->sizeX || cY < 0 || cY >= GameBuf->sizeY || (cX == GameBuf->castleX && cY == GameBuf->castleY)) {//�}�X�ڂ̒[�����܂Œ��ׂ���A����������B

						exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

						board[x + drctnX][y + drctnY].creature->DeleteCreature();
						board[x + drctnX][y + drctnY].creature = NULL;
						break;
					}

					if (board[cX][cY].creature != NULL) {//�]��������ɉ��������烋�[�v�����B

						if (board[cX][cY].creature->status == EMPEROR || board[cX][cY].creature->status == ELDER || board[cX][cY].creature->status == NORMAL) {//��l�y���M��������������

							exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

							board[x + drctnX][y + drctnY].creature->x = cX - drctnX;//���̋��ꏊ���瓮���y���M�����w�肵�A����XY��ύX�B
							board[x + drctnX][y + drctnY].creature->y = cY - drctnY;
							board[cX - drctnX][cY - drctnY].creature = board[x + drctnX][y + drctnY].creature;//�V�����܂��ɗ��A�h���X�����B
							board[x + drctnX][y + drctnY].creature = NULL;//���̈ʒu�̗��A�h���X���폜�B

						/*	s = "";
							s = "NewPlace X:" + std::to_string(cX - drctnX) + "Y:" + std::to_string(cY - drctnY);
							exhibitScreen(x, y, TRUE);
							DrawString(800, 570, s.c_str(), WHITE);
							WaitKey();*/
						}


						else if (board[cX][cY].creature->status == EGG) {//��������������

							exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

							board[cX][cY].creature->DeleteCreature();
							board[cX][cY].creature = NULL;

							board[x + drctnX][y + drctnY].creature->DeleteCreature();
							board[x + drctnX][y + drctnY].creature = NULL;
						}


						else if (board[cX][cY].creature->status == BULL) {//���̌x���͂ǂ��������ƁH�H

							exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);
							board[x + drctnX][y + drctnY].creature->DeleteCreature();
							board[x + drctnX][y + drctnY].creature = NULL;
						}
						/*s = "�����Ԃ������I";
						exhibitScreen(x, y, TRUE);
						DrawString(800, 570, s.c_str(), WHITE);
						WaitKey();*/

						break;


					}
					i++;
				}
				return TRUE;
			}
		}
	}
	return FALSE;

}




int Emperor::GetExpPoint(int expP) {
	expPoint += expP;
	int surplus_expP;

	if (expPoint >= levelUp * 100 / 3 + 150) {//���x���A�b�v�K�v���̌o���l�𓾂���A���x���A�b�v

		//expPoint = expPoint - (levelUp * 100 / 6 + 100);//���x���A�b�v�B�����ɗ]�����o���l�͎��̃��x���p�ɒ��߂���B


		surplus_expP = expPoint - (levelUp * 100 / 3 + 150);//����̃��x���A�b�v�ŗ]�����o���l
		levelUp += 1;
		attackPower += 1 + GetRand(1);
		defensePower += 2 + GetRand(2);
		expPoint = 0;
		GetExpPoint(surplus_expP);

		return levelUp;//�オ�������x����Ԃ��B
	}
	return 0;
}






//
//bool Emperor::kick(int size) {
//	int checkX = 0;
//	int checkY = 0;
//	int drctnX, drctnY;
//	string s;
//
//	GETdirectionXY(&drctnX, &drctnY);
//	checkX = x + drctnX;
//	checkY = y + drctnY;
//
//	if (checkX > 0 && checkX < size && checkY > 0 && checkY < size) {
//		if (board[checkX][checkY].creature == NULL) {//�������}�X�̕����ɉ������Ȃ������珈�����I���B
//			return FALSE;
//		}
//
//		if (board[checkX][checkY].creature->status != EGG) {//�������}�X�̕����ɗ��ȊO������Ώ������I���B
//			return FALSE;
//		}else{
//
//			while (1) {
//				exhibitScreen();
//				DrawString(800, 180, "kick�J�n", WHITE);
//				WaitKey();
//
//
//
//				checkX = checkX + drctnX;//�]��������̃}�X���ЂƂÂ��ׂ�B
//				checkY = checkY + drctnY;
//
//
//				s = "";
//				s = "X:" + std::to_string(checkX) + "Y:" + std::to_string(checkY);
//				DrawString(800, 570, s.c_str(), WHITE);
//				WaitKey();
//
//
//
//				if (checkX <= 0 || checkX > size || checkY <= 0 || checkY > size) {//�}�X�ڂ̒[�����܂Œ��ׂ���A����������B
//					board[x + drctnX][y + drctnY].creature->killed();
//					board[x + drctnX][y + drctnY].creature = NULL;
//					break;
//				}
//
//
//				
//
//
//
//				if (board[checkX][checkY].creature != NULL) {//�]��������ɉ��������烋�[�v�����B
//
//					if (board[checkX][checkY].creature->status == NORMAL || ELDER || EMPEROR) {//��l�y���M��������������
//
//						board[x + drctnX][y + drctnY].creature->x = checkX - drctnX;
//						board[x + drctnX][y + drctnY].creature->x = checkY - drctnY;
//
//						s = "";
//						s = "X:" + std::to_string(checkX - drctnX) + "Y:" + std::to_string(checkY - drctnY);
//						DrawString(800, 570, s.c_str(), WHITE);
//						WaitKey();
//
//
//						board[checkX - drctnX][checkY - drctnY].creature = board[x + drctnX][y + drctnY].creature;//�V�����܂��ɗ��A�h���X�����B
//						board[x + drctnX][y + drctnY].creature = NULL;//���̈ʒu�̗��A�h���X���폜�B
//					}
//
//
//
//					if (board[checkX][checkY].creature->status == EGG) {//��������������
//						board[checkX][checkY].creature->killed();
//						board[checkX][checkY].creature = NULL;
//
//						board[x + drctnX][y + drctnY].creature->killed();
//						board[x + drctnX][y + drctnY].creature = NULL;
//					}
//
//
//
//
//					if (board[checkX][checkY].creature->status == BULL) {
//					}
//
//
//					break;
//				}
//
//
//			}
//		}
//	}
//	return TRUE;
//}