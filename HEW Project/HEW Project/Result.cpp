#include "main.h"
#include "Result.h"
#include "input.h"
#include "scene.h"
#include "GameData.h"
#include "GameObject.h"
#include <DxLib.h>
#include "ResultScore.h"


static GameObject obj[2];
static ResultScore score[6];
static ResultScore ui;
static int g_TotalScore;
double ranking[RANKING_MAX] = { 0,0,0,0,0 };
double Runranking[RANKING_MAX] = { 0,0,0,0,0 };

// 走ったキョリランキングを作る(リザルトに表示はしない)


void Init_Result()
{

	//走った距離
	int Distance_p = gamedata.GetRunningDistance();

	//アクションポイント
	int Action_p = gamedata.GetActionPoint();

	//合計スコア
	g_TotalScore = ((Distance_p * 3 / 2 + (Action_p * 2) / 2)*2);


	//ランキングの読み込み
	Ranking_Read();

	//ソートしたランキングの反映
	Ranking_Sort(g_TotalScore);

	// 走ったキョリランキングをソートしてバイナリファイルに書き込み
	RunningRanking_Wright(Distance_p);

	//画面の背景表示
	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
	obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	obj[0].Object.Scale.x = 1.00f;
	obj[0].Object.Scale.y = 1.00f;

	obj[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_RESULT_BG]);
	obj[1].Object.Pos.x = 400.0f;
	obj[1].Object.Pos.y = 460.0f;
	obj[1].Object.Scale.x = 0.75f;
	obj[1].Object.Scale.y = 0.75f;


	ui.Init();
	
	//ランキングの表示
	for (int i = 0; i < RANKING_MAX; i++)
	{
		score[i].ScoreCreate(ranking[i], SCREEN_WIDTH / 2 - 200, 100*i);

	}

	//合計スコアの表示
	score[5].ScoreCreate(g_TotalScore, SCREEN_WIDTH / 2 - 200, 600);

}

void Uninit_Result()
{

}

void Update_Result()
{
	ui.Update();

	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Result()
{

	obj[0].Draw();
	obj[1].Draw();


	for (int i = 0; i < RANKING_MAX; i++)
	{
		DrawFormatString(0, i*30, GetColor(255, 255, 255), "%d 位", i + 1);

		DrawFormatString(100, i*30, GetColor(255, 255, 255), "%f \n", ranking[i]);

	}


	//DrawFormatString(0, 0, GetColor(255, 255, 255), "走った距離:%d", gamedata.GetRunningDistance());

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "アクションポイント:%d", gamedata.GetActionPoint());


	DrawFormatString(500, 0, GetColor(255, 255, 255), "合計:%d", g_TotalScore);

	score[0].Draw();
	score[1].Draw();
	score[2].Draw();
	score[3].Draw();
	score[4].Draw();
	score[5].Draw();

	ui.Draw();
}




void Ranking_Sort(double score) {
	FILE* fp;
	
	fopen_s(&fp, "file.bin", "wb");

	if (fp == NULL)
	{
		printf("%sのオープンに失敗しました。\n", "file.bin");
		return;
	}

	int i;
	int j;

	//ランキングの降順処理
	for (i = 0; i < RANKING_MAX; i++) {//1位から比較
		//今の順位よりも高ければそれが今回の順位となる
		//(1位より高ければ1位、1位より低く2位より高ければ2位、…)
		if (score > ranking[i]) {
			for (j = RANKING_MAX - 1; j > i; j--) {//今回の順位以降のスコアをずらす
				ranking[j] = ranking[j - 1];
			}
			ranking[i] = score;//今回のスコアを記憶
			break;//以降の順位は調べない
		}
	}
	//ランキングの保存
	fwrite(ranking, sizeof(ranking), 5, fp);

	fclose(fp);
}

void Ranking_Read() {

	FILE* fp;

	fopen_s(&fp, "file.bin", "rb");

	if (fp == NULL)
	{
		printf("%sのオープンに失敗しました。\n", "file.bin");
		return;
	}

	fread(ranking, sizeof(ranking), 5, fp);
	fclose(fp);
}


// 走ったキョリランキング(今回の走ったキョリ)
void RunningRanking_Wright(double RunningDistans)
{
	FILE* fp_Running;     // ファイルポインタ
	const char* FileName = "RunningRunkingFile.bin";     // ファイルネーム

	//================= ランキングファイル読み取り =================//
	fopen_s(&fp_Running, FileName, "rb");
	if (fp_Running == NULL){ printf_s("%s ファイルが開けませんでした。", FileName); exit(1); }
	fread(Runranking, sizeof(Runranking), 5, fp_Running);     // 走ったキョリランキングに上位５個を読み取り
	fclose(fp_Running);
	//================= ランキングファイル読み取り =================//



	//================= ランキングソート =================//
	fopen_s(&fp_Running, FileName, "wb");
	if (fp_Running == NULL) { printf_s("%s ファイルが開けませんでした。", FileName); exit(1); }
	//// ランキングの降順処理 ////
	int i, j;
	for (i = 0; i < RANKING_MAX; i++) {//1位から比較
		//今の順位よりも高ければそれが今回の順位となる
		//(1位より高ければ1位、1位より低く2位より高ければ2位、…)
		if (RunningDistans > Runranking[i]) {
			for (j = RANKING_MAX - 1; j > i; j--) {//今回の順位以降のスコアをずらす
				Runranking[j] = Runranking[j - 1];
			}
			Runranking[i] = RunningDistans;//今回のスコアを記憶
			break;//以降の順位は調べない
		}
	}
	fwrite(Runranking, sizeof(Runranking), 5, fp_Running);     // ランキングの保存
	fclose(fp_Running);
	//================= ランキングソート =================//

}