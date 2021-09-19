#include <iostream>
#include <array>
#include <sstream>
#include <conio.h>
#include <string>
#include<windows.h>

using namespace std;
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

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

    Node(patient_info info, date_time dateTime, bool disab_option, string sickness_descp, string doct_name, string med_info) {
        this->info = info;
        this->sickness_descp = sickness_descp;
        this->dateTime = dateTime;
        this->disab_option = disab_option;
        this->doct_name = doct_name;
        this->med_info = med_info;
    }

}*wHead, * wCurrent, * wTail, * hHead, * hCurrent, * hTail;

class nurses {
public:
    string idMaker(int length) {//generate patient id automatically
        string id;
        if (length < 10) {
            id = "P000" + to_string(length);
        }
        else if (length >= 10 && length < 100) {
            id = "P00" + to_string(length);
        }
        else if (length >= 100 && length < 1000) {
            id = "P0" + to_string(length);
        }
        else {
            id = "P" + to_string(length);
        }
        return id;
    }

    string idGenerator() {//making new id
        hCurrent = hHead;
        int length = 1;
        string id = idMaker(length);
        while (hCurrent != NULL) {
            if (id == hCurrent->info.id) {
                ++length;
                id = idMaker(length);
                hCurrent = hHead;
            }
            hCurrent = hCurrent->next;
        }
        wCurrent = wHead;
        while (wCurrent != NULL) {
            if (id == wCurrent->info.id) {
                ++length;
                id = idMaker(length);
                wCurrent = wHead;
            }
            wCurrent = wCurrent->next;
        }
        return id;
    }


    void addNewPatient() { //for question 1.1 adding patient to the waiting list (add into menu)
        string id, first_name, last_name, gender, phone, addressNo, buildingStreet, city, state, country;
        int age, zip, date, month, year, hour, minute, choice1, choice2;
        bool disab_option;

        id = idGenerator();
        cout << "---->New Patient ID : " << id << "<----" << endl << endl;
        cin.ignore();
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

    //transfer waiting list to history list 
    void transferNode(Node* hptr) {
        hptr->next = NULL;
        hCurrent = hHead;
        if (hHead == NULL) {
            hptr->prev = NULL;
            hHead = hptr;
            hTail = hptr;
            return;
        }
        while (hCurrent->next != NULL) {
            hCurrent = hCurrent->next;
        }
        hptr->prev = hCurrent;
        hCurrent->next = hptr;
        hTail = hptr;
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
        int i = 0, choice3;
        while (true) {
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
            cout << "Enter 0 to go back to main menu\nEnter 1 to move to previous page\nEnter 2 to move to next page\nChoice?  ";
            cin >> choice3;
            while (choice3 < 0 || choice3>2) {
                cout << "\nInvalid choice, try again!" << endl;
                cout << "Enter 0 to go back to main menu\nEnter 1 to move to previous page\nEnter 2 to move to next page\nChoice?  ";
                cin >> choice3;
            }
            if (choice3 == 0) {
                break;
            }
            else if (choice3 == 1) {
                if ((i - 1) < 0) {
                    cout << "\nThere is no previous record" << endl;
                }
                else {
                    --i;
                };
            }
            else {
                if ((i + 1) > findLength() - 1) {
                    cout << "\nThere is no next record" << endl;
                }
                else {
                    ++i;
                }
            }
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

    //for 1.5 to search by ID
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
        {
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tPatient ID is not existed!\n";
            SetConsoleTextAttribute(color, 7);
        }
    }

    //for 1.5 to search by name
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
        {
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tPatient's First Name is not existed!\n";
            SetConsoleTextAttribute(color, 7);
        }

    }

    //for 1.5 to select ID or First Name
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
                SetConsoleTextAttribute(color, 4);
                cout << "Wrong Input! Please Try Again!";
                SetConsoleTextAttribute(color, 7);
                system("pause");
            }

        } while (choice != 1 && choice != 2);
    }

    //for 1.4 delete the called patient
    void calledpatient() {
        string id, first_name, last_name, gender, phone, addressNo, buildingStreet, city, state, country;
        int age, zip, date, month, year, hour, minute;
        bool disab_option;
     
        wCurrent = wHead;

        id = wCurrent->info.id;
        first_name = wCurrent->info.first_name;
        last_name = wCurrent->info.last_name;
        age = wCurrent->info.age;
        gender = wCurrent->info.gender;
        phone = wCurrent->info.phone;
        addressNo = wCurrent->info.pAddress.addressNo;
        buildingStreet = wCurrent->info.pAddress.buildingStreet;
        city = wCurrent->info.pAddress.city;
        zip = wCurrent->info.pAddress.zip;
        state = wCurrent->info.pAddress.state;
        country = wCurrent->info.pAddress.country;
        disab_option = wCurrent->disab_option;
        date = wCurrent->dateTime.date;
        year = wCurrent->dateTime.year;
        month = wCurrent->dateTime.month;
        hour = wCurrent->dateTime.hour;
        minute = wCurrent->dateTime.minute;

        cout << endl << endl;
        cout << "The next patient to call is";
        cout << "\n Patient ID : " << wCurrent->info.id <<
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
        cout << "\nCalling this patient";
        Node* n = wHead;
        //copy the data of the next node to head
        wHead = wHead->next; 
        //createNode
        Node* nodeptr = createNode(id, first_name, last_name, age, gender, phone, addressNo, buildingStreet, zip, city, state, country, date, month, year, hour, minute, disab_option);
        // Node* n store into the history list
        transferNode(nodeptr);
        free(n); //free memory
        cout << "\nThe next patient to call is"; //The next head data
        cout << "\n Patient ID : " << wHead->info.id <<
            "\n Name : " << wHead->info.first_name + " " +
            wHead->info.last_name << "\n Age : " << wHead->info.age
            << "\n Gender : " << wHead->info.gender << "\n Phone No : " <<
            wHead->info.phone << "\n Address : " << wHead->info.pAddress.addressNo +
            ", " + wHead->info.pAddress.buildingStreet + ", " + wHead->info.pAddress.city +
            ", " + to_string(wHead->info.pAddress.zip) + ", " + wHead->info.pAddress.state + ", " +
            wHead->info.pAddress.country << "\n Disability : " << wHead->disab_option <<
            "\n Current date time : " << wHead->dateTime.year << "-" << wHead->dateTime.month <<
            "-" << wHead->dateTime.date << " " << wHead->dateTime.hour << ":" << wHead->dateTime.minute <<
            endl << endl << "|------------------------------|" << endl;
    }
};

class doctors {
public:

    Node* createHnode(string id, string first_name, string last_name, int age, string gender, string phone,
        string addressNo, string buildingStreet, int zip, string city, string state, string country,
        int date, int month, int year, int hour, int minute, bool disab_option, string sick_descp, string doct_name, string med_info) {
        address ad = address(addressNo, buildingStreet, zip, city, state, country);
        patient_info pI = patient_info(id, first_name, last_name, age, gender, phone, ad);
        date_time dt = date_time(date, month, year, hour, minute);
        Node* hptr = new Node(pI, dt, disab_option, sick_descp, doct_name, med_info);
        return hptr;
    }

    void insertIntoHList(Node* hptr) {
        hptr->next = NULL;
        hCurrent = hHead;
        if (hHead == NULL) {
            hptr->prev = NULL;
            hHead = hptr;
            hTail = hptr;
            return;
        }
        while (hCurrent->next != NULL) {
            hCurrent = hCurrent->next;
        }
        hptr->prev = hCurrent;
        hCurrent->next = hptr;
        hTail = hptr;
        return;
    }


    void searchAndModify()
    {
        string id, pN, sicknessDecs, mediInfo, dcName, addressNo, buildingStreet, city, state, country;
        int choice, age, AddressNo, zip;
        char selection, selection2, selection3;

        hCurrent = hTail;

        cout << "\n\tPlease Enter The Patient's ID: ";
        cin >> id;


        while (hCurrent != NULL)
        {
            if (hCurrent->info.id == id)
            {
                cout << "\n\t================================== PATIENT'S INFO ==================================\n";
                cout << "\tPatient ID           : " << hCurrent->info.id << endl;
                cout << "\tName                 : " << hCurrent->info.first_name << " " << hCurrent->info.last_name << endl;
                cout << "\tAge                  : " << hCurrent->info.age << endl;
                cout << "\tGender               : " << hCurrent->info.gender << endl;
                cout << "\tPhone Number         : " << hCurrent->info.phone << endl;
                cout << "\tAddress              : " << hCurrent->info.pAddress.addressNo << ", " << hCurrent->info.pAddress.buildingStreet << ", " << hCurrent->info.pAddress.city << ", " << hCurrent->info.pAddress.zip << ", " << hCurrent->info.pAddress.state << ", " << hCurrent->info.pAddress.country << endl;
                cout << "\tDisability           : " << hCurrent->disab_option << endl;
                cout << "\tCurrent date time    : " << hCurrent->dateTime.year << "-" << hCurrent->dateTime.month << "-" << hCurrent->dateTime.date << " " << hCurrent->dateTime.hour << ":" << hCurrent->dateTime.minute << endl;
                cout << "\tSickness Description : " << hCurrent->sickness_descp << endl;
                cout << "\tMedicine Information : " << hCurrent->med_info << endl;
                cout << "\tDoctor Name          : " << hCurrent->doct_name << endl;
                cout << "\t====================================================================================\n\n";

                do {
                    cout << "\tWould you like to modify " << hCurrent->info.first_name << "'s infomation? (Y/N): ";
                    cin >> selection;

                    if (toupper(selection) == 'Y')
                    {
                        do {
                            do {
                                cout << "\n\t-----------------------------------------------------------------------------------\n\n";
                                cout << "\t1. Age \n";
                                cout << "\t2. Phone Number\n";
                                cout << "\t3. Address\n";
                                cout << "\t4. Sickness Desciption\n";
                                cout << "\t5. Medicine Information\n";
                                cout << "\t6. Doctor Name\n";
                                cout << "\tWhich would you like to modify? (1-6): ";
                                cin >> choice;

                                switch (choice)
                                {
                                case 1:
                                    cout << "\n\tCurrent Age  : " << hCurrent->info.age;
                                    cout << "\n\tUpdated Age  : ";
                                    cin >> age;

                                    do {
                                        cout << "\n\tConfirm to update age? (Y/N): ";
                                        cin >> selection2;

                                        if (toupper(selection2) == 'Y')
                                        {
                                            hCurrent->info.age = age;
                                        }
                                        else if (toupper(selection2) == 'N')
                                        {
                                            cout << "\n\tCancel Update...";
                                        }
                                        else
                                        {
                                            SetConsoleTextAttribute(color, 4);
                                            cout << "\n\tWrong Input! Please try again!";
                                            SetConsoleTextAttribute(color, 7);
                                        }
                                    } while (toupper(selection2) != 'Y' && toupper(selection2) != 'N');

                                    break;

                                case 2:
                                    cout << "\n\tCurrent Phone Number  : " << hCurrent->info.phone;
                                    cout << "\n\tUpdated Phone Number  : ";
                                    cin >> pN;

                                    do {
                                        cout << "\n\tConfirm to update phone number? (Y/N): ";
                                        cin >> selection2;

                                        if (toupper(selection2) == 'Y')
                                        {
                                            hCurrent->info.phone = pN;
                                        }
                                        else if (toupper(selection2) == 'N')
                                        {
                                            cout << "\n\tCancel Update...";
                                        }
                                        else
                                        {
                                            SetConsoleTextAttribute(color, 4);
                                            cout << "\n\tWrong Input! Please try again!";
                                            SetConsoleTextAttribute(color, 7);
                                        }
                                    } while (toupper(selection2) != 'Y' && toupper(selection2) != 'N');

                                    break;

                                case 3:
                                    cout << "\n\t Current Address  : " << hCurrent->info.pAddress.addressNo << ", " << hCurrent->info.pAddress.buildingStreet << ", " << hCurrent->info.pAddress.city << ", " << hCurrent->info.pAddress.zip << ", " << hCurrent->info.pAddress.state << ", " << hCurrent->info.pAddress.country;
                                    cout << "\n\n\tUpdated Address ";
                                    cin.ignore();
                                    cout << "\n\tAddress Number : ";
                                    getline(cin, addressNo);
                                    cout << "\tBuidling or Street Name : ";
                                    getline(cin, buildingStreet);
                                    cout << "\tZip Number : ";
                                    cin >> zip;
                                    cin.ignore();
                                    cout << "\tCity : ";
                                    getline(cin, city);
                                    cout << "\tState : ";
                                    getline(cin, state);
                                    cout << "\tCountry : ";
                                    getline(cin, country);

                                    do {
                                        cout << "\n\tConfirm to update address? (Y/N): ";
                                        cin >> selection2;

                                        if (toupper(selection2) == 'Y')
                                        {
                                            hCurrent->info.pAddress.addressNo = addressNo;
                                            hCurrent->info.pAddress.buildingStreet = buildingStreet;
                                            hCurrent->info.pAddress.city = city;
                                            hCurrent->info.pAddress.zip = zip;
                                            hCurrent->info.pAddress.state = state;
                                            hCurrent->info.pAddress.country = country;
                                        }
                                        else if (toupper(selection2) == 'N')
                                        {
                                            cout << "\n\tCancel Update...";
                                        }
                                        else
                                        {
                                            SetConsoleTextAttribute(color, 4);
                                            cout << "\n\tWrong Input! Please try again!";
                                            SetConsoleTextAttribute(color, 7);
                                        }
                                    } while (toupper(selection2) != 'Y' && toupper(selection2) != 'N');


                                    break;

                                case 4:
                                    cin.ignore();
                                    cout << "\n\tCurrent Sickness  : " << hCurrent->sickness_descp;
                                    cout << "\n\tUpdated Sickness  : ";
                                    getline(cin, sicknessDecs);

                                    do {
                                        cout << "\n\tConfirm to update sickness? (Y/N): ";
                                        cin >> selection2;

                                        if (toupper(selection2) == 'Y')
                                        {
                                            hCurrent->sickness_descp = sicknessDecs;
                                        }
                                        else if (toupper(selection2) == 'N')
                                        {
                                            cout << "\n\tCancel Update...";
                                        }
                                        else
                                        {
                                            SetConsoleTextAttribute(color, 4);
                                            cout << "\n\tWrong Input! Please try again!";
                                            SetConsoleTextAttribute(color, 7);
                                        }
                                    } while (toupper(selection2) != 'Y' && toupper(selection2) != 'N');

                                    break;

                                case 5:
                                    cin.ignore();
                                    cout << "\n\tCurrent Medicine Information  : " << hCurrent->med_info;
                                    cout << "\n\tUpdated Medicine Information  : ";
                                    getline(cin, mediInfo);

                                    do {
                                        cout << "\n\tConfirm to update medicine information? (Y/N): ";
                                        cin >> selection2;

                                        if (toupper(selection2) == 'Y')
                                        {
                                            hCurrent->med_info = mediInfo;
                                        }
                                        else if (toupper(selection2) == 'N')
                                        {
                                            cout << "\n\tCancel Update...";
                                        }
                                        else
                                        {
                                            SetConsoleTextAttribute(color, 4);
                                            cout << "\n\tWrong Input! Please try again!";
                                            SetConsoleTextAttribute(color, 7);
                                        }
                                    } while (toupper(selection2) != 'Y' && toupper(selection2) != 'N');

                                    break;

                                case 6:
                                    cin.ignore();
                                    cout << "\n\tCurrent Doctor Name  : " << hCurrent->doct_name;
                                    cout << "\n\tUpdated Doctor Name  : ";
                                    getline(cin, dcName);

                                    do {
                                        cout << "\n\tConfirm to update doctor name? (Y/N): ";
                                        cin >> selection2;

                                        if (toupper(selection2) == 'Y')
                                        {
                                            hCurrent->doct_name = dcName;
                                        }
                                        else if (toupper(selection2) == 'N')
                                        {
                                            cout << "\n\tCancel Update...";
                                        }
                                        else
                                        {
                                            SetConsoleTextAttribute(color, 4);
                                            cout << "\n\tWrong Input! Please try again!";
                                            SetConsoleTextAttribute(color, 7);
                                        }
                                    } while (toupper(selection2) != 'Y' && toupper(selection2) != 'N');

                                    break;

                                default:
                                    SetConsoleTextAttribute(color, 4);
                                    cout << "\n\tWrong Input!";
                                    SetConsoleTextAttribute(color, 7);
                                }

                            } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);

                            do {
                                cout << "\tWould you like to modify others? (Y/N): ";
                                cin >> selection3;

                                if (toupper(selection3) == 'N')
                                {
                                    system("cls");
                                    cout << "\n\tUpdating...";
                                    Sleep(1000);

                                    system("cls");
                                    cout << "\n\t=============================UPDATED PATIENT'S INFO ===============================\n";
                                    cout << "\tPatient ID           : " << hCurrent->info.id << endl;
                                    cout << "\tName                 : " << hCurrent->info.first_name << " " << hCurrent->info.last_name << endl;
                                    cout << "\tAge                  : " << hCurrent->info.age << endl;
                                    cout << "\tGender               : " << hCurrent->info.gender << endl;
                                    cout << "\tPhone Number         : " << hCurrent->info.phone << endl;
                                    cout << "\tAddress              : " << hCurrent->info.pAddress.addressNo << ", " << hCurrent->info.pAddress.buildingStreet << ", " << hCurrent->info.pAddress.city << ", " << hCurrent->info.pAddress.zip << ", " << hCurrent->info.pAddress.state << ", " << hCurrent->info.pAddress.country << endl;
                                    cout << "\tDisability           : " << hCurrent->disab_option << endl;
                                    cout << "\tCurrent date time    : " << hCurrent->dateTime.year << "-" << hCurrent->dateTime.month << "-" << hCurrent->dateTime.date << " " << hCurrent->dateTime.hour << ":" << hCurrent->dateTime.minute << endl;
                                    cout << "\tSickness Description : " << hCurrent->sickness_descp << endl;
                                    cout << "\tMedicine Information : " << hCurrent->med_info << endl;
                                    cout << "\tDoctor Name          : " << hCurrent->doct_name << endl;
                                    cout << "\t====================================================================================\n\n";
                                    cout << "\t" << hCurrent->info.first_name << "'s information has been updated!\n\n";
                                }
                                else if (toupper(selection3) != 'Y' && toupper(selection3) != 'N')
                                {
                                    SetConsoleTextAttribute(color, 4);
                                    cout << "\n\tWrong Input! Please try Again!";
                                    SetConsoleTextAttribute(color, 7);
                                }
                            } while (toupper(selection3) != 'Y' && toupper(selection3) != 'N');

                        } while (toupper(selection3) == 'Y');

                    }
                    else if (toupper(selection) != 'N' && toupper(selection) != 'Y')
                    {
                        SetConsoleTextAttribute(color, 4);
                        cout << "\n\tWrong Input! Please Try Again!\n";
                        SetConsoleTextAttribute(color, 7);
                    }

                } while (toupper(selection) != 'N' && toupper(selection) != 'Y');

                break;
            }
            else
            {
                hCurrent = hCurrent->prev;
            }
        }

        if (hCurrent == NULL)
        {
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tThe Patient ID is not existed!\n";
            SetConsoleTextAttribute(color, 7);
        }
    }

    //calculate the length of the linked list
    int findLength() {
        int length = 0;
        hCurrent = hHead;
        while (hCurrent != NULL) {
            length++;
            hCurrent = hCurrent->next;
        }
        return length;
    }

    //convert linked list into an array
    Node* convertToArray() {
        int length = findLength();
        int index = 0;
        Node* nodeArrptr = new Node[length];
        hCurrent = hHead;
        while (hCurrent != NULL) {
            *(nodeArrptr + (index++)) = *hCurrent;
            hCurrent = hCurrent->next;
        }
        return nodeArrptr;
    }

    //swaping of node element in the list
    void swap(Node& a, Node& b) {
        Node change = a;
        a = b;
        b = change;
    }

    int arrSeperationFname(Node* arrPtr, int i, int j) {
        string low = (arrPtr + (j))->info.first_name;
        int x = (i - 1);

        for (int y = i; y < j; y++) {
            string high = (arrPtr + (y))->info.first_name;
            if (high < low) {
                x++;
                swap(*(arrPtr + x), *(arrPtr + y));
            }
        }
        swap(*(arrPtr + (x + 1)), *(arrPtr + (j)));
        return (x + 1);
    }
    //for quick sort
    void quickSortFname(Node* arrPtr, int low, int high) {
        if (low < high) {
            int index = arrSeperationFname(arrPtr, low, high);
            quickSortFname(arrPtr, low, index - 1);
            quickSortFname(arrPtr, index + 1, high);
        }
    }
    // The display array is the waiting list should be history list, needed to change
    void displayArray(Node* arrPtr, int length) {
        int i = 0, choice3;
        while (true) {
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
            cout << "Enter 0 to go back to main menu\nEnter 1 to move to previous page\nEnter 2 to move to next page\nChoice?  ";
            cin >> choice3;
            while (choice3 < 0 || choice3>2) {
                cout << "\nInvalid choice, try again!" << endl;
                cout << "Enter 0 to go back to main menu\nEnter 1 to move to previous page\nEnter 2 to move to next page\nChoice?  ";
                cin >> choice3;
            }
            if (choice3 == 0) {
                break;
            }
            else if (choice3 == 1) {
                if ((i - 1) < 0) {
                    cout << "\nThere is no previous record" << endl;
                }
                else {
                    --i;
                };
            }
            else {
                if ((i + 1) > findLength() - 1) {
                    cout << "\nThere is no next record" << endl;
                }
                else {
                    ++i;
                }
            }
        }
        cout << "|______________________END OF RESULT________________________|" << endl;
    }

    void sortByFname() {
        int length = findLength();
        Node* nodeArrPtr = convertToArray();
        quickSortFname(nodeArrPtr, 0, length - 1);
        displayArray(nodeArrPtr, length);
    }

    int arrSeperationLname(Node* arrPtr, int i, int j) {
        string low = (arrPtr + (j))->info.last_name;
        int x = (i - 1);

        for (int y = i; y < j; y++) {
            string high = (arrPtr + (y))->info.last_name;
            if (high < low) {
                x++;
                swap(*(arrPtr + x), *(arrPtr + y));
            }
        }
        swap(*(arrPtr + (x + 1)), *(arrPtr + (j)));
        return (x + 1);
    }

    // The display array is the waiting list should be history list, needed to change
    void sortByLname() {
        int length = findLength();
        Node* nodeArrPtr = convertToArray();
        quickSortLname(nodeArrPtr, 0, length - 1);
        displayArray(nodeArrPtr, length);
    }

    void quickSortLname(Node* arrPtr, int low, int high) {
        if (low < high) {
            int index = arrSeperationLname(arrPtr, low, high);
            quickSortLname(arrPtr, low, index - 1);
            quickSortLname(arrPtr, index + 1, high);
        }
    }

    //2.3 sort menu 
    void sortMenu() {
        int choice;

        do {
            system("cls");
            cout << "\n\t======= PATIENT'S INFO ========";
            cout << "\n\t1. First Name";
            cout << "\n\t2. Last Name";
            cout << "\n\tWhat would you like to sort by? (1,2): ";
            cin >> choice;

            if (choice == 1)
            {
                sortByFname();
            }
            else if (choice == 2)
            {
                sortByLname();
            }
            else
            {
                SetConsoleTextAttribute(color, 4);
                cout << "Wrong Input! Please Try Again!";
                SetConsoleTextAttribute(color, 7);
                system("pause");
            }

        } while (choice != 1 && choice != 2);
    }
    //2.4 Search patient history list using sickness description
    void searchPatientbySickDesc() {
        string sicknessDecs;

        hCurrent = hHead;
        cout << "Please enter the patient sickness description: ";
        cin >> sicknessDecs;

        if (hCurrent->sickness_descp == sicknessDecs)
        {
            cout << "\n\t================================== PATIENT'S INFO ==================================\n";
            cout << "\tPatient ID           : " << hCurrent->info.id << endl;
            cout << "\tName                 : " << hCurrent->info.first_name << " " << hCurrent->info.last_name << endl;
            cout << "\tAge                  : " << hCurrent->info.age << endl;
            cout << "\tGender               : " << hCurrent->info.gender << endl;
            cout << "\tPhone Number         : " << hCurrent->info.phone << endl;
            cout << "\tAddress              : " << hCurrent->info.pAddress.addressNo << ", " << hCurrent->info.pAddress.buildingStreet << ", " << hCurrent->info.pAddress.city << ", " << hCurrent->info.pAddress.zip << ", " << hCurrent->info.pAddress.state << ", " << hCurrent->info.pAddress.country << endl;
            cout << "\tDisability           : " << hCurrent->disab_option << endl;
            cout << "\tCurrent date time    : " << hCurrent->dateTime.year << "-" << hCurrent->dateTime.month << "-" << hCurrent->dateTime.date << " " << hCurrent->dateTime.hour << ":" << hCurrent->dateTime.minute << endl;
            cout << "\tSickness Description : " << hCurrent->sickness_descp << endl;
            cout << "\tMedicine Information : " << hCurrent->med_info << endl;
            cout << "\tDoctor Name          : " << hCurrent->doct_name << endl;
            cout << "\t====================================================================================\n\n";
        }
        if (wCurrent == NULL)
        {
            SetConsoleTextAttribute(color, 4);
            cout << "\n\t Sickness Description is not existed!\n";
            SetConsoleTextAttribute(color, 7);
        }
    }

    //2.4 Search patient history list using first name
    void searchPatientbyFirstName() {
        string fname;

        hCurrent = hHead;
        cout << "Please enter the patient first name: ";
        cin >> fname;

        if (hCurrent->info.first_name == fname)
        {
            cout << "\n\t================================== PATIENT'S INFO ==================================\n";
            cout << "\tPatient ID           : " << hCurrent->info.id << endl;
            cout << "\tName                 : " << hCurrent->info.first_name << " " << hCurrent->info.last_name << endl;
            cout << "\tAge                  : " << hCurrent->info.age << endl;
            cout << "\tGender               : " << hCurrent->info.gender << endl;
            cout << "\tPhone Number         : " << hCurrent->info.phone << endl;
            cout << "\tAddress              : " << hCurrent->info.pAddress.addressNo << ", " << hCurrent->info.pAddress.buildingStreet << ", " << hCurrent->info.pAddress.city << ", " << hCurrent->info.pAddress.zip << ", " << hCurrent->info.pAddress.state << ", " << hCurrent->info.pAddress.country << endl;
            cout << "\tDisability           : " << hCurrent->disab_option << endl;
            cout << "\tCurrent date time    : " << hCurrent->dateTime.year << "-" << hCurrent->dateTime.month << "-" << hCurrent->dateTime.date << " " << hCurrent->dateTime.hour << ":" << hCurrent->dateTime.minute << endl;
            cout << "\tSickness Description : " << hCurrent->sickness_descp << endl;
            cout << "\tMedicine Information : " << hCurrent->med_info << endl;
            cout << "\tDoctor Name          : " << hCurrent->doct_name << endl;
            cout << "\t====================================================================================\n\n";
        }
        if (hCurrent == NULL)
        {
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tPatient's First Name is not existed!\n";
            SetConsoleTextAttribute(color, 7);
        }
    }

    //for 2.4 to select Sick Desc or First Name (menu)
    void searchPatientHis()
    {
        int choice;

        do {
            system("cls");
            cout << "\n\t1. Sickness Description";
            cout << "\n\t2. Patient First Name";
            cout << "\n\tWhat would you like to search on? (1,2): ";
            cin >> choice;

            if (choice == 1)
            {
                searchPatientbySickDesc();
            }
            else if (choice == 2)
            {
                searchPatientbyFirstName();
            }
            else
            {
                SetConsoleTextAttribute(color, 4);
                cout << "Wrong Input! Please Try Again!";
                SetConsoleTextAttribute(color, 7);
                system("pause");
            }

        } while (choice != 1 && choice != 2);
    }
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
            system("pause");
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
            system("cls");
            nurse.calledpatient();
            system("pause");
            break;

        case 5:

            nurse.searchPatient();
            system("pause");
            break;

        case 6:
            system("cls");
            nurse.sortByTime();
            system("pause");
            break;

        case 7:
            system("cls");
            cout << "\n\tLogging Out...";
            Sleep(1000);
            break;

        default:
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tWrong Input! Try Again!\n";
            SetConsoleTextAttribute(color, 7);
            system("pause");
        }

    } while (selection != 7);


}

void doctorMenuPage()
{
    nurses nurse;
    doctors doctor;
    Design design;
    int selection;

    do {
        design.doctorMenu();
        cout << "\n\tPlease selection one of the option: ";
        cin >> selection;

        switch (selection)
        {
        case 1:
            system("cls");
            nurse.displayLinkedList();
            system("pause");
            break;
        case 2:
            system("cls");
            doctor.searchAndModify();
            system("pause");
            break;
        case 3:
            system("cls");
            doctor.sortMenu();
            system("pause");
            break;
        case 4:
            system("cls");
            doctor.searchPatientHis();
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "\n\tLogging Out...";
            Sleep(1000);
            break;
        default:
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tWrong Input! Please Try Again!\n";
            SetConsoleTextAttribute(color, 7);
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
                SetConsoleTextAttribute(color, 4);
                cout << "\n\tID or Password are Not Correct! Please Try Again\n\n";
                SetConsoleTextAttribute(color, 7);
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
                SetConsoleTextAttribute(color, 4);
                cout << "\n\tID or Password are Not Correct! Please Try Again\n\n";
                SetConsoleTextAttribute(color, 7);
                system("pause");
                cout << endl;
            }

        }
        else
        {
            access = false;
            index = _putch(NULL);
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tID is Not Correct! Please Try Again\n\n";
            SetConsoleTextAttribute(color, 7);
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
            SetConsoleTextAttribute(color, 4);
            cout << "\n\tWrong Input! Please Try Again!\n";
            SetConsoleTextAttribute(color, 7);
            system("pause");
        }
    } while (selection != 2);

}

int main() {
    nurses* nurse = NULL;
    doctors* doctor = NULL;
    Node* wNode = NULL, * hNode = NULL;
    wNode = nurse->createNode("P0006", "Eren", "Yeager", 23, "male", "0124353214", "No. 54", "Street A", 13412, "City A", "State A", "A", 22, 8, 2021, 14, 45, true);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0007", "Armin", "Arlelt", 21, "male", "0124453214", "No. 55", "Street A", 13412, "City A", "State A", "A", 22, 8, 2021, 14, 55, false);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0008", "Mikasa", "Ackerman", 20, "female", "0124356765", "No. 56", "Street A", 13412, "City A", "State A", "A", 22, 8, 2021, 14, 56, false);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0009", "Hange", "Zoe", 33, "female", "0198973214", "No. 12", "Street B", 13416, "City B", "State B", "A", 22, 8, 2021, 15, 6, true);
    nurse->insertNode(wNode);
    wNode = nurse->createNode("P0010", "Jean", "Kirschtein", 26, "male", "0174543214", "No. 65", "Street C", 13416, "City C", "State C", "A", 22, 8, 2021, 15, 10, false);
    nurse->insertNode(wNode);
    hNode = doctor->createHnode("P0001", "Levi", "Arkerman", 33, "male", "0124353214", "No. 59", "Street A", 13412, "City A", "State A", "A", 21, 8, 2021, 11, 34, true, "Allergies", "Doctor Chong", "Allergy shots");
    doctor->insertIntoHList(hNode);
    hNode = doctor->createHnode("P0002", "Erwin", "Smith", 50, "male", "0124453214", "No. 23", "Street A", 13412, "City A", "State A", "A", 21, 8, 2021, 12, 35, false, "Cold and Flu", "Doctor Chong", "Anti-flu medicines");
    doctor->insertIntoHList(hNode);
    hNode = doctor->createHnode("P0003", "Reiner", "Braun", 32, "male", "0124356765", "No. 43", "Street A", 13412, "City A", "State A", "A", 21, 8, 2021, 12, 36, false, "Cough", "Doctor Chong", "cough suppressant");
    doctor->insertIntoHList(hNode);
    hNode = doctor->createHnode("P0004", "Connie", "Springer", 20, "male", "0198973214", "No. 56", "Street B", 13416, "City B", "State B", "A", 21, 8, 2021, 12, 46, true, "Sore Throat", "Doctor Chong", "Antibiotics");
    doctor->insertIntoHList(hNode);
    hNode = doctor->createHnode("P0005", "Historia", "Reiss", 19, "female", "0174543214", "No. 21", "Street C", 13416, "City C", "State C", "A", 21, 8, 2021, 13, 45, false, "Fever", "Doctor Chong", "Aspirin");
    doctor->insertIntoHList(hNode);
    hNode = doctor->createHnode("P0001", "Levi", "Arkerman", 33, "male", "0124353214", "No. 59", "Street A", 13412, "City A", "State A", "A", 21, 8, 2021, 14, 45, true, "Allergies", "Doctor Chong", "Allergy shots");
    doctor->insertIntoHList(hNode);
    mainMenu();
    return 0;
}

