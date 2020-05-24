#include "Hash.h"

// implemented for you - don't change this one
unsigned int DJB2(std::string key){
  unsigned int hash = 5381;
  // Leaving the debugging stuff commented out, in case you want to
  // play. It will output the hash at each incremental step so you can
  // see how it takes shape.
  //
  //  cout << "Hashing string \"" << key << "\"" << endl;
  //  cout << bitset<32>(hash) << " " << hash << endl;
  for (size_t i=0; i < key.length(); i++) {
    char c = key[i]; 
    hash = ((hash << 5) + hash) + c;
    // cout << bitset<32>(hash) << " " << hash << endl;
  }
  // cout << "Hashed string \"" << key << "\" to " << hash << endl;
  //
  // for light reading on why djb2 might not be the best
  // production-grade hash function, go to
  // http://dmytry.blogspot.com/2009/11/horrible-hashes.html
  return hash;
}

// implemented for you - don't change this one
unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap){
  unsigned int b = hashcode % cap;
  return b;
}

// constructor, initialize class variables and pointers here if need.
Hash::Hash(){
  // your code here
}

//deconstructor,
Hash::~Hash(){
}

shared_ptr<hash_table> Hash::InitTable(unsigned int cap){
  shared_ptr<hash_table> ret(new hash_table);
  shared_ptr<hash_node> ret2(new hash_node);
   // your code here
  ret->capacity = cap;
  ret->size = 0;
  ret->occupied = 0;
  ret->hash_func = DJB2;
  ret->bucket_func = ModuloBucketFunc;
  ret->table->at(cap) = ret2; 
  for (unsigned int i=0; i < cap; i++) {
    ret->table->at(i) = NULL;
  }
  return ret;
}

shared_ptr<hash_node> Hash::InitNode(std::string key, unsigned int hashcode, std::string val){
  shared_ptr<hash_node> ret(new hash_node);
   // your code here
  ret->deleted = false;
  ret->key = key;
  ret->hashcode = hashcode;
  ret->value = val;
  return ret;
}



bool Hash::SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value){
  // your code here
  if(tbl->capacity == tbl->occupied){
  return false;
}
unsigned int hashcode = tbl->hash_func(key);
shared_ptr<hash_node> node(InitNode(key, hashcode, value));
int insert_index = tbl->bucket_func(hashcode, tbl->capacity);

while(tbl->table->at(insert_index) && tbl->table->at(insert_index)->hashcode != hashcode) {
  insert_index = (insert_index + 1) % tbl->capacity;
}
insert_index = insert_index % tbl->capacity;

if (!tbl->table->at(insert_index)) {
  tbl->size++;
  tbl->occupied++;
}
tbl->table->at(insert_index) = node; 
return true;
}



float Hash::Load(shared_ptr<hash_table> tbl){
   // your code here
  return (float)tbl->size / (float)tbl->capacity;
  return 0;
}



std::string Hash::GetVal(shared_ptr<hash_table> tbl, std::string key){
   // your code here
  unsigned int hashcode = tbl->hash_func(key);
  unsigned int get_index = tbl->bucket_func(hashcode, tbl->capacity);
  if(!tbl->table->at(get_index)){
    return "";
  }
  while(tbl->table->at(get_index) && tbl->table->at(get_index)->hashcode != hashcode) {
    get_index = (get_index + 1) % tbl->capacity;
  }
  if (tbl->table->at(get_index)) {
    return tbl->table->at(get_index)->value;
  }
  return "";
}




bool Hash::Contains(shared_ptr<hash_table> tbl, std::string key){
   // your code here
  unsigned int hashcode = tbl->hash_func(key);
  unsigned int get_index = tbl->bucket_func(hashcode, tbl->capacity);
  if (!tbl->table->at(get_index)) {
    return false;
  }
  while(tbl->table->at(get_index) && tbl->table->at(get_index)->hashcode != hashcode) {
    get_index = (get_index + 1) % tbl->capacity;
 }
 if (tbl->table->at(get_index)) {
   return true;
 }
  return false;
}



bool Hash::Remove(shared_ptr<hash_table> tbl, std::string key){
  // your code here
  unsigned int hashcode = tbl->hash_func(key);
  unsigned int get_index = tbl->bucket_func(hashcode, tbl->capacity);
  if (!tbl->table->at(get_index)) {
  return false;
}
  while(tbl->table->at(get_index) && tbl->table->at(get_index)->hashcode != hashcode) {
    get_index = (get_index + 1) % tbl->capacity;
  }
  if (tbl->table->at(get_index)) {
    tbl->table->at(get_index)->deleted = true;
    tbl->size--;
    return true;
  }
  return false;
}




void Hash::Resize(shared_ptr<hash_table> tbl, unsigned int new_capacity){
  //your code here
//   shared_ptr<hash_node> new_tbl (new hash_node);

// for (int i=0; i < new_capacity; i++) {
//   new_tbl -> at(i) = NULL;
// }
// for (int i =0; i < tbl->capacity; i++) {
//   if (tbl-> table-> at(i)) {
//     shared_ptr<hash_node> node = tbl->table->at(i);
//     string key = node->key;
//     string value = node->value;
//     unsigned int hashcode = tbl->hash_func(key);
//     node->hashcode = hashcode;
    
//     int add_index = tbl->bucket_func(hashcode, new_capacity);
//     while(tbl->table->at(add_index) && tbl->table->at(add_index)->hashcode != hashcode) {
//       add_index = (add_index + 1) % new_capacity;
//     }
//     new_tbl -> at(insert_index) = node;
//   }
// }

// delete tbl->table;
// tbl->table = new_tbl;
// tbl->capacity = new_capacity;
// }
}
// implemented for you - feel free to change this one if you like
void Hash::PrintTable(shared_ptr<hash_table> tbl){
  cout << "Hashtable:" << endl;
  cout << "  capacity: " << tbl->capacity << endl;
  cout << "  size:     " << tbl->size << endl;
  cout << "  occupied: " << tbl->occupied << endl;
  cout << "  load:     " << Load(tbl) << endl;
  if (tbl->capacity < 130) {
    for (unsigned int i=0; i < tbl->capacity; i++) {
      cout << "[" << i << "]    ";
      if (!tbl->table->at(i)) {
        cout << "<empty>" << endl;
      } else if (tbl->table->at(i)->deleted) {
        cout << "<deleted>" << endl;
      } else {
        cout << "\"" << tbl->table->at(i)->key << "\" = \"" << tbl->table->at(i)->value << "\"" << endl;
      }
    }
  } else {
    cout << "    <hashtable too big to print out>" << endl;
  }
}

