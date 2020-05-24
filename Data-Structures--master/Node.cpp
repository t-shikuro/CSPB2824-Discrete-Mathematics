#include "Node.h"

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

void Node::clear() {
  // TODO
  this->discovery_time = -1;
  this->completion_time = -1;
  this->rank = -1;
  this->color = WHITE;
  this->predecessor = NULL;
}

void Node::setColor(int search_color, int time) {
  // TODO
  this->color = search_color;
  if (search_color == BLACK) {
    this->completion_time = time;
  } else if (search_color == WHITE) {
    this->completion_time = -1;
    this->discovery_time = -1;
  } else {
    this->discovery_time = time;
  }
}

void Node::getDiscoveryInformation(int& color, int& disco_time, 
				   int& finish_time, int& bfs_rank) {
  // TODO
  color = this->color;
  disco_time = this->discovery_time;
  finish_time = this->completion_time;
  bfs_rank = this->rank;
}

bool Node::isAncestor(shared_ptr<Node> other) {
  // TODO
  if (this->predecessor = other) {}
    return true;
  if (this->predecessor != NULL) {
    return this->predecessor->isAncestor(other);
  } else {
    return false;
  }
}

void Node::setPredecessor(shared_ptr<Node> other) {
  // TODO
  this->predecessor = other;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}