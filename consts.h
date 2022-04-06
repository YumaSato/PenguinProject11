#pragma once

enum Team {
	red = 1, //�ԃ`�[��
	blue = 2 //�`�[��
};

enum Status {
	EGG = 1,        //��
	NORMAL = 2,     //���ʃy���M��
	ELDER = 3,      //�V�����y���M��
	EMPEROR = 4,    //�c��y���M��
	FIREGOD = 5,    //�΂̐_
	LIQUIDGOD = 6,  //���̐_
	MUSCLEMAN = 7,  //�ؓ��j
	SPRINTER = 8    //�����j
};


enum Direction {
	NW,
	NN,
	NE,
	EE,
	SE,
	SS,
	SW,
	WW
};

enum State {
	VACANT,
	GROUND,  //�n��
	WATER,   //��
	POISON   //�ŏ�
};

constexpr int BUFFER = 256;

constexpr int FIELDSIZE = 16;//�t�B�[���h�̃}�X�ڂ̐�
constexpr int CHARACTERNUM = 2;//����\�ȃL�����N�^��

const int WHITE = GetColor(255, 255, 255);

const int mobLimit = 1024;
