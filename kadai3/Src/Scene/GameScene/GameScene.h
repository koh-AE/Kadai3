#pragma once
#include "../SceneBase.h"
#include <DxLib.h>


//クラスの前方宣言
class Grid;
class Stage;
class Player;
class EnemyBase;

//ベースの継承
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene() override;

	void Init(void) override; // 初期化
	void Load(void) override; // 読み込み
	void LoadEnd(void) override; // 読み込み終わり
	void Update(void) override; // 更新
	void Draw(void) override; // 描画
	void Release(void) override; // 解放処理

private:
	//デバック描画
	void DebugDraw(void);

	//線のデバッグ表示
	VECTOR lineTopPos_;
	VECTOR lineDownPos_;

	//衝突判定
	void Collision(void);

	//ステージとプレイヤーの衝突判定
	void CollisionStage(void);
private:
	Grid* grid_; // グリッドクラス

	Stage* stage_;	//ステージクラス
	Player* player_;
	EnemyBase* enemy_;
};