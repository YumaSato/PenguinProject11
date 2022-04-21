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
	string msg = "は何する?\n\n1:歩く 2:産卵 3:孵化 4:攻撃 5:蹴る\nキャラを右クリック:状態を表示";
	int xClick = NULL;
	int yClick = NULL;
	int XBuf = -49;
	int YBuf = -49;
	int mouse = NULL;
	int dx = 0;
	int dy = 0;
	mainMsg = name + msg;
	exhibitScreen(x,y,TRUE);
	WaitKey();
	while (1) {




		//GetMousePoint(&xClick, &yClick);
		//xClick = xClick / 48;
		//yClick = yClick / 48;
		//if (xClick < FIELDSIZE && yClick < FIELDSIZE) {
		//	dx = xClick - x;
		//	dy = yClick - y;
		//	if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {//自分の隣のマスをクリックしている場合

		//		//SETdirection(dx, dy);//その方向を向く。
		//		//exhibitScreen(x, y, TRUE);

		//		if (board[xClick][yClick].creature == NULL && board[xClick][yClick].state == VACANT) {//さらにそのマスに生物がいない、かつVACANTだった場合

		//			int StringColor = 0;
		//			string Msg = "";
		//			bool colorUpOrDown = TRUE;

		//			exhibitScreen(x, y, TRUE);
		//			DrawBox(xClick * 48, yClick * 48, xClick * 48 + 48, yClick * 48 + 48, GetColor(StringColor, 255, 50), TRUE);

		//			if (colorUpOrDown == TRUE) {
		//				StringColor += 9;
		//			}
		//			if (colorUpOrDown == FALSE) {
		//				StringColor -= 9;
		//			}
		//			if (StringColor >= 240) {
		//				colorUpOrDown = FALSE;
		//			}
		//			if (StringColor <= 10) {
		//				colorUpOrDown = TRUE;
		//			}
		//		}
		//	}
		//	else{
		//		exhibitScreen(x, y, TRUE);
		//	}

		//}





		mouse = GetMouseInput();
		if (mouse & MOUSE_INPUT_RIGHT) {
			GetMousePoint(&xClick, &yClick);
			xClick = xClick / 48;
			yClick = yClick / 48;

			if (xClick == XBuf && yClick == YBuf) {//もともとの表示座標と同じところをクリックしたら
				exhibitScreen(x, y, TRUE);//ステータス詳細を消す。
				WaitTimer(250);
				XBuf = -1;
				YBuf = -1;
			}else if (xClick < FIELDSIZE && yClick < FIELDSIZE) {//もともとの座標と違うが、座標内をクリックしたら
				XBuf = xClick;
				YBuf = yClick;
				if (board[XBuf][YBuf].creature != NULL) {//ステータス詳細を表示。
					exhibitStatus(x, y, XBuf, YBuf, TRUE);
					WaitTimer(250);
				}
				if (board[XBuf][YBuf].creature == NULL) {
					exhibitScreen(x, y, TRUE);
				}
			}
		}
		if (mouse & MOUSE_INPUT_LEFT) {
			xClick = xClick / 48;
			yClick = yClick / 48;
			if (xClick < FIELDSIZE && yClick < FIELDSIZE) {
				if (walk(FIELDSIZE) == TRUE) {
					break;//1が返ってくる、つまり成功すればループ抜けでターン終了
				}
			}

		}



			




		if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//向きだけ変わる:右
			//directionX = 1;
			//directionY = 0;
			SETdirection(1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:右上
				//directionY = -1;
				SETdirection(1, -1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:右下
				//directionY = 1;
				SETdirection(1, 1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			exhibitScreen(x, y, TRUE);
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//向きだけ変わる:左
			//directionX = -1;
			//directionY = 0;
			SETdirection(-1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:左上
				//directionY = -1;
				SETdirection(-1, -1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:左下
				//directionY = 1;
				SETdirection(-1, 1);
				exhibitScreen(x, y, TRUE);
				WaitTimer(200);
			}
			exhibitScreen(x, y, TRUE);
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:下
			//directionX = 0;
			//directionY = 1;
			SETdirection(0, 1);
			exhibitScreen(x, y, TRUE);
		}
		else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:上
			//directionX = 0;
			//directionY = -1;
			SETdirection(0, -1);
			exhibitScreen(x, y, TRUE);
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

	HP += 8;//HP回復
	if (HP > HP_Limit) {
		HP = HP_Limit;//HPが満タンになるとき。
	}

	

	actionMsg = "行動終了。スタミナが回復します。";
	exhibitScreen(x, y, TRUE);
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
	exhibitScreen(x, y, TRUE);
};


bool Character::walk(int size) {//歩く。盤面サイズ(size)を受け取る
	int distance = 3;
	int checkX;
	int checkY;
	int staminaNeed = 10;

	if (stamina < 20) {//最低スタミナ消費数である20以下しかスタミナがない場合、walkできずリターン。
		return FALSE;
	}

	int xClick = 0;
	int yClick = 0;
	int dx;
	int dy;
	int StringColor = 0;
	string Msg = "";
	bool colorUpOrDown = TRUE;

	actionMsg = "歩こう!　1:移動終了　SHIFT:斜めサポート";


	for (int i = 1; i <= distance; i++) {//1歩歩く

		if (stamina < staminaNeed) {//スタミナが必要数に満たない場合walk中断でリターン。
			actionMsg = "スタミナ切れだ！";
			exhibitScreen(x, y, TRUE);
			return TRUE;
		}

		
		exhibitScreen(x, y, TRUE);


		




		while (1) {

			for (int iix = -1; iix <= 1; iix++) {
				for (int iiy = -1; iiy <= 1; iiy++) {
					if (board[x + iix][y + iiy].creature == NULL && board[x + iix][y + iiy].state == VACANT) {
						DrawBox((x + iix) * 48, (y + iiy) * 48, (x + iix) * 48 + 48, (y + iiy) * 48 + 48, GetColor(StringColor, 255, 50), TRUE);
					}
				}
			}
			DrawBox(xClick * 48, yClick * 48, xClick * 48 + 48, yClick * 48 + 48, GetColor(StringColor, 255 - StringColor, 50), TRUE);

			if (colorUpOrDown == TRUE) {
				StringColor += 9;
			}
			if (colorUpOrDown == FALSE) {
				StringColor -= 9;
			}
			if (StringColor >= 240) {
				colorUpOrDown = FALSE;
			}
			if (StringColor <= 10) {
				colorUpOrDown = TRUE;
			}


		//
		//	GetMousePoint(&xClick, &yClick);
		//	xClick = xClick / 48;
		//	yClick = yClick / 48;
		//	if (xClick < FIELDSIZE && yClick < FIELDSIZE) {
		//		dx = xClick - x;
		//		dy = yClick - y;
		//		if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {//自分の隣のマスの上にマウスポインタがある場合

		//			//SETdirection(dx, dy);//その方向を向く。
		//			//exhibitScreen(x, y, TRUE);

		//			if (board[xClick][yClick].creature == NULL && board[xClick][yClick].state == VACANT) {//さらにそのマスに生物がいない、かつVACANTだった場合

		//				

		//				

		//			}
		//		}
		//		else {
		//			exhibitScreen(x, y, TRUE);
		//		}

		//	}





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
						exhibitScreen(x, y, TRUE);
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

		
		exhibitScreen(x, y, TRUE);
		/*WaitKey();*/
	};


	actionMsg = "walkの実行が終了";
	exhibitScreen(x, y, TRUE);
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




		exhibitScreen(x, y, TRUE);
		DrawString(800, 180, actionMsg.c_str(), GetColor(255, 200, 255));
		WaitKey();
		return TRUE;
	}
	return FALSE;
}
