#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "IndexOfPermutation.cpp"
using namespace std;

int main() {
  vector<int> input = {2,5,3,1,3};
  int index = permutationIndexII(input);
  cout << index << endl;
  return 1;    
}