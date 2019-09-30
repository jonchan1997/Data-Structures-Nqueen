#include <iostream>

using namespace std;

struct QBoard {
  bool hasQueen;
  QBoard () {
    hasQueen = false;
  }
};

void PrintChessBoard(QBoard** board, int n) {
  for (int row = 0; row < n; row++) {
    for (int column = 0; column < n; column++) {
      if (board[row][column].hasQueen) {
        cout << "1";
      } else {
        cout << "0";
      }
    } 
    cout << endl;
  }
}

bool IsSafeToPutQueen(int row, int column, QBoard** board, int n) {
  int columnLeft = column - 1;
  int rowBelow = row + 1;
  int rowAbove = row - 1;

  while ((columnLeft >= 0) or (rowBelow < n) or (rowAbove >= 0)) {
    bool leftUpperDiagonalAttack = (rowAbove >= 0) 
        and (columnLeft >= 0) 
        and board[rowAbove][columnLeft].hasQueen;

    bool leftLowerDiagonalAttack = (rowBelow < n) 
        and (columnLeft >= 0) 
        and board[rowBelow][columnLeft].hasQueen;

    bool leftAttack = (columnLeft >= 0) 
        and board[row][columnLeft].hasQueen;

    if (leftUpperDiagonalAttack or leftLowerDiagonalAttack or leftAttack) {
      return false;
    } else {
      columnLeft--;
      rowAbove--;
      rowBelow++;
    }
  }
  return true;
}

bool CanSolveWithBackTrack(QBoard** board, int n) {
  bool inBacktrack = false;
  int column = 0;
  while (column < n) {
    bool wasQueenPlaced = false;
    for (int row = 0; row < n; row++) {
      if (IsSafeToPutQueen(row, column, board, n)) {
        if (inBacktrack) {
          if (board[row][column].hasQueen) {
              board[row][column].hasQueen = false;
              inBacktrack = false;
              // now Move to Next Row
              continue;
          }
        } else {
          board[row][column].hasQueen = true;
          wasQueenPlaced = true;
          break;              
        }
      }
    }

    if ((not wasQueenPlaced) and (not board[n-1][column].hasQueen)) {
      column--;
      if (column < 0) {
        // can't solve it
        return false;
      }
      inBacktrack = true;
    } else {
      column++;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  // Read board size from user
  int n = 0;
  cout << "Enter the value of N" << "\n";
  cin >> n;

  // Dynamically allocate array of arrays for chess board 
  QBoard** board = new QBoard*[n];
  for (int i = 0; i < n; i++) {
    board[i] = new QBoard[n];
  }

  // Print out the board if solvable, or an error message
  if (CanSolveWithBackTrack(board, n)) {
    cout << "This combination CAN place the queens!" << "\n";
    PrintChessBoard(board, n);
  } else {
    cout << "This combination CAN'T place the queens." << "\n";
  }

  // Free chess board arrays...MUST use array form "delete[]"!
  for (int i = 0; i < n; i++) {
    delete[] board[i];
  }
  delete[] board;

  return 0;
}