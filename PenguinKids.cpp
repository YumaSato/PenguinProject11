#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>

using namespace std;

PenguinKids::PenguinKids() {
}








void PenguinKids::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {//実質的なコンストラクタ。
	//未初期化のPenguinKids配列を作るためにはコンストラクタに何か書いてあるとダメらしいので、コンストラクタでやるべきことを別の関数にした。

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	name = "ペンギン";
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
	attackPower = 30 + GetRand(3);
	defensePower = 1;

	int random = GetRand(100) + 30;
	speed = ((parentSpeed -1)*(random - GetRand(20)) / random)-1;//素早さは世代を重ねるごとに低下する。減少量はランダム。
	//
	if (speed < 1) { speed = 1; }
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = TRUE;//ペンギンキッズが生まれた時点では、こいつは行動をスキップする（まだ動かない）
	score += 5;


	/*exhibitScreen();
	DrawString(800, 180, "ペンギンキッズのSetMobs実行。", GetColor(255, 200, 255));*/
	/*numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "のペンギンの素早さは、" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();*/


}





bool PenguinKids::selectAction() {

	if (skip == TRUE) {//skipする状態なら、即終了。
		skip = FALSE;//skip状態を解消。
		return FALSE;//行動しなかった判定にする。これがTRUEだと、こいつの行動について説明が表示されてしまう。
	}

	if (status == EGG) {//skipする状態なら、即終了。
		return FALSE;
	}

	HP += 12;
	if (HP > HP_Limit) {//自然治癒
		HP = HP_Limit;
	}


	int iX = x;
	int iY = y;
	int tmpx, tmpy;
	GETdirectionXY(&tmpx, &tmpy);
	//ix = ix + directionX;
	//iy = iy + directionY;
	iX = iX + tmpx;
	iY = iY + tmpy;
	if (status == ELDER || status == NORMAL) {
		if (iX >= 0 && iX < FIELDSIZE && iY >= 0 && iY < FIELDSIZE) {
			if (board[iX][iY].creature != NULL) {//向いている方向のマスに何か居たら
				if (board[iX][iY].creature->status == EGG && board[iX][iY].creature->team == team) {//同じチームの卵があれば
					if (specialMovement1(FIELDSIZE) == TRUE) {//優先行動として産卵。
						return TRUE;
					}
				}
			}
		}
	}




	if (attack(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
			quitGame = TRUE;
		}
		return TRUE;
	}
	if (specialMovement1(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
			quitGame = TRUE;
		}
		return TRUE;
	}
	if (specialMovement2(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
			quitGame = TRUE;
		}
		return TRUE;
	}
	return FALSE;
}





void PenguinKids::test() {
	string s;
	s = "";
	s = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "のtestメソッド実行";
	exhibitScreen(x, y, TRUE);
	DrawString(800, 300, s.c_str(), WHITE);
	WaitKey();
}



bool PenguinKids::attack(int size) {

	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;
	int tmpx;
	int tmpy;
	bool attackPriority = FALSE;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {//攻撃優先モードに当てはまるかを調べる。
		if (board[checkX][checkY].creature != NULL) {//目の前に生物がいたら
			if (board[checkX][checkY].creature->enemy == TRUE) {//そこにいるやつが敵ならば攻撃。
				damage(checkX, checkY);
				return TRUE;
			}
			if (status == NORMAL && (board[checkX][checkY].creature->status != EGG || board[checkX][checkY].creature->team != team)) {//目の前に別チームもしくは卵以外がいて、かつ卵を産みたい状態のとき
				attackPriority = TRUE;//索敵開始。
			}
		}
	}
	if (board[checkX][checkY].state == ROCK) {//攻撃優先モードに当てはまるかを調べる。当てはまった場合、向いている方向以外も索敵する。
		attackPriority = TRUE;//岩場を向いている場合。
	}
	if (status == ELDER || attackPriority == TRUE) {//出産という仕事が終わっている場合か、ノーマル状態でも目の前に何かいて卵を産めないとき

		int diCheck[8] = { 0,1,2,3,4,5,6,7 };//正面に敵いあればそれが優先的に孵化されるが、隣にいくつも卵がある場合、卵を孵化させる方向をランダムにする。
		for (int i = 0; i < 7; i++) {
			int r = GetRand(7 - i) + i;
			int tmp = diCheck[i];
			diCheck[i] = diCheck[r];
			diCheck[r] = tmp;
		}

		for (int i = 0; i < 8; i++) {//８方向調べる。これなんでswitch使うとi==7の場合しか発動しないの？←ブレイクを書いていなかったから。

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
			checkX = x + tmpx;
			checkY = y + tmpy;

			if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {

				if (board[checkX][checkY].creature != NULL) {//向いている方向のマスに何か居たら
					if (board[checkX][checkY].creature->enemy == TRUE) {//それが敵だと判定されたら

						SETdirection(tmpx, tmpy);//敵の方を向いて
						damage(checkX, checkY);//攻撃。
						return TRUE;
					}
				}
			}
		}
	}

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

		if (ix >= 0 && ix < size && iy >= 0 && iy < size && board[ix][iy].creature == NULL && board[ix][iy].state == VACANT) {//向いている方向のマスが空いていたら



			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, tmpx, tmpy, ix, iy, speed);


			mobs_PenguinKids[num_penguinKids] = penguinKids;
			board[ix][iy].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;
			status = ELDER;//老化する



			actionMsg = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "が産卵した！";

			//board[ix][iy].creature = &penguinKids;

			return TRUE;//成功。
		}
	}
	return FALSE;
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


	if (status == NORMAL or status == ELDER) {
		if (ix >= 0 && ix < size && iy >= 0 && iy < size) {

			if (board[ix][iy].creature != NULL) {//向いている方向のマスに何か居たら
				if (board[ix][iy].creature->status == EGG && board[ix][iy].creature->team == team) {

					incubate(ix, iy);
					actionMsg = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "が孵化させた！";
					return TRUE;
				}
			}
		}


		int diCheck[8] = { 0,1,2,3,4,5,6,7 };//正面に卵があればそれが優先的に孵化されるが、隣にいくつも卵がある場合、卵を孵化させる方向をランダムにする。
		for (int i = 0; i < 7; i++) {
			int r = GetRand(7 - i) + i;
			int tmp = diCheck[i];
			diCheck[i] = diCheck[r];
			diCheck[r] = tmp;
		}


		for (int i = 0; i < 8; i++) {//８方向調べる。これなんでswitch使うとi==7の場合しか発動しないの？←ブレイクを書いていなかったから。


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




				if (board[ix][iy].creature != NULL) {//向いている方向のマスに何か居たら
					if (board[ix][iy].creature->status == EGG && board[ix][iy].creature->team == team) {//それが卵であった場合

						SETdirection(tmpx, tmpy);
						incubate(ix, iy);
						actionMsg = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "が孵化させた！";
						return TRUE;
					}
				}

			}
		}

	}
	return FALSE;
}






