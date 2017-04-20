// Code of a hashed Maxheap (can be converted into a MinHeap easily)
// operations
//     1. insert: add a new key-value pair into the heap - Olog(n)
//     2. remove: remove a existing key-value pair from the heap - O(logn)
//     3. getMax: return the key-value pair with the max value - O(1)
//     4. popMax: pop out the key-value pair with the max value - O(logn)
//     5. getKey: return the value of a provided key if existing - O(1)

class HeapNode {
public:
    int key, val;
    HeapNode(int k, int v)
    : key(k), val(v) {
    }

    bool operator<(const HeapNode &hn) const {
        return val < hn.val;
    }
};

class HashHeap {
public:
    HashHeap()
    : size(0) {
    }

    void insert(int k, int v) {
        nodes.push_back(HeapNode(k, v));
        ++size;
        update(size - 1);
        bubup(size - 1);
    }

    void remove(int k) {
        if (!lookup.count(k)) {
            return;
        }
        int index = lookup[k];
        lookup.erase(k);
        swap(nodes[size - 1], nodes[index]);
	    nodes.pop_back();
        --size;
	    update(index);
        bubup(index);
        popdn(index);
    }

    HeapNode getMax() {
        if (size == 0) {
            return HeapNode(0, 0);
        }
        return nodes[0];
    }
    
    void popMax() {
        if (size == 0) {
            return;
        }
        remove(nodes[0].key);
    }
    
    int getKey(int k) {
        if (lookup.count(k) == 0) {
            return INT_MIN;
        }
        return nodes[lookup[k]].val;
    }

private:
    vector<HeapNode> nodes;
    map<int, int> lookup;
    int size;
    void bubup(int pos) {
        int parent = (pos + 1) / 2 - 1;
        if(parent < 0 || pos >= size) {
            return;
        }
        if (nodes[parent] < nodes[pos]) {
            swap(nodes[parent], nodes[pos]);
            update(parent);
            update(pos);
            bubup(parent);
        }
    }

    void popdn(int pos) {
        int child1 = (pos + 1) * 2 -1;
        if (pos < 0 || child1 >= size) {
            return;
        }
        int maxChild;
        if (child1 == size - 1) {
            maxChild = child1;
        } else {
            int child2 = child1 + 1;
            if (nodes[child1] < nodes[child2]) {
                maxChild = child2;
            } else {
                maxChild = child1;
            }
        }
        if (nodes[pos] < nodes[maxChild]) {
            swap(nodes[pos], nodes[maxChild]);
            update(pos);
            update(maxChild);
            popdn(maxChild);
        }
    }

    void update(int pos) {
	    if (size <= pos) {
            return;
        }
        int key = nodes[pos].key;
        lookup[key] = pos;
    }
};
