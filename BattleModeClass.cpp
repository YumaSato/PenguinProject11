#include "DxLib.h"
#include <iostream>
#include <string>
#include <vector>
#include "MyClasses.h"
#include "consts.h"
#include "externs.h"

#include <algorithm>
#include <functional>

#include <cstdlib>
#include <ctime>

using namespace std;



void turnFinal();//ターンの最後にまとめて行われる操作。

void enemyEnter(int turn);//敵が襲来する動作。
void yieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy);

bool speedOrder(Creature* a, Creature* b);






BattleMode_GameManager::BattleMode_GameManager() {//コンストラクタ。
	turnNum = 0;
	

	for (int i = 0; i < FIELDSIZE; i++) {
		board[i][0].state = ROCK;
		board[i][FIELDSIZE -1].state = ROCK;
		board[0][i].state = ROCK;
		board[FIELDSIZE - 1][i].state = ROCK;

		board[CASTLE_X][CASTLE_Y].state = CASTLE;
	}
}



bool BattleMode_GameManager::BattleMode() {

	//string turnF = "";

	Emperor Emperor1(red, 0);//インスタンス化
	handledCharacters[0] = &Emperor1;
	Emperor Emperor2(blue, 1);//インスタンス化
	handledCharacters[1] = &Emperor2;

	DrawGraph(0, 0, HandleBoard, TRUE);
	WaitKey();
	gameMode = 1;

	while (gameMode == 1) {
		if (Emperor1.HP > 0) {
			Emperor1.selectAction();
		}
		if (Emperor2.HP > 0) {
			Emperor2.selectAction();
		}

		if (Emperor1.HP <= 0 && Emperor2.HP <= 0 ) {
			mainMsg = "ゲームオーバー";
			actionMsg = "ゲームを終了します。";
			exhibitScreen();
			WaitKey();
			return FALSE;
		}

		turnFinal();

		if (Emperor1.HP <= 0 && Emperor2.HP <= 0 || board[CASTLE_X][CASTLE_Y].state == VACANT) {
			mainMsg = "ゲームオーバー";
			actionMsg = "ゲームを終了します。";
			exhibitScreen();
			WaitKey();
			return FALSE;
		}
		

		enemyEnter(turnNum);
		turnNum += 1;
		exhibitScreen();
		/*turnF = "現在のターン:" + std::to_string(turnNum);
		DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turnF.c_str(), GetColor(255, 200, 255));
		WaitKey();*/


	}
}















void turnFinal() {//素早さ順にmobが行動していく関数。
	string mobStatusMsg;
	string numSpeed;
	string numX;
	string numY;
	string s = "";
	string allS = "";
	//Creature* mobsSpeedOrder[2048];
	bool moveOrNot = FALSE;

	int mobNumberNow;
	mobNumberNow = mobNumber;//このターンで実行するペンギンキッズ行動の回数を入れるローカル変数に、ターン末尾行動開始時点でのモブ数を代入。
	//これにより実行中にモブ数が増えてループ中にループ回数が変わりバグが発生することを防げる。多分。

	for (int i = 0; i < num_penguinKids; i++) {//いったん代入する。
		mobsSpeedOrder[i] = &mobs_PenguinKids[i];

	}
	for (int i = 0; i < num_bull; i++) {
		mobsSpeedOrder[i + num_penguinKids] = &mobs_Bull[i];//mobs_PenguinKidsの中身を入れ終わったら、その後ろにbullポインタ配列の中身も入れていく。
	}



	//
	//for (int i = 0; i < mobNumber; i++) {
	//	s += "アドレス" + to_string(mobsSpeedOrder[i]->speed);//素早さ順アドレス配列のスピードを表示。
	//}
	//DrawString(800, 570, s.c_str(), WHITE);
	//WaitKey();

	sort(mobsSpeedOrder, mobsSpeedOrder + mobNumber, speedOrder);

	s = "";
	for (int i = 0; i < mobNumber; i++) {
		if (mobsSpeedOrder[i]->speed > 0) {
			s = "X" + std::to_string(mobsSpeedOrder[i]->x) + "Y" + std::to_string(mobsSpeedOrder[i]->y) + "の素早さ:" + to_string(mobsSpeedOrder[i]->speed) + " \n";//素早さ順アドレス配列のスピードを表示。
			allS += s;
		}
	}
	exhibitScreen();
	DrawString(FIELDSIZE * SQUARESIZE, 570, allS.c_str(), WHITE);
	WaitKey();








	for (int i = 0; i < mobNumberNow; i++) {

		//if (mobsspeedorder[i] == null) {
		//	continue;
		//}
		if (mobsSpeedOrder[i] == NULL) {//スピード順配列にもう何もなければ終了。
			return;
		}
		if (mobsSpeedOrder[i]->speed < 0) {//スピードがマイナス、つまり死んでいたら終了。
			return;
		}


		//if (mobsSpeedOrder[i]->pass == TRUE) {//キャラは居るけど行動しない状態であればコンティニュー。
		//	continue;
		//}

		if (mobsSpeedOrder[i]->status == NORMAL || mobsSpeedOrder[i]->status == ELDER) {//普通or老人ペンギンならペンギンのselectActionを呼ぶ。
			moveOrNot = reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction();
		}
		if (mobsSpeedOrder[i]->status == BULL) {//普通or老人ペンギンならペンギンのselectActionを呼ぶ。
			moveOrNot = reinterpret_cast<Bull*>(mobsSpeedOrder[i])->selectAction();
		}


		if (moveOrNot == TRUE) {//もし行動が行われていたら
			exhibitScreen();
			numSpeed = (to_string(mobsSpeedOrder[i]->speed));
			numX = (to_string(mobsSpeedOrder[i]->x));
			numY = (to_string(mobsSpeedOrder[i]->y));
			mobStatusMsg = "X:" + numX + ",Y:" + numY + "の" + mobsSpeedOrder[i]->name + "\n 行動速度:" + numSpeed + " 体力:" + to_string(mobsSpeedOrder[i]->HP) + "/" + to_string(mobsSpeedOrder[i]->HP_Limit);
			DrawString(FIELDSIZE * SQUARESIZE, 160, mobStatusMsg.c_str(), WHITE);
			WaitKey();
		}
	}

}












bool speedOrder(Creature* a, Creature* b) {

	if (a->speed == NULL) {
		a->speed = -1;
	}
	if (b->speed == NULL) {
		b->speed = -1;
	}
	return a->speed > b->speed;
}


//bool speedOrder(Creature* a, Creature* b) {
//	if (a->speed == b->speed) {
//		return a->speed < b->speed;
//	}
//	else {
//		return a->speed > b->speed;
//	}	
//}












void enemyEnter(int turn) {//どのターンで敵が出現するかを決める。
	int side = 0;
	int place = 0;

	if (turn == 1) {//１ターン目から、敵が出現しない側を決定する。
		randomSide = GetRand(3);
	}
	if (turn == 14) {//敵が出現しない側を決定する。
		randomSide = GetRand(2);
	}


	if (1 < turn && turn < 25) {
		if (turn % 5 == 2 || turn % 5 == 4 || turn == 10 || turn == 15 ) {

			side = GetRand(2);
			if (side <= randomSide) {//ランダムでとってきたsideの値が、敵出現なし側、つまり-1と定められてたら、方向番号を1増やす。
				side += 1;
			}

			place = GetRand(FIELDSIZE - 3);

			if (side == 0) {
				yieldEnemy(BULL, blue, 0, 1, place + 1, 0);
			}
			if (side == 1) {
				yieldEnemy(BULL, blue, 0, -1, place + 1, FIELDSIZE - 1);
			}
			if (side == 2) {
				yieldEnemy(BULL, blue, 1, 0, 0, place + 1);
			}
			if (side == 3) {
				yieldEnemy(BULL, blue, -1, 0, FIELDSIZE - 1, place + 1);
			}
		}
	}

	if (turn == 20 || turn == 25) {
		side = GetRand(3);
		place = GetRand(FIELDSIZE - 3);
		if (side == 0) {
			yieldEnemy(BULL, blue, 0, 1, place + 1, 0);
		}
		if (side == 1) {
			yieldEnemy(BULL, blue, 0, -1, place + 1, FIELDSIZE - 1);
		}
		if (side == 2) {
			yieldEnemy(BULL, blue, 1, 0, 0, place + 1);
		}
		if (side == 3) {
			yieldEnemy(BULL, blue, -1, 0, FIELDSIZE - 1, place + 1);
		}

	}









	if (turn == 22) {//敵が出現する側を決定する。1つの方向から集中攻撃がくるぞ！
		randomSide = GetRand(3);
	}
	if (22 < turn && turn < 28) {

		place = GetRand(FIELDSIZE - 3);
		if (randomSide == 0) {
			yieldEnemy(BULL, red, 0, 1, place + 1, 0);
		}
		if (randomSide == 1) {
			yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1);
		}
		if (randomSide == 2) {
			yieldEnemy(BULL, red, 1, 0, 0, place + 1);
		}
		if (randomSide == 3) {
			yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1);
		}
	}

}






void yieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy) {

	if (enemyType == BULL) {
		Bull bull = Bull();
		bull.setMobs(enemyTeam, dx, dy, cx, cy, 400000);
		mobs_Bull[num_bull] = bull;
		board[cx][cy].creature = &mobs_Bull[num_bull];
		mobNumber += 1;
		num_bull += 1;

	}



}