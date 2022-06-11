//============================================================================
// Name        : Reverse Engineering Project 1.cpp
// Author      : Zac Gonzalez
// Version     :
// Copyright   : Copyright of Zac Gonzalez
// Description : Final Project for Software Reverse Engineering
//============================================================================

//Includes
#include <iostream>
#include <string>
using namespace std;

//initialized Variables
string userName;
int passWord = 321;
int choice = 5;

//string Array for Clients
string clients[2][5] = { {"Bob Jones","Sarah Davis","Amy Friendly","Johnny Smith","Carol Spears"},{"2","2","1","1","2"} };

//Password Check Function
void checkPass() {
	cout << endl;
	cout << "Hello! Welcome to our Investment Company." << endl;
	cout << "Enter Your Username:\n" << endl;
	cin >> userName;
	cout << "Enter Your Password:\n" << endl;
	cin >> passWord;
	cout << "Checking Password..." << endl;
}

//Change Customer Choice Function
void changeCustomerChoice() {
	int temp = 0;

	int serviceOption;
	cout << endl;
	cout << "You chose 2" << endl << endl;
	cout << "Enter the number of the client that you wish to change" << endl << endl;
	cin >> temp;
	cout << endl;

	//Error if Improper Selection
	if (temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5) {
		cout << "Improper Selection! Please Try Again!" << endl;
		changeCustomerChoice();
	}

	cout << endl;
	cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)\n";
	cout << endl;
	cin >> serviceOption;
	cout << endl;

	if (serviceOption == 1 || serviceOption == 2) {
		//Selecting Service Choice
		cout << "Please Confirm New Service Choice (1 = Brokerage, 2 = Retirement)\n"  << endl << endl;
		cin >> clients[1][temp - 1];
		cout << endl;
		cout << "Changed Option To : " << clients[1][temp - 1];

	}
	if (serviceOption != 1 && serviceOption != 2) {
		//Error if Service Choice is Incorrect
		cout << "Incorrect Service Choice! Pleast Try Again!" << endl;
		changeCustomerChoice();
	}
}

//Display Function
void DisplayInfo() {

		cout << endl;
		cout << "You chose 1\n" << endl << "Client's Name Service Selected (1 = Brokerage, 2 = Retirement)\n";
		for (int i = 0; i < 5; i++) {
			cout << clients[0][i] << " selected option " << clients[1][i] << endl;
		}

		
	}

//Choice Selection Function
void choiceSelection() {
	cout << endl;
	cout << "What would you like to do?" << endl;
	cout << "Display Client Info (enter 1)" << endl;
	cout << "CHANGE a client's choice (enter 2)" << endl;
	cout << "Exit the program.. (enter 3)" << endl;
	cout << "Enter your choice:\n" << endl;
	cin >> choice;

	switch (choice) {

	case 1:
		DisplayInfo();
		choiceSelection();
		break;

	case 2:
		changeCustomerChoice();
		choiceSelection();
		break;

	case 3:
		exit(0);

	default:
		cout << "Invalid Selection" << endl;
		cin.clear();
		choiceSelection();
	}
}

//Main Function
int main() {


	cout << endl;
	cout << "Hello! Welcome to our Investment Company." << endl << endl;
	cout << "Enter Your Username:\n" << endl;
	cin >> userName;
	cout << endl;
	cout << "Enter Your Password:\n" << endl;
	cin >> passWord;
	cout << endl;
	cout << "Checking Password..." << endl;

	//Allow Access if Password is Correct
	if (passWord == 123) {
		cout << "Access Granted!" << endl;
		choiceSelection();
	}

	//Prevent Access if Password is Incorrect
	if (passWord != 123) {
		cout << endl << "Incorrect Password! Try Again!" << endl << endl << endl;
		main();
	}
	

	return 0;
}