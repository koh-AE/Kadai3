#pragma once
#include <DxLib.h>

class Player
{
public:
	//アニメーション種別
	enum class ANIM_TYPE
	{
		DEAD = 0,	//死亡
		IDLE = 3,	//待機
		WALK = 14,	//歩行
	};
public:
	//モデルの大きさ
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };
	//初期位置
	static constexpr VECTOR INIT_POS = { 300.0f, 500.0f, 300.0f };
	//自己発光
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f };
	//プレイヤーの移動スピード
	static constexpr float MOVE_SPEED = 10.0f;
	//重力
	static constexpr float GRAVITY = 0.8f;
	//地面衝突判定用の線分の長さ
	static constexpr float COLL_LINE_LEN = 10.0f;
public:
	Player();
	~Player();

	void Init(void);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	//座標を取得
	VECTOR GetPos(void);
	//衝突判定
	void CollisionStage(VECTOR pos);
private:
	//移動制限
	void ProcessMove(void);
	//ジャンプ制御
	void ProcessJump(void);
	//アニメーション更新
	void UpdateAnim(void);
private:
	int modelId_;	//モデルハンドル
	VECTOR pos_;	//座標
	VECTOR angle_;	//向き
	VECTOR scale_;	//サイズ
	float JumpPow_;	//ジャンプ力

	//アニメーション
	ANIM_TYPE prevAnimType_;	//前回のアニメーション
	ANIM_TYPE nowAnimType_;		//現在のアニメーション

	//アニメーション
	int attachNo_;			//アニメーションの番号
	float nowAnimTime_;		//再生中の時間
	float totalAnimTime_;	//総再生時間
};
