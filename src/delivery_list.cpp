//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 2, 2019
//Class: CS202 - Programming Systems
//Program: #2 - Deliveries
//File: delivery_list.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to packages being send and
//picked up from users, the program also allows the deliverer to deliver and pickup the package based on
//package type.
//delivery_list.cpp has the purpose of implementing the functions that pertain to the node and
//delivery list class heirarchies.
//*****************************************************************************************
#include "delivery.h"
#include <iostream>
#include <cstring>



using namespace std;



//Node Class
//Node Default Constructor
node::node()
{
	package = nullptr;
	next = nullptr;
	location = nullptr;
}



//Node Assignment Constructor: Takes a delivery pointer and a char pointer as arguments.
node::node(delivery * new_delivery, char * new_location)
{
	package = new_delivery;
	next = nullptr;
	location = new char[strlen(new_location) + 1];
	strcpy(location, new_location);
}



//Node Copy Constructor: Takes a const reference node as an argument.
node::node(const node &to_copy)
{
	next = nullptr;
	if(to_copy.location)
	{
		location = new char[strlen(to_copy.location) + 1];
		strcpy(location, to_copy.location);
	}
	else
	{
		location = nullptr;
	}
	normal * ptr = dynamic_cast<normal*>(to_copy.package);
	if(ptr)
	{
		package = new normal(*ptr);
	}
	else
        {
		insured * ptr = dynamic_cast<insured*>(to_copy.package);
		if(ptr)
		{
			package = new insured(*ptr);
		}
		else
		{
			pickup * ptr = dynamic_cast<pickup*>(to_copy.package);
			if(ptr)
			{
				package = new pickup(*ptr);
			}
			else
			{
				parish * ptr = dynamic_cast<parish*>(to_copy.package);
				if(ptr)
				{
					package = new parish(*ptr);
				}
			}
		}	
	}
}



//Node Deconstructor
node::~node()
{
	if(location)
	{
		delete [] location;
	}
	if(package)
	{
		delete package;
	}
}



//Has the purpose of print the location and package info for a delivery.
void node::print_node()
{
	if(package)
	{
		if(location)
		{
			cout << " (P or D) Loccation: " << location;
		}
		package->print_info();
	}
}



//Has the purpose of printing the specialized message for a delivery
void node::print_message()
{
	if(package)
	{
		package->print_package();
	}
}



//Has the purpose of interacting with a delivery, if object is insured ptr->sign_here is called.
int node::interact_package()
{
	normal * ptr = dynamic_cast<normal*>(package);
	if(ptr)
	{
		return 1;
	}
	else
	{
		insured * ptr = dynamic_cast<insured*>(package);
		if(ptr)
		{
			ptr->sign_here();
			return 2;
		}
		else
		{
			pickup * ptr = dynamic_cast<pickup*>(package);
			if(ptr)
			{
				return 3;
			}
			else
			{
				parish * ptr = dynamic_cast<parish*>(package);
				if(ptr)
				{
					return 4;
				}
				else
				{
					return 0;
				}
			}
		}
	}
}



//Used to compare the types of a package. Takes a int as an argument and returns a bool.
bool node::compare(int n)
{
	return package->compare_type(n);
}



//Used to grab the next pointer, returns the pointer by reference.
node *& node::get_next()
{
	return next;
}



//Used to grab the package pointer, returns a package pointer.
delivery * node::get_package()
{
	return package;
}



//Circular List
//Circular List Default Constructor
circular_list::circular_list()
{	
	rear = nullptr;
}



//Circular List Copy Constructor: Takes a const reference circular_list object as an argument.
circular_list::circular_list(const circular_list &to_copy)
{
	rear = nullptr;
	if(to_copy.rear)
	{
		copy_all(to_copy.rear, to_copy.rear->get_next(), rear);
	}
}



//Function used to recursively copy a circular list, takes a node * pointer that acts as absolute head of the old 
//list, a pointer that acts as the traversal node of the old list, and a pass by reference node pointer of 
//the new list.
void circular_list::copy_all(node * source_rear, node * source, node *& rear)
{
	if(source == source_rear)
	{
		if(!rear)
		{
			rear = new node(*source);
			rear->get_next() = rear;
		}
		else
		{
			node * temp = new node(*source);
			temp->get_next() = rear->get_next();
			rear->get_next() = temp;
			rear = temp;
		}
		return;
	}
	if(!rear)
	{
		rear = new node(*source);
		rear->get_next() = rear;
	}
	else
	{
		node * temp = new node(*source);
		temp->get_next() = rear->get_next();
		rear->get_next() = temp;
		rear = temp;
	}
	copy_all(source_rear, source->get_next(), rear);
}



//Circular List Deconstructor
circular_list::~circular_list()
{
	if(rear)
	{
		delete_list(rear->get_next());
		delete rear;
	}
	rear = nullptr;
}



//Called by Deconstructor, Used to recursuvely delete the list, takes a pass by reference node pointer as an argument.
void circular_list::delete_list(node *& rear)
{
	if(rear == this->rear)
	{
		return;
	}
	delete_list(rear->get_next());
	if(rear)
	{
		node * temp = rear->get_next();
		delete rear;
		rear = temp;
	}
}



//Function used to insert a node into the list, inserts at rear or rear->next, takes a delivery pointer and char pointer
//as arguments.
void circular_list::insert(delivery * new_delivery, char * new_location)
{
	node * temp = nullptr;
	if(new_delivery)
	{
		temp = new node(new_delivery, new_location);
		if(!rear)
		{
			rear = temp;
			rear->get_next() = rear;
		}
		else
		{
			temp->get_next() = rear->get_next();
			rear->get_next() = temp;
			if(temp->compare(4) == false)
			{
				rear = temp;
			}
		}
	}
}



//Functions used to remove a node from the head of the list.
void circular_list::remove()
{
	node * temp = nullptr;
	if(!rear)
	{
		return;
	}
	else if(rear->get_next() == rear)
	{
		delete rear;
		rear = nullptr;
	}
	else
	{
		temp = rear->get_next();
		rear->get_next() = temp->get_next();
		delete temp;
	}
}



//Wrapper Function to print the list.
void circular_list::print_list()
{
	if(rear)
	{
		print_list(rear->get_next());
		rear->print_node();
	}
}



//Recursive function called by wrapper to print the list. Takes a node pointer as an argument.
void circular_list::print_list(node * rear)
{
	if(rear == this->rear)
	{
		return;
	}
	rear->print_node();
	print_list(rear->get_next());
}



//Function used to retrieve the info for the current rear->next (head of the list)
void circular_list::retrieve_package()
{
	if(rear)
	{
		cout << endl;
		node * temp = rear->get_next();
		temp->print_node();
		cout << endl;
		temp->print_message();
		cout << endl;
	}		
}



//Delivery Default Constructor
delivery_list::delivery_list() {}



//Function Used to add a package to the route, takes user input and sends it to the insert function, inserts based on whether
//it is perishable or not. 
void delivery_list::add_to_route()
{
	cin.ignore();
	cout << endl;
	delivery * ptr = nullptr;
	char sname[20], sadd[20], rname[20], radd[20], info[100];
	int type;
	cout << " Please enter the sender name: ";
	cin.getline(sname, sizeof(sname));
	cout << " Please enter the sender address: ";
	cin.getline(sadd, sizeof(sadd));
	cout << " Please enter the reciever name: ";
	cin.getline(rname, sizeof(rname));
	cout << " Please enter the reciever address: ";
	cin.getline(radd, sizeof(radd));
	cout << " Please enter the package info: ";
	cin.getline(info, sizeof(info));
	cout << " Please enter a number that corresponds with the following package types: 1 - Normal; 2 - Insured; 3 - Pickup; 4 - Parishables: ";
	cin >> type;
	if(type == 2)
	{
		ptr = new insured(rname, radd, sname, sadd, info, type);
		insert(ptr, radd);
	}
	else if(type == 3)
	{
		ptr = new pickup(rname, radd, sname, sadd, info, type);
		insert(ptr, sadd);
	}
	else if(type == 4)
	{
		ptr = new parish(rname, radd, sname, sadd, info, type);	
		insert(ptr, radd);
	}
	else
	{
		ptr = new normal(rname, radd, sname, sadd, info, type);
		insert(ptr, radd);
	}
}



//Function used to deliver a package, prints off current package and its special message/task, then deletes it. If its a packaage pickup
//then the pickup is changed into another form of delivery and readded to the list.
void delivery_list::deliver_package()
{
	delivery * ptr = nullptr;
	delivery * curr = nullptr;
	int type = 0;
	if(rear)
	{
		node * temp = rear->get_next();
		if(temp)
		{
			retrieve_package();
			if(temp->interact_package() == 3)
			{
				curr = temp->get_package();
				cout << " What package type is this delivery: 1 - Normal; 2 - Insured; 4 - Parishables: ";
				cin >> type;
				if(type == 2)
				{
					ptr = new insured(*curr);
					ptr->change_type(type);
				}
				else if(type == 4)
				{
					ptr = new parish(*curr);
					ptr->change_type(type);
				}	
				else
				{	
					ptr = new normal(*curr);
					ptr->change_type(1);
				}
			}
			remove();
			if(ptr)
			{
				insert(ptr, ptr->get_raddress());
			}
		}
	}
}
