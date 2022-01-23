#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <memory>
#include <windows.h>

#include "5sages.h"

std::mutex my_mutex; //mutex for the program
std::vector<std::unique_ptr<std::mutex>> sticks; //stock mutex sticks into vector

//Random
std::default_random_engine rndm;
std::uniform_int_distribution<int> range(1, 5);

void foo(Sages* sages)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	my_mutex.lock();
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << sages->name << " commence a penser."<< std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	my_mutex.unlock();

	while (sages->myTime <= 5)
	{
		std::this_thread::sleep_for(std::chrono::seconds(sages->thinkTime));

		if (sages->waiting == false)
		{
			my_mutex.lock();
			SetConsoleTextAttribute(hConsole, 11);
			std::cout << sages->name << " est epuise de penser et voudrais bien manger" << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			my_mutex.unlock();
		}

		if (sticks[sages->actualStick]->try_lock())
		{
			if (sticks[sages->nextStick]->try_lock())
			{
				my_mutex.lock();
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				std::cout << sages->name << " se goinfre pendant " << sages->eatTime << " secondes" << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
				sages->waiting = false;
				my_mutex.unlock();

				std::this_thread::sleep_for(std::chrono::seconds(sages->eatTime));

				my_mutex.lock();
				sages->myTime += sages->eatTime;
				std::cout << sages->name << " a fait le plein d'energie et repart reflechir sur la fin du monde" << std::endl;
				my_mutex.unlock();

				sticks[sages->nextStick]->unlock();
			}
			else
			{
				if (sages->waiting != true)
				{
					my_mutex.lock();
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					std::cout << sages->name << " doit attendre que la baguette " << sages->nextStick << " soit disponible." << std::endl;
					SetConsoleTextAttribute(hConsole, 7); //7 -> white
					sages->waiting = true;
					my_mutex.unlock();
				}
			}
			sticks[sages->actualStick]->unlock();
		}
		else
		{
			if (sages->waiting != true)
			{
				my_mutex.lock();
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				std::cout << sages->name << " doit attendre, car la baguette " << sages->actualStick << " n'est pas disponible pour l'instant" << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
				sages->waiting = true;
				my_mutex.unlock();
			}
		}
	}
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << sages->name << " quitte la table car il a beaucoup mange !! " << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

int main()
{
	Action action;

	int nextIndex = 0;

	std::cout << "Combien de philosophe sont autours de la table ?" << std::endl;
	std::cin >> action.numberOfsage;

	for (int i = 0; i < action.numberOfsage; i++)
	{
		nextIndex = i + 1;
		if (i == action.numberOfsage - 1)
			nextIndex = 0;

		action.sagesArray.push_back({ range(rndm), range(rndm), i, nextIndex }); //thinkTime, eatime, stick, nextStick
		sticks.push_back(std::unique_ptr<std::mutex>(new std::mutex));
		std::cout << "Comment s'appelle le philosophe numero " << i + 1 << " ?" << std::endl;
		std::cin >> action.sagesArray[i].name;
	}

	for (int i = 0; i < action.numberOfsage; i++)
		action.sagesArray[i].thinkAndEat = std::thread{ foo, &action.sagesArray[i] };

	for (int i = 0; i < action.numberOfsage; i++)
		action.sagesArray[i].thinkAndEat.join();

	return 0;
}