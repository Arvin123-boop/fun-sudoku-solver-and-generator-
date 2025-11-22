#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Sudoku {
    int grid[9][9];

public:
    Sudoku() { 
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                grid[i][j]=0;
    }

    void printGrid() {
        cout << "-------------------------\n";
        for(int i=0;i<9;i++) {
            for(int j=0;j<9;j++) {
                if(j%3==0) cout << "| ";
                if(grid[i][j]==0) cout << ". ";
                else cout << grid[i][j] << " ";
            }
            cout << "|\n";
            if((i+1)%3==0) cout << "-------------------------\n";
        }
    }

    bool isSafe(int row,int col,int num) {
        for(int x=0;x<9;x++)
            if(grid[row][x]==num || grid[x][col]==num)
                return false;

        int startRow = row - row%3;
        int startCol = col - col%3;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(grid[i+startRow][j+startCol]==num)
                    return false;
        return true;
    }

    bool solve() {
        int row=-1,col=-1;
        bool empty=false;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(grid[i][j]==0){
                    row=i; col=j;
                    empty=true;
                    break;
                }
            }
            if(empty) break;
        }
        if(!empty) return true;

        for(int num=1;num<=9;num++){
            if(isSafe(row,col,num)){
                grid[row][col]=num;
                if(solve()) return true;
                grid[row][col]=0;
            }
        }
        return false;
    }

    void fillDiagonal() {
        for(int i=0;i<9;i+=3)
            fillBox(i,i);
    }

    void fillBox(int row,int col){
        vector<int> nums={1,2,3,4,5,6,7,8,9};
        random_shuffle(nums.begin(),nums.end());
        int idx=0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                grid[row+i][col+j]=nums[idx++];
    }

    void removeDigits(int count){
        srand(time(0));
        while(count>0){
            int i = rand()%9;
            int j = rand()%9;
            if(grid[i][j]!=0){
                grid[i][j]=0;
                count--;
            }
        }
    }

    void generateSudoku(int difficulty=40){
        fillDiagonal();
        solve();
        removeDigits(difficulty);
    }
};

int main(){
    Sudoku s;
    cout << "Generating Sudoku...\n";
    s.generateSudoku(40); // 40 empty cells = medium difficulty
    cout << "\nSudoku Puzzle:\n";
    s.printGrid();

    char choice;
    cout << "\nDo you want to solve it? (y/n): ";
    cin >> choice;
    if(choice=='y' || choice=='Y'){
        if(s.solve()){
            cout << "\nSolved Sudoku:\n";
            s.printGrid();
        } else {
            cout << "No solution exists!\n";
        }
    }

    return 0;
}
