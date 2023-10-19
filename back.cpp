#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> twoVec;
using namespace std;
//connect4 game to learn something about polymorphimzm and inheritance
//code uses polimorphism and inheritance


class Player{
    //create players
    public:
        string name = "";
        int num = 0;
        Player() = default;
        Player(string name, int num){
            this -> name = name;
            this -> num = num;
        }
        string get_name(){
            return name;
        }
        int get_num(){
            return num;
        }
};

class Play : protected Player{
    private:

        //initialize board
        twoVec get_board(){
            twoVec board{
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
            };
            return board;
        }
        //create players
        Player get_player(int sign){
            string name;
            cout << "Select player " <<  sign << " name -> ";
            cin >> name;
            cout << endl;
            return Player(name, sign);
        }
        //turns
        Player get_turn(Player players[2], int turn){
            return players[turn % 2];
        }
        //print board method
        void print_board(twoVec board){
            cout << "-0--1--2--3--4--5--6-" << endl;
            for (int i = 0; i < board.size(); i++){
                for (int j = 0; j < board[i].size(); j++){
                    cout << "|" << board[i][j] << "|";
                }    
                cout << endl;
            }
            cout << "---------------------" << endl;
        }
        
        twoVec update_board(twoVec board, int sign){
            twoVec b = board;
            int choose;
            bool check = 0;

            //choose column number
            while (true){
                cout << "Choose number of column (0-6): ";
                cin >> choose;
                cout << endl;
                if ((choose <= 6) && (choose >= 0))
                    if (b[0][choose] == 0)
                        break;
                else{
                    cout << "Invalid input" <<endl;
                }
            }

            //add on stack
            for (int i = 5; i <= 5; i--){
                if (b[i][choose] == 0){
                    b[i][choose] = sign;
                    break;
                }
            }

            return b;
        }

        bool check_win(twoVec board){
            //Can I make it prettier? Is it necessary? Do I even care?
            //vertical
            for(int i = 0; i <= 5; i++){
                for(int j = 0; j <= 3; j++){
                    if((board[i][j] == board[i][j+1]) && (board[i][j] == board[i][j+2]) && (board[i][j] == board[i][j+3]) && (board[i][j] != 0))
                        return true;
                }
            }
            //horizontal
            for(int j = 0; j <= 6; j++){
                for(int i = 0; i <= 2; i++){
                    if((board[i][j] == board[i+1][j]) && (board[i][j] == board[i+2][j]) && (board[i][j] == board[i+3][j]) && (board[i][j] != 0))
                        return true;
                }
            }
            //up to down diagonal
            for(int i = 0; i <= 2; i++){
                for(int j = 0; j <= 3; j++){
                    if((board[i][j] == board[i+1][j+1]) && (board[i][j] == board[i+2][j+2]) && (board[i][j] == board[i+3][j+3]) && (board[i][j] != 0))
                        return true;
                }
            }
            //down to up diagonal
            for(int i = 5; i >= 3; i--){
                for(int j = 0; j <= 3; j++){
                    if((board[i][j] == board[i-1][j+1]) && (board[i][j] == board[i-2][j+2]) && (board[i][j] == board[i-3][j+3]) && (board[i][j] != 0))
                        return true;
                }
            }
            return false;
        }

        bool check_tie(twoVec board){
            for(int i = 0; i <= 5; i++){
                for(int j = 0; j <= 6; j++){
                    if(board[i][j] == 0)
                        return false;
                }
            }
            return true;
        }

        //gameloop
        int game_loop(Player players[2], Player* players_pointer, bool* restet_signal_pointer){
            string answer;
            bool reset_signal;
            int turn = 0;
            twoVec board = get_board();
            while (true){
                Player current_player = get_turn(players, turn);
                cout<< current_player.get_name() << endl;
                print_board(board);
                board = update_board(board, current_player.get_num());
                if (check_win(board)){
                    print_board(board);
                    cout << "Winner: " << current_player.get_name() << endl;
                    cout << "Reset? (yes/no) -> ";
                    cin >> answer;
                    while (true){
                        if ((answer == "no") || (answer == "No") || (answer == "n") || (answer == "N")){
                            reset_signal = false;
                            *restet_signal_pointer = reset_signal;
                            return 0;
                        }
                        else if ((answer == "yes") || (answer == "Yes") || (answer == "y") || (answer == "Y")){
                            *players_pointer = players[2];
                            reset_signal = true;
                            *restet_signal_pointer = reset_signal;
                            return 0;
                        }
                        else{
                            cout << "Invalid input" << endl;
                            return 0;
                        }
                    }
                }
                if(check_tie(board)){
                    print_board(board);
                    cout << "Tie" << endl;
                    cout << "Reset? (yes/no) -> ";
                    cin >> answer;
                    while (true){
                        if ((answer == "no") || (answer == "No") || (answer == "n") || (answer == "N")){
                            reset_signal = false;
                            *restet_signal_pointer = reset_signal;
                            return 0;
                        }
                        else if ((answer == "yes") || (answer == "Yes") || (answer == "y") || (answer == "Y")){
                            *players_pointer = players[2];
                            reset_signal = true;
                            *restet_signal_pointer = reset_signal;
                            return 0;
                        }
                        else{ 
                            cout << "Invalid input" << endl;
                            return 0;
                        }
                    }
                }
                turn++;
            }
        }
    public:
        //main game function
        void play(){
            Player player1 = get_player(1);
            Player player2 = get_player(2);
            Player players[2] = {player1, player2}, players_pointer;
            bool reset_signal_pointer = true;

            while (reset_signal_pointer){
                game_loop(players, &players_pointer, &reset_signal_pointer);
            }
        }
};



int main(){
    //start game
    Play myGame;
    myGame.play();
    
    return 0;
}