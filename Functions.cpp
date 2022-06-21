#include "DxLib.h"
#include <string>
#include <iostream>
#include "DxLib.h"
#include "consts.h"
#include "externs.h"
#include "MyClasses.h"
#include <vector>

using std::to_string;






void exhibitStatusMsg(Emperor* handledCharacters) {//動かせるキャラクタのステータス情報を表示する。

	string CharacterStatusMsg;

	string HP_Msg = "";
	string staminaMsg = "";
	int exhibitY = 600;
	for (int i = 0; i < CHARACTERNUM; i++) {

		DrawBox(830, 300 + i * 100, 1150, 385 + i * 100, GetColor(240, 230, 140), TRUE);

		DrawGraph(832, 305 + i * 100, handle[handledCharacters[i].team][handledCharacters[i].status][5], TRUE);


		string numHP;
		numHP = (to_string(handledCharacters[i].HP));
		string numHP_Limit;
		numHP_Limit = (to_string(handledCharacters[i].HP_Limit));
		string numLevel;
		numLevel = (to_string(handledCharacters[i].levelUp));
		string numExp;
		numExp = (to_string(handledCharacters[i].expPoint));
		string atta;
		atta = (to_string(handledCharacters[i].attackPower));
		string defe;
		defe = (to_string(handledCharacters[i].defensePower));
		string neededExp;
		neededExp = (to_string(handledCharacters[i].levelUp * 100 / 3 + 150));

		CharacterStatusMsg = handledCharacters[i].name + "      Lv." + numLevel + "\n 状態 HP : " + numHP + " / " + numHP_Limit + "\n 攻撃力：" + atta + "   防御力：" + defe + "\n 経験値：" + numExp + " / " + neededExp;




		DrawString(880, 305 + i * 100, CharacterStatusMsg.c_str(), GetColor(20, 0, 0));



		exhibitY = exhibitY + 90;
	}

}





void exhibitScreen(int markX, int markY, bool attention, Grid** board, Emperor* handledCharacters) {//ペンギンを描画（ステータスと向きからペンギンの適切な画像のハンドルを入手し格納してから描画）
	int h;//ハンドル格納用
	string turn = "";
	bool HPexhibitOrNot;
	ClearDrawScreen();//一度画面を全消し
	//DrawGraph(0, 0, HandleBoard, TRUE);

	if (attention == TRUE) {//注目対象キャラのマスに注目用の円を表示するか否か
		DrawBox(markX * 48 + 2, markY * 48 + 2, markX * 48 + 46, markY * 48 + 46, GetColor(255, 200, 0), TRUE);
	}



	for (int ix = 0; ix < FIELDSIZE + 1; ix++) {
		for (int iy = 0; iy < FIELDSIZE + 1; iy++) {
			/*if (board[ix][ iy].state == ROCK) {
				DrawBox(ix * SQUARESIZE, iy * SQUARESIZE, ix * SQUARESIZE + 47, iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}
			if (board[ix][iy].state == CASTLE) {
				DrawGraph( ix * SQUARESIZE,  iy * SQUARESIZE, HandleCastle, TRUE);
			}*/

			/*if (board[GameBuf->exhibitX / 48 + ix][GameBuf->exhibitY / 48 + iy].state == ROCK) {
				DrawBox(GameBuf->exhibitX / 48 + ix * SQUARESIZE, GameBuf->exhibitY / 48 + iy * SQUARESIZE, GameBuf->exhibitX / 48 + ix * SQUARESIZE + 47, GameBuf->exhibitY / 48 + iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}
			if (board[ix][iy].state == CASTLE) {
				DrawGraph(GameBuf->exhibitX / 48 + ix * SQUARESIZE, GameBuf->exhibitY / 48 + iy * SQUARESIZE, HandleCastle, TRUE);
			}*/

			if (board[ix][ iy].state == ROCK) {
				DrawBox(-GameBuf->exhibitX + ix * SQUARESIZE, -GameBuf->exhibitY+ iy * SQUARESIZE, -GameBuf->exhibitX+ ix * SQUARESIZE + 47, -GameBuf->exhibitY + iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}
			if (board[ix][iy].state == CASTLE) {
				DrawGraph(-GameBuf->exhibitX  + ix * SQUARESIZE, -GameBuf->exhibitY  + iy * SQUARESIZE, HandleCastle, TRUE);
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


				if (board[ix][iy].creature->HP < board[ix][iy].creature->HP_Limit) {
					HPexhibitOrNot = TRUE;
				}
			}
			//LoadGraphScreen(0, 0, "back.png", TRUE);
			DrawGraph(ix * SQUARESIZE, iy * SQUARESIZE, h, TRUE);//一度クラスの変数に格納したHandleで描画
			//DrawString(450, 20, msg.c_str(), WHITE);

			if (HPexhibitOrNot == TRUE) {
				DrawGraph(ix * SQUARESIZE + 5, iy * SQUARESIZE + 29, hHP, TRUE);
				DrawBox(ix * SQUARESIZE + 16, iy * SQUARESIZE + 31, ix * SQUARESIZE + 16 + board[ix][iy].creature->HP / 2, iy * SQUARESIZE + 36, GetColor(45, 205, 50), TRUE);
			}

		}
	}
	DrawString(FIELDSIZE * SQUARESIZE + 5, 20, mainMsg.c_str(), WHITE);
	DrawString(FIELDSIZE * SQUARESIZE + 5, 170, actionMsg.c_str(), GetColor(255, 200, 255));

	turn = "現在のターン:" + std::to_string(turnNum) + "   現在のスコア:" + std::to_string(score);
	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turn.c_str(), GetColor(255, 200, 255));
	actionMsg = "";

	exhibitStatusMsg(handledCharacters);

	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 80, std::to_string(GameBuf->exhibitX).c_str(), GetColor(255, 200, 255));
	DrawString(FIELDSIZE * SQUARESIZE + 100, FIELDSIZE * SQUARESIZE - 80, std::to_string(GameBuf->exhibitY).c_str(), GetColor(255, 200, 255));
}
















void exhibitDamage(int markX, int markY, int damageX, int damageY, bool attention, int damageHP, Grid** board, Emperor* handledCharacters) {

	Creature* damaged = board[damageX][damageY].creature;//被ダメージ側を一時保存。
	board[damageX][damageY].creature = NULL;//一旦その場にキャラがいないことにする。

	Creature substitute = *damaged;//被ダメージ側の身代わりを作る。
	substitute.HP += damageHP;//身代わりは、体力満タンとして扱う。

	int damaging = 0;//繰り返しにより減り続けるメーターのHP値。

	//int damagedHP = damaged->HP;//被ダメージ側のHPを一時保存。

	for (int i = 0; i < damageHP + 5; i++) {
		if (i % 5 == 0) {
			board[damageX][damageY].creature = NULL;//4の倍数ごとにチカチカ切り替え。
		}
		if (i % 5 == 3) {
			board[damageX][damageY].creature = &substitute;
		}


		if (damaging < damageHP) {
			damaging += 1;
		}
		exhibitScreen(markX, markY, TRUE, board, handledCharacters);
		DrawGraph(damageX * SQUARESIZE + 5, damageY * SQUARESIZE + 29, hHP, TRUE);
		DrawBox(damageX * SQUARESIZE + 16, damageY * SQUARESIZE + 31, damageX * SQUARESIZE + 16 + (substitute.HP - damaging) / 2, damageY * SQUARESIZE + 36, GetColor(45, 205, 50), TRUE);

		WaitTimer(30);

		if (substitute.HP - damaging < 0) {
			break;
		}
	}
	board[damageX][damageY].creature = damaged;
}











void exhibitStatus(int markX, int markY, int statusX, int statusY, bool attention, int color, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
	exhibitScreen(markX, markY, attention, board, handledCharacters);
	string Msg = "";
	string Bulls = "";

	if (statusX < FIELDSIZE && statusY < FIELDSIZE) {



		if (markX == statusX && markY == statusY) {//ステータス表示キャラと操作可能キャラが同じだった場合、行動選択の表示を行う。


			string Msg1 = "";
			string Msg2 = "";

			DrawBox(markX * 48 + 40, markY * 48 + 2, markX * 48 + 360, markY * 48 + 46, GetColor(225, 200, 0), TRUE);//外側のボックス
			DrawBox(markX * 48 + 39, markY * 48 + 1, markX * 48 + 361, markY * 48 + 47, GetColor(125, 0, 0), FALSE);//外側のボックスの縁

			for (int iii = 0; iii < 6; iii++) {
				DrawBox(markX * 48 + 50 + iii * 51, markY * 48 + 24, markX * 48 + 85 + iii * 51, markY * 48 + 43, GetColor(50 + ((color + iii * 3) / 10), 220 + iii * 5 - (color / 3), 100), TRUE);//選択ボックス


			}

			Msg1 = board[markX][markY].creature->name + "のHP:" + std::to_string(board[markX][markY].creature->HP) + "/" + std::to_string(board[markX][markY].creature->HP_Limit) + "   素早さ値:" + std::to_string(board[markX][markY].creature->speed);
			Msg2 = " 歩く　産卵　孵化　攻撃　押す　パス";

			DrawString(markX * 48 + 42, markY * 48 + 5, Msg1.c_str(), GetColor(0, 10, 55));
			DrawString(markX * 48 + 42, markY * 48 + 26, Msg2.c_str(), GetColor(0, 10, 55));

			WaitTimer(10);

		}
		else {

			DrawBox(statusX * 48 + 40, statusY * 48 + 5, statusX * 48 + 300, statusY * 48 + 43, GetColor(225, 200, 0), TRUE);
			DrawBox(statusX * 48 + 40, statusY * 48 + 5, statusX * 48 + 300, statusY * 48 + 43, GetColor(125, 000, 0), FALSE);

			Msg = board[statusX][statusY].creature->name + "  HP:" + to_string(board[statusX][statusY].creature->HP) + "/" + to_string(board[statusX][statusY].creature->HP_Limit) + "　 Lv." + to_string(board[statusX][statusY].creature->levelUp) + "\n素早さ:" + to_string(board[statusX][statusY].creature->speed) + "  攻撃:" + (to_string(board[statusX][statusY].creature->attackPower)) + "  防御:" + to_string(board[statusX][statusY].creature->defensePower);

			DrawString(statusX * 48 + 42, statusY * 48 + 7, Msg.c_str(), GetColor(0, 10, 55));


		}




		////以下、モブ配列がバグっているので調査
		//DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 235, "mobs_PenguinKids", GetColor(255, 200, 255));
		//for (int i = 0; i < 12; i++) {
		//	Bulls = std::to_string(mobs_PenguinKids[i].num) + " X:" + std::to_string(mobs_PenguinKids[i].x) + " Y:" + std::to_string(mobs_PenguinKids[i].y);
		//	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 220 + i*13, Bulls.c_str(), GetColor(255, 200, 255));
		//	DrawString(FIELDSIZE * SQUARESIZE + 100, FIELDSIZE * SQUARESIZE - 220 + i * 13, mobs_PenguinKids[i].name.c_str(), GetColor(255, 200, 255));
		//}
		//DrawString(FIELDSIZE * SQUARESIZE + 200, FIELDSIZE * SQUARESIZE - 235, "mobs_Bull", GetColor(255, 200, 255));
		//for (int i = 0; i < 12; i++) {
		//	Bulls = std::to_string(mobs_Bull[i].num) + " X:" + std::to_string(mobs_Bull[i].x) + " Y:" + std::to_string(mobs_Bull[i].y);
		//	DrawString(FIELDSIZE * SQUARESIZE + 200, FIELDSIZE * SQUARESIZE - 220 + i * 13, Bulls.c_str(), GetColor(255, 200, 255));
		//	DrawString(FIELDSIZE * SQUARESIZE + 295, FIELDSIZE * SQUARESIZE - 220 + i * 13, mobs_Bull[i].name.c_str(), GetColor(255, 200, 255));
		//}


	}
}







void exhibitRolling(int kickX, int kickY, int dx, int dy, int distance, Grid** board, Emperor* handledCharacters) {

	Creature* kicked = board[kickX + dx][kickY + dy].creature;//蹴られた卵のポインタを仮置き場に代入し保持。
	int handleEgg = handle[board[kickX + dx][kickY + dy].creature->team][EGG][NW];
	board[kickX + dx][kickY + dy].creature = NULL;
	for (int i = 0; i < distance * SQUARESIZE / 4; i = i++) {

		exhibitScreen(kickX, kickY, TRUE, board, handledCharacters);
		DrawGraph((kickX + dx) * SQUARESIZE + (i * 4 * dx), (kickY + dy) * SQUARESIZE + (i * 4 * dy), handleEgg, TRUE);
		//WaitTimer(2);
		ScreenFlip(); //裏画面を表画面に反映
	}

	board[kickX + dx][kickY + dy].creature = kicked;//元の位置にポインタを戻す。
}





void exhibitRule() {

	string rule1 = "ペンギンロボットバトル・ルールブック\n\n 皇帝ペンギンをを動かして、城を守れ！\n 敵に城を壊されたらゲームオーバー！\n\nターンについて：\n  盤面上の全てのキャラクタは、素早さ順に行動するぞ！";
	string rule2 = "行動について: \n  歩く:\n　　皇帝ペンギンは3歩まで歩ける。\n　産卵：\n　　向いている方向にクローンペンギンの卵を産む。";
	string rule3 = "　孵化：\n　　向いている方向にいる卵を孵化させる。\n　　クローンは自分と同じ色の卵だけ孵化させる。\n　　生まれた子は孵化させたペンギンと同じ方向を向く。";
	string rule4 = "\n　攻撃：\n　　向いている方向にいるキャラクタにダメージを与える。\n　蹴る：\n　　卵を蹴るとペンギンにぶつかるまで真っすぐ転がる。\n　　クローンペンギンを蹴ると、蹴った側と同じ方向を向く。";
	string rule5 = "クローンペンギンについて:\n  クローンは歩けない。産卵と攻撃と孵化を行う。\n　クローンペンギンには、「卵・若者・老人」の3つの状態がある。\n　　若者：卵を産む前の状態。向いている方向に産卵しようとする。\n　　老人：卵を産むと老人になる。\n　　　　　周囲に敵がいれば攻撃し、卵があれば孵化させる。\n\n\n\nEsc:ルールを閉じる";


	DrawBox(550, 30, 1150, 1150, GetColor(173, 255, 47), TRUE);
	DrawBox(550, 30, 1150, 1150, GetColor(130, 0, 0), FALSE);
	DrawString(560, 50, rule1.c_str(), GetColor(0, 40, 55));
	DrawString(560, 250, rule2.c_str(), GetColor(0, 40, 55));
	DrawString(560, 340, rule3.c_str(), GetColor(0, 40, 55));
	DrawString(560, 400, rule4.c_str(), GetColor(0, 40, 55));
	DrawString(560, 550, rule5.c_str(), GetColor(0, 40, 55));
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