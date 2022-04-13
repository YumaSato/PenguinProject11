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
	attackPower = NULL;
	defensePower = NULL;
	speed = 500000 - GetRand(160);//素早さは世代を重ねるごとに低下する。減少量はランダム。
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = FALSE;//TRUEのとき、ペンギンキッズが生まれた時点では、こいつは行動をスキップする（まだ動かない）
	enemy = TRUE;//こいつは、敵。

	DrawString(800, 180, "闘牛のSetMobs実行。", GetColor(255, 200, 255));
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "の闘牛の素早さは、" + numSpeed;
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