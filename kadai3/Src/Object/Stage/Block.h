#pragma once
#include <DxLib.h>

class Block
{
public:
	//�u���b�N�̎��
	enum class Type
	{
		NONE = -1,	//�����Ȃ�
		GRASS,		//���u���b�N
		METAL, 		//�����u���b�N
		ICE,		//�X�u���b�N
		MAX			//�S��ʐ�
	};

	//�萔
	//���Ȕ���(RGBA)
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };
	//���f���̑傫��
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };
	//1�u���b�N������̃T�C�Y
	static constexpr float SIZE = 100.0f;
public:
	Block();
	~Block();

	//�u���b�N�𐶐�����
	void Create(Type type, int modelId, int mapX, int mapZ);
	void Update();	//�X�V
	void Draw();	//�`��
	void Release();	//���

	//���f���̃n���h��ID���擾����
	int GetModelId(void);

private:
	Type type_;		//�u���b�N�̎��
	int modelId_;	// ���f��ID
	VECTOR pos_;	// ���W
	VECTOR scale_;	// �X�P�[��
};
