#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>

using namespace std;

PenguinKids::PenguinKids() {
	}








void PenguinKids::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed){//実質的なコンストラクタ。
	//未初期化のPenguinKids配列を作るためにはコンストラクタに何か書いてあるとダメらしいので、コンストラクタでやるべきことを別の関数にした。

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	team = ParentTeam;
	status = EGG;//卵である意。
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
	speed = parentSpeed - 32 ;//素早さは世代を重ねるごとに低下する。減少量はランダム。
	//- GetRand(32) *2
	if (speed < 1) { speed = 1;}
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = TRUE;//ペンギンキッズが生まれた時点では、こいつは行動をスキップする（まだ動かない）

	DrawString(800, 180, "ペンギンキッズのSetMobs実行。", GetColor(255, 200, 255));
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "のペンギンの素早さは、" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();

	
}





bool PenguinKids::selectAction() {


	if (skip == TRUE) {//skipする状態なら、即終了。
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
	DrawString(800, 300, "PenguinKids.testメソッド実行", WHITE);
	WaitKey();
}

bool PenguinKids::attack(int size) {
	return FALSE;
}

bool PenguinKids::specialMovement1(int size) {//産卵
	if (status == NORMAL) {
		//exhibitScreen();
		//DrawString(800, 300, "PenguinKids.specialMovement1メソッド実行", WHITE);
		//WaitKey();
		int ix = x;
		int iy = y;
		int tmpx, tmpy;
		GETdirectionXY(&tmpx, &tmpy);
		//ix = ix + directionX;
		//iy = iy + directionY;
		ix = ix + tmpx;
		iy = iy + tmpy;

		if (ix >= 0 && ix < size && iy >= 0 && iy < size && board[ix][iy].creature == NULL) {//向いている方向のマスが空いていたら

			

			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, tmpx, tmpy, ix, iy, speed);


			mobs_PenguinKids[num_penguinKids] = penguinKids;
			board[ix][iy].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;
			status = ELDER;//老化する

			exhibitScreen();
			DrawString(800, 180, "産卵完了", WHITE);
			WaitKey();

			//board[ix][iy].creature = &penguinKids;

			return TRUE;//成功。
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

			if (board[ix][iy].creature != NULL) {//向いている方向のマスに何か居たら
				if (board[ix][iy].creature->status == EGG) {
					board[ix][iy].creature->status = NORMAL;

					exhibitScreen();
					DrawString(800, 300, "PenguinKids.specialMovement2メソッド実行", WHITE);
					WaitKey();
					return TRUE;
				}
			}
		}
		return FALSE;
	}

}
