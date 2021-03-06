// code of calculate streaming medians with 2 heaps

vector<double> streamingMedians(vector<int> &nums) {
    priority_queue<int, vector<int>, greater<int>> upper;
    priority_queue<int, vector<int>, less<int>> lower;
    vector<double> medians;
    for (int num : nums) {
        // update heaps
        if (upper.empty() && lower.empty()) {
            lower.push(num);
        } else if (upper.empty()) {
            int sml = lower.top();
            lower.pop();
            lower.push(min(sml, num));
            upper.push(max(sml, num));
        } else {
            int sml = lower.top();
            int lrg = upper.top();
            lower.pop(); upper.pop();
            vector<int> threeNum({sml, num, lrg});
            sort(threeNum.begin(), threeNum.end(), less<int>());
            lower.push(threeNum[0]);
            upper.push(threeNum[2]);
            if (lower.size() > upper.size()) {
                upper.push(threeNum[1]);
            } else {
                lower.push(threeNum[1]);
            }
        }
        // find medians
        if (lower.size() == upper.size()) {
            medians.push_back((lower.top() + upper.top()) / 2.0);
        } else {
            medians.push_back(lower.top());
        }
    }
    return medians;
}
