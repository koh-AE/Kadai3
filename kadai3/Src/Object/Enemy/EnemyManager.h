#pragma once
#include "EnemyManager.h"
#include <vector>

//�O���錾
class EnemyBase;
class Player;

class EnemyManager
{
public:
	//�萔
	//�G�̍ő吔
	static constexpr int ENEMY_MAX_NUM = 10;

	//�G�̏o���Ԋu
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
	//�G�l�~�[���܂Ƃ߂铮�I�z��
	std::vector<EnemyBase*>enemys_;
	//�v���C���[���A�h���X
	Player* player_;
	//�o���Ԋu
	int spawnInterval_;
};
