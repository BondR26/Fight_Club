
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

class Warrior
{
protected:

	char* name;
	char* weapon_name;
	int health;
	int armor;
	int power;
	int weapon;

public:

	Warrior(): name(nullptr), weapon_name(nullptr), health(0), armor(0), weapon(0), power(0) {}

	Warrior(const char* name, const char* weapon_name) : name{ new char[strlen(name) + 1] }, weapon_name{ new char[strlen(weapon_name) + 1] }
	{
		strcpy(this->name, name);
		strcpy(this->weapon_name, weapon_name);
		health = armor = power = 100;
		weapon = 0;
	}

	Warrior(const Warrior& copy)
	{
		this->name = new char[strlen(copy.name) + 1];
		strcpy(this->name, copy.name);

		this->health = copy.health;
		this->armor = copy.armor;
		this->power = copy.power;
		this->weapon = copy.weapon;
		
		this->weapon_name = new char[strlen(copy.weapon_name) + 1];
		strcpy(this->weapon_name, copy.weapon_name);
	}

	~Warrior()
	{
		delete[] name;
		delete[] weapon_name;
	}

	bool operator==(const Warrior& other)
	{
		return this->armor == other.armor and this->power == other.power and
			strcmp(this->name, other.name) == 0 and strcmp(this->weapon_name, other.weapon_name) == 0
			and this->health == other.health and this->weapon == other.weapon;
	}

	Warrior& operator = (const Warrior& other)
	{
		if (*this == other)
		{
			return *this;
		}

		if (this->name != nullptr)
		{
			delete[] this->name;
		}

		this->name = new char[strlen(other.name) + 1];
		strcpy(this->name, other.name);

		if (this->weapon_name != nullptr)
		{
			delete[] this->weapon_name;
		}

		this->weapon_name = new char[strlen(other.weapon_name) + 1];
		strcpy(this->weapon_name, other.weapon_name);

		this->health = other.health;
		this->armor = other.armor;
		this->power = other.power;
		this->weapon = other.weapon;
		return *this;
	}

	friend int attack(Warrior& other, int weapon);

	friend int GetHealth(const Warrior& warrior);

	

	char* GetName()
	{
		return this->name;
	}

	char* GetWeaponName()
	{
		return this->weapon_name;
	}

	int& GetWeapon()
	{
		return this->weapon;
	}

	void decrese_of_power(int heritage)
	{
		this->power -=(heritage / 5);
	}


	friend std::ostream& operator << (std::ostream& out, const Warrior& other)
	{
		out << "Name -> " << other.name << std::endl;
		out << "Health -> " << other.health << std::endl;
		out << "Power -> " << other.power << std::endl;
		out << "Armor -> " << other.armor << std::endl;
		out << other.weapon_name << " damage -> " << other.weapon << std::endl;

		return out;
	}

};


class Knight : public Warrior
{
private:

	int sword_attack;

public:

	Knight(const char* name, const char* weapon_name, int heritage) : Warrior(name, weapon_name)
	{
		health += heritage;
		armor += heritage;
		power += heritage;
		sword_attack = power / 9;
		weapon = sword_attack;
	}
};

class Valkyrie : public Warrior
{
private:

	int spear_attack;

public:

	Valkyrie(const char* name, const char* weapon_name, int heritage) : Warrior(name, weapon_name)
	{
		health += 3 * heritage;
		armor += 0;
		power -= heritage;
		spear_attack = power / 10;
		weapon = spear_attack;
	}

	

};

class Viking : public Warrior
{
private:

	int axe_attack;

public:

	Viking(const char* name, const char* weapon_name, int heritage) : Warrior(name, weapon_name)
	{
		health += heritage;
		armor -= heritage;
		power += 2 * heritage;
		axe_attack = power / 8;
		weapon = axe_attack;
	}

	
};

class Kosack : public Warrior
{
private:

	int shablya_attack;

public:

	Kosack(const char* name, const char* weapon_name, int heritage) : Warrior(name, weapon_name)
	{
		health += 2 * heritage;
		armor -= 2 * heritage;
		power += 2 * heritage;
		shablya_attack = power / 10;
		weapon = shablya_attack;

	}
};

int attack(Warrior& other, int weapon)
{
	int force_of_attack = weapon * (other.power % 5);

	other.health -= force_of_attack;
	
	return force_of_attack;
}

int GetHealth(const Warrior& warrior)
{
	return warrior.health;
}


int main(int argc, char* argv[])
{


	/*int count = 1;
	while (true)
	{
		system("CLS");
		if (count % 2 == 0)
		{
			std::cout << "Initialization of warriors ..";
		}
		else if (count % 1 == 0)
		{
			std::cout << "Initialization of warriors ...";
		}

		Sleep(100);
		count++;

		if (count > 10)
		{
			break;
		}
	}*/

	srand(time(0));

	int heritage = 1 + rand() % 20;

	int pair = 1 + rand()%4;

	Knight knight("Good Sir Knight", "Sword" ,heritage);
	Valkyrie valkyrie("Tessa", "Spear",heritage);
	Viking viking("Hrothgar", "Axe", heritage);
	Kosack kosack("Taras Bulba", "Shablya", heritage);

	Warrior warrior_1;
	Warrior warrior_2;

	switch (pair)
	{
	case 1:
	{
		warrior_1 = knight;
		warrior_2 = viking;

		break;
	}
	case 2:
	{

		warrior_1 = valkyrie;
		warrior_2 = viking;
		break;
	}
	case 3:
	{
		warrior_1 = knight;

		warrior_2 = viking;
		break;
	}
	case 4:
	{
		warrior_1 = kosack;
		warrior_2 = viking;
		break;
	}

	}

	std::cout << warrior_1 << " \nVS\n\n " << warrior_2;
	std::cout << "\nFight !\n";


	int round = 0;

	while (true)
	{
		//system("CLS");

		std::cout << "\nRound " << round++ << std::endl;

		std::cout << warrior_1.GetName() << " attacks with "<<  warrior_1.GetWeaponName() << std::endl;

		int min_hp;

		if ((min_hp = attack(warrior_2, warrior_1.GetWeapon())) == 0)
		{
			std::cout << warrior_1.GetName() << " missed a shot\n" << std::endl;
		}
		else
		{
			std::cout << warrior_2.GetName() << " health minus -> " << min_hp << std::endl;
		}
		if (GetHealth(warrior_2) < 0)
		{
			std::cout << warrior_1.GetName() << " won!\n";
			break;
		}

		std::cout << warrior_2.GetName() << " attacks with " << warrior_2.GetWeaponName() << std::endl;

		if ((min_hp = attack(warrior_1, warrior_2.GetWeapon())) == 0)
		{
			std::cout << warrior_2.GetName() << " missed a shot!\n";
		}
		else
		{
			std::cout << warrior_1.GetName() <<" health minus -> " << min_hp << std::endl;
		}


		if (GetHealth(warrior_1) < 0)
		{
			std::cout << warrior_2.GetName() << " won!\n";
			break;
		}

		std::cout << warrior_1.GetName() << " and "<< warrior_2.GetName() <<" power decreases\n";

		warrior_1.decrese_of_power(heritage);
		warrior_2.decrese_of_power(heritage);

		Sleep(3000);

	}
	
	

	return EXIT_SUCCESS;
}