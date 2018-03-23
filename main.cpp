#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <windows.h>

using namespace std;

//Prototypes
void gameOneP(); //132
void options(); //305
void gameTwoP(); //426
void drawTurnBoard(char[3][3], int, string); //569
void drawBoard(char[3][3], string); //647
short gameAIEasy(char[3][3]); //665
short gameAIMedium(char[3][3]); //681
short gameAIInsane(char[3][3]); //728
short minimax(char[3][3], short, bool); //767
short winCheck(char[3][3]); //834
bool playAgain(); //929
bool checkPos(short, char[3][3]); //945
string lowerCase(string); //958
short promptToMove(char[3][3]); //971
void drawMainMenu(int); //989
void drawAIMenu(int); //1013
void drawOptionsMenu(int); //1034
void drawPlayAgain(int);
short getRegionsX(short); //1111
short getRegionsY(short); //1123
void resetGame(char*[3]); //1129
void unitTestWinCheckHorizontal(); //1140
void unitTestWinCheckVertical(); //1179
void unitTestWinCheckDiagonal(); //1218
void unitTestWinCheckCats(); //1246
void unitTestAIWin(); //1264
void unitTestAIMiddle(); //1358
void unitTestAIBlock(); //1367
void unitTestMinimaxEndStates(); //1426
void unitTestGUI(); //1485
void assertion(string, bool); //1512

int sleep, scrollSpeed, compScore, playerScore, ties;
string cursor, cursorPick;

int main(int argc, char *argv[])
{
    
    compScore = 0;
    playerScore = 0;
    ties = 0;
    bool quit = false;
    short players = 0;
    short option = 0;
    string input = "";
    
    sleep = 150;
    scrollSpeed = 2;
    cursor = ">>";
    cursorPick = ">>";
    
   /*
    * This is a bit more of a complicated menu interface
    *  that runs a bit smoother and is infintely times
    *  more user friendly! It serves 2 purposes:
    *  1. limit player input
    *  2. create a menu that is easier to use.
    */
   while(true){
        
        system("CLS");
        drawMainMenu(option);
        
        while (true){
    
            if(GetAsyncKeyState( VK_UP ) & 0x8000 && option > 0){
                option--;
                drawMainMenu(option);
                Sleep(sleep);
            }   
    
            else if(GetAsyncKeyState( VK_DOWN ) & 0x8000 && option < 3){
                option++;
                drawMainMenu(option);
                Sleep(sleep);
            }
        
            else if(GetAsyncKeyState( VK_RETURN ) & 0x8000 && option == 0){
                Sleep(100);
                gameOneP();
                break;
            }
        
            else if(GetAsyncKeyState( VK_RETURN ) & 0x8000 && option == 1){
                Sleep(100);
                gameTwoP();
                break;
            }
        
            else if(GetAsyncKeyState( VK_RETURN ) & 0x8000 && option == 2){
                Sleep(100);
                options();
                break;
            }
        
            else if(GetAsyncKeyState( VK_RETURN ) & 0x8000 && option == 3){
                Sleep(100);
                quit = true;
                break;
            }
        }
        
        if(quit == true){
            Sleep(100);
            quit = false;
            break;
        }
    }
    
    //unitTestWinCheckHorizontal();
    //unitTestWinCheckVertical();
    //unitTestWinCheckDiagonal();
    //unitTestWinCheckCats();
    //unitTestAIWin();
    //unitTestAIMiddle();
    //unitTestAIBlock();
    //unitTestMinimaxEndStates();
    //unitTestGUI();
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

void gameOneP(){
     
     short whoseTurn = 2;
     short pOneMove = 0;
     short pTwoMove = 0;
     short whoWon = 3;
     short aiLevel = 0;
     short option = 0;
     bool again = true;
     bool emptyPos = false;
     bool chosen = false;
     bool gameEnd = false;
     
     string input = "";
     string name;
     string lowercaseName;
     char regions[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'*','*','*'}};
                   
     getline(cin, name);        
     system("CLS");
     cout << "Please input your name\n\n\n" << cursor << "\t";
     getline(cin, name);
     lowercaseName = lowerCase(name);
     system("CLS");
     
     if(lowercaseName == "obama" || lowercaseName == "barrack obama"){
         cout << "Welcome back Mr. President." << endl;
         system("PAUSE");
         Sleep(100);
     }
     
     drawAIMenu(option);
     
     while(true){
        
        chosen = false;
        
        //Another user friendly menu interface
        if(GetAsyncKeyState( VK_UP ) & 0x8000 && option > 0){
            option--;
            drawAIMenu(option);
            Sleep(sleep);
        }
        
        else if(GetAsyncKeyState( VK_DOWN ) & 0x8000 && option < 2){
            option++;
            drawAIMenu(option);
            Sleep(sleep);
        }
        
        else if(GetAsyncKeyState( VK_RETURN ) & 0x8000 && option == 0){
            aiLevel = 1;
            break;
        }
        
        else if(GetAsyncKeyState( VK_RETURN ) & 0x8000 && option == 1){
            aiLevel = 2;
            break;
        }
        
        else if(GetAsyncKeyState( VK_RETURN ) & 0x8000 && option == 2){
            aiLevel = 3;
            break;
        }
    }
     
     drawBoard(regions, "");
     
    while(true){ 
        while(true){
            
            if(again){ 
                //Using Pointers that point to pointer arrays
                //that point to a 2d array to reset the board
                char *change[3];
                *(change) = regions[0];
                *(change + 1) = regions[1];
                *(change + 2) = regions[2];
                char **ptr = &*change;
            
                resetGame(ptr);
                again = false;
                whoWon = 3;
                pOneMove = 0;
                pTwoMove = 0;
            }
          
            //If there is no current player's turn, randomly select a first turn
            if(whoseTurn == 2){
                srand(time(NULL));
                whoseTurn = rand() % 2;
            }
     
            system("PAUSE");
            Sleep(100);
          
            emptyPos = false;
          
            while(emptyPos == false){
                if(whoseTurn == 0){
                            
                            drawBoard(regions, "Player's Turn");
                            system("PAUSE");
                            Sleep(100);
                    
                            pOneMove = promptToMove(regions);
                    
                            emptyPos = checkPos(pOneMove, regions);
                    
                            //If the player's choice is empty: go there
                            if(emptyPos){
                                regions[getRegionsX(pOneMove)][getRegionsY(pOneMove)] = 'X';
                                whoseTurn = 1;
                            
                                /*cout << "Debug: player move success";
                                system("PAUSE");
                                Sleep(sleep);*/
                            }
                    
                            else if(!emptyPos){
                                cout << "That space is already taken! ";
                                system("PAUSE");
                                Sleep(100);
                            }
                        
                            /*cout << "Debug: player turn end";
                            system("PAUSE");
                            Sleep(sleep);*/
                        
                            drawBoard(regions, "Player's Turn");
                }
                else{
                        switch(aiLevel){
                            case 1:
                                pTwoMove = gameAIEasy(regions);
                                break;
                        
                            case 2:
                                pTwoMove = gameAIMedium(regions);
                                break;
                        
                            case 3:
                                pTwoMove = gameAIInsane(regions);
                                break;
                        }
                    
                        /*cout << "Debug: Computer Move";
                        system("PAUSE");
                        Sleep(sleep);*/
                    
                        //Place the AI's game piece
                        regions[getRegionsX(pTwoMove)][getRegionsY(pTwoMove)] = 'O';
                    
                        emptyPos = true;
                    
                        drawBoard(regions, "Computer's Turn");
                    
                        /*cout << "Debug: Computer turn end";
                        system("PAUSE");
                        Sleep(sleep);*/
                    
                        whoseTurn = 0;
                }
          
                whoWon = winCheck(regions);
          
                //All possible end game outcomes
                if( whoWon == 0){
                    cout << "Congratulations " << name << "! You win!" << endl;
                    Sleep(100);
                    again = playAgain();
                    gameEnd = true;
                    whoseTurn = 2;
                    playerScore++;
                }
          
                else if(whoWon == 1){
                    cout << "You lose!" << endl;
                    Sleep(100);
                    again = playAgain();
                    gameEnd = true;
                    whoseTurn = 2;
                    compScore++;
                }
          
                else if(whoWon == 2){
                    cout << "It was a Cat's Game! Nobody won!" << endl;
                    Sleep(100);
                    again = playAgain();
                    gameEnd = true;
                    whoseTurn = 2;
                    ties++;
                }
         
            drawBoard(regions, "");
            }
            if(gameEnd){
                Sleep(100);
                gameEnd = false;
                break;
            }
        }
        if(!again){
            Sleep(100);
            again = true;
            break;
        }
    }         
}

//Options Menu Controller
void options(){
    
    int option = 0;
    bool quit = false;
    
    while(true){
        system("CLS");
        drawOptionsMenu(option);
        
        while(true){
            
            if(GetAsyncKeyState(VK_UP) & 0x8000 && option > 0){
                option--;
                drawOptionsMenu(option);
                Sleep(sleep);
            }
    
            else if(GetAsyncKeyState(VK_DOWN) & 0x8000 && option < 3){
                option++;
                drawOptionsMenu(option);
                Sleep(sleep);
            }
    
            else if(GetAsyncKeyState(VK_LEFT) & 0x8000 && option == 0 && scrollSpeed > 0){
                sleep += 25;
                scrollSpeed--;
                drawOptionsMenu(option);
                Sleep(sleep);
            }
    
            else if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && option == 0 && scrollSpeed < 4){
                sleep -= 25;
                scrollSpeed++;
                drawOptionsMenu(option);
                Sleep(sleep);
            }
    
            else if(GetAsyncKeyState(VK_RETURN) & 0x8000 && option == 1){
                Sleep(150);
                playerScore = 0;
                compScore = 0;
                ties = 0;
                cout << "Your stats have been reset!";
                system("PAUSE");
            }
            
            else if(GetAsyncKeyState(VK_LEFT) & 0x8000 && option == 2){
                if(cursorPick == ">>"){
                    cursorPick = ":-";
                }
                else if(cursorPick == ":-"){
                    cursorPick = ")-";
                }
                else if(cursorPick == ")-"){
                    cursorPick = "o-";
                }
                else if(cursorPick == "o-"){
                    cursorPick = "--";
                }
                else if(cursorPick == "--"){
                    cursorPick = ":>";
                }
                else if(cursorPick == ":>"){
                    cursorPick = ")>";
                }
                else if(cursorPick == ")>"){
                    cursorPick = "O>";
                }
                else if(cursorPick == "O>"){
                    cursorPick = ">>";
                }
                drawOptionsMenu(option);
                Sleep(sleep);
            }
            
            else if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && option == 2){
                if(cursorPick == ">>"){
                    cursorPick = "O>";
                }
                else if(cursorPick == "O>"){
                    cursorPick = ")>";
                }
                else if(cursorPick == ")>"){
                    cursorPick = ":>";
                }
                else if(cursorPick == ":>"){
                    cursorPick = "--";
                }
                else if(cursorPick == "--"){
                    cursorPick = "o-";
                }
                else if(cursorPick == "o-"){
                    cursorPick = ")-";
                }
                else if(cursorPick == ")-"){
                    cursorPick = ":-";
                }
                else if(cursorPick == ":-"){
                    cursorPick = ">>";
                }
                drawOptionsMenu(option);
                Sleep(sleep);
            }
            
            else if(GetAsyncKeyState(VK_RETURN) & 0x8000 && option == 2){
                Sleep(150);
                cursor = cursorPick;
                drawOptionsMenu(option);
            }
            
            else if(GetAsyncKeyState(VK_RETURN) & 0x8000 && option == 3){
                Sleep(150);
                quit = true;
                break;
            }
        }
        
        if(quit == true){
            Sleep(100);
            quit = false;
            break;
        }
    }  
}

void gameTwoP(){
     
     short whoseTurn = 2;
     short pOneMove = 0;
     short pTwoMove = 0;
     short whoWon = 3;
     short option = 0;       
     bool again = true;
     bool emptyPos = false;
     bool gameEnd = false;
     
     string nameOne;
     string nameTwo;
     string lowercaseNameOne;
     string lowercaseNameTwo;
     char regions[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'*','*','*'}};
                           
     system("CLS");
     cout << "Player One Please input your name\n\n\n" << cursor << "\t";
     cin >> nameOne;
     cout << "Player Two Please input your name\n\n\n" << cursor << "\t";
     cin >> nameTwo;
     lowercaseNameOne = lowerCase(nameOne);
     lowercaseNameTwo = lowerCase(nameTwo);
     system("CLS");
     
     if(lowercaseNameOne == "obama" || lowercaseNameOne == "barrack obama"){
         cout << "Welcome back Mr. President." << endl;
         system("PAUSE");
     }
     
     if(lowercaseNameTwo == "obama" || lowercaseNameTwo == "barrack obama"){
         cout << "Welcome back Mr. President." << endl;
         system("PAUSE");
     }
     
     drawBoard(regions, "");
     
     while(true){
        while(true){
     
            if(again == 'y'){
              //Reseting the board again
              char *change[3];
              *(change) = regions[0];
              *(change + 1) = regions[1];
              *(change + 2) = regions[2];
              char **ptr = &*change;
            
              resetGame(ptr);
              again = 'a';
              whoWon = 3;
              pOneMove = 0;
              pTwoMove = 0;
            }
                 
          //Randomly selecting first turn again                     
          if(whoseTurn == 2){
               srand(time(NULL));
               whoseTurn = rand() % 2;
          }
     
          system("PAUSE");
          
          emptyPos = false;
          
          while(emptyPos == false){
               if(whoseTurn == 0){
                            
                    drawBoard(regions, "Player One");
                    system("PAUSE");
                    Sleep(100);
                    
                    pOneMove = promptToMove(regions);
                    
                    emptyPos = checkPos(pOneMove, regions);
                    
                    //If empty, go there
                    if(emptyPos){
                        regions[getRegionsX(pOneMove)][getRegionsY(pOneMove)] = 'X';
                        whoseTurn = 1;
                    }
                    
                    else{
                         cout << "That space is already taken! ";
                         system("PAUSE");
                         Sleep(100);
                    }
                    
                    drawBoard(regions, "Player One: Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
               }
               
               else{
                    drawBoard(regions, "Player Two: Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
                    system("PAUSE");
                    
                    pTwoMove = promptToMove(regions);
                    
                    emptyPos = checkPos(pTwoMove, regions);
                    
                    //If empty, go there
                    if(emptyPos){
                        regions[getRegionsX(pTwoMove)][getRegionsY(pTwoMove)] = 'O';
                        whoseTurn = 0;
                    }
                    
                    else{
                         cout << "That space is already taken! ";
                         system("PAUSE");
                         Sleep(100);
                    }
                    
                    drawBoard(regions, "Player Two");
              }
          
              whoWon = winCheck(regions);
          
              //All possible end game outcomes
              if(whoWon == 0){
                  cout << "Congratulations " << nameOne << "! You win!" << endl;
                  Sleep(100);
                  again = playAgain();
                  gameEnd = true;
                  whoseTurn = 2;
              }
          
              else if(whoWon == 1){
                  cout << "Congratulations " << nameTwo << "! You win!" << endl;
                  Sleep(100);
                  again = playAgain();
                  gameEnd = true;
                  whoseTurn = 2;
              }
          
              else if(whoWon == 2){
                   cout << "It was a Cat's Game! Nobody won!" << endl;
                   Sleep(100);
                   again = playAgain();
                   gameEnd = true;
                   whoseTurn = 2;
              }
          }
         
         drawBoard(regions, "");
         if(gameEnd){
                Sleep(100);
                gameEnd = false;
                break;
        }
        }
        if(!again){
            Sleep(100);
            again = true;
            break;
        }      
    }
}

//These functions draw the board in the console
void drawTurnBoard(char regions[3][3], int option, string text){
     
     char prospectiveRegions[3][3];
     
      for(short x = 0; x < 3; x++){
          for(short y = 0; y < 3; y++){
              prospectiveRegions[x][y] = regions[x][y];
          }
      }
     
     if(option == 1){
         prospectiveRegions[0][0] = ' ';
     }
    
     else if(option == 2){
         prospectiveRegions[0][1] = ' ';
     }
     
     else if(option == 3){
         prospectiveRegions[0][2] = ' ';
     }
     
     else if(option == 4){
         prospectiveRegions[1][0] = ' ';
     }
     
     else if(option == 5){
         prospectiveRegions[1][1] = ' ';
     }
     
     else if(option == 6){
         prospectiveRegions[1][2] = ' ';
     }
     
     else if(option == 7){
         prospectiveRegions[2][0] = ' ';
     }
     
     else if(option == 8){
         prospectiveRegions[2][1] = ' ';
     }
     
     else if(option == 9){
         prospectiveRegions[2][2] = ' ';
     }
     
     system("CLS");
     
     cout << text << "\n";
     cout << "Player: " << playerScore << "\tComputer: " << compScore << "\tCat Games: " << ties << "\n\n";
     
     for(short y=0; y<3; y++){
         for(short x=0; x<3; x++){
             cout << prospectiveRegions[y][x];
             if(x < 2){
                 cout << " | ";
             }
         }
         cout << endl;
         if(y < 2){
              cout << "--+---+--\n";
         }
     }
     
}

void drawBoard(char regions[3][3], string text){
    
    system("CLS");
    
    cout << text << "\n";
    cout << "Player: " << playerScore << "\tComputer: " << compScore << "\tCat Games: " << ties << "\n\n";
     
     for(short y=0; y<3; y++){
         for(short x=0; x<3; x++){
             cout << regions[y][x];
             if(x < 2){
                 cout << " | ";
             }
         }
         cout << endl;
         if(y < 2){
              cout << "--+---+--\n";
         }
     }
}

short gameAIEasy(char regions[3][3]){
    
    short moveAI;
    bool emptyPos = false;
    
    //Go in a random empty spot.
    while(!emptyPos){
        srand(time(NULL));
        moveAI = rand() % 9 + 1;
        
        emptyPos = checkPos(moveAI, regions);
    }
    
    return moveAI;
}

short gameAIMedium(char regions[3][3]){
      
      char prospectiveRegions[3][3];
      short moveAI = 0;
      bool emptyPos = false;
      
      //If middle is available, take it!
      if(checkPos(5, regions)){
          return 5;
      }
      
      //Assign values of regions array to prospectiveRegions
      for(short x = 0; x < 3; x++){
          for(short y = 0; y < 3; y++){
              prospectiveRegions[x][y] = regions[x][y];
          }
      }
      
      //Scans all possible moves
      for(short inc = 1; inc < 10; inc++){
           emptyPos = checkPos(inc, regions);
           
           if(emptyPos){
           
               //Check to see if there is a possible win. If so, take it.
               prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = 'O';
               if(winCheck(prospectiveRegions) == 1){
                   return inc;
               }
               
               prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = 'X';
               if(winCheck(prospectiveRegions) == 0){
                   moveAI = inc;
               }
               
               //If currently scanned move is not a win, don't go there.
               prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = '*'; 
           }
      }
      
      if(moveAI == 0){
            moveAI = gameAIEasy(regions);
      }
      
      return moveAI;
}

short gameAIInsane(char regions[3][3]){
    
    int value;
    int bestValue = -9999;
    short moveAI = 0;
    char prospectiveRegions[3][3];
    bool emptyPos = false;
 
    //If middle is available, take it!
    
    //Assign values of regions array to prospectiveRegions
    for(short x = 0; x < 3; x++){
        for(short y = 0; y < 3; y++){
            prospectiveRegions[x][y] = regions[x][y];
        }
    }
    
    //Scans all possible moves
    for(short inc = 1; inc < 10; inc++){
        emptyPos = checkPos(inc, regions);
           
        if(emptyPos){
           
            prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = 'O';
            value = minimax(prospectiveRegions, 1, false);
            
            if(value > bestValue){
                bestValue = value;
                moveAI = inc;
            }
            
            prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = '*'; 
        }
    }
 
    return moveAI;
    
}

short minimax(char regions[3][3], short depth, bool maximizingPlayer) {
    
    short evaluation;
    int val;
    int bestValue;
    char prospectiveRegions[3][3];
    bool emptyPos = false;
    
    evaluation = winCheck(regions);

    if (evaluation != 3) {
        // this is a final-state board
        if (evaluation == 0) {
           // X won
           return -1000 + depth;
        } else if (evaluation == 1) {
           // O won
           return 1000 - depth;
        } else {
           // Cat game
           return 0;
        }
    }
    
    //Assign values of regions array to prospectiveRegions
    for (short x = 0; x < 3; x++) {
        for (short y = 0; y < 3; y++) {
            prospectiveRegions[x][y] = regions[x][y];
        }
    }

    if (maximizingPlayer) {
        bestValue = -9999;

        for(short inc = 1; inc < 10; inc++){
             emptyPos = checkPos(inc, regions);
           
             if(emptyPos){
               prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = 'O';
               val = minimax(prospectiveRegions, depth + 1, false);
               bestValue = max(bestValue, val);
               //cout << "Max " <<  inc << " - " << val << " - " << bestValue << " - Depth: " << depth << endl;
               prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = '*';
             }
        }

        return bestValue;
    } else {
        bestValue = 9999;

        for(short inc = 1; inc < 10; inc++){
             emptyPos = checkPos(inc, regions);
           
             if(emptyPos){
               prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = 'X';
               val = minimax(prospectiveRegions, depth + 1, true);
               bestValue = min(bestValue, val);
               //cout << "Min " << inc << " - " << val << " - " << bestValue << " - Depth: " << depth << endl;
               prospectiveRegions[getRegionsX(inc)][getRegionsY(inc)] = '*';
             }
        }

        return bestValue;
    }
}

//This function checks for win states
short winCheck(char regions[3][3]){
      
    short backwards = 2;
    
    //Check Horizontal
    for(short x = 0; x < 3; x++){
        for(short i = 0; i < 3; i++){
            if(regions[x][i] == '*'){
                break;
            }
            if(i == 2 && regions[x][0] == regions[x][1] 
                && regions[x][1] == regions[x][2] 
                && regions[x][2] == 'X'){
                return 0;
            }
            else if(i == 2 && regions[x][0] == regions[x][1] 
                && regions[x][1] == regions[x][2] 
                && regions[x][2] == 'O'){
                return 1;
            }
        }
    }
    
    //Check Vertical
    for(short y = 0; y < 3; y++){
        for(short i = 0; i < 3; i++){
            if(regions[i][y] == '*'){
                break;
            }
            if(i == 2 && regions[0][y] == regions[1][y] 
                && regions[1][y] == regions[2][y] 
                && regions[2][y] == 'X'){
                return 0;
            }
            else if(i == 2 && regions[0][y] == regions[1][y] 
                && regions[1][y] == regions[2][y] 
                && regions[2][y] == 'O'){
                return 1;
            }
        }
    }
    
    //Check Diagonal
    for(short i = 0; i < 3; i++){
        if(regions[i][i] == '*'){
            break;
        }
        if(i == 2 && regions[0][0] == regions[1][1]
            && regions[1][1] == regions[2][2]
            && regions[2][2] == 'X'){
            return 0;
        }
        
        else if(i == 2 && regions[0][0] == regions[1][1]
            && regions[1][1] == regions[2][2]
            && regions[2][2] == 'O'){
            return 1;
        }
    }
        
    //Check Diagonal Backwards
    for(short i = 0; i < 3; i++){
       if(regions[backwards][i] == '*'){
           break;
       }
       if(i == 2 && regions[0][2] == regions[1][1]
           && regions[1][1] == regions [2][0]
           && regions[2][0] == 'X'){
           return 0;
       }
       else if(i == 2 && regions[0][2] == regions[1][1]
           && regions[1][1] == regions [2][0]
           && regions[2][0] == 'O'){
           return 1;
       }
       backwards--;
    }
    
    //Check for Cat's Game
    for(short y = 0; y < 3; y++){
        for(short x = 0; x < 3; x++){
            if(regions[x][y] == '*'){
                return 3;
            }
            if(y == 2 && x == 2){
                return 2;
            }
        }
    }
    
    //Nobody has won yet
    return 3;
}

//This function just asks if the player want's to play again
bool playAgain(){
     
     short option = 0;
     bool play;
     
     drawPlayAgain(option);
     
     while(true){
            if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && option == 0){
                option = 1;
                drawPlayAgain(option);
                Sleep(sleep);
            }
            
            else if(GetAsyncKeyState(VK_LEFT) & 0x8000 && option == 1){
                option = 0;
                drawPlayAgain(option);
                Sleep(sleep);
            }
            
            else if(GetAsyncKeyState(VK_RETURN) & 0x8000 && option == 0){
                Sleep(150);
                system("CLS");
                play = true;
                break;
            }
            
            else if(GetAsyncKeyState(VK_RETURN) & 0x8000 && option == 1){
                Sleep(150);
                system("CLS");
                play = false;
                break;
            }
    }
    
    return play;
}

//This function checks if a move is legal
bool checkPos(short move, char regions[3][3]){
     
     if(regions[getRegionsX(move)][getRegionsY(move)] == '*'){
          return true;
     }
     
     else{
          return false;
     }
     
}

//All for the easter egg
string lowerCase(string source){
 
    string lower;
 
    lower.resize(source.size());
    transform(source.begin(),
              source.end(),
              lower.begin(),
              ::tolower);
              
    return lower;
}

short promptToMove(char regions[3][3]){
 
    short option = 1;
    short thisTurn = 0;
    
    drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
    Sleep(sleep);
    drawBoard(regions, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
    Sleep(sleep);
    drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
    
    while(true){
        
        if(GetAsyncKeyState( VK_UP ) & 0x8000 && (option - 3) > 0){
            Sleep(sleep);
            option -= 3;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_DOWN ) & 0x8000 && (option + 3) < 10){
            Sleep(sleep);
            option += 3;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_LEFT ) & 0x8000 && option > 1 && option < 4){
            Sleep(sleep);
            option--;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_LEFT ) & 0x8000 && option > 3 && option < 7){
            Sleep(sleep);
            option--;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_LEFT ) & 0x8000 && option > 6){
            Sleep(sleep);
            option--;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_RIGHT ) & 0x8000 && option < 3){
            Sleep(sleep);
            option++;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_RIGHT ) & 0x8000 && option < 6 && option > 3){
            Sleep(sleep);
            option++;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_RIGHT ) & 0x8000 && option < 9 && option > 6){
            Sleep(sleep);
            option++;
            drawTurnBoard(regions, option, "Use the ARROW keys to navigate the board and the ENTER key to place a piece!");
        }
        
        else if(GetAsyncKeyState( VK_RETURN ) & 0x8000){
            thisTurn = option;
            break;
        }
    }
    
    return thisTurn;
}

//Draw functions for user friendly menu interfaces
void drawMainMenu(int option){
    
    system("CLS");
    
    cout << "Would you like to play 1 player or 2?\n\n\n";
 
     if(option == 0){
          cout << "" << cursor << "\tOne Player\n\tTwo Players\n\tOptions\n\tQuit" << endl;
     }
     
     else if(option == 1){
          cout << "\tOne Player\n" << cursor << "\tTwo Players\n\tOptions\n\tQuit" << endl;
     }
     
     else if(option == 2){
          cout << "\tOne Player\n\tTwo Players\n" << cursor << "\tOptions\n\tQuit" << endl;
     }
     
     else{
          cout << "\tOne Player\n\tTwo Players\n\tOptions\n" << cursor << "\tQuit" << endl;
     }
    
}

void drawAIMenu(int option){

    system("CLS");
    
    cout << "Which AI would you like to play against?\n\n" << endl;
 
     if(option == 0){
          cout << "" << cursor << "\tEasy\n\tIntermediate\n\tInsane (WARNING: Unbeatable)" << endl;
     }
     
     else if(option == 1){
          cout << "\tEasy\n" << cursor << "\tIntermediate\n\tInsane (WARNING: Unbeatable)" << endl;
     }
     
     else if(option == 2){
          cout << "\tEasy\n\tIntermediate\n" << cursor << "\tInsane (WARNING: Unbeatable)" << endl;
     }

}

//Draw Function for the Options menu
void drawOptionsMenu(int option){
    
    system("CLS");
    
    cout << "\tOPTIONS\n\n" << endl;
    
    if(option == 0){
        if(scrollSpeed == 0){
            cout << cursor << "\tScroll Speed (|----)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 1){
            cout << cursor << "\tScroll Speed (-|---)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 2){
            cout << cursor << "\tScroll Speed (--|--)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 3){
            cout << cursor << "\tScroll Speed (---|-)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 4){
            cout << cursor << "\tScroll Speed (----|)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
    }
    else if(option == 1){
        if(scrollSpeed == 0){
            cout << "\tScroll Speed (|----)\n" << cursor << "\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 1){
            cout << "\tScroll Speed (-|---)\n" << cursor << "\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 2){
            cout << "\tScroll Speed (--|--)\n" << cursor << "\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 3){
            cout << "\tScroll Speed (---|-)\n" << cursor << "\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 4){
            cout << "\tScroll Speed (----|)\n" << cursor << "\tClear Game Stats\n\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
    }
    else if(option == 2){
        if(scrollSpeed == 0){
            cout << "\tScroll Speed (|----)\n\tClear Game Stats\n" << cursor << "\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 1){
            cout << "\tScroll Speed (-|---)\n\tClear Game Stats\n" << cursor << "\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 2){
            cout << "\tScroll Speed (--|--)\n\tClear Game Stats\n" << cursor << "\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 3){
            cout << "\tScroll Speed (---|-)\n\tClear Game Stats\n" << cursor << "\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 4){
            cout << "\tScroll Speed (----|)\n\tClear Game Stats\n" << cursor << "\tCursor Type " << cursorPick << "\n\tBack to Main Menu" << endl;
        }
    }
    else if(option == 3){
        if(scrollSpeed == 0){
            cout << "\tScroll Speed (|----)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n" << cursor << "\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 1){
            cout << "\tScroll Speed (-|---)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n" << cursor << "\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 2){
            cout << "\tScroll Speed (--|--)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n" << cursor << "\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 3){
            cout << "\tScroll Speed (---|-)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n" << cursor << "\tBack to Main Menu" << endl;
        }
        else if(scrollSpeed == 4){
            cout << "\tScroll Speed (----|)\n\tClear Game Stats\n\tCursor Type " << cursorPick << "\n" << cursor << "\tBack to Main Menu" << endl;
        }
    }
}

void drawPlayAgain(int option){
    
    system("CLS");
    
    cout << "Would you like to play again?\n";
    
    if(option == 0){
            cout << cursor << "Yes\t  No" << endl;
    }
    else if(option == 1){
            cout << "  Yes\t" << cursor << "No" << endl;
    }  
}

//Get X and Y co-ordinates
short getRegionsX(short moveAI) {
      
   if (moveAI <= 3){
       return 0;
   }
   if (moveAI <= 6){
       return 1;
   }
   
   return 2;
}

short getRegionsY(short moveAI) {
      
   return (moveAI + 2) % 3;
}

//Reset Game Board
void resetGame(char *change[3]){
    
    for(int inc = 0; inc < 3; inc++){
        *(change[inc]) = '*';
        *(change[inc] + 1) = '*';
        *(change[inc] + 2) = '*';
    }
    
}

//Unit Test
void unitTestWinCheckHorizontal() {
     char emptyBoard[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'*','*','*'}};

     char xWinTopRow[3][3] = {{'X','X','X'},
                           {'*','*','*'},
                           {'*','*','*'}};

     char oWinTopRow[3][3] = {{'O','O','O'},
                           {'*','*','*'},
                           {'*','*','*'}};

     char xWinMiddleRow[3][3] = {{'*','*','*'},
                           {'X','X','X'},
                           {'*','*','*'}};

     char oWinMiddleRow[3][3] = {{'*','*','*'},
                           {'O','O','O'},
                           {'*','*','*'}};

     char xWinBottomRow[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'X','X','X'}};

     char oWinBottomRow[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'O','O','O'}};


	 assertion("Emptyboard test failed.", winCheck(emptyBoard) == 3);
	 assertion("xWinTopRow test failed.", winCheck(xWinTopRow) == 0);
	 assertion("oWinTopRow test failed.", winCheck(oWinTopRow) == 1);
	 assertion("xWinMiddleRow test failed.", winCheck(xWinMiddleRow) == 0);
	 assertion("oWinMiddleRow test failed.", winCheck(oWinMiddleRow) == 1);
	 assertion("xWinBottomRow test failed.", winCheck(xWinBottomRow) == 0);
	 assertion("oWinBottomRow test failed.", winCheck(oWinBottomRow) == 1);
}

void unitTestWinCheckVertical() {
     char emptyBoard[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'*','*','*'}};

     char xWinLeftCol[3][3] = {{'X','*','*'},
                           {'X','*','*'},
                           {'X','*','*'}};

     char oWinLeftCol[3][3] = {{'O','*','*'},
                           {'O','*','*'},
                           {'O','*','*'}};

     char xWinMiddleCol[3][3] = {{'*','X','*'},
                           {'*','X','*'},
                           {'*','X','*'}};

     char oWinMiddleCol[3][3] = {{'*','O','*'},
                           {'*','O','*'},
                           {'*','O','*'}};

     char xWinRightCol[3][3] = {{'*','*','X'},
                           {'*','*','X'},
                           {'*','*','X'}};

     char oWinRightCol[3][3] = {{'*','*','O'},
                           {'*','*','O'},
                           {'*','*','O'}};


	 assertion("Emptyboard test failed.", winCheck(emptyBoard) == 3);
	 assertion("xWinLeftCol test failed.", winCheck(xWinLeftCol) == 0);
	 assertion("oWinLeftCol test failed.", winCheck(oWinLeftCol) == 1);
	 assertion("xWinMiddleCol test failed.", winCheck(xWinMiddleCol) == 0);
	 assertion("oWinMiddleCol test failed.", winCheck(oWinMiddleCol) == 1);
	 assertion("xWinRightCol test failed.", winCheck(xWinRightCol) == 0);
	 assertion("oWinRightCol test failed.", winCheck(oWinRightCol) == 1);
}

void unitTestWinCheckDiagonal() {
     char emptyBoard[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'*','*','*'}};

     char xWinDiag[3][3] = {{'X','*','*'},
                           {'*','X','*'},
                           {'*','*','X'}};

     char oWinDiag[3][3] = {{'O','*','*'},
                           {'*','O','*'},
                           {'*','*','O'}};
     
     char xWinBackDiag[3][3] = {{'*','*','X'},
                           {'*','X','*'},
                           {'X','*','*'}};
                           
     char oWinBackDiag[3][3] = {{'*','*','O'},
                           {'*','O','*'},
                           {'O','*','*'}};

	 assertion("Emptyboard test failed.", winCheck(emptyBoard) == 3);
	 assertion("xWinDiag test failed.", winCheck(xWinDiag) == 0);
	 assertion("oWinDiag test failed.", winCheck(oWinDiag) == 1);
	 assertion("xWinBackDiag test failed.", winCheck(xWinBackDiag) == 0);
	 assertion("oWinBackDiag test failed.", winCheck(oWinBackDiag) == 1);
}

void unitTestWinCheckCats() {
     char emptyBoard[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'*','*','*'}};

     char winCats[3][3] = {{'*','*','O'},
                           {'O','X','X'},
                           {'X','*','O'}};
                           
     char catGame[3][3] = {{'O','X','O'},
                           {'X','X','O'},
                           {'X','O','X'}};

	 assertion("Emptyboard test failed.", winCheck(emptyBoard) == 3);
	 assertion("winCats test failed.", winCheck(winCats) == 3);
	 assertion("catGame test failed.", winCheck(catGame) == 2);
}

void unitTestAIWin() {

     char winHorizontal1[3][3] = {{'O','O','*'},
                           {'*','X','*'},
                           {'X','*','*'}};

     char winHorizontal2[3][3] = {{'O','*','O'},
                           {'*','X','*'},
                           {'X','*','*'}};

     char winHorizontal3[3][3] = {{'*','O','O'},
                           {'*','X','*'},
                           {'X','*','*'}};
                           
     char winHorizontal4[3][3] = {{'X','*','X'},
                           {'O','O','*'},
                           {'*','*','*'}};
                           
     char winHorizontal5[3][3] = {{'X','*','X'},
                           {'O','*','O'},
                           {'*','*','*'}};
                           
     char winHorizontal6[3][3] = {{'X','*','X'},
                           {'*','O','O'},
                           {'*','*','*'}};
                           
     char winHorizontal7[3][3] = {{'*','*','*'},
                           {'X','X','*'},
                           {'*','O','O'}};
                           
     char winHorizontal8[3][3] = {{'*','*','*'},
                           {'*','X','X'},
                           {'O','*','O'}};
                           
     char winHorizontal9[3][3] = {{'*','*','*'},
                           {'X','X','*'},
                           {'O','O','*'}};
     
     char winDiagonal[3][3] = {{'*','*','*'},
                           {'X','O','*'},
                           {'*','X','O'}};
     
     char winAntiDiagonal[3][3] = {{'*','*','*'},
                           {'X','O','*'},
                           {'O','X','*'}};
                           
     char winVertical1[3][3] = {{'*','*','*'},
                           {'O','X','*'},
                           {'O','X','*'}};
                           
     char winVertical2[3][3] = {{'*','O','*'},
                           {'X','*','X'},
                           {'*','O','*'}};
                           
     char winVertical3[3][3] = {{'*','*','O'},
                           {'X','X','O'},
                           {'*','*','*'}};
                           
     char winPlayer[3][3] = {{'*','X','*'},
                           {'*','*','X'},
                           {'O','O','X'}};
                           
  assertion("Medium winHorizontal1 test failed.", gameAIMedium(winHorizontal1) == 3);
  assertion("Medium winHorizontal2 test failed.", gameAIMedium(winHorizontal2) == 2);
  assertion("Medium winHorizontal3 test failed.", gameAIMedium(winHorizontal3) == 1);
  assertion("Medium winHorizontal4 test failed.", gameAIMedium(winHorizontal4) == 6);
  assertion("Medium winHorizontal5 test failed.", gameAIMedium(winHorizontal5) == 5);
  assertion("Medium winHorizontal6 test failed.", gameAIMedium(winHorizontal6) == 4);
  assertion("Medium winHorizontal7 test failed.", gameAIMedium(winHorizontal7) == 7);
  assertion("Medium winHorizontal8 test failed.", gameAIMedium(winHorizontal8) == 8);
  assertion("Medium winHorizontal9 test failed.", gameAIMedium(winHorizontal9) == 9);
  assertion("Medium winDiagonal test failed.", gameAIMedium(winDiagonal) == 1);
  assertion("Medium winAntiDiagonal test failed.", gameAIMedium(winAntiDiagonal) == 3);
  assertion("Medium winVertical1 test failed.", gameAIMedium(winVertical1) == 1);
  assertion("Medium winVertical2 test failed.", gameAIMedium(winVertical2) == 5);
  assertion("Medium winVertical3 test failed.", gameAIMedium(winVertical3) == 9);
  assertion("Insane winHorizontal1 test failed.", gameAIInsane(winHorizontal1) == 3);
  assertion("Insane winHorizontal2 test failed.", gameAIInsane(winHorizontal2) == 2);
  assertion("Insane winHorizontal3 test failed.", gameAIInsane(winHorizontal3) == 1);
  assertion("Insane winHorizontal4 test failed.", gameAIInsane(winHorizontal4) == 6);
  assertion("Insane winHorizontal5 test failed.", gameAIInsane(winHorizontal5) == 5);
  assertion("Insane winHorizontal6 test failed.", gameAIInsane(winHorizontal6) == 4);
  assertion("Insane winHorizontal7 test failed.", gameAIInsane(winHorizontal7) == 7);
  assertion("Insane winHorizontal8 test failed.", gameAIInsane(winHorizontal8) == 8);
  assertion("Insane winHorizontal9 test failed.", gameAIInsane(winHorizontal9) == 9);
  assertion("Insane winDiagonal test failed.", gameAIInsane(winDiagonal) == 1);
  assertion("Insane winAntiDiagonal test failed.", gameAIInsane(winAntiDiagonal) == 3);
  assertion("Insane winVertical1 test failed.", gameAIInsane(winVertical1) == 1);
  assertion("Insane winVertical2 test failed.", gameAIInsane(winVertical2) == 5);
  assertion("Insane winVertical3 test failed.", gameAIInsane(winVertical3) == 9);
  assertion("Insane winPlayer test failed.", gameAIInsane(winPlayer) == 3);
  cout << gameAIInsane(winPlayer) << endl;
}

void unitTestAIMiddle() {
     
    char emptyBoard[3][3] = {{'*','*','*'},
                           {'*','*','*'},
                           {'*','*','*'}};
    
    assertion("Emptyboard test failed.", gameAIMedium(emptyBoard) == 5);
}

void unitTestAIBlock(){
    
    char blockMove1[3][3] = {{'*','O','*'},
                           {'*','X','*'},
                           {'*','O','X'}};
                           
    char blockMove2[3][3] = {{'X','*','X'},
                           {'*','O','*'},
                           {'O','*','*'}};
                           
    char blockMove3[3][3] = {{'*','X','*'},
                           {'O','X','*'},
                           {'*','*','O'}};
                           
    char blockMove4[3][3] = {{'*','*','X'},
                           {'O','X','O'},
                           {'*','*','*'}};
                           
    char blockHorizontal1[3][3] = {{'X','X','*'},
                                {'*','O','*'},
                                {'*','O','*'}};

    char blockVertical1[3][3] = {{'*','*','O'},
                                {'X','O','*'},
                                {'X','*','*'}};

    char blockDiagonal1[3][3] = {{'O','*','*'},
                                {'O','X','*'},
                                {'X','*','*'}};
                           
    char blockOrWin1[3][3] = {{'X','*','*'},
                           {'X','O','*'},
                           {'*','O','*'}};
                           
    char blockOrWin2[3][3] = {{'X','*','X'},
                           {'O','O','*'},
                           {'*','*','*'}};
                           
    assertion("Medium blockMove1 test failed.", gameAIMedium(blockMove1) == 1);
    assertion("Medium blockMove2 test failed.", gameAIMedium(blockMove2) == 2);
    assertion("Medium blockMove3 test failed.", gameAIMedium(blockMove3) == 8);
    assertion("Medium blockMove4 test failed.", gameAIMedium(blockMove4) == 7);
    assertion("Medium blockHorizontal1 test failed.", gameAIMedium(blockHorizontal1) == 3);
    assertion("Medium blockVertical1 test failed.", gameAIMedium(blockVertical1) == 1);
    assertion("Medium blockDiagonal1 test failed.", gameAIMedium(blockDiagonal1) == 3);
    assertion("Medium blockOrWin1 test failed.", gameAIMedium(blockOrWin1) == 2);
    assertion("Medium blockOrWin2 test failed.", gameAIMedium(blockOrWin2) == 6);
    assertion("Insane blockMove1 test failed.", gameAIInsane(blockMove1) == 1);
    assertion("Insane blockMove2 test failed.", gameAIInsane(blockMove2) == 2);
    assertion("Insane blockMove3 test failed.", gameAIInsane(blockMove3) == 8);
    assertion("Insane blockMove4 test failed.", gameAIInsane(blockMove4) == 7);
    assertion("Insane blockHorizontal1 test failed.", gameAIInsane(blockHorizontal1) == 3);
    assertion("Insane blockVertical1 test failed.", gameAIInsane(blockVertical1) == 1);
    assertion("Insane blockDiagonal1 test failed.", gameAIInsane(blockDiagonal1) == 3);
    assertion("Insane blockOrWin1 test failed.", gameAIInsane(blockOrWin1) == 2);
    assertion("Insane blockOrWin2 test failed.", gameAIInsane(blockOrWin2) == 6);
                           
}

void unitTestMinimaxEndStates() {
    char winState1[3][3] = {{'O','*','*'},
                           {'*','O','*'},
                           {'X','X','O'}};

    char winState2[3][3] = {{'X','*','O'},
                           {'*','O','*'},
                           {'O','X','*'}};

    char winState3[3][3] = {{'*','*','*'},
                           {'O','O','O'},
                           {'X','X','*'}};

    char winState4[3][3] = {{'X','O','*'},
                           {'*','O','*'},
                           {'X','O','*'}};
         
    char loseState1[3][3] = {{'X','*','*'},
                           {'*','X','*'},
                           {'O','O','X'}};

    char loseState2[3][3] = {{'O','*','X'},
                           {'*','X','*'},
                           {'X','O','*'}};

    char loseState3[3][3] = {{'*','*','*'},
                           {'X','X','X'},
                           {'O','O','*'}};

    char loseState4[3][3] = {{'O','X','*'},
                           {'*','X','*'},
                           {'O','X','*'}};
         
    char catState1[3][3] = {{'X','X','O'},
                           {'O','O','X'},
                           {'X','O','X'}};

    char catState2[3][3] = {{'O','O','X'},
                           {'X','X','O'},
                           {'O','X','O'}};
                           
    char winHorizontal4[3][3] = {{'X','*','X'},
                           {'O','O','*'},
                           {'*','*','*'}};

    assertion("winState1 test failed.", minimax(winState1, 0, true) == 1000);
    assertion("winState2 test failed.", minimax(winState2, 0, true) == 1000);
    assertion("winState3 test failed.", minimax(winState3, 0, true) == 1000);
    assertion("winState4 test failed.", minimax(winState4, 0, true) == 1000);
    assertion("loseState1 test failed.", minimax(loseState1, 0, true) == -1000);
    assertion("loseState2 test failed.", minimax(loseState2, 0, true) == -1000);
    assertion("loseState3 test failed.", minimax(loseState3, 0, true) == -1000);
    assertion("loseState4 test failed.", minimax(loseState4, 0, true) == -1000);
    assertion("catState1 test failed.", minimax(catState1, 0, true) == 0);
    assertion("catState2 test failed.", minimax(catState2, 0, true) == 0);
    cout << "Calling Horizontal 4" << endl;
    minimax(winHorizontal4, 0, true);
}

void unitTestGUI(){
                            
    for(int i = 0; i < 10; i++){
        char emptyBoard[3][3] = {{'*', '*', '*'},
                            {'*', '*', '*'},
                            {'*', '*', '*'}};
                            
        drawTurnBoard(emptyBoard, 1, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 2, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 3, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 4, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 5, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 6, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 7, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 8, "");
        Sleep(250);
        drawTurnBoard(emptyBoard, 9, "");
    }
}

void assertion(string message, bool toCheck) {
   if (!toCheck) {
      cout << message << endl;
   }
}
