#pragma once
#include <DxLib.h>

class Camera {
public:
	//定数
		// シングルトン（生成・取得・削除）
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Camera(); } };
	static Camera* GetInstance(void) { return instance_; };
	static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

private:
	Camera();
	~Camera();
	//静的インスタンス
	static Camera* instance_;

public:
	//カメラの初期位置
	static constexpr VECTOR INIT_POS = { 0.0f, 1000.0f, -1000.0f };

	//カメラの初期角度
	static constexpr VECTOR INIT_ANGLE = { DX_PI_F / 180.0f * 30.0f, 0.0f, 0.0f };

	//カメラクリップ:NEAR
	static constexpr float CAMERA_NEAR = 3.0f;

	//カメラクリップ:FAR
	static constexpr float CAMERA_FAR = 5000.0f;

	//カメラのスピード（移動）
	static constexpr float CAMERA_SPEED = 10.0f;

	//カメラのスピード（角度）
	static constexpr float ANGLE_SPEED = 1.0f;

	static constexpr float MOVE_SPEED = 5.0f;

	void Init(void); // 初期化
	void Update(void); // 更新
	void SetBeforeDraw(void); // 描画
	void DebugDraw(void); // デバッグ描画
	void Release(void); // 解放

	//追従する座標
	void SetFollowPos(VECTOR pos);

private:
	//カメラ座標
	VECTOR pos_;

	//カメラの角度(rad)
	VECTOR angle_;

	//
	VECTOR followpos_;
};