#include <algorithm>
#include <vector>
#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"
#include "ActionSlot.h"
#include "ActionUI.h"
#include "GameData.h"
#include "Live2D.h"
#include "gameprogress.h"
#include "Staminagauge.h"
#include "ActionAffect.h"
#include "BackGround.h"
#include "GameOver.h"

// Debug Mode
#define DEBUG

/* 
プロトタイプ宣言
*/

// 走る処理
void Running();
// Debugパネル
void Debug_Panel();
// キャラクター処理
void CharacterMove();
// Debug走る (キーボード)
void Debug_Running();

/*
グローバル変数
*/

// スビート計算用
std::vector<int> Speed_Array;
static int Max_Count;
static int Judge_Count;
// アクションUI
ActionUI Action;
// アクションゲージ
ActionSlot Actionslot;
// アクション失敗画像
GameObject Failed;
// Live2Dキャラクター
Live2D Character;
// ゲーム進行バー
GameProgress *gameprogress;
// スタミナゲージ
StaminaGauge *stamina;

BackGround background;

GameOver gameover;
// アクションエフェクト用
std::vector<ActionAffect*> ActionEffectVector;

std::vector <ActionPointAnime*> ActionPointVector;

void Init_Game() {

	gameprogress = new GameProgress;
	stamina = new StaminaGauge;

	//スタミナゲージ初期化
	stamina->Init();

	// アクションUI初期化	

	Action.Init();

	Action.Pos.x = 700;

	Action.Pos.y = 200;

	Action.Interval.x = 150;

	Action.Interval.y = 0;

	// アクションゲージ初期化

	Actionslot.Load();

	Actionslot.Pos.x = 330;

	Actionslot.Pos.y = 450;

	// キャラクター初期化

	Character.LoadModel(Live2D_Dict["HIYORI"]);

	Character.Zoom.x = 1.0f;

	Character.Zoom.y = 1.0f;

	Character.Pos.x = -400;

	Character.Pos.y = -150;

	// アクション失敗初期化

	Failed.LoadTexture(TexturePassDict[TEXTURE_INDEX_END]);

	Failed.Object.Pos.x = 600;

	Failed.Object.Pos.y = 200;

	// ゲームデータ初期化

	gamedata.Init();

	//ゲーム進行バー初期化
	gameprogress->Init();

	background.Init();

	gameover.Init();
}

void Uninit_Game() {

	Character.~Live2D();

	gameprogress = nullptr;
	delete gameprogress;

	stamina = nullptr;
	delete stamina;

	ActionEffectVector.~vector();
	ActionPointVector.~vector();
	
}

void Update_Game() {

	//スタミナゲージ更新処理
	stamina->Update();

	Character.SetMontionIndex(GetRand(8));

	// アクションUI更新
	Action.Update();
	// アクションゲージ更新
	Actionslot.Update(stamina->GetStaminaScale_x());
	// スビート更新
	gamedata.UpdateSpeed();

	// 走る処理
	Running();

	// ゲーム進行バー処理
	//gameprogress->Update();

	// キャラクター処理
	CharacterMove();

	gameover.Update();

	// アクションエフェクト処理
	for (int i = 0; i < ActionEffectVector.size(); i++) {
		if (ActionEffectVector[i] != NULL) {
			ActionEffectVector[i]->Update();
		}
	}

	for (int i = 0; i < ActionPointVector.size(); i++) {
		if (ActionPointVector[i]->OutFlag) {
			continue;
		}
		ActionPointVector[i]->Update();
	}

	
	background.SetSpeed(1.0);

	if (gamedata.Gethp() <= 0) {
		background.SetSpeed(0);
	}

	background.Update();

	// アクション完成判定
	if (Action.GetFinishFlag()) {
		if (Action.GetProgress() == Action.GetActionAmount()) {
			Actionslot.AddValue(0.5);
			
		}
		else {
		
		}
	}

#ifdef DEBUG

	// Go Title
	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

	// Go Result
	if (keyboard.IsTrigger(DIK_ESCAPE)) {
		Scene_Change(SCENE_INDEX_RESULT);
	}

	// Remove Trash
	if (keyboard.IsPress(DIK_Q)) {

		std::vector<ActionAffect*>().swap(ActionEffectVector);
		std::vector<ActionPointAnime*>().swap(ActionPointVector);
	}

	if (keyboard.IsPress(DIK_E)) {
		Actionslot.AddValue(0.5);
	}

	Debug_Running();

#endif // DEBUG

	
}

void Draw_Game() {

	background.Draw();

	// アクションエフェクト描画
	for (int i = 0; i < ActionEffectVector.size(); i++) {
		if (ActionEffectVector[i] != NULL) {
			ActionEffectVector[i]->Draw_Affect();
		}
	}

	for (int i = 0; i < ActionPointVector.size(); i++) {
		ActionPointVector[i]->Draw();
	}


	// アクションゲージ描画
	Actionslot.Draw();

	Character.Draw();
	
	//スタミナゲージ描画
	stamina->Draw();

	// アクションUI描画
	Action.Draw();
	
	gameprogress->Draw();

	gameover.Draw();
	

#ifdef DEBUG
	Debug_Panel();
#endif // DEBUG

}

void Running() {

	if (joycon[1].GetGyro_Y() > 150) {
		joycon[1].Action_Judge[0] = true;
		Speed_Array.push_back(joycon[1].GetGyro_Y());
	}

	if (joycon[1].Action_Judge[0] && joycon[1].GetGyro_Y() < -200) {
		joycon[1].Action_Judge[1] = true;
	}

	if (joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].GetGyro_Y() > 150) {
		joycon[1].Action_Judge[2] = true;
	}

	if ((joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].Action_Judge[2])) {
		for (int i = 0; i < 3; i++) {
			joycon[1].Action_Judge[i] = false;
		}
		vector<int>::iterator iter = max_element(Speed_Array.begin(), Speed_Array.end());
		Max_Count = *iter;
		Judge_Count += Max_Count;

		if (Judge_Count > 1000) {
			gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
			Judge_Count = 0;
		}

		gamedata.SetRunningSpeed(405);

		Speed_Array.clear();


		ActionPointAnime *obj = new ActionPointAnime();

		ActionAffect *tmp = new ActionAffect(Actionslot.GetState());

		switch (Actionslot.GetState())
		{
		case ACTIONSLOT_OVER:
			obj->Create(150);
			break;
		case ACTIONSLOT_GREAT:
			obj->Create(120);
			break;
		case ACTIONSLOT_GOOD:
			obj->Create(50);
			break;
		case ACTIONSLOT_BAD:
			break;
		}

		ActionEffectVector.push_back(tmp);

		ActionPointVector.push_back(obj);
	}

	if (gamedata.GetRunningSpeed() > 0) {
		gamedata.AddRunningSpeed(-15);
	}

	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
}

void CharacterMove() {

	// 右

	if (gamedata.GetRunningSpeed() >= 150 && Character.Zoom.x < 1.3) {

		Character.Pos.x += 5.0f;

		Character.Zoom.x += 0.0025f;

		Character.Zoom.y += 0.0025f;

		Character.Pos.y -= 0.75f;

		Actionslot.Pos.x += 5.0f;

		Actionslot.Pos.y += 0.75f;

		Actionslot.Scale += D3DXVECTOR2(0.0025f, 0.0025f);

		Actionslot.Fire_Offset += D3DXVECTOR2(0.75f, 0.15f);

		Actionslot.offsect_dis += 0.03;
	}

	// 左

	if (gamedata.GetRunningSpeed() <= 30 && Character.Zoom.x > 1.0) {

		Character.Pos.x -= 5.0f;

		Character.Zoom.x -= 0.0025f;

		Character.Zoom.y -= 0.0025f;

		Character.Pos.y += 0.75f;

		Actionslot.Pos.x -= 5.0f;

		Actionslot.Pos.y -= 0.75f;

		Actionslot.Scale -= D3DXVECTOR2(0.0025f, 0.0025f);

		Actionslot.Fire_Offset -= D3DXVECTOR2(0.75f, 0.15f);

		Actionslot.offsect_dis -= 0.03;
	}

}

void Debug_Running() {

	if (keyboard.IsTrigger(DIK_RIGHTARROW)) {
		Judge_Count += 350;
	}

	if (Judge_Count >= 350) {

		gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

		gamedata.SetRunningSpeed(405);

		Judge_Count = 0;

		gamedata.Action_Point_Update(Actionslot.GetState());
		
		ActionPointAnime *obj = new ActionPointAnime();

		ActionAffect *tmp = new ActionAffect(Actionslot.GetState());

		switch (Actionslot.GetState())
		{
		case ACTIONSLOT_OVER:
			obj->Create(150);
			break;
		case ACTIONSLOT_GREAT:
			obj->Create(120);
			break;
		case ACTIONSLOT_GOOD:
			obj->Create(50);
			break;
		case ACTIONSLOT_BAD:
			break;
		}
		
		ActionEffectVector.push_back(tmp);

		ActionPointVector.push_back(obj);
		
	}

	if (gamedata.GetRunningSpeed() > 0) {

		gamedata.AddRunningSpeed(-15);

	}

	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

}

void Debug_Panel() {

	SetFontSize(24);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "走る距離 : %d", gamedata.GetRunningMeter());

	DrawFormatString(0, 30, GetColor(255, 255, 255), "アクションゲージ : %f", Actionslot.GetValue());

	DrawFormatString(0, 60, GetColor(255, 255, 255), "アクションゲージ状態 : %d", Actionslot.GetState());

	DrawFormatString(0, 90, GetColor(255, 255, 255), "アクション状態 : %d", Action.GetState());

	DrawFormatString(0, 120, GetColor(255, 255, 255), "スビート : %d", gamedata.GetRunningSpeed());

	DrawFormatString(0, 150, GetColor(255, 255, 255), "聖火 : %d", gamedata.Gethp());

	DrawFormatString(0, 180, GetColor(255, 255, 255), "アクションポイント： %d", gamedata.GetActionPoint());

	//DrawFormatString(0, 210, GetColor(255, 255, 255), "経過:%d秒",gameprogress->stime / 60);

	DrawFormatString(0, 240, GetColor(255, 255, 255), "ゲームモード: %d ",gamedata.GetGameMode());


}