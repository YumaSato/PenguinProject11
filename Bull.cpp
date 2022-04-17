#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"
#include <string>
#include <stdlib.h>

using namespace std;

Bull::Bull() {
}

void Bull::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {//実質的なコンストラクタ。
	//未初期化のBull配列を作るためにはコンストラクタに何か書いてあるとダメらしいので、コンストラクタでやるべきことを別の関数にした。

	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;

	if (ParentTeam == red) {
		name = "赤い闘牛";
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
	}

	if (ParentTeam == blue) {
		name = "紫の闘牛";
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
		attackPower = 58;
		defensePower = 160;
		speed = 500000 - GetRand(360);//素早さはランダム。
		staminaRecoverAbility = NULL;
		num = mobNumber;
		skip = FALSE;//TRUEのとき、ペンギンキッズが生まれた時点では、こいつは行動をスキップする（まだ動かない）
		enemy = TRUE;//こいつは、敵。
	}



	exhibitScreen(x,y,TRUE);
	numSpeed = (to_string(speed));
	numX = (to_string(x));
	numY = (to_string(y));
	mobStatusMsg = "X:" + numX + ",Y:" + numY + "に闘牛が現れた！";
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

	if (attack(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		return TRUE;
	}
	if (walk(FIELDSIZE) == TRUE) {
		exhibitScreen(x, y, TRUE);
		WaitKey();
		return TRUE;
	}
	exhibitScreen(x, y, TRUE);
	WaitKey();
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
	bool walkOrNot = FALSE;

	if (ix >= 0 && ix < size && iy >= 0 && iy < size) {//歩くか否かを判定し、walkOrNotに判定結果を格納。
		if (board[ix][iy].creature != NULL) {
			if (board[ix][iy].creature->status == EGG) {//マスに卵があれば
				board[ix][iy].creature->DeleteCreature();//卵が死ぬ。
				actionMsg = name + "は歩いた。卵を踏みつぶした。";
				walkOrNot = TRUE;
			}
		}
		if (board[ix][iy].creature == NULL && board[ix][iy].state != CASTLE) {//マスが空白なら
			actionMsg = name + "は歩いた。";
			walkOrNot = TRUE;
		}
	}

	if (walkOrNot == TRUE) {//歩く判定TRUEなら、調べたマスに自分のアドレスを入れる。
		board[ix][iy].creature = this;
		board[x][y].creature = NULL;
		x = ix;//自分の位置をxyに入れる。
		y = iy;


		int randDi = 0;//歩き終わってから次に行動する方向を決定する。
		randDi = GetRand(1);
		if (CASTLE_X - x > 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {
			//x軸距離が+(城より左)で、かつy軸距離が+(城より上)で、かつX軸の城との距離がY軸の城との距離より長い場合(西北西)
			if (randDi == 0) {
				SETdirection(EE);
			}
			if (randDi == 1) {
				SETdirection(SE);
			}
		}
		if (CASTLE_X - x > 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {
			//x軸距離が+(城より左)で、かつy軸距離が+(城より上)で、かつX軸の城との距離がY軸の城との距離と同じ場合(北西)
			SETdirection(SE);
		}
		if (CASTLE_X - x > 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {
			//x軸距離が+(城より左)で、かつy軸距離が+(城より上)で、かつX軸の城との距離がY軸の城との距離より短い場合（北北西）
			if (randDi == 0) {
				SETdirection(SS);
			}
			if (randDi == 1) {
				SETdirection(SE);
			}
		}
		if (CASTLE_X - x > 0 && CASTLE_Y == y) {
			//x軸距離が+(城より左)で、かつy軸距離が0(城と同じ)で、かつX軸の城との距離がY軸の城との距離より長い場合（西）
			SETdirection(EE);
		}

		if (CASTLE_X - x > 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {
			//x軸距離が+(城より左)で、かつy軸距離が-(城より下)で、かつX軸の城との距離がY軸の城との距離より長い場合（西南西）
			if (randDi == 0) {
				SETdirection(EE);
			}
			if (randDi == 1) {
				SETdirection(NE);
			}
		}
		if (CASTLE_X - x > 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {
			//x軸距離が+(城より左)で、かつy軸距離が-(城より下)で、かつX軸の城との距離がY軸の城との距離が同じ場合（南西）
			SETdirection(NE);
		}

		if (CASTLE_X - x > 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {
			//x軸距離が+(城より左)で、かつy軸距離が-(城より下)で、かつX軸の城との距離がY軸の城との距離より短い場合（南南西）
			if (randDi == 0) {
				SETdirection(NN);
			}
			if (randDi == 1) {
				SETdirection(NE);
			}
		}


		if (CASTLE_X - x < 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {//東北東
			if (randDi == 0) {
				SETdirection(WW);
			}
			if (randDi == 1) {
				SETdirection(SW);
			}
		}
		if (CASTLE_X - x < 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {//北東
			SETdirection(SW);
		}
		if (CASTLE_X - x < 0 && CASTLE_Y - y > 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {//北北東
			if (randDi == 0) {
				SETdirection(SS);
			}
			if (randDi == 1) {
				SETdirection(SW);
			}
		}
		if (CASTLE_X - x < 0 && CASTLE_Y == y) {//東
			SETdirection(WW);
		}

		if (CASTLE_X - x < 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) > abs(CASTLE_Y - y)) {//東南東
			if (randDi == 0) {
				SETdirection(WW);
			}
			if (randDi == 1) {
				SETdirection(NW);
			}
		}
		if (CASTLE_X - x < 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) == abs(CASTLE_Y - y)) {//南東
			SETdirection(NW);
		}
		if (CASTLE_X - x < 0 && CASTLE_Y - y < 0 && abs(CASTLE_X - x) < abs(CASTLE_Y - y)) {//南南東
			if (randDi == 0) {
				SETdirection(NN);
			}
			if (randDi == 1) {
				SETdirection(NW);
			}
		}

		if (CASTLE_X == x && CASTLE_Y - y < 0) {//南
			SETdirection(NN);
		}
		if (CASTLE_X == x && CASTLE_Y - y > 0) {//北
			SETdirection(SS);
		}

		return TRUE;
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
			if (board[ix][iy].creature->enemy == TRUE || board[ix][iy].creature->status == EGG) {//でも敵側同士か卵だったら
				return FALSE;
			}
			if (board[ix][iy].creature->enemy == FALSE) {//NULLじゃなくてロボットどもだったら攻撃
				damage(ix, iy);
				return TRUE;
			}
		}



		if (board[ix][iy].creature == NULL && team == blue) {//マスが空白である場合

			int diCheck[8] = { 0,1,2,3,4,5,6,7 };//正面に敵があればそれが優先的に攻撃されるが、隣にいくつも敵がある場合、敵を攻撃する方向をランダムにする。
			Direction di = GETdirection();//方向データを仮置き。
			for (int i = 0; i < 7; i++) {
				int r = GetRand(7 - i) + i;
				int tmp = diCheck[i];
				diCheck[i] = diCheck[r];
				diCheck[r] = tmp;
			}

			for (int i = 0; i < 8; i++) {

				switch (diCheck[i]) {
				case 0:
					SETdirection(NW);
					break;
				case 1:
					SETdirection(NN);
					break;
				case 2:
					SETdirection(NE);
					break;
				case 3:
					SETdirection(EE);
					break;
				case 4:
					SETdirection(SE);
					break;
				case 5:
					SETdirection(SS);
					break;
				case 6:
					SETdirection(SW);
					break;
				case 7:
					SETdirection(WW);
					break;
				}



				if ((GETdirection() - di <= 2 && GETdirection() - di >= -2) || (GETdirection() == 1 && di == 7) || (GETdirection() == 0 && di == 7) || (GETdirection() == 0 && di == 6)) {
					//索敵範囲は、方向+-2まで。一旦方向を変えたことにする。索敵範囲をすべて索敵した後に、見つからなければ方向を元に戻す。
					GETdirectionXY(&dx, &dy);
					ix = x + dx;
					iy = y + dy;//索敵マスを設定。

					if (ix >= 0 && ix < size && iy >= 0 && iy < size) {

						if (board[ix][iy].creature != NULL) {//向いている方向のマスに何か居たら
							if (board[ix][iy].creature->enemy == FALSE && board[ix][iy].creature->status != EGG) {//それがペンギン共で、卵じゃなければ
								SETdirection(dx, dy);//敵の方を向いて
								damage(ix, iy);
								return TRUE;
							}
						}
					}
				}
				SETdirection(di);//索敵しても見つからなかったら元の方向に戻る。
			}
		}



		if (board[ix][iy].state == CASTLE) {
			board[ix][iy].state = VACANT;
			actionMsg = "城を壊されてしまった。";
			return TRUE;
		}
	}
	return FALSE;
}