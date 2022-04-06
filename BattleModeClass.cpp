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

//bool speedOrder(Creature* a, Creature* b);




	

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


		}
	}















	void turnFinal() {//素早さ順にmobが行動していく関数。
		string mobStatusMsg;
		string numSpeed;
		string numX;
		string numY;
		int sortSpeedOrder[mobLimit];
		int mobNumberNow;

		mobNumberNow = mobNumber;

		for (int i = 0; i < mobNumber; i++) {
			sortSpeedOrder[i] = mobs_PenguinKids[i].speed;//まず素早さ順で素早さを入れるint配列に、mobsのnum順で素早さ値を代入。



			/*if (sortSpeedOrder[i] == NULL) {
				sortSpeedOrder[i] = -1;
			}*/
			/*numSpeed = (to_string(sortSpeedOrder[i]));
			DrawString(800, 560 + i*20, numSpeed.c_str(), WHITE);
			WaitKey();*/
		}	

		sort(sortSpeedOrder, sortSpeedOrder + mobNumber, greater<>());//降順で並べ替え。
		//素早さ順で素早さを入れるint配列の中身を、ちゃんと素早さ順に並べ替える。


		string s = "";
		for (int i = 0; i < mobNumber; i++) {
			s += " " + to_string(sortSpeedOrder[i]);
		}
		DrawString(800, 550, s.c_str(), WHITE);
		WaitKey();


		for (int sort_i = 0; sort_i < mobNumber; sort_i++) {//素早さ順int配列ごとに、

			if (sortSpeedOrder[sort_i] == NULL) {
				continue;
			}

			for (int mobs_i = 0; mobs_i < mobNumber; mobs_i++) {//各mobsを調べて、


				//numSpeed = (to_string(mobs_PenguinKids[mobs_i].speed));
				//DrawString(800, 660 + mobs_i*20, numSpeed.c_str(), WHITE);
				//WaitKey();

				if (sortSpeedOrder[sort_i] == mobs_PenguinKids[mobs_i].speed) {//素早さ順intの素早さとmobsの素早さが一致したら
					mobsSpeedOrder[sort_i] = &mobs_PenguinKids[mobs_i];//素早さ順アドレス配列に代入。
				}
			}
		}

		//s = "";
		//for (int i = 0; i < mobNumber; i++) {
		//	s += "アドレス" + to_string(mobsSpeedOrder[i]->speed);//素早さ順アドレス配列のスピードを表示。
		//}
		//DrawString(800, 570, s.c_str(), WHITE);
		//WaitKey();








		for (int i = 0; i < mobNumberNow ; i++) {

			//if (mobsspeedorder[i] == null) {
			//	continue;
			//}
			if (mobsSpeedOrder[i] == NULL) {//スピード順配列にもう何もなければ終了。
				return;
			}

			//if (mobsSpeedOrder[i]->pass == TRUE) {//キャラは居るけど行動しない状態であればコンティニュー。
			//	continue;
			//}
			
			if (mobsSpeedOrder[i]->status == NORMAL or mobsSpeedOrder[i]->status == ELDER) {
				reinterpret_cast<PenguinKids*>(mobsSpeedOrder[i])->selectAction();
			}
			
			//mobsSpeedOrder[i]->specialMovement2(FIELDSIZE);
			//mobsSpeedOrder[i]->attack();

			exhibitScreen();

			numSpeed = (to_string(mobsSpeedOrder[i]->speed));
			numX = (to_string(mobsSpeedOrder[i]->x));
			numY = (to_string(mobsSpeedOrder[i]->y));
			mobStatusMsg = "X:" + numX + ",Y:" + numY + "のペンギンの俊敏さは、" + numSpeed;
			DrawString(800, 160, mobStatusMsg.c_str(), WHITE);
			WaitKey();
		}

	}















	/*bool speedOrder(Creature* a, Creature* b) {

		if (a->speed == b->speed) {
			return a->speed < b->speed;
		}
		else {
			return a->speed > b->speed;
		}
		
	}*/



