#pragma once

class Loading
{
public:
	//�V���O���g��==1�������i�����E�擾�E�폜�j
	static void CreateInstance(void) {if (instance_ == nullptr) {instance_ = new Loading();}}
	static Loading* GetInstance(void){return instance_;}
	static void DeleteInstance(void){if (instance_ != nullptr){delete instance_;instance_ = nullptr;}}

private:
	// �R���X�g���N�^
	Loading(void);
	// �f�X�g���N�^
	~Loading(void);
	//�ÓI�C���X�^���X
	static Loading* instance_;

public:
	void Init(void);	// ������
	void Load(void);	// �ǂݍ��ݏ���
	void Update(void);	//�X�V����
	void Draw(void);	// �`�揈��
	void Release(void);	// ���

	void StartAsybcLoad(void);	//�񓯊����[�h�̊J�n
	void EndAsyncLoad(void);	//�񓯊����[�h�̏I��

	//���[�h���Ȃ̂��Ԃ�
	bool IsLoading(void);

private:
	//�摜�n���h��
	int handle_;

	//���W
	int posX_;
	int posY_;

	//���[�h���t���O
	bool isLoading_;

	//���[�h��ʂ�\�����鎞��
	int loadTimer_;
};

