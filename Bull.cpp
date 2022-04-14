#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>

using namespace std;

Bull::Bull() {
}

void Bull::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {//実質的なコンストラクタ。
	//未初期化のBull配列を作るためにはコンストラクタに何か書いてあるとダメらしいので、コンストラクタでやるべきことを別の関数にした。

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	name = "闘牛";
	team = ParentTeam;
	status = BULL;//卵である意。
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
	speed = 500000 - GetRand(260);//素早さはランダム。
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = FALSE;//TRUEのとき、ペンギンキッズが生まれた時点では、こいつは行動をスキップする（まだ動かない）
	enemy = TRUE;//こいつは、敵。



	exhibitScreen();
	DrawString(800, 180, "闘牛のSetMobs実行。", GetColor(255, 200, 255));
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "の闘牛の素早さは、" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();
}



bool Bull::selectAction() {

	if (skip == TRUE) {//skipする状態なら、即終了。
		skip = FALSE;
		return TRUE;
	}

	HP += 2;
	if (HP > HP_Limit) {//自然治癒
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

	if (ix >= 0 && ix < size && iy >= 0 && iy < size) {//マスが盤面以内なら
		if (board[ix][iy].creature == NULL) {//マスが空白なら

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
	if (ix >= 0 && ix < size && iy >= 0 && iy < size) {//マスが盤面以内なら
		if (board[ix][iy].creature != NULL) {//マスが空白でない、つまり何か居る場合
			if (board[ix][iy].creature->enemy == TRUE) {//でも敵側同士だったら
				return FALSE;
			}
			if (board[ix][iy].creature->enemy == FALSE) {//NULLじゃなくてロボットどもだったら攻撃
				damage(ix, iy);

			}
		}
	}
	return FALSE;
}