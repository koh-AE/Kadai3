#pragma once

// クラスの前方宣言
class FpsControl;

class Application
{
public:
	// スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 1024;	// スクリーン横幅
	static constexpr int SCREEN_SIZE_Y = 768;	// スクリーン縦幅

public:
	// シングルトン（生成・取得・削除）
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Application(); } }
	static Application* GetInstance(void) { return instance_; }
	static void DeleteInstance(void) { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

public:

	void Init(void);	// 初期化
	void Run(void);		// ゲームループの開始
	void Release(void);	// 解放

	// 初期化成功／失敗の判定
	bool IsInitFail(void) const { return isInitFail_; };

	// 解放成功／失敗の判定
	bool IsReleaseFail(void) const { return isReleaseFail_; };

private:
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	Application(void);

	// デストラクタも同様
	~Application(void);

	// コピー・ムーブ操作を禁止
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(Application&&) = delete;

	// 下記をコンパイルエラーさせるため 上記を追加
	// Application copy = *Application::GetInstance();
	// Application copied(*Application::GetInstance());
	// Application moved = std::move(*Application::GetInstance());
private:

	// 静的インスタンス
	static Application* instance_;

	// 初期化失敗
	bool isInitFail_;

	// 解放失敗
	bool isReleaseFail_;

	// FPS
	FpsControl* fps_;
};
