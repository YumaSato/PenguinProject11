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
	string msg = "は何する?\n\n自分を左クリック:行動を選択\n隣のマスを右クリック(十字キー):向き変更\n\n1:歩く 2:産卵 3:孵化 4:攻撃 5:蹴る 6:パス\n\nキャラクタを左クリック:状態を表示\n\n\n\n\nスペースキー:ルールを表示";
	int xClick = 0;
	int yClick = 0;
	int XBuf = -49;
	int YBuf = -49;
	int mouse = NULL;
	bool clickStop = FALSE;
	bool ruleExhibit = FALSE;
	int dx = 0;
	int dy = 0;
	bool colorUpOrDown = TRUE;
	bool exhibitOrNot = FALSE;
	int color = 10;

	clicking = 0;

	mainMsg = name + msg;
	exhibitScreen(x,y,TRUE);
	WaitKey();

	while (1) {
		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
			return FALSE;
		}

		if (ruleExhibit == TRUE) {
			while (1) {
				WaitKey();
				if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
					ruleExhibit = FALSE;
					break;
				}
			}
		}


		if (colorUpOrDown == TRUE) {
			color += 25;
		}
		if (colorUpOrDown == FALSE) {
			color -= 25;
		}
		if (color >= 225) {
			colorUpOrDown = FALSE;
		}
		if (color <= 26) {
			colorUpOrDown = TRUE;
		}




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

		//もしクリックされたら、clicking=1になる。1の間は処理は行われない。




		mouse = GetMouseInput();


		if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//右も左もどちらのクリックも押されていなかったら、次のクリックを受け付ける。
			clicking = 0;
		}


		if (mouse & MOUSE_INPUT_RIGHT) {//右クリックされたら

			if (clicking == 0) {
				clicking = 1;

				GetMousePoint(&xClick, &yClick);
				xClick = xClick / 48;
				yClick = yClick / 48;

				dx = xClick - x;
				dy = yClick - y;
				if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {//自分の隣のマスの上にマウスポインタがある場合
					SETdirection(dx, dy);
					exhibitScreen(x, y, TRUE);//その方向を向く。
				}
			}
		}
		


		if (mouse & MOUSE_INPUT_LEFT) {//左クリックが行われた際の処理


			if (clicking == 0) {
				clicking = 1;

				GetMousePoint(&xClick, &yClick);//マウスポインタがどこにあるかを取得

				if (exhibitOrNot == TRUE) {//キャラ詳細表示を表示するフラグが立っていた場合
					bool turnFinish = FALSE;
					for (int iii = 0; iii < 6; iii++) {
						if (xClick > x * 48 + 50 + iii * 51 && xClick < x * 48 + 85 + iii * 51 && yClick > y * 48 + 24 && yClick < y * 48 + 43) {

							if (iii == 0) {//キャラ詳細表示の各ボタンを押すと行動が行われる
								if (walk(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 1) {
								if (specialMovement1(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 2) {
								if (specialMovement2(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 3) {
								if (attack(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 4) {
								if (kick(FIELDSIZE) == TRUE) {
									turnFinish = TRUE;
									break;
								}
							}
							if (iii == 5) {
								if (turnFinish == FALSE) {
									turnFinish = TRUE;
									break;
								}
							}
						}
					}
					if (turnFinish == TRUE) {
						break;
					}
					
				}




				xClick = xClick / 48;
				yClick = yClick / 48;
				if (xClick < FIELDSIZE && yClick < FIELDSIZE) {
					//if (board[xClick][yClick].creature == NULL) {//クリックした場所が空白マスならば、歩行メソッドを実行
					//	dx = xClick - x;
					//	dy = yClick - y;
					//	if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {
					//		WaitTimer(120);
					//		if (walk(FIELDSIZE) == TRUE) {
					//			break;//1が返ってくる、つまり成功すればループ抜けでターン終了
					//		}
					//	}

					//	
					//}
					//if (board[xClick][yClick].creature != NULL) {
					//	if (xClick == XBuf && yClick == YBuf) {//もともとの表示座標と同じところをクリックしたら
					//		exhibitScreen(x, y, TRUE);//ステータス詳細を消す。
					//		exhibitOrNot = FALSE;
					//		WaitTimer(70);
					//		XBuf = -1;
					//		YBuf = -1;
					//	}
					if (board[xClick][yClick].creature == NULL) {
						exhibitOrNot = FALSE;
						exhibitScreen(x, y, TRUE);
					}
					if (XBuf >= 0 && XBuf < FIELDSIZE && YBuf >= 0 && YBuf < FIELDSIZE) {//ステータス表示中のマスを示すXBufとYBufが盤面上の座標を示していた場合
						if (board[xClick][yClick].creature == board[XBuf][YBuf].creature) {//表示中のマスを触ったらステータス表示消える。
							exhibitOrNot = FALSE;
							exhibitScreen(x, y, TRUE);
						}
					}


					if (board[xClick][yClick].creature != NULL) {

						//if (xClick < FIELDSIZE && yClick < FIELDSIZE) {//もともとの座標と違うが、座標内をクリックしたら
						exhibitOrNot = TRUE;
						//}
					}

				}
			}
		}

		


		if (exhibitOrNot == TRUE) {//誰かキャラクタがいるマスを左クリックしたときの詳細表示。
			XBuf = xClick;
			YBuf = yClick;
			if (board[XBuf][YBuf].creature != NULL) {//ステータス詳細を表示。
				if (board[XBuf][YBuf].creature == this) {//それが自分であれば、選択肢を表示してクリックを受け付ける。

					

					exhibitScreen(x, y, TRUE);
					string Msg1 = "";
					string Msg2 = "";

					DrawBox(x * 48 + 40, y * 48 + 2, x * 48 + 360, y * 48 + 46, GetColor(225, 200, 0), TRUE);//外側のボックス
					DrawBox(x * 48 + 39, y * 48 + 1, x * 48 + 361, y * 48 + 47, GetColor(125, 0, 0), FALSE);//外側のボックスの縁

					for (int iii = 0; iii < 6; iii++) {
						DrawBox(x * 48 + 50 + iii * 51, y * 48 + 24, x * 48 + 85 + iii * 51, y * 48 + 43, GetColor(50+((color + iii*3) / 10), 220 + iii*5 - (color / 3), 100), TRUE);//選択ボックス

						/*if (xClick > x * 48 + 50 + iii * 51 && xClick < x * 48 + 85 + iii * 51 && yClick > y * 48 + 24 && yClick < y * 48 + 43) {
							if (iii == 0) {
								if (specialMovement1(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 1) {
								if (specialMovement2(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 2) {
								if (attack(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 3) {
								if (kick(FIELDSIZE) == TRUE) { return TRUE; }
							}
							if (iii == 0) {
								return TRUE;
							}
						}*/
					}

					Msg1 = board[x][y].creature->name + "のHP:" + std::to_string(board[x][y].creature->HP) + "/" + std::to_string(board[x][y].creature->HP_Limit) + "   素早さ値:" + std::to_string(board[x][y].creature->speed);
					Msg2 = " 歩く　産卵　孵化　攻撃　蹴る　パス";

					DrawString(x * 48 + 42, y * 48 + 5, Msg1.c_str(), GetColor(0, 10, 55));
					DrawString(x * 48 + 42, y * 48 + 26, Msg2.c_str(), GetColor(0, 10, 55));

					WaitTimer(10);

				}
				else {//クリックしたのが操作しているキャラじゃない場合、普通にステータスを表示する。
					exhibitStatus(x, y, XBuf, YBuf, TRUE);
	/*				WaitTimer(10);*/
				}
			}
			if (board[XBuf][YBuf].creature == NULL) {
				exhibitScreen(x, y, TRUE);
			}
		}




		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
			exhibitOrNot = FALSE;
			exhibitScreen(x, y, TRUE);
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
			WaitTimer(100);
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
		if (CheckHitKey(KEY_INPUT_6) == TRUE) {
			break;
		}

		if (CheckHitKey(KEY_INPUT_SPACE) == TRUE) {
			ruleExhibit = TRUE;
			exhibitRule();
		}




		WaitTimer(10);
	}

	//stamina += staminaRecoverAbility;//スタミナ回復
	//if (stamina > staminaLimit) {
	//	stamina = staminaLimit;//スタミナが満タンになるとき。
	//}

	HP += 8;//HP回復
	if (HP > HP_Limit) {
		HP = HP_Limit;//HPが満タンになるとき。
	}

	
	mainMsg = "";
	actionMsg = "行動終了。体力が回復します。";
	exhibitScreen(x, y, TRUE);
	WaitKey();
	
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
	int distance = 0;
	int checkX = 0;
	int checkY = 0;
	int staminaNeed = 10;

	int xClick = 0;
	int yClick = 0;
	int dx = 0;
	int dy = 0;
	int StringColor = 0;
	int mouse = 0;
	string Msg = "";
	bool colorUpOrDown = TRUE;

	actionMsg = "歩こう!　Esc:移動終了　SHIFT:斜めサポート";

	clicking = 1;





	while (distance < 3) {//各歩行の入力待機
		exhibitScreen(x, y, TRUE);
		checkX = 0;
		checkY = 0;
		mouse = 0;

		//if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//両方クリックが解除されていたら、次のクリックを受け付ける。
		//	clicking = 0;
		//}


		//if (stamina < staminaNeed) {//スタミナが必要数に満たない場合walk中断でリターン。
		//	actionMsg = "スタミナ切れだ！";
		//	exhibitScreen(x, y, TRUE);
		//	WaitKey();
		//	if (distance == 0) {
		//		return FALSE;
		//	}
		//	else {
		//		return TRUE;
		//	}
		//}

		exhibitScreen(x, y, TRUE);//歩けるマスは表示色変更。
		for (int iix = -1; iix <= 1; iix++) {
			for (int iiy = -1; iiy <= 1; iiy++) {
				if (board[x + iix][y + iiy].creature == NULL && board[x + iix][y + iiy].state == VACANT) {
					DrawBox((x + iix) * 48 + 1, (y + iiy) * 48 + 1, (x + iix) * 48 + 47, (y + iiy) * 48 + 47, GetColor(StringColor + (iix + 1) * 5 + iiy * 5, 255, 120), TRUE);
				}
			}
		}



		GetMousePoint(&xClick, &yClick);
		xClick = xClick / 48;
		yClick = yClick / 48;


		if (xClick < FIELDSIZE && yClick < FIELDSIZE) {

			

			dx = xClick - x;
			dy = yClick - y;
			if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1)) {//自分の隣のマスの上にマウスポインタがある場合
				if (board[xClick][yClick].creature == NULL && board[xClick][yClick].state == VACANT) {//空白マスにカーソルがある場合、キラキラ表示
					DrawBox(xClick * 48, yClick * 48, xClick * 48 + 48, yClick * 48 + 48, GetColor(10 + (StringColor / 5), 145 + (StringColor / 3), 0), TRUE);

					mouse = GetMouseInput();

					if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//右も左もどちらのクリックも押されていなかったら、次のクリックを受け付ける。
						clicking = 0;
					}

					
					if (mouse & MOUSE_INPUT_LEFT) {


				
						if (clicking == 0) {
							clicking = 1;

							board[xClick][yClick].creature = this;
							board[x][y].creature = NULL;

							x = xClick;//居場所を新たなマスに設定。
							y = yClick;
							SETdirection(dx, dy);


							distance++;

							stamina = stamina - staminaNeed;//スタミナの消費を実行。
							staminaNeed = staminaNeed + distance * 3;//次の歩みで減少するスタミナを決定。

							WaitTimer(10);//次の歩行クリックが即座に行われないよう、クリック直後に硬直時間を設ける。

						}
					}
				}
				else if(dx == 0 && dy == 0){//なんでこれクリックを条件にしてるのにカーソル乗せるだけで反応しちゃうんだよ～！！？！？
					//mouse = GetMouseInput();
					if (mouse & MOUSE_INPUT_LEFT) {
						if (distance == 0) {
							return FALSE;
						}
					}
				}
				
			}
			if((dx < -1 || dx > 1 || dy < -1 || dy > 1 || board[xClick][yClick].creature != NULL || board[xClick][yClick].state != VACANT) && (board[xClick][yClick].creature != this)) {//「進めないマスをクリックしている（自分を除く）場合
				mouse = GetMouseInput();
				if (mouse & MOUSE_INPUT_LEFT) {

					if (clicking == 0) {
						clicking = 1;

						exhibitScreen(x, y, TRUE);//歩行可能マス表示を消す。
						WaitTimer(130);
						if (distance == 0) {
							return FALSE;//0歩目なら行動はなかったことになる
						}
						else if (distance > 0) {
							return TRUE;//1歩以上進んでいたら行動した判定になる。
						}
					}
				}
			}

			mouse = GetMouseInput();
			if (mouse & MOUSE_INPUT_RIGHT) {//右クリックされて、まだ歩いていなければ歩きをキャンセルするのに成功。
				if (distance == 0) {
					return FALSE;
					exhibitScreen(x, y, TRUE);
				}
			}

			
			
			


		}
				


		if (colorUpOrDown == TRUE) {
			StringColor += 9;
		}
		if (colorUpOrDown == FALSE) {
			StringColor -= 9;
		}
		if (StringColor >= 230) {
			colorUpOrDown = FALSE;
		}
		if (StringColor <= 11) {
			colorUpOrDown = TRUE;
		}














		if (CheckHitKey(KEY_INPUT_LSHIFT) == FALSE && CheckHitKey(KEY_INPUT_RSHIFT) == FALSE) {
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
		}
		if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE or CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) {//斜め補助シフトが押されていたら
			DrawString(820, 85, "斜め移動モードオン!", WHITE);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//左上
				checkX -= 1;
				checkY -= 1;
				//directionY = -1;
				SETdirection(-1, -1);
				
			}
			else if (CheckHitKey(KEY_INPUT_UP) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//右上
				checkX += 1;
				checkY -= 1;
				//directionY = -1;
				SETdirection(1, -1);
				
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//左下
				checkX -= 1;
				checkY += 1;
				//directionY = -1;
				SETdirection(-1, +1);
				
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//右下
				checkX += 1;
				checkY += 1;
				//directionY = -1;
				SETdirection(1, +1);
				
			}	
		}
	


		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {//1を押したら歩行終了。
			if (distance == 0) {
				WaitTimer(100);
				exhibitScreen(x, y, TRUE);
				return FALSE;
			}
			else {
				return TRUE;
				WaitTimer(80);
			}
		}

		if (x + checkX >= 0 && x + checkX < size && y + checkY >= 0 && y + checkY < size) {
			if (board[x + checkX][y + checkY].creature == NULL && board[x + checkX][y + checkY].state == VACANT) {//押したマスの方向が空いていたらループ抜け

				SETdirection(checkX, checkY);

				board[x + checkX][y + checkY].creature = this;
				board[x][y].creature = NULL;

				x += checkX;//居場所を新たなマスに設定。
				y += checkY;



				distance += 1;

				stamina = stamina - staminaNeed;//スタミナの消費を実行。
				staminaNeed = staminaNeed + distance * 3;//次の歩みで減少するスタミナを決定。

				WaitTimer(150);
			}
		}

	
		WaitTimer(20);
	}
	return TRUE;
	actionMsg = "walkの実行が終了";
		
	exhibitScreen(x, y, TRUE);
	

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
