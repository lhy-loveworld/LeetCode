// 1255. Maximum Score Words Formed by Letters
// Hard
// Recursion with backtrack.
// TC: O(2^N)
// SC: O(N)
class Solution {
 public:
  vector<int> word_score_;
  int res;
    
  bool CanForm(const std::string& word, vector<int>* num) {
    for (char c : word) {
      if ((*num)[c - 'a'] == 0) return false;
      (*num)[c - 'a'] -= 1;
    }
    return true;
  }
  void helper(const vector<string>& words, int idx, int cur,
	      const vector<int>& num) {
    if (idx == words.size()) {
      res = max(res, cur);
      return;
    }
    vector<int> num_copy = num;
    if (CanForm(words[idx], &num_copy)) {
      helper(words, idx + 1, cur + word_score[idx], num_copy);
    }
    helper(words, idx + 1, cur, num);
  }
    
  int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
    for (const std::string& word : words) {
      int s = 0;
      for (char c : word) {
	s += score[c - 'a'];
      }
      word_score.push_back(s);
    }      

    vector<int> letters_num(26);
    for (char c : letters) {
      letters_num[c - 'a'] += 1;
    }
        
    res = 0;
    helper(words, 0, 0, letters_num);
    return res;
  }
};
