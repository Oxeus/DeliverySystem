//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 2, 2019
//Class: CS202 - Programming Systems
//Program: #2 - Deliveries
//File: assignment02.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to packages being send and 
//picked up from users, the program also allows the deliverer to deliver and pickup the package based on 
//package type.
//assignment02.cpp has the purpose of controlling the program and calling the methods defined in the classes.
//*****************************************************************************************

#include "delivery.h"
#include <iostream>

using namespace std;

int main()
{
	delivery_list list;
	bool control = true;
	int choice = 0;
	cout << " ------------------------ Assignment 02: Deliveries ------------------------ " << endl;
	while(control)
	{
		cout << endl;
		cout << " -------------------- Menu -------------------- " << endl;
		cout << " Option 01: Add a Package to the Route. " << endl;
		cout << " Option 02: Print the Route. (Testing) " << endl;
		cout << " Option 03: Deliver a Package. " << endl;
		cout << " Option 04: Make a Copy of the Route. " << endl;
		cout << " Option 05: Quit the Delivery Program. " << endl;
		cout << " ---------------------------------------------- " << endl;
		cout << " Please enter an option of your choice: ";
		cin >> choice;
		switch(choice){
			case 1:
				list.add_to_route();
				break;
			case 2: 
				list.print_list();
				break;
			case 3:
				list.deliver_package();
				break;
			case 4:

				break;
			case 5:
				control = false;
				break;
		}
	
	}
	cout << endl;
	cout << " --------------------------- Exiting the Program --------------------------- " << endl;
	return 0;
}
