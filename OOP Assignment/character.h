#include <iostream>

using namespace std;

#pragma once
class Character
{
private:
	string str_weapon;
	int num_health, num_agilty, num_endurance, num_strength, damage_multiplier, health_multiplier;
public:
	// Weapon Set/Get
	void setWeapon(string aWeapon) { str_weapon = aWeapon; }
	string getWeapon() { return str_weapon; }

	// Health Set/Get
	void setHealth(int aHealth) { num_health = aHealth;  }
	int getHealth() { return num_health; }

	// Agiliy Set/Get
	void setAgility(int aAgility) { num_agilty = aAgility; }
	int getAgility() { return num_agilty; }

	// Endurance Set/Get
	void setEndurance(int aEndurance) { num_endurance = aEndurance; }
	int getEndurance() { return num_endurance; }

	// Strength Set/Get
	void setStrength(int aStrength) { num_strength = aStrength; }
	int getStrength() { return num_strength; }
};

class Player : public Character
{
private:
	string str_name;
public:
	// Name Set/Get
	void setName(string aName) { str_name = aName; }
	string getName() { return str_name; }
};