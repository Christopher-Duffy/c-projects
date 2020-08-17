#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


void drawBoard(char board[9]){
  printf( "\n\n     %c | %c | %c\n", board[0],board[1],board[2]);
  printf( "     ---------\n");
  printf( "     %c | %c | %c\n", board[3],board[4],board[5]);
  printf( "     ---------\n");
  printf( "     %c | %c | %c\n\n\n", board[6],board[7],board[8]);
}

void pause(void){
  puts("");
  puts("Type any character and press enter to continue...");
  char pause = 0;
  scanf(" %c",&pause);
}

bool validPlay(char state[9],int play){
  if (state[play] == 'X' || state[play] == 'O'){
    return false;
  }
  return true;
}

int computerPlay(void){
  int space=(rand()%9)+1;
  return space;
}

void gameLoop(char playerType){
  char boardState[9] ={'1', '2', '3','4', '5', '6','7', '8', '9' };
  bool playing = true;
  char pChar = playerType;
  char cChar;
  if (pChar == 'X'){
    cChar = 'O';
  }else{
    cChar = 'X';
    //computer makes play here
  }
  int counter = 0;
  while (playing){
    //draw board
    system("clear");
    drawBoard(boardState);
    //player instruction
    printf("You are playing as %c\n",pChar);
    printf("The PC is playing as %c\n",cChar);
    printf("Type a number 1-9 followed by enter.\n");
    //player move
    int pMove;
    scanf("%d",&pMove);
    pMove--;
    //if input is already taken then loop until good input
    while (!validPlay(boardState,pMove)){
      system("clear");
      drawBoard(boardState);
      printf("Invalid Play!\n\n");
      printf("You are playing as %c\n",pChar);
      printf("The PC is playing as %c\n",cChar);
      printf("Type a number 1-9 followed by enter.\n");
      scanf("%d",&pMove);
      pMove--;
    }
    //actual makes the play
    boardState[pMove] = pChar;
    counter++;
    //check player wins
    //computer move
    int cMove = computerPlay();
    while (!validPlay(boardState,cMove)){
      cMove = computerPlay();
    }
    boardState[cMove] = cChar;
    //check computer wins
    counter++;
    if (counter >= 9){
      playing = false;
      system("clear");
      drawBoard(boardState);
      printf("The game is a draw!\n");
    }
  }
  pause();
  puts(" I made it to the end of the game loop!");
}

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

char getMainMenuInput(void){
  char inputChar;
  system("clear");
  drawMainMenu();
  printf("\nMake a selection: \n");
  scanf(" %c", &inputChar);
  while (inputChar != '1' && inputChar != '2' && inputChar != '3' && inputChar != '4') {
    system("clear");
    drawMainMenu();
    printf("\nInvalid selection");
    printf("\nMake another selection: ");
    scanf(" %c", &inputChar);
  } 
  return inputChar;
}

int main()
{
  char menuChoice = getMainMenuInput();
  
  while (menuChoice != '4'){
    if (menuChoice =='1'){
      gameLoop('X');
      puts("I made it here");
    }else if (menuChoice == '2'){
      gameLoop('O');
    }else if (menuChoice == '3'){
      system("clear");
      puts("  Tic Tac Toe - Instructions");
      puts("------------------------------");
      puts("This is how to play");
      puts("This is how to play");
      puts("This is how to play");
      puts("This is how to play");
      puts("This is how to play");
      pause();
    }
    menuChoice = getMainMenuInput();
  }
  system("clear");
  printf("\nThanks for playing Tic Tac Toe! Goodbye!\n\n");
  return 0;
}
