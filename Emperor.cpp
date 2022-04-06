#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"

//�v���g�^�C�v�錾
void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor(Team team, int num) : Character() {//�c��̃R���X�g���N�^
	this->status = EMPEROR;//�X�e�[�^�X���u�c��v���Ӗ�����4�ɕύX
	this->team = team;

	if (this->team == red) {//�ԃ`�[��(=1)�̍c��ł���ΐԍc���Ֆʏ㕔�ɃX�|�[��
		this->name = "�ԍc��";
		this->x = 6;
		this->y = 7;
		//this->directionX = 0;
		//this->directionY = -1;
		SETdirection(0, -1);
		this->status = EMPEROR;
		this->HP = 120;
		this->HP_Limit = 120;
		this->stamina = 100;
		this->staminaLimit = 100;
		this->attackPower = 50;
		this->defensePower = 50;
		this->speed = 500001;
		this->staminaRecoverAbility = 5;
		this->num = num;


		//setCreature(num, x, y);

		board[x][y].creature = this;//�}�X�ڂɎ����̃|�C���^�����B

	}

	if (this->team == blue) {//�`�[��(=2)�̍c��ł���ΐc���Ֆʉ����ɃX�|�[��
		this->name = "�c��";
		this->x = 6;
		this->y = 0;
		//this->directionX = 0;
		//this->directionY = 1;
		SETdirection(0, 1);
		this->status = EMPEROR;
		this->HP = 120;
		this->HP_Limit = 120;
		this->stamina = 100;
		this->staminaLimit = 100;
		this->attackPower = 50;
		this->defensePower = 50;
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
		if (board[checkX][checkY].creature == NULL) {//�������}�X�̕������󂢂Ă�����C���X�^���X�������s
			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, drctnX, drctnY, checkX, checkY, speed);
			
			//kids.push_back(penguinKids);
			//board[checkX][checkY].creature = &kids.back();

			
			mobs_PenguinKids[mobNumber] = penguinKids;
			board[checkX][checkY].creature = &mobs_PenguinKids[mobNumber];
			mobNumber += 1;
			
			
			
			

			stamina -= 5;
			exhibitScreen();
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
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
			return 1;
		}
		if (board[checkX][checkY].creature->status == EGG) {//�������}�X�̕����ɗ�������Ώ��������s
			board[checkX][checkY].creature->status = NORMAL;
			board[checkX][checkY].creature->SETdirection(this->GETdirection());
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
