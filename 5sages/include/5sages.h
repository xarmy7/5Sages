#pragma once

#include <thread>
#include <mutex>
#include <vector>

class Sages
{
public:
	int thinkTime = 0;
	int eatTime = 0;
	int actualStick = 0;
	int nextStick = 0;
	std::string name;
	int myTime = 0;
	bool waiting = false;

	std::thread thinkAndEat{};

	Sages() {};
	Sages(int think, int eat, int currIndex, int nextIndex);
};

class Action
{
private:

public:
	int numberOfsage = 5;
	std::vector<Sages> sagesArray;
	//Sages sagesArray[5]; //ToChange
};