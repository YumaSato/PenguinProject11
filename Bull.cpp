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

	name = "����";
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
	attackPower = 38;
	defensePower = 100;
	speed = 500000 - GetRand(260);//�f�����̓����_���B
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = FALSE;//TRUE�̂Ƃ��A�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j
	enemy = TRUE;//�����́A�G�B



	exhibitScreen();
	DrawString(800, 180, "������SetMobs���s�B", GetColor(255, 200, 255));
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "�̓����̑f�����́A" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();
}



bool Bull::selectAction() {

	if (skip == TRUE) {//skip�����ԂȂ�A���I���B
		skip = FALSE;
		return TRUE;
	}

	HP += 2;
	if (HP > HP_Limit) {//���R����
		HP = HP_Limit;
	}

	if (walk(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	if (attack(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	return FALSE;
}


void Bull::test() {
}


bool Bull::walk(int size) {
	int ix;
	int iy;
	int dx;
	int dy;
	GETdirectionXY(&dx, &dy);
	ix = x + dx;
	iy = y + dy;

	if (ix >= 0 && ix < size && iy >= 0 && iy < size) {//�}�X���Ֆʈȓ��Ȃ�
		if (board[ix][iy].creature == NULL) {//�}�X���󔒂Ȃ�

			board[ix][iy].creature = this;
			board[x][y].creature = NULL;

			x = ix;
			y = iy;
			return TRUE;
		}
	}
	return FALSE;
}


bool Bull::specialMovement1(int size) {
	return TRUE;
}

bool Bull::specialMovement2(int size) {
	return TRUE;
}

bool Bull::attack(int size) {
	int ix;
	int iy;
	int dx;
	int dy;

	GETdirectionXY(&dx, &dy);
	ix = x + dx;
	iy = y + dy;
	if (ix >= 0 && ix < size && iy >= 0 && iy < size) {//�}�X���Ֆʈȓ��Ȃ�
		if (board[ix][iy].creature != NULL) {//�}�X���󔒂łȂ��A�܂艽������ꍇ
			if (board[ix][iy].creature->enemy == TRUE) {//�ł��G�����m��������
				return FALSE;
			}
			if (board[ix][iy].creature->enemy == FALSE) {//NULL����Ȃ��ă��{�b�g�ǂ���������U��
				damage(ix, iy);

			}
		}
	}
	return FALSE;
}