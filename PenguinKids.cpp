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
	speed = parentSpeed - 32 - GetRand(16) * 2;//�f�����͐�����d�˂邲�Ƃɒቺ����B�����ʂ̓����_���B
	//
	if (speed < 1) { speed = 1;}
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = TRUE;//�y���M���L�b�Y�����܂ꂽ���_�ł́A�����͍s�����X�L�b�v����i�܂������Ȃ��j

	exhibitScreen();
	DrawString(800, 180, "�y���M���L�b�Y��SetMobs���s�B", GetColor(255, 200, 255));
	/*numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "�̃y���M���̑f�����́A" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();*/

	
}





bool PenguinKids::selectAction() {


	if (skip == TRUE) {//skip�����ԂȂ�A���I���B
		skip = FALSE;
		return TRUE;
	}

	HP += 20;
	if (HP < HP_Limit) {//���R����
		HP = HP_Limit;
	}

	if (specialMovement1(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	if (specialMovement2(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	if (attack(FIELDSIZE) == TRUE) {
		return TRUE;
	}
	return FALSE;
}





void PenguinKids::test() {
	string s;
	s = "";
	s = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "��test���\�b�h���s";
	exhibitScreen();
	DrawString(800, 300, s.c_str(), WHITE);
	WaitKey();
}

bool PenguinKids::attack(int size) {
	return FALSE;
}

bool PenguinKids::specialMovement1(int size) {//�Y��
	if (status == NORMAL) {
		string s;
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

			
			s = "";
			s = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "���Y�������I";
			exhibitScreen();
			DrawString(800, 300, s.c_str(), WHITE);
			WaitKey();

			//board[ix][iy].creature = &penguinKids;

			return TRUE;//�����B
		}
		return FALSE;
	}
}




bool PenguinKids::specialMovement2(int size) {

	string s = "";
	string allS = "";
	int ix = x;
	int iy = y;
	int tmpx, tmpy;
	GETdirectionXY(&tmpx, &tmpy);
	//ix = ix + directionX;
	//iy = iy + directionY;
	ix = ix + tmpx;
	iy = iy + tmpy;


	int diCheck[8] = {0,1,2,3,4,5,6,7};//�ׂɂ�������������ꍇ�A����z������������������_���ɂ���B
	for (int i = 0 ; i < 7; i++) {
		int r = GetRand(7-i)+i;
		int tmp = diCheck[i];
		diCheck[i] = diCheck[r];
		diCheck[r] = tmp;
	}
	
	/*s = "";
	for (int i = 0; i < 8; i++) {
		s += to_string(diCheck[i]);
	}
	exhibitScreen();
	DrawString(800, 570, s.c_str(), WHITE);
	WaitKey();*/



	if (status == NORMAL or status == ELDER) {
		if (ix >= 0 && ix < size && iy >= 0 && iy < size) {

			if (board[ix][iy].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
				if (board[ix][iy].creature->status == EGG && board[ix][iy].creature->team == team) {
					board[ix][iy].creature->status = NORMAL;
					board[ix][iy].creature->SETdirection(this->GETdirection());

					exhibitScreen();
					DrawString(800, 300, "PenguinKids.specialMovement2���\�b�h���s", WHITE);
					WaitKey();
					return TRUE;
				}
			}
		}

		

		for (int i = 0; i < 8; i++) {//�W�������ׂ�B����Ȃ��switch�g����i==7�̏ꍇ�����������Ȃ��́H���u���C�N�������Ă��Ȃ���������B


			switch (diCheck[i]) {
			case 0:
				tmpx = -1;
				tmpy = -1;
				break;
			case 1:
				tmpx = 0;
				tmpy = -1;
				break;
			case 2:
				tmpx = 1;
				tmpy = -1;
				break;
			case 3:
				tmpx = 1;
				tmpy = 0;
				break;
			case 4:
				tmpx = 1;
				tmpy = 1;
				break;
			case 5:
				tmpx = 0;
				tmpy = 1;
				break;
			case 6:
				tmpx = -1;
				tmpy = 1;
				break;
			case 7:
				tmpx = -1;
				tmpy = 0;
				break;
			}

			ix = x + tmpx;
			iy = y + tmpy;



			/*s = "ix" + std::to_string(ix) + "iy" + std::to_string(iy) + " tmpx" + std::to_string(tmpx) + " tmpy" + std::to_string(tmpy);
			exhibitScreen();
			DrawString(800, 570, s.c_str(), WHITE);
			WaitKey();*/


			if (ix >= 0 && ix < size && iy >= 0 && iy < size) {




				if (board[ix][iy].creature != NULL) {//�����Ă�������̃}�X�ɉ���������
					if (board[ix][iy].creature->status == EGG && board[ix][iy].creature->team == team) {//���ꂪ���ł������ꍇ
						SETdirection(tmpx, tmpy);//���̕����������B
						board[ix][iy].creature->status = NORMAL;//�z��������B
						board[ix][iy].creature->SETdirection(this->GETdirection());//�e�Ɠ�������������������B

						exhibitScreen();
						DrawString(800, 300, "PenguinKids.specialMovement2���\�b�h���s", WHITE);
						WaitKey();
						return TRUE;
					}
				}

			}
		}



		return FALSE;
	}

}






