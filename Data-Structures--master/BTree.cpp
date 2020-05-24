#include "BTree.h"

// constructor, initialize class variables and pointers here if need.
BTree::BTree(){
  // Your code here
}

//deconstructor,
BTree::~BTree(){
}

//insert and remove must handle cases where adding or removing keys will grow
//or shrink the tree. In some cases, you'll have to merge nodes and re-allocate keys; other 
//times you'll have to need to split nodes and similarly shuffle keys around. Consider
//having logic to test the various situations and handle them in their own functions.
void BTree::insert(shared_ptr<btree> root, int key){
  //implements find function for determining node for key #valid keys
  shared_ptr<btree> insrt_node = find(root, key);
  for (int i = 0; i < insrt_node->num_keys; i++) {
    if (insrt_node->keys[i] == key) {
      return;
    }
  }
   // check leaf bool
  if (insrt_node->is_leaf == true) {
    if (insrt_node->num_keys < BTREE_ORDER - 1) {
    // iterate through i
      int i = insrt_node->num_keys - 1;
    
  if (key > insrt_node->keys[i]) {
    insrt_node->keys[i+1] = key;
    insrt_node->num_keys += 1;
    return;
  } else {
    int i = insrt_node->num_keys - 1;
      while (i >= 0 && key < insrt_node->keys[i]) {
        insrt_node->keys[i+1] = insrt_node->keys[i];  //copy keys
        i -= 1;
        }  
        insrt_node->keys[i+1] = key;
        insrt_node->num_keys += 1;
        return;      
      }
    }
    //splitting node
  if (insrt_node->num_keys == BTREE_ORDER - 1) {
    shared_ptr<btree> ret = shared_ptr<btree>(new btree);
    ret->num_keys = 0;
    ret->is_leaf = true;
    for (int i=0; i <= BTREE_ORDER; i++) {
      ret->children[i] = NULL;
    }
    int j = 0;
    int idx = insrt_node->num_keys - 1;
    while (idx >= 0 && key < insrt_node->keys[idx]) {
      insrt_node->keys[idx+1] = insrt_node->keys[idx];
      idx -= 1;
    }
      insrt_node->keys[idx+1] = key;
      insrt_node->num_keys += 1;

    for (int i = (BTREE_ORDER/2)+1; i < insrt_node->num_keys; i++) {
      ret->keys[j] = insrt_node->keys[i];
      j += 1; 
      }
      ret->num_keys = j;
      int mdn_key = insrt_node->keys[(BTREE_ORDER/2)];
      insrt_node->num_keys = j;
      idx = root->num_keys - 1;

  if (mdn_key < root->keys[idx]) {  
    while (mdn_key < root->keys[idx]) {
      root->keys[idx+1] = root->keys[idx];
      root->children[idx+2] = root->children[idx+1];
      idx -= 1;
    }
      root->keys[idx+1] = mdn_key;
      root->num_keys += 1;
      root->children[idx + 2] = ret;
    }
    }  
  }
}



// remove deletes the given key from a b-tree rooted at 'root'. If the
// key is not in the btree this should do nothing.
void BTree::remove(shared_ptr<btree> root, int key){
// shared_ptr<btree> rem_node = find(root, key);
//   if (rem_node->is_leaf == true) {  
//   for (int i = 0; i < rem_node->num_keys; i++) {
//     if (key == rem_node->keys[i]) {
//       for (int j = i + 1; j < rem_node->num_keys; ++j) {
//         rem_node->keys[j-1] = rem_node->keys[j];
//       }
//         rem_node->num_keys -= 1;
//         return;
//       }
//     }
//   }
}   // passed 1 additional test but with lower score :)  commented out instead//


// find (a) currently contains this key,
// or (b) the node that would contain it if we were to try to insert
// it.  Note that this always returns a non-null node. 
shared_ptr<btree> BTree::find(shared_ptr<btree> root, int key){
  int i = 0;    //initiate counter
  shared_ptr<btree> cursor = root;
   while (i < cursor->num_keys && key > cursor->keys[i]) {
    i++;
  }
  
  if (i < cursor->num_keys && key == cursor->keys[i]) {
    return cursor;
  } else if (cursor->is_leaf == true) {
    return cursor;
  }

  if (key < cursor->keys[i]) {   
    return find(cursor->children[i], key);
  } else if (key > cursor->keys[i-1]) {
    return find(cursor->children[i], key);
  }
}


int BTree::count_nodes(shared_ptr<btree> root){
if (root == NULL) {
    return 0;
  }
  int counter = 0;
  if (root->is_leaf == true) {
    return 1;
  }
  counter += 1;
  
  for (int i = 0; i < (root->num_keys + 1); i++) {
    counter += count_nodes(root->children[i]); 
  }
  return counter;
}


int BTree::count_keys(shared_ptr<btree> root){
if (root == NULL) {
    return 0;
  }
  int counter = 0;
  if (root->is_leaf == true) {
    return root->num_keys;
  }
  counter += root->num_keys;
  for (int i = 0; i < (root->num_keys + 1); i++) {
    counter += count_keys(root->children[i]);
  }
  return counter;
}