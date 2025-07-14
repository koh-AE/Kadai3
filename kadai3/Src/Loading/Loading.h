#pragma once

class Loading
{
public:
	//シングルトン==1つだけ作る（生成・取得・削除）
	static void CreateInstance(void) {if (instance_ == nullptr) {instance_ = new Loading();}}
	static Loading* GetInstance(void){return instance_;}
	static void DeleteInstance(void){if (instance_ != nullptr){delete instance_;instance_ = nullptr;}}

private:
	// コンストラクタ
	Loading(void);
	// デストラクタ
	~Loading(void);
	//静的インスタンス
	static Loading* instance_;

public:
	void Init(void);	// 初期化
	void Load(void);	// 読み込み処理
	void Update(void);	//更新処理
	void Draw(void);	// 描画処理
	void Release(void);	// 解放

	void StartAsybcLoad(void);	//非同期ロードの開始
	void EndAsyncLoad(void);	//非同期ロードの終了

	//ロード中なのか返す
	bool IsLoading(void);

private:
	//画像ハンドル
	int handle_;

	//座標
	int posX_;
	int posY_;

	//ロード中フラグ
	bool isLoading_;

	//ロード画面を表示する時間
	int loadTimer_;
};

