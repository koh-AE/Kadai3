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
	//モデルを動かす順番　	大きさ→角度→座標
	//モデルのサイズ
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	//モデルの角度
	angle_ = AsoUtility::VECTOR_ZERO;
	MV1SetRotationXYZ(modelId_, angle_);

	//モデル座標
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	//自己発光
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);

	//ジャンプ力の初期化
	JumpPow_ = 0.0f;

	//アニメーション
	prevAnimType_ = ANIM_TYPE::IDLE;
	nowAnimType_ = ANIM_TYPE::IDLE;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;
}

void Player::Load(void)
{
	//モデルのロード
	modelId_ = MV1LoadModel("Data/Model/Player/Player.mv1");
}

void Player::LoadEnd(void)
{
	//初期化
	Init();

	//アニメーションの初期化
	//現在のアニメーションをアタッチする
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	//アニメーション総再生時間取得	attach=アニメーションをくっつける
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);

}

void Player::Update(void)
{
	//移動操作
	ProcessMove();

	//ジャンプ操作
	ProcessJump();

	//アニメーションの更新
	UpdateAnim();

	//カメラに座標を渡す
	Camera::GetInstance()->SetFollowPos(pos_);
}

void Player::Draw(void)
{
	//モデルの描画
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
	//衝突して位置を戻す
	pos_ = pos;
	JumpPow_ = 0.0f;
}

void Player::ProcessMove(void)
{
	//移動方向を決める
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	//上方向 IsNew==長押し選択
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W))
	{
		moveDir = AsoUtility::DIR_F;
	}
	//下方向
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S))
	{
		moveDir = AsoUtility::DIR_B;
	}
	//右方向
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D))
	{
		moveDir = AsoUtility::DIR_R;
	}
	//左方向
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A))
	{
		moveDir = AsoUtility::DIR_L;
	}

	//移動していたら Equals == 等しい　!==not
	//VSZeroと等しいか
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		//モデルの移動方向にY軸回転させる
		//方向角度（ラジアン(0°から180°)）に変換
		angle_.y = atan2(moveDir.x, moveDir.z);

		//モデルが反転しているので強制的に回転させる  Deg2RadF
		angle_.y += AsoUtility::Deg2RadF(180.0f);

		//モデルに回転を設定
		MV1SetRotationXYZ(modelId_, angle_);
		
		//移動量を計算する(方向＊　スピード)
		VECTOR movePos = VScale(moveDir, MOVE_SPEED);

		//移動処理（座標　＋　移動量）
		pos_ = VAdd(pos_, moveDir);

		//モデル座標を設定する
		MV1SetPosition(modelId_, pos_);

		//アニメーションを変更する
		nowAnimType_ = ANIM_TYPE::WALK;
	}
	else
	{
		//移動していない

		//アニメーションを変更する
		nowAnimType_ = ANIM_TYPE::IDLE;
	}
}

void Player::ProcessJump(void)
{
	//重力
	JumpPow_ -= GRAVITY;

	//プレイヤー座標にジャンプを加算する
	pos_.y += JumpPow_;

	//衝突判定前の落下制御
	if (pos_.y < -1000.0f)
	{
		//初期化
		Init();
	}

	//モデルの座標を設定する
	MV1SetPosition(modelId_, pos_);

}

void Player::UpdateAnim(void)
{
	//アニメーションが変更されたどうか
	if (prevAnimType_ != nowAnimType_)
	{
		//アニメーション種別を合わせる
		prevAnimType_ = nowAnimType_;
		
		//モデルから前回のアニメーションを外す
		MV1DetachAnim(modelId_, attachNo_);

		//アニメーションを変更する
		attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

		//アニメーションの総再生時間を取得
		totalAnimTime_ = MV1GetAnimTotalTime(modelId_, attachNo_);

		//アニメーション時間を初期化
		nowAnimTime_ = 0;
	}
	//アニメーションの時間を進める
	nowAnimTime_ += 1.0f;

	//アニメーションをループ
	if (nowAnimTime_ > totalAnimTime_)
	{
		nowAnimTime_ = 0.0f;
	}

	//アニメーションの設定
	MV1SetAttachAnimTime(modelId_, attachNo_, nowAnimTime_);
}
