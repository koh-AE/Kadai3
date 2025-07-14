#pragma once
#include <DxLib.h>
#include "Block.h"

class Stage
{
public:
	//�u���b�N�̃��f�����
	static constexpr int BLOCK_MODEL_NUM = static_cast<int>(Block::Type::MAX);
	//�u���b�N�̌��i�}�b�v�T�C�Y�j
	static constexpr int BLOCK_NUM_X = 20;
	static constexpr int BLOCK_NUM_Z = 20;

	//�X�e�[�W�S�̂�X�T�C�Y
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

	//�����̃u���b�N�̏Փ˔���
	bool IsCollLine(
		VECTOR topPos, VECTOR downPos, tagMV1_COLL_RESULT_POLY* result
	);
private:
	//�}�b�v�f�[�^�̓ǂݍ���
	void LoadMapCsvData(void);

private:
	//�u���b�N�̃I���W�i���n���h��
	int blockOriginModel_[BLOCK_MODEL_NUM];

	//�u���b�N�N���X
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];
};
