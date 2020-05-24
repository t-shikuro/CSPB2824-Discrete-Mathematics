#include "Hospital_Priority.h"

HQueue::HQueue(){
    arraySize = 10;
    //shared_ptr<Patient> (new Patient); initialized at 10
    patientArray = new Patient*[arraySize]; 
    for(int i=0; i<arraySize; i++)
        patientArray[i] = NULL;

}

HQueue::~HQueue(){
    for(int i=0; i<arraySize; i++){
        if(patientArray[i] != NULL){
            delete patientArray[i];
        }
    }
}

void HQueue::printPatients(){
    for(int k=0; k<arraySize; k++){
        if(patientArray[k] != NULL){
            printPatientPointer(patientArray[k]);
        }
    }
}

void HQueue::print_array(){
    for(int k=0; k<arraySize; k++){
        if(patientArray[k] != NULL){
            std::cout << "patientArray[" << k << "]: " << patientArray[k]->name;
            std::cout <<", urgency level: " << patientArray[k]->urgency << std::endl;
        }
        else
            std::cout << "patientArray[" << k << "]: NULL" << std::endl;
    }
}


void HQueue::printPatientInfo(std::string name){
        Patient * p = find_p(name);
        if(p==NULL){
            std::cout<< "Unable to Find Patient" << std::endl;
        }
        else{
            printPatientPointer(p);
        }
}

void HQueue::printPatientPointer(Patient * p){
    std::cout << "<><><><><><><><>" << std::endl;
    std::cout << "Patient's Name: " << p->name << std::endl;
    std::cout << "Urgency Level (1-10): " << p->urgency << std::endl;
    std::cout << "Notes: " << p->notes << std::endl;
    std::cout << "<><><><><><><><>" << std::endl;
}

void HQueue::insert_p(std::string name, int urgency, std::string notes){
    Patient* p = new Patient(name, urgency, notes);
    Patient* prevP = patientArray[1]; //heap's root
    int index = 1;
    if(prevP==NULL){
    }
    while(prevP != NULL && index < arraySize){
        index++;

        prevP = patientArray[index];
    }

    if(index==1){ //empty heap
        patientArray[index] = p;
        p->parent = NULL;
        p->left = NULL;
        p->right = NULL;
    }
    else{
        if(index == arraySize){
            double_array();
        }
        patientArray[index] = p;
        Patient *parent = patientArray[index/2];
        if(parent->left == NULL){
            parent->left = p;
        }
        else if(parent->right == NULL){
            parent->right = p;
        }
        else{
            std::cout << "Parent Not Found" << std::endl;
        }
        p->parent = parent;
        p->left = NULL;
        p->right = NULL;
        if(parent != NULL){
        }

        while(parent != NULL && parent->urgency < p->urgency){

            swapPatientsIndex(index, index/2);
            if(p->parent != NULL){
                parent = p->parent;
    
            }
            else
                parent = NULL;
        }
    }
}


//Swap patient info while maintaining heap 
void HQueue::swapPatients(Patient* child, Patient* parent){
    int chd = -1, par = -1;
    for(int i=0; i< arraySize; i++){
        if(patientArray[i] == child){
            chd = i;
        }
        if(patientArray[i] == parent){
            par = i;
        }
    }
    if(chd == -1 || par == -1){
        std::cout << "Error: Unable to Locate" << std::endl;
    }
    else{
        swapPatientsIndex(chd, par);
    }
}


void HQueue::swapPatientsIndex(int h_Child, int h_Parent){
    Patient * child = patientArray[h_Child];
    //shared_ptr<Patient> child (new Patient)
    Patient * parent = patientArray[h_Parent];
    //shared_ptr<Patient> parent (new Patient)
    if(child == NULL){
        std::cout << "NULL" << std::endl;
    }
    if(parent == NULL){
        std::cout << "NULL" << std::endl;
    }
    Patient *alt_child;
    bool left=false;
    if(parent->left == child){
        //std::cout << "child to left" << std::endl;
        alt_child = parent->right;
        left = true;
    }
    else{
        alt_child = parent->left;
    }
    child->parent = parent->parent;
    if(parent->parent != NULL){
        if(parent->parent->left == parent)
            parent->parent->left = child;
        else
            parent->parent->right = child;
    }
    parent->parent=child;
 
    if(child->left != NULL)
        child->left->parent = parent;
    if(child->right != NULL)
        child->right->parent = parent;
    parent->left = child->left;
    parent->right = child->right;

    if(alt_child != NULL)
        alt_child->parent = child;
    if(left){
        child->left = parent;
        child->right = alt_child;
    }
    else{
        child->right = parent;
        child->left = alt_child;
    }

    patientArray[h_Child] = parent;
    patientArray[h_Parent] = child;

}


//Pops and returns/removes patient with greatest urgency level 
Patient * HQueue::pop(){
    Patient * next_P = patientArray[1]; //root; patient with highest urgency level
    if(next_P == NULL){
   
        return NULL;
    }
    int i = delete_p(next_P, 1);
    if(i==0){

    }

    return next_P;

}


int HQueue::delete_p(Patient * next_P, int patientIndex){
  //deletes next_P; returns 0 if successful, 1 otherwise
    if(patientIndex > arraySize){
        std::cout << "Error" << std::endl;
        return 1;
    }
    Patient * array_end = patientArray[1];
    //shared_ptr<Patient> array_end (new Patient)
    int i = 1;
    while(patientArray[i+1] != NULL && i<arraySize){
        i++;
        array_end = patientArray[i];
    }

  
    if(i!=1){ // >1 element in heap structure

        patientArray[patientIndex] = array_end;
        patientArray[i] = NULL;
       
        if(array_end->parent->left == array_end){
            array_end->parent->left = NULL;
        }
        else
            array_end->parent->right = NULL;
        array_end->left = next_P->left;
        if(array_end->left != NULL){
          

        }
        else
            //Left child null" 
        if(array_end->right != NULL){
            //New right child"

        }
    
        array_end->right = next_P->right;
        array_end->parent = next_P->parent;
        
        Patient * urgentChild = NULL;
        //shared_ptr<Patient> urgentChild (new Patient)
        urgentChild = Largest_Child(array_end);

        while(urgentChild != NULL){
          
            if(urgentChild->urgency > array_end->urgency){
                
                swapPatients(urgentChild, array_end);
                urgentChild = Largest_Child(array_end);
            }
            else{
                urgentChild = NULL;
            }

        }

    }
    else{ //1 patient in array
        patientArray[1] = NULL;

    }


    return 0;

}

int HQueue::remove_p(std::string name){
    Patient *p = NULL;
    int index = 0;
    for(int i=0; i<arraySize; i++){
        if(patientArray[i] != NULL && patientArray[i]->name == name){
            p = patientArray[i];
            index = i;
        }
    }
    if(p!=NULL){
        return delete_p(p, index);
    }

    return 1;
}


Patient* HQueue::Largest_Child(Patient* parent){
    Patient* largerChild = NULL;
    //shared_ptr<Patient> largerChild (new Patient)
    if(parent->left != NULL || parent->right != NULL){

            if(parent->left != NULL){
                if(parent->right != NULL){
                    if(parent->left->urgency > parent->right->urgency) 
                        largerChild = parent->left;
                    else
                        largerChild = parent->right;

                }
                else //left; right null
                    largerChild = parent->left;

            }
            else //right; left null
                largerChild = parent->right;

        }
    return largerChild;

}

void HQueue::double_array(){
    Patient ** temp = new Patient*[arraySize*2];
    for(int i=0; i<arraySize; i++){
        temp[i] = patientArray[i];

    }
    for(int k=arraySize; k<arraySize*2; k++){
        temp[k] = NULL;
    }
    delete[] patientArray;
    patientArray = temp;
    arraySize = arraySize*2;


}

Patient * HQueue::find_p(std::string name){
    Patient * p = NULL;
    for(int i=0; i<arraySize; i++){
        if(patientArray[i] != NULL && patientArray[i]->name == name){
            p = patientArray[i];
        }
    }
    return p;

}