// Karger's randomized minimum cut algorithm
// Graph is represented in a adjacent list

int kargerMinCut(vector<vector<int>> graph) {
    int noofnode = graph.size();
    vector<bool> book(noofnode, false);
    int noofedge(0);
    for (int i = 0; i < noofnode; ++i) {
        noofedge += graph[i].size();
    }
    // contract can only happen n - 2 times
    for (int i = 0; i < noofnode - 2; ++i) {
        // pick a random edge for every contraction
        int index = rand() % noofedge;
        pair<int, int> edge = findEdge(graph, index);
        int live = min(edge.first, edge.second);
        int dead = max(edge.first, edge.second);
        // merge the 2 nodes connected by the selected edge
        removeEdge(graph, live, dead);
        for (int j = 0; j < graph[dead].size(); ++j) {
            if (graph[dead][j] == live) {
                noofedge -= 2;
                continue;
            }
            updateEdge(graph, graph[dead][j], dead, live);
        }
        graph[dead] = vector<int>();
        book[dead] = true;
        // re-sort all the lists
        for (int i = 0; i < noofnode; ++i) {
            if (book[i]) {
                continue;
            }
            sort(graph[i].begin(), graph[i].end(), less<int>());
        }
    }
    return noofedge / 2;
}

pair<int, int> findEdge(vector<vector<int>> &graph, int index) {
    int cur(0);
    while (1) {
        if (index < graph[cur].size()) {
            break;
        }
        index -= graph[cur++].size();
    }
    return pair<int, int>(cur, graph[cur][index]);
}

void removeEdge(vector<vector<int>> &graph, int tail, int head) {
    int cnt(0);
    int size = graph[tail].size();
    for (int i = 0; i < size; ++i) {
        if (graph[tail][i] == head) {
            graph[tail][i] = graph[tail][size - 1 - cnt];
            ++cnt;
        }
    }
    for (int i = 0; i < cnt; ++i) {
        graph[tail].pop_back();
    }
}

void updateEdge(vector<vector<int>> &graph, int tail, int preHead, int newHead) {
    graph[newHead].push_back(tail);
    int size = graph[tail].size();
    for (int i = 0; i < size; ++i) {
        if (graph[tail][i] == preHead) {
            graph[tail][i] = newHead;
            break;
        }
    }
}
