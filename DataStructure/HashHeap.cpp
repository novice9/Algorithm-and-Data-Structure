// Code of a hashed Maxheap (can be converted into a MinHeap easily)
// operations
//     1. insert: add a new key-value pair into the heap - Olog(n)
//     2. remove: remove a existing key-value pair from the heap - Olog(n)
//     3. getMax: return the key-value pair with the max value - Olog(n)

class HeapNode {
public:
    int key, val;
    HeapNode(int k = -1, int v = 0)
    : key(k), val(v) {
    }
    
    bool operator<(const HeapNode &hn) const {
        return val < hn.val;
    }
};

class HashHeap {
public:
    HashHeap(int s)
    : size(s), tail(0) {
        nodeList = new HeapNode[size]();
    }
    void insert(int k, int v) {
        nodeList[tail] = HeapNode(k, v);
        update(tail);
        ++tail;
        bubup(tail - 1);
    }

    void remove(int k) {
        if (!lookup.count(k)) {
            return;
        }
        int index = lookup[k];
        lookup.erase(k);
        --tail;
        swap(nodeList[tail], nodeList[index]);
        update(index);
        bubup(index);
        popdn(index);
    }

    int getMax() {
        if (tail == 0) {
            return 0;
        }
        return nodeList[0].val;
    }

private:
    HeapNode *nodeList;
    map<int, int> lookup;
    int size, tail;
    void bubup(int pos) {
        int parent = (pos + 1) / 2 - 1;
        if(parent < 0) {
            return;
        }
        if (nodeList[parent] < nodeList[pos]) {
            swap(nodeList[parent], nodeList[pos]);
            update(parent);
            update(pos);
            bubup(parent);
        }
    }

    void popdn(int pos) {
        int child1 = (pos + 1) * 2 -1;
        if (child1 >= tail) {
            return;
        }
        int maxChild;
        if (child1 == tail - 1) {
            maxChild = child1;
        } else {
            int child2 = child1 + 1;
            if (nodeList[child1] < nodeList[child2]) {
                maxChild = child2;
            } else {
                maxChild = child1;
            }
        }
        if (nodeList[pos] < nodeList[maxChild]) {
            swap(nodeList[pos], nodeList[maxChild]);
            update(pos);
            update(maxChild);
            popdn(maxChild);
        }
    }

    void update(int pos) {
        int key = nodeList[pos].key;
        if (!lookup.count(key)) {
            lookup.insert(make_pair(key, -1));
        }
        lookup[key] = pos;
    }
};

