//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 2, 2019
//Class: CS202 - Programming Systems
//Program: #2 - Deliveries
//File: delivery.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to packages being send and
//picked up from users, the program also allows the deliverer to deliver and pickup the package based on
//package type.
//delivery.cpp has the purpose of implementing the functions pertaining to the delivery classes
//and their parents.
//*****************************************************************************************
#include "delivery.h"
#include <iostream>
#include <cstring>



using namespace std;



//Sender Class
//Sender Default Constuctor
sender::sender()
{
	s_name = nullptr;
	s_address = nullptr;
}



//Sender Assignment Constructor: takes two char * pointers as arguments.
sender::sender(char * new_sname, char * new_saddress)
{
	s_name = new char[strlen(new_sname) + 1];
	strcpy(s_name, new_sname);
	s_address = new char[strlen(new_saddress) + 1];
	strcpy(s_address, new_saddress);
}



//Sender Copy Constructor: Takes a const reference sender class as an argument.
sender::sender(const sender &to_copy)
{
	s_name = new char[strlen(to_copy.s_name) + 1];
	strcpy(s_name, to_copy.s_name);	
	s_address = new char[strlen(to_copy.s_address) + 1];
	strcpy(s_address, to_copy.s_address);	
}



//Sender Destructor
sender::~sender()
{
	if(s_name)
	{
		delete [] s_name;
	}
	if(s_address)
	{
		delete [] s_address;
	}
}



//Has the purpose of printing the sender class members.
void sender::print_sender()
{
	if(s_name)
	{
		cout << " Sender Name: " << s_name << endl;
	}
	if(s_address)
	{
		cout << " Sender Address: " << s_address << endl;
	}
}



//Reciever Class
//Reciever Default Constructor
reciever::reciever()
{
	r_name = nullptr;
	r_address = nullptr;
}



//Reciever Assignment Constructor, Takes 4 char * as arguments. Calls the assignment constructor for sender.
reciever::reciever(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress) : sender(new_sname, new_saddress)
{
	r_name = new char[strlen(new_rname) + 1];
	strcpy(r_name, new_rname);
	r_address = new char[strlen(new_raddress) + 1];
	strcpy(r_address, new_raddress);	
}



//Reciever Copy Constructor. Takes a const reference reciever object. Calls the copy constructor for sender.
reciever::reciever(const reciever &to_copy) : sender(to_copy)
{
	r_name = new char[strlen(to_copy.r_name) + 1];
	strcpy(r_name, to_copy.r_name);
	r_address = new char[strlen(to_copy.r_address) + 1];
	strcpy(r_address, to_copy.r_address);
}



//Reciever Deconstructor
reciever::~reciever()
{
	if(r_name)
	{
		delete [] r_name;
	}
	if(r_address)
	{
		delete [] r_address;
	}
}



//Has the purpose of returning the address of the reciever. Returns a char pointer as an output.
char * reciever::get_raddress()
{
	return r_address;
}



//Has the purpose of printing out the information that pertains to the reciever class.
void reciever::print_reciever()
{
	if(r_name)
	{
		cout << " Reciever Name: " << r_name << endl;
	}
	if(r_address)
	{
		cout << " Reciever Address: " << r_address << endl;
	}
}



//Delivery Class
//Delivery Default Constructor
delivery::delivery()
{
	package_info = nullptr;
}



//Delivery Assignment Constructor: Takes 5 char pointers and an int as arguments. Calls the assignment constructor for reciever.
delivery::delivery(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type) : reciever(new_rname, new_raddress, new_sname, new_saddress)
{
	package_info = new char[strlen(new_info) + 1];
	strcpy(package_info, new_info);
	type = new_type;
}



//Delivery Copy Constructor: Takes a const reference delivery object as an argument. Calls the Reciever copy constructor.
delivery::delivery(const delivery &to_copy) : reciever(to_copy)
{
	package_info = new char[strlen(to_copy.package_info) + 1];
	strcpy(package_info, to_copy.package_info);
	type = to_copy.type;
}



//Delivery Deconstructor
delivery::~delivery()
{
	if(package_info)
	{
		delete [] package_info;
	}
}



//Used to print out all information that pertains to a package, its sender info, reciever info, content, and type.
void delivery::print_info()
{
	cout << endl << " Package Information: " << endl;
	print_sender();
	print_reciever();
	cout << " Contents: " << package_info << endl;
	cout << " Package Type: ";
	if(type == 2)
	{
		cout << "Insured" << endl;
	}
	else if(type == 3)
	{
		cout << "Pickup" << endl;
	}
	else if(type == 4)
	{
		cout << "Parishable" << endl;
	}
	else
	{
		cout << "Normal" << endl; 
	}
}



//Used to compare the package type returns true of c_type is same otherwise false. Takes an int as an argument.
bool delivery::compare_type(int c_type)
{
	if(c_type == type)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//Used to change the type stored in the class. Takes a int as an argument.
void delivery::change_type(int c_type)
{
	if(c_type > 0 && c_type <=4)
	{
		type = c_type;
	}
}



//Package Types

//Normal Class
//Normal Default Constructor
normal::normal() {}



//Normal Assignment Constructor: Supplies information to Delivery Assignment Constructor
normal::normal(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type) : delivery(new_rname, new_raddress, new_sname, new_saddress, new_info, new_type) {}



//Normal "Normal" Copy Constructor: Takes a const reference normal object, calls delivery copy constructor.
normal::normal(const normal &to_copy) : delivery(to_copy) {}



//Normal "Delivery" Copy Constructor: Takes a const reference delivery object, calls delivery copy constructor.
normal::normal(const delivery &to_copy) : delivery(to_copy) {}



//Used to print specialized message for normal class.
void normal::print_package()
{
	cout << " Hello valued customer, a package has been delivered to your residence. Have a Nice Day! " << endl;
}



//Insured Class
//Insured Default Constructor
insured::insured() {}



//Insured Argument Constructor: Supplies information to Delivery Assignment Constructor
insured::insured(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type) : delivery(new_rname, new_raddress, new_sname, new_saddress, new_info, new_type) {}



//Insured "Insured" Copy Constructor: Takes a const reference Insured object, calls delivery copy constructor.
insured::insured(const insured &to_copy) : delivery(to_copy) {}



//Insured "Delivery" Copy Constructor: Takes a const reference delivery object, calls delivery copy constructor.
insured::insured(const delivery &to_copy) : delivery(to_copy) {}



//Used to print specialized message for insured class.
void insured::print_package()
{
	cout << " Hello esteemed customoer, an insured package has been delivered to your residence. " << endl;
}



//Unsed to get user to sign a signature for a package then print that sgnature out. Can only be access with RTTI
//when accessed with a derived pointer.
void insured::sign_here()
{
	cin.ignore();
	char sign[20];
	cout << " Please sign a signature here to release the package: ";
	cin.getline(sign, sizeof(sign));
	cout << endl << " Thanks " << sign << " for your signature. Have a Nice Day! " << endl;
}



//Pickup Class
//Pickup Default Constructor
pickup::pickup() {}



//Pickup Assignment Constructor: Supplies info to Delivery Assignment Constructor
pickup::pickup(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type) : delivery(new_rname, new_raddress, new_sname, new_saddress, new_info, new_type) {}



//Pickup "Pickup" Copy Constructor: Takes a const reference pickup object, calls the Delivery Copy Constructor
pickup::pickup(const pickup &to_copy) : delivery(to_copy) {}



//Pickup "Delivery" Copy Constructor: Takes a const reference delivery object, calls the Delivery Copy Constructor
pickup::pickup(const delivery &to_copy) : delivery(to_copy) {}



//Used to Print Specialized message for pickup class.
void pickup::print_package()
{
	cout << " Hello valued customer, I am here for the package you requested to be delivered. " << endl;
}



//Parish Class
parish::parish() {}



//Parish Assignment Constructor: Supplies info to Delivery Assignment Constructor
parish::parish(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type) : delivery(new_rname, new_raddress, new_sname, new_saddress, new_info, new_type) {}



//Parish "Parish" Copy Constructor: Takes a const reference parish object, calls delivery copy constructor
parish::parish(const parish &to_copy) : delivery(to_copy) {}



//Parish "Delivery" Copy Constructor: Takes a const reference delivery object, calls delivery copy constructor
parish::parish(const delivery &to_copy) : delivery(to_copy) {}



//Used to Print Specialized message for parish class.
void parish::print_package()
{
	cout << " Hello valued customer, a parishable package has been delivered to your residence as quickly as possible. Have a Nice Day! " << endl;
}


