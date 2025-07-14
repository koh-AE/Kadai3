#pragma once

//クラスの前方宣言
class SceneBase;

class SceneManager
{
public:
	//シーンの管理用
	enum class SCENE_ID
	{
		NONE,	// 何もない
		TITLE,	// タイトルシーン
		GAME	// ゲームシーン
	};

public:
	//シングルトン==1つだけ作る（生成・取得・削除）
	static void CreateInstance(void) {
		if (instance_ == nullptr)
		{
			instance_ = new SceneManager();
		}
	}
	static SceneManager* GetInstance(void)
	{
		return instance_;
	}

	static void DeleteInstance(void)
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

private:
	// コンストラクタ
	SceneManager(void);
	// デストラクタ
	~SceneManager(void);

	//静的インスタンス
	static SceneManager* instance_;

public:
	void Init(void);
	void Init3D(void);	//3D情報の初期化
	void Update(void);
	void Draw(void);
	void Release(void);

	//状態遷移
	void ChangeScene(SCENE_ID nextId);
	//シーンIDの取得
	SCENE_ID GetSceneId(void) { return sceneId_; }

	//ゲーム終了
	void GameEnd(void) { isGameEnd_ = true; }

	//ゲーム終了フラグの取得
	bool IsGameEnd(void) const { return isGameEnd_; }

private:
	//各種シーン
	SceneBase* scene_;

	//シーンID
	SCENE_ID sceneId_;

	//ゲーム終了
	bool isGameEnd_;
};
