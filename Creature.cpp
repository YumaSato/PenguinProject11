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
	memset(&this->stamina, NULL, sizeof(this->stamina));
	memset(&this->staminaLimit, NULL, sizeof(this->staminaLimit));
	memset(&this->attackPower, NULL, sizeof(this->attackPower));
	memset(&this->defensePower, NULL, sizeof(this->defensePower));
	memset(&this->speed, NULL, sizeof(this->speed));
	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
	memset(&this->num, NULL, sizeof(this->num));
	name = "Somebody";
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


void Creature::setMobs(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {
}

bool Creature::selectAction() {
	return TRUE;
}

bool Creature::walk(int size) {
	return FALSE;
}





bool Creature::kick(int size) {
	int cX = 0;
	int cY = 0;
	int drctnX, drctnY;
	string s;

	GETdirectionXY(&drctnX, &drctnY);
	cX = x + drctnX;
	cY = y + drctnY;

	if (cX > 0 && cX < size && cY > 0 && cY < size) {
		if (board[cX][cY].creature == NULL) {//押したマスの方向に何もいなかったら処理を終了。
			return FALSE;
		}

		if (status == EMPEROR){
			if (board[cX][cY].creature->status == NORMAL || board[cX][cY].creature->status == ELDER) {//押したマスの方向に大人がいたら
				board[cX][cY].creature->SETdirection(directionX, directionY);//ダメージは無し。向きだけ変える。
				/*board[cX][cY].creature->HP -= 5;
				if (board[cX][cY].creature->HP <= 0) {
					board[cX][cY].creature->DeleteCreature();
				}*/
				return TRUE;
			}
		}

		if (board[cX][cY].creature->status == EGG){
			exhibitScreen();
			DrawString(800, 180, "kick開始", WHITE);
			WaitKey();

			while (1) {
				cX = cX + drctnX;//転がる方向のマスをひとつづつ調べる。
				cY = cY + drctnY;

				s = "";
				s = "X:" + std::to_string(cX) + "Y:" + std::to_string(cY);
				exhibitScreen();
				DrawString(800, 570, s.c_str(), WHITE);
				WaitKey();

				if (cX < 0 || cX > size || cY < 0 || cY > size) {//マス目の端っこまで調べたら、卵が消える。
					board[x + drctnX][y + drctnY].creature->DeleteCreature();
					board[x + drctnX][y + drctnY].creature = NULL;
					break;
				}

				if (board[cX][cY].creature != NULL) {//転がる方向に何か居たらループ抜け。

					if (board[cX][cY].creature->status == EMPEROR || board[cX][cY].creature->status == ELDER || board[cX][cY].creature->status == NORMAL) {//大人ペンギンが見つかったら

						board[x + drctnX][y + drctnY].creature->x = cX - drctnX;//元の居場所から動くペンギンを指定し、そのXYを変更。
						board[x + drctnX][y + drctnY].creature->y = cY - drctnY;
						board[cX - drctnX][cY - drctnY].creature = board[x + drctnX][y + drctnY].creature;//新しいますに卵アドレスを代入。
						board[x + drctnX][y + drctnY].creature = NULL;//元の位置の卵アドレスを削除。

						s = "";
						s = "NewPlace X:" + std::to_string(cX - drctnX) + "Y:" + std::to_string(cY - drctnY);
						exhibitScreen();
						DrawString(800, 570, s.c_str(), WHITE);
						WaitKey();
					}


					if (board[cX][cY].creature->status == EGG) {//卵が見つかったら
						board[cX][cY].creature->DeleteCreature();
						board[cX][cY].creature = NULL;

						board[x + drctnX][y + drctnY].creature->DeleteCreature();
						board[x + drctnX][y + drctnY].creature = NULL;
					}


					if (board[cX][cY].creature->status == BULL) {
					}
					s = "卵がぶつかった！";
					exhibitScreen();
					DrawString(800, 570, s.c_str(), WHITE);
					WaitKey();

					break;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}






void Creature::changeDirection() {
}

bool Creature::attack(int size) {
	return FALSE;
}

bool Creature::specialMovement1(int size){
	/*DrawString(800, 300, "Creature.specialMovement1メソッド実行", WHITE);
	WaitKey();*/
	return FALSE;
}

bool Creature::specialMovement2(int size) {
	return FALSE;
}

int Creature::useItem(int size) {
	return 0;
};

void Creature::test() {
};

void Creature::killed() {
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
	memset(&this->stamina, NULL, sizeof(this->stamina));
	memset(&this->staminaLimit, NULL, sizeof(this->staminaLimit));
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




void Creature::incubate(int checkX, int checkY) {//指定地点に生物がいる前提。孵化の内容を実行。

	board[checkX][checkY].creature->status = NORMAL;
	board[checkX][checkY].creature->defensePower = 25 + GetRand(2);
	board[checkX][checkY].creature->SETdirection(GETdirection());
}



void Creature::damage(int checkX, int checkY) {//指定地点に生物がいる前提。攻撃の内容を実行。
	board[checkX][checkY].creature->HP = board[checkX][checkY].creature->HP - (30 + GetRand(2)) * attackPower / board[checkX][checkY].creature->defensePower;//ダメ計
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
	if (board[checkX][checkY].creature->HP <= 0) {
		board[checkX][checkY].creature->DeleteCreature();
		board[checkX][checkY].creature = NULL;
	}
}