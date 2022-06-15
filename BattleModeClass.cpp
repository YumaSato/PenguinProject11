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



bool turnFinal(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Emperor* handledCharacters);//ターンの最後にまとめて行われる操作。

void enemyEnter(int turn, int level, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Emperor* handledCharacters);//敵が襲来する動作。
void yieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Emperor* handledCharacters);
bool ending();




bool speedOrder(Creature* a, Creature* b);






BattleMode_GameManager::BattleMode_GameManager() {//コンストラクタ。
	turnNum = 0;

	/*for (int i = 0; i < CHARACTERNUM; i++) {
		handledCharacters[i] = NULL;
	}*/
	Emperor* Emperor1 = new Emperor();//インスタンス化
	Emperor1->setMobs(red, 1, 0, 1, 0, 0, 0, board, handledCharacters);
	handledCharacters[0] = *Emperor1;
	board[Emperor1->x][Emperor1->y].creature = &handledCharacters[0];//マス目に自分のポインタを代入。
	delete Emperor1;

	Emperor* Emperor2 = new Emperor();//インスタンス化
	Emperor2->setMobs(blue, 2, 0, 0, 1, 0, 0, board, handledCharacters);
	handledCharacters[1] = *Emperor2;
	board[Emperor2->x][Emperor2->y].creature = &handledCharacters[1];
	delete Emperor2;



}




int BattleMode_GameManager::BattleMode(int level) {

	//string turnF = "";





	for (int i = 0; i < FIELDSIZE; i++) {
		board[i][0].state = ROCK;
		board[i][FIELDSIZE - 1].state = ROCK;
		board[0][i].state = ROCK;
		board[FIELDSIZE - 1][i].state = ROCK;
		board[CASTLE_X][CASTLE_Y].state = CASTLE;
	}



	//handledCharacters[0].specialMovement1(FIELDSIZE, mobs_PenguinKids, mobs_Bull, board, handledCharacters);

	int actionReturn = 1;

	gameMode = 1;

	while (gameMode == 1) {


		for (int i = 0; i < CHARACTERNUM; i++) {
			if (handledCharacters[i].HP > 0) {
				actionReturn = handledCharacters[i].selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);
				if (actionReturn == 0) {
					return 0;
				}
				if (actionReturn == 2) {
					return 2;
				}
			}
		}





		//if (Emperor1.HP > 0) {
		//	actionReturn = Emperor1.selectAction(mobs_PenguinKids, mobs_Bull, board, *handledCharacters);
		//	if (actionReturn ==0) {
		//		return 0;
		//	}
		//	if (actionReturn == 2) {
		//		return 2;
		//	}

		//}
		//if (Emperor2.HP > 0) {
		//	actionReturn = Emperor2.selectAction(mobs_PenguinKids, mobs_Bull, board, *handledCharacters);
		//	if (actionReturn == 0) {
		//		return 0;//ゲーム直接終了
		//	}
		//	if (actionReturn == 2) {
		//		return 2;//タイトル画面に戻る
		//	}
		//}

		if ((handledCharacters[0].HP <= 0 && handledCharacters[1].HP <= 0) || board[CASTLE_X][CASTLE_Y].state == VACANT) {
			mainMsg = "ゲームオーバー";
			actionMsg = "Escを押すと、ゲームを終了します。";
			exhibitScreen(0, 0, FALSE, board, handledCharacters);
			WaitKey();
			while (1) {
				if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
					return FALSE;
				}

				if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
					return FALSE;
				}
				WaitTimer(10);
			}
			return FALSE;
		}

		if ((level == 0 && turnNum == 60) || (level == 1 && turnNum == 100)) {
			mainMsg = std::to_string(turnNum) + "ターン生き延びた！ ゲームクリア！ \nおめでとう！";
			actionMsg = "戦わされた子ペンギンの数:" + std::to_string(num_penguinKids) + "\nモンスターの総数:" + std::to_string(num_bull);
			exhibitScreen(0, 0, FALSE, board, handledCharacters);
			WaitKey();
			if (ending() == FALSE) {
				return FALSE;
			}

			exhibitScreen(0, 0, FALSE, board, handledCharacters);
			WaitKey();
		}


		mainMsg = "";
		if (turnFinal(mobs_PenguinKids, mobs_Bull, board, handledCharacters) == FALSE) {
			return FALSE;
		}

		if ((handledCharacters[0].HP <= 0 && handledCharacters[1].HP <= 0) || board[CASTLE_X][CASTLE_Y].state == VACANT) {
			mainMsg = "ゲームオーバー";
			actionMsg = "Escを押すと、ゲームを終了します。";
			exhibitScreen(0, 0, FALSE, board, handledCharacters);
			WaitKey();
			while (1) {
				if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
					return FALSE;
				}

				if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
					return FALSE;
				}
				WaitTimer(10);
			}
			return FALSE;
		}


		enemyEnter(turnNum, level, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		turnNum += 1;
		exhibitScreen(0, 0, FALSE, board, handledCharacters);
		/*turnF = "現在のターン:" + std::to_string(turnNum);
		DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turnF.c_str(), GetColor(255, 200, 255));
		WaitKey();*/


	}
}















bool turnFinal(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Emperor* handledCharacters) {//素早さ順にmobが行動していく関数。
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

	for (int i = 0; i < mobNumberNow; i++) {

		if (mobsSpeedOrder[i] == NULL) {//スピード順配列にもう何もなければ終了。
			return TRUE;
		}
		if (mobsSpeedOrder[i]->speed < 0) {//スピードがマイナス、つまり死んでいたら終了。
			return TRUE;
		}


		//if (mobsSpeedOrder[i]->pass == TRUE) {//キャラは居るけど行動しない状態であればコンティニュー。
		//	continue;
		//}

		if (mobsSpeedOrder[i]->status == NORMAL || mobsSpeedOrder[i]->status == ELDER) {//普通or老人ペンギンならペンギンのselectActionを呼ぶ。
			moveOrNot = reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);


			//渡すべき引数、下の二つのうちどっちが正しんだ！？！？
			//&mobs_PenguinKids[mobLimit], & mobs_Bull[mobLimit]
			//mobs_PenguinKids, mobs_Bull
		}



		if (mobsSpeedOrder[i]->status == BULL) {//普通or老人ペンギンならペンギンのselectActionを呼ぶ。
			moveOrNot = reinterpret_cast<Bull*>(mobsSpeedOrder[i])->selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}

		if (quitGame == TRUE) {
			return FALSE;
		}

	}
	return TRUE;

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












void enemyEnter(int turn, int level, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Emperor* handledCharacters) {//どのターンで敵が出現するかを決める。
	int side = 0;
	int place = 0;

	if (turn == 0) {//１ターン目から、敵が出現しない側を決定する。
		randomSide = GetRand(3);
	}
	if (turn == 14) {//敵が出現しない側を決定する。
		randomSide = GetRand(3);
	}
	if (turn == 40) {//敵が出現しない側を決定する。
		randomSide = GetRand(3);
	}


	if ((1 < turn && turn < 25) || (36 < turn && turn < 50)) {
		if ((turn % 3 == 2 || turn % 3 == 0) || turn == 8) {

			side = GetRand(2);
			if (side >= randomSide) {//ランダムでとってきたsideの値が、敵出現なし側、つまり-1と定められてたら、方向番号を1増やす。
				side += 1;
			}

			place = GetRand(FIELDSIZE - 3);

			if (side == 0) {
				yieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}
			if (side == 1) {
				yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}
			if (side == 2) {
				yieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}
			if (side == 3) {
				yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}
		}
	}

	if ((turn % 2 == 0 && turn > 16 && turn < 25) || (turn % 3 == 2 && turn > 30)) {

		side = GetRand(3);
		place = GetRand(FIELDSIZE - 3);
		if (side == 0) {
			yieldEnemy(BULL, blue, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 1) {
			yieldEnemy(BULL, blue, 0, -1, place + 1, FIELDSIZE - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 2) {
			yieldEnemy(BULL, blue, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 3) {
			yieldEnemy(BULL, blue, -1, 0, FIELDSIZE - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
	}




	if (turn % 8 == 6 && level == 1) {

		side = GetRand(3);
		place = GetRand(FIELDSIZE - 3);
		if (side == 0) {
			yieldEnemy(BULL, blue, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 1) {
			yieldEnemy(BULL, blue, 0, -1, place + 1, FIELDSIZE - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 2) {
			yieldEnemy(BULL, blue, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 3) {
			yieldEnemy(BULL, blue, -1, 0, FIELDSIZE - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
	}




	//yieldEnemy(BULL, blue, 1, 0, 0, 5);
	//yieldEnemy(BULL, red, 1, 0, 0, 5);

	//yieldEnemy(BULL, blue, 0, -1, 5, FIELDSIZE -1);
	//yieldEnemy(BULL, red, 0, -1, 5, FIELDSIZE - 1);




	if (turn == 28) {//敵が出現する側を決定する。1つの方向から集中攻撃がくるぞ！
		randomSide = GetRand(3);
	}
	if ((28 < turn && turn < 34) || turn == 9) {

		place = GetRand(FIELDSIZE - 3);
		if (randomSide == 0) {
			yieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (randomSide == 1) {
			yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (randomSide == 2) {
			yieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (randomSide == 3) {
			yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
	}




	if ((turn % 5 == 0 && turn > 12) || turn == 16) {//普通に赤が来る。半分の確率で反対側からも来る。
		side = GetRand(3);
		place = GetRand(FIELDSIZE - 3);
		if (side == 0) {
			yieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			place = GetRand(FIELDSIZE - 3);
			yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 1) {
			yieldEnemy(BULL, red, 0, -1, place + 1, FIELDSIZE - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 2) {
			yieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			place = GetRand(FIELDSIZE - 3);
			yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}
		if (side == 3) {
			yieldEnemy(BULL, red, -1, 0, FIELDSIZE - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters);
		}

	}



}







void yieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid board[][FIELDSIZE], Emperor* handledCharacters) {

	if (enemyType == BULL) {


		if (board[cx][cy].creature != NULL) {
			int rand = GetRand(1);
			if (cx == 0 || cx == FIELDSIZE - 1) {
				if (rand == 0) {
					cy += 1;
				}
				if (rand == 1) {
					cy -= 1;
				}
			}
			if (cy == 0 || cy == FIELDSIZE - 1) {
				if (rand == 0) {
					cx += 1;
				}
				if (rand == 1) {
					cx -= 1;
				}
			}
		}
		if (board[cx][cy].creature == NULL) {

			Bull bull = Bull();
			bull.setMobs(enemyTeam, dx, dy, cx, cy, turnNum / 10 + 1, 400000, board, handledCharacters);
			mobs_Bull[num_bull] = bull;
			board[cx][cy].creature = &mobs_Bull[num_bull];
			mobNumber += 1;
			num_bull += 1;
		}


	}



}












bool ending() {


	int height = FIELDSIZE * SQUARESIZE + 40;
	const int msgNum = 8;
	int msgCenter = (FIELDSIZE * 48 + 384) / 2;
	string endingMsg[8];
	endingMsg[0] = "PENGUIN ROBOT BATTLE!";
	endingMsg[1] = "2022";
	endingMsg[2] = "";
	endingMsg[3] = "企画:iwashi";
	endingMsg[4] = "ディレクター:iwashi";
	endingMsg[5] = "メインプログラム:iwashi";
	endingMsg[6] = "デザイナー:はぺぺ";
	endingMsg[7] = "スペシャルサンクス:dolpast";

	int DrawWidth[msgNum];
	int StrLen[msgNum];

	string quitMsg = "";

	ClearDrawScreen();

	for (int i = 0; i < msgNum; i++) {
		StrLen[i] = strlen(endingMsg[i].c_str());//文字数取得
		DrawWidth[i] = GetDrawStringWidth(endingMsg[i].c_str(), StrLen[i]);//文字幅取得
	}

	while (1) {
		ClearDrawScreen();
		for (int i = 0; i < msgNum; i++) {
			DrawString(msgCenter - DrawWidth[i] / 2, height + i * 100, endingMsg[i].c_str(), GetColor(210, 255, 250));

			if (DrawWidth[i] != 0) {
				DrawGraph(msgCenter - DrawWidth[i] / 2 - 78, height + i * 100 - 15, handle[blue][EGG][NW], TRUE);
				DrawGraph(msgCenter + DrawWidth[i] / 2 + 30, height + i * 100 - 15, handle[red][EGG][NW], TRUE);
			}
		}
		height--;
		WaitTimer(20);



		if (height < -720) {
			break;
		}
		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押される終了
			return FALSE;
		}
		if (CheckHitKey(KEY_INPUT_SPACE) == TRUE || CheckHitKey(KEY_INPUT_1) == TRUE) {
			height = height - 4;
		}


		ScreenFlip(); //裏画面を表画面に反映
	}




	quitMsg = "ゲームを終了しますか？ 1:Yes 2:No";
	DrawString(FIELDSIZE * SQUARESIZE + 5, 20, quitMsg.c_str(), WHITE);
	WaitKey();
	while (1) {
		if (CheckHitKey(KEY_INPUT_1) == TRUE) {//なぜ上下左右が逆なの？謎。
			quitMsg = "本当にゲームを終了してよろしいですか？ \n1:Yes 2:No";
			ClearDrawScreen();
			DrawString(FIELDSIZE * SQUARESIZE + 5, 20, quitMsg.c_str(), WHITE);
			WaitKey();
			while (1) {
				if (CheckHitKey(KEY_INPUT_1) == TRUE) {//なぜ上下左右が逆なの？謎。
					return FALSE;
				}
				if (CheckHitKey(KEY_INPUT_2) == TRUE) {//なぜ上下左右が逆なの？謎。
					break;
				}
				WaitTimer(10);
			}
		}
		if (CheckHitKey(KEY_INPUT_2) == TRUE) {//なぜ上下左右が逆なの？謎。
			break;
		}
		WaitTimer(10);
	}
	return TRUE;
}