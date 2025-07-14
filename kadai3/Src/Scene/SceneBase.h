#pragma once

//=0は何もしない
//virtual == 純粋仮想関数
class SceneBase
{
public:
	SceneBase();	//コンストラ
	virtual ~SceneBase() = 0;	//デストラ

	// 初期化
	virtual void Init(void) = 0;
	//読み込み
	virtual void Load(void) = 0;	//読み込みは最初だけ(Initで再度読み込みしない)
	//読み込み終わり
	virtual void LoadEnd(void) = 0;
	// 更新
	virtual void Update(void) = 0;
	//描画
	virtual void Draw(void) = 0;
	//解放処理
	virtual void Release(void) = 0;
};

