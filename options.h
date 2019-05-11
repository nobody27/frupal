#ifndef OPTIONS_H
#define OPTIONS_H
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "seeker.h"

using namespace std;

struct options{
	char** lines;
	int boardSize = 0;
	int startEnergy = 0;
	int startMoney = 0;
	int binocularCost = 0;

	int toolCount = 0;
	int lineCount = 0;
	int obstacleCount = 0;
	string* obstacles;
	
	Tool** loadedTools;
/*
	int size;
	int energy;
	int money;
	int binocularCost;
	int meadow;
	int forest;
	int bog;
	int rocks;
	int trees;
*/

	void readOptions();
	void displayOptions();
	void changeOptions();
	void writeOptions();

	void generalMenu();
	void obstacleMenu();
	void toolMenu();
	void displayCategories();
	void optionsMainMenu();
	void testOptions();
};
void clear_all();
void display_splash();

const int MAX_LINE_COUNT = 20;
const int MAX_LINE_LENGTH = 100;

#endif
