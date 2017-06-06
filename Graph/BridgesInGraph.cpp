// Code of finding bridges in undirected Graph with DFS
// Algorithm Explanation: 
//    -> Traverse the graph with DFS will result in a DFS tree, and each node is assigned with a parent and index
//    -> Because loop exists in the Graph, children maybe able to access the ancestor of parent
//    -> If children can access the ancestor of parent, this edge can't be a bridge(back path exists)
//    -> Otherwise the edge is a bridge. Thus, we need to find the earliest ancestor can be reached by children to check

vector<pair<int, int>> bridgesInGraph(vector<pair<int, int>> &edges, int n) {
    vector<vector<int>> graph(n);
    // build the graph, note all edges are bi-directional
    for (pair<int, int> edge : edges) {
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }
    vector<pair<int, int>> bridges;
    vector<bool> visited(n, false);
    // order: the time order of node i get visited;
    // ancestor: the earliest ancestor in time order can be reached from node i
    // parent: the direct parent of node i during the DFS traversal
    // thus if there exists a edge(u, v), and ancestor[v] > order[u]; edge(u, v) will be a bridge, because v can not reach ancestor of u
    vector<int> order(n, INT_MAX), ancestor(n, INT_MAX), parent(n, -1);
    int index(0);
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            continue;
        }
        helper(graph, i, visited, order, ancestor, parent, index, bridges);
    }
    return bridges;
}

void helper(vector<vector<int>> &graph, int cur, vector<bool> &visited,
        vector<int> &order, vector<int> &ancestor, vector<int> &parent, int &index, vector<pair<int, int>> &bridges) {
    visited[cur] = true;
    // initialization
    order[cur] = ancestor[cur] = index++;
    for (int next : graph[cur]) {
        if (next == parent[cur]) {
            continue;
        }
        if (visited[next]) {
            ancestor[cur] = min(ancestor[cur], order[next]);
        } else {
            parent[next] = cur;
            helper(graph, next, visited, order, ancestor, parent, index, bridges);
            // the ancestor can be accessable from my direct children is also accessable from me
            ancestor[cur] = min(ancestor[cur], ancestor[next]);
            // check the condition of bridge
            if (ancestor[next] > order[cur]) {
                bridges.push_back(make_pair(cur, next));
            }
        }  
    }
}
