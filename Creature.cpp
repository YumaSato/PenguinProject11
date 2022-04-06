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
	pass = FALSE;
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

void Creature::changeDirection() {
}

bool Creature::attack(int size) {
	return FALSE;
}

bool Creature::specialMovement1(int size){
	DrawString(800, 300, "Creature.specialMovement1���\�b�h���s", WHITE);
	WaitKey();
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

void Creature::DeleteCharacter() {
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