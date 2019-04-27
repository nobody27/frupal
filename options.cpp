#include "options.h"
void options::testOptions(){
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
//	test.writeOptions();
/*	test.selectMenu();

	test.changeOptions();
*/
}
}

void options::readOptions(){
	ifstream myfile;
	string type;
	string name;
	string value;
	string line;
	string toolName;
	string obstacleName;
	int energySaved;
	int singleUse;
	int price;
	int quantity;		
	//char next[MAX_LINE_COUNT][MAX_LINE_LENGTH];
	 lineCount = 0;
	myfile.open("options.txt");
	
	while(getline(myfile, line)){
		lineCount++;
		if(line[0] == '3'){
			toolCount++;
		}else if(line[0] == '2'){
			obstacleCount++;
		}
	}
	cout << "\nLine count = " << lineCount;
	cout << "\nTool count = " << toolCount;
	cout << "\nObstacle count = " << obstacleCount;

	loadedTools = new Tool*[toolCount];	
	obstacles = new string[obstacleCount];

	myfile.close();
	myfile.open("options.txt");
	int i = 0;
	while(getline(myfile, type, ',')){
	cout << "\nType: " << type;
	
	if(type[0] == '1'){
		getline(myfile, name, ',');
		cout << "\nName: " << name;
		getline(myfile, value, '\n');
		cout << "\nValue: " << value;
			if(!name.compare("boardSize")){
					boardSize = stoi(value);
			}else if(!name.compare("startEnergy")){
					startEnergy = stoi(value);
			}else if(!name.compare("startMoney")){
					startMoney = stoi(value);
			}else if(!name.compare("binocularCost")){
					binocularCost = stoi(value);
			}

	}else if(type[0] == '2'){
		getline(myfile, name, '\n');
		obstacles[i] = name;
	}else if(type[0] == '3'){
		getline(myfile, toolName, ',');
		getline(myfile, obstacleName, ',');
		getline(myfile, value, ',');
		energySaved = stoi(value);
		getline(myfile, value, ',');
		singleUse = stoi(value);
		getline(myfile, value, ',');
		price = stoi(value);
		getline(myfile, value);
		quantity = stoi(value);
		
		cout << "\nTool name: " << toolName <<
			"\nObstacle name: " << obstacleName <<
			"\nEnergy saved: " << energySaved <<
			"\nsingleUse: " << singleUse <<
			"\nprice: " << price <<
			"\nquantity: " << quantity;
		loadedTools[i] = new Tool(toolName, obstacleName, energySaved, singleUse, price, quantity);			
	}
	i++;

myfile.peek();	
	}
}

void options::displayOptions(){
	clear_all();

	cout << "\nBoard size: " << boardSize <<
		"\nStarting Energy: " << startEnergy <<
		"\nStarting Money: " << startMoney <<
		"\nBinoculars Cost: " << binocularCost;

	for(int t = 0; t < toolCount; t++){
		cout << "\nTool " << (t+1) << ": ";
	}
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
//	cout << "\033[2J\033[1;1H";
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
	//	clear_all();
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
/*
	char* prev;
	char* parts;
	char* maybethiswillwork;
	cout << "\nPrinting options starting with '1'" << endl;
	for(int i = 0; i < lineCount; i++){
		if(lines[i][0] == '1'){
			//cout << lines[i] << endl;
//			maybethiswillwork = new char[strlen(lines[i])+1];
			strcpy(maybethiswillwork, lines[i]);
//			parts = strtok(maybethiswillwork,",");	
//			while(parts != NULL){
			while((parts = strtok_r(maybethiswillwork, ",", &maybethiswillwork))){
				//cout << parts << endl;
				strcpy(prev, parts);
//				parts = strtok(NULL, ",");	
				if(!strcmp(prev, "boardSize") && parts){
					boardSize = atoi(parts);
				}else if(!strcmp(prev, "startEnergy") && parts){
					startEnergy = atoi(parts);
				}else if(!strcmp(prev, "startMoney") && parts){
					startMoney = atoi(parts);
				}else if(!strcmp(prev, "binocularCost") && parts){
					binocularCost = atoi(parts);
				}
			}
		}
//			delete maybethiswillwork;
	}
//		free(maybethiswillwork);
*/	
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
	char x;
cin >> x;
}
