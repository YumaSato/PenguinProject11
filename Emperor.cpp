#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"

//プロトタイプ宣言
void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor(Team team, int num) : Character() {//皇帝のコンストラクタ
	this->status = EMPEROR;//ステータスを「皇帝」を意味する4に変更
	this->team = team;

	if (this->team == red) {//赤チーム(=1)の皇帝であれば赤皇帝を盤面上部にスポーン
		this->name = "赤皇帝";
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

		board[x][y].creature = this;//マス目に自分のポインタを代入。

	}

	if (this->team == blue) {//青チーム(=2)の皇帝であれば青皇帝を盤面下部にスポーン
		this->name = "青皇帝";
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


bool Emperor::specialMovement1(int size) {//特殊技：産卵
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
		if (board[checkX][checkY].creature == NULL) {//押したマスの方向が空いていたらインスタンス化を実行
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


bool Emperor::specialMovement2(int size) {//特殊技：孵化
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
		if (board[checkX][checkY].creature->status == EGG) {//押したマスの方向に卵があれば処理を実行
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
