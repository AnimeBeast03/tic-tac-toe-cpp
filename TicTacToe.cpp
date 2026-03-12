#include <iostream>
#include <termios.h>    // to perform backend
#include <unistd.h>     // same
#include <random>       // random cpu input
#include <limits>       // no extra input
using namespace std;



class gameBox {
    private :
        //variables
        int menuOption = 0;
        int gameMode = 0;
        int cursorPosition = 21; //21 mobile 39 pc
        int totalGameRounds = 9;
        int tossWinner = 0;
        string emptyInput;
        string previousWinner = "";
        string winner = "";
        string gameBoard[3][3] = {
                {" "," "," "},
                {" "," "," "},
                {" "," "," "},
            };
    public :
        //sub functions
        void clearScreen();
        void drawTitle();
        void showInstructions(int r);
        void printGameMenu();
        void performBackend();
        void drawGrid();
        void takePlayerInput(string mark = "X");
        void takeCpuInput();
        void checkIfWinning();
        void performToss();
        void gameReset();
        //main functions
        void introPage();
        void gameLoop();
};



//clears the screen
void gameBox::clearScreen() {
    cout << "\033[2J\033[H";
}
//draws title with instructions
void gameBox::showInstructions(int r) {
    // left spacing variable
    int marginLeft = 5;
    // left spacing
    for (int k=1; k<=marginLeft; k++) {
        cout << " ";
    }
    // print instructions
    if (r == 4) {
      cout << "X. Single-Player Mode ~";
    }
    else if (r == 7) {
      cout << "1. Player is X, CPU is O.";
    }
    else if (r == 8) {
      cout << "2. Player always starts the first match.";
    }
    else if (r == 9) {
      cout << "3. An empty 3×3 board is shown.";
    }
    else if (r == 10) {
      cout << "4. Player places X in any empty space.";
    }
    else if (r == 11) {
      cout << "5. CPU places O on its turn.";
    }
    else if (r == 12) {
      cout << "6. Turns continue one by one.";
    }
    else if (r == 13) {
      cout << "7. Three marks in a r wins the game.";
    }
    else if (r == 14) {
      cout << "8. rs can be horizontal, vertical, or diagonal.";
    }
    else if (r == 15) {
      cout << "9. If all spaces fill with no winner, it is a draw.";
    }
    else if (r == 16) {
      cout << "10. On replay, previous match winner starts next game; if draw, player starts again.";
    }
    else if (r == 19) {
      cout << "O. Multi-Player Mode ~";
    }
    else if (r == 22) {
      cout << "1. Two human players join the game.";
    }
    else if (r == 23) {
      cout << "2. Both players agree to play Tic Tac Toe.";
    }
    else if (r == 24) {
      cout << "3. A toss is done to decide first player.";
    }
    else if (r == 25) {
      cout << "4. Toss winner gets X and plays first.";
    }
    else if (r == 26) {
      cout << "5. Toss loser gets O and plays next.";
    }
    else if (r == 27) {
      cout << "6. Players take turns using empty spaces.";
    }
    else if (r == 28) {
      cout << "7. Three marks in a row wins the game.";
    }
    else if (r == 29) {
      cout << "8. Winning row can be horizontal, vertical, or diagonal.";
    }
    else if (r == 30) {
      cout << "9. If the board fills with no winner, it is a draw.";
    }
    else if (r == 31) {
      cout << "10. On replay, previous winner starts next game; if draw, toss is done again.";
    }
}
void gameBox::drawTitle() {
    // letter spacings
    int t = 1;
    int i = 22;
    int ce = 35;
    int ao = 17;
    int marginLeft = 5;
    // clear screen
    clearScreen();
    // print title
    for (int r=-1; r<=36; r++) {
    	// draw required symbols
        for (int k=((marginLeft*-1)+1); k<=46; k++) {
            if (
                // draw T
                ((r==1||r==13||r==25)&&(k>=t+1&&k<=t+13)) ||
                ((r==3||r==15||r==27)&&(k>=t+1&&k<=t+5)) ||
                ((r==3||r==15||r==27)&&(k>=t+9&&k<=t+13)) ||
                ((r==10||r==22||r==34)&&(k>=t+6&&k<=t+8)) ||
                // draw I
                ((r==1||r==3||r==5||r==10)&&(k>=i+1&&k<=i+3)) ||
                // draw C
                ((r==3||r==10||r==15||r==22)&&((k==ce+3)||(k>=ce+4&&k<=ce+9))) ||
                ((r==5||r==8||r==17||r==20)&&(k>=ce+6&&k<=ce+9)) ||
                // draw A
                ((r==15||r==22)&&((k==ao+3)||(k>=ao+4&&k<=ao+9))) ||
                ((r==17||r==20)&&(k>=ao+5&&k<=ao+9)) ||
                ((r==15||r==22)&&(k>=ao+11&&k<=ao+13)) ||
                // draw O
                ((r==27||r==34)&&(k==ao+3||(k>=ao+4&&k<=ao+11))) ||
                ((r==29||r==32)&&(k>=ao+5&&k<=ao+9)) ||
                // draw E
                (r==27&&(k>=ce+3&&k<=ce+9)) ||
                (r==34&&(k>=ce+3&&k<=ce+10)) ||
                ((r==30||r==32)&&(k>=ce+5&&k<=ce+10))
            ) { cout << "-"; }
            else if (
                // draw T
                ((r==2||r==14||r==26)&&(k==t||k==t+14)) ||
                ((r>=4&&r<=9)&&(k==t+5||k==t+9)) ||
                ((r>=16&&r<=21)&&(k==t+5||k==t+9)) ||
                ((r>=28&&r<=33)&&(k==t+5||k==t+9)) ||
                // draw I
                ((r==2||(r>=6&&r<=9))&&(k==i||k==i+4)) ||
                // draw C
                ((r==6||r==7||r==18||r==19)&&(k==ce+4||k==ce)) ||
                ((r==4||r==9||r==16||r==21)&&(k==ce+10)) ||
                // draw A
                ((r==18||r==19)&&(k==ao+10||k==ao+4||k==ao)) ||
                ((r>=16&&r<=21)&&(k==ao+14)) ||
                // draw O
                ((r==30||r==31)&&(k==ao+10||k==ao+4||k==ao||k==ao+14)) ||
                // draw E
                (r==30&&k==ce) ||
                (r==31&&(k==ce+4||k==ce)) ||
                ((r==33||r==29)&&k==ce+11)
            ) { cout << "|"; }
            else if (
                // draw C
                (((r==5||r==17)&&k==ce)||((r==4||r==16)&&k==ce+1)) ||
                // draw A
                ((r==17&&k==ao)||(r==16&&k==ao+1)) ||
                // draw O
                ((r==32&&k==ao+14)||(r==33&&k==ao+13)) ||
                ((r==29&&k==ao)||(r==28&&k==ao+1)) ||
                // draw E
                ((r==29&&k==ce)||(r==28&&k==ce+1))
            ) { cout << "/"; }
            else if (
                // draw C
                (((r==8||r==20)&&k==ce)||((r==9||r==21)&&k==ce+1)) ||
                // draw A
                ((r==20&&k==ao)||(r==21&&k==ao+1)) ||
                // draw O
                ((r==29&&k==ao+14)||(r==28&&k==ao+13)) ||
                ((r==32&&k==ao)||(r==33&&k==ao+1)) ||
                // draw E
                ((r==28&&k==ce+11)||(r==32&&k==ce)||(r==33&&k==ce+1))
            ) { cout << "\\"; }
            else if (
                // draw E
                (r==28&&(k>=ce+5&&k<=ce+7))
            ) { cout << "_"; }
            else { cout << " "; }
        }
		// show instruction based on each line
		showInstructions(r);
        cout << "\n";
    }
}
//shows game menu
void gameBox::performBackend() {
    // customize terminal settings (disable Canonical Mode)
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // perform detection loop
    while (true) {
        char ch = getchar();
        // if any Escape keys are found in input
        if (ch == 27) {
            ch = getchar();
            // if arrow keys are pressed
            if (ch == '[') {
                ch = getchar();
                // if UP arrow key is pressed
                if (ch == 'A') {
                	// change game mode according to menu type
                    if (menuOption == 1 || menuOption == 2) {
	                    gameMode = 1;
	                    menuOption = 1;
                    }
                    if (menuOption == 3 || menuOption == 4) {
	                    menuOption = 3;
                    }
					// mover cursor to 1st option
					printf("\033[%d;%df", cursorPosition, 55);
                }
                // if DOWN arrow key is pressed
                if (ch == 'B') {
                    // change game mode according to menu type
                    if (menuOption == 1 || menuOption == 2) {
                        gameMode = 2;
                        menuOption = 2;
                    }
                    if (menuOption == 3 || menuOption == 4) {
                        menuOption = 4;
                    }
                    // mover cursor to 2nd option
                    printf("\033[%d;%df", cursorPosition+1, 55);
                }
            }
        }
		else {
			// if pressed Enter
            if (ch == '\n' || ch == '\r') {
            	// fix errors and leave
                if (gameMode == 0) gameMode = 1;
                if (menuOption == 0) menuOption = 1;
                break;
            }
        }
    }
	// restore old terminal settings (enable Canonical Mode)
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
void gameBox::printGameMenu() {
    // print menu
    while (true) {
    	// print empty spaces
        for (int k=0;k<=60;k++) {
            cout << " ";
        }
        // print menu items according to on what lines
        if (menuOption == 0) {
            cout << "[Press Enter To Start]";
            cout << "\033[" << 55 << "G";
            performBackend();
            drawTitle();
        }
        else if (menuOption == 1) {
            cout << "[Single  Player]\n";
            menuOption = 2;
        }
        else if (menuOption == 2) {
            cout << " [Multi Player]\n";
            menuOption = 1;
            printf("\033[%d;%df", cursorPosition, 55);
            performBackend();
            break;
        }
        else if (menuOption == 3) {
            cout << "[Play Again]\n";
            menuOption = 4;
        }
        else if (menuOption == 4) {
            cout << "[Main  Menu]\n";
            menuOption = 3;
            printf("\033[%d;%df", cursorPosition, 55);
            performBackend();
            break;
        }
    }
}
//draw grid
void gameBox::drawGrid() {
    cout << "\n";
    for (int i=0;i<3;i++) {
        cout << " ";
        for (int k=0;k<3;k++) {
            if (k<2) {
                cout << " " << gameBoard[i][k] << " |";
            } else {
                cout << " " << gameBoard[i][k] << " \n";
            }
        }
        if (i<2) {
            cout << " ---+---+---\n";
        }
    }
    cout << "\n";
}
//process input
void gameBox::takePlayerInput(string mark) {
    //variables
    int playerRow;
    int playerColumn;
    //take and check player input
    while (totalGameRounds != 0) {
        // take input
        cout << "Select a Row : ";
        cin >> playerRow;
        cout << "Select a Column : ";
        cin >> playerColumn;
        // if alphabet input then skip that round
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\nNo Alphabets Allowed. Try again.\n";
            cout << "[Press Enter]";
            getline(cin,emptyInput);
            clearScreen();
            cout << "Rounds Left : " << totalGameRounds << "\n";
            drawGrid();
            continue;
        }
        // if inside range then make it valid
        if (
            (playerRow >= 1 && playerRow <= 3) &&
            (playerColumn >= 1 && playerColumn <= 3)
        )
        {
            //if desired space is empty
            if (gameBoard[playerRow-1][playerColumn-1] == " ") {
                gameBoard[playerRow-1][playerColumn-1] = mark;
                totalGameRounds--;
                break;
            }
            else {
                cout << "\n\nAlready Occupied. Try Again.\n";
                cout << "[Press Enter]";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,emptyInput);
                clearScreen();
                cout << "Rounds Left : " << totalGameRounds << "\n";
                drawGrid();
            }
        }
        else {
            cout << "\n\nOut Of Range. Try again.\n";
            cout << "[Press Enter]";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,emptyInput);
            clearScreen();
            cout << "Rounds Left : " << totalGameRounds << "\n";
            drawGrid();
        }
    }
}
void gameBox::takeCpuInput() {
    // create random cpu row and column every round
    while (totalGameRounds != 0) {
        //generate random number
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(1,3);
        int cpuRow = dist(gen);
        int cpuColumn = dist(gen);
        //check input
        if (gameBoard[cpuRow-1][cpuColumn-1] == " ") {
            gameBoard[cpuRow-1][cpuColumn-1] = "O";
            totalGameRounds--;
            break;
        }
    }
}
void gameBox::checkIfWinning() {
    // marks
    string mark1 = "X";
    string mark2 = "O";
    // check rows
    for (int i=0;i<3;i++) {
        if (
            (gameBoard[i][0] == mark1) &&
            (gameBoard[i][1] == mark1) &&
            (gameBoard[i][2] == mark1)
        ) {winner=mark1;break;}
        if (
            (gameBoard[i][0] == mark2) &&
            (gameBoard[i][1] == mark2) &&
            (gameBoard[i][2] == mark2)
        ) {winner=mark2;break;}
    }
    // check columns
    for (int i=0;i<3;i++) {
        if (
            (gameBoard[0][i] == mark1) &&
            (gameBoard[1][i] == mark1) &&
            (gameBoard[2][i] == mark1)
        ) {winner=mark1;break;}
        if (
            (gameBoard[0][i] == mark2) &&
            (gameBoard[1][i] == mark2) &&
            (gameBoard[2][i] == mark2)
        ) {winner=mark2;break;}
    }
    // check diagonals
    if (
        gameBoard[0][0] == mark1 &&
        gameBoard[1][1] == mark1 &&
        gameBoard[2][2] == mark1
    ) {winner=mark1;}
    if (
        gameBoard[0][2] == mark1 &&
        gameBoard[1][1] == mark1 &&
        gameBoard[2][0] == mark1
    ) {winner=mark1;}
    if (
        gameBoard[0][0] == mark2 &&
        gameBoard[1][1] == mark2 &&
        gameBoard[2][2] == mark2
    ) {winner=mark2;}
    if (
        gameBoard[0][2] == mark2 &&
        gameBoard[1][1] == mark2 &&
        gameBoard[2][0] == mark2
    ) {winner=mark2;}
}
//perform toss
void gameBox::performToss() {
    // variables
    char choice;
    int result;
    //msg
    clearScreen();
    cout << "Both players, get ready!\n";
    cout << "Time to decide who starts first.\n\n";
    cout << "[Press Enter to Start]";
    getline(cin,emptyInput);
    //input loop
    while (true) {
        clearScreen();
        cout << "Player 1, make your call.\nChoose Heads or Tails.\n";
        cout << "\n[Type H/T] : ";
        cin >> choice;
        choice = tolower(choice);
        //if valid input then break
        if (choice == 'h' || choice == 't') {
            clearScreen();
            cout << "\nFlipping the Coin...\n";
            break;
        }
        //else taje input again
        else {
            cout << "\nOnly Type Letter 'H' OR Letter 'T'.\n";
            cout << "Try Again.\n\n";
            cout << "[Press Enter]";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,emptyInput);
        }
    }
    //generate random number
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0,1);
    result = dist(gen);
    //if 0 - heads
    if (result == 0) {
        cout << "\nIt's HEADS!\n";
        if (choice == 'h') {
            tossWinner = 1;
            cout << "\nPlayer 1 wins the toss!\nYou will make the First move.";
        }
        if (choice == 't') {
            tossWinner = 2;
            cout << "\nPlayer 2 wins the toss!\nHe will start First.";
        }
    }
    //if 1 - tails
    else {
        cout << "\nIt's TAILS!\n";
        if (choice == 't') {
            tossWinner = 1;
            cout << "\nPlayer 1 wins the toss!\nYou start First.";
        }
        if (choice == 'h') {
            tossWinner = 2;
            cout << "\nPlayer 2 wins the toss!\nHe will make the First move.";
        }
    }
    //outro
    cout << "\n\n[Press Enter to Start The Game]";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,emptyInput);
}
//game reset
void gameBox::gameReset() {
	//reset all data to default
    totalGameRounds = 9;
    previousWinner = winner;
    winner = "";
    //reset the game board
    for(int r=0;r<3;r++) {
        for(int k=0;k<3;k++) {
            gameBoard[r][k] = " ";
        }
    }
}



//game intro page
void gameBox::introPage() {
    drawTitle();
    printGameMenu();
}
//game loop
void gameBox::gameLoop() {
    while (true) {
        // single player mode
        if (gameMode == 1 && menuOption == 1) {
            // if spaces left on game board
            if (totalGameRounds > 0) {
                clearScreen();
                cout << "Rounds Left : " << totalGameRounds << "\n";
                drawGrid();
                takePlayerInput();
                checkIfWinning();
                if (winner == "X") {
                    clearScreen();
                    drawGrid();
                    cout << "GG! You Won the Game.\n";
                    cout << "\n[Press Enter]";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,emptyInput);
                    gameReset();
                    menuOption = 3;
                    introPage();
                    continue;
                }
                takeCpuInput();
                checkIfWinning();
                if (winner == "O") {
                    clearScreen();
                    drawGrid();
                    cout << "Oops! Game is Over.\n";
                    cout << "\n[Press Enter]";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,emptyInput);
                    gameReset();
                    menuOption = 3;
                    introPage();
                    continue;
                }
            }
            else {
                clearScreen();
                drawGrid();
                cout << "\nIts a Draw.\n";
                cout << "[Press Enter]";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,emptyInput);
                gameReset();
                menuOption = 3;
                introPage();
                continue;
            }
        }
        // multi player mode
        if (gameMode == 2 && menuOption == 2) {
            //decide who starts first
            if (tossWinner == 0) {
                performToss();
            }
            // start playing 
            if (tossWinner == 1) {
                if (totalGameRounds > 0) {
                    clearScreen();
                    cout << "Rounds Left : " << totalGameRounds << "\n";
                    drawGrid();
                    cout << "Player 1's turn -\n\n";
                    takePlayerInput("X");
                    checkIfWinning();
                    if (winner == "X") {
                        clearScreen();
                        drawGrid();
                        cout << "GG Guyz! The match is Over.\n";
                        cout << "Player 1 is the Winner!\n";
                        cout << "\n[Press Enter]";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin,emptyInput);
                        gameReset();
                        menuOption = 3;
                        introPage();
                        continue;
                    }
                    clearScreen();
                    cout << "Rounds Left : " << totalGameRounds << "\n";
                    drawGrid();
                    cout << "Player 2's turn -\n\n";
                    takePlayerInput("O");
                    checkIfWinning();
                    if (winner == "O") {
                        clearScreen();
                        drawGrid();
                        cout << "GG Guyz! The match is Over.\n";
                        cout << "Player 2 is the Winner!\n";
                        cout << "\n[Press Enter]";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin,emptyInput);
                        gameReset();
                        menuOption = 3;
                        introPage();
                        continue;
                    }
                }
                else {
                    clearScreen();
                    drawGrid();
                    cout << "\nIts a Draw.\n";
                    cout << "[Press Enter]";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,emptyInput);
                    gameReset();
                    tossWinner = 0;
                    menuOption = 3;
                    introPage();
                    continue;
                }
            }
            if (tossWinner == 2) {
                if (totalGameRounds > 0) {
                    clearScreen();
                    cout << "Rounds Left : " << totalGameRounds << "\n";
                    drawGrid();
                    cout << "Player 2's turn -\n\n";
                    takePlayerInput("X");
                    checkIfWinning();
                    if (winner == "X") {
                        clearScreen();
                        drawGrid();
                        cout << "GG Guyz! The match is Over.\n";
                        cout << "Player 2 is the Winner!\n";
                        cout << "\n[Press Enter]";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin,emptyInput);
                        gameReset();
                        menuOption = 3;
                        introPage();
                        continue;
                    }
                    clearScreen();
                    cout << "Rounds Left : " << totalGameRounds << "\n";
                    drawGrid();
                    cout << "Player 1's turn -\n\n";
                    takePlayerInput("O");
                    checkIfWinning();
                    if (winner == "O") {
                        clearScreen();
                        drawGrid();
                        cout << "GG Guyz! The match is Over.\n";
                        cout << "Player 1 is the Winner!\n";
                        cout << "\n[Press Enter]";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin,emptyInput);
                        gameReset();
                        menuOption = 3;
                        introPage();
                        continue;
                    }
                }
                else {
                    clearScreen();
                    drawGrid();
                    cout << "\nIts a Draw.\n";
                    cout << "[Press Enter]";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,emptyInput);
                    gameReset();
                    tossWinner = 0;
                    menuOption = 3;
                    introPage();
                    continue;
                }
            }
        }
        // single player - play again
        if (gameMode == 1 && menuOption == 3) {
            // if cpu wins last round then it start first
            if (previousWinner == "O") {
                // if spaces left on game board
                if (totalGameRounds > 0) {
                    clearScreen();
                    takeCpuInput();
                    checkIfWinning();
                    if (winner == "O") {
                        clearScreen();
                        drawGrid();
                        cout << "Oops! Game is Over.\n";
                        cout << "\n[Press Enter]";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin,emptyInput);
                        gameReset();
                        menuOption = 3;
                        introPage();
                        continue;
                    }
                    cout << "Rounds Left : " << totalGameRounds << "\n";
                    drawGrid();
                    takePlayerInput();
                    checkIfWinning();
                    if (winner == "X") {
                        clearScreen();
                        drawGrid();
                        cout << "GG! You Won the Game.\n";
                        cout << "\n[Press Enter]";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin,emptyInput);
                        gameReset();
                        menuOption = 3;
                        introPage();
                        continue;
                    }
                }
                else {
                    clearScreen();
                    drawGrid();
                    cout << "\nIts a Draw.\n";
                    cout << "[Press Enter]";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,emptyInput);
                    gameReset();
                    menuOption = 3;
                    introPage();
                    continue;
                }
            }
            else {
                menuOption = 1;
                continue;
            }
        }
        // multi player - play again
        if (gameMode == 2 && menuOption == 3) {
            if (tossWinner == 1) {
                if (previousWinner == "X") {
                    tossWinner = 1;
                    menuOption = 2;
                    continue;
                }
                if (previousWinner == "O") {
                    tossWinner = 2;
                    menuOption = 2;
                    continue;
                }
            }
            if (tossWinner == 2) {
                if (previousWinner == "X") {
                    tossWinner = 2;
                    menuOption = 2;
                    continue;
                }
                if (previousWinner == "O") {
                    tossWinner = 1;
                    menuOption = 2;
                    continue;
                }
            }
            if (tossWinner == 0) {
                tossWinner = 0;
                menuOption = 2;
                continue;
            }
        }
        // go back to main menu
        if (menuOption == 4) {
            // perform data reset and go to main menu
            gameReset();
            menuOption = 1;
            introPage();
        }
    }
}



int main() {
    gameBox game;
    game.introPage();
    game.gameLoop();
}





