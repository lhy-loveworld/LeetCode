// #10 Regular Expression Matching
// Hard
// Method: DP
// Time complexity: O(M*N)
// Space complexity: O(N)

class Solution {
 public:
  // Method 1: DP. Outer loop is for s, and inner loop is for p. Look back at
  // each step.
  bool isMatch(string s, string p) {
    if (p.empty()) return s.empty();
    vector<vector<bool>> helper(2, vector<bool>(p.size() + 1, false));
    helper[0][0] = true;
    for (int i = 1; i < p.size(); i += 2) {
      if (p[i] == '*') helper[0][i + 1] = helper[0][i - 1];
    }
    for (int i = 0; i < s.size(); ++i) {
      for (int j = 0; j < p.size(); ++j) {
        if (p[j] == '*') {
          // Look back at each step.
          helper[1][j + 1] =
              helper[1][j - 1] ||
              (p[j - 1] == '.' || s[i] == p[j - 1]) && helper[0][j + 1];
        } else {
          helper[1][j + 1] = helper[0][j] && (p[j] == '.' || s[i] == p[j]);
        }
      }
      helper[0] = helper[1];
    }
    return helper[0].back();
  }

  // Method 2: recursively from head to end, if p is started with .* or a*, test
  // s with p[2:] and s[1:] with p. Look forward at each step.
  bool isMatch(string s, string p) {
    if (p.empty()) return s.empty();
    if (p.size() == 1 || p[1] != '*')
      return !s.empty() && (p[0] == '.' || p[0] == s[0]) &&
             isMatch(s.substr(1), p.substr(1));
    return isMatch(s, p.substr(2)) || !s.empty() &&
                                          (p[0] == '.' || p[0] == s[0]) &&
                                          isMatch(s.substr(1), p);
  }

  // Method 3: memoization-optimized recursion.
  std::vector<std::vector<int>> memo_;
  bool RecurMatch(const std::string& s, const std::string& p, int next_s,
                  int next_p) {
    if (next_p == p.size()) {
      if (next_s == s.size()) {
        return true;
      } else {
        return false;
      }
    }
    if (memo_[next_s][next_p]) return memo_[next_s][next_p] == 1;
    if (next_p + 1 >= p.size() || p[next_p + 1] != '*') {
      if (next_s < s.size() && (p[next_p] == '.' || p[next_p] == s[next_s]) &&
          RecurMatch(s, p, next_s + 1, next_p + 1)) {
        memo_[next_s][next_p] = 1;
        return true;
      } else {
        memo_[next_s][next_p] = 2;
        return false;
      }
    }
    if (p[next_p] == '.' && next_p + 2 == p.size()) {
      memo_[next_s][next_p] = 1;
      return true;
    }
    if (RecurMatch(s, p, next_s, next_p + 2)) {
      memo_[next_s][next_p] = 1;
      return true;
    }
    if (next_s < s.size() && (p[next_p] == '.' || p[next_p] == s[next_s]) &&
        RecurMatch(s, p, next_s + 1, next_p)) {
      memo_[next_s][next_p] = 1;
      return true;
    } else {
      memo_[next_s][next_p] = 2;
      return false;
    }
  }
  bool isMatch(string s, string p) {
    memo_ = std::vector<std::vector<int>>(s.size() + 1,
                                          std::vector<int>(p.size() + 1));
    return RecurMatch(s, p, 0, 0);
  }
};

// Method 4: BFS
class Solution {
 public:
  bool isMatch(string s, string p) {
    std::queue<std::pair<int, int>> q;
    std::unordered_set<int> mem;
    int m = s.size(), n = p.size();
    q.push({0, 0});
    while (!q.empty()) {
      auto [i, j] = q.front();
      if (i == m && j == n) {
        return true;
      }
      q.pop();
      if (j == n) continue;
      if (j + 1 < n && p[j + 1] == '*') {
        while (mem.count(100 * i + j + 2) == 0) {
          mem.insert(100 * i + j + 2);
          q.push({i, j + 2});
          if (i == m || p[j] != '.' && s[i] != p[j]) break;
          ++i;
        }
        continue;
      }
      if (i < m && (s[i] == p[j] || p[j] == '.') &&
          mem.count(100 * (i + 1) + j + 1) == 0) {
        mem.insert(100 * (i + 1) + j + 1);
        q.push({i + 1, j + 1});
      }
    }
    return false;
  }
};