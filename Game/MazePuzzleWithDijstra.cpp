// There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
// Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.
// The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

class MazePuzzle {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int row = maze.size();
        int col = maze[0].size();
        vector<vector<int>> dist(row, vector<int>(col, INT_MAX));
        dist[start[0]][start[1]] = 0;
        HashHeap distHeap;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                distHeap.add(to_string(i) + "," + to_string(j), dist[i][j]);
            }
        }
        while (distHeap.getMin().val != INT_MAX) {
            HeapNode cur = distHeap.getMin();
            distHeap.popMin();
            vector<int> coordinate = parse(cur.key);
            int base = cur.val;
            // update distance result (add this coordinate into source group)
            dist[coordinate[0]][coordinate[1]] = base;
            int x, y, move;
            string key;
            // Go Up
            x = coordinate[0]; y = coordinate[1]; move = 0;
            while (x > 0 && maze[x - 1][y] != 1) {
                --x; ++move;
            }
            key = to_string(x) + "," + to_string(y);
            if (distHeap.get(key) > base + move) {
                distHeap.del(key);
                distHeap.add(key, base + move);
            }
            // Go Down
            x = coordinate[0]; y = coordinate[1]; move = 0;
            while (x < row - 1 && maze[x + 1][y] != 1) {
                ++x; ++move;
            }       
            key = to_string(x) + "," + to_string(y);
            if (distHeap.get(key) > base + move) {
                distHeap.del(key);
                distHeap.add(key, base + move);
            }
            // Go Left
            x = coordinate[0]; y = coordinate[1]; move = 0;
            while (y > 0 && maze[x][y - 1] != 1) {
                --y; ++move;
            }       
            key = to_string(x) + "," + to_string(y);
            if (distHeap.get(key) > base + move) {
                distHeap.del(key);
                distHeap.add(key, base + move);
            }
            // Go Right
            x = coordinate[0]; y = coordinate[1]; move = 0;
            while (y < col - 1 && maze[x][y + 1] != 1) {
                ++y; ++move;
            }
            key = to_string(x) + "," + to_string(y);
            if (distHeap.get(key) > base + move) {
                distHeap.del(key);
                distHeap.add(key, base + move);
            }  
        }
        if (dist[destination[0]][destination[1]] == INT_MAX) {
            return -1;
        }
        return dist[destination[0]][destination[1]];
    }

private:
    vector<int> parse(string &str) {
        stringstream stm(str);
        string token;
        vector<int> coor;
        while (getline(stm, token, ',')) {
            if (token.empty()) {
                continue;
            }
            coor.push_back(stoi(token));
        }
        return coor;
    }
};


// Implementation of Min HashHeap
class HeapNode {
public:
    string key;
    int val;
    HeapNode(string k, int v)
    : key(k), val(v) {
        
    }
    
    bool operator>(const HeapNode &hn) const {
        return val > hn.val;
    }
};

class HashHeap {
public:
    HashHeap()
    : size(0) {
        
    }
    // add the shortest distance so far to coordinate into the heap
    void add(string k, int v) {
        nodes.push_back(HeapNode(k, v));
        update(size);
        ++size;
        rise(size - 1);
    }
    // return -1 if no found, means the shortest distance to this coordination already found
    int get(string k) {
        if (!book.count(k)) {
            return -1;
        }
        return nodes[book[k]].val;
    }
    // remove the previous distance to coordinate k from the heap
    void del(string k) {
        if (!book.count(k)) {
            return;
        }
        int index = book[k];
        nodes[index] = nodes.back();
        update(index);
        nodes.pop_back();
        book.erase(k);
        --size;
        rise(index);
        sink(index);
    }
    // return the closest coordinate can be accessed from source group
    HeapNode getMin() {
        if (size == 0) {
            return HeapNode("-1,-1", INT_MAX);
        }
        return nodes[0];
    }
    // remove the next closest coordinate from the heap (move to the source group)
    void popMin() {
        if (size == 0) {
            return;
        }
        string key = nodes[0].key;
        del(key);
    }
    // debug feature
    void print() {
        for (HeapNode hn : nodes) {
            cout << hn.key << ": " << hn.val << endl;
        }
    }

private:
    int size;
    vector<HeapNode> nodes;
    unordered_map<string, int> book;
    void rise(int pos) {
        int parent = (pos + 1) / 2 - 1;
        if (parent == -1) {
            return;
        }
        if (nodes[parent] > nodes[pos]) {
            swap(nodes[parent], nodes[pos]);
            update(parent);
            update(pos);
            rise(parent);
        }
    }
    
    void sink(int pos) {
        int child1 = (pos + 1) * 2 - 1;
        int minChild;
        if (child1 > size - 1) {
            return;
        } else if (child1 == size - 1) {
            minChild = child1;
        } else {
            int child2 = child1 + 1;
            minChild = (nodes[child1] > nodes[child2] ? child2 : child1);
        }
        if (nodes[pos] > nodes[minChild]) {
            swap(nodes[minChild], nodes[pos]);
            update(minChild);
            update(pos);
            sink(minChild);
        }
    }
    
    void update(int pos) {
        string key = nodes[pos].key;
        book[key] = pos;
    }
};

