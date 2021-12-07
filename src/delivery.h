//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 2, 2019
//Class: CS202 - Programming Systems
//Program: #2 - Deliveries
//File: delivery.h
//Purpose: The purpose of this program is to keep track of information pertaining to packages being send and
//picked up from users, the program also allows the deliverer to deliver and pickup the package based on
//package type.
//delivery.h has the purpose of defining the classes and their functions that were used in the
//program. Also defines the relationship between classes whether it is "is a" or "has a".
//*****************************************************************************************



class delivery;



//Node Class
//Has the purpose of defining the node for the circular linked list, contains a "has a" relationship
//with delivery class. Has functions to allow the user to print the node infomation, print the specialized
//message of delivery pointer, compare the numberical type number stored in delivery, and a function 
//to interact with the delivery.
class node
{
	public:
		node();
		node(delivery * new_delivery, char * new_location);
		node(const node &to_copy);
		~node();

		void print_node();
		void print_message();
		bool compare(int n);
		int interact_package();

		node *& get_next();
		delivery * get_package();
	protected:
		delivery * package;
		char * location;
		node * next;
};



//Circular List Class
//Used to Define the circular linked list and its basic functions. contains a "has a" relationship
//with the node class. Printlist and retrieve package can be access from outside hieracrchy and print
//list and the latter prints the current head package. Classes with "is a" relationships can access
//methods to insert, remove, delete list, and copy_all.
class circular_list
{
	public:
		circular_list();
		circular_list(const circular_list &to_copy);
		~circular_list();

		void print_list();
		void retrieve_package();

	protected:
		void insert(delivery * new_delivery, char * new_location);
		void remove();
		void delete_list(node *& rear);
		void print_list(node * rear);
		void copy_all(node * source_rear, node * source, node *& rear);
		node * rear;
};



//Delivery List Class
//Used to define the list functions that handle specialized functions that pertain to the control
//of the delivery and its route. Has a "is a" relationship with circular_list. Has a function to
//add to the route depending on the type and a function to deliver or pickup a package.
class delivery_list : public circular_list
{
	public:
		delivery_list();
		void add_to_route();
		void deliver_package();
	protected:
};



//Delivery Classes
//Sender Class
//Used to contain the sender informations and define functions that use this info. Base class.
//Has a function to print the sender info.
class sender
{
	public:
		sender();
		sender(char * new_sname, char * new_saddress);
		sender(const sender &to_copy);
		~sender();

		void print_sender();
	protected:
		char * s_name;
		char * s_address;
};



//Reciever Class
//Used to contain the reciever information and define functions that use this info. Has a "is a" 
//relationship with sender. Allows the user to get an address and print the reciever information.
class reciever : public sender
{
	public:
		reciever();
		reciever(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress);
		reciever(const reciever & to_copy);
		
		char * get_raddress();
		void print_reciever();

		~reciever();
	protected:
		char * r_name;
		char * r_address;
};



//Delivery Class
//Used to contain the delivery information and the functions that perform operations on the information. Has
//a "is a" relationship with reciever. Has functions to print all info, print object spefic delivery message
//using dynamic binding, compares a delivery type, and allows a type to be changed.
class delivery : public reciever
{
	public:
		delivery();
		delivery(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type);
		delivery(const delivery &to_copy);
		virtual ~delivery();
		
		void print_info();
		virtual void print_package() = 0;
		bool compare_type(int c_type);
		void change_type(int c_type);
	protected:
		int type;
		char * package_info;
};



//Normal Class
//Used to define the dynamically binded normal object. Has a "is a" relationship with delivery.
class normal : public delivery
{
	public:
		normal();
		normal(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type);
		normal(const normal &to_copy);
		normal(const delivery &to_copy);
		
		void print_package();
};



//Used to define the dynamically binded insured object. Has a "is a" relationship with delivery. Has a function to perform a signature
//which needs RTTI to access.
class insured : public delivery
{
	public:
		insured();
		insured(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type);
		insured(const insured &to_copy);
		insured(const delivery &to_copy);

		void print_package();
		void sign_here();
};



//Used to define the dynamically binded pickup object. Has a "is a" relationship with delivery.
class pickup : public delivery
{
	public:
		pickup();
		pickup(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type);
		pickup(const pickup &to_copy);
		pickup(const delivery &to_copy);

		void print_package();
};



//Used to define the dynamically binded perish object. Has a "is a" relationship with delivery.
class parish : public delivery
{
	public:
		parish();
		parish(char * new_rname, char * new_raddress, char * new_sname, char * new_saddress, char * new_info, int new_type);
		parish(const parish &to_copy);
		parish(const delivery &to_copy);

		void print_package();

};






