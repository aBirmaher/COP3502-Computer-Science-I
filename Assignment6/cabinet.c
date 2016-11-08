//Alan Birmaher
//COP 3502C-0001
//Assignment #6
//11/28/12

//Header Files to include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Establishes person data type
typedef struct game{
    char name[30];
    struct game* next;
} Game;

//Files
FILE* IFP;
FILE* IFP2;
FILE* OFP;

//Declare Functions
void addGame(char nameGame[29]);
int hash(char nameGame[29]);
int findGame(char nameGame[29]);
int listSize(int key);

//Global variables
Game** cabinet;
int numGames;

//Main function
void main(){

    //Opens our files
    IFP = fopen("gamelist.txt", "r");
    IFP2 = fopen("query.txt", "r");
    OFP = fopen("queryresults.out", "w");

    //Sets aside space for variables
    int numQueries=0;
    int i=0;
    int option=0;
    char tempWord[30];
    char queryGame[30];
    int location=-1;
    int hashKey=-1;
    int size=-1;

    //Read in number of games from input file 1
    fscanf(IFP, "%d", &numGames);

    //allocate memory
    cabinet = (Game**)malloc(sizeof(Game) * numGames);

    //Sets all parts of cabinet to NULL
    for(i = 0; i < numGames; i++) {
        cabinet[i] = NULL;
    }

    //Loop to read in games and add to list
    for(i=0;i<numGames;i++){
        fscanf(IFP,"%s", &tempWord);
        addGame(tempWord);
    }

    //Number of queries from file 2
    fscanf(IFP2,"%d", &numQueries);

    //Loop to read in lines in file
    for(i=0;i<numQueries;i++){
        fscanf(IFP2, "%d %s", &option, queryGame);

        //If query 1 is selected
        if(option==1){

            //Prints number of query to file
            fprintf(OFP,"Query #%d: ", i+1);

            //Finds the location where the game is stored
            location= findGame(queryGame);

            //If game was not found print that it was not found
            if(location == -1)
                fprintf(OFP, "%s was not found in the game cabinet\n", queryGame);

            //If it was found print where it was found
            else
                fprintf(OFP,"%s was found in location %d.\n", queryGame, location);
        }

        //If query 2 is selected
        else if(option==2){

            //Prints the number of query to file
            fprintf(OFP,"Query #%d: ", i+1);

            //Find the hash key for a certain game
            hashKey=hash(queryGame);

            //Gets the size of the list
            size= listSize(hashKey);

            //Determine games stored in the cabinet/hash table at location
            fprintf(OFP,"There are %d games stored at location %d.\n", size, hashKey);
        }

        //If there is an error
        else
            printf("There was a problem");

    //Puts a line break between queries
    fprintf(OFP,"\n");
    }

    //Close files
    fclose(IFP);
    fclose(IFP2);
    fclose(OFP);
}

//Adds the game node to hash table
//Precondition: There must be a name of the game to be inserted into the table
//Postcondition: Creates a new game and puts it in the hash table
void addGame(char nameGame[29]){

    //Allocate memory for node
    Game* temp = (Game*)malloc(sizeof(Game));
    strcpy(temp->name, nameGame);
    temp->next = NULL;

    //find hash of were to put game
    int hashVal= hash(nameGame);

    //If location is NULL put new node in
    if (cabinet[hashVal]==NULL) {
        cabinet[hashVal]=temp;
    }

    //If its not NULL
    else{

        //Create a helper struct
        Game* helper= cabinet[hashVal];

        //While next isn't NULL set make helper move to next
        while (helper->next != NULL)
            helper= helper->next;

        //Sets the next helper as temp
        helper->next=temp;
    }
}

//Finds the hash value
//Precondition: There must be a name of the game to be inserted into the table
//Postcondition: Returns the hash value in the form of an integer
int hash(char nameGame[29]){

    //Variables
    int value=0;
    int j=0;

    //Amount of letters
    int length=strlen(nameGame);

    //Loop produces value
    for(j=0;j<length;j++){
        value+=nameGame[j];
    }

    //Mod divides to find a value in our table to return
    int hash = (value%numGames);

    //Returns hash value
    return hash;
}

//Finds the location of the game
//Precondition: There must be a game stored in the hash table
//Postcondition:Returns the location in our hash table
int findGame(char nameGame[29]){

    //Variables
    int i;

    //Traverses the columns
    for(i=0;i<numGames;i++){
        Game* helper = cabinet[i];

        //Traverses the rows
        while(helper!=NULL){

            //If the location is found return it
            if (strcmp(nameGame,helper->name)==0)
                return i;

            //Moves to the next node
            helper= helper->next;
        }

    }

    //Indicates game was not found
    return -1;
}

//This function returns the amount of nodes at a key value
//Precondition: There must have been a hash value produced to be passed in
//Postcondition:Returns the size of the portion of our hash table
int listSize(int key){

    //if the hash key is less than zero
    if(key < 0)

        //Return -1
        return -1;

    //Sets count to 0
    int count=0;

    //Creates a helper
    Game* helper = cabinet[key];

    //Traverses the rows
    while(helper!=NULL){

        //Increases count by 1
        count++;

        //Moves to the next node
        helper= helper->next;
    }

    //Returns our counter
    return count;
}
