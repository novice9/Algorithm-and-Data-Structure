// code of KMP algorithm to match substring

vector<int> strStr(string haystack, string needle) {
	int sizeH = haystack.size();
	int sizeN = needle.size();
	if (sizeN == 0) {
        return 0;
	}
	vector<int> lps = calLPS(needle);
	int ptr1, ptr2;
	ptr1 = ptr2 = 0;
	vector<int> indexs;
	while (ptr1 < sizeH) {
		if (haystack[ptr1] == needle[ptr2]) {
			++ptr1; ++ptr2;
			if (ptr2 == sizeN) {
				indexs.push_back(ptr1 - sizeN);
				ptr2 = lps[ptr2 - 1];
			}
		} else {
			if (ptr2 == 0) {
				++ptr1;
			} else {
				ptr2 = lps[ptr2 - 1];
			}
		}
	}
	return indexs;
}
    
vector<int> calLPS(string &str) {
	int size = str.size();
	vector<int> lps(size, 0);
	int pos(1), len(0);
	while (pos < size) {
		if (str[pos] == str[len]) {
			lps[pos++] = ++len;
		} else {
			if (len == 0) {
				lps[pos++] = 0;
			} else {
				--len;
			}
		}
	}
	return lps;
}
