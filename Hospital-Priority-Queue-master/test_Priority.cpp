#include <iostream>
#include "Hospital_Priority.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
int main(){

    HQueue q;
    string s="";
    int i;
    do {
        cout << "======Main Menu======" << endl;
        cout << "(1) Enter New Patient Info" << endl; //To add a new patient to the heap
        cout << "(2) Print Patient List" << endl; //Will print out the names and urgencies of all the patients currently in the heap
        //Will return and remove the patient with the highest urgency from the heap. Used for getting the next patient who needs to
        //be treated.
        cout << "(3) Get Next Patient" << endl;
        cout << "(4) Remove Patient" << endl; //Will remove a patient by name.
        cout << "(5) Find Patient" << endl; //Will print out the info for a patient searched by name.
        cout << "(6) Edit Patient Info" << endl; //Will delete an entered patient and allow you to re-enter the data.
        cout << "(7) Exit" << endl;
        cin >> s;
        try{
            i = stoi(s);
        }
        catch(...){
            i = 0;
            cout << "Error: Enter Menu Option" << endl;
        }
        switch(i){
            case 1:{
                bool correct = false;
                string name, notes, u;
                int urgency = -1;
                cin.ignore();
                while(!correct){

                    cout << "Patient's Name: " << endl;
                    getline(cin, name);
                    cin.clear();
                    while(urgency == -1){
                        cout << "Enter Urgency Priority (1-10): 10 denotes immediate attention needed" << endl;
                        getline(cin, u);
                        try{
                            urgency = stoi(u);

                        }
                        catch(...){
                            urgency =- 1;
                            cout << "Error: Re-Enter Urgency Priority" << endl;
                        }
                    }
                    //cout << "Please enter the specialist for the patient. If none, enter 'none'" << endl;
                    //getline(cin, special);
                    cout << "Enter Notes Regarding Patient. Specify none, if applicable." << endl;
                    getline(cin, notes);
                    bool valid = false;
                    do {
                        cout << "Verify Information is Correct? (Y) or (N)" << endl;
                        cout << "Name: " << name << ", Urgency: " << urgency << ", notes: " << notes << endl;
                        string check;
                        getline(cin, check);
                        if(check=="no"||check=="n"||check=="NO"||check=="N"||check=="No"){
                            urgency = -1;
                            cout << "Please re-enter the information." << endl;
                            valid = true;
                        }
                        else if (check=="yes"||check=="y"||check=="YES"||check=="Y"||check=="Yes"){
                            correct = true;
                            valid = true;
                        }
                        else {
                            cout<<"Enter valid input"<<endl;
                        }

                    }
                    while (!valid);

                }

                q.insert_p(name, urgency, notes); //Inserts the new patient into the heap
                break;

            }
            case 2:{
                q.printPatients();
                break;

            }
            case 3:{
                cout << "Enter Next Patient: " << endl;
                Patient * p=q.pop();
                if(p==NULL){
                    cout << "Empty Hospital Queue" << endl;
                }
                else{
                    q.printPatientPointer(p); //Will print out name, urgency, and notes.
                }
                break;

            }
            case 4:{
                cout << "Patient's Name: "  << endl;
                string findName;
                cin.ignore();
                getline(cin, findName);
                int removed=q.remove_p(findName);
                if(removed!=0){
                    cout << "Patient Not Found" << endl;
                }
                else{
                    cout << "Successfully Removed." << endl;
                }
                break;

            }
            case 5:{
                cout << "Patient's Name: "  << endl;
                string findName;
                cin.ignore();
                getline(cin, findName);
                q.printPatientInfo(findName);
                break;

            }
            case 6:{
                cout << "Patient's Name: "  << endl;
                string findName;
                cin.ignore();
                getline(cin, findName);

                q.remove_p(findName);

                bool correct=false;
                string name,  notes, u;
                int urgency;
                while(!correct){

                    cout << "Patient's Name" << endl;
                    getline(cin, name);
                    cout << "Enter Urgency Priority (1-10): 10 denotes immediate attention needed" << endl;
                    getline(cin, u);
                    urgency=stoi(u);
                    //cout << "Please enter the specialist for the patient. If none, enter 'none'" << endl;
                    //getline(cin, special);
                    cout << "Enter Notes Regarding Patient. Specify none, if applicable." << endl;
                    getline(cin, notes);
                    cout << "Verify Information is Correct? (Y) or (N)" << endl;
                    cout << "Name: " << name << ", Urgency: " << urgency << ", notes: " << notes << endl;
                    string check;
                    getline(cin, check);
                    if(check=="no"||check=="n"||check=="NO"||check=="N"){
                        cout << "Re-Enter Patient Info: " << endl;
                    }
                    else
                        correct=true;

                }
                cout << "Inserting" << endl;
                cout << "***********" << endl;
                q.insert_p(name, urgency, notes);
                break;

            }
        }
    }
    while(i!=7);
    cout << "Queue Updated. Session Complete" << endl;

    return 0;
}