#pragma once

//=0�͉������Ȃ�
//virtual == �������z�֐�
class SceneBase
{
public:
	SceneBase();	//�R���X�g��
	virtual ~SceneBase() = 0;	//�f�X�g��

	// ������
	virtual void Init(void) = 0;
	//�ǂݍ���
	virtual void Load(void) = 0;	//�ǂݍ��݂͍ŏ�����(Init�ōēx�ǂݍ��݂��Ȃ�)
	//�ǂݍ��ݏI���
	virtual void LoadEnd(void) = 0;
	// �X�V
	virtual void Update(void) = 0;
	//�`��
	virtual void Draw(void) = 0;
	//�������
	virtual void Release(void) = 0;
};

