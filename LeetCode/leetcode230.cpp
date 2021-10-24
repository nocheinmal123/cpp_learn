#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <algorithm>
using namespace std;
/**
 * Definition for a binary tree node.
 * 二叉搜索树中序就是总小到大排列好
**/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    vector<int> ans;
    void dfs(TreeNode* cur){
        if(cur == nullptr) return;
        dfs(cur->left);
        ans.push_back(cur->val);
        dfs(cur->right);
    }
    int kthSmallest(TreeNode* root, int k) {
        TreeNode* cur = root;
        dfs(cur);
        return ans[k-1];
    }
};