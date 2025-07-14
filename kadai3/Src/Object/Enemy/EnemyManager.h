#pragma once
#include "EnemyManager.h"
#include <vector>

//前方宣言
class EnemyBase;
class Player;

class EnemyManager
{
public:
	//定数
	//敵の最大数
	static constexpr int ENEMY_MAX_NUM = 10;

	//敵の出現間隔
	static constexpr int SPAWN_INTERVAL = 120;
public:
	EnemyManager(void);
	~EnemyManager(void);

	void Init(Player* player);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	//エネミーをまとめる動的配列
	std::vector<EnemyBase*>enemys_;
	//プレイヤー情報アドレス
	Player* player_;
	//出現間隔
	int spawnInterval_;
};
