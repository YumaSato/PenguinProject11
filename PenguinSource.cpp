#include "DxLib.h"
//#include<iostream>
//#include<stdio.h>
//Version15.�e�}�X�ڂɐ����̃|�C���^���������悤�Ǝv�������G���[�B�q���y���M�����C���X�^���X�������ۂ�
//�ϒ��z��ɃC���X�^���X�������āA�������̊֐�����o��ƃC���X�^���X���������Ⴄ���������������A��̃G���[�B
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

#pragma warning(disable:4996)//printf�n�̊֐����댯���ƌ��������Ďg�킹�Ă���Ȃ�Visual Studio�̌����ӂ������@�̌��t

using namespace std;

using std::string;
using std::vector;
using std::to_string;


//�v���g�^�C�v�錾
void handlePenguin();
//void exhibitScreen(Grid board[FIELDSIZE][FIELDSIZE]);
//void setCreature(int num, int ix, int iy);

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	SetMainWindowText("�y���M�����{�b�g�o�g��");
	if (ChangeWindowMode(TRUE) != 0) {//������TRUE��n���ƃE�B���h�E���[�h�ɂȂ�B
		return 0;
	}
	// �E�C���h�E�̃T�C�Y���蓮�ł͂ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(SCREENSIZE * 48 + 384, SCREENSIZE * 48, 32); // ��ʃT�C�Y�͍ő��1024, 900 �ɂ��Ă���
	SetWindowSize(SCREENSIZE * 48 + 384, SCREENSIZE * 48);// �ŏ��� 1024, 900 �ɂ��Ă���

	


	if (DxLib_Init() == -1) {
		return 0;
	}  // �c�w���C�u��������������


	handlePenguin();//�y���M���̑S�Ẳ摜�f�[�^��ǂݍ��ށB
	HandleBoard = LoadGraph("Imgs/back.png");
	hHP = LoadGraph("Imgs/HPmeter43,9.png");
	HandleCastle = LoadGraph("Imgs/Castle.png");

	bool game = TRUE;
	int handleTitle;
	int titleStringColor = 200;
	bool colorUpOrDown = TRUE;
	handleTitle = LoadGraph("Imgs/title.jpg");


	int music;

	//int pm;
	//pm = LoadSoundMem("Imsg/SampleBGM.ogg");
	//int counter = 0;
	/*handleMusic = LoadSoundMem("Imgs/SampleYukkuri.wav");*/
	
	PlayMusic("Imgs/ochaBGM.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(40);

	//PlaySoundMem(handleMusic, DX_PLAYTYPE_LOOP, 1);
	//PlaySoundMem(pm, DX_PLAYTYPE_BACK, 1);

	while (game == TRUE) {
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			break;
		}

		//if (counter % 8760 == 0) {//BGM��������
		//	PlaySoundMem(pm, DX_PLAYTYPE_BACK,1);
		//}
		//counter++;
		






		DrawGraph(0, 0, handleTitle, TRUE);
		DrawString(960, 320, "���[�h��I�����Ă��������B\n\n\n1:�ʏ탂�[�h(Normal)\n60�^�[�������c��I\n\n\n2:��փ��[�h(Lunatic)\n100�^�[�������c��I\n\n\nEsc:��߂�\n\n\n\n\n\n\n\n\n\n\n\n            VERSION:2", GetColor(titleStringColor, 245,255));
		
		if (CheckHitKey(KEY_INPUT_1) == TRUE) {
			BattleMode_GameManager *battle0 = new BattleMode_GameManager(11,15);
			game = battle0->BattleMode(0);//FALSE���ƃQ�[���I���B
			delete battle0;
		}
		if (CheckHitKey(KEY_INPUT_2) == TRUE) {
			BattleMode_GameManager* battle1 = new BattleMode_GameManager(17, 17);
			game = battle1->BattleMode(1);//FALSE���ƃQ�[���I���B
			delete battle1;
		}


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






		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}


	DxLib_End();    // �c�w���C�u�����g�p�̏I������

	return 0;    // �\�t�g�̏I�� 
}
















void handlePenguin() {//�n���h���ɉ摜�̃|�C���^����
	handle[red][EGG][NW] = LoadGraph("Imgs/redEgg.png");
	handle[blue][EGG][NW] = LoadGraph("Imgs/blueEgg.png");

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


	for (int i = 0; i <= 7; i++) {//�V�����ԃy���M�������ʂ̃y���M���Ɠ����G�B
		sprintf(tmp, "Imgs/redOld%d.png", i);
		handle[red][ELDER][i] = LoadGraph(tmp);
	}
	for (int i = 0; i <= 7; i++) {//�V�����y���M�������ʂ̃y���M���Ɠ����G�B
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




