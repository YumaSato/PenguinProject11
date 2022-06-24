#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//プロトタイプ宣言
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor() {//皇帝のコンストラクタ

}


void Emperor::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, Grid** board, Emperor* handledCharacters) {
	this->status = EMPEROR;//ステータスを「皇帝」を意味する4に変更
	this->team = ParentTeam;

	giveExpPoint = 600;

	if (ParentTeam == red) {//赤チーム(=1)の皇帝であれば赤皇帝を盤面上部にスポーン
		this->name = "赤皇帝";
		this->x = GameBuf->castleX - 1;
		this->y = GameBuf->castleY - 1;
		//this->directionX = 0;
		//this->directionY = -1;
		SETdirection(0, -1);
		this->status = EMPEROR;
		this->HP = 50;
		this->HP_Limit = 50;
		this->levelUp = 1;
		this->expPoint = 0;
		this->attackPower = 20;
		this->defensePower = 35;
		this->speed = 1001;
		this->staminaRecoverAbility = 10;
		this->num = 0;


		//setCreature(num, x, y);



	}

	if (ParentTeam == blue) {//青チーム(=2)の皇帝であれば青皇帝を盤面下部にスポーン
		this->name = "青皇帝";
		this->x = GameBuf->castleX + 1;
		this->y = GameBuf->castleY + 1;
		//this->directionX = 0;
		//this->directionY = 1;
		SETdirection(0, 1);
		this->status = EMPEROR;
		this->HP = 50;
		this->HP_Limit = 50;
		this->levelUp = 1;
		this->expPoint = 0;
		this->attackPower = 20;
		this->defensePower = 35;
		this->speed = 1000;
		this->staminaRecoverAbility = 5;
		this->num = 1;

		//setCreature(num, x, y);


	}

}





bool Emperor::specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {//特殊技：産卵
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < GameBuf->sizeX && checkY >= 0 && checkY < GameBuf->sizeY) {
		if (board[checkX][checkY].creature == NULL && board[checkX][checkY].state == VACANT) {//押したマスの方向が空いていたらインスタンス化を実行
			PenguinKids penguinKids = PenguinKids();
			penguinKids.setMobs(team, drctnX, drctnY, checkX, checkY, levelUp, speed, board, handledCharacters);

			//kids.push_back(penguinKids);
			//board[checkX][checkY].creature = &kids.back();
			/*mobs_PenguinKids[mobNumber] = penguinKids;
			board[checkX][checkY].creature = &mobs_PenguinKids[mobNumber];
			mobNumber += 1;*/

			mobs_PenguinKids[num_penguinKids] = penguinKids;//生まれたキッズを配列に入れる。
			board[checkX][checkY].creature = &mobs_PenguinKids[num_penguinKids];
			mobNumber += 1;
			num_penguinKids += 1;




			exhibitScreen(x, y, TRUE, board, handledCharacters);
			return TRUE;
		}
		else {

			return FALSE;
		}
	}
	return FALSE;
}


bool Emperor::specialMovement2( Grid** board, Emperor* handledCharacters) {//特殊技：孵化
	int checkX = 0;
	int checkY;
	int drctnX, drctnY;
	GETdirectionXY(&drctnX, &drctnY);
	checkX = x + drctnX;
	checkY = y + drctnY;

	if (checkX >= 0 && checkX < GameBuf->sizeX && checkY >= 0 && checkY < GameBuf->sizeY) {
		if (board[checkX][checkY].creature == NULL) {
			return FALSE;
		}
		if (board[checkX][checkY].creature->status == EGG) {//押したマスの方向に卵があれば処理を実行

			incubate(checkX, checkY, board, handledCharacters);
			//board[checkX][checkY].creature->directionX = this->directionX;
			//board[checkX][checkY].creature->directionY = this->directionY;
			exhibitScreen(x, y, TRUE, board, handledCharacters);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

bool Emperor::kick(Grid** board, Emperor* handledCharacters) {
	int cX = 0;
	int cY = 0;
	int drctnX, drctnY;
	string s;

	GETdirectionXY(&drctnX, &drctnY);
	cX = x + drctnX;
	cY = y + drctnY;

	if (cX > 0 && cX < GameBuf->sizeX && cY > 0 && cY < GameBuf->sizeY) {
		if (board[cX][cY].creature == NULL) {//押したマスの方向に何もいなかったら処理を終了。
			return FALSE;
		}

		if (status == EMPEROR) {
			if (board[cX][cY].creature->status == NORMAL || board[cX][cY].creature->status == ELDER) {//押したマスの方向に大人がいたら
				board[cX][cY].creature->SETdirection(drctnX, drctnY);//ダメージは無し。向きだけ変える。
				/*board[cX][cY].creature->HP -= 5;
				if (board[cX][cY].creature->HP <= 0) {
					board[cX][cY].creature->DeleteCreature();
				}*/
				return TRUE;
			}
			if (board[cX][cY].creature->status == EGG) {
				//exhibitScreen(x, y, TRUE);
				//DrawString(800, 180, "kick開始", WHITE);
				//WaitKey();
				int i = 0;
				while (1) {


					cX = cX + drctnX;//転がる方向のマスをひとつづつ調べる。
					cY = cY + drctnY;

					/*s = "";
					s = "X:" + std::to_string(cX) + "Y:" + std::to_string(cY);
					exhibitScreen(x, y, TRUE);
					DrawString(800, 570, s.c_str(), WHITE);
					WaitKey();*/

					if (cX < 0 || cX >= GameBuf->sizeX || cY < 0 || cY >= GameBuf->sizeY || (cX == GameBuf->castleX && cY == GameBuf->castleY)) {//マス目の端っこまで調べたら、卵が消える。

						exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

						board[x + drctnX][y + drctnY].creature->DeleteCreature();
						board[x + drctnX][y + drctnY].creature = NULL;
						break;
					}

					if (board[cX][cY].creature != NULL) {//転がる方向に何か居たらループ抜け。

						if (board[cX][cY].creature->status == EMPEROR || board[cX][cY].creature->status == ELDER || board[cX][cY].creature->status == NORMAL) {//大人ペンギンが見つかったら

							exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

							board[x + drctnX][y + drctnY].creature->x = cX - drctnX;//元の居場所から動くペンギンを指定し、そのXYを変更。
							board[x + drctnX][y + drctnY].creature->y = cY - drctnY;
							board[cX - drctnX][cY - drctnY].creature = board[x + drctnX][y + drctnY].creature;//新しいますに卵アドレスを代入。
							board[x + drctnX][y + drctnY].creature = NULL;//元の位置の卵アドレスを削除。

						/*	s = "";
							s = "NewPlace X:" + std::to_string(cX - drctnX) + "Y:" + std::to_string(cY - drctnY);
							exhibitScreen(x, y, TRUE);
							DrawString(800, 570, s.c_str(), WHITE);
							WaitKey();*/
						}


						else if (board[cX][cY].creature->status == EGG) {//卵が見つかったら

							exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

							board[cX][cY].creature->DeleteCreature();
							board[cX][cY].creature = NULL;

							board[x + drctnX][y + drctnY].creature->DeleteCreature();
							board[x + drctnX][y + drctnY].creature = NULL;
						}


						else if (board[cX][cY].creature->status == BULL) {//この警告はどういうこと？？

							exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);
							board[x + drctnX][y + drctnY].creature->DeleteCreature();
							board[x + drctnX][y + drctnY].creature = NULL;
						}
						/*s = "卵がぶつかった！";
						exhibitScreen(x, y, TRUE);
						DrawString(800, 570, s.c_str(), WHITE);
						WaitKey();*/

						break;


					}
					i++;
				}
				return TRUE;
			}
		}
	}
	return FALSE;

}




int Emperor::GetExpPoint(int expP) {
	expPoint += expP;
	int surplus_expP;

	if (expPoint >= levelUp * 100 / 3 + 150) {//レベルアップ必要分の経験値を得たら、レベルアップ

		//expPoint = expPoint - (levelUp * 100 / 6 + 100);//レベルアップ達成時に余った経験値は次のレベル用に貯められる。


		surplus_expP = expPoint - (levelUp * 100 / 3 + 150);//今回のレベルアップで余った経験値
		levelUp += 1;
		attackPower += 1 + GetRand(1);
		defensePower += 2 + GetRand(2);
		expPoint = 0;
		GetExpPoint(surplus_expP);

		return levelUp;//上がったレベルを返す。
	}
	return 0;
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