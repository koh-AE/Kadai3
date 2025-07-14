#include "EnemyBase.h"
#include "../../Utility/AsoUtility.h"
#include "../../Object/Player/Player.h"
#include "../Stage/Stage.h"
#include "EnemyManager.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}
void EnemyBase::Init(Player* player)
{
	//�v���C���[�̃|�C���^���擾
	player_ = player;
	//�ړ����x�̏�����
	moveSpeed_ = 5.0f;

	//�A�j���[�V����
	prevAnimType_ = ANIM_TYPE::WALK;
	nowAnimType_ = ANIM_TYPE::WALK;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;

	//�v���C���[�̕���������
	LookPlayer();
}

void EnemyBase::Load(void)
{
	//���f���̃��[�h
	modelId_ = MV1LoadModel("Data/Model/Enemy/Demon.mv1");
}

void EnemyBase::LoadEnd(void)
{
	//�A�j���[�V�����̏�����
	//���݂̃A�j���[�V�������A�^�b�`����
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	//�A�j���[�V�������Đ����Ԏ擾	attach=�A�j���[�V��������������
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);

}

void EnemyBase::Update(void)
{
	//�v���C���[�̕���������
	LookPlayer();

	//�ړ�
	Move();

	//�A�j���[�V�����̍X�V
	UpdateAnim();
}

void EnemyBase::Draw(void)
{
	//�`��
	MV1DrawModel(modelId_);
}

void EnemyBase::Release(void)
{
	//���f���̍폜
	MV1DeleteModel(modelId_);
}

void EnemyBase::LookPlayer(void)
{
	//�v���C���[�̌������v�Z VSub== �����Z
	VECTOR diff = VSub(player_->GetPos(), pos_);
	diff.y = 0.0f;
	//�x�N�g���𐳋K���i�����݂̂̏��ɕϊ��j
	moveDir_ = VNorm(diff);

	//�������p�x�ɕϊ�(x��y���͉�]�����Ȃ�)
	angle_.x = 0.0f;
	angle_.z = 0.0f;
	angle_.y = atan2f(moveDir_.x, moveDir_.z);

	//���f�����t�����������Ă���̂�Y���𔽓]
	angle_.y += AsoUtility::Deg2RadF(180.0f);

	//���f���̉�]�𔽉f������
	MV1SetRotationXYZ(modelId_, angle_);


}

void EnemyBase::Move(void)
{
	//�ړ����� VScale==�|���Z
	pos_ = VAdd(pos_, VScale(moveDir_, moveSpeed_));
	//�G�̈ړ�����
	if (pos_.x < 0.0f)
	{
		pos_.x = 0.0f;
	}
	if (pos_.x > Stage::STAGE_SIZE_X)
	{
		pos_.x = Stage::STAGE_SIZE_X;
	}
	if (pos_.z < 0.0f)
	{
		pos_.z = 0.0f;
	}
	if (pos_.z > Stage::STAGE_SIZE_Z)
	{
		pos_.z = Stage::STAGE_SIZE_Z;
	}


	//���f���̍��W�𔽉f������
	MV1SetPosition(modelId_, pos_);

}

void EnemyBase::UpdateAnim(void)
{
	//�A�j���[�V�������ύX���ꂽ�ǂ���
	if (prevAnimType_ != nowAnimType_)
	{
		//�A�j���[�V������ʂ����킹��
		prevAnimType_ = nowAnimType_;

		//���f������O��̃A�j���[�V�������O��
		MV1DetachAnim(modelId_, attachNo_);

		//�A�j���[�V������ύX����
		attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

		//�A�j���[�V�����̑��Đ����Ԃ��擾
		totalAnimTime_ = MV1GetAnimTotalTime(modelId_, attachNo_);

		//�A�j���[�V�������Ԃ�������
		nowAnimTime_ = 0;
	}
	//�A�j���[�V�����̎��Ԃ�i�߂�
	nowAnimTime_ += 1.0f;

	//�A�j���[�V���������[�v
	if (nowAnimTime_ > totalAnimTime_)
	{
		nowAnimTime_ = 0.0f;
	}

	//�A�j���[�V�����̐ݒ�
	MV1SetAttachAnimTime(modelId_, attachNo_, nowAnimTime_);
}