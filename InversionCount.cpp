int InvsCnt(vector<int> &nums, int beg, int end) {
    int size = end - beg + 1;
    if (size < 2) {
        return 0;
    }
    int mid = beg + size / 2;
    int left = InvsCnt(nums, beg, mid - 1);
    int right = InvsCnt(nums, mid, end);
    vector<int> buffer;
    for (int i = beg; i < mid; ++i) {
        buffer.push_back(nums[i]);
    }
    // merge array
    int cross(0);
    int ptr(beg), ptr1(0), ptr2(mid);
    while (ptr1 < buffer.size() && ptr2 <= end) {
        if (buffer[ptr1] <= nums[ptr2]) {
            nums[ptr++] = buffer[ptr1++];
        } else {
            nums[ptr++] = nums[ptr2++];
            cross += (buffer.size() - ptr1);
        }
    }
    while (ptr1 < buffer.size()) {
        nums[ptr++] = buffer[ptr1++];
    }
    return cross + left + right;
}
