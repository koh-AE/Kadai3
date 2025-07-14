#include "GameScene.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyBase.h"


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	// グリッドの初期化
	grid_->Init();
	// カメラの初期化
	Camera::GetInstance()->Init();
	//ステージの初期化
	stage_->Init();
	//プレイヤーの初期化
	player_->Init();
	//エネミーの初期化
	enemy_->Init(player_);
}

void GameScene::Load(void)
{
	//グリッドの生成
	grid_ = new Grid();

	//カメラの生成
	Camera::CreateInstance();

	//ステージの生成
	stage_ = new Stage();
	stage_->Load();

	//プレイヤーの生成
	player_ = new Player();
	player_->Load();

	//エネミーの生成
	enemy_ = new EnemyBase();
	enemy_->Load();
}

void GameScene::LoadEnd(void)
{
	//初期化
	Init();

	//ステージの読み込み後
	stage_->LoadEnd();

	player_->LoadEnd();

	enemy_->LoadEnd();
}

void GameScene::Update(void)
{
	//グリッドの更新
	grid_->Update();
	//カメラの更新
	Camera::GetInstance()->Update();
	//ステージの更新
	stage_->Update();
	//ステージの更新
	player_->Update();
	//プレイヤーの更新
	enemy_->Update();
	//衝突判定
	Collision();
}

void GameScene::Draw(void)
{
	//グリッドの描画
	grid_->Draw();
	//カメラの描画
	Camera::GetInstance()->SetBeforeDraw();
	Camera::GetInstance()->DebugDraw();


	//ステージの描画
	stage_->Draw();

	//プレイヤーの描画
	player_->Draw();

	//エネミーの描画
	enemy_->Draw();
}

void GameScene::Release(void)
{
	//グリッドの解放
	grid_->Release();
	delete grid_;

	//カメラの解放
	Camera::GetInstance()->Release();
	Camera::DeleteInstance();

	//ステージの解放
	stage_->Release();
	delete stage_;

	//プレイヤーの解放
	player_->Release();
	delete player_;

	//エネミーの解放
	enemy_->Release();
	delete enemy_;
}

void GameScene::DebugDraw(void)
{

}

void GameScene::Collision(void)
{
	//ステージとプレイヤーの当たり判定
	CollisionStage();
}

void GameScene::CollisionStage(void)
{
	//プレイヤーの座標取得
	VECTOR playerPos = player_->GetPos();

	//線分の上座標
	VECTOR topPos = playerPos;
	topPos.y = playerPos.y + (Player::COLL_LINE_LEN * 2.0);

	//線分の下座標
	VECTOR downPos = playerPos;
	downPos.y = playerPos.y - Player:: COLL_LINE_LEN;

	//デバッグ用に確保
	lineTopPos_ = topPos;
	lineDownPos_ = downPos;

	//線分とブロックの衝突判定
	tagMV1_COLL_RESULT_POLY result;

	//当たっているか
	if (stage_->IsCollLine(topPos, downPos, &result))
	{
		//プレイヤーの衝突座標
		player_->CollisionStage(result.HitPosition);
	}

}
