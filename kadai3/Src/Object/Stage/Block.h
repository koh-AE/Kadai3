#pragma once
#include <DxLib.h>

class Block
{
public:
	//ブロックの種別
	enum class Type
	{
		NONE = -1,	//何もなし
		GRASS,		//草ブロック
		METAL, 		//金属ブロック
		ICE,		//氷ブロック
		MAX			//全種別数
	};

	//定数
	//自己発光(RGBA)
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };
	//モデルの大きさ
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };
	//1ブロック当たりのサイズ
	static constexpr float SIZE = 100.0f;
public:
	Block();
	~Block();

	//ブロックを生成する
	void Create(Type type, int modelId, int mapX, int mapZ);
	void Update();	//更新
	void Draw();	//描画
	void Release();	//解放

	//モデルのハンドルIDを取得する
	int GetModelId(void);

private:
	Type type_;		//ブロックの種別
	int modelId_;	// モデルID
	VECTOR pos_;	// 座標
	VECTOR scale_;	// スケール
};
