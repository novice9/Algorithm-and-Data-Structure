// Dijstra's shortest path algorithm (graph should not contain negative edge)
// Graph is represented as adjacent list, Min HashHeap is used to improve timing complexity
// Code of HashHeap is in the data structure directory

vector<int> dijstraShortestPath(vector<unordered_map<int, int>> &graph, int source) {
    int size = graph.size();
    vector<int> dist(size, INT_MAX);
    // initiate the minHeap with source node
    HashHeap minHeap;
    minHeap.insert(source, 0);
    for (int i = 0; i < size; ++i) {
        HeapNode cur = minHeap.getMin();
        minHeap.popMin();
        dist[cur.key] = cur.val;
        for (pair<int, int> e : graph[cur.key]) {
            int key = e.first;
            // shortest path to key aleready found
            if (dist[key] != INT_MAX) {
                continue;
            }
            int val = cur.val + e.second;
            // existing path is shorter
            if(minHeap.getKey(key) <= val) {
                continue;
            }
            // update minHeap to include the shorter path
            minHeap.remove(key);
            minHeap.insert(key, val);
        }
    }
    return dist;
}

