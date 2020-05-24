#include "Huffman.h"

// constructor, initialize class variables and pointers here if need.
Huffman::Huffman(){
  // your code here
}

//deconstructor,
Huffman::~Huffman(){
}

shared_ptr<freq_info> Huffman::CreateLeaf(char symbol, int count) {
  // TODO
  shared_ptr<freq_info> leaf = shared_ptr<freq_info> (new freq_info);
  leaf->symbol = symbol;
  leaf->count = count;
  leaf->left = NULL;
  leaf->right = NULL;
  leaf->is_leaf = true;
  return leaf;

  return shared_ptr<freq_info>(NULL);
}

shared_ptr<freq_info> Huffman::CombineNodes(shared_ptr<freq_info> left, shared_ptr<freq_info> right) {
  // TODO
  shared_ptr<freq_info> internal = shared_ptr<freq_info> (new freq_info);
  internal->symbol = NULL;
  internal->count = left->count + right->count;
  internal->left = left;
  internal->right = right;
  internal-> is_leaf = false;
  return internal;
  return shared_ptr<freq_info>(NULL);
}

void Huffman::IncrementLookup(map<char, int>& lookup, char symbol) {
  // TODO
  if (lookup[symbol] == NULL) {
    lookup[symbol] = 1;
  } else {
    lookup [symbol] = lookup[symbol] + 1;
  }
}

void Huffman::LoadQueue(const map<char, int>& lookup, tree_queue& q) {
  // TODO
  map<char,int>::const_iterator i = lookup.begin();
    while (i != lookup.end()) {
      char symbol = i->first;
      int count = i->second;
      shared_ptr<freq_info> node = CreateLeaf(symbol, count);
      q.push(node);
        i++;
    }
}

shared_ptr<freq_info> Huffman::BuildTree(tree_queue& q) {
  // TODO
  bool done = false;
  shared_ptr<freq_info> left = NULL;
  shared_ptr<freq_info> right = NULL;
  while(true) {
    if (q.size() == 1) {
      return q.top();
    }
    left = q.top();
    q.pop();
    right = q.top();
    q.pop();
    shared_ptr<freq_info> new_node = CombineNodes(left,right);
    q.push(new_node);

  }
  return NULL;
}


// void traverse_tree(map<char,string> table) {
//   if (cursor->is_leaf) {
//     table -> (pair<char,string>(cursor->symbol,path));
//   } else {
//     traverse_tree(table, cursor->left, path + LEFT_CHAR);
//     traverse_tree(table, cursor->left, path + RIGHT_CHAR);
//   }
// }

map<char, string> Huffman::BuildEncodingTable(shared_ptr<freq_info> root) {
  // TODO
  map<char,string> table = map<char,string>();
  string bitstring = "";
  shared_ptr<freq_info> cursor = root;


  return map<char, string>();
}

string Huffman::Encode(map<char, string> enc_table, string input) {
  // TODO
  string encoded = "";
  for(int i=0; i < input.length(); i++) {
    char character = input[i];
    string char_code = enc_table[character];
    encoded += char_code;
  }
  return encoded;
  return "";
}

string Huffman::Decode(shared_ptr<freq_info> root, string input) {
  // TODO
  shared_ptr<freq_info> cursor = root;
  string decoded = "";
  for (int i=0; i<input.length(); i++) {
    char direction = input[i];
    if (direction == '^') {
      cursor = cursor->right;
    } else if (direction == '.') {
      cursor = cursor->left;
    }
    if (cursor->is_leaf) {
      decoded += cursor->symbol;
      cursor = root;
    }
  }
  return decoded;
  return "";
}