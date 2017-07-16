// The code of morries algorithm to traverse binary search without extra space

// standard traversal
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

// traversal with iterator
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> trav;
    while (root != NULL) {
        root = morrisNext(root);
        trav.push_back(root->val);
        // can add any operations here
        root = root->right;
    }
    return trav;
}

TreeNode* morrisNext(TreeNode* cur) {
    if (root->left == NULL) {
        return root;
    } else {
        TreeNode *pred = root->left;
        while (pred != NULL && pred->right != NULL && pred->right != root) {
                pred = pred->right;
        }
        if (pred->right == NULL) {
            pred->right = root;
            return morrisNext(root->left);
        } else {
            pred->right = NULL;
            return root;
        }
    }
}
        
