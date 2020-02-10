#pragma once
#include "Character.h"
class PROJECTILE {

public:
	COORD projectileCoord;
	//int prevDirX, prevDirY;

	void move(int moveX,int moveY)
	{
		//if (entireMapChar[projectileCoord.Y][projectileCoord.X] == 0)
		//{
		//	entireMapChar[projectileCoord.Y][projectileCoord.X] = 0;
			projectileCoord.X += moveX;
			projectileCoord.Y += moveY;
		//	entireMapChar[projectileCoord.Y][projectileCoord.X] = 8;
		//}
	}
	void doDamage(Character* player,int damage)
	{
		player->m_CharHealth -= damage;
	}
	void SetPosition(const int& x, const int& y) {
		projectileCoord.X = x;
		projectileCoord.Y = y;
	}
};