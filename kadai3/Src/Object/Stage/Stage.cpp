#include "Stage.h"
#include "../../Utility/AsoUtility.h"
#include <fstream>

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
}

void Stage::Load(void)
{
	//各種ブロックのオリジナルをロード
	blockOriginModel_[static_cast<int>(Block::Type::GRASS)]
		= MV1LoadModel("Data/Model/Blocks/Block_Grass.mv1");
	blockOriginModel_[static_cast<int>(Block::Type::METAL)]
		= MV1LoadModel("Data/Model/Blocks/Block_Metal.mv1");
	blockOriginModel_[static_cast<int>(Block::Type::ICE)]
		= MV1LoadModel("Data/Model/Blocks/Block_Ice.mv1");

	//マップ読み込み
	LoadMapCsvData();
}

void Stage::LoadEnd(void)
{
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	//ブロックの描画
	for (int z = 0; z < BLOCK_NUM_Z; z++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			blocks_[z][x]->Draw();
		}
	}
}

void Stage::Release(void)
{
	//ブロックの削除
	for (int z = 0; z < BLOCK_NUM_Z; z++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			blocks_[z][x]->Release();
			delete blocks_[z][x];
		}
	}
	//オリジナルモデルの削除
	for (int i = 0; i < BLOCK_MODEL_NUM; i++)
	{
		MV1DeleteModel(blockOriginModel_[i]);
	}
}

bool Stage::IsCollLine(VECTOR topPos, VECTOR downPos, tagMV1_COLL_RESULT_POLY* result)
{
	for (int z = 0; z < BLOCK_NUM_Z; z++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			//配列からBlockを1づつ取り出す
			Block* block = blocks_[z][x];

			//線分とモデルの当たり判定
			MV1_COLL_RESULT_POLY coll =
				MV1CollCheck_Line(block->GetModelId(), -1, topPos, downPos);

			//当たった
			if (coll.HitFlag)
			{
				//結果を返す
				*result = coll;
				return true;
			}
		}
	}
	return false;
}

void Stage::LoadMapCsvData(void)
{
	//ファイルの読み込み
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");
	//ファイルが読み込み成功しているか
	if (!ifs)
	{
		//エラーが発生
		return;
	}

	//ファイルを1行ずつ読み込む
	std::string line;	//	1行の文字情報
	std::vector<std::string>strSplit;	//1行を1文字の動的配列に分裂

	int mapNo = 0;	//マップの種類
	int z = 0;		//

	while (getline(ifs, line))
	{
		//1行をカンマ区切りで分割
		strSplit = AsoUtility::Split(line, ',');

		for (int x = 0; x < strSplit.size(); x++)
		{
			//文字列から整数に変換
			//stringからintに変換
			mapNo = stoi(strSplit[x]);

			//マップタイプをキャスト
			Block::Type type = static_cast<Block::Type>(mapNo);

			//オリジナルのモデルを取る
			int baseModel = blockOriginModel_[mapNo];

			//ブロックを生成
			Block* block = new Block();
			block->Create(type, baseModel, x, z);

			//2次元配列にブロックを格納
			blocks_[z][x] = block;
		}
		z++;
	}
}

