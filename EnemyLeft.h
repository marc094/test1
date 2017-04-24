#pragma once
#include "Enemy.h"
#include "Path.h"

class EnemyLeft :
	public Enemy
{

private:
	Path movement;

	Animation e1_forward;
	Animation e1_backward;
	Animation e1_left;
	Animation e1_right;
	Animation e1_up_right;
	Animation e1_up_left;
	Animation e1_down_right;
	Animation e1_down_left;

	Animation* GetAnimationForDirection(int dir);
	int angle;
	int collision = false;

public:
	EnemyLeft(int x, int y);
	virtual ~EnemyLeft();
	virtual void Move();
	virtual void OnCollision(Collider* collider);
};

