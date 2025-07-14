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
	//�e��u���b�N�̃I���W�i�������[�h
	blockOriginModel_[static_cast<int>(Block::Type::GRASS)]
		= MV1LoadModel("Data/Model/Blocks/Block_Grass.mv1");
	blockOriginModel_[static_cast<int>(Block::Type::METAL)]
		= MV1LoadModel("Data/Model/Blocks/Block_Metal.mv1");
	blockOriginModel_[static_cast<int>(Block::Type::ICE)]
		= MV1LoadModel("Data/Model/Blocks/Block_Ice.mv1");

	//�}�b�v�ǂݍ���
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
	//�u���b�N�̕`��
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
	//�u���b�N�̍폜
	for (int z = 0; z < BLOCK_NUM_Z; z++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			blocks_[z][x]->Release();
			delete blocks_[z][x];
		}
	}
	//�I���W�i�����f���̍폜
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
			//�z�񂩂�Block��1�Â��o��
			Block* block = blocks_[z][x];

			//�����ƃ��f���̓����蔻��
			MV1_COLL_RESULT_POLY coll =
				MV1CollCheck_Line(block->GetModelId(), -1, topPos, downPos);

			//��������
			if (coll.HitFlag)
			{
				//���ʂ�Ԃ�
				*result = coll;
				return true;
			}
		}
	}
	return false;
}

void Stage::LoadMapCsvData(void)
{
	//�t�@�C���̓ǂݍ���
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");
	//�t�@�C�����ǂݍ��ݐ������Ă��邩
	if (!ifs)
	{
		//�G���[������
		return;
	}

	//�t�@�C����1�s���ǂݍ���
	std::string line;	//	1�s�̕������
	std::vector<std::string>strSplit;	//1�s��1�����̓��I�z��ɕ���

	int mapNo = 0;	//�}�b�v�̎��
	int z = 0;		//

	while (getline(ifs, line))
	{
		//1�s���J���}��؂�ŕ���
		strSplit = AsoUtility::Split(line, ',');

		for (int x = 0; x < strSplit.size(); x++)
		{
			//�����񂩂琮���ɕϊ�
			//string����int�ɕϊ�
			mapNo = stoi(strSplit[x]);

			//�}�b�v�^�C�v���L���X�g
			Block::Type type = static_cast<Block::Type>(mapNo);

			//�I���W�i���̃��f�������
			int baseModel = blockOriginModel_[mapNo];

			//�u���b�N�𐶐�
			Block* block = new Block();
			block->Create(type, baseModel, x, z);

			//2�����z��Ƀu���b�N���i�[
			blocks_[z][x] = block;
		}
		z++;
	}
}

