#include <iostream>
#include <array>
#include <sstream>

using namespace std;


struct address{
    string addressNo;
    string buildingStreet;
    int zip;
    string city;
    string state;
    string country;

    address(){};
    address(string addressNo, string buildingStreet, int zip, string city, string state, string country){
        this->addressNo= addressNo;
        this->buildingStreet = buildingStreet;
        this->zip = zip;
        this->city = city;
        this->state = state;
        this->country = country;
    }
};

struct patient_info{
    string id;
    string first_name;
    string last_name;
    int age;
    string gender;
    string phone;
    address pAddress;

    patient_info(){};
    patient_info(string id, string first_name, string last_name, int age, string gender, string phone,address pAddress){
        this->id = id;
        this->first_name = first_name;
        this->last_name = last_name;
        this->age = age;
        this->gender = gender;
        this->phone = phone;
        this->pAddress = pAddress;
    }
};

struct date_time{
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
    date_time(){};
    date_time(int date, int month, int year, int hour, int minute){
        this->date=date;
        this->month=month;
        this->year=year;
        this->hour=hour;
        this->minute=minute;
        abbr = year*(y)+month*(m)+date*(d)+hour*(100)+minute;
    }
};

struct Node{
    patient_info info;
    string sickness_descp;
    date_time dateTime;
    bool disab_option;
    string doct_name;
    string med_info;
    struct Node *prev;
    struct Node *next;
    
    Node(){};
    Node(patient_info info, date_time dateTime, bool disab_option){
         this->info = info;
         this->sickness_descp = "";
         this->dateTime = dateTime;
         this->disab_option = disab_option;
         this->doct_name = "";
         this->med_info = "";
     }

}*wHead , * wCurrent, * wTail, *hHead , *hCurrent, * hTail;

class nurses{
    public:

    void addNewPatient(){ //for question 1.1 adding patient to the waiting list (add into menu)
        string id, first_name, last_name, gender, phone, addressNo, buildingStreet, city, state, country;
        int age, zip, date,month, year, hour, minute; bool disab_option;
        cout << "Please enter the information below" << endl << "Patient ID : ";
        getline(cin, id);
        cout << "Patient first name : ";
        getline(cin, first_name);
        cout << "Patient last name : ";
        getline(cin, last_name);
        cout << "What is the gender? 1. Male \t 2. Female : ";
        int choice1;
        cin >> choice1;
        while(!(choice1>0)&&(choice1<3)){
            cout << "Invalid answer, please try again" << endl;
            cout << "What is the gender? 1. Male \t 2. Female : ";
            cin >> choice1;
        }
        if (choice1==1){
            gender = "male";
        }else{
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
        getline(cin,city);
        cout << "State : ";
        getline(cin, state);
        cout << "Country : ";
        getline(cin, country);
        cout << "Current visit date and time (please follow this format : yyyy MM dd HH mm) : ";
        cin >> year >> month >> date >> hour >> minute;
        cout << "Is the patient disable ? 1. Yes \t 2. No : ";
        int choice2;
        cin >> choice2; 
        while(!((choice2>0)&&(choice2<3))){
            cout << "Invalid answer, please try again" << endl;
            cout << "Is the patient disable ? 1. Yes \t 2. No : ";
            cin >> choice2;
        }
        if(choice2==1){
            disab_option = true;
        }else{
            disab_option = false;
        }
        Node * nodeptr = createNode(id, first_name, last_name, age, gender, phone, addressNo, buildingStreet, zip, city, state, country, date, month, year, hour, minute, disab_option);
        insertNode(nodeptr);
    }
    //creating new node
    Node * createNode(string id, string first_name, string last_name, int age, string gender, string phone,
    string addressNo, string buildingStreet, int zip, string city, string state, string country,
    int date, int month, int year, int hour, int minute, bool disab_option){
        address ad = address(addressNo, buildingStreet, zip, city, state, country);
        patient_info pI = patient_info(id, first_name, last_name, age, gender, phone, ad);
        date_time dt = date_time(date, month, year, hour, minute);
        Node* wptr = new Node(pI, dt, disab_option);
        return wptr;
    }
    //insert the new node created from the createNode() function into the linkedlist
    void insertNode(Node * wptr){
        wptr->next = NULL;
        if(wHead == NULL){
            wHead = wptr;
            wHead->prev = NULL;
            wTail = wHead;
        }else{
            wCurrent = wHead;
            if(wptr->disab_option == true){
                insertPriority(wptr);
            }else{
                while(wCurrent->next!=NULL){
                    wCurrent = wCurrent ->next;
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
    void insertPriority(Node * wptr){
        wCurrent = wHead;
        if(wCurrent->next==NULL){
            if(wCurrent->disab_option == true){
                wCurrent->next = wptr;
                wptr->prev = wCurrent;
                wTail = wptr;
                return;
            }else{
                wCurrent->prev = wptr;
                wptr->next = wCurrent;
                wHead = wptr;
                return;
            }
        }
        while((wCurrent->disab_option==true)&&(wCurrent->next!=NULL)){
            wCurrent = wCurrent->next;
        }
        if(wCurrent->disab_option==true){
            wptr->prev = wCurrent;
            wCurrent->next = wptr;
            wTail = wptr;return;
        }
        if(wCurrent->prev==NULL){
            wptr->prev = NULL;
            wptr->next=wCurrent;
            wCurrent->prev = wptr;
            wHead = wptr;return;
        }
        wptr->next = wCurrent;
        wptr->prev = wCurrent->prev;
        wCurrent->prev = wptr;
        wptr->prev->next = wptr;
        return;
    } 

    //this one for question 1.3 and 2.1, displays all the information of a node in the waiting list (need to add into main menu) *ps: do inform me incase u wanna share this function for you tasks
    void displayLinkedList(){
        wCurrent = wHead;
        int i=0;
        while(wCurrent!=NULL){
            cout << endl << endl;
            cout << ++i << ". Patient ID : "<< wCurrent->info.id <<
            "\n Name : " << wCurrent->info.first_name + " " +
            wCurrent->info.last_name << "\n Age : " << wCurrent->info.age 
            << "\n Gender : "<< wCurrent->info.gender << "\n Phone No : "<<
            wCurrent->info.phone << "\n Address : " << wCurrent->info.pAddress.addressNo +
            ", " + wCurrent->info.pAddress.buildingStreet + ", " + wCurrent->info.pAddress.city+
            ", " + to_string(wCurrent->info.pAddress.zip) + ", "+ wCurrent->info.pAddress.state+", "+ 
            wCurrent->info.pAddress.country << "\n Disability : " << wCurrent->disab_option <<
            "\n Current date time : " << wCurrent->dateTime.year <<"-"<<wCurrent->dateTime.month<<
            "-"<<wCurrent->dateTime.date<<" "<<wCurrent->dateTime.hour<<":"<<wCurrent->dateTime.minute<<
            endl<<endl<<"|------------------------------|" <<endl;    
            wCurrent=wCurrent->next;    
            }
            cout << "|______________________END OF RESULT________________________|"<<endl;
    }

    //calculate the length of the linked list
    int findLength(){
        int length=0;
        wCurrent = wHead;
        while(wCurrent!=NULL){
            length++;
            wCurrent = wCurrent->next;
        }
        return length;
    }

    //convert linked list into an array
    Node * convertToArray(){
        int length = findLength();
        int index=0;
        Node * nodeArrptr = new Node[length];
        wCurrent = wHead;
        while(wCurrent!=NULL){
            *(nodeArrptr+(index++)) = *wCurrent;
            wCurrent = wCurrent->next;
        }
        return nodeArrptr;
    }

    //swaping of node element in the list
    void swap(Node &a, Node &b){
        Node temp = a;
        a = b;
        b = temp;
    }

    //partitioning the array into smaller array for sorting purpose
    int arrPatition(Node * arrPtr, int low, int high){
        long long int pivot = (arrPtr+(high))->dateTime.abbr;
        int i = (low-1);

        for(int x=low; x<high; x++){
            long long int pointed = (arrPtr+(x))->dateTime.abbr;
            if(pointed<pivot){
                i++;
                swap(*(arrPtr+i), *(arrPtr+x));
            }
        }
        swap(*(arrPtr+(i+1)), *(arrPtr+(high)));
        return (i+1);
    } 
    //for quick sorting
    void quickSort(Node * arrPtr, int low, int high){
        if(low<high){
            int index = arrPatition(arrPtr, low, high);
            quickSort(arrPtr, low, index-1);
            quickSort(arrPtr, index+1, high);
        }
    }
    //display all the array, might change ltr
    void displayArray(Node * arrPtr, int length){
        for(int i=0; i<length; i++){
            cout << endl << endl;
            cout << i+1 << ". Patient ID : "<< (arrPtr+i)->info.id <<
            "\n Name : " << (arrPtr+i)->info.first_name + " " +
            (arrPtr+i)->info.last_name << "\n Age : " << (arrPtr+i)->info.age 
            << "\n Gender : "<< (arrPtr+i)->info.gender << "\n Phone No : "<<
            (arrPtr+i)->info.phone << "\n Address : " << (arrPtr+i)->info.pAddress.addressNo +
            ", " + (arrPtr+i)->info.pAddress.buildingStreet + ", " + (arrPtr+i)->info.pAddress.city+
            ", " + to_string((arrPtr+i)->info.pAddress.zip) + ", "+ (arrPtr+i)->info.pAddress.state+", "+ 
            (arrPtr+i)->info.pAddress.country << "\n Disability : " << (arrPtr+i)->disab_option <<
            "\n Current date time : " << (arrPtr+i)->dateTime.year <<"-"<<(arrPtr+i)->dateTime.month<<
            "-"<<(arrPtr+i)->dateTime.date<<" "<<(arrPtr+i)->dateTime.hour<<":"<<(arrPtr+i)->dateTime.minute<<
            endl<<endl<<"|------------------------------|" <<endl;        
            }
            cout << "|______________________END OF RESULT________________________|"<<endl;
    }
    //this one for question 1.6, sort patients by visit time, (need to add into the main menu)
    void sortByTime(){
        int length  = findLength();
        Node * nodeArrPtr = convertToArray();
        quickSort(nodeArrPtr, 0, length-1);
        displayArray(nodeArrPtr, length);
    }

};

class doctors{
    public:

};

int main(){
   nurses * nurse;
   Node * wNode;
   wNode=nurse->createNode("P0001", "Eren", "Yeager", 23, "male", "0124353214", "No. 54", "Street A", 13412,"City A", "State A", "A", 13, 8, 2021, 14, 45, true);
   nurse->insertNode(wNode);
   wNode=nurse->createNode("P0002", "Armin", "Arlelt", 21, "male", "0124453214", "No. 55", "Street A", 13412,"City A", "State A", "A", 13, 9, 2020, 15, 55, false);
   nurse->insertNode(wNode);
   wNode=nurse->createNode("P0003", "Mikasa", "Ackermann", 20, "female", "0124356765", "No. 56", "Street A", 13412,"City A", "State A", "A", 13, 1, 2019, 14, 45, false);
   nurse->insertNode(wNode);
   wNode=nurse->createNode("P0004","Hange", "Zoe", 33, "female", "0198973214", "No. 12", "Street B", 13416,"City B", "State B", "A", 13, 10, 2021, 14, 46, true);
   nurse->insertNode(wNode);
   wNode=nurse->createNode("P0005", "Jean", "Kirschtein", 26, "male", "0174543214", "No. 65", "Street C",13416,"City C", "State C", "A", 16, 8, 2021, 15, 45, false);
   nurse->insertNode(wNode);
   return 0;
}