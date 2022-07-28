#include "DxLib.h"
//#include<iostream>
//#include<stdio.h>
//Version15.各マス目に生物のポインタを持たせようと思ったがエラー。子供ペンギンをインスタンス化した際に
//可変長配列にインスタンスを代入して、生成時の関数から出るとインスタンスが消えちゃう問題を解決したが、謎のエラー。
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

#pragma warning(disable:4996)//printf系の関数を危険だと言い張って使わせてくれないVisual Studioの口をふさぐ魔法の言葉

using namespace std;

using std::string;
using std::vector;
using std::to_string;


//プロトタイプ宣言
void handlePenguin();
//void exhibitScreen(Grid board[FIELDSIZE][FIELDSIZE]);
//void setCreature(int num, int ix, int iy);

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	SetMainWindowText("ペンギンロボットバトル");
	if (ChangeWindowMode(TRUE) != 0) {//引数にTRUEを渡すとウィンドウモードになる。
		return 0;
	}
	// ウインドウのサイズを手動ではできず、且つウインドウのサイズに合わせて拡大もしないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(FIELDSIZE * 48 + 384, FIELDSIZE * 48, 32); // 画面サイズは最大の1024, 900 にしておく
	SetWindowSize(FIELDSIZE * 48 + 384, FIELDSIZE * 48);// 最初は 1024, 900 にしておく

	


	if (DxLib_Init() == -1) {
		return 0;
	}  // ＤＸライブラリ初期化処理


	handlePenguin();//ペンギンの全ての画像データを読み込む。
	HandleBoard = LoadGraph("Imgs/back.png");
	hHP = LoadGraph("Imgs/HPmeter43,9.png");
	HandleCastle = LoadGraph("Imgs/Castle.png");

	bool game = TRUE;
	int handleTitle;
	int titleStringColor = 200;
	bool colorUpOrDown = TRUE;
	//handleTitle = LoadGraph("Imgs/title.jpg");


	//int music;

	//int pm;
	//pm = LoadSoundMem("Imsg/SampleBGM.ogg");
	//int counter = 0;
	/*handleMusic = LoadSoundMem("Imgs/SampleYukkuri.wav");*/

	/*PlayMusic("Imgs/ochaBGM.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(40);*/

	//PlaySoundMem(handleMusic, DX_PLAYTYPE_LOOP, 1);
	//PlaySoundMem(pm, DX_PLAYTYPE_BACK, 1);


	int levelU = 0;
	int px = 3;

	while (game == TRUE) {
		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
			break;
		}

		//if (counter % 8760 == 0) {//BGM流したい
		//	PlaySoundMem(pm, DX_PLAYTYPE_BACK,1);
		//}
		//counter++;






		ClearDrawScreen();
		DrawGraph(0, 0, handleBack[1], TRUE);
		DrawString(960, 320, "モードを選択してください。\n\n\n1:簡単モード(Easy)\n60ターン生き残れ！\n\n\n2:通常モード(Normal)\n60ターン生き残れ！\n\n\n3:難関モード(Lunatic)\n100ターン生き残れ！\n\n\nEsc:やめる\n\n\n\n\n\n\n\n\n\n            VERSION:2", GetColor(titleStringColor, 245, 255));

		if (CheckHitKey(KEY_INPUT_1) == TRUE) {
			pushingKey = 1;
			BattleMode_GameManager* battle0 = new BattleMode_GameManager(0,20, 24);
			game = battle0->BattleMode(0);//FALSEだとゲーム終了。
			delete battle0;
		}
		if (CheckHitKey(KEY_INPUT_2) == TRUE) {
			pushingKey = 1;
			BattleMode_GameManager* battle1 = new BattleMode_GameManager(1,20, 19);
			game = battle1->BattleMode(0);//FALSEだとゲーム終了。
			delete battle1;
		}
		if (CheckHitKey(KEY_INPUT_3) == TRUE) {
			pushingKey = 1;
			BattleMode_GameManager* battle1 = new BattleMode_GameManager(1, 18, 19);
			game = battle1->BattleMode(1);//FALSEだとゲーム終了。
			delete battle1;
		}



		//3 + (levelU / 5)
		//expPoint - (levelUp * 100 / 3 + 150)

		if (CheckHitKey(KEY_INPUT_Z) == TRUE) {
			levelU++;
			if (levelU % (4 + (levelU / 5)) == 0) {
				px++;
			}
			WaitTimer(60);
		}
	
		//+levelU / (3 + );
		DrawString(960, 270, std::to_string(levelU).c_str(), GetColor(250, 200, 100));
		DrawString(960, 300, std::to_string(px).c_str(), GetColor(250, 200, 100));






		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
			return 0;
		}




		if (colorUpOrDown == TRUE) {
			titleStringColor += 7;
		}
		if (colorUpOrDown == FALSE) {
			titleStringColor -= 7;
		}
		if (titleStringColor >= 246) {
			colorUpOrDown = FALSE;
		}
		if (titleStringColor <= 8) {
			colorUpOrDown = TRUE;
		}






		ScreenFlip(); //裏画面を表画面に反映
	}


	DxLib_End();    // ＤＸライブラリ使用の終了処理

	return 0;    // ソフトの終了 
}
















void handlePenguin() {//ハンドルに画像のポインタを代入
	handle[red][EGG][NW] = LoadGraph("Imgs/redEgg.png");
	handle[blue][EGG][NW] = LoadGraph("Imgs/blueEgg.png");
	
	handleField[0] = LoadGraph("Imgs/Field/grassGreen.png");
	handleField[1] = LoadGraph("Imgs/Field/grassLight.png");
	handleField[2] = LoadGraph("Imgs/Field/cliff0.png");
	handleField[3] = LoadGraph("Imgs/Field/cliff1.png");
	handleField[4] = LoadGraph("Imgs/Field/cliff2.png");
	handleField[5] = LoadGraph("Imgs/Field/cliff3.png");
	handleField[6] = LoadGraph("Imgs/Field/cliff4.png");
	handleField[7] = LoadGraph("Imgs/Field/cliff5.png");
	handleField[8] = LoadGraph("Imgs/Field/cliff6.png");
	handleField[9] = LoadGraph("Imgs/Field/cliff7.png");


	handleBack[0] = LoadGraph("Imgs/Back/Nishikita.jpg");
	handleBack[1] = LoadGraph("Imgs/Back/title.jpg");

	



	char tmp[50];
	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/redPenguin%d.png", i);
		handle[red][NORMAL][i] = LoadGraph(tmp);
	}

	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/redEmperor%d.png", i);
		handle[red][EMPEROR][i] = LoadGraph(tmp);
	}

	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/bluePenguin%d.png", i);
		handle[blue][NORMAL][i] = LoadGraph(tmp);
	}

	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/blueEmperor%d.png", i);
		handle[blue][EMPEROR][i] = LoadGraph(tmp);
	}


	for (int i = 0; i <= 7; i++) {//老いた赤ペンギンも普通のペンギンと同じ絵。
		sprintf(tmp, "Imgs/redOld%d.png", i);
		handle[red][ELDER][i] = LoadGraph(tmp);
	}
	for (int i = 0; i <= 7; i++) {//老いた青ペンギンも普通のペンギンと同じ絵。
		sprintf(tmp, "Imgs/blueOld%d.png", i);
		handle[blue][ELDER][i] = LoadGraph(tmp);
	}

	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/redBull%d.png", i);
		handle[red][BULL][i] = LoadGraph(tmp);
	}
	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/blueBull%d.png", i);
		handle[blue][BULL][i] = LoadGraph(tmp);
	}

}

//void setCreature(int num, int ix, int iy) {
//    board[ix][iy].creature = handledCharacters[num];
//};




