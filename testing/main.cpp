#include<iostream>
#include<array>
#include<sstream>

using namespace std;

struct patient_info {
	string id;
	string f_name;
	string l_name;
	int age;
	string gender;
	string phone;
	string address;
};

struct date_time {
	int date;
	int month;
	int year;
	int hour;
	int minute;
};

struct waiting_node {
	struct patient_info info;
	string sickness_descp;
	struct date_time datetime;
	bool disab_option;
	string doct_name;
	string med_info;
	struct waiting_node* prev;
	struct waiting_node* next;
};

struct history_node {
	struct patient_info info;
	string sickness_descp;
	struct date_time datetime;
	bool disab_option;
	string doct_name;
	string med_info;
	struct waiting_node* prev;
	struct waiting_node* next;
};

struct waiting_node* wRoot = NULL;
struct history_node* hRoot = NULL;

int main()
{
 cout << "hello";
}