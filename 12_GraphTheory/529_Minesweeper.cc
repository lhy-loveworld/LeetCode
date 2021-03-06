// 529. Minesweeper
// Medium
// DFS
// TC: O(MN)
// SC: O(1)
class Solution {
 public:
  void RevealAdjacent(std::vector<std::vector<char>>& board, int x, int y) {
    if (x < 0 || x == board.size() || y < 0
	|| y == board[0].size() || board[x][y] != 'E') {
      return;
    }
    int mines = 0;
    if (x > 0) {
      if (y > 0) {
	mines += board[x-1][y-1] == 'M';
      }
      mines += board[x-1][y] == 'M';
      if (y + 1 < board[0].size()) {
        mines += board[x-1][y+1] == 'M';
      }
    }
    if (y > 0) {
      mines += board[x][y-1] == 'M';
    }
    if (y + 1 < board[0].size()) {
      mines += board[x][y+1] == 'M';
    }
    if (x + 1 < board.size()) {
      if (y > 0) {
        mines += board[x+1][y-1] == 'M';
      }
      mines += board[x+1][y] == 'M';
      if (y + 1 < board[0].size()) {
        mines += board[x+1][y+1] == 'M';
      }
    }
    if (mines > 0) {
      board[x][y] = '0' + mines;
      return;
    }
    board[x][y] = 'B';
    RevealAdjacent(board, x-1, y-1);
    RevealAdjacent(board, x, y-1);
    RevealAdjacent(board, x+1, y-1);
    RevealAdjacent(board, x-1, y);
    RevealAdjacent(board, x+1, y);
    RevealAdjacent(board, x-1, y+1);
    RevealAdjacent(board, x, y+1);
    RevealAdjacent(board, x+1, y+1);    
  }

  vector<vector<char>> updateBoard(vector<vector<char>>& board,
				   vector<int>& click) {
    int x = click[0], y = click[1];
    if (board[x][y] == 'M') {
      board[x][y] = 'X';
      return board;
    }
    RevealAdjacent(board, x, y);
    return board;
  }
};
