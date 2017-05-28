// The code of morries algorithm to traverse binary search without extra space

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> trav;
    if (root == NULL) {
        return trav;
    }
    TreeNode* cur = root;
    TreeNode* pre = NULL;
    while (cur != NULL) {
        if (cur->left != NULL) {
            pre = cur->left;
            while (pre != NULL && pre->right != NULL && pre->right != cur) {
                pre = pre->right;
            }
            if (pre->right == NULL) {
                pre->right = cur;
                cur = cur->left;
            } else {
                pre->right = NULL;
                trav.push_back(cur->val);
                cur = cur->right;
            }
        } else {
            trav.push_back(cur->val);
            cur = cur->right;
        }
    }
    return trav;
}
