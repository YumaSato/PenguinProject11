#pragma once

enum Team {
	red = 1, //赤チーム
	blue = 2, //青チーム
	enemy = 3 //敵キャラども。
};

enum Status {
	EGG = 1,        //卵
	NORMAL = 2,     //普通ペンギン
	ELDER = 3,      //老いたペンギン
	EMPEROR = 4,    //皇帝ペンギン
	FIREGOD = 5,    //火の神
	LIQUIDGOD = 6,  //酒の神
	BULL = 7,       //闘牛
	SPRINTER = 8    //速足男
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
	GROUND,  //地面
	WATER,   //水
	POISON   //毒沼
};

constexpr int BUFFER = 256;

constexpr int FIELDSIZE = 16;//フィールドのマス目の数
constexpr int CHARACTERNUM = 2;//操作可能なキャラクタ数

const int WHITE = GetColor(255, 255, 255);

const int mobLimit = 1024;
