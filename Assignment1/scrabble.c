//Alan Birmaher
//COP 3502C-0001
//Assignment #1
//9/14/12

//Including external header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Declairing global variables
char letters[7];
char inword[7];
int randNums[7];
int distribution[26];
int inpoints=0;
int howmanywords=0;
char dictionary[10000][7];
int bestpoints=0;
char bestWord[7];
int triesCount=0;

//Declare functions
void letterGenerate();
int letterCheck();
int dictCheck();
void wordPoints();

//Main function
int main(){

    //Opening File
    FILE* IFP=fopen("dictionary.txt", "r");

    //Instantiating Variables
    int choice=0;
    int flag=0;
    int keepGoing=0;
    int i=0;

    //Reads in the number of words in the dictionary
    fscanf(IFP,"%d", &howmanywords);

    //Read in all the words to the dictionary
    for(i=0; i<howmanywords; i++){
        fscanf(IFP, "%s", dictionary[i]);
    }

    //Close file
    fclose(IFP);

    //Generate Random Letters in function and return an array with the 7 letters, within the function have it check to make sure that they are correct
    letterGenerate();

    //Welcomes you to the game and prints random letter for use
    printf("Welcome to the Scrabble Practice Program!\n\n");
    printf("Here are your letters: %s\n\n", letters);

    //While look in which we actually take user input to evaluate
    while(choice!=2){

        //Prompts the user for what they want to do
        printf("What would you like to do? (Enter 1 or 2)\n");
        printf("1- Enter a word (in all UPPER CASE)\n");
        printf("2- Quit\n\n");
        printf("Choice: ");
        scanf("%d", &choice);

        //If the user chooses option 1
        if(choice==1){
            //Prompts the user for their word
            printf("Word: ");
            scanf("%s", &inword);
            printf("\n");

            //Makes sure that the word has the correct letters
            do{
                int flag=letterCheck();

                if (flag!=0){
                    printf("Invalid letters used & ");
                }
                else{
                    keepGoing=1;
                    break;
                }
            }while(flag!=0);

            //Make sure the word is a real word in the dictionary file
            do{
                int flag=dictCheck();

                keepGoing =0;

                if (flag!=0){
                    printf("Invalid word entered, please try again");
                    printf("\n\n");
                }
                else{
                    keepGoing=1;
                    break;
                }
            }while(flag!=0);

            //Find points for the word and if greater than max save the word
            if(keepGoing==1){
                wordPoints();
                triesCount++;
                //Prints out how much the user inputed word is worth
                printf("The word is worth: %d points\n\n", inpoints);
            }
        }
        //If user chooses option 2
        else if(choice==2){
            if(triesCount!=0)   //If the user entered at least one
                                //word correctly print the following
                printf("Your best word was %s worth %d points.", bestWord, bestpoints);
        }
        //If the user enters neither of these values they will be prompted to try again
        else
            printf("Incorrect input try again\n\n");
    }

    return 0;
}

void letterGenerate(){

    //Instantiating variables for the function
    int i=0, n=0, flag=0;
    char temporary[7];

    //Setting up for random generation
    int randSeed=time(NULL);
    srand(randSeed);

    //Loop that generates random numbers and checks them for correct distribution
    do{
        //Reset flag to 0
        flag=0;

        //Reset counters to zero
        for(n=0;n<25;n++){
            distribution[n]=0;
        }

        //Finds seven random capital letters and saves them in an array
        //then every letter is checked and kept track of to make sure that
        //the amount we have does not exceed that amount that we are aloud
        for(i=0; i<7; i++){
            randNums[i]=(rand()%25)+65;

            //Distribution for A
            if(randNums[i]==65){
                distribution[0]++;
                if(distribution[0]==10)
                    flag=1;
            }

            //Distribution for B
            if(randNums[i]==66){
                distribution[1]++;
                if(distribution[1]==3)
                    flag=1;
            }

            //Distribution for C
            if(randNums[i]==67){
                distribution[2]++;
                if(distribution[2]==3)
                    flag=1;
            }

            //Distribution for D
            if(randNums[i]==68){
                distribution[3]++;
                if(distribution[3]==5)
                    flag=1;
            }

            //Distribution for E
            if(randNums[i]==69){
                distribution[4]++;
                if(distribution[4]==13)
                    flag=1;
            }

            //Distribution for F
            if(randNums[i]==70){
                distribution[5]++;
                if(distribution[5]==3)
                    flag=1;
            }

            //Distribution for G
            if(randNums[i]==71){
                distribution[6]++;
                if(distribution[6]==4)
                    flag=1;
            }

            //Distribution for H
            if(randNums[i]==72){
                distribution[7]++;
                if(distribution[7]==3)
                    flag=1;
            }

            //Distribution for I
            if(randNums[i]==73){
                distribution[8]++;
                if(distribution[8]==10)
                    flag=1;
            }

            //Distribution for J
            if(randNums[i]==74){
                distribution[9]++;
                if(distribution[9]==2)
                    flag=1;
            }

            //Distribution for K
            if(randNums[i]==75){
                distribution[10]++;
                if(distribution[10]==2)
                    flag=1;
            }

            //Distribution for L
            if(randNums[i]==76){
                distribution[11]++;
                if(distribution[11]==5)
                    flag=1;
            }

            //Distribution for M
            if(randNums[i]==77){
                distribution[12]++;
                if(distribution[12]==3)
                    flag=1;
            }

            //Distribution for N
            if(randNums[i]==78){
                distribution[13]++;
                if(distribution[13]==7)
                    flag=1;
            }

            //Distribution for O
            if(randNums[i]==79){
                distribution[14]++;
                if(distribution[14]==9)
                    flag=1;
            }

            //Distribution for P
            if(randNums[i]==80){
                distribution[15]++;
                if(distribution[15]==3)
                    flag=1;
            }

            //Distribution for Q
            if(randNums[i]==81){
                distribution[16]++;
                if(distribution[16]==2)
                    flag=1;
            }

            //Distribution for R
            if(randNums[i]==82){
                distribution[17]++;
                if(distribution[17]==7)
                    flag=1;
            }

            //Distribution for S
            if(randNums[i]==83){
                distribution[18]++;
                if(distribution[18]==5)
                    flag=1;
            }

            //Distribution for T
            if(randNums[i]==84){
                distribution[19]++;
                if(distribution[19]==7)
                    flag=1;
            }

            //Distribution for U
            if(randNums[i]==85){
                distribution[20]++;
                if(distribution[20]==3)
                    flag=1;
            }

            //Distribution for V
            if(randNums[i]==86){
                distribution[21]++;
                if(distribution[21]==3)
                    flag=1;
            }

            //Distribution for W
            if(randNums[i]==87){
                distribution[22]++;
                if(distribution[22]==3)
                    flag=1;
            }

            //Distribution for X
            if(randNums[i]==88){
                distribution[23]++;
                if(distribution[23]==2)
                    flag=1;
            }

            //Distribution for Y
            if(randNums[i]==89){
                distribution[24]++;
                if(distribution[24]==3)
                    flag=1;
            }

            //Distribution for Z
            if(randNums[i]==90){
                distribution[25]++;
                if(distribution[25]==2)
                    flag=1;
            }
        }
    }while(flag==1);

    //Converts the checked numbers into letters one by one, storing them in an array
    for(i=0;i<7;i++){
        temporary[i]= (char)randNums[i];
    }

    //Copies the random letters into the global array
    strcpy(letters,temporary);
}

int letterCheck(){

    //Instantiating variables
    int refCheck[26];
    int i=0, j=0, flag=-1;

    //Copying the distribution values into a new arrray
    for(i=0;i<26;i++){
        refCheck[i]=distribution[i];
    }

    //Converts the letters of the inputted word into integers
    //and stores them in an array
    for(i=0;i<7;i++){
        j=(int)inword[i];
        if (j!=0){
            j-=65;
            refCheck[j]--;
        }
    }

    //Reset flag to -1
    flag=-1;

    //If any letter is used more than the letters provided
    //it is flagged as flag=1
    for(i=0;i<26;i++){
        if(refCheck[i]>=0)
            flag=0;
        else{
            flag=1;
            break;
        }
    }

    //Returns the correct value
    if(flag==0)
        return 0;
    else
        return 1;
}

int dictCheck(){

    //Instantiating variables
    int refCheck[26];
    int i=0, flag=-1;

    //Compare words in the dictionary to our word
    for(i=0; i<howmanywords; i++){
        if(strcmp(inword,dictionary[i])==0){
            flag=0;
            break;
        }
        else
            flag=1;
    }

    //Returns the correct value
    if(flag==0)
        return 0;
    else
        return 1;

}

void wordPoints(){

    //Instantiating variables
    int pointCount[26];
    int i=0;
    int j=0;

    //Set point count's parts to 0
    for(i=0; i<26; i++){
        pointCount[i]=0;
    }

    //Find how many of each letter exist in the word
    for(i=0;i<7;i++){
        j=(int)inword[i];
        if (j!=0){
            j-=65;
            pointCount[j]++;
        }
    }

    //Reseting the point tracking variable
    inpoints=0;

    //Multiplies the number of each letter of the word
    //by their point value and adds it to the point
    //counter for the word
    for(i=0; i<26; i++){
        if(i==0)
            inpoints+=(pointCount[i]);
        else if(i==1)
            inpoints+=(pointCount[i]*3);
        else if(i==2)
            inpoints+=(pointCount[i]*3);
        else if(i==3)
            inpoints+=(pointCount[i]*2);
        else if(i==4)
            inpoints+=(pointCount[i]);
        else if(i==5)
            inpoints+=(pointCount[i]*4);
        else if(i==6)
            inpoints+=(pointCount[i]*2);
        else if(i==7)
            inpoints+=(pointCount[i]*4);
        else if(i==8)
            inpoints+=(pointCount[i]);
        else if(i==9)
            inpoints+=(pointCount[i]*8);
        else if(i==10)
            inpoints+=(pointCount[i]*5);
        else if(i==11)
            inpoints+=(pointCount[i]);
        else if(i==12)
            inpoints+=(pointCount[i]*3);
        else if(i==13)
            inpoints+=(pointCount[i]);
        else if(i==14)
            inpoints+=(pointCount[i]);
        else if(i==15)
            inpoints+=(pointCount[i]*3);
        else if(i==16)
            inpoints+=(pointCount[i]*10);
        else if(i==17)
            inpoints+=(pointCount[i]);
        else if(i==18)
            inpoints+=(pointCount[i]);
        else if(i==19)
            inpoints+=(pointCount[i]);
        else if(i==20)
            inpoints+=(pointCount[i]);
        else if(i==21)
            inpoints+=(pointCount[i]*4);
        else if(i==22)
            inpoints+=(pointCount[i]*4);
        else if(i==23)
            inpoints+=(pointCount[i]*8);
        else if(i==24)
            inpoints+=(pointCount[i]*4);
        else if(i==25)
            inpoints+=(pointCount[i]*10);
    }

    //Sets the point value of the current word and
    //the current word itself as the highest valued
    if (inpoints>=bestpoints){
        bestpoints=inpoints;
        strcpy(bestWord,inword);
    }
}
