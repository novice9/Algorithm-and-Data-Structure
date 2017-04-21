// Code of Bellman Ford dynamic programming algorithm to solve shortest path
// graph is represented as adjacent list

vector<int> bellmanFord(vector<unordered_map<int, int>> &graph, int source) {
    int size = graph.size();
    vector<int> cur(size, 0), pre(size, INT_MAX);
    pre[source] = 0;
    for (int i = 0; i <= size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (pair &e : graph[j]) {
                cur[j] = min(pre[j], pre[e.first] + e.second);
            }
        }
        vector<int> tmp = pre;
        pre = cur;
        cur = tmp;
    }
    // negative cycle detection
    for (int i = 0; i < size; ++i) {
        if (cur[i] != pre[i]) {
            return vector<int>(size, INT_MIN);
        }
    }
    // if no negative cycle exist, return shortest paths
    return cur;
}
