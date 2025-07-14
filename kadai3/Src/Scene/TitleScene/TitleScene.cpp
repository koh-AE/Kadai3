#include "TitleScene.h"
#include <DxLib.h>
#include "../SceneManager/SceneManager.h"
#include "../../Input/InputManager.h"
#include "../../Application/Application.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
}

void TitleScene::Load(void)
{
	handle_ = LoadGraph("Data/Image/Title.png");
}

void TitleScene::LoadEnd(void)
{
	Init();
}

void TitleScene::Update(void)
{
	//次のシーンへ遷移
	toNextScene();
}

void TitleScene::Draw(void)
{
	DrawExtendGraph(
		0.0,
		0.0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,		
		handle_,
		true
	);
}

void TitleScene::Release(void)
{
	DeleteGraph(handle_);
}

void TitleScene::toNextScene(void)
{
	//シーン遷移
	//スペースキーが押されたら
	if (InputManager::GetInstance()->IsTrgUp(KEY_INPUT_SPACE))
	{
		//ゲームシーンへ
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}
