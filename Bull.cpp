#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>

using namespace std;

Bull::Bull() {
}

void Bull::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {//�����I�ȃR���X�g���N�^�B
	//����������Bull�z�����邽�߂ɂ̓R���X�g���N�^�ɉ��������Ă���ƃ_���炵���̂ŁA�R���X�g���N�^�ł��ׂ����Ƃ�ʂ̊֐��ɂ����B

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	team = ParentTeam;
	status = BULL;//���ł���ӁB
	//directionX = DirectionX;
	//directionY = DirectionY;
	SETdirection(DirectionX, DirectionY);
	x = ix;
	y = iy;
	HP = 50;
	HP_Limit = 50;
	stamina = NULL;
	staminaLimit = NULL;
	attackPower = NULL;
	defensePower = NULL;
	speed = 500000 - GetRand(160);//�f�����͐�����d�˂邲�Ƃɒቺ����B�����ʂ̓����_���B
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = FALSE;//TRUE�̂Ƃ��A�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j
	enemy = TRUE;//�����́A�G�B

	DrawString(800, 180, "������SetMobs���s�B", GetColor(255, 200, 255));
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "�̓����̑f�����́A" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();
}



bool Bull::selectAction() {
	return TRUE;
}

void Bull::test() {
}

bool Bull::specialMovement1(int size) {
	return TRUE;
}

bool Bull::specialMovement2(int size) {
	return TRUE;
}

bool Bull::attack(int size) {
	return TRUE;
}