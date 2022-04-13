#include <string>
#include "DxLib.h"
#include "MyClasses.h"

using std::string;

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);

Creature::Creature() {//�R���X�g���N�^�B�`�[���ƈʒu���󂯎��B
	memset(&this->team, NULL, sizeof(this->team));//team��status��int�ł͂Ȃ�enum�^�ł��邩��NULL�����ł��Ȃ��B
	memset(&this->status, NULL, sizeof(this->status));//������memset��team�̃T�C�Y���̎w��o�C�g����NULL�Ŗ��߂Ă�B
	memset(&this->directionX, NULL, sizeof(this->directionX));
	memset(&this->directionY, NULL, sizeof(this->directionY));
	memset(&this->x, NULL, sizeof(this->x));
	memset(&this->y, NULL, sizeof(this->y));
	memset(&this->HP, NULL, sizeof(this->HP));
	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
	memset(&this->stamina, NULL, sizeof(this->stamina));
	memset(&this->staminaLimit, NULL, sizeof(this->staminaLimit));
	memset(&this->attackPower, NULL, sizeof(this->attackPower));
	memset(&this->defensePower, NULL, sizeof(this->defensePower));
	memset(&this->speed, NULL, sizeof(this->speed));
	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
	memset(&this->num, NULL, sizeof(this->num));
	name = "Somebody";
	skip = FALSE;
	enemy = FALSE;
	//this->team = NULL;
	//this->status = NULL;
	//this->directionX = NULL;
	//this->directionY = NULL;
	//this->x = NULL;
	//this->y = NULL;
	//this->HP = NULL;
	//this->HP_Limit = NULL;
	//this->stamina = NULL;
	//this->staminaLimit = NULL;
	//this->attackPower = NULL;
	//this->defensePower = NULL;
	//this->speed = NULL;
	//this->staminaRecoverAbility = NULL;
	//this->num = NULL;
}


void Creature::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {
}

bool Creature::selectAction() {
	return TRUE;
}

bool Creature::walk(int size) {
	return FALSE;
}





bool Creature::kick(int size) {
	int cX = 0;
	int cY = 0;
	int drctnX, drctnY;
	string s;

	GETdirectionXY(&drctnX, &drctnY);
	cX = x + drctnX;
	cY = y + drctnY;

	if (cX > 0 && cX < size && cY > 0 && cY < size) {
		if (board[cX][cY].creature == NULL) {//�������}�X�̕����ɉ������Ȃ������珈�����I���B
			return FALSE;
		}

		if (status == EMPEROR){
			if (board[cX][cY].creature->status == NORMAL || board[cX][cY].creature->status == ELDER) {//�������}�X�̕����ɑ�l��������
				board[cX][cY].creature->SETdirection(directionX, directionY);//�_���[�W�͖����B���������ς���B
				/*board[cX][cY].creature->HP -= 5;
				if (board[cX][cY].creature->HP <= 0) {
					board[cX][cY].creature->DeleteCreature();
				}*/
				return TRUE;
			}
		}

		if (board[cX][cY].creature->status == EGG){
			exhibitScreen();
			DrawString(800, 180, "kick�J�n", WHITE);
			WaitKey();

			while (1) {
				cX = cX + drctnX;//�]��������̃}�X���ЂƂÂ��ׂ�B
				cY = cY + drctnY;

				s = "";
				s = "X:" + std::to_string(cX) + "Y:" + std::to_string(cY);
				exhibitScreen();
				DrawString(800, 570, s.c_str(), WHITE);
				WaitKey();

				if (cX < 0 || cX > size || cY < 0 || cY > size) {//�}�X�ڂ̒[�����܂Œ��ׂ���A����������B
					board[x + drctnX][y + drctnY].creature->DeleteCreature();
					board[x + drctnX][y + drctnY].creature = NULL;
					break;
				}

				if (board[cX][cY].creature != NULL) {//�]��������ɉ��������烋�[�v�����B

					if (board[cX][cY].creature->status == EMPEROR || board[cX][cY].creature->status == ELDER || board[cX][cY].creature->status == NORMAL) {//��l�y���M��������������

						board[x + drctnX][y + drctnY].creature->x = cX - drctnX;//���̋��ꏊ���瓮���y���M�����w�肵�A����XY��ύX�B
						board[x + drctnX][y + drctnY].creature->y = cY - drctnY;
						board[cX - drctnX][cY - drctnY].creature = board[x + drctnX][y + drctnY].creature;//�V�����܂��ɗ��A�h���X�����B
						board[x + drctnX][y + drctnY].creature = NULL;//���̈ʒu�̗��A�h���X���폜�B

						s = "";
						s = "NewPlace X:" + std::to_string(cX - drctnX) + "Y:" + std::to_string(cY - drctnY);
						exhibitScreen();
						DrawString(800, 570, s.c_str(), WHITE);
						WaitKey();
					}


					if (board[cX][cY].creature->status == EGG) {//��������������
						board[cX][cY].creature->DeleteCreature();
						board[cX][cY].creature = NULL;

						board[x + drctnX][y + drctnY].creature->DeleteCreature();
						board[x + drctnX][y + drctnY].creature = NULL;
					}


					if (board[cX][cY].creature->status == BULL) {
					}
					s = "�����Ԃ������I";
					exhibitScreen();
					DrawString(800, 570, s.c_str(), WHITE);
					WaitKey();

					break;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}






void Creature::changeDirection() {
}

bool Creature::attack(int size) {
	return FALSE;
}

bool Creature::specialMovement1(int size){
	/*DrawString(800, 300, "Creature.specialMovement1���\�b�h���s", WHITE);
	WaitKey();*/
	return FALSE;
}

bool Creature::specialMovement2(int size) {
	return FALSE;
}

int Creature::useItem(int size) {
	return 0;
};

void Creature::test() {
};

void Creature::killed() {
	this->HP = NULL;
	this->x = NULL;
	this->y = NULL;
}


void Creature::SETdirection(int xward, int yward) {
	this->directionX = xward;
	this->directionY = yward;
	this->compass = GETdirectionBYxy(xward, yward);
}

void Creature::SETdirection(Direction compass) {
	int tmp_x, tmp_y;
	GETxyBYdirection(&tmp_x, &tmp_y, compass);
	
	this->directionX = tmp_x;
	this->directionY = tmp_y;
	this->compass = compass;
}

void Creature::GETdirectionXY(int* xward, int* yward) {//�����̒l��������ϐ��̃A�h���X���󂯎��
	*xward = directionX;
	*yward = directionY;//���̃A�h���X�̒��g�ɕ��������B�^���I�ɒl��Ԃ���B
}

Direction Creature::GETdirection() {
	return compass;
}




void Creature::DeleteCreature() {
	memset(&this->team, NULL, sizeof(this->team));
	memset(&this->status, NULL, sizeof(this->status));
	memset(&this->directionX, NULL, sizeof(this->directionX));
	memset(&this->directionY, NULL, sizeof(this->directionY));
	memset(&this->x, NULL, sizeof(this->x));
	memset(&this->y, NULL, sizeof(this->y));
	memset(&this->HP, NULL, sizeof(this->HP));
	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
	memset(&this->stamina, NULL, sizeof(this->stamina));
	memset(&this->staminaLimit, NULL, sizeof(this->staminaLimit));
	memset(&this->attackPower, NULL, sizeof(this->attackPower));
	memset(&this->defensePower, NULL, sizeof(this->defensePower));
	memset(&this->speed, NULL, sizeof(this->speed));
	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
	memset(&this->num, NULL, sizeof(this->num));

	
	//team = NULL;
	//status = NULL;
	//directionX = NULL;
	//directionY = NULL;
	//x = NULL;
	//y = NULL;
	//HP = NULL;
	//HP_Limit = NULL;
	//stamina = NULL;
	//staminaLimit = NULL;
	//attackPower = NULL;
	//defensePower = NULL;
	//speed = NULL;
	//staminaRecoverAbility = NULL;
	//num = NULL;
}




void Creature::incubate(int checkX, int checkY) {//�w��n�_�ɐ���������O��B�z���̓��e�����s�B

	board[checkX][checkY].creature->status = NORMAL;
	board[checkX][checkY].creature->defensePower = 25 + GetRand(2);
	board[checkX][checkY].creature->SETdirection(GETdirection());
}



void Creature::damage(int checkX, int checkY) {//�w��n�_�ɐ���������O��B�U���̓��e�����s�B
	board[checkX][checkY].creature->HP = board[checkX][checkY].creature->HP - (30 + GetRand(2)) * attackPower / board[checkX][checkY].creature->defensePower;//�_���v
	if (board[checkX][checkY].creature->status == NORMAL || board[checkX][checkY].creature->status == ELDER) {//���肪�y���M���������ꍇ�A�������ς��B
		switch (GETdirection()) {
		case NW:
			board[checkX][checkY].creature->SETdirection(SE);
			break;
		case NN:
			board[checkX][checkY].creature->SETdirection(SS);
			break;
		case NE:
			board[checkX][checkY].creature->SETdirection(SW);
			break;
		case EE:
			board[checkX][checkY].creature->SETdirection(WW);
			break;
		case SE:
			board[checkX][checkY].creature->SETdirection(NW);
			break;
		case SS:
			board[checkX][checkY].creature->SETdirection(NN);
			break;
		case SW:
			board[checkX][checkY].creature->SETdirection(NE);
			break;
		case WW:
			board[checkX][checkY].creature->SETdirection(EE);
			break;
		}
	}
	if (board[checkX][checkY].creature->HP <= 0) {
		board[checkX][checkY].creature->DeleteCreature();
		board[checkX][checkY].creature = NULL;
	}
}