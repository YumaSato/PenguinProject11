#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//プロトタイプ宣言
void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor(Team team, int num) : Character() {//皇帝のコンストラクタ
	this->status = EMPEROR;//ステータスを「皇帝」を意味する4に変更
	this->team = team;

	if (this->team == red) {//赤チーム(=1)の皇帝であれば赤皇帝を盤面上部にスポーン
		this->name = "赤皇帝";
		this->x = FIELDSIZE - 6;
		this->y = 6;
		//this->directionX = 0;
		//this->directionY = -1;
		SETdirection(0, -1);
		this->status = EMPEROR;
		this->HP = 100;
		this->HP_Limit = 100;
		this->stamina = 100;
		this->staminaLimit = 100;
		this->attackPower = 30;
		this->defensePower = 30;
		this->speed = 500001;
		this->staminaRecoverAbility = 5;
		this->num = num;


		//setCreature(num, x, y);

		board[x][y].creature = this;//マス目に自分のポインタを代入。

	}

	if (this->team == blue) {//青チーム(=2)の皇帝であれば青皇帝を盤面下部にスポーン
		this->name = "青皇帝";
		this->x = 6;
		this->y = FIELDSIZE - 6;
		//this->directionX = 0;
		//this->directionY = 1;
		SETdirection(0, 1);
		this->status = EMPEROR;
		this->HP = 100;
		this->HP_Limit = 100;
		this->stamina = 100;
		this->staminaLimit = 100;
		this->attackPower = 30;
		this->defensePower = 30;
		this->speed = 500002;
		this->staminaRecoverAbility = 5;
		this->num = num;

		//setCreature(num, x, y);

		board[x][y].creature = this;
	}
}


bool Emperor::specialMovement1(int size) {//特殊技：産卵
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
		if (board[checkX][checkY].creature == NULL && board[checkX][checkY].state == VACANT) {//押したマスの方向が空いていたらインスタンス化を実行
			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, drctnX, drctnY, checkX, checkY, speed);

			//kids.push_back(penguinKids);
			//board[checkX][checkY].creature = &kids.back();
			/*mobs_PenguinKids[mobNumber] = penguinKids;
			board[checkX][checkY].creature = &mobs_PenguinKids[mobNumber];
			mobNumber += 1;*/

			mobs_PenguinKids[num_penguinKids] = penguinKids;//生まれたキッズを配列に入れる。
			board[checkX][checkY].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;



			stamina -= 5;
			exhibitScreen();
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	return FALSE;
}


bool Emperor::specialMovement2(int size) {//特殊技：孵化
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < size && checkY >= 0 && checkY < size) {
		if (board[checkX][checkY].creature == NULL) {
			return FALSE;
		}
		if (board[checkX][checkY].creature->status == EGG) {//押したマスの方向に卵があれば処理を実行

			incubate(checkX, checkY);
			//board[checkX][checkY].creature->directionX = this->directionX;
			//board[checkX][checkY].creature->directionY = this->directionY;
			exhibitScreen();
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}







//
//bool Emperor::kick(int size) {
//	int checkX = 0;
//	int checkY = 0;
//	int drctnX, drctnY;
//	string s;
//
//	GETdirectionXY(&drctnX, &drctnY);
//	checkX = x + drctnX;
//	checkY = y + drctnY;
//
//	if (checkX > 0 && checkX < size && checkY > 0 && checkY < size) {
//		if (board[checkX][checkY].creature == NULL) {//押したマスの方向に何もいなかったら処理を終了。
//			return FALSE;
//		}
//
//		if (board[checkX][checkY].creature->status != EGG) {//押したマスの方向に卵以外があれば処理を終了。
//			return FALSE;
//		}else{
//
//			while (1) {
//				exhibitScreen();
//				DrawString(800, 180, "kick開始", WHITE);
//				WaitKey();
//
//
//
//				checkX = checkX + drctnX;//転がる方向のマスをひとつづつ調べる。
//				checkY = checkY + drctnY;
//
//
//				s = "";
//				s = "X:" + std::to_string(checkX) + "Y:" + std::to_string(checkY);
//				DrawString(800, 570, s.c_str(), WHITE);
//				WaitKey();
//
//
//
//				if (checkX <= 0 || checkX > size || checkY <= 0 || checkY > size) {//マス目の端っこまで調べたら、卵が消える。
//					board[x + drctnX][y + drctnY].creature->killed();
//					board[x + drctnX][y + drctnY].creature = NULL;
//					break;
//				}
//
//
//				
//
//
//
//				if (board[checkX][checkY].creature != NULL) {//転がる方向に何か居たらループ抜け。
//
//					if (board[checkX][checkY].creature->status == NORMAL || ELDER || EMPEROR) {//大人ペンギンが見つかったら
//
//						board[x + drctnX][y + drctnY].creature->x = checkX - drctnX;
//						board[x + drctnX][y + drctnY].creature->x = checkY - drctnY;
//
//						s = "";
//						s = "X:" + std::to_string(checkX - drctnX) + "Y:" + std::to_string(checkY - drctnY);
//						DrawString(800, 570, s.c_str(), WHITE);
//						WaitKey();
//
//
//						board[checkX - drctnX][checkY - drctnY].creature = board[x + drctnX][y + drctnY].creature;//新しいますに卵アドレスを代入。
//						board[x + drctnX][y + drctnY].creature = NULL;//元の位置の卵アドレスを削除。
//					}
//
//
//
//					if (board[checkX][checkY].creature->status == EGG) {//卵が見つかったら
//						board[checkX][checkY].creature->killed();
//						board[checkX][checkY].creature = NULL;
//
//						board[x + drctnX][y + drctnY].creature->killed();
//						board[x + drctnX][y + drctnY].creature = NULL;
//					}
//
//
//
//
//					if (board[checkX][checkY].creature->status == BULL) {
//					}
//
//
//					break;
//				}
//
//
//			}
//		}
//	}
//	return TRUE;
//}