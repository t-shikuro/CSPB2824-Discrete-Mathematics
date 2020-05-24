/***
 *             /\                                               
 *         _  / |            /                         /        
 *        (  /  |  . )  (---/---.-._.  .-. .-. .-. ---/---.-.   
 *         `/.__|_.'(    ) /   (   ) )/   )   |  |   /   (  |   
 *     .:' /    |    `--':/     `-' '/   /   ( `-'-'/     `-'-' 
 *    (__.'     `-'                           `-'               
 */

#include <string>

// Note that the header file doesn't have 'using namespace std', so
// all references to string have to be qualified using std::string.

// prev returns the index before i. If i is 0, it should return
// (string_size - 1).
int prev(int i, int string_size);

// next returns the index after i. If i is (string_size - 1), it
// should return 0.
int next(int i, int string_size);

// get_neighborhoold creates a three-element string that should be
// equivalent to the characters in[previous_index], in[i], and
// in[next_index] (in that order). This function should use the prev
// and next functions, because we want to treat the string as being
// circular, where the last element and the first element are
// adjacent.
//
// Example: if the input string is "abcdef", and we want the
// neigborhood around index 5, the return value should be "efa".
//
// Example using sharp signs and spaces: if the input string is
// " #  #   #   ##  # # ###  #", here's the expected output in
// table form:
//
// index  output  remark
//   0     "# #"  The string is circular. The ends meet.
//   1     " # "
//   2     "#  "
//  25     " # "  Index 25 is the last # sign in the input.
std::string get_neighborhood(std::string in, int i);

// rule90 is a function that looks at the small neighborhood of the
// input string centered about index i, and returns a character for
// the next generator. See https://en.wikipedia.org/wiki/Rule_90 for
// more than you probably want to know on the subject.
//
// Short version is: if the neighborhood is X, return Y, according to
// this table:
//
// "###" --> ' '
// "## " --> '#'
// "# #" --> ' '
// "#  " --> '#'
// " ##" --> '#'
// " # " --> ' '
// "  #" --> '#'
// "   " --> ' '
//
// There are several ways to implement this, and we're not placing any
// restrictions on how you go about it.
//
// Just to be super clear, the input to rule90 will be something like:
// " #  #   #   ##  # # ###  #"
char rule90(std::string in, int i);

// make_next_generation uses the current generation (the `in`
// parameter) and uses the `rule90` function for each cell of the
// current generation to produce a next generation string.
std::string make_next_generation(std::string in);

// generate runs make_next_generation several times using the
// initial_state as the first state; for subsequent calls it uses the
// return value from the previous invocation of
// `make_next_generation`.
//
// `num_generations` is the number of times to invoke
// `make_next_generation`.
//
// This should print the initial state and every following generation
// to the console using cout.
//
// Look at the example_output.txt file to see what it might look
// like. The example was generated with a string that looks like the
// following (a bunch of spaces, a # sign, and then the same number of
// spaces).
//
// "            #            ".
void generate(std::string initial_state, int num_generations);
