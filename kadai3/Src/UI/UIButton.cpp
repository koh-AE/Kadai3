#include "UIButton.h"

#include <DxLib.h>
#include "../Collision/Collision.h"

UIButton::UIButton(int posX, int posY, int sizeW, int sizeH)
{
	posX_ = posX;
	posY_ = posY;

	sizeW_ = sizeW;
	sizeH_ = sizeH;

	buttonState_ = BUTTON_STATE::DISABLED;
}

UIButton::~UIButton()
{
}

void UIButton::Init(void)
{
	handle_[(int)BUTTON_STATE::DEFAULT] = LoadGraph("Data/Image/Button/s_001.png");
	handle_[(int)BUTTON_STATE::HOVER] = LoadGraph("Data/Image/Button/s_001_hover.png");
	handle_[(int)BUTTON_STATE::DISABLED] = LoadGraph("Data/Image/Button/s_001_click.png");
}

void UIButton::Update(void)
{
	// マウスの座標を取得
	int mousePosX = 0;
	int mousePosY = 0;

	GetMousePoint(&mousePosX, &mousePosY);

	// デフォルト状態
	buttonState_ = BUTTON_STATE::DEFAULT;

	// ボタンの上にマウスポインタがあるか？
	if (CollCheckPointRect(posX_, posY_, sizeW_, sizeH_, mousePosX, mousePosY))
	{
		// ボタンの上にマウスポインタがある
		buttonState_ = BUTTON_STATE::HOVER;

		// クリックされているのか？
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			// クリックされている
			buttonState_ = BUTTON_STATE::DISABLED;
		}
	}
}

void UIButton::Draw(void)
{
	// 描画
	DrawRotaGraph(
		posX_, posY_,				// 座標
		1.0,						// 拡大値
		0.0,						// 回転値
		handle_[(int)buttonState_],	// 画像ハンドル
		true						// 透過フラグ
	);
}

void UIButton::Delete(void)
{
	// 削除
	for (int i = 0; i < (int)BUTTON_STATE::BUTTON_STATE_MAX; i++)
	{
		DeleteGraph(handle_[i]);
	}
}

BUTTON_STATE UIButton::GetButtonState(void)
{
	return buttonState_;
}
