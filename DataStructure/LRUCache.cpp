
class DoubleListNode {
public:
    int key, val;
    DoubleListNode *next, *prev;
    DoubleListNode(int k, int v)
    : key(k), val(v), next(NULL), prev(NULL) {
        
    }
};

class LRUCache{
public:
    LRUCache(int capacity)
    : cap(capacity), head(NULL), tail(NULL) {
        
    }
    
    int get(int key) {
        if (!lookup.count(key)) {
            return -1;
        }
        bubup(lookup[key]);
        return lookup[key]->val;
    }
    
    void set(int key, int value) {
        if (lookup.count(key)) {
            lookup[key]->val = value;
            bubup(lookup[key]);
        } else {
            clrup();
            DoubleListNode* cur = new DoubleListNode(key, value);
            lookup[key] = cur;
            if (tail == NULL) {
                head = tail = cur;
            } else {
                tail->next = cur;
                cur->prev = tail;
                tail = cur;
            }
        }
    }

private:
    int cap;
    map<int, DoubleListNode*> lookup;
    DoubleListNode *head, *tail;
    
    void bubup(DoubleListNode* target) {
        DoubleListNode *before = target->prev;
        DoubleListNode *after = target->next;
        if (after == NULL) {
            // target is the tail
            return;
        }
        after->prev = before;
        if (before == NULL) {
            // target is the head
            head = after;
        } else {
            before->next = after;
        }
        tail->next = target;
        target->prev = tail;
        target->next = NULL;
        tail = target;
    }
    
    void clrup() {
        if (lookup.size() == cap) {
            int rmv = head->key;
            lookup.erase(rmv);
            head = head->next;
            if (head == NULL) {
                tail = NULL;
            } else {
                head->prev = NULL;
            }
        }
    }
};
