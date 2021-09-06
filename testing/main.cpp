#include <iostream>
#include <array>
#include <sstream>
#include <conio.h>
#include <string>
#include<windows.h>

using namespace std;

struct address {
    string addressNo;
    string buildingStreet;
    int zip;
    string city;
    string state;
    string country;

    address() {};

    address(string addressNo, string buildingStreet, int zip, string city, string state, string country) {
        this->addressNo = addressNo;
        this->buildingStreet = buildingStreet;
        this->zip = zip;
        this->city = city;
        this->state = state;
        this->country = country;
    }
};

struct patient_info {
    string id;
    string first_name;
    string last_name;
    int age;
    string gender;
    string phone;
    address pAddress;

    patient_info() {};

    patient_info(string id, string first_name, string last_name, int age, string gender, string phone, address pAddress) {
        this->id = id;
        this->first_name = first_name;
        this->last_name = last_name;
        this->age = age;
        this->gender = gender;
        this->phone = phone;
        this->pAddress = pAddress;
    }
};

struct date_time {
    int date;
    int month;
    int year;
    int hour;
    int minute;
    long long int abbr;
    long long int y = 100000000;
    long long int m = 1000000;
    long int d = 10000;
    //line 54 to 57 can be ignored, only used in sorting by date and time

    date_time() {};

    date_time(int date, int month, int year, int hour, int minute) {
        this->date = date;
        this->month = month;
        this->year = year;
        this->hour = hour;
        this->minute = minute;
        abbr = year * (y)+month * (m)+date * (d)+hour * (100) + minute;
    }
};

struct Node {
    patient_info info;
    string sickness_descp;
    date_time dateTime;
    bool disab_option;
    string doct_name;
    string med_info;
    struct Node* prev;
    struct Node* next;

    Node() {};

    Node(patient_info info, date_time dateTime, bool disab_option) {
        this->info = info;
        this->sickness_descp = "";
        this->dateTime = dateTime;
        this->disab_option = disab_option;
        this->doct_name = "";
        this->med_info = "";
    }

}*wHead, * wCurrent, * wTail, * hHead, * hCurrent, * hTail;

class nurses {
public:

    void addNewPatient() { //for question 1.1 adding patient to the waiting list (add into menu)
        string id, first_name, last_name, gender, phone, addressNo, buildingStreet, city, state, country;
        int age, zip, date, month, year, hour, minute, choice1, choice2;
        bool disab_option;

        cin.ignore();
        cout << "Please enter the information below" << endl << "Patient ID : ";
        getline(cin, id);
        cout << "Patient first name : ";
        getline(cin, first_name);
        cout << "Patient last name : ";
        getline(cin, last_name);
        cout << "What is the gender? 1. Male \t 2. Female : ";
        cin >> choice1;
        while (!(choice1 > 0) && (choice1 < 3)) {
            cout << "Invalid answer, please try again" << endl;
            cout << "What is the gender? 1. Male \t 2. Female : ";
            cin >> choice1;
        }
        if (choice1 == 1) {
            gender = "male";
        }
        else {
            gender = "female";
        }

        cout << "Age : ";
        cin >> age;
        cin.ignore();
        cout << "Phone number : ";
        getline(cin, phone);
        cout << "Address Number : ";
        getline(cin, addressNo);
        cout << "Buidling or Street Name : ";
        getline(cin, buildingStreet);
        cout << "Zip Number : ";
        cin >> zip;
        cin.ignore();
        cout << "City : ";
        getline(cin, city);
        cout << "State : ";
        getline(cin, state);
        cout << "Country : ";
        getline(cin, country);
        cout << "Current visit date and time (please follow this format : yyyy MM dd HH mm) : ";
        cin >> year >> month >> date >> hour >> minute;
        cout << "Is the patient disable ? 1. Yes \t 2. No : ";
        cin >> choice2;

        while (!((choice2 > 0) && (choice2 < 3))) {
            cout << "Invalid answer, please try again" << endl;
            cout << "Is the patient disable ? 1. Yes \t 2. No : ";
            cin >> choice2;
        }
        if (choice2 == 1) {
            disab_option = true;
        }
        else {
            disab_option = false;
        }
        Node* nodeptr = createNode(id, first_name, last_name, age, gender, phone, addressNo, buildingStreet, zip, city, state, country, date, month, year, hour, minute, disab_option);
        insertNode(nodeptr);
    }
    //creating new node

    Node* createNode(string id, string first_name, string last_name, int age, string gender, string phone,
        string addressNo, string buildingStreet, int zip, string city, string state, string country,
        int date, int month, int year, int hour, int minute, bool disab_option) {
        address ad = address(addressNo, buildingStreet, zip, city, state, country);
        patient_info pI = patient_info(id, first_name, last_name, age, gender, phone, ad);
        date_time dt = date_time(date, month, year, hour, minute);
        Node* wptr = new Node(pI, dt, disab_option);
        return wptr;
    }

    //insert the new node created from the createNode() function into the linkedlist
    void insertNode(Node* wptr) {
        wptr->next = NULL;
        if (wHead == NULL) {
            wHead = wptr;
            wHead->prev = NULL;
            wTail = wHead;
        }
        else {
            wCurrent = wHead;
            if (wptr->disab_option == true) {
                insertPriority(wptr);
            }
            else {
                while (wCurrent->next != NULL) {
                    wCurrent = wCurrent->next;
                }
                wCurrent->next = wptr;
                wptr->prev = wCurrent;
                wTail = wptr;
            }
        }
        return;
    }

    //fulfilled question 1.2, when there disab_option is true for the new node, then will call this function to add the node infront of the queue,
    //at least in front of those who aren't disable
    void insertPriority(Node* wptr) {
        wCurrent = wHead;
        if (wCurrent->next == NULL) {
            if (wCurrent->disab_option == true) {
                wCurrent->next = wptr;
                wptr->prev = wCurrent;
                wTail = wptr;
                return;
            }
            else {
                wCurrent->prev = wptr;
                wptr->next = wCurrent;
                wHead = wptr;
                return;
            }
        }

        while ((wCurrent->disab_option == true) && (wCurrent->next != NULL)) {
            wCurrent = wCurrent->next;
        }

        if (wCurrent->disab_option == true) {
            wptr->prev = wCurrent;
            wCurrent->next = wptr;
            wTail = wptr; return;
        }

        if (wCurrent->prev == NULL) {
            wptr->prev = NULL;
            wptr->next = wCurrent;
            wCurrent->prev = wptr;
            wHead = wptr; return;
        }
        wptr->next = wCurrent;
        wptr->prev = wCurrent->prev;
        wCurrent->prev = wptr;
        wptr->prev->next = wptr;
        return;
    }

    //this one for question 1.3 and 2.1, displays all the information of a node in the waiting list (need to add into main menu) *ps: do inform me incase u wanna share this function for you tasks
    void displayLinkedList() {
        wCurrent = wHead;
        int i = 0;
        while (wCurrent != NULL) {
            cout << endl << endl;
            cout << ++i << ". Patient ID : " << wCurrent->info.id <<
                "\n Name : " << wCurrent->info.first_name + " " +
                wCurrent->info.last_name << "\n Age : " << wCurrent->info.age
                << "\n Gender : " << wCurrent->info.gender << "\n Phone No : " <<
                wCurrent->info.phone << "\n Address : " << wCurrent->info.pAddress.addressNo +
                ", " + wCurrent->info.pAddress.buildingStreet + ", " + wCurrent->info.pAddress.city +
                ", " + to_string(wCurrent->info.pAddress.zip) + ", " + wCurrent->info.pAddress.state + ", " +
                wCurrent->info.pAddress.country << "\n Disability : " << wCurrent->disab_option <<
                "\n Current date time : " << wCurrent->dateTime.year << "-" << wCurrent->dateTime.month <<
                "-" << wCurrent->dateTime.date << " " << wCurrent->dateTime.hour << ":" << wCurrent->dateTime.minute <<
                endl << endl << "|------------------------------|" << endl;
            wCurrent = wCurrent->next;
        }
        cout << "|______________________END OF RESULT________________________|" << endl;
    }

    //calculate the length of the linked list
    int findLength() {
        int length = 0;
        wCurrent = wHead;
        while (wCurrent != NULL) {
            length++;
            wCurrent = wCurrent->next;
        }
        return length;
    }

    //convert linked list into an array
    Node* convertToArray() {
        int length = findLength();
        int index = 0;
        Node* nodeArrptr = new Node[length];
        wCurrent = wHead;
        while (wCurrent != NULL) {
            *(nodeArrptr + (index++)) = *wCurrent;
            wCurrent = wCurrent->next;
        }
        return nodeArrptr;
    }

    //swaping of node element in the list
    void swap(Node& a, Node& b) {
        Node temp = a;
        a = b;
        b = temp;
    }

    //partitioning the array into smaller array for sorting purpose
    int arrPatition(Node* arrPtr, int low, int high) {
        long long int pivot = (arrPtr + (high))->dateTime.abbr;
        int i = (low - 1);

        for (int x = low; x < high; x++) {
            long long int pointed = (arrPtr + (x))->dateTime.abbr;
            if (pointed < pivot) {
                i++;
                swap(*(arrPtr + i), *(arrPtr + x));
            }
        }
        swap(*(arrPtr + (i + 1)), *(arrPtr + (high)));
        return (i + 1);
    }
    //for quick sorting
    void quickSort(Node* arrPtr, int low, int high) {
        if (low < high) {
            int index = arrPatition(arrPtr, low, high);
            quickSort(arrPtr, low, index - 1);
            quickSort(arrPtr, index + 1, high);
        }
    }
    //display all the array, might change ltr
    void displayArray(Node* arrPtr, int length) {
        for (int i = 0; i < length; i++) {
            cout << endl << endl;
            cout << i + 1 << ". Patient ID : " << (arrPtr + i)->info.id <<
                "\n Name : " << (arrPtr + i)->info.first_name + " " +
                (arrPtr + i)->info.last_name << "\n Age : " << (arrPtr + i)->info.age
                << "\n Gender : " << (arrPtr + i)->info.gender << "\n Phone No : " <<
                (arrPtr + i)->info.phone << "\n Address : " << (arrPtr + i)->info.pAddress.addressNo +
                ", " + (arrPtr + i)->info.pAddress.buildingStreet + ", " + (arrPtr + i)->info.pAddress.city +
                ", " + to_string((arrPtr + i)->info.pAddress.zip) + ", " + (arrPtr + i)->info.pAddress.state + ", " +
                (arrPtr + i)->info.pAddress.country << "\n Disability : " << (arrPtr + i)->disab_option <<
                "\n Current date time : " << (arrPtr + i)->dateTime.year << "-" << (arrPtr + i)->dateTime.month <<
                "-" << (arrPtr + i)->dateTime.date << " " << (arrPtr + i)->dateTime.hour << ":" << (arrPtr + i)->dateTime.minute <<
                endl << endl << "|------------------------------|" << endl;
        }
        cout << "|______________________END OF RESULT________________________|" << endl;
    }
    //this one for question 1.6, sort patients by visit time, (need to add into the main menu)
    void sortByTime() {
        int length = findLength();
        Node* nodeArrPtr = convertToArray();
        quickSort(nodeArrPtr, 0, length - 1);
        displayArray(nodeArrPtr, length);
    }

    void searchPatientById()
    {
        string id;

        wCurrent = wHead;
        cout << "\n\tPlease Enter The Patient's ID: ";
        cin >> id;


        while (wCurrent != NULL)
        {
            if (wCurrent->info.id == id)
            {
                cout << "\n\t================================== PATIENT'S INFO ==================================\n";
                cout << "\tPatient ID        : " << wCurrent->info.id << endl;
                cout << "\tName              : " << wCurrent->info.first_name << " " << wCurrent->info.last_name << endl;
                cout << "\tAge               : " << wCurrent->info.age << endl;
                cout << "\tGender            : " << wCurrent->info.gender << endl;
                cout << "\tPhone Number      : " << wCurrent->info.phone << endl;
                cout << "\tAddress           : " << wCurrent->info.pAddress.addressNo << ", " << wCurrent->info.pAddress.buildingStreet << ", " << wCurrent->info.pAddress.city << ", " << wCurrent->info.pAddress.zip << ", " << wCurrent->info.pAddress.state << ", " << wCurrent->info.pAddress.country << endl;
                cout << "\tDisability        : " << wCurrent->disab_option << endl;
                cout << "\tCurrent date time : " << wCurrent->dateTime.year << "-" << wCurrent->dateTime.month << "-" << wCurrent->dateTime.date << " " << wCurrent->dateTime.hour << ":" << wCurrent->dateTime.minute << endl;
                cout << "\t====================================================================================\n\n";
                break;
            }
            else
            {
                wCurrent = wCurrent->next;
            }
        }

        if (wCurrent == NULL)
            cout << "\n\tThe Patient ID is not existed!\n";
    }

    void searchPatientByFname()
    {
        string fName;

        wCurrent = wHead;
        cout << "\n\tPlease Enter The Patient's First Name: ";
        cin >> fName;


        while (wCurrent != NULL)
        {
            if (wCurrent->info.first_name == fName)
            {
                cout << "\n\t================================== PATIENT'S INFO ==================================\n";
                cout << "\tPatient ID        : " << wCurrent->info.id << endl;
                cout << "\tName              : " << wCurrent->info.first_name << " " << wCurrent->info.last_name << endl;
                cout << "\tAge               : " << wCurrent->info.age << endl;
                cout << "\tGender            : " << wCurrent->info.gender << endl;
                cout << "\tPhone Number      : " << wCurrent->info.phone << endl;
                cout << "\tAddress           : " << wCurrent->info.pAddress.addressNo << ", " << wCurrent->info.pAddress.buildingStreet << ", " << wCurrent->info.pAddress.city << ", " << wCurrent->info.pAddress.zip << ", " << wCurrent->info.pAddress.state << ", " << wCurrent->info.pAddress.country << endl;
                cout << "\tDisability        : " << wCurrent->disab_option << endl;
                cout << "\tCurrent date time : " << wCurrent->dateTime.year << "-" << wCurrent->dateTime.month << "-" << wCurrent->dateTime.date << " " << wCurrent->dateTime.hour << ":" << wCurrent->dateTime.minute << endl;
                cout << "\t====================================================================================\n\n";
                break;
            }
            else
            {
                wCurrent = wCurrent->next;
            }
        }

        if (wCurrent == NULL)
            cout << "\n\tThe Patient's First Name is not existed!\n";
    }

    void searchPatient()
    {
        int choice;

        do {
            system("cls");
            cout << "\n\t1. Patient ID";
            cout << "\n\t2. Patient First Name";
            cout << "\n\tWhat would you like to search on? (1,2): ";
            cin >> choice;

            if (choice == 1)
            {
                searchPatientById();
            }
            else if (choice == 2)
            {
                searchPatientByFname();
            }
            else
            {
                cout << "Wrong Input! Please Try Again!";
                system("pause");
            }

        } while (choice != 1 && choice != 2);
    }

};

class doctors {
public:

};

class Design {
public:
    void mainMenu() {
        system("cls");
        cout << "\n\t--------------------------------------------------\n";
        cout << "\tWELCOME TO PATIENT'S QUEUE BASED MANAGEMENT SYSTEM\n";
        cout << "\t--------------------------------------------------\n\n";
        cout << "\t1. Log In";
        cout << "\n\t2. Exit";
        cout << endl;
    }

    void nurseMenu() {
        system("cls");
        cout << "\n\t--------------------------------------------------\n";
        cout << "\t\tWELCOME TO NURSE MENU PAGE\n";
        cout << "\t--------------------------------------------------\n\n";
        cout << "\t1. Add a new patient on the waiting list";
        cout << "\n\t2. Change the patient order according to the priority on the waiting list";
        cout << "\n\t3. View all patients on the original waiting list";
        cout << "\n\t4. Calling the patient to be treated";
        cout << "\n\t5. Search patient from the waiting list ";
        cout << "\n\t6. Sort the waiting list by patient's current visit time";
        cout << "\n\t7. Log Out";
        cout << endl;
    }

    void doctorMenu() {
        system("cls");
        cout << "\n\t--------------------------------------------------\n";
        cout << "\t\tWELCOME TO DOCTOR MENU PAGE\n";
        cout << "\t--------------------------------------------------\n\n";
        cout << "\t1. View all patients on the original waiting list";
        cout << "\n\t2. Search Specific Patient from the patient's visit history and modify patient records";
        cout << "\n\t3. Sort and display all records from the patient's visit history list";
        cout << "\n\t4. Search patients from the patient's visit history list";
        cout << "\n\t5. Log Out";
        cout << endl;
    }
};

void nurseMenuPage()
{
    Design design;
    nurses nurse;

    int selection;

    do {
        design.nurseMenu();
        cout << "\n\tPlease select one of the option: ";
        cin >> selection;

        switch (selection) {

        case 1:
            system("cls");
            nurse.addNewPatient();
            break;

        case 2:
            system("cls");
            /*nurse.insertPriority(Node * wptr);*/
            break;

        case 3:
            system("cls");
            nurse.displayLinkedList();
            system("pause");
            break;
        case 4:
            cout << "soon";
            break;

        case 5:

            nurse.searchPatient();
            system("pause");
            break;

        case 6:
            cout << "soon";
            break;

        case 7:
            system("cls");
            cout << "\n\tLogging Out...";
            Sleep(1000);
            break;

        default:
            cout << "\nWrong Input! Try Again!\n";
            system("pause");
        }

    } while (selection != 7);


}

void doctorMenuPage()
{
    Design design;
    int selection;

    do {
        design.doctorMenu();
        cout << "\n\tPlease selection one of the option: ";
        cin >> selection;

        switch (selection)
        {
        case 1:
            cout << "soon";
            break;
        case 2:
            cout << "soon";
            break;
        case 3:
            cout << "soon";
            break;
        case 4:
            cout << "soon";
            break;
        case 5:
            system("cls");
            cout << "\n\tLogging Out...";
            Sleep(1000);
            break;
        default:
            cout << "\nWrong Input! Please Try Again!";
            system("pause");
        }

    } while (selection != 5);


}

void login()
{
    string id;
    const char* nursePassword = "nurse999", * doctorPassword = "doctor999", * nurseID = "N007", * doctorID = "D007";
    int index = 0;
    bool access;
    char password[100] = "", c;

    cout << "\n\t--------------------------------------------\n";

    do {
        cout << "\n\tPlease Enter Your ID: ";
        cin >> id;

        cout << "\n\tPlease Enter Your Password: ";

        //using ASCII code for asterik
        //13 is a ASCII value of ENTER character
        while ((c = _getch()) != 13) {
            if (index < 0)
                index = 0;

            //8 is ASCII value of BACKSPACE character 
            if (c == 8) {
                if (index > 0)
                {
                    _putch('\b');
                    _putch(' ');
                    _putch(NULL);
                    _putch('\b');
                    index--;
                    continue;
                }

            }
            password[index++] = c;
            _putch('*');
        }
        password[index] = '\0';

        if (id == nurseID)
        {
            if (!strcmp(password, nursePassword))
            {
                access = true;
                system("cls");
                cout << "\n\tLogging In...";
                Sleep(1000);
                nurseMenuPage();
            }
            else
            {
                access = false;
                index = _putch(NULL);
                cout << "\n\tID or Password are Not Correct! Please Try Again\n\n";
                system("pause");
                cout << endl;
            }

        }

        else if (id == doctorID)
        {
            if (!strcmp(password, doctorPassword))
            {
                access = true;
                system("cls");
                cout << "\n\tLogging In...";
                Sleep(1000);
                doctorMenuPage();

            }
            else {
                access = false;
                index = _putch(NULL);
                cout << "\n\tID or Password are Not Correct! Please Try Again\n\n";
                system("pause");
                cout << endl;
            }

        }
        else
        {
            access = false;
            index = _putch(NULL);
            cout << "\n\tID is Not Correct! Please Try Again\n\n";
            system("pause");
            cout << endl;
        }

    } while (access == false);

}

void mainMenu()
{
    Design design;
    int selection;

    do
    {
        design.mainMenu();
        cout << "\n\tPlease select one of the options (1,2): ";
        cin >> selection;

        if (selection == 1)
        {
            login();
        }
        else if (selection == 2)
        {
            cout << "\n\tBye!";
        }
        else {
            cout << "\n\tWrong Input! Please Try Again!\n";
            system("pause");
        }
    } while (selection != 2);

}

int main() {
    nurses* nurse;
    Node* wNode;
    nurse = NULL;
    wNode = nurse->createNode("P0001", "Eren", "Yeager", 23, "male", "0124353214", "No. 54", "Street A", 13412, "City A", "State A", "A", 13, 8, 2021, 14, 45, true);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0002", "Armin", "Arlelt", 21, "male", "0124453214", "No. 55", "Street A", 13412, "City A", "State A", "A", 13, 9, 2020, 15, 55, false);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0003", "Mikasa", "Ackermann", 20, "female", "0124356765", "No. 56", "Street A", 13412, "City A", "State A", "A", 13, 1, 2019, 14, 45, false);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0004", "Hange", "Zoe", 33, "female", "0198973214", "No. 12", "Street B", 13416, "City B", "State B", "A", 13, 10, 2021, 14, 46, true);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0005", "Jean", "Kirschtein", 26, "male", "0174543214", "No. 65", "Street C", 13416, "City C", "State C", "A", 16, 8, 2021, 15, 45, false);
    nurse->insertNode(wNode);

    mainMenu();
    return 0;
}
