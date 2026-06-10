// #72 Edit Distance
// Hard
// Method: DP. dp[m][n] means the edit distance from word1[0:m] to word2[0:n].
// if word1[m] == word2[n] dp[m][n] = dp[m-1][n-1]
// else dp[m][n] = min(dp[m][n-1] + 1, // insert at back
//                     dp[m-1][n-1] + 1, // replace back
//                     dp[m+1][n] + 1) // delete at back
// Time complexity: O(M*N)
// Space complexity: O(N)

class Solution {
 public:
  int minDistance(std::string word1, std::string word2) {
    int m = word1.size(), n = word2.size();
    std::vector<int> helper(n + 1, 0);
    int prev;
    for (int i = 1; i <= n; ++i) helper[i] = i;
    for (int i = 1; i <= m; ++i) {
      prev = helper[0];
      helper[0] = i;
      for (int j = 1; j <= n; ++j) {
        swap(helper[j], prev);
        if (word1[i - 1] != word2[j - 1])
          helper[j] = min(helper[j - 1] + 1, min(prev + 1, helper[j] + 1));
      }
    }
    return helper.back();
  }
};

// Solution 2: BFS.
// Time complexity: O(M*N) worst case, when all characters are different.
//                         but it can cut many branches when there are many
//                         same characters.
// Space complexity: O(M*N) worst case, when all characters are different, and
// we need to store all the states in the set.
class Solution {
 public:
  int minDistance(string word1, string word2) {
    std::queue<std::pair<int, int>> q;
    // std::pair is not hashable, but has default comparator.
    // std::set<std::pair<int, int>> mem;
    std::unordered_set<uint64_t> mem;
    int l1 = word1.size(), l2 = word2.size();
    q.push({0, 0});
    int d = 0;
    while (!q.empty()) {
      int n = q.size();
      for (int k = 0; k < n; k++) {
        auto [i, j] = q.front();
        q.pop();
        // pack i and j into a uint64_t, to avoid the overhead of pair hashing.
        uint64_t p = (static_cast<uint64_t>(i) << 32) + j;
        if (mem.count(p) > 0) {
          continue;
        }
        mem.insert(p);
        while (i != l1 && j != l2 && word1[i] == word2[j]) {
          i++;
          j++;
        }
        if (i == l1 && j == l2) {
          return d;
        }
        if (i != l1) {
          if (j != l2) {
            q.push({i + 1, j + 1});
          }
          q.push({i + 1, j});
        }
        if (j != l2) {
          q.push({i, j + 1});
        }
      }
      d++;
    }
    return -1;
  }
};