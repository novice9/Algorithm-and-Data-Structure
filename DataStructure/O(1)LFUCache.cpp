// Code of a LFU(lease frequent used) cache
// operation
//     1. insert: bring new element into cache (if cache is full, remove the least frequent one) - O(1)
//     2. query: check the value of a key - O(1)

class DoubleListNode {
public:
    int key, val, freq;
    DoubleListNode *prev, *next;
    DoubleListNode(int k, int v)
    : key(k), val(v), freq(1), prev(NULL), next(NULL) {
        
    }
};

class LFUCache {
public:
    LFUCache(int capacity) 
    : thr(capacity) {
        dummy = new DoubleListNode(0, 0);
    }
    
    int get(int key) {
        if (!lookup.count(key)) {
            return -1;
        }
        update(lookup[key]);
        return lookup[key]->val;
    }
    
    void set(int key, int value) {
        if (lookup.count(key)) {
            lookup[key]->val = value;
            update(lookup[key]);
            // print();
            return;
        }
        if (thr == 0) {
            return;
        }
        if (lookup.size() == thr) {
            erase();
        }
        DoubleListNode* newNode = new DoubleListNode(key, value);
        lookup[key] = newNode;
        insert(newNode);
    }

private:
    int thr;
    DoubleListNode *dummy;
    map<int, DoubleListNode*> lookup;
    map<int, DoubleListNode*> freqHead, freqTail;
    void insert(DoubleListNode *target) {
        if (!freqHead.count(1) && !freqTail.count(1)) {
            DoubleListNode* head = dummy->next;
            dummy->next = target;
            target->prev = dummy;
            target->next = head;
            if (head != NULL) {
                head->prev = target;
            }
            freqHead[1] = freqTail[1] = target;
        } else {
            DoubleListNode* afterTail = freqTail[1]->next;
            freqTail[1]->next = target;
            target->prev = freqTail[1];
            target->next = afterTail;
            if (afterTail != NULL) {
                afterTail->prev = target;
            }
            freqTail[1] = target;
        }
    }
    void update(DoubleListNode *target) {
        int freq = target->freq;
        ++(target->freq);
        if (target == freqHead[freq] && target == freqTail[freq]) {
            freqHead.erase(freq);
            freqTail.erase(freq);
            if (!freqHead.count(freq + 1) && !freqTail.count(freq + 1)) {
                freqHead[freq + 1] = freqTail[freq + 1] = target;
            } else {
                DoubleListNode *beforeTar = target->prev;
                beforeTar->next = freqHead[freq + 1];
                freqHead[freq + 1]->prev = beforeTar;
                DoubleListNode *afterTail = freqTail[freq + 1]->next;
                freqTail[freq + 1]->next = target;
                target->prev = freqTail[freq + 1];
                target->next = afterTail;
                if (afterTail != NULL) {
                    afterTail->prev = target;
                }
                freqTail[freq + 1] = target;
            }
        } else if (target == freqHead[freq]) {
            freqHead[freq] = target->next;
            DoubleListNode *beforeTar = target->prev;
            beforeTar->next = freqHead[freq];
            freqHead[freq]->prev = beforeTar;
            if (!freqHead.count(freq + 1) && !freqTail.count(freq + 1)) {
                DoubleListNode *afterTail = freqTail[freq]->next;
                freqTail[freq]->next = target;
                target->prev = freqTail[freq];
                target->next = afterTail;
                if (afterTail != NULL) {
                    afterTail->prev = target;
                }
                freqHead[freq + 1] = freqTail[freq + 1] = target;
            } else {
                DoubleListNode *afterTail = freqTail[freq + 1]->next;
                freqTail[freq + 1]->next = target;
                target->prev = freqTail[freq + 1];
                target->next = afterTail;
                if (afterTail != NULL) {
                    afterTail->prev = target;
                }
                freqTail[freq + 1] = target;
            }
        } else if (target == freqTail[freq]) {
            freqTail[freq] = target->prev;
            if (!freqHead.count(freq + 1) && !freqTail.count(freq + 1)) {
                freqHead[freq + 1] = freqTail[freq + 1] = target;
            } else {
                DoubleListNode *beforeTar = target->prev;
                beforeTar->next = freqHead[freq + 1];
                freqHead[freq + 1]->prev = beforeTar;
                DoubleListNode *afterTail = freqTail[freq + 1]->next;
                freqTail[freq + 1]->next = target;
                target->prev = freqTail[freq + 1];
                target->next = afterTail;
                if (afterTail != NULL) {
                    afterTail->prev = target;
                }
                freqTail[freq + 1] = target;
            }
        } else {
            DoubleListNode *beforeTar = target->prev;
            DoubleListNode *afterTar = target->next;
            beforeTar->next = afterTar;
            afterTar->prev = beforeTar;
            if (!freqHead.count(freq + 1) && !freqTail.count(freq + 1)) {
                DoubleListNode *afterTail = freqTail[freq]->next;
                freqTail[freq]->next = target;
                target->prev = freqTail[freq];
                target->next = afterTail;
                if (afterTail != NULL) {
                    afterTail->prev = target;
                }
                freqHead[freq + 1] = freqTail[freq + 1] = target;
            } else {
                DoubleListNode *afterTail = freqTail[freq + 1]->next;
                freqTail[freq + 1]->next = target;
                target->prev = freqTail[freq + 1];
                target->next = afterTail;
                if (afterTail != NULL) {
                    afterTail->prev = target;
                }
                freqTail[freq + 1] = target;
            }
        }
    }
    void erase() {
        DoubleListNode *head = dummy->next;
        DoubleListNode *afterHead = head->next;
        lookup.erase(head->key);
        int freq = head->freq;
        if (head == freqHead[freq] && head == freqTail[freq]) {
            freqHead.erase(freq);
            freqTail.erase(freq);
        } else {
            // List head should be the head of some freq range
            freqHead[freq] = head->next; 
        }
        dummy->next = afterHead;
        if (afterHead != NULL) {
            afterHead->prev = dummy;
        }
    }
};
