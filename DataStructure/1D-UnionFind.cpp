// code of 1D union find
// operations
//     union: merge 2 groups into 1 group - O(a(n))
//     find: get the group the node belong to - O(a(n))
//     a(*) means reverse Ackman function

class Node {
public:
    int key, depth, leader;
    Node(int k, int d = 0, int l)
    : key(k), depth(d), leader(l) {
    }
};

class UnionFind {
public:
    UnionFind(int size) {
        for (int i = 0; i < size; ++i) {
            nodes.push_back(Node(i, 0, i));
        }
    }
    
    int find(int k) {
        int leader = nodes[k].leader;
        if (leader != k) {
            nodes[k].leader = find(leader);
        }
        return nodes[k].leader;
    }
    
    void unify(int k1, int k2) {
        int l1 = find(k1);
        int l2 = find(k2);
        if (nodes[l1].depth == nodes[l2].depth) {
            nodes[l2].leader = l1;
            ++nodes[l1].depth;
        } else if (nodes[l1].depth < nodes[l2].depth) {
            nodes[l1].leader = l2;
        } else {
            nodes[l2].leader = l1;
        }
    }
    
private:
    vector<Node> nodes;
};
