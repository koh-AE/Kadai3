#include "Loading.h"
#include <DxLib.h>
#include "../Application/Application.h"

Loading* Loading::instance_ = nullptr;

static constexpr int MIN_LOAD_TIME = 60; // ���[�h��ʂ̕\�����ԁi�t���[�����j

Loading::Loading() {};
Loading::~Loading() {};

void Loading::Init(void)
{
	loadTimer_ = 0;
	isLoading_ = false;

	posX_ = Application::SCREEN_SIZE_X / 2;
	posY_ = Application::SCREEN_SIZE_Y / 2;
}

void Loading::Load(void)
{
	handle_ = LoadGraph("Data/Image/Axe.png");
 }

void Loading::Update(void)
{
	loadTimer_++;

	//�ǂݍ��ݒ��̂��̂������Ȃ�����
	if (GetASyncLoadNum() == 0 && loadTimer_ >= MIN_LOAD_TIME)
	{
		//���[�h�I��
		Init();
	}
	//�ǂݍ��ݒ�
	else
	{
		//���[�h��ʂŗV�т�����Ȃ炱���ɋL�q
	}
}

void Loading::Draw(void)
{
	DrawRotaGraph(
		posX_,	// X���W
		posY_,	// Y���W
		1.0,	//�g��l
		0.0,	//��]�p�x
		handle_,//�摜�n���h��
		true);	//�����F���g�p���邩
}

void Loading::Release(void)
{
	DeleteGraph(handle_);
}

void Loading::StartAsybcLoad(void)
{
	isLoading_ = true;
	SetUseASyncLoadFlag(true); // �񓯊����[�h��L���ɂ���
}

void Loading::EndAsyncLoad(void)
{
	SetUseASyncLoadFlag(false); // �񓯊����[�h�𖳌��ɂ���
}

bool Loading::IsLoading(void)
{
	return isLoading_;
}
