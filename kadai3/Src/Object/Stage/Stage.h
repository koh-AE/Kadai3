#pragma once
#include <DxLib.h>
#include "Block.h"

class Stage
{
public:
	//ブロックのモデル種類
	static constexpr int BLOCK_MODEL_NUM = static_cast<int>(Block::Type::MAX);
	//ブロックの個数（マップサイズ）
	static constexpr int BLOCK_NUM_X = 20;
	static constexpr int BLOCK_NUM_Z = 20;

	//ステージ全体のXサイズ
	static constexpr float STAGE_SIZE_X = Block::SIZE * static_cast<float>(BLOCK_NUM_X);
	static constexpr float STAGE_SIZE_Z = Block::SIZE * static_cast<float>(BLOCK_NUM_Z);
public:
	Stage();
	~Stage();

	void Init(void);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//線分のブロックの衝突判定
	bool IsCollLine(
		VECTOR topPos, VECTOR downPos, tagMV1_COLL_RESULT_POLY* result
	);
private:
	//マップデータの読み込み
	void LoadMapCsvData(void);

private:
	//ブロックのオリジナルハンドル
	int blockOriginModel_[BLOCK_MODEL_NUM];

	//ブロッククラス
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];
};
