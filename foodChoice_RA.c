#include<stdio.h>
//need this for string to long
#include<stdlib.h>
//made this a function and used a switch statement
void writeChoice(int choice){
  switch(choice){
    case 1:
      printf("You should eat a nice salad.\n");
      break;
    case 2:
      printf("You should eat a nice pasta.\n");
      break;
    case 3:
      printf("You should eat a nice burger.\n");
      break;
    case 4:
      printf("You should eat a nice baked potato.\n");
      break;
    case 5:
      printf("You should eat a nice soup.\n");
      break;
    case 6:
      printf("You should eat a nice corn on the cob.\n");
      break;
    case 7:
      printf("You should eat a nice steak.\n");
      break;
    default:
      printf("Thank you for using our system. Goodbye.\n");
  }
}
//made this a function and protected against bad input
int getChoice(void){
  //set up a 'string'
  char inputBuffer[32];
  char *ptr;
  int number=0;
  do{
    printf("Enter an integer between 1-7 or 8 to quit.\n");
    //grab the whole line
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    //parse out an int, if no int number will be 0
    number = strtol(inputBuffer,&ptr,10);
  } while(number<1 || number>8);
  return number;
}
//main is decluttered
int main()
{
  int choiceNum;
  do{
    choiceNum = getChoice();
    writeChoice(choiceNum);
  }while(choiceNum != 8);
  return 0;	
}
