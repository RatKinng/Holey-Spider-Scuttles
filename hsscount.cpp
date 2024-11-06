//Caleb Fronek
//10/10/23
//Implamentation file for holy spider scuttles path finders

#include "hsscount.hpp"
#include <vector>
using std::vector;

//OG passed an empty partial solution
int hssCount_recurse(vector<vector<int>> & board, int dim_x, int dim_y, int finish_x, int finish_y, int curr_x, int curr_y, int squaresLeft){
    //Finish check
    if(curr_x == finish_x && curr_y == finish_y && squaresLeft == 0){
        return 1;
    }
    int total = 0;
                       //N, S, W,E,NW,NE,SW,SE
    vector<int> x_mov = {0, 0,-1,1,-1, 1,-1, 1};
    vector<int> y_mov = {1,-1, 0,0, 1, 1,-1,-1};
    for(int i=0; i < x_mov.size(); i++){
        int new_x = curr_x + x_mov[i];
        int new_y = curr_y + y_mov[i];
        if(new_x < dim_x && new_x >= 0 && new_y < dim_y && new_y >= 0 && board[new_x][new_y] == 0){
            //Set new square == 1
            board[new_x][new_y] = 1;
            squaresLeft --;
            //Go from there
            total += hssCount_recurse(board, dim_x, dim_y, finish_x, finish_y, new_x, new_y, squaresLeft); 
            board[new_x][new_y] = 0;//Set new square back to 0 to make sure it's not altered
            squaresLeft ++; //Same for squaresLeft
        }
    }
    return total;
}

//Will accept: 
//dim_x, dim_y >=0
//hole_x, hole_y >=0 && <= dim_x, dim_y respectively
//start_x, start_y ''''''''
//finish_x, finish_y ''''''
int hssCount(int dim_x, int dim_y, int hole_x, int hole_y, int start_x, int start_y, int finish_x, int finish_y){
    //lookup using board[i][j]
    //Initialize board here so it's all ready to be passed into the recursive function
    vector<vector<int>> board(dim_x, vector<int>(dim_y, 0));

    //Need to set hole and start to 1, as the spider has already visited start, and should never visit hole
    board[hole_x][hole_y] = 1; //setting hole square == 1
    board[start_x][start_y] = 1; //setting start square ==1

    //Need to know how many squares are left
    //get rid of 2 for start and hole
    int squaresLeft = (dim_x * dim_y)-2;

    //Call recursive function
    return hssCount_recurse(board, dim_x, dim_y, finish_x, finish_y, start_x, start_y, squaresLeft);
}
