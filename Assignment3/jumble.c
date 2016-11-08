//Alan Birmaher
//COP 3502C-0001
//Assignment #3
//10/5/12

//Files to include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Global Variables
FILE *IFP;
FILE *OFP;
char permIn[19];
int numWords;
char** dictionary;
int flag=0;

//Declare functions
void addDictionary();
void permCheck(char provided[], char wordCopy[], int count);
void exchangeCharacters(char wordCopy[], int i, int j);
int binarySearch(char wordCopy[]);

//Main function
void main(){

//Variables
char enterNew;
int getOut=0;
int count=0;
char wordCopy[19];

//Read in dictionary file
addDictionary();

//Opens the output file
OFP = fopen("jumbleout.txt", "w");

//Welcomes user to the program
printf("Welcome to the Jumble Puzzle Solver!\n");

//Loop to run program until user quits
do{

    //Setting our flag to zero
    flag=0;

    //Clears previous enterNew choice
    enterNew= '\0';

    // Asks the user if they want to check a word
    printf("\nWould you like to enter a jumbled world?\n");

    //Takes user ipnut and displays it back to them
    enterNew=getch();
    printf("%c\n", enterNew);

    //If the user said he would like to enter a word do this
    if (enterNew=='y' || enterNew=='Y'){

        //Asks the user for the word they would like scored and takes it
        printf("What word would you like scored?\n");
        scanf("%s", &permIn);

        //Makes a copy of the inputted leters
        strcpy(wordCopy, permIn);

        //Calls the permCheck function
        permCheck(permIn, wordCopy, count);

        //If no matches are found in the dictionary print that to screen and file
        if (flag == 0){
            printf("\nSorry, no permutations of %s form a word.\n\n", permIn);
            fprintf(OFP,"Sorry, no permutations of %s form a word.\n", permIn);
        }

    }

    //If a user did not want to enter a word set getOut to 1 to quit
    else if(enterNew=='n' || enterNew=='N'){
        getOut=1;
    }

    //If the entred option is not correct and alerts the user
    else if (enterNew!='y' || enterNew!='Y' || enterNew!='n' || enterNew!='N'){
        printf("Incorrect entry try again\n\n");
    }

}while(getOut!=1);

//Closes file
fclose(OFP);
}

//Pre-condition: To have a dictionary file to draw from
//Post-condition: The entire list from the file is saved into a 2D array
void addDictionary(){

    //Sets up variables for use
    int i;
    int letters=19;

    //Opens the dictionary file for reading
    FILE *IFP = fopen("dictionary.txt", "r");

    //Scans in the number of words in the file
    fscanf(IFP, "%d", &numWords);

    //Allocate memory for words
    dictionary = (char**)malloc(numWords * sizeof(char*));

    //Alocate memory for letters in each word & stores them in a 2D array
    for(i = 0; i < numWords; i++) {
        dictionary[i] = (char*)malloc(letters * sizeof(char));
        fscanf(IFP, "%s", dictionary[i]);
    }

    //Closes the file
    fclose(IFP);
}

//Pre-condition: Provided and word copy are the same word but two different versions. They are
//the inputted letters. Int count is a counter variable keeping track.
//Post-Condition: If there is a permutation prints what it is to the screen and file. If there is none it
//sets a flag to that it can be printed on screen and in file in the main that there is no permutation.
void permCheck(char provided[], char wordCopy[], int count){

    //Sets up variables for use
    int j=0;

    //Loop for when we have checked all possible permutations to go into
    if (count == strlen(wordCopy)){

        //If words are found they will be printed to screen and file
        if (binarySearch(wordCopy)==1){
            fprintf(OFP,"A permutation of %s that is a valid word is %s.\n", provided, wordCopy);
            printf("A permutation of %s that is a valid word is %s.\n", provided, wordCopy);
            flag=1;    //Sets a flag to 1 to indicate at least 1 word was found
        }
    }


    //Checks for all permutations by exchangeing characters and recalling perCheck
    else {
        for(j = count; j < strlen(wordCopy); j++) {
            exchangeCharacters(wordCopy, count, j);
            permCheck(provided, wordCopy, count+1);
            exchangeCharacters(wordCopy, j, count);
        }
    }

}

//Pre-condition: That word copy be a string of lettters to move around for permutation.
//Intigers i and j should have real values as well
//Post-Condition: That letters be swapped in order to move forward with permutations
void exchangeCharacters(char wordCopy[], int i, int j) {

    //Swaps letters to do permutations
    char temp = wordCopy[i];
    wordCopy[i] = wordCopy[j];
    wordCopy[j] = temp;
}

//Pre-condition: Takes in a single permutation of the given letters at a time and checks
//it against the dictionary array to see if the word is a real word.
//Post-Condition: If the word exists then it returns 1 and in the permCheck function
//we print what we find.
int binarySearch(char wordCopy[]) {

    //Set up variables for use
    int low = 0;
    int high = numWords - 1;

    //While low value is less than high value proceed
    while(low <= high) {
        int mid = (low+high)/2;
        int compare = strcmp(wordCopy, dictionary[mid]);  //Saves the value of compared words

        //Narrow down the part of the array we are looking at for comparison
        if(compare < 0)
            high = mid - 1;
        else if(compare > 0)
            low = mid + 1;
        else
            return 1;  //When finished return 1
    }

    //Returns no
    return 0;
}
