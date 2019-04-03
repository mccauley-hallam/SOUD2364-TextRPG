#include <iostream>
#include <time.h>

using namespace std;

#pragma once
class game
{
private:
	string enemy[10] = {"Nightborne","Dark Iron Dwarf","Pandaren", "Doomguard", "Mogu", "Satyr", "Sayaadi", "Tuskaar", "Dryad", "Nathrezim"};
	int gold;
public:
	game();
	~game();

	string generateEnemy()
	{
		srand(time(NULL));
		int num = (rand() % 10) + 1;
		string selection = enemy[num];
		return selection;
	}
	int generateGold()
	{
		srand(time(NULL));
		gold = (rand() % 200) + 1;
		return gold;
	}
};
