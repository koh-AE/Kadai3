#pragma once
#include <DxLib.h>

//クラスの前方宣言
class Player;

class EnemyBase
{
public:
	//アニメーション種別
	enum class ANIM_TYPE
	{
		WALK = 6,	//歩行
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

	//生存フラグを設定する
	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }

	//生存フラグを取得する
	bool GetIsAlive(void) { return isAlive_; }

private:
	//プレイヤーの方向を向く
	void LookPlayer(void);

	//移動
	void Move(void);

	//アニメーション更新
	void UpdateAnim(void);

private:
	//プレイヤーの情報アドレス
	Player* player_;

	//モデルのハンドルID
	int  modelId_;
	//生存フラグ
	bool isAlive_;
	//座標
	VECTOR pos_;
	//角度
	VECTOR angle_;
	//大きさ
	VECTOR scale;
	//移動方向
	VECTOR moveDir_;
	//移動速度
	float moveSpeed_;

	//アニメーション
	ANIM_TYPE prevAnimType_;	//前回のアニメーション
	ANIM_TYPE nowAnimType_;		//現在のアニメーション

	//アニメーション
	int attachNo_;			//アニメーションの番号
	float nowAnimTime_;		//再生中の時間
	float totalAnimTime_;	//総再生時間
};
