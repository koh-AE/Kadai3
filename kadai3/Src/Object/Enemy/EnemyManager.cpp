#include "EnemyManager.h"
#include "EnemyBase.h"

EnemyManager::EnemyManager(void)
{
}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(Player* player)
{
	player_ = player;

	//出現間隔の初期化
	spawnInterval_ = 0;

	//全てのエネミーを回す
	for (EnemyBase* enemy : enemys_)
	{
		//初期化
		enemy->Init(player_);
	}
}

void EnemyManager::Load(void)
{
	//エネミーの生成
	//エネミーの最大数を確保しておく
	for (int i = 0; i < ENEMY_MAX_NUM; i++)
	{
		//エネミーの生成
		EnemyBase* enemy = new EnemyBase();
		enemy->Load();

		//作成したエネミーを配列に入れる
		enemys_.push_back(enemy);
	}
}

void EnemyManager::LoadEnd(void)
{
	//全てのエネミーを回す
	for (EnemyBase* enemy : enemys_)
	{
		//読み込み
		enemy->LoadEnd();
	}
}


void EnemyManager::Update(void)
{
	for (EnemyBase* enemy : enemys_)
	{
		//更新
		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	for (EnemyBase* enemy : enemys_)
	{
		//描画
		enemy->Draw();
	}
}

void EnemyManager::Release(void)
{
	for (EnemyBase* enemy : enemys_)
	{
		//解放
		enemy->Release();
		delete enemy;
	}
	//配列をクリア
	enemys_.clear();
}