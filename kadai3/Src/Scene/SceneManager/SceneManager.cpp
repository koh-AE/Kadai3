#include "SceneManager.h"
#include <DxLib.h>
#include "../TitleScene/TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../../Loading/Loading.h"
SceneManager* SceneManager::instance_ = nullptr;

SceneManager::SceneManager(void)
{
}

SceneManager::~SceneManager(void)
{
}

void SceneManager::Init(void)
{
	//���[�h��ʂ̐���
	Loading::CreateInstance();
	Loading::GetInstance()->Load();
	Loading::GetInstance()->Init();

	//3D���̏�����
	Init3D();

	//�ŏ��̓^�C�g���V�[��
	ChangeScene(SCENE_ID::TITLE);
}


void SceneManager::Init3D(void)
{
	//�w�i�F�ݒ�
	SetBackgroundColor(0, 0, 0);

	//Z�o�b�t�@��L��
	SetUseZBuffer3D(true);

	//Z�o�b�t�@�ւ̏�������
	SetWriteZBuffer3D(true);

	//�o�b�N�J�����O��L����
	SetUseBackCulling(true);

	//���C�g�̐ݒ�
	SetUseLighting(true);

	//���ʂ���΂߉��Ɍ����������C�g
	ChangeLightTypeDir({ 0.0f,-1.0f, 1.0f });
}

void SceneManager::Update(void)
{

	//���[�h��
	//�������[�h����������
	if (Loading::GetInstance()->IsLoading())
	{
		//���[�h�X�V
		Loading::GetInstance()->Update();

		//���[�h���I�����Ă�����
		if (Loading::GetInstance()->IsLoading() == false)
		{
			//���[�h��̏�����
			scene_->LoadEnd();
		}
	}
	//�ʏ�̍X�V����
	else
	{
		//�V�[���̍X�V
		scene_->Update();
	}
}

void SceneManager::Draw(void)
{
	//���[�h���Ȃ烍�[�h��ʂ�`��
	if (Loading::GetInstance()->IsLoading())
	{
		//���[�h���
		Loading::GetInstance()->Draw();
	}
	//�ʏ���
	else
	{
		//���݂̃V�[����`��
		scene_->Draw();
	}
}

void SceneManager::Release(void)
{
	//���݂̃V�[��������E�폜
	scene_->Release();
	delete scene_;

	//���[�h��ʂ̉��
	Loading::GetInstance()->Release();
	Loading::DeleteInstance();
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{
	//�V�[����ύX����
	sceneId_ = nextId;

	//���݂̃V�[�����J��
	if (scene_ != nullptr)
	{
		scene_->Release();	//���݂̃V�[�����J��
		delete scene_;		//�V�[���̍폜
	}

	//�e�V�[���ɐ؂�ւ���
	switch (sceneId_)
	{
	case SceneManager::SCENE_ID::NONE:
		break;
	case SceneManager::SCENE_ID::TITLE:
		scene_ = new TitleScene();	
		break;
	case SceneManager::SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	default:
		break;
	}

	//������
	Loading::GetInstance()->StartAsybcLoad();	// �񓯊����[�h�J�n
	scene_->Load();								// �V�[���̃��[�h
	Loading::GetInstance()->EndAsyncLoad();		// �񓯊����[�h�I��
}
