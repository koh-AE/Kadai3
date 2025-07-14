#include "Player.h"
#include "../../Utility/AsoUtility.h"
#include "../../Input/InputManager.h"
#include "../../Camera/Camera.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(void)
{
	//���f���𓮂������ԁ@	�傫�����p�x�����W
	//���f���̃T�C�Y
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	//���f���̊p�x
	angle_ = AsoUtility::VECTOR_ZERO;
	MV1SetRotationXYZ(modelId_, angle_);

	//���f�����W
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	//���Ȕ���
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);

	//�W�����v�͂̏�����
	JumpPow_ = 0.0f;

	//�A�j���[�V����
	prevAnimType_ = ANIM_TYPE::IDLE;
	nowAnimType_ = ANIM_TYPE::IDLE;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;
}

void Player::Load(void)
{
	//���f���̃��[�h
	modelId_ = MV1LoadModel("Data/Model/Player/Player.mv1");
}

void Player::LoadEnd(void)
{
	//������
	Init();

	//�A�j���[�V�����̏�����
	//���݂̃A�j���[�V�������A�^�b�`����
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	//�A�j���[�V�������Đ����Ԏ擾	attach=�A�j���[�V��������������
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);

}

void Player::Update(void)
{
	//�ړ�����
	ProcessMove();

	//�W�����v����
	ProcessJump();

	//�A�j���[�V�����̍X�V
	UpdateAnim();

	//�J�����ɍ��W��n��
	Camera::GetInstance()->SetFollowPos(pos_);
}

void Player::Draw(void)
{
	//���f���̕`��
	MV1DrawModel(modelId_);
}

void Player::Release(void)
{
	MV1DeleteModel(modelId_);
}

VECTOR Player::GetPos(void)
{
	return pos_;
}

void Player::CollisionStage(VECTOR pos)
{
	//�Փ˂��Ĉʒu��߂�
	pos_ = pos;
	JumpPow_ = 0.0f;
}

void Player::ProcessMove(void)
{
	//�ړ����������߂�
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	//����� IsNew==�������I��
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W))
	{
		moveDir = AsoUtility::DIR_F;
	}
	//������
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S))
	{
		moveDir = AsoUtility::DIR_B;
	}
	//�E����
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D))
	{
		moveDir = AsoUtility::DIR_R;
	}
	//������
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A))
	{
		moveDir = AsoUtility::DIR_L;
	}

	//�ړ����Ă����� Equals == �������@!==not
	//VSZero�Ɠ�������
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		//���f���̈ړ�������Y����]������
		//�����p�x�i���W�A��(0������180��)�j�ɕϊ�
		angle_.y = atan2(moveDir.x, moveDir.z);

		//���f�������]���Ă���̂ŋ����I�ɉ�]������  Deg2RadF
		angle_.y += AsoUtility::Deg2RadF(180.0f);

		//���f���ɉ�]��ݒ�
		MV1SetRotationXYZ(modelId_, angle_);
		
		//�ړ��ʂ��v�Z����(�������@�X�s�[�h)
		VECTOR movePos = VScale(moveDir, MOVE_SPEED);

		//�ړ������i���W�@�{�@�ړ��ʁj
		pos_ = VAdd(pos_, moveDir);

		//���f�����W��ݒ肷��
		MV1SetPosition(modelId_, pos_);

		//�A�j���[�V������ύX����
		nowAnimType_ = ANIM_TYPE::WALK;
	}
	else
	{
		//�ړ����Ă��Ȃ�

		//�A�j���[�V������ύX����
		nowAnimType_ = ANIM_TYPE::IDLE;
	}
}

void Player::ProcessJump(void)
{
	//�d��
	JumpPow_ -= GRAVITY;

	//�v���C���[���W�ɃW�����v�����Z����
	pos_.y += JumpPow_;

	//�Փ˔���O�̗�������
	if (pos_.y < -1000.0f)
	{
		//������
		Init();
	}

	//���f���̍��W��ݒ肷��
	MV1SetPosition(modelId_, pos_);

}

void Player::UpdateAnim(void)
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
