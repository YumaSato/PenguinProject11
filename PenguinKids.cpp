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
	speed = parentSpeed - 32 - GetRand(16) * 2;//素早さは世代を重ねるごとに低下する。減少量はランダム。
	//
	if (speed < 1) { speed = 1;}
	staminaRecoverAbility = NULL;
	num = mobNumber;
	skip = TRUE;//ペンギンキッズが生まれた時点では、こいつは行動をスキップする（まだ動かない）

	exhibitScreen();
	DrawString(800, 180, "ペンギンキッズのSetMobs実行。", GetColor(255, 200, 255));
	/*numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "のペンギンの素早さは、" + numSpeed;
	DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
	WaitKey();*/

	
}





bool PenguinKids::selectAction() {


	if (skip == TRUE) {//skipする状態なら、即終了。
		skip = FALSE;
		return TRUE;
	}

	HP += 20;
	if (HP < HP_Limit) {//自然治癒
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
	s = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "のtestメソッド実行";
	exhibitScreen();
	DrawString(800, 300, s.c_str(), WHITE);
	WaitKey();
}

bool PenguinKids::attack(int size) {
	return FALSE;
}

bool PenguinKids::specialMovement1(int size) {//産卵
	if (status == NORMAL) {
		string s;
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

			
			s = "";
			s = "X:" + std::to_string(x) + "Y:" + std::to_string(y) + "が産卵した！";
			exhibitScreen();
			DrawString(800, 300, s.c_str(), WHITE);
			WaitKey();

			//board[ix][iy].creature = &penguinKids;

			return TRUE;//成功。
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


	int diCheck[8] = {0,1,2,3,4,5,6,7};//隣にいくつも卵がある場合、卵を孵化させる方向をランダムにする。
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

			if (board[ix][iy].creature != NULL) {//向いている方向のマスに何か居たら
				if (board[ix][iy].creature->status == EGG && board[ix][iy].creature->team == team) {
					board[ix][iy].creature->status = NORMAL;
					board[ix][iy].creature->SETdirection(this->GETdirection());

					exhibitScreen();
					DrawString(800, 300, "PenguinKids.specialMovement2メソッド実行", WHITE);
					WaitKey();
					return TRUE;
				}
			}
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
						SETdirection(tmpx, tmpy);//その方向を向く。
						board[ix][iy].creature->status = NORMAL;//孵化させる。
						board[ix][iy].creature->SETdirection(this->GETdirection());//親と同じ方向を向けさせる。

						exhibitScreen();
						DrawString(800, 300, "PenguinKids.specialMovement2メソッド実行", WHITE);
						WaitKey();
						return TRUE;
					}
				}

			}
		}



		return FALSE;
	}

}






