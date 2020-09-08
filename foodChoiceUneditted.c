#include<stdio.h>

int main()
{
	int choice;
	
	printf("Enter a number between 1 and 7 to select what food you should eat. Type 8 to Quit\n");
	scanf("%d", &choice);
	
	while(choice != 8){	
		if(choice == 1){
			printf("You should eat a nice salad.\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
		else if(choice == 2){
			printf("You should eat a pizza.\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
		else if(choice == 3){
			printf("You should have some spaghetti.\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
		else if(choice == 4){
			printf("You should enjoy a burger.\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
		else if(choice == 5){
			printf("You should have burritos.\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
		else if(choice == 6){
			printf("You should eat a sandwich.\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
		else if(choice == 7){
			printf("You should have salmon.\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
		else{
			printf("Please enter a number between 1 and 8\n");
			printf("Enter a number between 1 and 7, or enter 8 to Quit\n");
			scanf("%d", &choice);
		}
	}

}

