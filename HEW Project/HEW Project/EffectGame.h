#pragma once
#include "Effect.h"
#define MaxParticleNum 32     // 一つのエフェクトで使える最大パーティクル数


class EffectGame:public Effect
{
	Effect* eft[MaxParticleNum];     // 操作するエフェクトポインタ配列
	bool DoOnce = true;     // メンバ変数
	void (EffectGame::*fpCallFunc)();     //呼び出すエフェクト関数ポインタ
public:
	// メモリを取得したエフェクトの数
	static int MaxEffectNum;
	// 自分のvector型の配列番号
	int MyEffectNum;
	// Effectの最大配列数(使ってるパーティクルの最大数)
	int MaxAryNum = 0;
	// 実行しているパーティクルの最大配列番号
	int IsUseMaxAryNum = -1;
	// アニメーション終了した時のdeleteフラグ
	bool DeleteFlag = false;


	EffectGame(void(EffectGame::*)());
	~EffectGame();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void E_end();     // エフェクト終了関数
	// ※ここから↑は触らない※


	//============================== ↓ エフェクト関数 ↓ ==============================//

	void E_game_Sample();     // エフェクト関数本体
	
////////////////////////////////////////////////////// タイトル(title) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// タイトル(title) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// チュートリアル(tutorial) //////////////////////////////////////////////////////
	void E_tutorial_AAA();
////////////////////////////////////////////////////// チュートリアル(tutorial) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////
	void E_game_ActionSucsess();
	void E_game_Baton1000P();
////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////



	//==============================	↑ エフェクト関数 ↑ ==============================//
};

// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付けてプロトタイプ宣言をする。
//============================== ↓ エフェクト再生関数 ↓ ==============================//

void call_E_game_Sample();     // エフェクト再生関数(呼び出し用)


////////////////////////////////////////////////////// タイトル(title) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// タイトル(title) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// チュートリアル(tutorial) //////////////////////////////////////////////////////
void call_E_tutorial_AAA();
////////////////////////////////////////////////////// チュートリアル(tutorial) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////
void call_E_game_ActionSucsess();
void call_E_game_Baton1000P();
////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////



//============================== ↑ エフェクト再生関数 ↑ ==============================//



// ※ここから↓は触らない※
// EffectGameMnager------------------------------------------VV
class EGManager:public EffectGame
{
public:
	// ゲームループ
	void Init();
	void Uninit();
	void Update();
	void Draw();
};