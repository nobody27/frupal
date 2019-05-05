#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct options{
	int size;
	int energy;
	int money;
	int binocularCost;
	int meadow;
	int forest;
	int bog;
	int rocks;
	int trees;

	void readOptions();
	void displayOptions();
	void changeOptions();
	void writeOptions();
};
void clear_all();
void display_splash();

int main(){
	options test;
	char reply = ' ';

	display_splash();	

	cout << "\n\n\nPress A to access the administration menu."
		<< "\nPress any other key to quit.";
	cin >> reply;

	test.readOptions();
	//	test.changeOptions();
	//	test.displayOptions();
	test.writeOptions();

	return 0;
}

void options::readOptions(){
	ifstream myfile;
	char next;
	int options[9];
	int i = 0;
	myfile.open("options.txt");
	while(!myfile.eof()){
		myfile.get(next);
		options[i] = next - '0';
		myfile.ignore(100,'\n');
		myfile.peek();			
		i++;
	}
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

}

void options::displayOptions(){
	clear_all();
	cout 	<< endl 
		<< "Size: " << size << endl
		<< "Energy: " << energy << endl
		<< "Money: " << money << endl
		<< "Cost of Binoculars: " << binocularCost << endl
		<< "Meadows: " << meadow << endl
		<< "Forests: " << forest << endl
		<< "Bog: " << bog << endl
		<< "Rocks: " << rocks << endl
		<< "Trees: " << trees << endl;

}

void options::changeOptions(){
	char option = ' ';
	char reply = '0';
	displayOptions();
	while(option != 'q'){
		displayOptions();
		cout << endl << "Press 'Q' to quit";
		cout << endl << "Which option would you like to change?" << endl
			<< "1: Size" << endl
			<< "2: Energy" << endl
			<< "3: Money" << endl
			<< "4: Cost of Binoculars" << endl
			<< "5: Meadows" << endl
			<< "6: Forests" << endl
			<< "7: Bog" << endl
			<< "8: Rocks" << endl
			<< "9: Trees" << endl;

		cin >> option;
		reply = tolower(option);
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
	} 
}

void options::writeOptions(){
	ofstream outfile;
	outfile.open("options.txt");
	outfile << size << ",size\n"
		<< energy << ",energy\n"
		<< money << ",money\n"
		<< binocularCost << ",binocularCost\n"
		<< meadow << ",meadow\n"
		<< forest << ",forest\n"
		<< bog << ",bog\n"
		<< rocks << ",rocks\n"
		<< trees << ",trees";
	outfile.close();

}

void clear_all(){
	system("clear");
	//cout << "\033[2J\033[1;1H";
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
