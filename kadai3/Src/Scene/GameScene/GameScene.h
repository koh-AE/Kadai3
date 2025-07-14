#pragma once
#include "../SceneBase.h"
#include <DxLib.h>


//�N���X�̑O���錾
class Grid;
class Stage;
class Player;
class EnemyBase;

//�x�[�X�̌p��
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene() override;

	void Init(void) override; // ������
	void Load(void) override; // �ǂݍ���
	void LoadEnd(void) override; // �ǂݍ��ݏI���
	void Update(void) override; // �X�V
	void Draw(void) override; // �`��
	void Release(void) override; // �������

private:
	//�f�o�b�N�`��
	void DebugDraw(void);

	//���̃f�o�b�O�\��
	VECTOR lineTopPos_;
	VECTOR lineDownPos_;

	//�Փ˔���
	void Collision(void);

	//�X�e�[�W�ƃv���C���[�̏Փ˔���
	void CollisionStage(void);
private:
	Grid* grid_; // �O���b�h�N���X

	Stage* stage_;	//�X�e�[�W�N���X
	Player* player_;
	EnemyBase* enemy_;
};