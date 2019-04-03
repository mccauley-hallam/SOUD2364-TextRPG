#include "game.h"
#include "character.h"
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
using jsonf = nlohmann::json;

game::game() {}
game::~game() {}

void logo()
{
	cout << "===================================================================\n";
	cout << " _______  _______  __   __  _______    ______    _______  _______  \n";
	cout << "|       ||       ||  |_|  ||       |  |    _ |  |       ||       | \n";
	cout << "|_     _||    ___||       ||_     _|  |   | ||  |    _  ||    ___| \n";
	cout << "  |   |  |   |___ |       |  |   |    |   |_||_ |   |_| ||   | __  \n";
	cout << "  |   |  |    ___| |     |   |   |    |    __  ||    ___||   ||  | \n";
	cout << "  |   |  |   |___ |   _   |  |   |    |   |  | ||   |    |   |_| | \n";
	cout << "  |___|  |_______||__| |__|  |___|    |___|  |_||___|    |_______| \n\n";
	cout << "===================================================================\n\n";
}

void NewGame();
void StatAllocation();
void Menu();
void Attack(); 
void reset();
void save();
void Store(); 

int enemy_damage_multiplier = 1, player_damage_multiplier = 1, player_health_multiplier = 1, enemy_health_multiplier = 1, playerHealth = 100, enemyHealth = 100;
string playerName;

string strName, opponent;
int gold;

int main()
{
	logo();

	cout << "1. New Game\n";
	cout << "2. Continue\n";
	cout << "3. Exit\n\n";

	int sel;

	cout << "Selection: "; cin >> sel;

	if (sel == 1)
	{
		// New Game
		NewGame();
	}
	else if (sel == 2)
	{
		// Continue
		ifstream exists("data.json");
		if (!exists)
		{
			system("cls");

			logo();

			// No player data found
			cout << "No savegame found, please create a new game.\n\n";
			system("pause");
			system("cls");
			main();
		}
		else
		{
			// Save data found
			Menu();
		}
	}
	else if (sel == 3)
	{
		// Exit
		
	}
	else
	{
		// Invalid Input
		cout << "\n\nInvalid Input.\n";
		system("pause");
		main();
	}
}

// Create a new save game
void NewGame()
{
	// Player Setup
	system("cls");

	logo();

	cout << "Name: "; cin >> strName;

	system("cls");

	StatAllocation();
}

// Allocation of stats (cont from NewGame)
void StatAllocation()
{
	int strength = 5, agility = 5, health = 100, endurance = 5; // PLayer Stats
	int alloStr, alloAgi, alloEnd;
	int allocation = 20; // Stat Allocation Counter

	Player *pl = new Player();

	logo();

	cout << "Note: Each stat has 5 points by default.\n";
	cout << "\nYou have " + to_string(allocation) + " remaining points to allocate.\n";

	// Logic checks for stat allocation
	if (allocation != 0)
	{
		cout << "Strength: "; cin >> alloStr;

		if (alloStr > allocation)
		{
			// Error
			cout << "Invalid Input. Does your value exceed the remaining amount?\n";
			system("pause");
			StatAllocation();
		}
		else
		{
			cout << "\nYou have " + to_string(allocation -= alloStr) + " remaining points to allocate.\n";
			cout << "Agility: "; cin >> alloAgi;

			if (alloAgi > allocation)
			{
				// Error
				cout << "Invalid Input. Does your value exceed the remaining amount?\n";
				system("pause");
				StatAllocation();
			}
			else
			{
				cout << "\nYou have " + to_string(allocation -= alloAgi) + " remaining points to allocate.\n";
				cout << "Endurance: "; cin >> alloEnd;

				if (alloEnd > allocation)
				{
					// Error
					cout << "Invalid Input. Does your value exceed the remaining amount?\n";
					system("pause");
					StatAllocation();
				}
				else
				{
					system("cls");

					logo();

					cout << "All statistics updated.\n\n";
				}
			}
		}
		strength += alloStr;
		agility += alloAgi;
		endurance += alloEnd;

		// Output values for confirmation
		cout << "Strength: " + to_string(strength);
		cout << "\nAgility: " + to_string(agility);
		cout << "\nEndurance: " + to_string(endurance) << "\n\n";

		string statConfirm;

		cout << "Are you happy with these stats?\n\n";
		cout << "Yes/No: "; cin >> statConfirm;

		if (statConfirm == "yes")
		{
			// Confirm Stats
			system("cls");

			logo();

			// Push Values
			pl->setName(strName); pl->setStrength(strength); pl->setAgility(agility); pl->setHealth(health); pl->setEndurance(endurance);

			cout << "Stats Confirmed.\n\n";
			system("pause");
		}
		else if (statConfirm == "no")
		{
			// Re-do stats
			StatAllocation();
		}
		else { /* Error */ }

		// Push Values
		pl->setName(strName); pl->setStrength(strength); pl->setAgility(agility); pl->setHealth(health); pl->setEndurance(endurance);

		// JSON formatting of player data
		jsonf j;

		j["player"]["name"] = strName;
		j["player"]["health"] = health;
		j["player"]["strength"] = strength;
		j["player"]["agility"] = agility;
		j["player"]["endurance"] = endurance;
		j["player"]["damage_multiplier"] = 1;
		j["player"]["health_multiplier"] = 1;
		j["player"]["gold"] = 100;

		j["arena"]["damage_multiplier"] = 1;
		j["arena"]["health_multiplier"] = 1;

		// Output of JSON file
		std::ofstream file("data.json");
		file << j;
	}
	system("cls");
	main();
}

// Main menu after player loads save
void Menu()
{
	int sel;
	Player *pl = new Player();
	game *arena = new game();

	system("cls");

	logo();

	ifstream ifs("data.json");
	json j = json::parse(ifs);
	
	string playerName = j["player"]["name"];

	cout << "Welcome back, " << playerName << "!\n\n";

	cout << "1. Arena\n";
	cout << "2. My Stats\n";
	cout << "3. Store\n";
	cout << "4. Save Game\n";
	cout << "5. Return to menu\n\n";

	cout << "Selection: "; cin >> sel;

	if (sel == 1)
	{
		// Arena
		system("cls");

		game *arena = new game();
		opponent = arena->generateEnemy();
		gold = arena->generateGold();

		ifstream ifs("data.json");
		json j = json::parse(ifs);

		enemy_damage_multiplier = j["arena"]["damage_multiplier"];
		enemy_health_multiplier = j["arena"]["health_multiplier"];

		player_damage_multiplier = j["player"]["damage_multiplier"];
		player_health_multiplier = j["player"]["health_multiplier"];

		enemyHealth = 100 * enemy_health_multiplier;
		playerHealth = 100 * player_health_multiplier;

		Attack();
	}
	else if (sel == 2)
	{
		// My Stats
		system("cls");
		logo();

		cout << "Name: " << playerName << "\n";
		cout << "Health: " << j["player"]["health"] << "\n";
		cout << "Endurance: " << j["player"]["endurance"] << "\n";
		cout << "Agility: " << j["player"]["agility"] << "\n";
		cout << "Strength: " << j["player"]["strength"] << "\n";
		cout << "Gold: " << j["player"]["gold"] << "\n";
		cout << "Health Multiplier: " << j["player"]["health_multiplier"] << "\n";
		cout << "Damage Multiplier: " << j["player"]["damage_multiplier"] << "\n\n";

		system("pause");
		system("cls");
		Menu();
	}
	else if (sel == 3)
	{
		// Store
		system("cls");
		Store();
	}
	else if (sel == 4)
	{
		// Save game
		
		
		system("cls");
		logo();

		save();

		cout << "Your game has been saved.\n\n";

		system("pause");
		system("cls");
		Menu();
	}
	else if (sel == 5)
	{
		// Return to menu
		system("cls");
		main();
	}
	else
	{
		cout << "Invalid Input..\n";
		system("pause");
		Menu();
	}
	system("pause");
	Menu();
}

void Attack()
{
	int sel;

	system("cls");

	logo();

	// Read Save File
	ifstream ifs("data.json");
	json j = json::parse(ifs);

	// Store Player Name
	string player = j["player"]["name"];

	cout << player << " VS. " << opponent << "\n\n";
	
	cout << "Player Health: " << to_string(playerHealth) << "\n";
	cout << "Enemy Health: " << to_string(enemyHealth) << "\n\n";

	cout << "1. Attack\n";
	cout << "2. Guard\n";
	cout << "3. Run\n\n";

	cout << "Selection: "; cin >> sel;

	// If player and enemy are alive
	if (playerHealth > 0 && enemyHealth > 0)
	{
		if (sel == 1)
		{
			srand(time(NULL));
			// Attack

			// Player damage
			double get_player_strength = j["player"]["strength"] * 0.2; // Retrieve player strength from save and divide by 0.2 (20%)
			int player_strength = ceil(get_player_strength); // Round up to the nearest whole number
			double get_player_agility = j["player"]["agility"] * 0.2; // Retrieve player agility from save and divide by 0.2 (20%)
			int player_agility = ceil(get_player_agility);

			// Random number between 1 - 20 * multiplier + 20% of strength
			double get_player_damage = (rand() % 20) + 1 * player_damage_multiplier + player_strength;
			// Player damage
			int player_damage = ceil(get_player_damage);
			// Enemy damage between range of 1 - 20 * multiplier - 20% of players agility
			int enemy_damage = (rand() % 20) + 1 * enemy_damage_multiplier - player_agility;

			system("cls");
			logo();

			cout << player << " attacks " << opponent << " dealing " << to_string(player_damage) << " damage.\n";
			cout << opponent << " attacks " << playerName << " dealing " << to_string(enemy_damage) << " damage.\n\n";

			// Health minus damage dealt
			playerHealth -= enemy_damage;
			enemyHealth -= player_damage;

			system("pause");
			Attack();
		}
		else if (sel == 2)
		{
			// Guard

			// Enemy damage
			int enemy_damage = (rand() % 20) + 1 * enemy_damage_multiplier;

			// Reduce Damage
			int reduction = (rand() % enemy_damage) + 1;
			enemy_damage -= reduction;

			// Health minus damage dealt
			playerHealth -= enemy_damage;

			system("cls");
			logo();

			cout << player << " blocked " << reduction << " of the damage.\n\n";

			system("pause");
			Attack();
		}
		else if (sel == 3)
		{
			// Run
			system("cls");
			reset();
			Menu();
		}
		else
		{
			// Invalid Input 
			system("cls");
			logo();
			
			cout << "Invalid Input...\n\n";

			system("pause");
			Attack();
		}
	}
	// If player is alive and enemy has been defeated
	else if (playerHealth > 0 && enemyHealth <= 0)
	{
		system("cls");
		logo();

		cout << "You have defeated " << opponent << " and claimed " << to_string(gold) << " gold!\n\n";
		system("pause");
		save();
		reset();
		Menu();
	}
	// If player has been defeated but enemy is alive
	else if (playerHealth <= 0 && enemyHealth > 0)
	{
		system("cls");
		logo();

		cout << "You have been defeated, " << opponent << " was victorious.\n\n";
		system("pause");
		reset();
		Menu();
	}
	// If both the player and the enemy have died
	else if (playerHealth <= 0 && enemyHealth <= 0)
	{
		system("cls");
		logo();

		cout << "You are both dead, is this a victory?\n\n";

		system("pause");
		reset();
		Menu();
	}
}

void save()
{
	// Read Save File
	ifstream ifs("data.json");
	json j = json::parse(ifs);
	
	string pull_name = j["player"]["name"];
	int pull_health = j["player"]["health"];
	int pull_strength = j["player"]["strength"];
	int pull_agility = j["player"]["agility"];
	int pull_endurance = j["player"]["endurance"];
	int pull_damage_multiplier = j["player"]["damage_multiplier"];
	int pull_health_multiplier = j["player"]["health_multiplier"];
	int pull_gold = j["player"]["gold"];

	int pull_arena_damage_multiplier = j["arena"]["damage_multiplier"];
	int pull_arena_health_multiplier = j["arena"]["health_multiplier"];

	jsonf jf;

	jf["player"]["name"] = pull_name;
	jf["player"]["health"] = pull_health;
	jf["player"]["strength"] = pull_strength;
	jf["player"]["agility"] = pull_agility;
	jf["player"]["endurance"] = pull_endurance;
	jf["player"]["damage_multiplier"] = pull_damage_multiplier;
	jf["player"]["health_multiplier"] = pull_health_multiplier;
	jf["player"]["gold"] = pull_gold + gold;

	jf["arena"]["damage_multiplier"] = pull_arena_damage_multiplier;
	jf["arena"]["health_multiplier"] = pull_arena_health_multiplier;

	// Output of JSON file
	std::ofstream file("data.json");
	file << jf;
}

void reset()
{
	string opponent, player;

	playerHealth = 100 * player_health_multiplier;
	enemyHealth = 100 * enemy_health_multiplier;
	player = "";
	opponent = "";
}

void save_store_strength();
void save_store_agility();

void Store()
{
	// Read Save File
	ifstream ifs("data.json");
	json j = json::parse(ifs);
	
	// Pull Name & Gold
	string pull_name = j["player"]["name"];
	int pull_gold = j["player"]["gold"];

	// Pull current stats
	int pull_strength = j["player"]["strength"];
	int pull_agility = j["player"]["agility"];

	int sel;

	logo();

	cout << "Welcome to the store, " << pull_name << ". What can I can do for you today?\n\n";
	cout << "Each session of training costs 200 gold. You will receive 1 point per session.\n\n";
	cout << "Your Gold: " << to_string(pull_gold) << "\n\n";

	cout << "1. Train Strength\n";
	cout << "2. Train Agility\n";
	cout << "3. Return to menu\n\n";

	cout << "Selection: "; cin >> sel;

	if (sel == 1 && pull_gold >= 200)
	{
		// Train Strength
		save_store_strength();

		system("cls");
		logo();

		cout << "In exchange for 200 gold, you have trained your strength for an additional 1 point.\n\n";
		system("pause");
		system("cls");
		Store();
	}
	else if (sel == 2 && pull_gold >= 200)
	{
		// Train Agility
		save_store_agility();

		system("cls");
		logo();

		cout << "In exchange for 200 gold, you have trained your agility for an additional 1 point.\n\n";
		system("pause");
		system("cls");
		Store();
	}
	else if (sel == 3)
	{
		// Return to menu
		system("cls");
		Menu();
	}
	else
	{
		// Invalid Input
		system("cls");
		logo();
		cout << "Input invalid or not enough gold to train\n\n";
		system("pause");
		system("cls");
		Menu();
	}
}

void save_store_strength()
{
	// Read Save File
	ifstream ifs("data.json");
	json j = json::parse(ifs);

	string pull_name = j["player"]["name"];
	int pull_health = j["player"]["health"];
	int pull_strength = j["player"]["strength"] + 1;
	int pull_agility = j["player"]["agility"];
	int pull_endurance = j["player"]["endurance"];
	int pull_damage_multiplier = j["player"]["damage_multiplier"];
	int pull_health_multiplier = j["player"]["health_multiplier"];
	int pull_gold = j["player"]["gold"];

	int new_gold = pull_gold -= 200;

	int pull_arena_damage_multiplier = j["arena"]["damage_multiplier"];
	int pull_arena_health_multiplier = j["arena"]["health_multiplier"];

	jsonf jf;

	jf["player"]["name"] = pull_name;
	jf["player"]["health"] = pull_health;
	jf["player"]["strength"] = pull_strength;
	jf["player"]["agility"] = pull_agility;
	jf["player"]["endurance"] = pull_endurance;
	jf["player"]["damage_multiplier"] = pull_damage_multiplier;
	jf["player"]["health_multiplier"] = pull_health_multiplier;
	jf["player"]["gold"] = new_gold;

	jf["arena"]["damage_multiplier"] = pull_arena_damage_multiplier;
	jf["arena"]["health_multiplier"] = pull_arena_health_multiplier;

	// Output of JSON file
	std::ofstream file("data.json");
	file << jf;
}

void save_store_agility()
{
	// Read Save File
	ifstream ifs("data.json");
	json j = json::parse(ifs);

	string pull_name = j["player"]["name"];
	int pull_health = j["player"]["health"];
	int pull_strength = j["player"]["strength"];
	int pull_agility = j["player"]["agility"] + 1;
	int pull_endurance = j["player"]["endurance"];
	int pull_damage_multiplier = j["player"]["damage_multiplier"];
	int pull_health_multiplier = j["player"]["health_multiplier"];
	int pull_gold = j["player"]["gold"];

	int new_gold = pull_gold -= 200;

	int pull_arena_damage_multiplier = j["arena"]["damage_multiplier"];
	int pull_arena_health_multiplier = j["arena"]["health_multiplier"];

	jsonf jf;

	jf["player"]["name"] = pull_name;
	jf["player"]["health"] = pull_health;
	jf["player"]["strength"] = pull_strength;
	jf["player"]["agility"] = pull_agility;
	jf["player"]["endurance"] = pull_endurance;
	jf["player"]["damage_multiplier"] = pull_damage_multiplier;
	jf["player"]["health_multiplier"] = pull_health_multiplier;
	jf["player"]["gold"] = new_gold;

	jf["arena"]["damage_multiplier"] = pull_arena_damage_multiplier;
	jf["arena"]["health_multiplier"] = pull_arena_health_multiplier;

	// Output of JSON file
	std::ofstream file("data.json");
	file << jf;
}