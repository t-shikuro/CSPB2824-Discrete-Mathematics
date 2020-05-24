
#include <vector>
#include <iostream>

struct Patient {
  //This struct stores patient information -- name and urgency of care
  //Contains string name, urgency, and any associated notes
  std::string name;
  int urgency;   //Higher integer denoting urgency of care
  std::string notes;
  Patient *parent;    //shared_ptr<Patient> parent;
  Patient *left;      //shared_ptr<Patient> left;
  Patient *right;    //shared_ptr<Patient> right;
  Patient(std::string n, int u, std::string note) {
    name = n;
    urgency = u;
    notes = note;
  }
};

class HQueue {
public:
  HQueue();
  ~HQueue();
  void insert_p(std::string name, int urgency, std::string notes); 
  //For creating new patient info and adding to queue using specified priority (urgency 1-10). 
  //o	Will consist of while loops, for loops, and pointers to compare indices
  Patient *pop(); 
  //Returns root of heap with priority info on patient with highest urgency score
  //Otherwise will return NULL. 


  void print_array(); 
  //Finds and prints name of patient in particular queue using particular if/else statements (array)

  void double_array();  
  //When adding patient to full array, size of array doubles

  Patient * find_p(std::string name); 
  // *Using heap (computation complexity) searches for pointer with string "name"

  int remove_p(std::string name);  
  //Calls delete_p; Removes patient by locating associated pointer and index

  int delete_p(Patient * next_P, int patientIndex); 
  //removes patient while restructuring heap

  void printPatientInfo (std::string name);  
  //Identifies patient with string "name" and prints info associated with urgency, notes, etc.

  void printPatientPointer (Patient * p); 
  //Prints name, urgency priority, and notes associated with pointer

  void printPatients();

private:

  
  int arraySize; 
  //determines initial array size
  
  Patient ** patientArray; 
  //Heap structure 
  
  Patient * Largest_Child(Patient* parent); 
  // finds child_node of parent with highest urgency level 

  void swapPatientsIndex(int h_child, int h_parent); 
  //swap pointers

  void swapPatients(Patient *child, Patient *parent); 
  //swap array contents; checks index values
  
};




