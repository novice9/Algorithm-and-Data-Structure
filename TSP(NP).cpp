// code of dynamic programming algorithm on traveling salesman problem 
// The distance between cities are represented as a matrix

// dp[i][j] denote the shortest trip start from city 0, end at city i + 1 and path through cities marked by j
// j is 32 bit integer, then the 1's index represent the IDs of cities visited
// e.g dp[2][7] : 7 is "00..00111" then it is the shortest path from city 0 to city 3 which via city 2 and 1

// thus this code can only solve TSP up to 33 cities

float TSP(vector<vector<float>> &roadMap) {
    int noofcity = roadMap.size();
    // assume the round trip always start from the city 0
    // thus only need to conside the trip of the remainning n - 1 cities
    int size = pow(2, noofcity - 1);
    vector<vector<float>> dp(noofcity - 1, vector<float>(size, FLT_MAX));
    // boundary condition
    for (int i = 0; i < noofcity - 1; ++i) {
        dp[i][(1 << i)] = roadMap[0][i + 1];
    }
    // dynamic programming
    for (int i = 2; i <= noofcity - 1; ++i) {
        int base(0);
        vector<int> trips;
        dfs(i, 0, noofcity - 1, base, trips);
        for (int trip : trips) {
            for (int j = 0; j < noofcity - 1; ++j) {
                // city not in the trip
                if ((trip & (1 << j)) == 0) {
                    continue;
                }
                // city in the trip, find the shortest trip end at this city
                int before(trip - (1 << j));
                for (int k = 0; k < noofcity - 1; ++k) {
                    // city not in the trip before
                    if ((before & (1 << k)) == 0) {
                        continue;
                    }
                    dp[j][trip] = min(dp[j][trip], dp[k][before] + roadMap[k + 1][j + 1]);
                }
            }
        }
    }
    float minTrip(FLT_MAX);
    int dest(0);
    for (int i = 0; i < noofcity - 1; ++i) {
		cout << dp[i][size - 1] << endl;
        if (minTrip < dp[i][size - 1] + roadMap[i + 1][0]) {
            continue;
        }
        minTrip = dp[i][size - 1] + roadMap[i + 1][0];
        dest = i + 1;
    }
    // retrieve the entire trip
    int trip(size - 1);
    vector<int> tour;
    int next(0);
    tour.push_back(0)
    while (trip) {
        int curt(0);
        float dist(FLT_MAX);
        for (int i = 0; i < noofcity - 1; ++i) {
            if ((trip & (1 << i)) == 0) {
                continue;
            }
            if (dist < (dp[i][trip] + roadMap[i + 1][next])) {
                continue;
            }
            dist = dp[i][trip] + roadMap[i + 1][next];
            curt = i;
        }
        trip -= (1 << curt);
        tour.push_back(curt + 1);
        next = curt + 1;
    }
    tour.push_back(0);
    return minTrip;
}

void dfs(int cnt, int pos, int bound, int index, vector<int> &indexs) {
    if (cnt == 0) {
        indexs.push_back(index);
    } else {
        for (int i = pos; i <= bound - cnt;++i) {
            dfs(cnt - 1, i + 1, bound, index + (1 << i), indexs);
        }
    }
}
