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

bool speedOrder(Creature* a, Creature* b);




	

	BattleMode_GameManager::BattleMode_GameManager() {//コンストラクタ。
		turnNum = 0;
	}


	void BattleMode_GameManager::BattleMode() {

		Emperor Emperor1(red, 0);//インスタンス化
		handledCharacters[0] = &Emperor1;
		Emperor Emperor2(blue, 1);//インスタンス化
		handledCharacters[1] = &Emperor2;

		DrawGraph(0, 0, HandleBoard, TRUE);
		WaitKey();
		gameMode = 1;

		while (gameMode == 1) {

			Emperor1.selectAction();

			Emperor2.selectAction();

			
			turnFinal();
			enemyEnter(turnNum);
			
			turnNum += 1;



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
				s = "X" + std::to_string(mobsSpeedOrder[i]->x) + "Y" + std::to_string(mobsSpeedOrder[i]->y) + "の素早さ:"+ to_string(mobsSpeedOrder[i]->speed) + " \n";//素早さ順アドレス配列のスピードを表示。
				allS += s;
			}
		}
		exhibitScreen();
		DrawString(800, 570, allS.c_str(), WHITE);
		WaitKey();








		for (int i = 0; i < mobNumberNow ; i++) {

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


			if (moveOrNot == TRUE) {//もし行動が行われていたら
				exhibitScreen();
				numSpeed = (to_string(mobsSpeedOrder[i]->speed));
				numX = (to_string(mobsSpeedOrder[i]->x));
				numY = (to_string(mobsSpeedOrder[i]->y));
				mobStatusMsg= "X:" +numX+ ",Y:" +numY + "の"+ mobsSpeedOrder[i]->name +"\n 行動速度:" +numSpeed+ " 体力:" + to_string(mobsSpeedOrder[i]->HP) + "/" + to_string(mobsSpeedOrder[i]->HP_Limit);
				DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
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





	void enemyEnter(int turn) {
		if (turn > 0 && turn < 10 && turn % 2 == 1) {

			Bull bull = Bull();
			int checkX = 1 + turn;
			int checkY = 1;
			bull.setMobs(red, 1,1,checkX,checkY,400000);
			mobs_Bull[num_bull] = bull;
			board[checkX][checkY].creature = &mobs_Bull[num_bull];
			mobNumber += 1;
			num_bull += 1;
		}


	}