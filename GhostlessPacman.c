#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define boardDim 12
#define randDim 10

void shuffle(int *a, int *b){
    // Stores the value of the array of its current index 
    // into temporary storage, ie blockStore
    int blockStore = *a;
    // Shuffles the array
    *a = *b;
    // Ensures that there are no repeating numbers
    *b = blockStore;
}

void blockRandomize(int blockRow[randDim], int blockCol[randDim]){ 
    
    int blockCount, blockNum, blockNum2;
      
    // Block randomizer
    for (blockCount = 0; blockCount < randDim; blockCount++){
        // This generates an array, i.e. blockRow, of numbers 
        // containing from 1 to 10
        blockRow[blockCount] = blockCount + 1;
    }
    for (blockCount = 0; blockCount < randDim; blockCount++){
        // Assigns blockNum a random number from 1 to 10
        blockNum = (rand()%9)+1;
        // Shuffles the array in a way that there is no repetition
        shuffle(&blockRow[blockCount], &blockRow[blockNum]);
    }
    // Generating another unique shuffled array to be used for the column
    for (blockCount = 0; blockCount < randDim; blockCount++){
        blockCol[blockCount] = blockCount + 1;
    }
    for (blockCount = 0; blockCount < randDim; blockCount++){
        blockNum2 = (rand()%9)+1;
        shuffle(&blockCol[blockCount], &blockCol[blockNum2]);
    }  
}

void foodRandomize(int foodRow[randDim], int foodCol[randDim]){ 
    
    int foodCount, foodCount2, foodNum, foodStore, foodNum2, foodStore2;

    // Food randomizer
    // ------------------------------------------------------

    for (foodCount = 0; foodCount < randDim; foodCount++){
        foodRow[foodCount] = foodCount + 1;
    }
    for (foodCount = 0; foodCount < randDim; foodCount++){
        foodNum = (rand()%9)+1;
        shuffle(&foodRow[foodCount], &foodRow[foodNum]);
    }

    // ------------------------------------------------------

    for (foodCount = 0; foodCount < randDim; foodCount++){
        foodCol[foodCount] = foodCount + 1;
    }
    for (foodCount = 0; foodCount < randDim; foodCount++){
        foodNum2 = (rand()%9)+1;
        shuffle(&foodCol[foodCount], &foodCol[foodNum2]);
    }
    
    // Checking array values if shuffled correctly
    /* 
    for (foodCount = 0; foodCount < randDim; foodCount++){
        printf(" %d", foodRow[foodCount]);
    }
    printf("\n-----------------------\n");
    
    for (foodCount = 0; foodCount < randDim; foodCount++){
        printf(" %d", foodCol[foodCount]);
    }
    printf("\n\n");
    */
}

void rand_blockFill(char boardArray[boardDim][boardDim], int exitRow, int exitCol, 
                    int blockRow[randDim], int blockCol[randDim]){

    // Placing blocks
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            for (int arrayCount = 0; arrayCount < randDim; arrayCount++){ 
                // Ensures that the blocks won't block Pacman and the exit
                while ((boardArray[blockRow[arrayCount]][blockCol[arrayCount]] == 'X') || 
                (blockRow[arrayCount] == (exitRow + 1) && blockCol[arrayCount] == exitCol) ||  
                (blockRow[arrayCount] == (exitRow - 1) && blockCol[arrayCount] == exitCol) || 
                (blockRow[arrayCount] == exitRow && blockCol[arrayCount] == (exitCol + 1)) ||
                (blockRow[arrayCount] == exitRow && blockCol[arrayCount] == (exitCol - 1)) ||
                (boardArray[blockRow[arrayCount]][blockCol[arrayCount]] == '<') || 
                (blockRow[arrayCount] == 1 && blockCol[arrayCount] == 1) || 
                (blockRow[arrayCount] == 2 && blockCol[arrayCount] == 1) ||
                (blockRow[arrayCount] == 2 && blockCol[arrayCount] == 2)){
                    blockRandomize(blockRow, blockCol);
                }
                boardArray[blockRow[arrayCount]][blockCol[arrayCount]]='W';
            }
        }
    }
}

void rand_foodFill(char boardArray[boardDim][boardDim], int blockRow[randDim], 
                    int blockCol[randDim], int foodRow[randDim], int foodCol[randDim], int foodChoice){
    
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            for (int arrayCount = 0; arrayCount < foodChoice; arrayCount++){
                // Ensures that the food won't be blocked by the blocks and won't concide with Pacman and the exit.
                while 
                ((boardArray[foodRow[arrayCount]][foodCol[arrayCount]] == 'W') || 
                (foodRow[arrayCount] == (blockRow[arrayCount] + 1) && foodCol[arrayCount] == blockCol[arrayCount]) ||  
                (foodRow[arrayCount] == (blockRow[arrayCount] - 1) && foodCol[arrayCount] == blockCol[arrayCount]) || 
                (foodRow[arrayCount] == blockRow[arrayCount] && foodCol[arrayCount] == (blockCol[arrayCount] + 1)) ||
                (foodRow[arrayCount] == blockRow[arrayCount] && foodCol[arrayCount] == (blockCol[arrayCount] - 1)) ||
                (boardArray[foodRow[arrayCount]][foodCol[arrayCount]] == '<') || 
                (boardArray[foodRow[arrayCount]][foodCol[arrayCount]] == 'X')){
                    foodRandomize(foodRow, foodCol);
                }
                boardArray[foodRow[arrayCount]][foodCol[arrayCount]]='@';
            }
        }
    }
}

void borderFill(char boardArray[boardDim][boardDim]){
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            // Assigning top and bottom borders
            if (countRow == 0 || countRow == boardDim - 1){
                boardArray[countRow][countColumn]='+';
            } 
            // Assigning left and right borders
            else if (countColumn == 0){
                boardArray[countRow][countColumn]='[';
            }
            else if (countColumn == boardDim - 1){
                boardArray[countRow][countColumn]=']';
            }
        }
    }
}

void playerWin(){

    int boardArray[boardDim][boardDim];
    int nameLoop = 0;
    char playerName[5];

    printf("<<[===============================]>>\n"); 
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            if (countRow == 0 || countRow == boardDim - 1){
                boardArray[countRow][countColumn]='+';
            }
            else if (countColumn == 0 || countColumn == boardDim - 1){
                boardArray[countRow][countColumn]='!';
            }
            else {
               boardArray[countRow][countColumn]=' ';
               for (int i = 1; i <= 10; i++){
                   if(i == 1){
                       boardArray[5][i] = 'C';
                   }
                   else if(i == 2){
                       boardArray[5][i] = 'o';
                   }
                   else if(i == 3){
                       boardArray[5][i] = 'n';
                       boardArray[6][i] = 'Y';
                   }
                   else if(i == 4){
                       boardArray[5][i] = 'g';
                       boardArray[6][i] = 'o';
                   }
                   else if(i == 5){
                       boardArray[5][i] = 'r';
                       boardArray[6][i] = 'u';
                   }
                   else if(i == 6){
                       boardArray[5][i] = 'a';
                   }
                   else if(i == 7){
                       boardArray[5][i] = 't';
                       boardArray[6][i] = 'w';
                   }
                   else if(i == 8){
                       boardArray[5][i] = 's';
                       boardArray[6][i] = 'i';
                   }
                   else if (i == 9) {
                       boardArray[5][i] = ',';
                       boardArray[6][i] = 'n';
                   }
                   else{
                       boardArray[6][i] = '!';
                   }
               }
            }    
            printf(" %c ", boardArray[countRow][countColumn]);   
        }  
        printf("\n");
    }
    printf( "    The ghosts have been revived! \n");
    printf( "::================================::\n"
            "      Machine Project I by Ark1\n"
            "     Press M to go back to menu.\n"
            "::================================::\n");
}

void playerLose(){

    int boardArray[boardDim][boardDim];

    printf("<<[===============================]>>\n"); 
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            if (countRow == 0 || countRow == boardDim - 1){
                boardArray[countRow][countColumn]='+';
            }
            else if (countColumn == 0 || countColumn == boardDim - 1){
                boardArray[countRow][countColumn]='!';
            }
            else {
               boardArray[countRow][countColumn]=' ';
               for (int i = 1; i <= 10; i++){
                   
                   if(i == 1){
                       boardArray[5][i] = 'O';
                   }
                   else if(i == 2){
                       boardArray[5][i] = 'o';
                       boardArray[6][i] = 'Y';
                   }
                   else if(i == 3){
                       boardArray[5][i] = 'p';
                       boardArray[6][i] = 'o';
                   }
                   else if(i == 4){
                       boardArray[5][i] = 's';
                       boardArray[6][i] = 'u';
                   }
                   else if(i == 5){
                       boardArray[5][i] = ' ';
                   }
                   else if(i == 6){
                       boardArray[5][i] = ':';
                       boardArray[6][i] = 'l';
                   }
                   else if(i == 7){
                       boardArray[5][i] = '(';
                       boardArray[6][i] = 'o';
                   }
                   else if(i == 8){
                       boardArray[6][i] = 's';
                   }
                   else if (i == 9) {
                       boardArray[6][i] = 'e';
                   }
                   else{
                       boardArray[6][i] = '!';
                   }
               }
            }    
            printf(" %c ", boardArray[countRow][countColumn]);   
        }  
        printf("\n");
    }
    printf( " Pacman remains eternally alone...\n");
    printf( "::================================::\n"
            "      Machine Project I by Ark1\n"
            "     Press M to go back to menu.\n"
            "::================================::\n");
}

void checkWin(int foodChoice, int foodCounter){

    if (foodCounter == (foodChoice*100)){
        playerWin();
    }
    else{
        playerLose();
    }
}

void print_initialBoard(char boardArray[boardDim][boardDim]){
    printf("<<[[===ARE YOU READY TO RUMBLE?===]]>>\n"); 
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            printf(" %c ", boardArray[countRow][countColumn]);   
        }  
        printf("\n");
    }
    printf("<<[[=======PRESS P TO PLAY=======]]>>\n"); 
}

void printBoard(char boardArray[boardDim][boardDim], int foodChoice, int foodCounter){
    printf("<<[[=============================]]>>\n");
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            printf(" %c ", boardArray[countRow][countColumn]);   
        }  
        printf("\n");
    }
    printf("Goal: %d                Points: %d\n"
            "<<[[============================]]>>\n"
            "     Press W, A, S, D to move.\n"
            "     Press M to go back to menu.\n"
            "<<[[============================]]>>\n", foodChoice*100, foodCounter);
                    
}

void welcomeSign(){

    printf("\n" 
    " /$$      /$$           /$$                                                     /$$              \n"
    "| $$  /$ | $$          | $$                                                    | $$              \n"
    "| $$ /$$$| $$  /$$$$$$ | $$  /$$$$$$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$        /$$$$$$    /$$$$$$ \n"
    "| $$/$$ $$ $$ /$$__  $$| $$ /$$_____/ /$$__  $$| $$_  $$_  $$ /$$__  $$      |_  $$_/   /$$__  $$\n"
    "| $$$$_  $$$$| $$$$$$$$| $$| $$      | $$  | $$| $$ | $$ | $$| $$$$$$$$        | $$    | $$  | $$\n"
    "| $$$/ |  $$$| $$_____/| $$| $$      | $$  | $$| $$ | $$ | $$| $$_____/        | $$ /$$| $$  | $$\n"
    "| $$/   |  $$|  $$$$$$$| $$|  $$$$$$$|  $$$$$$/| $$ | $$ | $$|  $$$$$$$        |  $$$$/|  $$$$$$/\n"
    "|__/     |__/ |_______/|__/ |_______/ |______/ |__/ |__/ |__/ |_______/         |___/   |______/ \n"
    "\n"                                                                                               
    "     /$$$$$$  /$$   /$$  /$$$$$$   /$$$$$$  /$$$$$$$$ /$$       /$$$$$$$$  /$$$$$$   /$$$$$$   \n"       
    "    /$$__  $$| $$  | $$ /$$__  $$ /$$__  $$|__  $$__/| $$      | $$_____/ /$$__  $$ /$$__  $$  \n"  
    "   | $$  |__/| $$  | $$| $$  | $$| $$  |__/   | $$   | $$      | $$      | $$  |__/| $$  |__/ \n"     
    "   | $$ /$$$$| $$$$$$$$| $$  | $$|  $$$$$$    | $$   | $$      | $$$$$   |  $$$$$$ |  $$$$$$  \n"   
    "   | $$|_  $$| $$__  $$| $$  | $$ |____  $$   | $$   | $$      | $$__/    |____  $$ |____  $$ \n"   
    "   | $$  | $$| $$  | $$| $$  | $$ /$$  | $$   | $$   | $$      | $$       /$$  | $$ /$$  | $$ \n"      
    "   |  $$$$$$/| $$  | $$|  $$$$$$/|  $$$$$$/   | $$   | $$$$$$$$| $$$$$$$$|  $$$$$$/|  $$$$$$/ \n"     
    "   |______/ |__/  |__/ |______/  |______/    |__/   |________/|________/ |______/  |______/   \n"    
    "\n"                                                                                              
    "               /$$$$$$$   /$$$$$$   /$$$$$$  /$$      /$$  /$$$$$$  /$$   /$$  \n"                                  
    "              | $$__  $$ /$$__  $$ /$$__  $$| $$$    /$$$ /$$__  $$| $$$ | $$ \n"                                 
    "              | $$  | $$| $$  | $$| $$  |__/| $$$$  /$$$$| $$  | $$| $$$$| $$ \n"                                 
    "              | $$$$$$$/| $$$$$$$$| $$      | $$ $$/$$ $$| $$$$$$$$| $$ $$ $$ \n"                                 
    "              | $$____/ | $$__  $$| $$      | $$  $$$| $$| $$__  $$| $$  $$$$ \n"                                 
    "              | $$      | $$  | $$| $$    $$| $$|  $ | $$| $$  | $$| $$|  $$$ \n"                                 
    "              | $$      | $$  | $$|  $$$$$$/| $$ |/  | $$| $$  | $$| $$ |  $$ \n"                                 
    "              |__/      |__/  |__/ |______/ |__/     |__/|__/  |__/|__/  |__/ \n\n");
}

void mainMenu(){
    
printf(
    "<[[==========================================================================================]]>\n"
    "                                         M A I N  M E N U\n"
    "<[[==========================================================================================]]>\n"
    "       (1) Start the game. \n"
    "       (2) Instructions. \n"
    "       (3) Exit the game. \n\n");
}

void instructionMenu(){

    int instrucLoop = 0;
    char instrucChoice;

    while (instrucLoop == 0){
        printf( 
                "     _       _            _                   _   _                 \n"
                "    (_)     | |          | |                 | | (_)                \n"              
                "     _ _ __ | |_ ___  ___| |_ _ __ _   _  ___| |_ _  ___  _ __  ___ \n"
                "    | | '_ || __/ __|/ __| __| '__| | | |/ __| __| |/ _ || '_ |/ __|\n"
                "    | | | | | |_|__ | (__| |_| |  | |_| | (__| |_| | (_) | | | |__ |\n"
                "    |_|_| |_||__|___/|___||__|_|   |__,_||___||__|_||___/|_| |_|___/\n"
                "<[[================================================================]]>\n"
                "             W H A T  D O  Y O U  W A N T  T O  K N O W ? \n"
                "<[[================================================================]]>\n"
                "       (A) How can I control Pacman?\n"
                "       (B) How can I win the game? \n"
                "       (C) How can I lose the game? \n"                                             
                "       (D) How do the blocks and foods work? \n"
                "       (E) Go back to menu. \n\n");
    
        scanf(" %c", &instrucChoice);
        switch (instrucChoice){
            case 'A':{
                system("clear");
                printf("How can I control Pacman?\n"
                        "You can press W, A, S, or D to move upward, leftward, downward, and rightward respectively.\n\n");
                break;
            }
            case 'a':{
                system("clear");
                printf("How can I control Pacman?\n"
                        "You can press W, A, S, or D to move upward, leftward, downward, and rightward respectively.\n\n");
                break;
            }
            case 'B':{
                system("clear");
                printf("How can I win the game?\n"
                        "You must first collect all the food and then go to the exit to win the game.\n"
                        "Each food gives you 100 points.\n"
                        "Food are represented by the symbol: @\n"
                        "Exit is represented by the symbol: X\n\n");
                break;
            }
            case 'b':{
                system("clear");
                printf("How can I win the game?\n"
                        "You must first collect all the food and then go to the exit to win the game.\n"
                        "Each food gives you 100 points.\n"
                        "Food are represented by the symbol: @\n"
                        "Exit is represented by the symbol: X\n\n");
                break;
            }
            case 'C':{
                system("clear");
                printf("How can I lose the game? \n"
                        "You will lose if you collide with any of the blocks or the border of the game.\n"
                        "You will also lose if you go to exit without collecting all the food.\n"
                        "Blocks are represented by the symbol: W\n\n");
                break;
            }
            case 'c':{
                system("clear");
                printf("How can I lose the game? \n"
                        "You will lose if you collide with any of the blocks or the border of the game.\n"
                        "You will also lose if you go to exit without collecting all the food.\n"
                        "Blocks are represented by the symbol: W\n\n");
                break;
            }
            case 'D':{
                system("clear");
                printf( "How do the blocks and foods work?\n"
                        "Blocks and food are randomly placed in the board. \n"
                        "You can choose how many food you want to appear.\n\n");
                break;
            }
            case 'd':{
                system("clear");
                printf( "How do the blocks and foods work?\n"
                        "Blocks and food are randomly placed in the board. \n"
                        "You can choose how many food you want to appear.\n"
                        "The food you choose can be from 2 to 9.\n\n");
                break;
            }
            case 'E':{
                system("clear");
                instrucLoop++;
                break;
            }
            case 'e':{
                system("clear");
                instrucLoop++;
                break;
            }
            default:{
                system("clear");
                printf("Invalid!\n\n");
                fgetc(stdin);
                break;
            }
        }
    }
}

void board_easterEgg(char boardArray[boardDim][boardDim], int PacX, int PacY){
    printf("<<[===============================]>>\n");
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            boardArray[PacY][PacX] ='<';
            if (countRow > 0 && countRow < boardDim - 1 && countColumn > 0 && countColumn < boardDim - 1){
                boardArray[countRow][countColumn]=' ';
                boardArray[PacY][PacX] ='<';
                for (int i = 1; i <= 10; i++){
                    if(i == 1){
                        boardArray[4][i] = 'O';
                        boardArray[5][i] = 'O';
                        boardArray[6][i] = 'O';
                    }
                    else if(i == 2){
                        boardArray[3][i] = 'O';
                        boardArray[7][i] = 'O';
                    }
                    else if(i == 3){
                        boardArray[2][i] = 'O';
                        boardArray[8][i] = 'O';
                    }
                    else if(i == 4){
                        boardArray[3][i] = 'O';
                        boardArray[9][i] = 'O';
                    }
                    else if(i == 5){
                        boardArray[3][i] = 'O';
                        boardArray[10][i] = 'O';
                    }
                    else if(i == 6){
                        boardArray[3][i] = 'O';
                        boardArray[10][i] = 'O';
                    }
                    else if(i == 7){
                        boardArray[3][i] = 'O';
                        boardArray[9][i] = 'O';
                    }
                    else if(i == 8){
                        boardArray[2][i] = 'O';
                        boardArray[8][i] = 'O';
                    }
                    else if (i == 9) {
                        boardArray[3][i] = 'O';
                        boardArray[7][i] = 'O';
                    }
                    else{
                        boardArray[4][i] = 'O';
                        boardArray[5][i] = 'O';
                        boardArray[6][i] = 'O';
                    }
               }
                if (boardArray[PacY][PacX] == 'O'){
                    boardArray[PacY][PacX] = 'X';
                }
            }
        printf(" %c ", boardArray[countRow][countColumn]);     
       
        }
    printf("\n");
    }
    printf( "<<[[============================]]>>\n"
            "   E A S T E R  E G G  F O U N D !\n"
            "       Here's a heart for you.\n"
            "<<[[============================]]>>\n"
            "     Press M to go back to menu.\n");
}

void roundUpdate(char boardArray[boardDim][boardDim], int PacY, int PacX){
    for (int countRow = 0; countRow < boardDim; countRow++){
        for(int countColumn = 0; countColumn < boardDim; countColumn++){
            // Placing borders
            borderFill(boardArray);
            // Placing contents of the game board
            if (countRow > 0 && countRow < boardDim - 1 && countColumn > 0 && countColumn < boardDim - 1){
                // Placing PacMan
                if (countRow == PacY && countColumn == PacX){
                    boardArray[countRow][countColumn] = '<';
                }
            }
        }
    }
}

void nomNom(){

    printf(
           "                                                    _ \n"
           "                                                   | |\n"
           "        _ __   ___  _ __ ___  _ __   ___  _ __ ___ | |\n"
           "       | '_ | / _ || '_ ` _ || '_ | / _ || '_ ` _ || |\n"
           "       | | | | (_) | | | | | | | | | (_) | | | | | |_|\n"
           "       |_| |_||___/|_| |_| |_|_| |_||___/|_| |_| |_(_)\n");
}


int main(){ 
 
    // Arrays for the board and randomization of its content 
    int blockRow[randDim], blockCol[randDim];
    int foodRow[randDim], foodCol[randDim];
    char boardArray[boardDim][boardDim];
    int exitRow, exitCol; 
    
    // User inputs 
    int menuChoice;
    int foodChoice;
    char pressChoice;
    char playChoice;
    char resultChoice;

    // Loops
    int pressLoop;
    int playLoop;
    int foodLoop;
    int resultLoop;
    int noreturnLoop;
    int easterLoop;

    // Game statistics
    int foodCounter;
    int controlLock;
    int PacX, PacY;
    int easterEgg;
    int easterLock;
    int wrongKey;

    // srand() uses a seed for randomization
    // time(NULL) makes use of computer's internal clock; hence the seed is always changing
    srand(time(NULL));

    // Main Lobby 
    while (menuChoice != 3){
        // Some fancy sign that I hope works 
        welcomeSign();
        // Main Menu
        mainMenu();
        scanf(" %d", &menuChoice);
        switch (menuChoice){
            case 1:{
                // foodChoice
                system("clear"); 
                nomNom();
                printf("::==========================================================::\n"
                       "    Please choose the number of food you want from 2 to 9.\n"
                       "::==========================================================::\n"); 
                foodLoop = 0;
                foodChoice = 0;
                while (foodLoop == 0){
                    scanf(" %d", &foodChoice);
                    if (foodChoice >= 2 && foodChoice <= 9){
                        system("clear");
                        foodLoop++;
                    }
                    else {
                        system("clear");
                        nomNom();
                        printf("::==========================================================::\n"
                               "I think you should only choose the number of food from 2 to 9.\n"
                               "::==========================================================::\n");
                        fgetc(stdin);
                    }
                }

                // Initializes the randomization of blocks, foods, and exit 
                blockRandomize(blockRow, blockCol);
                foodRandomize(foodRow, foodCol);
                exitRow = (rand()%9)+1;
                exitCol = (rand()%9)+1;

                pressLoop = 0;
                noreturnLoop = 0;
                while (pressLoop == 0){     

                    // Creating a randomized game board
                    for (int countRow = 0; countRow < boardDim; countRow++){
                        for(int countColumn = 0; countColumn < boardDim; countColumn++){
                            // Placing borders
                            borderFill(boardArray);
                            // Placing contents of the game board
                            if (countRow > 0 && countRow < boardDim - 1 && countColumn > 0 && countColumn < boardDim - 1){
                                // Placing blank spaces
                                boardArray[countRow][countColumn]='.';
                                // Placing PacMan
                                if (countRow == 1 && countColumn == 1){
                                    boardArray[countRow][countColumn] = '<';
                                }
                                // Placing exit 
                                while (boardArray[exitRow][exitCol] == '<'){
                                    exitRow = (rand()%9)+1;
                                    exitCol = (rand()%9)+1;
                                    boardArray[exitRow][exitCol] = boardArray[exitRow][exitCol];
                                }
                                if (boardArray[countRow][countColumn] != '<'){
                                    boardArray[exitRow][exitCol] = 'X';
                                }
                                // Filling blocks
                                rand_blockFill(boardArray, exitRow, exitCol, blockRow, blockCol);
                                // Filling food
                                rand_foodFill(boardArray, blockRow, blockCol, foodRow, foodCol, foodChoice);
                            }
                        }
                    } 
                    
                    // Prints the initial game board
                    print_initialBoard(boardArray);

                    // Game Start
                    if(noreturnLoop > 0){
                        printf("There's no going back! The show must go on ;)\n");
                    }
                    printf("Hint: Stuck? Press S to generate a new world!\n");
                    scanf(" %c", &pressChoice);
                    if (pressChoice == 'p' || pressChoice == 'P'){
                        system("clear");
                        pressLoop++;
                    }
                    // If bad RNG happens, there should be a salvation key xD
                    else if (pressChoice == 's' || pressChoice == 'S'){
                        system("clear");
                        blockRandomize(blockRow, blockCol);
                        foodRandomize(foodRow, foodCol);
                        exitRow = (rand()%9)+1;
                        exitCol = (rand()%9)+1;
                    }
                    else {
                        noreturnLoop++;
                        system("clear");
                        fgetc(stdin);
                    }
                }

                // Resets the game statistics
                playLoop = 0;
                PacX = 1;
                PacY = 1;
                foodCounter = 0;
                controlLock = 0;
                resultLoop = 0;
                easterEgg = 0;
                easterLock = 0;
                easterLoop = 0;
                wrongKey = 0;

                while (playLoop == 0){

                    system("clear");

                    // When a food is eaten
                    if (boardArray[PacY][PacX] == '@'){
                        boardArray[PacY][PacX] = '<';
                        foodCounter += 100;
                    }
                    
                    // Conditions for losing: either Pacman collides with the block or the border
                    if (boardArray[PacY][PacX] == 'W' || PacY <= 0 || PacY >= 11 || PacX <= 0 || PacX >= 11){
                        while (resultLoop == 0){
                            system("clear");
                            playerLose();
                            controlLock++;
                            scanf(" %c", &resultChoice);
                            if(resultChoice == 'M' || resultChoice == 'm'){
                                system("clear");
                                resultLoop++;
                            }
                            else{
                                fgetc(stdin);
                            }
                        }
                        playLoop++;
                    }
                    
                    // Conditions for winning... and something about eggs
                    if (boardArray[PacY][PacX] == 'X'){
                        while (resultLoop == 0){
                            system("clear");
                            // Checks if the player has collected the right amount of food before exiting 
                            checkWin(foodChoice, foodCounter);
                            controlLock++;
                            scanf(" %c", &resultChoice);

                            // ...? What's this?
                            // Ark1 LOVEEES easter eggs, so he made on for his game :D
                            // And what better way to honor the creator of C?
                            switch (resultChoice){
                            case 'R':{
                                easterEgg++;
                                easterLock++;
                                break;}
                            case 'i':{
                                if(easterLock == 1 || easterLock == 5){
                                easterEgg++;
                                easterLock++;
                                }
                                break;}
                            case 't':{
                                if(easterLock == 2){
                                easterEgg++;
                                easterLock++;
                                }
                                break;}
                            case 'c':{
                                if(easterLock == 3){
                                easterEgg++;
                                easterLock++;
                                }
                                break;}
                            case 'h':{
                                if(easterLock == 4){
                                easterEgg++;
                                easterLock++;
                                }
                                break;}
                            case 'e':{
                                if(easterLock == 6){
                                easterEgg++;
                                }
                                break;}   
                            default:{
                                fgetc(stdin);
                                break;}  
                            }
                            if(easterEgg < 7){
                                if(resultChoice == 'M' || resultChoice == 'm'){
                                    system("clear");
                                    resultLoop++;
                                }
                                else{
                                    fgetc(stdin);
                                }
                            }
                            else if (easterEgg >= 7){
                                PacX = 1;
                                PacY = 1;
                                while (easterLoop == 0){
                                    system("clear");
                                    board_easterEgg(boardArray, PacX, PacY);
                                    if (wrongKey == 1){
                                        printf("Invalid Key!\n");
                                    }
                                    scanf(" %c", &resultChoice);
                                    switch (resultChoice){
                                        case 'W':{
                                            PacY--;
                                            boardArray[PacY+1][PacX] =' ';
                                            wrongKey = 0;
                                            break;}
                                        case 'w':{
                                            PacY--;
                                            boardArray[PacY+1][PacX] =' ';
                                            wrongKey = 0;
                                            break;}
                                        case 'A':{
                                            PacX--;
                                            boardArray[PacY][PacX+1] =' ';
                                            wrongKey = 0;
                                            break;}
                                        case 'a':{
                                            PacX--;
                                            boardArray[PacY][PacX+1] =' ';
                                            wrongKey = 0;
                                            break;}
                                        case 'S':{
                                            PacY++;
                                            boardArray[PacY-1][PacX] =' ';
                                            wrongKey = 0;
                                            break;}  
                                        case 's':{
                                            PacY++;
                                            boardArray[PacY-1][PacX] =' ';
                                            wrongKey = 0;
                                            break;}
                                        case 'D':{
                                            PacX++;
                                            boardArray[PacY][PacX-1] =' ';
                                            wrongKey = 0;
                                            break;}
                                        case 'd':{
                                            PacX++;
                                            boardArray[PacY][PacX-1] =' ';
                                            wrongKey = 0;
                                            break;} 
                                        case 'M':{
                                            system("clear");
                                            resultLoop++;
                                            easterLoop++;
                                            break;}    
                                        case 'm':{
                                            system("clear");
                                            resultLoop++;
                                            easterLoop++;
                                            break;}   
                                        default:{
                                            wrongKey = 1;
                                            fgetc(stdin);
                                            break;}  
                                    }  
                                }
                            }
                        }
                        playLoop++;
                    }

                    // User-input controls
                    // Locks after winning or losing
                    if (controlLock == 0){

                        // Initalizes or updates the board game  
                        roundUpdate(boardArray, PacY, PacX);

                        // Printing current round's board game
                        printBoard(boardArray, foodChoice, foodCounter);

                        // ...pressing only wasd isn't hard at all... jk xD
                        if (wrongKey == 1){
                            printf("Wrong key!\n");
                        }

                        scanf(" %c", &playChoice);
                        switch (playChoice){
                        case 'W':{
                            PacY--;
                            boardArray[PacY+1][PacX] =' ';
                            wrongKey = 0;
                            break;}
                        case 'w':{
                            PacY--;
                            boardArray[PacY+1][PacX] =' ';
                            wrongKey = 0;  
                            break;}
                        case 'A':{
                            PacX--;
                            boardArray[PacY][PacX+1] =' ';
                            wrongKey = 0;
                            break;}
                        case 'a':{
                            PacX--;
                            boardArray[PacY][PacX+1] =' ';
                            wrongKey = 0;
                            break;}
                        case 'S':{
                            PacY++;
                            boardArray[PacY-1][PacX] =' ';
                            wrongKey = 0;
                            break;}  
                        case 's':{
                            PacY++;
                            boardArray[PacY-1][PacX] =' ';
                            wrongKey = 0;
                            break;}
                        case 'D':{
                            PacX++;
                            boardArray[PacY][PacX-1] =' ';
                            wrongKey = 0;
                            break;}
                        case 'd':{
                            PacX++;
                            boardArray[PacY][PacX-1] =' ';
                            wrongKey = 0;
                            break;} 
                        case 'M':{
                            system("clear");
                            controlLock++;
                            playLoop++;
                            break;}    
                        case 'm':{
                            system("clear");
                            controlLock++;
                            playLoop++;
                            break;}   
                        default:{
                            wrongKey = 1;
                            fgetc(stdin);
                            break;}   
                        }   
                    }
                }
                break;
            }
            case 2:{
                system("clear");
                // Instructions
                instructionMenu();
            break;
            }
            case 3:{
                system("clear");
                printf("Thank you for your time. Come again soon!\n");
                break;
                }
            default:{
                system("clear");
                printf("Invalid choice! Please try again.\n\n");
                fgetc(stdin);
                break;
                }
        }
    }
   return 0;
}