#include <string>
#include "DxLib.h"
#include "MyClasses.h"

using std::string;

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);

Creature::Creature() {//コンストラクタ。チームと位置を受け取る。
	memset(&this->team, NULL, sizeof(this->team));//teamとstatusはintではなくenum型であるからNULLを代入できない。
	memset(&this->status, NULL, sizeof(this->status));//だからmemsetでteamのサイズ分の指定バイト数をNULLで埋めてる。
	memset(&this->directionX, NULL, sizeof(this->directionX));
	memset(&this->directionY, NULL, sizeof(this->directionY));
	memset(&this->x, NULL, sizeof(this->x));
	memset(&this->y, NULL, sizeof(this->y));
	memset(&this->HP, NULL, sizeof(this->HP));
	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
	memset(&this->levelUp, NULL, sizeof(this->levelUp));
	memset(&this->expPoint, NULL, sizeof(this->expPoint));
	memset(&this->attackPower, NULL, sizeof(this->attackPower));
	memset(&this->defensePower, NULL, sizeof(this->defensePower));
	memset(&this->speed, NULL, sizeof(this->speed));
	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
	memset(&this->num, NULL, sizeof(this->num));
	name = "Somebody";
	giveExpPoint = 0;
	skip = FALSE;
	enemy = FALSE;

	//this->team = NULL;
	//this->status = NULL;
	//this->directionX = NULL;
	//this->directionY = NULL;
	//this->x = NULL;
	//this->y = NULL;
	//this->HP = NULL;
	//this->HP_Limit = NULL;
	//this->stamina = NULL;
	//this->staminaLimit = NULL;
	//this->attackPower = NULL;
	//this->defensePower = NULL;
	//this->speed = NULL;
	//this->staminaRecoverAbility = NULL;
	//this->num = NULL;
}


void Creature::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int initLevel, int parentSpeed, int pareAtt, int pareDef, Grid** board, Emperor* handledCharacters) {
}

int Creature::selectAction(PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
	return TRUE;
}

bool Creature::walk( Grid** board, Emperor* handledCharacters) {
	return FALSE;
}





bool Creature::kick( Grid** board, Emperor* handledCharacters) {
	//int cX = 0;
	//int cY = 0;
	//int drctnX, drctnY;
	//string s;

	//GETdirectionXY(&drctnX, &drctnY);
	//cX = x + drctnX;
	//cY = y + drctnY;

	//if (cX > 0 && cX < GameBuf->sizeX && cY > 0 && cY < GameBuf->sizeY) {
	//	if (board[cX][cY].creature == NULL) {//押したマスの方向に何もいなかったら処理を終了。
	//		return FALSE;
	//	}

	//	if (status == EMPEROR) {
	//		if (board[cX][cY].creature->status == NORMAL || board[cX][cY].creature->status == ELDER) {//押したマスの方向に大人がいたら
	//			board[cX][cY].creature->SETdirection(directionX, directionY);//ダメージは無し。向きだけ変える。
	//			/*board[cX][cY].creature->HP -= 5;
	//			if (board[cX][cY].creature->HP <= 0) {
	//				board[cX][cY].creature->DeleteCreature();
	//			}*/
	//			return TRUE;
	//		}
	//		if (board[cX][cY].creature->status == EGG) {
	//			//exhibitScreen(x, y, TRUE);
	//			//DrawString(800, 180, "kick開始", WHITE);
	//			//WaitKey();
	//			int i = 0;
	//			while(1) {
	//				

	//				cX = cX + drctnX;//転がる方向のマスをひとつづつ調べる。
	//				cY = cY + drctnY;

	//				/*s = "";
	//				s = "X:" + std::to_string(cX) + "Y:" + std::to_string(cY);
	//				exhibitScreen(x, y, TRUE);
	//				DrawString(800, 570, s.c_str(), WHITE);
	//				WaitKey();*/

	//				if (cX < 0 || cX >= GameBuf->sizeX || cY < 0 || cY >= GameBuf->sizeY || (cX == GameBuf->castleX && cY == GameBuf->castleY)) {//マス目の端っこまで調べたら、卵が消える。

	//					exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

	//					board[x + drctnX][y + drctnY].creature->DeleteCreature();
	//					board[x + drctnX][y + drctnY].creature = NULL;
	//					break;
	//				}

	//				if (board[cX][cY].creature != NULL) {//転がる方向に何か居たらループ抜け。

	//					if (board[cX][cY].creature->status == EMPEROR || board[cX][cY].creature->status == ELDER || board[cX][cY].creature->status == NORMAL) {//大人ペンギンが見つかったら

	//						exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

	//						board[x + drctnX][y + drctnY].creature->x = cX - drctnX;//元の居場所から動くペンギンを指定し、そのXYを変更。
	//						board[x + drctnX][y + drctnY].creature->y = cY - drctnY;
	//						board[cX - drctnX][cY - drctnY].creature = board[x + drctnX][y + drctnY].creature;//新しいますに卵アドレスを代入。
	//						board[x + drctnX][y + drctnY].creature = NULL;//元の位置の卵アドレスを削除。

	//					/*	s = "";
	//						s = "NewPlace X:" + std::to_string(cX - drctnX) + "Y:" + std::to_string(cY - drctnY);
	//						exhibitScreen(x, y, TRUE);
	//						DrawString(800, 570, s.c_str(), WHITE);
	//						WaitKey();*/
	//					}


	//					else if (board[cX][cY].creature->status == EGG) {//卵が見つかったら

	//						exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);

	//						board[cX][cY].creature->DeleteCreature();
	//						board[cX][cY].creature = NULL;

	//						board[x + drctnX][y + drctnY].creature->DeleteCreature();
	//						board[x + drctnX][y + drctnY].creature = NULL;
	//					}


	//					else if (board[cX][cY].creature->status == BULL) {//この警告はどういうこと？？

	//						exhibitRolling(x, y, drctnX, drctnY, i, board, handledCharacters);
	//						board[x + drctnX][y + drctnY].creature->DeleteCreature();
	//						board[x + drctnX][y + drctnY].creature = NULL;
	//					}
	//					/*s = "卵がぶつかった！";
	//					exhibitScreen(x, y, TRUE);
	//					DrawString(800, 570, s.c_str(), WHITE);
	//					WaitKey();*/

	//					break;

	//					
	//				}
	//				i++;
	//			}
	//			return TRUE;
	//		}
	//	}
	//}
	//return FALSE;
	return FALSE;
}






void Creature::changeDirection(Grid** board, Emperor* handledCharacters) {
}

bool Creature::attack( Grid** board, Emperor* handledCharacters) {
	return FALSE;
}

bool Creature::specialMovement1( PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
	/*DrawString(800, 300, "Creature.specialMovement1メソッド実行", WHITE);
	WaitKey();*/
	return FALSE;
}

bool Creature::specialMovement2( Grid** board, Emperor* handledCharacters) {
	return FALSE;
}

int Creature::useItem( Grid** board, Emperor* handledCharacters) {
	return 0;
};

void Creature::test() {
};

void Creature::killed(Grid** board, Emperor* handledCharacters) {
	this->HP = NULL;
	this->x = NULL;
	this->y = NULL;
}


void Creature::SETdirection(int xward, int yward) {
	this->directionX = xward;
	this->directionY = yward;
	this->compass = GETdirectionBYxy(xward, yward);
}

void Creature::SETdirection(Direction compass) {
	int tmp_x, tmp_y;
	GETxyBYdirection(&tmp_x, &tmp_y, compass);

	this->directionX = tmp_x;
	this->directionY = tmp_y;
	this->compass = compass;
}

void Creature::GETdirectionXY(int* xward, int* yward) {//方向の値を代入する変数のアドレスを受け取る
	*xward = directionX;
	*yward = directionY;//そのアドレスの中身に方向を代入。疑似的に値を返せる。
}

Direction Creature::GETdirection() {
	return compass;
}




void Creature::DeleteCreature() {
	memset(&this->team, NULL, sizeof(this->team));
	memset(&this->status, NULL, sizeof(this->status));
	memset(&this->directionX, NULL, sizeof(this->directionX));
	memset(&this->directionY, NULL, sizeof(this->directionY));
	memset(&this->x, NULL, sizeof(this->x));
	memset(&this->y, NULL, sizeof(this->y));
	memset(&this->HP, NULL, sizeof(this->HP));
	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
	memset(&this->levelUp, NULL, sizeof(this->levelUp));
	memset(&this->expPoint, NULL, sizeof(this->expPoint));
	memset(&this->attackPower, NULL, sizeof(this->attackPower));
	memset(&this->defensePower, NULL, sizeof(this->defensePower));
	memset(&this->speed, NULL, sizeof(this->speed));
	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
	memset(&this->num, NULL, sizeof(this->num));


	//team = NULL;
	//status = NULL;
	//directionX = NULL;
	//directionY = NULL;
	//x = NULL;
	//y = NULL;
	//HP = NULL;
	//HP_Limit = NULL;
	//stamina = NULL;
	//staminaLimit = NULL;
	//attackPower = NULL;
	//defensePower = NULL;
	//speed = NULL;
	//staminaRecoverAbility = NULL;
	//num = NULL;
}




void Creature::incubate(int checkX, int checkY, Grid** board, Emperor* handledCharacters) {//指定地点に生物がいる前提。孵化の内容を実行。

	board[checkX][checkY].creature->status = NORMAL;
	
	board[checkX][checkY].creature->SETdirection(GETdirection());
}



int Creature::damage(int checkX, int checkY, Grid** board, Emperor* handledCharacters) {//指定地点に生物がいる前提。攻撃の内容を実行。

	int damageHP = 0;
	if (board[checkX][checkY].creature->status == EGG) {//卵相手なら確実に殺す
		damageHP = 51;
	}
	else {
		damageHP = (30 + GetRand(2)) * attackPower / board[checkX][checkY].creature->defensePower;//ダメ計
	}


	board[checkX][checkY].creature->HP = board[checkX][checkY].creature->HP - damageHP;//体力-damageHPの計算を行う。

	if (board[checkX][checkY].creature->status == NORMAL || board[checkX][checkY].creature->status == ELDER) {//相手がペンギンだった場合、向きが変わる。
		switch (GETdirection()) {
		case NW:
			board[checkX][checkY].creature->SETdirection(SE);
			break;
		case NN:
			board[checkX][checkY].creature->SETdirection(SS);
			break;
		case NE:
			board[checkX][checkY].creature->SETdirection(SW);
			break;
		case EE:
			board[checkX][checkY].creature->SETdirection(WW);
			break;
		case SE:
			board[checkX][checkY].creature->SETdirection(NW);
			break;
		case SS:
			board[checkX][checkY].creature->SETdirection(NN);
			break;
		case SW:
			board[checkX][checkY].creature->SETdirection(NE);
			break;
		case WW:
			board[checkX][checkY].creature->SETdirection(EE);
			break;
		}
	}
	string msg1 = "は攻撃した。";
	actionMsg = name + msg1;
	exhibitDamage(x, y, checkX, checkY, TRUE, damageHP, board, handledCharacters);
	string msg2 = "";
	string msg3 = "";

	if (board[checkX][checkY].creature->HP <= 0) {//HPがマイナスになったら死ぬ
		board[checkX][checkY].creature->HP = 0;

		int expUp;
		int lvUp = NULL;
		expUp = board[checkX][checkY].creature->giveExpPoint;

		board[checkX][checkY].creature->DeleteCreature();
		board[checkX][checkY].creature = NULL;

		if (team == red && enemy == FALSE) {//倒した側のTeamの皇帝が経験値を得る。
			if (handledCharacters[0].HP > 0) {//皇帝が生存していれば
				lvUp = handledCharacters[0].GetExpPoint(expUp);
			}
		}
		else if (team == blue && enemy == FALSE) {
			if (handledCharacters[1].HP > 0) {
				lvUp = handledCharacters[1].GetExpPoint(expUp);
			}
		}
		msg2 = "\n相手をやっつけた。";

		if (lvUp == 0) {//経験値獲得関数内でゲームが終了されたら
			return 0;
		}
		score += expUp;



		actionMsg = name + msg1 + msg2 + msg3;
		

		exhibitScreen(x, y, TRUE, FALSE, board, handledCharacters);

		




		return 1;//成功したら1を返す。
	}
}