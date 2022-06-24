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



//bool turnFinal(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);//ターンの最後にまとめて行われる操作。

//void enemyEnter(int turn, int level, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);//敵が襲来する動作。
//void YieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters);
bool ending();




bool speedOrder(Creature* a, Creature* b);






BattleMode_GameManager::BattleMode_GameManager(int stageLevel, int xSize, int ySize) {//コンストラクタ。
	turnNum = 0;

	board = new Grid * [xSize];

	for (int xi = 0; xi < xSize; xi++) {
		Grid* yGrid = new Grid[ySize];
		board[xi] = yGrid;//Gridがたの初期化
	}
	this->sizeX = xSize;
	this->sizeY = ySize;
	GameBuf = this;

	//board = new Grid * [xSize];

	//for (int yi = 0; yi < ySize; yi++) {
	//	Grid* yGrid = new Grid[ySize];
	//	board[yi] = yGrid;//Gridがたの初期化
	//}
	//this->sizeX = xSize;
	//this->sizeY = ySize;
	//GameBuf = this;





	/*for (int i = 0; i < CHARACTERNUM; i++) {
		handledCharacters[i] = NULL;
	}*/
	
	






	exhibitX = (handledCharacters[0].x - (FIELDSIZE - (FIELDSIZE /2))) * 48;//キャラ0から表示マスサイズの半分の距離だけ左上から表示。つまりキャラ0を中心に画面を描画。
	exhibitY = (handledCharacters[0].y - (FIELDSIZE - (FIELDSIZE /2))) * 48;
	if (exhibitX < 0) {
		exhibitX = 0;
	}
	if (exhibitX/48 + FIELDSIZE > sizeX) {
		exhibitX = (sizeX - FIELDSIZE)*48;
	}
	if (exhibitY < 0) {
		exhibitY = 0;
	}
	if (exhibitY/48 + FIELDSIZE > sizeY) {
		exhibitY = (sizeY - FIELDSIZE)*48;//描画マスの左上を示すexhibitXYが盤面上におけるマイナスや、描画マスの右下が盤面サイズをはみ出る場合、はみ出ない場所に再設定。
	}
}










BattleMode_GameManager::~BattleMode_GameManager() {
	//delete[][] board;


	for (int xi = 0; xi < sizeX; xi++) {//マス目を消す
		delete[] board[xi];
	}
	delete[] board;
	delete Emperor1;
	delete Emperor2;

	GameBuf = NULL;
};




int BattleMode_GameManager::BattleMode(int stageLevel) {

	//string turnF = "";



	castleX = sizeX / 2;
	castleY = sizeY / 2;

	for (int ix = 0; ix < sizeX; ix++) {
		for (int iy = 0; iy < sizeY; iy++) {
			board[ix][0].state = ROCK;
			board[ix][sizeY - 1].state = ROCK;
			board[0][iy].state = ROCK;
			board[sizeX - 1][iy].state = ROCK;
			board[castleX][castleY].state = CASTLE;
		}
	}
	Emperor1 = new Emperor();//インスタンス化
	Emperor1->setMobs(red, 1, 0, 1, 0, 0, 0, board, handledCharacters);
	handledCharacters[0] = *Emperor1;
	board[Emperor1->x][Emperor1->y].creature = &handledCharacters[0];//マス目に自分のポインタを代入。


	Emperor2 = new Emperor();//インスタンス化
	Emperor2->setMobs(blue, 2, 0, 0, 1, 0, 0, board, handledCharacters);
	handledCharacters[1] = *Emperor2;
	board[Emperor2->x][Emperor2->y].creature = &handledCharacters[1];







	int actionReturn = 1;//何が返ってくるか。0ならばゲーム終了。1は正常に行動を完了させたという意味。2はタイトルに戻る。
	gameMode = 1;
	while (gameMode == 1) {

		for (int i = 0; i < CHARACTERNUM; i++) {
			if (handledCharacters[i].HP > 0) {
				actionReturn = handledCharacters[i].selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);
				actionMsg = "";
				if (actionReturn == 0) {
					return 0;
				}
				if (actionReturn == 2) {
					return 2;
				}
			}
		}





		if ((handledCharacters[0].HP <= 0 && handledCharacters[1].HP <= 0) || board[castleX][castleY].state == VACANT) {
			if (GameOver() == 0) {//ゲームオーバー
				return 0;
			}
		}

		if ((stageLevel == 0 && turnNum == 60) || (stageLevel == 1 && turnNum == 100)) {//ゲームクリア
			if (GameClear() == 0) {
				return 0;
			}
		}


		mainMsg = "";
		if (TurnFinal() == FALSE) {
			return FALSE;
		}

		if ((handledCharacters[0].HP <= 0 && handledCharacters[1].HP <= 0) || board[castleX][castleY].state == VACANT) {
			mainMsg = "ゲームオーバー";
			actionMsg = "Escを押すと、ゲームを終了します。";
			exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
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


		if (EnemyEnter(turnNum, stageLevel, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) {
			return 0;
		}
		turnNum += 1;
		exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
		

	}
}






int  BattleMode_GameManager::GameClear() {
	mainMsg = std::to_string(turnNum) + "ターン生き延びた！ ゲームクリア！ \nおめでとう！";
	actionMsg = "戦わされた子ペンギンの数:" + std::to_string(num_penguinKids) + "\nモンスターの総数:" + std::to_string(num_bull);
	exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
	WaitKey();
	if (ending() == FALSE) {
		return FALSE;
	}

	exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
	WaitKey();

}

int  BattleMode_GameManager::GameOver() {

	mainMsg = "ゲームオーバー";
	actionMsg = "Escを押すと、ゲームを終了します。";
	exhibitScreen(0, 0, FALSE, FALSE, board, handledCharacters);
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













int  BattleMode_GameManager::TurnFinal() {//素早さ順にmobが行動していく関数。
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

		

		//if (mobsSpeedOrder[i] == NULL) {//スピード順配列にもう何もなければ終了。
		//	return TRUE;
		//}
		//if (mobsSpeedOrder[i]->speed < 0) {//スピードがマイナス、つまり死んでいたら終了。
		//	return TRUE;
		//}
		if (mobsSpeedOrder[i] != NULL && mobsSpeedOrder[i]->speed >= 0) {//モブがいるとき
			actionMsg = "";
			if (mobsSpeedOrder[i]->status == NORMAL || mobsSpeedOrder[i]->status == ELDER) {//普通or老人ペンギンならペンギンのselectActionを呼ぶ。
				moveOrNot = reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);

			}
			if (mobsSpeedOrder[i]->status == BULL) {//牛なら牛のselectActionを呼ぶ。
				moveOrNot = reinterpret_cast<Bull*>(mobsSpeedOrder[i])->selectAction(mobs_PenguinKids, mobs_Bull, board, handledCharacters);
			}

			if (moveOrNot == TRUE) {
				/*exhibitScreen(mobsSpeedOrder[i]->x, mobsSpeedOrder[i]->y, TRUE, board, handledCharacters);
				ScreenMove(mobsSpeedOrder[i]->x, mobsSpeedOrder[i]->y);*/

				/*if (quitGame == TRUE) {
					return FALSE;
				}*/

				if (GoNext(mobsSpeedOrder[i]->x, mobsSpeedOrder[i]->y) ==FALSE) {
					return FALSE;
				}
			}
		}
		//WaitKey();

		

	}
	return TRUE;

}



int BattleMode_GameManager::GoNext(int markX, int markY) {
	{
		int mouse = NULL;
		int xClick = NULL;
		int yClick = NULL;
		int nextFlag = -1;
		while (1) {
			if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
				return 0;
			}
			exhibitScreen(markX, markY, TRUE, FALSE, board, handledCharacters);
			mouse = NULL;
			xClick = NULL;
			yClick = NULL;
			if (CheckHitKey(KEY_INPUT_1) == FALSE && CheckHitKey(KEY_INPUT_2) == FALSE && CheckHitKey(KEY_INPUT_3) == FALSE && CheckHitKey(KEY_INPUT_4) == FALSE && CheckHitKey(KEY_INPUT_5) == FALSE && CheckHitKey(KEY_INPUT_6) == FALSE && CheckHitKey(KEY_INPUT_ESCAPE) == FALSE && CheckHitKey(KEY_INPUT_RETURN) == FALSE && CheckHitKey(KEY_INPUT_SPACE) == FALSE) {
				pushingKey = 0;
			}

			ScreenMove(markX,markY);
			DrawBox(FIELDSIZE * SQUARESIZE + 120, 700, FIELDSIZE * SQUARESIZE + 320, 785, GetColor(255, 183, 0), TRUE);
			DrawString(FIELDSIZE * SQUARESIZE + 170, 720, "次へ進む\n(SPACE)",GetColor(20,0,40));

			//nextFlag = GetClickPlace(&xClick, &yClick);
			//actionMsg = "afew=" + std::to_string(nextFlag);
			//exhibitScreen(markX, markY, TRUE, board, handledCharacters);//なんで？？？？
			//WaitKey();

			if (GetClickPlace(&xClick, &yClick) == 1) {
				if (xClick > FIELDSIZE * SQUARESIZE + 100 && xClick < FIELDSIZE * SQUARESIZE + 250 && yClick > 700 && yClick < 770) {
					return 1;
				}
				
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == TRUE && pushingKey == FALSE) {//現在の押下状態がFALSEで、いまEnterが押された場合
				pushingKey = 1;
				return 1;
			}

			ScreenFlip();
		}
	}

}



int  BattleMode_GameManager::ScreenMove(int markX, int markY) {
	if (CheckHitKey(KEY_INPUT_W) == TRUE) {//WASDで視点移動
		if (GameBuf->exhibitY > 0) {
			GameBuf->exhibitY -= 4;
			if (GameBuf->exhibitY < 0) {
				GameBuf->exhibitY = 0;
			}
			exhibitScreen(markX,markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);

		}
	}
	if (CheckHitKey(KEY_INPUT_S) == TRUE) {
		if (GameBuf->exhibitY < (GameBuf->sizeY - FIELDSIZE) * SQUARESIZE) {
			GameBuf->exhibitY += 4;
			if (GameBuf->exhibitY / 48 + FIELDSIZE >= GameBuf->sizeY) {//描画中心が被っているマス＋描画マス数＋１(描画下端マス)が、二次元配列サイズを超えていたら
				GameBuf->exhibitY = (GameBuf->sizeY - FIELDSIZE) * 48;//描画マスの左上を示すexhibitXYが盤面上におけるマイナスや、描画マスの右下が盤面サイズをはみ出る場合、はみ出ない場所に再設定。
			}

			exhibitScreen(markX,markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);
		}
	}
	if (CheckHitKey(KEY_INPUT_A) == TRUE) {//WASDで視点移動
		if (GameBuf->exhibitX > 0) {
			GameBuf->exhibitX -= 4;
			if (GameBuf->exhibitX < 0) {
				GameBuf->exhibitX = 0;
			}
			exhibitScreen(markX,markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);

		}
	}
	if (CheckHitKey(KEY_INPUT_D) == TRUE) {
		if (GameBuf->exhibitX < (GameBuf->sizeX - FIELDSIZE) * SQUARESIZE) {
			GameBuf->exhibitX += 4;
			if (GameBuf->exhibitX / 48 + FIELDSIZE >= GameBuf->sizeX) {
				GameBuf->exhibitX = (GameBuf->sizeX - FIELDSIZE) * 48;
			}
			exhibitScreen(markX, markY, TRUE, FALSE, board, handledCharacters);
			//WaitTimer(10);
		}
	}
	return 0;
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












int BattleMode_GameManager::EnemyEnter(int turn, int level, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {//どのターンで敵が出現するかを決める。
	int side = 0;
	int place = 0;
	int yieldReturnFlag = 0;

	if (turn == 0) {//１ターン目から、敵が出現しない側を決定する。
		randomSide = GetRand(3);
	}
	if (turn == 14) {//敵が出現しない側を決定する。
		randomSide = GetRand(3);
	}
	if (turn == 40) {//敵が出現しない側を決定する。
		randomSide = GetRand(3);
	}



	//if (GameBuf->sizeX == GameBuf->sizeY) {
	if ((1 < turn && turn < 25) || (36 < turn && turn < 50)) {
		if ((turn % 3 == 2 || turn % 3 == 0) || turn == 8) {

			side = GetRand(2);
			if (side >= randomSide) {//ランダムでとってきたsideの値が、敵出現なし側、つまり-1と定められてたら、方向番号を1増やす。
				side += 1;
			}

			place = GetRand(GameBuf->sizeX - 3);

			if (side == 0) {
				if (YieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
			if (side == 1) {
				if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
			if (side == 2) {
				if (YieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
			if (side == 3) {
				if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			}
		}
	}

	if ((turn % 2 == 0 && turn > 16 && turn < 25) || (turn % 3 == 2 && turn > 30)) {

		side = GetRand(3);
		place = GetRand(GameBuf->sizeX - 3);
		if (side == 0) {
			if (YieldEnemy(BULL, blue, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 1) {
			if (YieldEnemy(BULL, blue, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 2) {
			if (YieldEnemy(BULL, blue, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 3) {
			if (YieldEnemy(BULL, blue, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
	}




	if (turn % 8 == 6 && level == 1) {

		side = GetRand(3);
		place = GetRand(GameBuf->sizeX - 3);
		if (side == 0) {
			if (YieldEnemy(BULL, blue, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 1) {
			if (YieldEnemy(BULL, blue, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 2) {
			if (YieldEnemy(BULL, blue, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 3) {
			if (YieldEnemy(BULL, blue, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
	}




	if (turn == 28) {//敵が出現する側を決定する。1つの方向から集中攻撃がくるぞ！
		randomSide = GetRand(3);
	}
	if ((28 < turn && turn < 34) || turn == 9) {

		place = GetRand(GameBuf->sizeX - 3);
		if (randomSide == 0) {
			if (YieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (randomSide == 1) {
			if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (randomSide == 2) {
			if (YieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (randomSide == 3) {
			if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
	}




	if ((turn % 5 == 0 && turn > 12) || turn == 16) {//普通に赤が来る。半分の確率で反対側からも来る。
		side = GetRand(3);
		place = GetRand(GameBuf->sizeX - 3);
		if (side == 0) {
			if (YieldEnemy(BULL, red, 0, 1, place + 1, 0, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			place = GetRand(GameBuf->sizeX - 3);
			if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 1) {
			if (YieldEnemy(BULL, red, 0, -1, place + 1, GameBuf->sizeY - 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 2) {
			if (YieldEnemy(BULL, red, 1, 0, 0, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
			place = GetRand(GameBuf->sizeX - 3);
				if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}
		if (side == 3) {
			if (YieldEnemy(BULL, red, -1, 0, GameBuf->sizeX - 1, place + 1, mobs_PenguinKids, mobs_Bull, board, handledCharacters) == 0) { return 0; }
		}

	}
	//}
	return 1;
	
}







int BattleMode_GameManager::YieldEnemy(Status enemyType, Team enemyTeam, int dx, int dy, int cx, int cy, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {

	if (enemyType == BULL) {


		if (board[cx][cy].creature != NULL) {
			int rand = GetRand(1);
			if (cx == 0 || cx == GameBuf->sizeX - 1) {
				if (rand == 0) {
					cy += 1;
				}
				if (rand == 1) {
					cy -= 1;
				}
			}
			if (cy == 0 || cy == GameBuf->sizeY - 1) {
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
			return GoNext(cx,cy);
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