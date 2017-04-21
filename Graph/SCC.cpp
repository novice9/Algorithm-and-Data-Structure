// code of finding strongly connected components with DFS
// strongly connected component is a group of nodes, in which a path can be found between any 2 nodes

vector<vector<int>> scc(vector<vector<int>> &graph) {
    int noofnode = graph.size();
    vector<vector<int>> revGraph(noofnode);
    for (int i = 0; i < noofnode; ++i) {
        for (int tail : graph[i]) {
            revGraph[tail].push_back(i);
        }
    }
    vector<int> order;
    unordered_set<int> mask;
    // first DFS on the reversed graph to calculate topologic order
    // the order guarantee the second DFS always start from a sink node
    for (int i = 0; i < noofnode; ++i) {
        if (mask.count(i)) {
            continue;
        }
        recDFS(revGraph, mask, cur, order);
    }
    mask.clear();
    vector<vector<int>> groups;
    // second DFS on the original graph to calculate all SCCs
    for (int i = noofnode - 1; i > -1; --i) {
        if (mask.count(order[i])) {
            continue;
        }
        groups.push_back(vector<int>);
        itrDFS(graph, mask, order[i], groups.back());
    }
    // sort the groups to show bigger group first
    sort(groups.begin(), groups.end(), comp);
    return groups;
}

static bool comp(const vector<int> &v1, const vector<int> &v2) {
    return v1.size() > v2.size();
}

void recDFS(vector<vector<int>> &graph, unordered_set<int> &mask, int cur, vector<int> &order) {
    mask.insert(cur);
    for (int head : graph[cur]) {
        if (mask.count(head)) {
            continue;
        }
        recDFS(graph, mask, head, order);
    }
    order.push_back(cur);
}

void itrDFS(vector<vector<int>> &graph, unordered_set<int> &mask, int cur, vector<int> &group) {
    stack<int> ns;
    ns.push(cur);
    mask.insert(cur);
    while (ns.size()) {
        int tail = ns.top();
        ns.pop();
        group.push_back(tail);
        for (int head : graph[tail]) {
            if (mask.count(head)) {
                continue;
            }
            ns.push(head);
            mask.insert(head);
        }
    }
}
