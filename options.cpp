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

	int lineCount;

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
};
void clear_all();
void display_splash();

const int MAX_LINE_COUNT = 20;
const int MAX_LINE_LENGTH = 100;

int main(){
	options test;
	char reply = ' ';

	display_splash();	

	cout << "\n\n\nPress A to access the administration screen."
		<< "\nPress any other key to quit."
		<< "\nYour choice: ";
	cin >> reply;
	reply = toupper(reply);

	if(reply == 'A'){
	test.readOptions();
	test.displayOptions();
	test.optionsMainMenu();
	test.writeOptions();
/*	test.selectMenu();

	test.changeOptions();
*/
}
	return 0;
}

void options::readOptions(){
	ifstream myfile;
	char next[MAX_LINE_COUNT][MAX_LINE_LENGTH];
	 lineCount = 0;
	myfile.open("options.txt");
	while(!myfile.eof()){
		myfile.getline(next[lineCount], MAX_LINE_LENGTH);
		lineCount++;
	}
	cout << lineCount << " options were loaded." << endl;

cout << endl << endl << endl;
lines = new char*[lineCount];
for(int n = 0; n < lineCount; n++){
	lines[n] = new char[strlen(next[n])+1];
	strcpy(lines[n], next[n]);
//	cout << lines[n] << endl;
}

/*

myfile.clear();

	while(!myfile.eof()){
		myfile.getline(next, 100);

for(int x = 0; x < 100; x++){
	cout << next[x];
}
		
//		options[i] = next - '0';
//		myfile.ignore(100,'\n');
		myfile.peek();			
	}
	myfile.close();

	size = options[0];
	energy = options[1];
	money = options[2];
	binocularCost = options[3];
	meadow = options[4];
	forest = options[5];
	bog = options[6];
	rocks = options[7];
	trees = options[8];
	myfile.close();
*/
}

void options::displayOptions(){
	clear_all();

for(int i = 0; i < lineCount; i++){
	cout << lines[i] << endl;
}
	cout 	<< endl ;
/*
		<< "Size: " << size << endl
		<< "Energy: " << energy << endl
		<< "Money: " << money << endl
		<< "Cost of Binoculars: " << binocularCost << endl
		<< "Meadows: " << meadow << endl
		<< "Forests: " << forest << endl
		<< "Bog: " << bog << endl
		<< "Rocks: " << rocks << endl
		<< "Trees: " << trees << endl;
*/
}

void options::changeOptions(){
	char reply = ' ';
	displayOptions();
	while(reply != 'q'){
		displayOptions();
		cout << "\nPress 'Q' to quit";
		
		//First tier menus: starting params,
				//define obstacles
				//define tools
		cout << "\nPress '1' to access General Options" <<
			"\nPress '2' to access Obstacle Options" <<
			"\nPress '3' to access Tool Options";

/*		cout << endl << "Which option would you like to change?" << endl
			<< "1: Size" << endl
			<< "2: Energy" << endl
			<< "3: Money" << endl
			<< "4: Cost of Binoculars" << endl
			<< "5: Meadows" << endl
			<< "6: Forests" << endl
			<< "7: Bog" << endl
			<< "8: Rocks" << endl
			<< "9: Trees" << endl;
*/
		cin >> reply;
		reply = tolower(reply);
		
		switch(reply){
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
		}
/*
		switch(option){
			case '1':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				size = reply - '0';
				break;
			case '2':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				energy = reply - '0';
				break;
			case '3':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				money = reply - '0';
				break;
			case '4':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				binocularCost = reply - '0';
				break;
			case '5':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				meadow = reply - '0';
				break;
			case '6':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				forest = reply - '0';
				break;
			case '7':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				bog = reply - '0';
				break;
			case '8':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				rocks = reply - '0';
				break;
			case '9':
				reply = '0';
				while(reply - '0' < 1 || reply - '0' > 9){
					cout << endl << "Enter a number from 1-9: ";
					cin >> reply;
				}
				trees = reply - '0';
				break;
			default:

				break;
		}
*/
	} 
}

void options::writeOptions(){
	ofstream outfile;
	outfile.open("options.txt");
	for(int i = 0; i < lineCount - 1; i++){
		outfile << lines[i] << "\n";
	}
	outfile << lines[lineCount];
/*
	outfile << size << ",size\n"
		<< energy << ",energy\n"
		<< money << ",money\n"
		<< binocularCost << ",binocularCost\n"
		<< meadow << ",meadow\n"
		<< forest << ",forest\n"
		<< bog << ",bog\n"
		<< rocks << ",rocks\n"

		<< trees << ",trees";
*/
	outfile.close();

}

void clear_all(){
	cout << "\033[2J\033[1;1H";
}

void display_splash(){
	clear_all();
	char pixel = ' ';
	ifstream splash;
	splash.open("splash.txt");
	while(!splash.eof()){
		splash.get(pixel);
		cout << pixel;
		splash.peek();
	}
}

void options::displayCategories(){


	char reply = ' ';

	while(reply != 'q'){
	displayCategories();

	}

}

void options::optionsMainMenu(){
	char reply = ' ';

	while(reply != 'q'){
		clear_all();
		cout << "Which category would you like to configure?" <<
			"\nPress '1' to configure general settings." <<
			"\nPress '2' to configure obstacles." <<
			"\nPress '3' to configure tools." <<
			"\nPress 'Q' to quit.";

		cin >> reply;
		reply = tolower(reply);
		
		switch(reply){
			case '1':
				generalMenu();
				break;
			case '2':
				obstacleMenu();	
				break;
			case '3':
				toolMenu();
				break;
			default:
				break;
		}
	}
}

void options::generalMenu(){

	char reply = ' ';	
	char* prev;
	char* parts;

	cout << "\nPrinting options starting with '1'" << endl;
	for(int i = 0; i < lineCount; i++){
		if(lines[i][0] == '1'){
			//cout << lines[i] << endl;
			
			parts = strtok(lines[i],",");	
			while(parts != NULL){
				//cout << parts << endl;
				strcpy(prev, parts);
				parts = strtok(NULL, ",");	
				if(!strcmp(prev, "boardSize")){
					boardSize = atoi(parts);
				}else if(!strcmp(prev, "startEnergy")){
					startEnergy = atoi(parts);
				}else if(!strcmp(prev, "startMoney")){
					startMoney = atoi(parts);
				}else if(!strcmp(prev, "binocularCost")){
					binocularCost = atoi(parts);
				}
			}
		}
	}

	
	while(reply != 'Q'){
	clear_all();
	cout << "General options:" <<
		"\n\nBoard Size = " << boardSize <<
		"\nStarting Energy = " << startEnergy <<
		"\nStarting Money = " << startMoney <<
		"\nBinocular Cost = " << binocularCost <<
	 	"\n\nWhich option would you like to change?" <<
		"\nPress '1' to change board size." <<
		"\nPress '2' to change starting energy." <<
		"\nPress '3' to change starting money." <<
		"\nPress '4' to change binocular cost." <<
		"\nPress 'Q' to quit to the previous menu." <<
		"\n\nYour choice: ";

		cin >> reply;
		reply = toupper(reply);
		switch(reply){
			case '1':
				cout << "\nEnter a number: ";
				cin >>	boardSize;
				break;
			case '2':
				cout << "\nEnter a number: ";
				cin >>	startEnergy;
				break;
			case '3':
				cout << "\nEnter a number: ";
				cin >>	startMoney;
				break;
			case '4':
				cout << "\nEnter a number: ";
				cin >>	binocularCost;
				break;
			default:
				break;	
		}
	}
}

void options::obstacleMenu(){
	cout << "\nPrinting options starting with '2'" << endl;
	for(int i = 0; i < lineCount; i++){
		if(lines[i][0] == '2'){
			cout << lines[i] << endl;
		}
	}
	char x;
cin >> x;
}
void options::toolMenu(){
	cout << "\nPrinting options starting with '3'" << endl;
	for(int i = 0; i < lineCount; i++){
		if(lines[i][0] == '3'){
			cout << lines[i] << endl;
		}
	}
	int x;
cin >> x;
}
