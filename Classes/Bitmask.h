#pragma once

class Bitmask
{
public:
	const static int Ignore = 0;
	const static int Ground = 1 << 0;
	const static int Wall = 1 << 1;
	const static int Object = 1 << 2;
	const static int Monster = 1 << 3;
	const static int Player = 1 << 4;
	const static int Invincibility = 1 << 5;
	const static int SkillObj = 1 << 6;
	const static int WorldItem = 1 << 7;
	const static int All_InvEx = INT32_MAX ^ (1 << 5);
	const static int All = INT32_MAX;
};