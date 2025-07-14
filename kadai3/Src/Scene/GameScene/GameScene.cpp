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
	// �O���b�h�̏�����
	grid_->Init();
	// �J�����̏�����
	Camera::GetInstance()->Init();
	//�X�e�[�W�̏�����
	stage_->Init();
	//�v���C���[�̏�����
	player_->Init();
	//�G�l�~�[�̏�����
	enemy_->Init(player_);
}

void GameScene::Load(void)
{
	//�O���b�h�̐���
	grid_ = new Grid();

	//�J�����̐���
	Camera::CreateInstance();

	//�X�e�[�W�̐���
	stage_ = new Stage();
	stage_->Load();

	//�v���C���[�̐���
	player_ = new Player();
	player_->Load();

	//�G�l�~�[�̐���
	enemy_ = new EnemyBase();
	enemy_->Load();
}

void GameScene::LoadEnd(void)
{
	//������
	Init();

	//�X�e�[�W�̓ǂݍ��݌�
	stage_->LoadEnd();

	player_->LoadEnd();

	enemy_->LoadEnd();
}

void GameScene::Update(void)
{
	//�O���b�h�̍X�V
	grid_->Update();
	//�J�����̍X�V
	Camera::GetInstance()->Update();
	//�X�e�[�W�̍X�V
	stage_->Update();
	//�X�e�[�W�̍X�V
	player_->Update();
	//�v���C���[�̍X�V
	enemy_->Update();
	//�Փ˔���
	Collision();
}

void GameScene::Draw(void)
{
	//�O���b�h�̕`��
	grid_->Draw();
	//�J�����̕`��
	Camera::GetInstance()->SetBeforeDraw();
	Camera::GetInstance()->DebugDraw();


	//�X�e�[�W�̕`��
	stage_->Draw();

	//�v���C���[�̕`��
	player_->Draw();

	//�G�l�~�[�̕`��
	enemy_->Draw();
}

void GameScene::Release(void)
{
	//�O���b�h�̉��
	grid_->Release();
	delete grid_;

	//�J�����̉��
	Camera::GetInstance()->Release();
	Camera::DeleteInstance();

	//�X�e�[�W�̉��
	stage_->Release();
	delete stage_;

	//�v���C���[�̉��
	player_->Release();
	delete player_;

	//�G�l�~�[�̉��
	enemy_->Release();
	delete enemy_;
}

void GameScene::DebugDraw(void)
{

}

void GameScene::Collision(void)
{
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	CollisionStage();
}

void GameScene::CollisionStage(void)
{
	//�v���C���[�̍��W�擾
	VECTOR playerPos = player_->GetPos();

	//�����̏���W
	VECTOR topPos = playerPos;
	topPos.y = playerPos.y + (Player::COLL_LINE_LEN * 2.0);

	//�����̉����W
	VECTOR downPos = playerPos;
	downPos.y = playerPos.y - Player:: COLL_LINE_LEN;

	//�f�o�b�O�p�Ɋm��
	lineTopPos_ = topPos;
	lineDownPos_ = downPos;

	//�����ƃu���b�N�̏Փ˔���
	tagMV1_COLL_RESULT_POLY result;

	//�������Ă��邩
	if (stage_->IsCollLine(topPos, downPos, &result))
	{
		//�v���C���[�̏Փˍ��W
		player_->CollisionStage(result.HitPosition);
	}

}
