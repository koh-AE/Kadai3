#pragma once
#include <DxLib.h>

//�N���X�̑O���錾
class Player;

class EnemyBase
{
public:
	//�A�j���[�V�������
	enum class ANIM_TYPE
	{
		WALK = 6,	//���s
	};
public:
	EnemyBase();
	~EnemyBase();

	void Init(Player* player);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//�����t���O��ݒ肷��
	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }

	//�����t���O���擾����
	bool GetIsAlive(void) { return isAlive_; }

private:
	//�v���C���[�̕���������
	void LookPlayer(void);

	//�ړ�
	void Move(void);

	//�A�j���[�V�����X�V
	void UpdateAnim(void);

private:
	//�v���C���[�̏��A�h���X
	Player* player_;

	//���f���̃n���h��ID
	int  modelId_;
	//�����t���O
	bool isAlive_;
	//���W
	VECTOR pos_;
	//�p�x
	VECTOR angle_;
	//�傫��
	VECTOR scale;
	//�ړ�����
	VECTOR moveDir_;
	//�ړ����x
	float moveSpeed_;

	//�A�j���[�V����
	ANIM_TYPE prevAnimType_;	//�O��̃A�j���[�V����
	ANIM_TYPE nowAnimType_;		//���݂̃A�j���[�V����

	//�A�j���[�V����
	int attachNo_;			//�A�j���[�V�����̔ԍ�
	float nowAnimTime_;		//�Đ����̎���
	float totalAnimTime_;	//���Đ�����
};
