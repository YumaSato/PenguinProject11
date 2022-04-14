#include <string>
#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"

using std::string;

//プロトタイプ宣言
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Character::Character() : Creature() {}

bool Character::selectAction() {
	string msg = "は何する?\n1:歩く 2:産卵 3:孵化 4:攻撃 5:蹴る";
	mainMsg = name + msg;
	exhibitScreen();
	WaitKey();
	while (1) {

		if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//向きだけ変わる:右
			//directionX = 1;
			//directionY = 0;
			SETdirection(1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:右上
				//directionY = -1;
				SETdirection(1, -1);
				exhibitScreen();
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:右下
				//directionY = 1;
				SETdirection(1, 1);
				exhibitScreen();
				WaitTimer(200);
			}
			exhibitScreen();
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//向きだけ変わる:左
			//directionX = -1;
			//directionY = 0;
			SETdirection(-1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:左上
				//directionY = -1;
				SETdirection(-1, -1);
				exhibitScreen();
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:左下
				//directionY = 1;
				SETdirection(-1, 1);
				exhibitScreen();
				WaitTimer(200);
			}
			exhibitScreen();
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:下
			//directionX = 0;
			//directionY = 1;
			SETdirection(0, 1);
			exhibitScreen();
		}
		else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:上
			//directionX = 0;
			//directionY = -1;
			SETdirection(0, -1);
			exhibitScreen();
		}




		//board[x][y].creature->directionX = this->directionX;
		//board[x][y].creature->directionY = this->directionY;




		if (CheckHitKey(KEY_INPUT_1) == TRUE) {
			if (walk(FIELDSIZE) == TRUE) {
				break;//1が返ってくる、つまり成功すればループ抜けでターン終了
			}
		}
		if (CheckHitKey(KEY_INPUT_2) == TRUE) {
			if (specialMovement1(FIELDSIZE) == TRUE) {
				break;//1が返ってくる、つまり成功すればループ抜けでターン終了
			}
		}
		if (CheckHitKey(KEY_INPUT_3) == TRUE) {
			if (specialMovement2(FIELDSIZE) == TRUE) {
				break;//1が返ってくる、つまり成功すればループ抜けでターン終了
			}
		}
		if (CheckHitKey(KEY_INPUT_4) == TRUE) {
			if (attack(FIELDSIZE) == TRUE) {
				break;//1が返ってくる、つまり成功すればループ抜けでターン終了
			}
		}
		if (CheckHitKey(KEY_INPUT_5) == TRUE) {
			if (kick(FIELDSIZE) == TRUE) {
				break;//1が返ってくる、つまり成功すればループ抜けでターン終了
			}
		}
	}

	stamina += 20;//スタミナ回復
	if (stamina > staminaLimit) {
		stamina = staminaLimit;//スタミナが満タンになるとき。
	}

	actionMsg = "行動終了。スタミナが回復します。";
	exhibitScreen();
	WaitKey();
	mainMsg = "";
	return TRUE;
};


void Character::test() {
	DrawString(400, 300, "Character.testメソッド実行", WHITE);
	WaitKey();
}


void Character::changeDirection() {//歩かずに向きを変える
	WaitKey();
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//なぜ上下左右が逆なの？謎。
		//directionX = 1;
		//directionY = 0;
		SETdirection(1, 0);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {
		//directionX = -1;
		//directionY = 0;
		SETdirection(-1, 0);
	}
	else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {
		//directionX = 0;
		//directionY = 1;
		SETdirection(0, 1);
	}
	else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {
		//directionX = 0;
		//directionY = -1;
		SETdirection(0, -1);
	}
	//board[x][y].creature->directionX = this->directionX;
	//board[x][y].creature->directionY = this->directionY;
	int tmpx, tmpy;
	this->GETdirectionXY(&tmpx, &tmpy);
	board[x][y].creature->SETdirection(tmpx, tmpy);
	exhibitScreen();
};


bool Character::walk(int size) {//歩く。盤面サイズ(size)を受け取る
	int distance = 3;
	int checkX;
	int checkY;
	int staminaNeed = 10;

	if (stamina < 20) {//最低スタミナ消費数である20以下しかスタミナがない場合、walkできずリターン。
		return FALSE;
	}

	for (int i = 1; i <= distance; i++) {//1歩歩く

		if (stamina < staminaNeed) {//スタミナが必要数に満たない場合walk中断でリターン。
			actionMsg = "スタミナ切れだ！";
			exhibitScreen();
			return TRUE;
		}

		actionMsg = "歩こう!　1:移動終了　SHIFT:斜めサポート";
		exhibitScreen();

		while (1) {
			checkX = this->x;//自分のいる座標を代入。
			checkY = this->y;//checkXとcheckYで進めるマスか探知。
			WaitKey();
			if (CheckHitKey(KEY_INPUT_1) == TRUE) {//1を押したら歩行終了。
				return TRUE;
			}




			if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {
				checkX -= 1;
				//directionX = -1;
				//directionY = 0;
				SETdirection(-1, 0);
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {
				checkX += 1;
				//directionX = 1;
				//directionY = 0;
				SETdirection(1, 0);
			}
			else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {
				checkY -= 1;
				//directionY = -1;
				//directionX = 0;
				SETdirection(0, -1);
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {
				checkY += 1;
				//directionY = 1;
				//directionX = 0;
				SETdirection(0, 1);
			}


			else if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE or CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) {//斜め補助シフトが押されていたら
				while (1) {
					DrawString(800, 85, "斜め移動モードオン!", WHITE);
					WaitKey();
					if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//左上
						checkX -= 1;
						checkY -= 1;
						//directionY = -1;
						SETdirection(-1, -1);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//右上
						checkX += 1;
						checkY -= 1;
						//directionY = -1;
						SETdirection(1, -1);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//左下
						checkX -= 1;
						checkY += 1;
						//directionY = -1;
						SETdirection(-1, +1);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//右下
						checkX += 1;
						checkY += 1;
						//directionY = -1;
						SETdirection(1, +1);
						break;
					}

					else if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE or CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) {//斜め補助解除
						exhibitScreen();
						DrawString(800, 70, "歩こう! 1:移動終了　SHIFT:斜めサポート", WHITE);
						break;
					}
					else if (CheckHitKey(KEY_INPUT_1) == TRUE) {//1を押したら歩行終了。
						return TRUE;
					}
				}
			}

			if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
				if (board[checkX][checkY].creature == NULL && board[checkX][checkY].state == VACANT) {//押したマスの方向が空いていたらループ抜け
					break;
				}
			}
		}


		board[checkX][checkY].creature = this;

		board[x][y].creature = NULL;

		x = checkX;//居場所を新たなマスに設定。
		y = checkY;


		stamina = stamina - staminaNeed;//スタミナの消費を実行。
		staminaNeed = staminaNeed + i * 5;//次の歩みで減少するスタミナを決定。


		exhibitScreen();
	};


	actionMsg = "walkの実行が終了";
	exhibitScreen();
	return TRUE;
}








bool Character::attack(int size) {

	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
		if (board[checkX][checkY].creature == NULL) {//殴った場所に誰もいなければ、FALSEを返して、行動なし判定。
			return FALSE;
		}
		damage(checkX, checkY);


		string msg1 = "は攻撃した。";
		//string msg2 = board[checkX][checkY].creature->name;//なぜか実行時エラーが出る。
		string msg3 = "はダメージを受けた。";
		actionMsg = name + msg1;

		//actionMsg = "fafafafafafafaffa";


		exhibitScreen();
		DrawString(800, 180, actionMsg.c_str(), GetColor(255, 200, 255));
		WaitKey();
		return TRUE;
	}
	return FALSE;
}
