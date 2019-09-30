/* Honor Pledge:
*
* I pledge that I have neither given nor 
* received any help on this assignment.
*
* Youngjon
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
using namespace std; 

//declarations

struct QBoard {
  bool hasQueen;
  QBoard () {
    hasQueen = false;
	stack<bool> stack;
	 
  }
};

void PrintBoard(QBoard** board, int n) {
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col].hasQueen) {
        cout << "1";
      } else {
        cout << "0";
      }
    } 
    cout << endl;
  }
}

bool SafeToPut(int row, int col, QBoard** board, int N) {
  int colL = col - 1;
  int rowB = row + 1;
  int rowA = row - 1;

  while ((colL >= 0) or (rowB < N) or (rowA >= 0)) {
    bool leftUpperDiagonalAttack = (rowA >= 0) 
        and (colL >= 0) 
        and board[rowA][colL].hasQueen;

    bool leftLowerDiagonalAttack = (rowB < N) 
        and (colL >= 0) 
        and board[rowB][colL].hasQueen;

    bool leftAttack = (colL >= 0) 
        and board[row][colL].hasQueen;

    if (leftUpperDiagonalAttack or leftLowerDiagonalAttack or leftAttack) {
      return false;
    } else {
      colL--;
      rowA--;
      rowB++;
    }
  }
  return true;
}

bool SolveWithBTrack(QBoard** board, int N) {
  bool BtrackOn = false;
  int col = 0;
  while (col < N) {
    bool QPlaced = false;
    for (int row = 0; row < N; row++) {
      if (SafeToPut(row, col, board, N)) {
        if (BtrackOn) {
          if (board[row][col].hasQueen) {
              board[row][col].hasQueen = false;
              BtrackOn = false;
              // now Move to Next Row
              continue;
          }
        } else {
          board[row][col].hasQueen = true;
          QPlaced = true;
          break;              
        }
      }
    }

    if ((not QPlaced) and (not board[N-1][col].hasQueen)) {
      col--;
      if (col < 0) {
        // can't solve it
        return false;
      }
      BtrackOn = true;
    } else {
      col++;
    }
  }
  return true;
}

void CreateBoard(int N){
	// Dynamically allocate array of arrays for chess board 
	QBoard** board = new QBoard*[N];
		for(int i = 0; i < N; i++){
			board[i] = new QBoard[N];
		}
		// Print out the board if solvable, or an error message
		if(SolveWithBTrack(board, N)){
			cout << "This combination CAN place the queens!" << endl;
			PrintBoard(board, N);
		}else{
			cout << "This combination CAN'T place the queens." << endl;
		}
		// Free chess board arrays...MUST use array form "delete[]"!
		for (int i = 0; i < N; i++) {
			delete[] board[i];
		}
		delete[] board;
	
}

//User interface & excuted commands go here
int main(){
	//init
	//seed generator
	srand(time(NULL));
	//exit program boolean
	int exit = 0;
	int start = 0;
	//response boolean
	int response = 0;
	//variable for size
	int N = 4;
	//start stack
	stack <int> Qcol;
	//Interface for random N or userinput or exiting
	while(exit == 0){
		
		//menu
		cout << endl;
		cout << "1. Enter N" << endl;
		cout << "2. Random N" << endl;
		cout << "3. Exit Program" << endl;
		cout<<endl;
		cout << "->Please enter your selection:" << endl;
		//user
		cin >> response;
		cout << endl;
		if(response == 1){
			//get valid N from user
			while(start == 0){
				cout << endl;
				cout << "-> Please Enter a Number:" << endl;
				cin >> N;
				if(N >=0){
					cout << endl;
					start = 1;
					break;
				} else {
					//error entry
					cout << endl;
					cout << "*Illegal Input Value, Try Again!*" << endl;
					continue;
				}	
			}
			
			//show user N
			cout << endl;
			cout << "User Defined N value:" << endl;
			cout << N << endl;
			cout << endl;
			CreateBoard(N);
			start = 0;
		} else if(response == 2){
			//random N
			N = rand() %10  + 4;
			//show N
			cout << endl;
			cout << "Random N value:" << endl;
			cout << N << endl;
			cout << endl;
			CreateBoard(N);
		} else if(response == 3){
			exit = 1;
			break;
		} else {
			//error entry
			cout << endl;
			cout << "*Illegal Input Value, Try Again!*" << endl;
			continue;
		}
		
	}
	 
	 return 0;
 }
