// 21000 タイトル画面

#include <algorithm>
#include <vector>
#include "title.h"
#include "scene.h"
#include "input.h"
#include  "main.h"
#include "DxLib.h"
#include "Live2D.h"
#include "GameObject.h"
#include "Menu.h"
#include "ActionUI.h"
#include "ActionSlot.h"
#include "GameData.h"

using namespace std;

Live2D Hiyori;

Menu TitleMenu(3);

GameObject test;

void Init_Title() {

	Hiyori.LoadModel(Live2DModelPassDict[LIVE2D_INDEX_HIYORI]);

	Hiyori.Zoom.x = 3.0f;
	Hiyori.Zoom.y = 3.0f;
	Hiyori.Pos.x = -300.0f;
	Hiyori.Pos.y = -450.0f;
	
	TitleMenu.Pos.x = 700.0f;
	TitleMenu.Pos.y = 100.0f;
	TitleMenu.FontSize = 64.0f;

	TitleMenu.SelectText.push_back("スタート");
	TitleMenu.SelectText.push_back("チュートリアル");
	TitleMenu.SelectText.push_back("終了");

	test.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);
	test.Object.Pos.x = 300;
	test.Object.Pos.y = 500;

}

void Uninit_Title() {

	Hiyori.~Live2D();

}

void Update_Title() {

	Hiyori.SetMontionIndex(GetRand(8));

	TitleMenu.Update();


	switch (TitleMenu.GetSelectNow())
	{
	case 0:
		if (keyboard.IsPress(DIK_RETURN) || joycon[LEFT_JOYCON].IsPress(JOYCON_L)) {
			Scene_Change(SCENE_INDEX_GAME);
		}
		break;
	case 1:
		break;
	case 2:
		if (keyboard.IsPress(DIK_RETURN) || joycon[LEFT_JOYCON].IsPress(JOYCON_L)) {
			exit(1);
		}
		break;
	default:
		break;
	}

	if (keyboard.IsTrigger(DIK_Z)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

	/*
	if (keyboard.IsPress(DIK_RIGHTARROW)) {
		Hiyori.Pos.x += 5.0f;
		Hiyori.Zoom.x += 0.005f;
		Hiyori.Zoom.y += 0.005f;
		Hiyori.Pos.y -= 1.0f;
	}
	if (keyboard.IsPress(DIK_LEFTARROW)) {
		Hiyori.Pos.x -= 5.0f;
		Hiyori.Zoom.x -= 0.005f;
		Hiyori.Zoom.y -= 0.005f;
		Hiyori.Pos.y += 1.0f;
	}
	*/
}

void Draw_Title() {

	Hiyori.Draw();

	TitleMenu.Draw();

	//test.Draw();


}