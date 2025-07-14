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

	//�o���Ԋu�̏�����
	spawnInterval_ = 0;

	//�S�ẴG�l�~�[����
	for (EnemyBase* enemy : enemys_)
	{
		//������
		enemy->Init(player_);
	}
}

void EnemyManager::Load(void)
{
	//�G�l�~�[�̐���
	//�G�l�~�[�̍ő吔���m�ۂ��Ă���
	for (int i = 0; i < ENEMY_MAX_NUM; i++)
	{
		//�G�l�~�[�̐���
		EnemyBase* enemy = new EnemyBase();
		enemy->Load();

		//�쐬�����G�l�~�[��z��ɓ����
		enemys_.push_back(enemy);
	}
}

void EnemyManager::LoadEnd(void)
{
	//�S�ẴG�l�~�[����
	for (EnemyBase* enemy : enemys_)
	{
		//�ǂݍ���
		enemy->LoadEnd();
	}
}


void EnemyManager::Update(void)
{
	for (EnemyBase* enemy : enemys_)
	{
		//�X�V
		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	for (EnemyBase* enemy : enemys_)
	{
		//�`��
		enemy->Draw();
	}
}

void EnemyManager::Release(void)
{
	for (EnemyBase* enemy : enemys_)
	{
		//���
		enemy->Release();
		delete enemy;
	}
	//�z����N���A
	enemys_.clear();
}