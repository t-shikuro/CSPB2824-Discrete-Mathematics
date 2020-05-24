#include "automata.h"
#include <sstream>

std::string balanced_in_middle(int n) {
  using namespace std;
  stringstream out;
  for (int i=0; i < n; i++) {
    out << " ";
  }
  out << "#";
  for (int i=0; i < n; i++) {
    out << " ";
  }
  return out.str();
}

int main() {
  // N spaces, an octothorpe, then N more spaces. This input will
  // give a Sierpinski triangle if you've implemented everything in
  // automata.cpp correclty :)
  // std::string in = "                                                                #                                                               ";

  
  // here is an alternate input. play around with it, try different
  // values.
  // string in= " # # # ## # # ### #";
  std::string in = balanced_in_middle(60);
  generate(in, 32);
}
