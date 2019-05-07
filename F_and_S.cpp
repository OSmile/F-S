#include "pch.h"
#include <iostream>
#include <string>


// Определяем интерфейс всех животных
class Animal {
public:
	virtual std::string getSound() = 0;
};

// Реализация интерфейса животных
class Cat : public Animal {
public:

	std::string getSound()override {
		return "Meow-meow";
	}
};

class Dog : public Animal {
public:

	std::string getSound()override {
		return "Bow-wow";
	}
};

// Объявление фабричного метода, который будет возвращать объект типа Животное
class Creator {
protected:
	Creator() {}
public:
	virtual Animal* CreateAnimal() = 0;
};

// Переопределение фабричного метода так, чтобы он создавал и возвращал животное
// учитывая то, есть ли у нас уже такое животное или нет
class CreatorCat : public Creator {
private:
	CreatorCat(){}
	static CreatorCat* cat;
public:

	static CreatorCat * GetInstance()
	{
		if (!cat)
		{
			cat = new CreatorCat();
			std::cout << "Oh... Your first cat" << std::endl;
		}
		else
			std::cout << "Cat already in" << std::endl;
		return cat;
	}

	Animal* CreateAnimal()override {
		return new Cat();
	}

};

CreatorCat* CreatorCat::cat = 0;

class CreatorDog : public Creator {
	CreatorDog() {}
	static CreatorDog* dog;
public:

	static CreatorDog* GetInstance()
	{
		if (!dog)
		{
			dog = new CreatorDog();
			std::cout << "Oh... Your first dog" << std::endl;
		}
		else
			std::cout << "Dog already in" << std::endl;
		return dog;
	}

	Animal* CreateAnimal()override {
		return new Dog();
	}

};

CreatorDog* CreatorDog::dog = 0;


int main()
{
	Creator* cat = CreatorCat::GetInstance();
	std::cout << cat->CreateAnimal()->getSound() << std::endl;

	Creator* dog = CreatorDog::GetInstance();
	std::cout << dog->CreateAnimal()->getSound() << std::endl;

	Creator* dog2 = CreatorDog::GetInstance();
	std::cout << dog2->CreateAnimal()->getSound() << std::endl;
	
	return 0;
}
