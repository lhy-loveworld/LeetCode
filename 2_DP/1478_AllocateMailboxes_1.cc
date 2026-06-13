// #1478. Allocate Mailboxes
// Hard
// Method: DP. When k == 1, the mailbox should be located at the medium of the
// houses. When k > 1, we separate the situation to k -1 and 1.
// Time Complexity: O(K*N*N)
// Space Complexity: O(N*N)
class Solution {
 public:
  // Method 1: Recursion + Memoisation
  std::vector<std::vector<int>> min_k_;
  int RecFind(const std::vector<std::vector<int>>& min_1, int k, int start,
              int end) {
    if (k == 1) return min_1[start][end];
    if (min_k_[k][end] >= 0) return min_k_[k][end];
    int res = INT_MAX;
    for (int i = k - 1; i <= end; ++i) {
      res = min(res, RecFind(min_1, k - 1, 0, i - 1) + min_1[i][end]);
    }
    min_k_[k][end] = res;
    return res;
  }
  int minDistance(vector<int>& houses, int k) {
    int n = houses.size();
    std::sort(houses.begin(), houses.end());
    for (int i = 1; i < n; ++i) {
      houses[i] += houses[i - 1];
    }
    std::vector<std::vector<int>> min_1(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int len = j - i + 1;
        int mid = (i + j) / 2;
        min_1[i][j] = houses[j] - houses[mid] * 2;
        if (len % 2 == 1) {
          min_1[i][j] += houses[mid] - houses[mid - 1];
        }
        if (i != 0) min_1[i][j] += houses[i - 1];
      }
    }
    min_k_ = std::vector<std::vector<int>>(k + 1, std::vector<int>(n, -1));

    return RecFind(min_1, k, 0, n - 1);
  }

  // Method 2: DP
  int minDistance(vector<int>& houses, int k) {
    int n = houses.size();
    std::sort(houses.begin(), houses.end());
    for (int i = 1; i < n; ++i) {
      houses[i] += houses[i - 1];
    }
    std::vector<std::vector<int>> min_1(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int len = j - i + 1;
        int mid = (i + j) / 2;
        min_1[i][j] = houses[j] - houses[mid] * 2;
        if (len % 2 == 1) {
          min_1[i][j] += houses[mid] - houses[mid - 1];
        }
        if (i != 0) min_1[i][j] += houses[i - 1];
      }
    }
    std::vector<int> dp = min_1[0];
    for (int i = 2; i <= k; ++i) {
      for (int j = n - 1; j > 0; --j) {
        for (int div = 0; div < j; ++div) {
          dp[j] = min(dp[j], dp[div] + min_1[div + 1][j]);
        }
      }
    }
    return dp.back();
  }
};
