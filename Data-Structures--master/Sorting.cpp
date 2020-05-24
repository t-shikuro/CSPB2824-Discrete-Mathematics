#include "Sorting.h"

/*
  Please refer to sorting.h for documentation on each function.
   + ------ N O T E: -- Big scary warning! -----------------------------\
   |                                                                    |
   |    We clearly can't use unit testing to ensure that you're         |
   |    actually implementing the correct algorithm. I suppose we could |
   |    write some complicated static analysis checker. But it is       |
   |    easier to just look at it with our eyeballs.                    |
   |                                                                    |
   |    After the assignment is due, we will look at the most recent    |
   |    version of your implementation that got the highest score and   |
   |    make sure you're not doing something sneaky like using a        |
   |    standard library call to sort a vector.                         |
   |                                                                    |
   |    Anyone caught doing this (even though it is kinda funny) will   |
   |    be given 0 points on the assignment.                            |
   |                                                                    |
   `--------------------------------------------------------------------/ 
*/

// constructor, initialize class variables and pointers here if you need.
Sorting::Sorting(){
  // Your code here
}

//deconstructor,
Sorting::~Sorting(){
}

void Sorting::quicksort(vector<int>& data, int low_idx, int high_idx){
    //O(nlogn) -> O(n^2); divide array half each time; important to pick correct median
  if (low_idx < high_idx) {
    int pivot_loc = quicksort_partition(data, low_idx, high_idx);
    quicksort(data, low_idx, pivot_loc-1);
    quicksort(data, pivot_loc+1, high_idx);
  }
}

int Sorting::quicksort_partition(vector<int>& data, int low_idx, int high_idx){
    //return pivot index
  int pivot = data[high_idx];
  int i = low_idx - 1;

  for (int j = low_idx; j < high_idx; j++) {
    if (data[j] < pivot) {
      i = i + 1;
      int hold = data[j];
      data[j] = data[i];
      data[i] = hold;
    }
  }  
  if (data[high_idx] < data[i+1]) {
    int p_hold = data[high_idx];
    data[high_idx] = data[i+1];
    data[i+1] = p_hold;
  }
  return i+1;
}
void Sorting::bubblesort(vector<int>& data){
//Note: Slower that other sorts O(n^2). Multiple loops to iterate to ensure initial passthrough comparisons do not exit loop.
    bool is_sorted = false;
    int last_unsort = data.size() - 1;
    while (!is_sorted) {
        is_sorted = true;
         for (unsigned int j=0; j < data.size(); j++) {
            if (data[j] > data[j+1]) {
                int hold = data[j];
                data[j] = data[j+1];
                data[j+1] = hold;
                is_sorted = false;
            }
    }
    last_unsort--;
  }
}

void Sorting::mergesort(vector<int>& data){
//O(nlogn) runtime O(n) memory  space; sort left then sort right then merge sorted halves in order; algorithm requires extra space
if (data.size() == 1) {
    return;
  }
  unsigned int middle = data.size() / 2;
  vector<int> left = vector<int>(data.begin(), data.begin() + middle);
  vector<int> right = vector<int>(data.begin() + middle, data.begin() + data.size());

  mergesort(left);
  mergesort(right);
  
}


void Sorting::merge(vector<int>& left, vector<int>& right, vector<int>& result){
    unsigned int i = 0;
    unsigned int j = 0;

    while(i <= (left.size()-1) && j <= (right.size()-1)) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            i ++;
    } else {
            result.push_back(right[j]);
            j ++;
    }
  }
    while (i <= left.size()-1) {
        result.push_back(left[i]);
        i ++;
  }
    while (j <= right.size()-1) {
        result.push_back(right[j]);
        j ++;
  }
}



void Sorting::mystery_sort(vector<int>& data){
//Insertion sort

    int i = 0;
    int j = 0;
    int hold = 0;

    for (i = 0; i < data.size(); i++) {
        hold = data[i];
        j = i-1;
    while (j >= 0 && data[j] > hold) {
        data[j+1] = data[j];
        j = j-1;
    }
    data[j+1] = hold;
  }
  }
