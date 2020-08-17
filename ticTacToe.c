#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//draws the current tic tac toe board
void drawBoard(char board[9]){
  printf( "\n\n     %c | %c | %c\n", board[0],board[1],board[2]);
  printf( "     ---------\n");
  printf( "     %c | %c | %c\n", board[3],board[4],board[5]);
  printf( "     ---------\n");
  printf( "     %c | %c | %c\n\n\n", board[6],board[7],board[8]);
}
//pauses so the user can read the screen
//there should be a way to get this to work just pressing enter, but I couldn't get it working in this context
//I think ive dirtied the input stream somehow
void pause(void){
  puts("");
  puts("Type any character and press enter to continue...");
  char pause = 0;
  scanf(" %c",&pause);
}
//checks whether a given play should be allowed on a given board
bool validPlay(char boardState[9],int play){
  //if the play space is taken or out of bounds return false
  if (boardState[play] == 'X' || boardState[play] == 'O' || play<0 || play>8){
    return false;
  }
  return true;
}
//picks a random space 0-8
int computerPlay(void){
  int space=(rand()%9);
  return space;
}
//checks if a token has won the board
bool checkWin(char boardState[9],char token){
  //check horizontals
  for (int i=0;i<7;i+=3){
   if ((boardState[i]==token)&&(boardState[i+1]==token)&&(boardState[i+2]==token)){
     return true;
   }
  }
  //check verticals
  for (int i=0;i<3;i+=1){
   if ((boardState[i]==token)&&(boardState[i+3]==token)&&(boardState[i+6]==token)){
     return true;
   }
  }
  //check diagonals
  if ((boardState[0]==token)&&(boardState[4]==token)&&(boardState[8]==token)){
     return true;
   }
   if ((boardState[2]==token)&&(boardState[4]==token)&&(boardState[6]==token)){
     return true;
   }
  return false;
}
//this is where all the magic happens
void gameLoop(char playerType){
  //init new game board
  char boardState[9] ={'1', '2', '3','4', '5', '6','7', '8', '9' };
  //this bool determines whether to continue the gameloop
  bool playing = true;
  //define x and o tokens
  char pChar = playerType;
  char cChar;
  //turn counter
  int counter = 0;
  if (pChar == 'X'){
    cChar = 'O';
  }else{
    cChar = 'X';
    //x always goes first
    int cMove = computerPlay();
    boardState[cMove] = cChar;
    counter++;
  }
  //the real gameloop
  while (playing){
    int pMove;
    do{
      //draw board
      system("clear");
      drawBoard(boardState);
      //player instruction
      printf("You are playing as %c\n",pChar);
      printf("The PC is playing as %c\n",cChar);
      printf("Type a number 1-9 followed by enter.\n");
      //player move input
      scanf("%d",&pMove);
      //decrement because array is 0-8
      pMove--;
    //if input is already taken then loop until good input
    }while (!validPlay(boardState,pMove));
    //actual makes the play
    boardState[pMove] = pChar;
    //increment turn counter
    counter++;
    //check player wins
    if (checkWin(boardState,pChar)){
      //if there is a win then stop the loop
      playing = false;
      system("clear");
      drawBoard(boardState);
      printf("You won!\n");
    }
    //if there is a win or there have been 9 plays then the computer shouldn't play
    if (playing==true && counter<9){
      //computer move
      int cMove;
      //loop until valid play is found
      //the computer is just picking 0-8 by random
      do{
        cMove = computerPlay();
      }while (!validPlay(boardState,cMove));
      boardState[cMove] = cChar;
      //check computer wins
      if (checkWin(boardState,cChar)){
        //if there is a win then stop the loop
        playing = false;
        system("clear");
        drawBoard(boardState);
        printf("You were defeated!\n");
      }else{
        //only increment if there was no win
        //otherwise there will be a false draw if the computer wins on turn 9
        counter++;
      }
    }
    //if there are 9 turns with no win there is a draw
    if (counter >= 9){
      playing = false;
      system("clear");
      drawBoard(boardState);
      printf("The game is a draw!\n");
    }
  }
  pause();
}
//draws a cool title image
void drawAsciiArt(void){
  puts(" _______ _        _______          _______");
  puts("|__   __(_)      |__   __|        |__   __|");
  puts("   | |   _  ___     | | __ _  ___    | | ___   ___");
  puts("   | |  | |/ __|    | |/ _` |/ __|   | |/ _ \\ / _ \\");
  puts("   | |  | | (__     | | (_| | (__    | | (_) |  __/");
  puts("   |_|  |_|\\___|    |_|\\__,_|\\___|   |_|\\___/ \\___|");
  puts(" ___________________________________________________");
  puts("|___________________________________________________|");
}
//shows the main menu screen
void drawMainMenu(void){
  drawAsciiArt();
  puts("");
  puts("Main Menu");
  puts("---------------------------");
  puts("1: Start a new game as X");
  puts("2: Start a new game as O");
  puts("3: View Instructions");
  puts("4: Quit game");
}
//asks for menu input until a valid option is chosen
char getMainMenuInput(void){
  char inputChar;
  do{
    system("clear");
    drawMainMenu();
    printf("\nMake a selection: \n");
    scanf(" %c", &inputChar);
  }while (inputChar != '1' && inputChar != '2' && inputChar != '3' && inputChar != '4');
  return inputChar;
}
//shows the instructions screen
void drawInstructions(void){
  system("clear");
  puts("  Tic Tac Toe - Instructions");
  puts("------------------------------");
  puts("Use Numbers 1-9 to select which space to play in.");
  puts("If you select a taken space you will be prompted to choose again.");
  puts("If you enter a non numeral you will quit the game.");
  puts("X always goes first.");
  puts("Have fun!");
}
//loops until the player quits
//takes the input from the main menu and runs the appropriate sub procedure
int main()
{
  char menuChoice;
  do{
    menuChoice = getMainMenuInput();
    if (menuChoice =='1'){
      gameLoop('X');
    }else if (menuChoice == '2'){
      gameLoop('O');
    }else if (menuChoice == '3'){
      drawInstructions();
      pause();
    }
  }while (menuChoice != '4');
  system("clear");
  printf("\nThanks for playing Tic Tac Toe! Goodbye!\n\n");
  return 0;
}
