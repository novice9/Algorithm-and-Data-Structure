// Code of Kruskals' algorithm to solve k-clustering with Union-Find (implementation is in DataStructur directory)
// k-clustering: group nodes into k clusters to maximize the minimum distance bewteen any 2 clusters
// MST(minimum spanning tree) can be treated as 1-clustering problem
// graph is undirected and represented as adjacent list

class edge {
public:
    int tail, head, cost;
    edge(int t, int h, int c)
    : tail(t), head(h), cost(c) {
    }
    
    bool operator<(const edge &e) const {
        return cost < e.cost;
    }
};

int kruskalCluster(vector<unordered_map<int, int>> &graph, int k) {
    int size = graph.size();
    vector<edge> edges;
    for (int i = 0; i < size; ++i) {
        int tail = i;
        for (pair<int, int> hc : graph[tail]) {
            // graph is undirected, thus filter out duplicate edges
            if (hc.first < tail) {
                continue;
            }
            edges.push_back(edge(tail, hc.first, hc.second));
        }
    }
    sort(edges.begin(), edges.end(), less<edge>());
    UnionFind uf(size);
    int clusters(size), minGap(INT_MAX);
    for (edge e : edges) {
        if (uf.find(e.tail) == uf.find(e.head)) {
            continue;
        } else {
            if (clusters == k) {
                minGap = e.cost;
                break;
            }
            uf.unify(e.tail, e.head);
            --clusters;        
        }
    }
    return minGap;
}
