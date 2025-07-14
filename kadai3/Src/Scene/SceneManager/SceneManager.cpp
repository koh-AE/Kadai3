#include "SceneManager.h"
#include <DxLib.h>
#include "../TitleScene/TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../../Loading/Loading.h"
SceneManager* SceneManager::instance_ = nullptr;

SceneManager::SceneManager(void)
{
}

SceneManager::~SceneManager(void)
{
}

void SceneManager::Init(void)
{
	//ロード画面の生成
	Loading::CreateInstance();
	Loading::GetInstance()->Load();
	Loading::GetInstance()->Init();

	//3D情報の初期化
	Init3D();

	//最初はタイトルシーン
	ChangeScene(SCENE_ID::TITLE);
}


void SceneManager::Init3D(void)
{
	//背景色設定
	SetBackgroundColor(0, 0, 0);

	//Zバッファを有効
	SetUseZBuffer3D(true);

	//Zバッファへの書き込み
	SetWriteZBuffer3D(true);

	//バックカリングを有効化
	SetUseBackCulling(true);

	//ライトの設定
	SetUseLighting(true);

	//正面から斜め下に向かったライト
	ChangeLightTypeDir({ 0.0f,-1.0f, 1.0f });
}

void SceneManager::Update(void)
{

	//ロード中
	//もしロード中だったら
	if (Loading::GetInstance()->IsLoading())
	{
		//ロード更新
		Loading::GetInstance()->Update();

		//ロードが終了していたら
		if (Loading::GetInstance()->IsLoading() == false)
		{
			//ロード後の初期化
			scene_->LoadEnd();
		}
	}
	//通常の更新処理
	else
	{
		//シーンの更新
		scene_->Update();
	}
}

void SceneManager::Draw(void)
{
	//ロード中ならロード画面を描画
	if (Loading::GetInstance()->IsLoading())
	{
		//ロード画面
		Loading::GetInstance()->Draw();
	}
	//通常画面
	else
	{
		//現在のシーンを描画
		scene_->Draw();
	}
}

void SceneManager::Release(void)
{
	//現在のシーンを解放・削除
	scene_->Release();
	delete scene_;

	//ロード画面の解放
	Loading::GetInstance()->Release();
	Loading::DeleteInstance();
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{
	//シーンを変更する
	sceneId_ = nextId;

	//現在のシーンを開放
	if (scene_ != nullptr)
	{
		scene_->Release();	//現在のシーンを開放
		delete scene_;		//シーンの削除
	}

	//各シーンに切り替える
	switch (sceneId_)
	{
	case SceneManager::SCENE_ID::NONE:
		break;
	case SceneManager::SCENE_ID::TITLE:
		scene_ = new TitleScene();	
		break;
	case SceneManager::SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	default:
		break;
	}

	//初期化
	Loading::GetInstance()->StartAsybcLoad();	// 非同期ロード開始
	scene_->Load();								// シーンのロード
	Loading::GetInstance()->EndAsyncLoad();		// 非同期ロード終了
}
