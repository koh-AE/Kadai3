#include "Loading.h"
#include <DxLib.h>
#include "../Application/Application.h"

Loading* Loading::instance_ = nullptr;

static constexpr int MIN_LOAD_TIME = 60; // ロード画面の表示時間（フレーム数）

Loading::Loading() {};
Loading::~Loading() {};

void Loading::Init(void)
{
	loadTimer_ = 0;
	isLoading_ = false;

	posX_ = Application::SCREEN_SIZE_X / 2;
	posY_ = Application::SCREEN_SIZE_Y / 2;
}

void Loading::Load(void)
{
	handle_ = LoadGraph("Data/Image/Axe.png");
 }

void Loading::Update(void)
{
	loadTimer_++;

	//読み込み中のものが無くなったら
	if (GetASyncLoadNum() == 0 && loadTimer_ >= MIN_LOAD_TIME)
	{
		//ロード終了
		Init();
	}
	//読み込み中
	else
	{
		//ロード画面で遊びを入れるならここに記述
	}
}

void Loading::Draw(void)
{
	DrawRotaGraph(
		posX_,	// X座標
		posY_,	// Y座標
		1.0,	//拡大値
		0.0,	//回転角度
		handle_,//画像ハンドル
		true);	//透明色を使用するか
}

void Loading::Release(void)
{
	DeleteGraph(handle_);
}

void Loading::StartAsybcLoad(void)
{
	isLoading_ = true;
	SetUseASyncLoadFlag(true); // 非同期ロードを有効にする
}

void Loading::EndAsyncLoad(void)
{
	SetUseASyncLoadFlag(false); // 非同期ロードを無効にする
}

bool Loading::IsLoading(void)
{
	return isLoading_;
}
