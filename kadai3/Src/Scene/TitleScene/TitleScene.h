#pragma once
#include "../SceneBase.h"

//override virtual �Z�b�g�@�p������.cpp��override�Ōp��

//�x�[�X�̌p��
class TitleScene : public SceneBase
{
public:
	TitleScene(void); // �R���X�g���N�^
	~TitleScene(void) override;// �f�X�g���N�^

	void Init(void) override; // ������
	void Load(void) override; // �ǂݍ���
	void LoadEnd(void) override; // �ǂݍ��ݏI���
	void Update(void) override; // �X�V
	void Draw(void) override; // �`��
	void Release(void) override; // �������

	void toNextScene(void); // ���̃V�[����

private:

	int handle_;
};