#ifndef INDEX_OF_PERMUTATION_CPP
#define INDEX_OF_PERMUTATION_CPP

#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Find the index of integer array permutation in lexigraphic order, integer array may contain duplicate

long long noComb(unordered_map<int, int> &cnts, long long wei) {
    for (pair<int, int> cnt : cnts) {
        if (cnt.second < 2) {
            continue;
        }
        for (int i = 1; i <= cnt.second; ++i) {
            wei /= i;
        }
    }
    return wei;
}

long long permutationIndexII(vector<int>& A) {
	// Write your code here
    int size = A.size();
    if (size < 2) {
        return 1;
    }
    unordered_map<int, int> sb;
    long long index(1);
    long long wei(1);
    for (int i = size - 1; i > -1; --i) {
        int thr = A[i];
        ++sb[thr];
        unordered_set<int> mask;
        for (int j = i + 1; j < size; ++j) {
            if (mask.count(A[j]) || A[j] >= thr) {
                continue;
             }
             mask.insert(A[j]);
             --sb[A[j]];
             index += noComb(sb, wei);
             ++sb[A[j]];
        }
        wei *= (size - i);
    }
    return index;
}

#endif
