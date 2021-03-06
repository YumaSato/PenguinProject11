#include <string>
#include "DxLib.h"
#include "externs.h"
#include "consts.h"
#include "MyClasses.h"

using std::string;



Character::Character() : Creature() {}

int Character::selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
	string msg = "は何する?\n\n自分を左クリック:行動を選択\n1:歩く 2:産卵 3:孵化 4:攻撃 5:押す 6:パス\nキャラクタを左クリック:状態を表示\nWASDキー:視点移動(SHIFTで高速移動)\n\n隣のマスを右クリック(十字キー):向き変更\n\n\n\n\nE:ルールを表示";
	int xClick = 0;
	int yClick = 0;
	int XBuf = -49;//ステータス表示を行う際に、今クリックしたわけじゃないけどステータス表示状態として持続しているマスの座標を表す。
	int YBuf = -49;
	int mouse = NULL;
	bool clickStop = FALSE;
	bool ruleExhibit = FALSE;
	int dx = 0;
	int dy = 0;
	bool colorUpOrDown = TRUE;
	bool exhibitOrNot = FALSE;
	bool exhibitMyStatusOrNot = FALSE;
	int color = 10;
	actionMsg = "";


	int afew = -2;//エラー解決用

	clicking = 1;
	pushingKey = 1;

	mainMsg = name + msg;
	exhibitScreen(x, y, TRUE, FALSE, board, handledCharacters);
	//WaitKey();

	while (1) {
		

		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
			return FALSE;
		}

		exhibitScreen(x, y, TRUE, ruleExhibit, board, handledCharacters);


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






		mouse = GetMouseInput();
		if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//右も左もどちらのクリックも押されていなかったら、次のクリックを受け付ける。
			clicking = 0;
		}
		if (CheckHitKey(KEY_INPUT_1) == FALSE && CheckHitKey(KEY_INPUT_2) == FALSE && CheckHitKey(KEY_INPUT_3) == FALSE && CheckHitKey(KEY_INPUT_4) == FALSE && CheckHitKey(KEY_INPUT_5) == FALSE && CheckHitKey(KEY_INPUT_6) == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE && CheckHitKey(KEY_INPUT_RETURN) == FALSE && CheckHitKey(KEY_INPUT_SPACE) == FALSE && CheckHitKey(KEY_INPUT_E) == FALSE) {
			pushingKey = 0;
		}


		if ((mouse & MOUSE_INPUT_RIGHT)&& clicking == 0) {//右クリックされたら
			clicking = 1;
			//ruleExhibit = FALSE;
			GetMousePoint(&xClick, &yClick);

		/*if (GetClickPlace(&xClick, &yClick) == 2) {*/
			
			xClick = (GameBuf->exhibitX + xClick) / 48;
			yClick = (GameBuf->exhibitY + yClick) / 48;

			dx = xClick - x;
			dy = yClick - y;
			if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && (dx != 0 || dy != 0)) {//自分の隣のマスの上にマウスポインタがある場合
				SETdirection(dx, dy);
				exhibitScreen(x, y, TRUE, ruleExhibit ,board, handledCharacters);//その方向を向く。

			}
		}



		//afew = GetClickPlace(&xClick, &yClick);//エラー確認用で返り値を描画。
		//actionMsg = "afew=" + std::to_string(afew);
		//exhibitScreen(x, y, TRUE, board, handledCharacters);//なんで？？？？
		//WaitKey();
		//if (afew == 1){
		//if (GetClickPlace(&xClick, &yClick) == 1) {


		if ((mouse & MOUSE_INPUT_LEFT) && clicking == 0) {//左クリックが行われた際の処理
			clicking = 1;
			//ruleExhibit = FALSE;
			GetMousePoint(&xClick, &yClick);
		

			if (exhibitMyStatusOrNot == TRUE) {//操作可能キャラの詳細を表示するフラグが立っていた場合
				bool turnFinish = FALSE;
				for (int iii = 0; iii < 6; iii++) {//６つの選択肢がクリックを受け付ける。
					if (xClick > -GameBuf->exhibitX + x * 48 + 50 + iii * 51 && xClick < -GameBuf->exhibitX + x * 48 + 85 + iii * 51 && yClick > -GameBuf->exhibitY + y * 48 + 24 && yClick < -GameBuf->exhibitY + y * 48 + 43) {

						if (iii == 0) {//キャラ詳細表示の各ボタンを押すと行動が行われる
							if (walk(board, handledCharacters) == TRUE) {
								turnFinish = TRUE;
								break;
							}
						}
						if (iii == 1) {
							if (specialMovement1(mobs_PenguinKids, mobs_Bull, board, handledCharacters) == TRUE) {
								turnFinish = TRUE;
								break;
							}
						}
						if (iii == 2) {
							if (specialMovement2(board, handledCharacters) == TRUE) {
								turnFinish = TRUE;
								break;
							}
						}
						if (iii == 3) {
							if (attack(board, handledCharacters) == TRUE) {
								turnFinish = TRUE;
								break;
							}
						}
						if (iii == 4) {
							if (kick(board, handledCharacters) == TRUE) {
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
			//これより上は、操作を受け付ける内容。この下は、



			//この先は、XClickとYClickが、押したマスを表す。
			xClick = (GameBuf->exhibitX + xClick) / 48;
			yClick = (GameBuf->exhibitY + yClick) / 48;



			if (xClick < GameBuf->sizeX && yClick < GameBuf->sizeY) {


				if (board[xClick][yClick].creature == NULL) {//押したマスがNULLなら、ステータス表示状態を解除。
					exhibitOrNot = FALSE;
					XBuf = -1;
					YBuf = -1;
					//exhibitScreen(x, y, TRUE, ruleExhibit, board, handledCharacters);
				}

				if (board[xClick][yClick].creature != NULL) {//キャラがいる場所をクリックした際

					if (XBuf >= 0 && XBuf < GameBuf->sizeX && YBuf >= 0 && YBuf < GameBuf->sizeY) {//ステータス表示中のマスを示すXBufとYBufが盤面上の座標を示していた場合
						if (board[xClick][yClick].creature == board[XBuf][YBuf].creature) {//表示中のマスを触ったらステータス表示消える。
							exhibitOrNot = FALSE;
							XBuf = -1;
							YBuf = -1;
							//exhibitScreen(x, y, TRUE, ruleExhibit, board, handledCharacters);
						}
					}
					else {
						exhibitOrNot = TRUE;
						ruleExhibit = FALSE;
					}


					if (xClick != x || yClick != y || (xClick == x && yClick == y && exhibitMyStatusOrNot == TRUE)) {
						exhibitMyStatusOrNot = FALSE;
					}
					else if (xClick == x && yClick == y) {
						exhibitMyStatusOrNot = TRUE;
					}
					
				}

			}

		}




		if (exhibitOrNot == TRUE) {//誰かキャラクタがいるマスを左クリックしたときの詳細表示。
			XBuf = xClick;
			YBuf = yClick;
			if (board[XBuf][YBuf].creature != NULL) {

				exhibitStatus(x, y, XBuf, YBuf, TRUE, color, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}
			if (board[XBuf][YBuf].creature == NULL) {
				//exhibitScreen(x, y, TRUE, ruleExhibit, board, handledCharacters);
			}
		}






		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
			exhibitOrNot = FALSE;
		}


		if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//向きだけ変わる:右
			SETdirection(1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:右上
				SETdirection(1, -1);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:右下
				SETdirection(1, 1);
				WaitTimer(200);
			}
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {//向きだけ変わる:左
			SETdirection(-1, 0);
			if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:左上
				SETdirection(-1, -1);
				WaitTimer(200);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:左下
				SETdirection(-1, 1);
				WaitTimer(200);
			}
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {//向きだけ変わる:下
			SETdirection(0, 1);
		}
		else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//向きだけ変わる:上
			SETdirection(0, -1);
		}







		GameBuf->ScreenMove(x, y);



		if (pushingKey == 0) {


			if (CheckHitKey(KEY_INPUT_1) == TRUE) {
				pushingKey = 1;
				ruleExhibit = FALSE;
				if (walk(board, handledCharacters) == TRUE) {
					break;//1が返ってくる、つまり成功すればループ抜けでターン終了
				}
			}
			if (CheckHitKey(KEY_INPUT_2) == TRUE) {
				pushingKey = 1;
				if (specialMovement1(mobs_PenguinKids, mobs_Bull, board, &handledCharacters[0]) == TRUE) {
					break;//1が返ってくる、つまり成功すればループ抜けでターン終了
				}
			}
			if (CheckHitKey(KEY_INPUT_3) == TRUE) {
				pushingKey = 1;
				if (specialMovement2(board, handledCharacters) == TRUE) {
					break;//1が返ってくる、つまり成功すればループ抜けでターン終了
				}
			}
			if (CheckHitKey(KEY_INPUT_4) == TRUE) {
				pushingKey = 1;
				if (attack(board, handledCharacters) == TRUE) {
					break;//1が返ってくる、つまり成功すればループ抜けでターン終了
				}
			}
			if (CheckHitKey(KEY_INPUT_5) == TRUE) {
				pushingKey = 1;
				if (kick(board, handledCharacters) == TRUE) {
					break;//1が返ってくる、つまり成功すればループ抜けでターン終了
				}
			}
			if (CheckHitKey(KEY_INPUT_6) == TRUE) {
				pushingKey = 1;
				break;
			}

			if (CheckHitKey(KEY_INPUT_E) == TRUE) {
				pushingKey = 1;
				if (ruleExhibit == FALSE) {
					ruleExhibit = TRUE;
				}
				else {
					ruleExhibit = FALSE;
				}
			}

			if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
				pushingKey = 1;
				ruleExhibit = FALSE;
				while (1) {
					mainMsg = "本当にゲームを終了してよろしいですか？ \nEnterキー:Yes 0:No";
					ClearDrawScreen();
					exhibitScreen(x, y, TRUE, ruleExhibit, board, handledCharacters);
					if (CheckHitKey(KEY_INPUT_RETURN) == TRUE) {
						return 2;
					}
					if (CheckHitKey(KEY_INPUT_0) == TRUE || CheckHitKey(KEY_INPUT_SPACE) == TRUE) {
						mainMsg = name + "は何する?\n\n自分を左クリック:行動を選択\n1:歩く 2:産卵 3:孵化 4:攻撃 5:押す 6:パス\nキャラクタを左クリック:状態を表示\nWASDキー:視点移動\n\n隣のマスを右クリック(十字キー):向き変更\n\n\n\n\nE:ルールを表示";
						break;
					}
					WaitTimer(10);
				}
			}
		}

		//WaitTimer(10);
		ScreenFlip(); //裏画面を表画面に反映
		
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
	//exhibitScreen(x, y, TRUE, board, handledCharacters);
	GameBuf->GoNext(x, y);

	//WaitKey();

	return TRUE;
};
















void Character::test() {
	DrawString(400, 300, "Character.testメソッド実行", WHITE);
	WaitKey();
}


//void Character::changeDirection() {//歩かずに向きを変える
//	WaitKey();
//	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE) {//なぜ上下左右が逆なの？謎。
//		//directionX = 1;
//		//directionY = 0;
//		SETdirection(1, 0);
//	}
//	else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE) {
//		//directionX = -1;
//		//directionY = 0;
//		SETdirection(-1, 0);
//	}
//	else if (CheckHitKey(KEY_INPUT_DOWN) == TRUE) {
//		//directionX = 0;
//		//directionY = 1;
//		SETdirection(0, 1);
//	}
//	else if (CheckHitKey(KEY_INPUT_UP) == TRUE) {
//		//directionX = 0;
//		//directionY = -1;
//		SETdirection(0, -1);
//	}
//	//board[x][y].creature->directionX = this->directionX;
//	//board[x][y].creature->directionY = this->directionY;
//	int tmpx, tmpy;
//	this->GETdirectionXY(&tmpx, &tmpy);
//	board[x][y].creature->SETdirection(tmpx, tmpy);
//	exhibitScreen(x, y, TRUE);
//};












bool Character::walk( Grid** board, Emperor* handledCharacters) {//歩く。盤面サイズ(size)を受け取る
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

		GameBuf->ScreenMove(x, y);

		exhibitScreen(x, y, TRUE, FALSE, board, handledCharacters);
		checkX = 0;
		checkY = 0;
		mouse = 0;

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




		//GameBuf->ScreenMove(x, y);

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

		
		for (int iix = -1; iix <= 1; iix++) {
			for (int iiy = -1; iiy <= 1; iiy++) {
				if (board[x + iix][y + iiy].creature == NULL && board[x + iix][y + iiy].state == VACANT) {
					DrawBox(-GameBuf->exhibitX + (x + iix) * 48 + 1, -GameBuf->exhibitY + (y + iiy) * 48 + 1, -GameBuf->exhibitX + (x + iix) * 48 + 47, -GameBuf->exhibitY + (y + iiy) * 48 + 47, GetColor(StringColor + (iix + 1) * 5 + iiy * 5, 255, 120), TRUE);
				}
			}
		}




		GetMousePoint(&xClick, &yClick);
		xClick = (GameBuf->exhibitX + xClick) / 48;
		yClick = (GameBuf->exhibitY + yClick) / 48;

		if (xClick < GameBuf->sizeX && yClick < GameBuf->sizeY) {



			dx = xClick - x;
			dy = yClick - y;
			if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1)) {//自分の隣のマスの上にマウスポインタがある場合
				if (board[xClick][yClick].creature == NULL && board[xClick][yClick].state == VACANT) {//空白マスにカーソルがある場合、キラキラ表示
					DrawBox(-GameBuf->exhibitX + xClick * 48, -GameBuf->exhibitY + yClick * 48, -GameBuf->exhibitX + xClick * 48 + 48, -GameBuf->exhibitY + yClick * 48 + 48, GetColor(10 + (StringColor / 5), 145 + (StringColor / 3), 0), TRUE);

					mouse = GetMouseInput();

					if (!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//右も左もどちらのクリックも押されていなかったら、次のクリックを受け付ける。
						clicking = 0;
					}


					if (mouse & MOUSE_INPUT_LEFT) {



						if (clicking == 0) {
							clicking = 1;
							SETdirection(dx, dy);
							exhibitWalking(x, y, dx, dy, StringColor, GameBuf->mobs_PenguinKids, GameBuf->mobs_Bull, board, handledCharacters);

							board[xClick][yClick].creature = this;
							board[x][y].creature = NULL;

							x = xClick;//居場所を新たなマスに設定。
							y = yClick;
							

							

							distance++;

							WaitTimer(10);//次の歩行クリックが即座に行われないよう、クリック直後に硬直時間を設ける。

						}
					}
				}
				else if (dx == 0 && dy == 0) {//なんでこれクリックを条件にしてるのにカーソル乗せるだけで反応しちゃうんだよ〜！！？！？
					//mouse = GetMouseInput();
					if (mouse & MOUSE_INPUT_LEFT) {
						if (distance == 0) {
							return FALSE;
						}
					}
				}

			}
			if ((dx < -1 || dx > 1 || dy < -1 || dy > 1 || board[xClick][yClick].creature != NULL || board[xClick][yClick].state != VACANT) && (board[xClick][yClick].creature != this)) {//「進めないマスをクリックしている（自分を除く）場合
				mouse = GetMouseInput();
				if (mouse & MOUSE_INPUT_LEFT) {

					if (clicking == 0) {
						clicking = 1;

						exhibitScreen(x, y, TRUE, FALSE, board, handledCharacters);//歩行可能マス表示を消す。
						//WaitTimer(130);
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
					exhibitScreen(x, y, TRUE, FALSE, board, handledCharacters);
				}
			}






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
				exhibitScreen(x, y, TRUE, FALSE, board, handledCharacters);
				return FALSE;
			}
			else {
				return TRUE;
				WaitTimer(80);
			}
		}

		if (x + checkX >= 0 && x + checkX < GameBuf->sizeX && y + checkY >= 0 && y + checkY < GameBuf->sizeY) {
			if (board[x + checkX][y + checkY].creature == NULL && board[x + checkX][y + checkY].state == VACANT) {//押したマスの方向が空いていたらループ抜け

				SETdirection(checkX, checkY);

				exhibitWalking(x,y,checkX,checkY,StringColor, GameBuf->mobs_PenguinKids, GameBuf->mobs_Bull,board,handledCharacters);

				board[x + checkX][y + checkY].creature = this;
				board[x][y].creature = NULL;

				x += checkX;//居場所を新たなマスに設定。
				y += checkY;



				distance += 1;

				WaitTimer(100);
			}
		}



		ScreenFlip();
	}
	return TRUE;
	actionMsg = "歩き終わった！";

	exhibitScreen(x, y, TRUE, FALSE, board, handledCharacters);


}








bool Character::attack( Grid** board, Emperor* handledCharacters) {

	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < GameBuf->sizeX && checkY >= 0 && checkY < GameBuf->sizeX) {
		if (board[checkX][checkY].creature == NULL) {//殴った場所に誰もいなければ、FALSEを返して、行動なし判定。
			return FALSE;
		}
		/*if (damage(checkX, checkY, board, handledCharacters) == 0) {
			return 0;
		}*/

		if (damage(checkX, checkY, board, handledCharacters) == 2) {
			quitGame = TRUE;
		}


		//string msg1 = "は攻撃した。";
		////string msg2 = board[checkX][checkY].creature->name;//なぜか実行時エラーが出る。
		//string msg3 = "はダメージを受けた。";
		//actionMsg = name + msg1;




		//exhibitScreen(x, y, TRUE, board, handledCharacters);
		//DrawString(800, 180, actionMsg.c_str(), GetColor(255, 200, 255));
		//WaitKey();
		return TRUE;
	}
	return FALSE;
}





bool Character::kick(Grid** board, Emperor* handledCharacters) {
	return FALSE;
}
