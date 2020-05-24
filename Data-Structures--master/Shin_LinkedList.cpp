#include "LinkedList.h"

// constructor, initialize class variables and pointers here if need.
LinkedList::LinkedList(){
  // Your code here
  
  top_ptr_ = shared_ptr<node>(new node);
  top_ptr_ = shared_ptr<node>(NULL);
  
}

//deconstructor,
LinkedList::~LinkedList(){
}


shared_ptr<node> LinkedList::InitNode(int data){
  shared_ptr<node> ret(new node);  
  // Your code here
  ret->data = data;         //storing data element inside new ret node
  ret->next = NULL;         //Return null for next unknown element

  return ret;
}

string LinkedList::Report(){
  string ret;
  // Your code here
  
  ret += "";      //empty string; list is empty

 
  shared_ptr<node> cursor = top_ptr_ ; //set cursor for appended data (from test_Linkedlist)
  top_ptr_ = shared_ptr<node>(cursor); //re-assigning shared pointer to newly created no

  while(cursor != NULL){        //while list is not empty, append data with space " "
   ret += to_string(cursor->data) + " ";
   cursor = cursor->next;       // point to next node
  }
  
  return ret;
}

void LinkedList::AppendData(int data){
  // Your code here
  Append(InitNode(data));         //Using Append and InitNode functions 
}

void LinkedList::Append(shared_ptr<node> new_node){
  // Your code here
  if (top_ptr_ == NULL) {         //If head is null
    top_ptr_ = new_node;
  } else {
    shared_ptr<node> cursor = top_ptr_;
    while (cursor->next != NULL) {
      cursor = cursor->next;     //Implementing new node with cursor pointing to empty space
    }
    cursor->next = new_node;
  }

}

void LinkedList::InsertData(int offset, int data){
  // Your code here
  Insert(offset, InitNode(data));    //Implementing Insert and InitNode functions
}

void LinkedList::Insert(int offset, shared_ptr<node> new_node){
  // Your code here
  int i = 0; //initialize variable i for loop used in function
  if (offset == 0) {
    // Both linked list is empty (head is null) we can create new node. Have new_node point to same address
    // top_ptr_ points to.
    new_node->next = top_ptr_;

    top_ptr_ = new_node; //top node refers to new_node
    return;
  } else {
    shared_ptr<node> cursor = top_ptr_;   //initialize cursor
    while (i < (offset - 1)) {
      cursor = cursor->next;
      i += 1;
    }
    shared_ptr<node> prior_insert = cursor;
    shared_ptr<node> after_insert = cursor->next; //pointing at new node
    prior_insert->next = new_node;
    new_node->next = after_insert;
  
  }
  return;
}

void LinkedList::Remove(int offset){
  // Your code here
  int i = 0;    //Again, initializing i variable for loop later. 
  if (offset == 0) {
    shared_ptr<node> r = top_ptr_;   //Similarly to Insert function. Have new node 'r' point to same node as top.
    top_ptr_ = r->next;
    
    return;
  } else {
    shared_ptr<node> cursor = top_ptr_;
    while(i < (offset-1)) {
      cursor = cursor->next;
      i += 1;
    }
    shared_ptr<node> prior_delete = cursor;
    shared_ptr<node> deletion = cursor->next;
    shared_ptr<node> after_delete = deletion->next;
    prior_delete->next = after_delete;

  }
  return;
}

int LinkedList::Size(){
  int ret;
  // Your code here
  if (top_ptr_ == NULL) {        //empty list
    return 0;
  }
  ret = 0;
  shared_ptr<node> cursor = top_ptr_;
  while (cursor != NULL) {
    ret += 1;                          //counts through while loop
    cursor = cursor->next;
  }
  return ret;
}

bool LinkedList::Contains(int data){
  bool ret;
  // Your code here
  ret = false;
  if (top_ptr_ == NULL) {   //returns false if list contains empty data set
    return ret;
  }
  shared_ptr<node> cursor = top_ptr_;    //set new node cursor as head
  
  while (cursor != NULL) {
    if (cursor->data == data) {
      ret = true;                     //if cursor contains data, return true for ret
    }
    cursor = cursor->next;
  }
  return ret;
}

// This function is implemented for you
// It returns the top pointer
shared_ptr<node> LinkedList::GetTop(){
  return top_ptr_;
}

// This function is implemented for you
// It sets a given pointer as the top pointer
void LinkedList::SetTop(shared_ptr<node> top_ptr){
  top_ptr_ = top_ptr;
}
