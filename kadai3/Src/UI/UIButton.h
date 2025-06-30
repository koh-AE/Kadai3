#pragma once


// ボタンの状態
enum class BUTTON_STATE
{
	DEFAULT,	// 通常
	HOVER,		// クリック可能
	DISABLED,	// クリック不可

	BUTTON_STATE_MAX,	// 状態の最大数
};

class UIButton
{
public:
	// コンストラクタ
	// 生成時に座標・サイズを設定可能
	UIButton(int posX, int posY, int sizeW, int sizeH);

	// デストラクタ
	~UIButton();

	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Delete(void);	// 削除

	// ボタンの状態を返す
	BUTTON_STATE GetButtonState(void);

private:
	BUTTON_STATE buttonState_;	// ボタンの状態

	// ボタンの画像ハンドル
	int handle_[(int)BUTTON_STATE::BUTTON_STATE_MAX];

	int posX_;	// X座標
	int posY_;	// Y座標

	int sizeW_;	// 横幅
	int sizeH_;	// 縦幅
};
