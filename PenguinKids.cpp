#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>

using namespace std;

PenguinKids::PenguinKids() {
	}








void PenguinKids::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed){//�����I�ȃR���X�g���N�^�B
	//����������PenguinKids�z�����邽�߂ɂ̓R���X�g���N�^�ɉ��������Ă���ƃ_���炵���̂ŁA�R���X�g���N�^�ł��ׂ����Ƃ�ʂ̊֐��ɂ����B

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	team = ParentTeam;
	status = EGG;//���ł���ӁB
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
	speed = parentSpeed - 32 ;//�f�����͐�����d�˂邲�Ƃɒቺ����B�����ʂ̓����_���B
	//- GetRand(32) *2
	if (speed < 1) { speed = 1;}
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = TRUE;//�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j

	DrawString(800, 180, "�y���M���L�b�Y��SetMobs���s�B", GetColor(255, 200, 255));
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "�̃y���M���̑f�����́A" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();

	
}





bool PenguinKids::selectAction() {


	if (skip == TRUE) {//skip�����ԂȂ�A���I���B
		return TRUE;
	}

	if (specialMovement1(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	if (specialMovement2(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	attack(FIELDSIZE);
	return TRUE;
}





void PenguinKids::test() {
	exhibitScreen();
	DrawString(800, 300, "PenguinKids.test���\�b�h���s", WHITE);
	WaitKey();
}

bool PenguinKids::attack(int size) {
	return FALSE;
}

bool PenguinKids::specialMovement1(int size) {//�Y��
	if (status == NORMAL) {
		//exhibitScreen();
		//DrawString(800, 300, "PenguinKids.specialMovement1���\�b�h���s", WHITE);
		//WaitKey();
		int ix = x;
		int iy = y;
		int tmpx, tmpy;
		GETdirectionXY(&tmpx, &tmpy);
		//ix = ix + directionX;
		//iy = iy + directionY;
		ix = ix + tmpx;
		iy = iy + tmpy;

		if (ix >= 0 && ix < size && iy >= 0 && iy < size && board[ix][iy].creature == NULL) {//�����Ă�������̃}�X���󂢂Ă�����

			

			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, tmpx, tmpy, ix, iy, speed);


			mobs_PenguinKids[num_penguinKids] = penguinKids;
			board[ix][iy].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;
			status = ELDER;//�V������

			exhibitScreen();
			DrawString(800, 180, "�Y������", WHITE);
			WaitKey();

			//board[ix][iy].creature = &penguinKids;

			return TRUE;//�����B
		}
		return FALSE;
	}
}




bool PenguinKids::specialMovement2(int size) {
	if (status == NORMAL or status == ELDER) {

		int ix = x;
		int iy = y;
		int tmpx, tmpy;
		GETdirectionXY(&tmpx, &tmpy);
		//ix = ix + directionX;
		//iy = iy + directionY;
		ix = ix + tmpx;
		iy = iy + tmpy;

		if (ix >= 0 && ix < size && iy >= 0 && iy < size) {

			if (board[ix][iy].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
				if (board[ix][iy].creature->status == EGG) {
					board[ix][iy].creature->status = NORMAL;

					exhibitScreen();
					DrawString(800, 300, "PenguinKids.specialMovement2���\�b�h���s", WHITE);
					WaitKey();
					return TRUE;
				}
			}
		}
		return FALSE;
	}

}
