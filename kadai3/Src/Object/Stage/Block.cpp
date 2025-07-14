#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}
void Block::Create(Type type, int modelId, int mapX, int mapZ)
{
	//ブロックの種類設定
	type_ = type;
	//モデルの複製
	modelId_ = MV1DuplicateModel(modelId);
	//色の自己発光
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);
	//大きさ設定
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);
	//1ブロックの半分の大きさ
	const float HALF_BLOCK_SIZE = SIZE * 0.5f;
	//引数で指定されたマップ座標から座標を計算
	//3Dモデルの中心座標はブロックの中心
	float x = static_cast<float>(mapX);	
	float z = static_cast<float>(mapZ);

	//座標の設定
	pos_ = VGet(
		(SIZE * x) + HALF_BLOCK_SIZE,
		-HALF_BLOCK_SIZE,
		(SIZE * z) + HALF_BLOCK_SIZE
	);
	MV1SetPosition(modelId_, pos_);

	//衝突判定（モデル全て）
	MV1SetupCollInfo(modelId_, -1);

}
void Block::Update()
{ 
}

void Block::Draw()
{
	//モデルの表示
	MV1DrawModel(modelId_);
}

void Block::Release()
{
	//モデルの削除
	MV1DeleteModel(modelId_);
}

int Block::GetModelId(void)
{
	return modelId_;
}
