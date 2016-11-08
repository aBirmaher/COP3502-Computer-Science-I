//Alan Birmaher
//COP 3502C-0001
//Assignment #2
//9/22/12

//Including external header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declairing struct
struct property{
    char name[30];
    int user;
    int num_houses;
    int num_hotels;
    struct property *next;
};

//Set up my list pointer to head of list
struct property *myList;

//Declairing global variables
int howMany=0;
int turn=0;
char buyTemp[30];
char improveTemp[30];
char sellTemp[30];
int toBuild=0;
int choice=0;
int amntProp=0;

//Declare functions
void ownerCheck1(char propCheck[30]);
void ownerCheck2(char propCheck[30]);
void newProp(char propCheck[30]);
void impProp(char propCheck[30]);
void sellProp(char propCheck[30]);
void printProp();

//Main Function
int main (void){

    //Instantiating Variables
    int i=0;

    //Welcomes player to tracker
    printf("Welcome to the Monopoly Property Tracker!\n\n");

    //Loop occurs until the user enters an appropriate number of players
    do{

        //Prompts player for number of players
        printf("How many people are playing? (1-6 players)\n");
        scanf("%d", &howMany);

        //Checks that number of players is valid
        if(howMany<1 || howMany>6)
            printf("Invalid choice please try again.\n\n");

        //Ends the loop at correct time
        }while(howMany<=0 || howMany>6);

    //Sets the player counter to player 1
    turn=1;

    //2 X Line Breaks
    printf("\n\n");

    //Loop to run until the game is ended
    do{

        //Prints the list of options for the player
        printf("Player %d, what would you like to do?\n", turn);
        printf("    1-Buy Property\n");
        printf("    2-Improve Property\n");
        printf("    3-Sell Property\n");
        printf("    4-View Properties\n");
        printf("    5-End Turn\n");
        printf("    6-End Game\n");
        scanf("%d", &choice);
        printf("\n\n");

        //If user chooses to buy a property
        if(choice==1){

            printf("What is the name of the property you wish to buy?\n");
            scanf("%s", &buyTemp);
            printf("\n\n");

            //Checks who owns the property in question
            ownerCheck1(buyTemp);

            //Sets the temporary string back to NULL
            for (i=0;i<30;i++){
                buyTemp[i]='\0';
            }
        }

        //If user chooses to improve a property
        else if(choice==2){

            //Prompts user for which property they want to imporve
            printf("Which property would you like to improve?\n");
            scanf("%s", &improveTemp);
            printf("\n\n");

            //Checks who owns the property in question
            ownerCheck2(improveTemp);

            //Sets the temporary string back to NULL
            for (i=0;i<30;i++){
                improveTemp[i]='\0';
            }
        }

        //If user chooses to sell a property
        else if(choice==3){

            //Asks the user which property he/she wants to sell
            printf("Which property would you like to sell?\n");
            scanf("%s", &sellTemp);
            printf("\n\n");

            //Checks to see if this player owns the property in question
            ownerCheck2(sellTemp);

            //Sets the temporary string back to NULL
            for (i=0;i<30;i++){
                sellTemp[i]='\0';
            }
        }

        //Prints the current standings
        else if(choice==4){

            //Prints the current list of properties and who owns them
            printProp();
        }

        //This choice ends the turn and adds 1 to the turn counter or
        //resets it to 1 if we have done a full round
        else if(choice==5){

            if(turn == howMany)
                turn-=(howMany-1);

            else
                turn+=1;
        }

        //Prints the standings and ends the program
        else if(choice==6){
            //Prints out the final list of properties and owners
            printProp();

            //Ends the program
            break;
        }

        //If the user selected an invalid entry
        else
            printf("Invalid, try again!\n\n");

    }while(choice!=6);

    return;

}

//Function that checks if the property is owned and then according to who owns it proceeds for choice 1
void ownerCheck1(char propCheck[30]){

    //Sets up the helper pointer
    struct property *helper = myList;

    //Instantiates variables
    int flag=0;
    int player=0;
    int compare=0;

    //If no list exists yet
    if (myList==NULL)
        newProp(propCheck);

    //If list exists
    else{

        //Loop to traverse the list
        while (helper != NULL) {

            //Compares the list to see if parts exist
            compare=strcmp(helper->name,propCheck);

            //If the property exists set a flag
            if(compare==0){
                flag=1;
                player=helper->user;
            }

            //Moves to the next node
            helper = helper->next;
        }

        //The property is in our list
        if(flag==1){

            //If the property does not belong to current player
            if(player!=turn)
                printf("This is not your property.\n\n");

            //If property does belong to current player
            else
                printf("You already own this property.\n\n");

        }

        //The property does not exist yet
        else{
            newProp(propCheck);
        }

    }
}

//Function that checks if the property is owned and then according to who owns it proceeds for choice 2
void ownerCheck2(char propCheck[30]){

    //Sets up the helper pointer
    struct property *helper = myList;

    //Instantiates variables
    int flag=0;
    int player=0;
    int compare=0;

    //If no list exists yet
    if (myList==NULL)
        printf("No properties in existance yet");

    //If list exists
    else{

        //Loop to traverse the list
        while (helper != NULL) {

            //Compares the list to see if parts exist
            compare=strcmp(helper->name,propCheck);

            //If the property exists set a flag
            if(compare==0){
                flag=1;
                player=helper->user;
            }

            //Moves to the next node
            helper = helper->next;
        }

        //The property is in our list
        if(flag==1){

            //Player owns the property
            if(player==turn){

                //If the choice was to improve
                if(choice==2)
                    impProp(propCheck);

                //If choice was to sell
                else if(choice==3)
                    sellProp(propCheck);
            }

            //Another player owns the property
            else if(player!=turn)
                printf("This is not your property.\n\n");

        }

        //If the property is not in our lit
        else{
            printf("This property does not exist.\n\n");
        }
    }

}

//Function that creates a new part of the linked list
void newProp(char propCheck[30]){

    //Define struct with values
    struct property *temp = (struct property*)malloc(sizeof(struct property));
    strcpy(temp->name, propCheck);
    temp->user = turn;
    temp->num_houses = 0;
    temp->num_hotels = 0;
    temp->next = NULL;

    //Add struct to empty list
    if(myList == NULL) {
        myList= temp;
    }
    //add struct to the rest of list
    else{
        //declare helper
        struct property *helper = myList;

        //Goes to the end of the list
        while(helper->next != NULL)
            helper = helper -> next;

        //Moves the helper to the next spot
        helper->next=temp;
    }

    //Adds 1 to property counter
    amntProp+=1;
}

//Function that adds houses or hotels to properties
void impProp(char propCheck[30]){
    //Declair variables
    int whatBuild;
    int amountNumber;

    //Setup my helper
    struct property *helper = myList;

    //Put the helper in the right place
    while(strcmp(helper->name, propCheck)!=0){
        helper=helper->next;
    }

    //Asks user what they want to build
    do{
    printf("Do you wish to build houses(1) or hotels(2)?\n");
    scanf("%d", &whatBuild);

        //If the user didnt select a correct choice
        if (whatBuild != 1 && whatBuild != 2)
            printf("\nIncorrect try again\n\n");

    //While they dont enter the correct choice
    }while(whatBuild != 1 && whatBuild != 2);

    //Asks the user how many houses they want to build
    if(whatBuild==1){
        printf("How many houses do you want to build?\n");
        scanf("%d", &amountNumber);

        //Adds the number of houses to the struct for the property
        helper->num_houses += amountNumber;
    }

    //Asks the user how many houses they want to build
    else if(whatBuild==2){
        printf("How many hotels do you want to build?\n");
        scanf("%d", &amountNumber);

        //Adds the number of hotels to the struct for the property
        helper->num_hotels += amountNumber;
    }

    //Makes some space
    printf("\n");
}

//Function that removes the property from list and prints the value
void sellProp(char propCheck[30]){

    //Instantiate the value of the property
    int value=100;

    //Setup my helper
    struct property *helper = myList;
    struct property *remove = myList;

    //Keep track of what is being removed
    while(strcmp(remove->name, propCheck)!=0)
        remove=remove->next;

    //Calculates the value of the propety being sold
    value += (remove->num_hotels*50);
    value += (remove->num_houses*25);

    //Print to user what they sold ans for how much
    printf("You sold %s for $%d.00!\n\n", remove->name, value);


    //If only one on the list gets rid of it
    if(amntProp==1){
        free(remove); //free memory
        myList=NULL;
    }

    //If its in the front of the list
    else if(remove==myList){
        myList=remove->next;
        free(remove); //free memory
    }

    //If the node is at the end of the list
    else if(remove->next = NULL){

        //Keep track of the node prior to the one being removed
        while(strcmp(helper->next->name, propCheck)!=0)
            helper=helper->next;

        //Free memory
        helper->next = NULL;
        free(remove);
    }

    //If its in the middle of the list
    else{

        //Keep track of the node prior to the one being removed
        while(strcmp(helper->next->name, propCheck)!=0)
            helper=helper->next;

        //Free memory
        helper->next=remove->next;
        free(remove);
    }

    amntProp-=1;
}

//Function that prints the list of properties
void printProp() {

    //Sets up the helper pointer
    struct property *helper= myList;

    //As long as properties exist
    while (helper!= NULL){
        printf("%s, owned by player %d\n", helper->name, helper->user);
        helper=helper->next;
        printf("\n");
    }

    //Lets the user know no properties
    if (amntProp==0)
        printf("No properties owned\n\n");
}
