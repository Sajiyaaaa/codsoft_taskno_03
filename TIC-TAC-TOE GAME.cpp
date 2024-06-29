#include <iostream>
#include <string>

using namespace std;


// Game Settings
const int rows = 10;
const int columns = 10;

const int win_combo_required = 5;


void display_game(string grid[rows][columns]) {
    for (int  i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << grid[i][j] << "\t";
        }
        cout << endl;
    }
}

void switchPlayer(int& player) {
    if (player == 0) player = 1;
    else if (player == 1) player = 0;
    else {
        cout << "Invalid Player Entered!" << endl; 
    }
}

bool play_move(string grid[rows][columns], int player, int pos) {
    string selected_pos = grid[pos/rows][pos%columns];
    if (selected_pos == "X" || selected_pos == "O") return false;

    string mark = "\0";
    if (player == 0) mark = "X";
    else if (player == 1) mark = "O";
    else {
        cout << "Wrong Player!" << endl;
        return false;
    }

    grid[pos/rows][pos%columns] = mark;
    return true;
}

// Return values
// -1 = No one Won
// 0 = Player 1 Won
// 1 = Player 2 Won
int check_win(string grid[rows][columns], int player) {
    string mark;

    bool won = false;

    if      (player == 0)   mark = "X";
    else if (player == 1)   mark = "O";

    bool is_same;

    // Rows
    is_same = true;
    for (int i = 0; i < rows && !won; i++) {
        for (int j = 0; j < columns - (win_combo_required-1) && !won; j++) {
            if (grid[i][j] == mark) {
                for (int k = 0; k < win_combo_required && is_same; k++) {
                    if (grid[i][j+k] != mark) {
                        is_same = false;
                    }
                }

                if (is_same) {
                    won = true;
                }
            }
        }
    }

    // Columns
    is_same = true;
    for (int j = 0; j < columns && !won; j++) {
        for (int i = 0; i < rows - (win_combo_required-1) && !won; i++) {
            if (grid[i][j] == mark) {
                for (int k = 0; k < win_combo_required && is_same; k++) {
                    if (grid[i+k][j] != mark) {
                        is_same = false;
                    }
                }

                if (is_same) {
                    won = true;
                }
            }
        }
    }

    // Diagonal Front
    is_same = true;
    for (int i = 0; i < rows-(win_combo_required-1) && !won; i++) {
        for (int j = 0; j < columns - (win_combo_required-1) && !won; j++) {
            if (grid[i][j] == mark) {
                for (int k = 0; k < win_combo_required && is_same; k++) {
                    if (grid[i+k][j+k] != mark) {
                        is_same = false;
                    }
                }
                if (is_same) {
                    won = true;
                }
            }
        }
    }


    // Diagonal Back
    is_same = true;
    for (int i = 0; i < rows - (win_combo_required-1) && !won; i++) {
        for (int j = (win_combo_required-1); j < columns && !won; j++) {
            if (grid[i][j] == mark) {
                for (int k = 0; k < win_combo_required && is_same; k++) {
                    if (grid[i+k][j-k] != mark) {
                        is_same = false;
                    }
                }
                if (is_same) {
                    won = true;
                }
            }
        }
    }



    if (won) {
        if (player == 0) return 0;
        else if (player == 1) return 1;
    }

    return -1;
}

int main() 
{
        string playerNames[2];

        cout << "Welcome to Tic Tac Toe !" << endl;
        cout << endl;

        cout << "Enter the name of Player 1: ";
        cin >> playerNames[0];

        cout << "Enter the name of Player 2: ";
        cin >> playerNames[1];

        cout << endl;

    // 0 = X
    // 1 = O
    int player = 0;

    string grid[rows][columns];

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            grid[i-1][j-1] = to_string((i-1)*rows + j);
        }
    }

        display_game(grid);

        cout << endl << "Let's Start Game !" << endl;

    int position;


    // Game Loop
        for (int count = 0; count < rows * columns - 1; count++) {
                cout << "Its " << playerNames[player] << " turn Enter where you want to put pos: ";
        take_input:
        do {
            cin >> position;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Not a number! Try again: ";
                cin >> position;
            }
            position--;

            if (position >= 0 && position <= rows * columns - 1) break;
            cout << "Invalid Move! Try again: ";

        } while (true);

        while (!play_move(grid, player, position)) {
            cout << "Box Already Filled! Try again: ";
            goto take_input;
        }

        display_game(grid);

        if (check_win(grid, player) != -1) {
            cout << playerNames[player] << " has Won!" << endl;
            return 0;
        }
        switchPlayer(player);

    }

        cout << "Its a Draw ! A good Game !";
        return 0;
}