#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//�v���g�^�C�v�錾
void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor(Team team, int num) : Character() {//�c��̃R���X�g���N�^
	this->status = EMPEROR;//�X�e�[�^�X���u�c��v���Ӗ�����4�ɕύX
	this->team = team;

	if (this->team == red) {//�ԃ`�[��(=1)�̍c��ł���ΐԍc���Ֆʏ㕔�ɃX�|�[��
		this->name = "�ԍc��";
		this->x = FIELDSIZE - 6;
		this->y = 6;
		//this->directionX = 0;
		//this->directionY = -1;
		SETdirection(0, -1);
		this->status = EMPEROR;
		this->HP = 100;
		this->HP_Limit = 100;
		this->stamina = 100;
		this->staminaLimit = 100;
		this->attackPower = 30;
		this->defensePower = 30;
		this->speed = 500001;
		this->staminaRecoverAbility = 5;
		this->num = num;


		//setCreature(num, x, y);

		board[x][y].creature = this;//�}�X�ڂɎ����̃|�C���^�����B

	}

	if (this->team == blue) {//�`�[��(=2)�̍c��ł���ΐc���Ֆʉ����ɃX�|�[��
		this->name = "�c��";
		this->x = 6;
		this->y = FIELDSIZE - 6;
		//this->directionX = 0;
		//this->directionY = 1;
		SETdirection(0, 1);
		this->status = EMPEROR;
		this->HP = 100;
		this->HP_Limit = 100;
		this->stamina = 100;
		this->staminaLimit = 100;
		this->attackPower = 30;
		this->defensePower = 30;
		this->speed = 500002;
		this->staminaRecoverAbility = 5;
		this->num = num;

		//setCreature(num, x, y);

		board[x][y].creature = this;
	}
}


bool Emperor::specialMovement1(int size) {//����Z�F�Y��
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
		if (board[checkX][checkY].creature == NULL && board[checkX][checkY].state == VACANT) {//�������}�X�̕������󂢂Ă�����C���X�^���X�������s
			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, drctnX, drctnY, checkX, checkY, speed);

			//kids.push_back(penguinKids);
			//board[checkX][checkY].creature = &kids.back();
			/*mobs_PenguinKids[mobNumber] = penguinKids;
			board[checkX][checkY].creature = &mobs_PenguinKids[mobNumber];
			mobNumber += 1;*/

			mobs_PenguinKids[num_penguinKids] = penguinKids;//���܂ꂽ�L�b�Y��z��ɓ����B
			board[checkX][checkY].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;



			stamina -= 5;
			exhibitScreen();
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	return FALSE;
}


bool Emperor::specialMovement2(int size) {//����Z�F�z��
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
		if (board[checkX][checkY].creature == NULL) {
			return FALSE;
		}
		if (board[checkX][checkY].creature->status == EGG) {//�������}�X�̕����ɗ�������Ώ��������s

			incubate(checkX, checkY);
			//board[checkX][checkY].creature->directionX = this->directionX;
			//board[checkX][checkY].creature->directionY = this->directionY;
			exhibitScreen();
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
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