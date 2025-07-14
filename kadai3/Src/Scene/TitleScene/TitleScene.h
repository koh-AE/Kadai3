#pragma once
#include "../SceneBase.h"

//override virtual セット　継承元を.cppにoverrideで継承

//ベースの継承
class TitleScene : public SceneBase
{
public:
	TitleScene(void); // コンストラクタ
	~TitleScene(void) override;// デストラクタ

	void Init(void) override; // 初期化
	void Load(void) override; // 読み込み
	void LoadEnd(void) override; // 読み込み終わり
	void Update(void) override; // 更新
	void Draw(void) override; // 描画
	void Release(void) override; // 解放処理

	void toNextScene(void); // 次のシーンへ

private:

	int handle_;
};