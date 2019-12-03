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
#include "GameOver.h"


static GameObject obj[1];

GameOver::GameOver() 
{

}

GameOver::~GameOver()
{

}

void GameOver::Init() 
{
	titleflag = false;
	objflag = false;
	TimeCount = SECONDS;
}


void GameOver::Uninit()
{

}

void GameOver::Update()
{
	GameOverisUse();
}

void GameOver::Draw() 
{
	obj[0].Draw();
}

/*
bool GameOver::GetisUse()
{
	return isUse;
}
*/

void GameOver::GameOverisUse()
{

	if (gamedata.Gethp() == 0)
	{
		//�Q�[���I�[�o�[�X�e�[�g�ɓ���
		TimeCount++;
		objflag = true;

		//�Q�[���I�[�o�[�e�N�X�`���̕\��
		if (objflag == true)
		{
			obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_GAME_OVER]);
			obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
			obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
			obj[0].Object.Scale.x = 1.5;
			obj[0].Object.Scale.y = 1.5;
		}

		if (TimeCount > 120.0f)
		{
			titleflag = true;

			//�^�C�g���֖߂�̕\��

		}
		if (titleflag == true && keyboard.IsTrigger(DIK_Z)) {
			Scene_Change(SCENE_INDEX_TITLE);

		}

	}

}