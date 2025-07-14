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
	//プレイヤーのポインタを取得
	player_ = player;
	//移動速度の初期化
	moveSpeed_ = 5.0f;

	//アニメーション
	prevAnimType_ = ANIM_TYPE::WALK;
	nowAnimType_ = ANIM_TYPE::WALK;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;

	//プレイヤーの方向を向く
	LookPlayer();
}

void EnemyBase::Load(void)
{
	//モデルのロード
	modelId_ = MV1LoadModel("Data/Model/Enemy/Demon.mv1");
}

void EnemyBase::LoadEnd(void)
{
	//アニメーションの初期化
	//現在のアニメーションをアタッチする
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	//アニメーション総再生時間取得	attach=アニメーションをくっつける
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);

}

void EnemyBase::Update(void)
{
	//プレイヤーの方向を向く
	LookPlayer();

	//移動
	Move();

	//アニメーションの更新
	UpdateAnim();
}

void EnemyBase::Draw(void)
{
	//描画
	MV1DrawModel(modelId_);
}

void EnemyBase::Release(void)
{
	//モデルの削除
	MV1DeleteModel(modelId_);
}

void EnemyBase::LookPlayer(void)
{
	//プレイヤーの向きを計算 VSub== 引き算
	VECTOR diff = VSub(player_->GetPos(), pos_);
	diff.y = 0.0f;
	//ベクトルを正規化（向きのみの情報に変換）
	moveDir_ = VNorm(diff);

	//方向を角度に変換(xとy軸は回転させない)
	angle_.x = 0.0f;
	angle_.z = 0.0f;
	angle_.y = atan2f(moveDir_.x, moveDir_.z);

	//モデルが逆方向を向いているのでY軸を反転
	angle_.y += AsoUtility::Deg2RadF(180.0f);

	//モデルの回転を反映させる
	MV1SetRotationXYZ(modelId_, angle_);


}

void EnemyBase::Move(void)
{
	//移動処理 VScale==掛け算
	pos_ = VAdd(pos_, VScale(moveDir_, moveSpeed_));
	//敵の移動制限
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


	//モデルの座標を反映させる
	MV1SetPosition(modelId_, pos_);

}

void EnemyBase::UpdateAnim(void)
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