#include <filesystem>
#include <iostream>
#include "ThreeDArray.h"
void tower_of_hannoi(int);
void setup_board(ThreeDArray*);
void move(ThreeDArray* tower, int start, int end);
void display_board(ThreeDArray*);
void solve_hannoi(ThreeDArray &tower, int num_disks, int start, int end, int aux);

void display_board(ThreeDArray* tower) {
    for (int k = 0; k < tower->get_column(); k++) {
       for (int j = 0; j < tower->get_row(); j++) {
           for (int i = 0; i < tower->get_slice(); i++) {
               std::cout<< tower->at(i,j,k) << " ";
           }
          // std::cout << std::endl;
       }
        std::cout << std::endl;

    }
    std::cout << std::endl << "* * * * * * * *" << std::endl << std::endl;
}



void tower_of_hannoi(int num_disks) {
    int board = 1, poles = 3;
    ThreeDArray tower(board,poles,num_disks);
    setup_board(&tower);
    display_board(&tower);
    solve_hannoi(tower, num_disks, 0, 2, 1);
}
void solve_hannoi(ThreeDArray &tower, int num_disks, int start, int end, int aux) {
    if (num_disks == 1) {
       move(&tower, start, end);
    }
    else {
        solve_hannoi(tower, num_disks - 1, start, aux,end);
        move(&tower, start, end);
        solve_hannoi(tower, num_disks  - 1, aux, end,start);
    }
}

void setup_board(ThreeDArray* tower) {
    int disk = tower->get_column(), disk_number = 1;
    for (int i = 0 ; i <= disk - 1 ; i++) {
        tower->at(0,0,i) = disk_number;
        disk_number++;
    }
}
void move (ThreeDArray* tower, int start, int end) {
    int slice = tower->get_slice() - 1;
    int disk_to_move = 0;
    int start_index = tower->get_column() - 1;

    while (start_index >= 0 && disk_to_move == 0) {
        if (tower->at(slice, start, start_index) != 0) {
            if (start_index == 0 || tower->at(slice, start, start_index - 1) == 0) {
                disk_to_move = tower->at(slice, start, start_index);
                tower->at(slice, start, start_index) = 0;
            }
        }
        start_index--;
    }

    int end_index = tower->get_column() - 1;
    int current = 0;
    while (end_index >= 0 && current == 0) {
        if (tower->at(slice, end, end_index) == 0) {
            tower->at(slice, end, end_index) = disk_to_move;
            current = 1;
        }
        end_index--;

    }
    display_board(tower);
}

int main() {
    int disks = 10;
    tower_of_hannoi(disks);

    return 0;
}
/*
1 0 0   0 0 0
2 0 0   2 0 0
3 0 0   3 1 0
*/