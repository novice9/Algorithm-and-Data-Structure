// code of a 2D segment tree (initialized with a matrix)
// operation
//     1. update: change the value of a slot in the matrix - O(logn)
//     2. query: check the sum of any sub-matrix - O(logn)

class SegmentTreeNode2D {
public:
    int left, right, top, bottom;
    int sum;
    // top-left, top-right, bottom-left, bottom-right; 
    vector<SegmentTreeNode2D*> children;
    SegmentTreeNode2D(int l, int r, int t, int b, int s = 0)
    : left(l), right(r), top(t), bottom(b), sum(s) {
        children = vector<SegmentTreeNode2D*>(4, NULL);
    }
};

class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        int row, col;
        row = matrix.size();
        if (row != 0) {
            col = matrix[0].size();
            if (col != 0) {
                root = build(matrix, 0, col - 1, 0, row - 1);
            } else {
                root = NULL;
            }
        } else {
            root = NULL;
        }
        cout << "Successfully create the Segment Tree!" << endl;
    }

    void update(int row, int col, int val) {
        int ori = query(root, col, col, row, row);
        update(root, row, col, val - ori);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int val = query(root, col1, col2, row1, row2);
        cout << "query: " << val << endl;
        return query(root, col1, col2, row1, row2);
    }

private:
    SegmentTreeNode2D* root;
    SegmentTreeNode2D* build(vector<vector<int>> &matrix, int l, int r, int t, int b) {
        if (l > r || t > b) {
            return NULL;
        } else if (l == r && t == b) {
            return new SegmentTreeNode2D(l, r, t, b, matrix[t][l]);
        } else {
            SegmentTreeNode2D *source = new SegmentTreeNode2D(l, r, t, b);
            int colMid = l + (r - l) / 2;
            int rowMid = t + (b - t) / 2;
            source->children[0] = build(matrix, l, colMid, t, rowMid);
            source->children[1] = build(matrix, colMid + 1, r, t, rowMid);
            source->children[2] = build(matrix, l, colMid, rowMid + 1, b);
            source->children[3] = build(matrix, colMid + 1, r, rowMid + 1, b);
            for (int i = 0; i < 4; ++i) {
                if (source->children[i] == NULL) {
                    continue;
                }
                source->sum += source->children[i]->sum;
            }
            return source;
        }
    }
    
    int query(SegmentTreeNode2D* source, int l, int r, int t, int b) {
        if (source == NULL || r < source->left || source->right < l || b < source->top || source->bottom < t) {
            return 0;
        } else if (source->left == l && source->right == r && source->top == t && source->bottom == b) {
            return source->sum;
        } else {
            int colMid = source->left + (source->right - source->left) / 2;
            int rowMid = source->top + (source->bottom - source->top) / 2;
            if (r <= colMid && b <= rowMid) {
                return query(source->children[0], l, r, t, b);
            } else if (l > colMid && b <= rowMid) {
                return query(source->children[1], l, r, t, b);
            } else if (r <= colMid && t > rowMid) {
                return query(source->children[2], l, r, t, b);
            } else if (l > colMid && t > rowMid) {
                return query(source->children[3], l, r, t, b);
            } else if (b <= rowMid) {
                return query(source->children[0], l, colMid, t, b) + query(source->children[1], colMid + 1, r, t, b);
            } else if (t > rowMid) {
                return query(source->children[2], l, colMid, t, b) + query(source->children[3], colMid + 1, r, t, b);
            } else if (r <= colMid) {
                return query(source->children[0], l, r, t, rowMid) + query(source->children[2], l, r, rowMid + 1, b);
            } else if (l > colMid) {
                return query(source->children[1], l, r, t, rowMid) + query(source->children[3], l, r, rowMid + 1, b);
            } else {
                return query(source->children[0], l, colMid, t, rowMid) + query(source->children[1], colMid + 1, r, t, rowMid) +
                    query(source->children[2], l, colMid, rowMid + 1, b) + query(source->children[3], colMid + 1, r, rowMid + 1, b);
            }
        }
    }

    void update(SegmentTreeNode2D* source, int row, int col, int chg) {
        if (source == NULL || col < source->left || source->right < col || row < source->top || source->bottom < row) {
            return;
        } else {
            source->sum += chg;
            if (source->left == col && source->right == col && source->top == row && source->bottom == row) {
                return;
            }
            int colMid = source->left + (source->right - source->left) / 2;
            int rowMid = source->top + (source->bottom - source->top) / 2;
            if (col <= colMid && row <= rowMid) {
                update(source->children[0], row, col, chg);
            } else if (col > colMid && row <= rowMid) {
                update(source->children[1], row, col, chg);
            } else if (col <= colMid && row > rowMid) {
                update(source->children[2], row, col, chg);
            } else if (col > colMid && row > rowMid) {
                update(source->children[3], row, col, chg);
            } else {
                return;
            }
        }
    }
};
