#include "BST.h"

// constructor, initialize class variables and pointers here if need.
BST::BST(){
  // Your code here
    root_ptr_ = shared_ptr<bst_node>(new bst_node);
    root_ptr_ = shared_ptr<bst_node>(NULL);
}

//deconstructor,
BST::~BST(){
}

shared_ptr<bst_node> BST::InitNode(int data){
  // Your code here
  shared_ptr<bst_node> ret (new bst_node);  //initialize new bst_node from heap (assign "n") using given int data
  ret->data = data;
  !ret->left;           //two NULL children; returns pointer
  !ret->right;
  return ret;
}


void BST::Insert(shared_ptr<bst_node> new_node){
  // Your code here
  if (!root_ptr_) {
     root_ptr_ = new_node;
     !new_node->left;
     !new_node->right;
     return;
     }
  shared_ptr<bst_node> cur = root_ptr_;   //create temp node
  if (new_node->data < cur->data) {
    if (!cur->left) {
      cur->left = new_node;       //if node to left is null, create new left node
      return;
    } else {
        root_ptr_ = new_node;
        !new_node->left;
        !new_node->right;
        return Insert(cur->left->left = new_node); 
    }
  }
  if (new_node->data > cur->data) {
    if (!cur->right) {
      cur->right = new_node;
      return;
    } else {
        root_ptr_ = new_node;
        !new_node->left;
        !new_node->right;
        return Insert(cur->right->right = new_node);  
}
  }
}

void BST::InsertData(int data){
  // Your code here

  	Insert(InitNode(data));
}

  
void BST::Remove(int data){
  // Your code here
// zybook pseudocode
//   shared_ptr<bst_node> par = NULL;
//   shared_ptr<bst_node> cur = root_ptr_;
  
//   while (!cur) {
  
//    if (cur->data == data) { // Node found 
//      if (!cur->left && !cur->right) {        // Remove leaf
//        if (!par) { // Node is root
//           root_ptr_ = NULL;
//       } else if (par->left == cur) {
//           par->left = NULL;
//         } else {
//               par->right = NULL;
//         }
//      }
//    }
//   }
//       if (cur->left && !cur->right) {    // Remove node with only left child
//           if (!par) {// Node is root
//                root_ptr_ = cur->left;
//            } else if (par->left == cur)  {
//                par->left = cur->left;
//             } else {
//                par->right = cur->left;
//             }
//       }
//           if (!cur->left && cur->right) {    // Remove node with only right child
//            if (!par) {// Node is root
//                root_ptr_ = cur->right;
//             } else if (par->left == cur) {
//                par->left = cur->right;
//             } else {
//                par->right = cur->right; 
//             }
//            }
//          } else {                                  // Remove node with two children
//             // Find successor (leftmost child of right subtree)
//             shared_ptr<bst_node> suc = cur->right;
//         } while (suc->left is not null) {
//                suc = suc->left;
//             successorData = InsertData(data)
//             Remove(root_ptr_, suc->data)     // Remove successor
//          }
//          return // Node found and removed
//       } else if (cur->data < key) { // Search right
//          par = cur
//          cur = cur->right
//       } else {                     // Search left
//          par = cur
//          cur = cur->left
//       }
//    }
//   }
  
//    return // Node not found
// }

if (root_ptr_ == NULL) {
    return;
  }

  shared_ptr<bst_node> cur = root_ptr_;

  bool rn = false;    //set bool variables to determine type of internal node (w/children)
  bool ln = false;
  bool nf = true;


  // removing root node
  if (cur->data == data){  
    shared_ptr<bst_node> removal_node = cur; 
    if (cur->left != NULL){          //left child; locate predecessor (along tree: left then right until locate)
      shared_ptr<bst_node> tempcursor = cur;
      cur = cur->left;
      if (cur->right){    //check node to right
        rn = true;    //return true for rn boolean
      }

      
      while (cur->right != NULL) {     //search nodes to locate predecessor of root
        tempcursor = cur;
        cur = cur->right;
      }
    
      if (rn) {    //let's remove the nodes to the right
        removal_node->data = cur->data;    
        tempcursor->right = NULL;   //set previous right node's location to NULL to delete node data was pulled from
        return;
      
      } else {
        removal_node->data = cur->data;
        tempcursor->data = tempcursor->left->data;
        tempcursor->left = NULL;
        return;
      }


    } else {    //if no child, locate successor by going right on tree then left until locate
      shared_ptr<bst_node> tempcursor = cur;
      cur = cur->right;

      if (cur->left){
        ln = true;   //return true for ln boolean
      }

      //continuing scanning nodes for various situations
      while (cur->left != NULL) {  
        tempcursor = cur;
        cur = cur->right;
      }

      if (ln) {
        removal_node->data = cur->data;
        tempcursor->left = NULL;
        return;
      } else {
        removal_node->data = cur->data;
        tempcursor->data = tempcursor->right->data;
        tempcursor->right = NULL;
        return;
      }

    }
  
  }
//Search through inner nodes 
 shared_ptr<bst_node> tempcursor = cur; 
  while (nf) {
    if (data < cur->data) {   //search for cursor equal to data
      if (cur->data == data) {
        nf = false;     
      } else {
        tempcursor = cur;
        cur = cur->left;
      }
    } else {            //search right
      if (cur->data == data) {
        nf = false;
      } else {
        tempcursor = cur;
        cur = cur->right;
      }
    }
  } 
  
  shared_ptr<bst_node> removal_node = cur;    //situation where tempcursor and cur are at node removal location

  // verify leaf for removal node
  if (removal_node->right == NULL && removal_node->left == NULL) {    
    if (removal_node->data < tempcursor->data) {
      tempcursor->left = NULL;
      return;
    } else {
      tempcursor->right = NULL;
      return;
    }
  }

  if (cur->left != NULL){
      shared_ptr<bst_node> tempcursor = cur;
      cur = cur->left;
      
      if (cur->right){
        rn = true;   //return true for rn boolean if situation is true
      }

      // search root predecessor
      while (cur->right != NULL) {
        tempcursor = cur;
        cur = cur->right;
      }
      // remove right nodes similarly to above
      if (rn) {
        removal_node->data = cur->data;
        tempcursor->right = NULL;
        return;
      
      } else {
        removal_node->data = cur->data;
        tempcursor->data = tempcursor->left->data;
        tempcursor->left = NULL;
        return;
      }

    // no left child, find successor in tree by going right and left until end search 
    } else {
      shared_ptr<bst_node> tempcursor = cur;
      cur = cur->right;
         if (cur->left){
        ln = true;   //return true for ln boolean
      }

      while (cur->left != NULL) {
        tempcursor = cur;
        cur = cur->right;
      }

      if (ln) {
        removal_node->data = cur->data;
        tempcursor->left = NULL;
        return;
      } else {
        removal_node->data = cur->data;
        tempcursor->data = tempcursor->right->data;
        tempcursor->right = NULL;
        return;
      }

    }
  
}

bool BST::Contains(shared_ptr<bst_node> subt, int data){
  // Your code here
    if (subt == NULL) {
    return false;
  }

  if (subt->data == data) {
    return true;
  }
  if (data < subt->data) {
    return Contains(subt->left, data);
  }
  
  if (data > subt->data) {
    return Contains(subt->right, data);
  }
}

shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data){
  // Your code here
    if (subt == NULL) {
    return NULL;
  }

  if (subt->data == data) {
    return subt;
  }


  if (data < subt->data) {   //left
    
    return GetNode(subt->left, data);
  } else {
    // look right
    return GetNode(subt->right, data);
  }

return shared_ptr<bst_node>(NULL);
}

int BST::Size(shared_ptr<bst_node> subt){
  // Your code here
    if (subt == NULL) {
    return 0;
  } else {
    return Size(subt->left) + Size(subt->right) + 1;
  }
return 0;
}

void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec){
  // Your code here
  // eventually fill in vec ex. vec[0] = 1;
    static int i = 0;
    if(root_ptr_ == NULL) {
    return;
    }

    ToVector(subt->left, vec);
    vec[i++] = subt->data;
    ToVector(subt->right, vec);
}
    
// This function is implemented for you
// Returns the root pointer
shared_ptr<bst_node> BST::GetRoot(){
  return root_ptr_;
}

// This function is implemented for you
// sets a given pointer as the top pointer
void BST::SetRoot(shared_ptr<bst_node> root_ptr){
  root_ptr_ = root_ptr;
}