// #104 Max Depth Binary Tree
// Easy
// https://leetcode.com/problems/maximum-depth-of-binary-tree/tabs/description
// Arthor: lhy-loveworld
// Method: Use of DFS and BFS (level order traversal)
// Complexity: Time O(N); Space O(1)


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
 public:
  // DFS
  int maxDepth(TreeNode *root) {
    return root == nullptr ? 0 :
      max(maxDepth(root -> left), maxDepth(root -> right)) + 1;
  }

  // BFS
  // Find the children of each level
  int maxDepth(TreeNode *root) {
    if(root == nullptr) return 0;
    int res = 0;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      ++ res;
      for (int i = 0, n = q.size(); i < n; ++ i) {
	TreeNode *p = q.front();
	q.pop();
	if(p -> left != nullptr)
	  q.push(p -> left);
	if(p -> right != nullptr)
	  q.push(p -> right);
      }
    }
    return res;
  }
};
