#include "DxLib.h"
#include <string>
#include <iostream>
#include "DxLib.h"
#include "consts.h"
#include "externs.h"
#include "MyClasses.h"
#include <vector>

using std::to_string;






void exhibitStatusMsg() {//動かせるキャラクタのステータス情報を表示する。

	string CharacterStatusMsg;

	string HP_Msg = "";
	string staminaMsg = "";
	int exhibitY = 400;
	for (int i = 0; i < CHARACTERNUM; i++) {

		string numHP;
		numHP = (to_string(handledCharacters[i]->HP));
		string numHP_Limit;
		numHP_Limit = (to_string(handledCharacters[i]->HP_Limit));
		string numStamina;
		numStamina = (to_string(handledCharacters[i]->stamina));
		string numStaminaLimit;
		numStaminaLimit = (to_string(handledCharacters[i]->staminaLimit));

		CharacterStatusMsg = handledCharacters[i]->name + "の状態\n HP :" + numHP + " / " + numHP_Limit + "\nスタミナ" + numStamina + " / " + numStaminaLimit;

		//char HP_NumStr[BUFFER];
		//sprintf_s(HP_NumStr, BUFFER, "%d / %d\n", handledCharacters[i].HP, handledCharacters[i].HP_Limit);

		//char stamina_NumStr[BUFFER];
		//sprintf_s(stamina_NumStr, BUFFER, "%d / %d", handledCharacters[i].stamina, handledCharacters[i].staminaLimit);

	   // CharacterStatusMsg = handledCharacters[i].name +"の状態\n HP :"+ (string)HP_NumStr +"スタミナ:"+ (string)stamina_NumStr;

		//staminaMsg = "スタミナ : % d / % d ", handledCharacters[i].stamina, handledCharacters[i].staminaLimit;
		//DrawString(800, exhibitY + 20 , HP_Msg.c_str(), GetColor(255, 200, 255));


		DrawString(800, exhibitY, CharacterStatusMsg.c_str(), GetColor(255, 200, 255));



		exhibitY = exhibitY + 90;
	}

}





void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/) {//ペンギンを描画（ステータスと向きからペンギンの適切な画像のハンドルを入手し格納してから描画）
	int h;//ハンドル格納用
	int hHP;
	bool HPexhibitOrNot;
	ClearDrawScreen();//一度画面を全消し
	DrawGraph(0, 0, HandleBoard, TRUE);

	//for (int ix = 0; ix < ; ix++)






	for (int ix = 0; ix < FIELDSIZE; ix++) {
		for (int iy = 0; iy < FIELDSIZE; iy++) {
			if (board[ix][iy].state == ROCK) {
				DrawBox(ix * 48, iy * 48, ix * 48 + 47, iy * 48 + 47, GetColor(205, 133, 63), TRUE);
				continue;
			}


			HPexhibitOrNot = FALSE;//体力が満タンでない場合、これがTRUEになり、メータが表示される。

			if (board[ix][iy].creature == NULL) {
				continue;
			}
			else if (board[ix][iy].creature->status == EGG) {//卵の場合は方向が無いため二次元配列の2個目の0番目にしか画像が入っておらずそれ以外はnull(?)。
				h = handle[board[ix][iy].creature->team][EGG][NW];
			}
			else if (board[ix][iy].creature->status != EGG) {
				//Func<int, int, bool> f = (i, j) = > board[ix][iy].directionX == i && board[ix][iy].directionY == j;
				//if (f(-1, -1)) directionNum = 0;
				//if (board[ix][iy].creature->directionX == -1 && board[ix][iy].creature->directionY == -1) {//方向が斜め左上のとき
				//	directionNum = NW;
				//}
				//if (board[ix][iy].creature->directionX == 0 && board[ix][iy].creature->directionY == -1) {//方向が上のとき
				//	directionNum = NN;
				//}
				//if (board[ix][iy].creature->directionX == 1 && board[ix][iy].creature->directionY == -1) {//方向が斜め右上のとき
				//	directionNum = NE;
				//}
				//if (board[ix][iy].creature->directionX == 1 && board[ix][iy].creature->directionY == 0) {//方向が右のとき
				//	directionNum = EE;
				//}
				//if (board[ix][iy].creature->directionX == 1 && board[ix][iy].creature->directionY == 1) {//方向が斜め右下のとき
				//	directionNum = SE;
				//}
				//if (board[ix][iy].creature->directionX == 0 && board[ix][iy].creature->directionY == 1) {//方向が下のとき
				//	directionNum = SS;
				//}
				//if (board[ix][iy].creature->directionX == -1 && board[ix][iy].creature->directionY == 1) {//方向が斜め左下のとき
				//	directionNum = SW;
				//}
				//if (board[ix][iy].creature->directionX == -1 && board[ix][iy].creature->directionY == 0) {//方向が左のとき
				//	directionNum = WW;
				//}
				Direction directionNum;
				directionNum = board[ix][iy].creature->GETdirection();
				h = handle[board[ix][iy].creature->team][board[ix][iy].creature->status][directionNum];


				if (board[ix][iy].creature->status != EMPEROR && board[ix][iy].creature->HP < board[ix][iy].creature->HP_Limit) {
					hHP = HandleHP;
					HPexhibitOrNot = TRUE;
				}
			}
			//LoadGraphScreen(0, 0, "back.png", TRUE);
			DrawGraph(ix * 48, iy * 48, h, TRUE);//一度クラスの変数に格納したHandleで描画
			//DrawString(450, 20, msg.c_str(), WHITE);

			if (HPexhibitOrNot == TRUE) {
				DrawGraph(ix * 48 + 5, iy * 48 + 29, hHP, TRUE);
				DrawBox(ix * 48 + 16, iy * 48 + 31, ix * 48 + 16 + board[ix][iy].creature->HP / 2, iy * 48 + 36, GetColor(45, 205, 50), TRUE);
			}

		}
	}
	exhibitStatusMsg();//キャラクタ0のメッセージを代入。
	DrawString(800, 20, mainMsg.c_str(), WHITE);
	DrawString(800, 130, actionMsg.c_str(), GetColor(255, 200, 255));
	actionMsg = "";
}











Direction GETdirectionBYxy(int x, int y) {
	if (x == -1) {
		if (y == -1)return NW;
		if (y == 0)return WW;
		if (y == 1)return SW;
	}
	if (x == 0) {
		if (y == -1)return NN;
		if (y == 1)return SS;
	}
	if (x == 1) {
		if (y == -1)return NE;
		if (y == 0)return EE;
		if (y == 1)return SE;
	}
}

void GETxyBYdirection(int* x, int* y, Direction drctn) {
	switch (drctn) {
	case NW:
		*x = -1;
		*y = -1;
		break;
	case NN:
		*x = 0;
		*y = -1;
		break;
	case NE:
		*x = 1;
		*y = -1;
		break;
	case EE:
		*x = 1;
		*y = 0;
		break;
	case SE:
		*x = 1;
		*y = 1;
		break;
	case SS:
		*x = 0;
		*y = 1;
		break;
	case SW:
		*x = -1;
		*y = 1;
		break;
	case WW:
		*x = -1;
		*y = 0;
		break;
	}
}










//
//void RandomDirection(int* tmpx, int* tmpy) {//周囲8方向を調べる際の順番をランダムにする。８個入る配列の入れ替え。
//
//	for (int i = 0; i < 8; i++) {//８方向調べる。これなんでswitch使うとi==7の場合しか発動しないの？←ブレイクを書いていなかったから。
//
//		switch (i) {
//		case 0:
//			*tmpx = -1;
//			*tmpy = -1;
//			break;
//		case 1:
//			*tmpx = 0;
//			*tmpy = -1;
//			break;
//		case 2:
//			*tmpx = 1;
//			*tmpy = -1;
//			break;
//		case 3:
//			*tmpx = 1;
//			*tmpy = 0;
//			break;
//		case 4:
//			*tmpx = 1;
//			*tmpy = 1;
//			break;
//		case 5:
//			*tmpx = 0;
//			*tmpy = 1;
//			break;
//		case 6:
//			*tmpx = -1;
//			*tmpy = 1;
//			break;
//		case 7:
//			*tmpx = -1;
//			*tmpy = 0;
//			break;
//		}
//	}