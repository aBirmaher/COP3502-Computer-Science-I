//Alan Birmaher
//COP 3502C-0001
//Assignment #4
//10/22/12

//Header Files to include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sets up out structs for queues and stacks
typedef struct card {
    int value;
    char suit;
} Card;

typedef struct queue {
    Card* playercards[52];
    int front;
    int numElements;
    int size;
} Queue;

typedef struct stack {
    Card tablecards[52];
    int top;
} Stack;

//Files
FILE* fin;
FILE* fout;

//This function creates a queue
//Precondition: Nothing must be true for this to begin
//Postcondition: A new queue will be created and returned
Queue* initQueue() {

    //Allocaes memory for queueptr
    Queue* queueptr = (Queue*) malloc(sizeof (Queue));

    //Sets up i for use
    int i = 0;

    //Sets all vlues in the queue to empty values
    for (i = 0; i < 52; i++) {
        queueptr->playercards[i] = NULL;
    }

    //Resets all other values in the stack to where they should be
    queueptr ->front = 0;
    queueptr ->numElements = 0;
    queueptr ->size = 52;

    //Returns the new queue
    return queueptr;
}

//This dunction frees a card from memory
//Precondition: A card must be passed in
//Postcondition: Memory space is now free

Card* freeCard(Card* card) {
    free(card);

    return NULL;
}

//Checks if the queue is empty
//Precondition: There must be a queue with numElements
//Postcondition: Returns if the queue is empty or not
int queueEmpty(Queue* queueptr) {
    return queueptr->numElements == 0;
}

//Checks if the queue is full
//Precondition: There mut be a queue to check
//Postcondition: Returns an int boolean value
int queueFull(Queue* queueptr) {

    // If the size is same as the number of elemnts
    if (queueptr->size == queueptr->numElements)
        return 1; //Return yes

        //If the size isnt, meaning its not full
    else
        return 0; //Return no

}

//Takes a card from the queue and returns it
//Precondition: Must have a queue to draw from
//Postcondition: Returns a card and removes it from queue
Card* dequeue(Queue* queueptr) {

    int head;
    int check;

    if (!queueEmpty(queueptr)) {
        head = queueptr->front;
        check = (head + 1) % (queueptr->size);
        queueptr->front = check;
        (queueptr->numElements)--;
        return queueptr->playercards[head];
    } else
        return NULL;
}

//Adds a card to the queue
//Precondition: Must have a queue and card to combine
//Postcondition: There is a card added to the queue
int enqueue(Queue* queueptr, Card* toAdd) {
    int placeCheck = 0;

    if (queueFull(queueptr) == 0) {
        placeCheck = (queueptr->front + queueptr ->numElements) % queueptr->size;
        queueptr->playercards[placeCheck] = toAdd;
        (queueptr->numElements)++;
        return 1;
    }
    else
        return 0;
}

//This function frees the queue from memory
//Precondition: Must have a queue to free
//Postcondition: Queue will be freed from memory
Queue* freeQueue(Queue* queue) {
    while (!queueEmpty(queue)) {
        freeCard(dequeue(queue));
    }

    free(queue);

    return NULL;
}

//This function initializes a stack
//Precondition: Must have memory to allocate
//Postcondition: Will return a new queue
Stack* initStack() {
    //Allocates memory for the stack pointer
    Stack* stackptr = (Stack*) malloc(sizeof (Stack));

    //Set up i variable
    int i;
    //Sets all values in that memory to empty
    for (i = 0; i < 52; i++) {
        stackptr->tablecards[i].value = 0;
        stackptr->tablecards[i].suit = '\0';
    }

    //Sets the top to a value that will not interfere
    stackptr->top = -1;

    //This returns the new stack
    return stackptr;
}

//Pops a card off the stack and returns it
//Precondition: That there be a stack to pop from
//Postcondition: We will return a card off the
//stack and stack will be smaller now
Card* pop(Stack* stackptr) {

    //If the stack is empty return NULL
    if (stackEmpty(stackptr))
        return NULL;

    //Stores the value in a temporary sturct
    Card* value = &stackptr->tablecards[stackptr->top];

    //Decrements the top value of the stack
    (stackptr->top)--;
    return (value); //Returns our temporary card

}

//This function checks if the stack is empty
//Precondition: For there to be a stack to check
//Postcondition: An integer is returned to confirm
int stackEmpty(Stack* stackptr) {

    //If the top is at -1 it has not been moved and stack is empty
    if (stackptr->top == -1)
        return 1; //Returns yes

        //If the top value had been changed
    else
        return 0; //Returns no
}

//This function releases the stacks from memory
//Precondition: There be a stack to free
//Postcondition: The stack to be freed from memory
Stack* freeStack(Stack* stack) {
    while (!stackEmpty(stack)) {
        freeCard(pop(stack));
    }

    free(stack);

    return NULL;
}

//This function pushes a card onto a stack
//Precondition: That there be a stack and card to combine
//Postcondition: That the card be placed on the stack
int push(Stack* stackptr, Card tempCard) {

    //If there is no more room in the stack return 0
    if (stackFull(stackptr))
        return 0;

    //Saves the top card as a temporary
    stackptr->tablecards[stackptr->top + 1] = tempCard;

    //Increments the top of the stack
    (stackptr->top)++;

    //Returns 1 if the operation was done
    return 1;

}

//This function checks if the stack is full
//Precondition: Have a stack to check
//Postcondition: Stack will be released from memory
int stackFull(Stack* stackptr) {
    return (stackptr->top == (51));
    //Returns yes or no for top being same as top value
}

//This function checks if either queue is empty
//Precondition: Have two queues to check
//Postcondition: Return a boolean for if game is over
int gameOver(Queue* player1, Queue* player2) {
    return queueEmpty(player1) || queueEmpty(player2);
}

//This function returns the result of the hand
//Precondition: Have two cards to compare for this hand
//Postcondition: Returns what the outcome of the hand is
int turnResult(Card* card1, Card* card2) {
    // equal: war
    if (card1->value == card2->value) {
        return 1;
    }

    // card1 ace: player1 win
    if (card1->value == 1) {
        return 2;
    }

    // card2 ace: player2 win
    if (card2->value == 1) {
        return 3;
    }

    // card1 > card2: player1 wins
    if (card1->value > card2->value) {
        return 2;
    }

    // card1 > card2: player1 wins
    if (card1->value < card2->value) {
        return 3;
    }

    return -1;
}

//This function dequeues a card and pushes it on the stack
//Precondition: Having a player and stack
//Postcondition: Sends back a card
Card* drawCard(Queue* player, Stack* stack) {
    Card* card = dequeue(player);

    if(card != NULL){
        push(stack, *card);
        fprintf(fout,"%d%c\t", card->value, card->suit);
    }

    return card;
}

//What happens when war occurs
//Precondition: Need 2 players and a stack
//Postcondition: Send back a boolean value
int turnWar(Queue* player1, Queue* player2, Stack* stack) {

    Card* temp1;
    Card* temp2;

    if (drawCard(player1, stack) == NULL) {
        return 0;
    }

    if (drawCard(player2, stack) == NULL) {
        return 0;
    }

    fprintf(fout,"\n");

    temp1=drawCard(player1, stack);
    temp2=drawCard(player2, stack);

    if (temp1 == NULL) {
        return 0;
    }

    if (temp2 == NULL) {
        return 0;
    }
        fprintf(fout,"\n");

    int result = turnResult(temp1, temp2);

    if (result == 1) {
        return turnWar(player1, player2, stack);
    }
    else if (result == 2) {
        return turnWin(player1, stack);
    }
    else if (result == 3) {
        return turnWin(player2, stack);
    }
        return 1;
}

//This function is what happens when a win occurs
//Precondition: Need a player and a stack
//Postcondition: Puts the cards where they go
int turnWin(Queue* winner, Stack* stack) {
    while (!stackEmpty(stack)) {
        enqueue(winner, pop(stack));
    }

    return 1;
}

//What hapens in  turn
//Precondition: 2 players and a stack
//Postcondition: Returns outcome of turn
int gameTurn(Queue* player1, Queue* player2, Stack* stack) {
    Card* card1 = drawCard(player1, stack);
    Card* card2 = drawCard(player2, stack);

    fprintf(fout,"\n");

    if (card1 == NULL || card2 == NULL) {
        return 0;
    }

    // compare two cards
    int result = turnResult(card1, card2);

    if (result == 1) {
        fprintf(fout, "WAR\n");
        return turnWar(player1, player2, stack);
    }
    else if (result == 2) {
        return turnWin(player1, stack);
    }
    else if (result == 3) {
        return turnWin(player2, stack);
    }
    return 0;
}

//Creates a card
//Precondition: Values for card to be made
//Postcondition: Creates card
Card* initCard(int value, char suit) {
    Card* card = (Card*) malloc(sizeof(Card));

    card->value = value;
    card->suit = suit;

    return card;
}

//This function reads in the file to the queues
//Precondition: That there be a file to read in from
//Postcondition:Nothing
void readInFile(FILE* fin, Queue* player) {

    //Variables
    int i;

    //Reads in the cards for player 1
    for (i = 0; i < 26; i++) {
        Card* temp = initCard(-1, '\0');
        fscanf(fin, "%d ", &temp->value);
        fscanf(fin, "%c", &temp->suit);
        enqueue(player, temp);
    }
}

//Main
void main() {
    fin = fopen("games.txt", "r");
    fout = fopen("war.txt", "w");

    int games;
    fscanf(fin, "%d", &games);

    int i;
    for (i = 0; i < games; i++) {
        Queue* player1 = initQueue();
        Queue* player2 = initQueue();
        Stack* stack = initStack();

        readInFile(fin, player1);
        readInFile(fin, player2);

        int running = 1;
        while (running) {
            running = gameTurn(player1, player2, stack);
        }

        if(queueEmpty(player1) == 1 && queueEmpty(player2) == 1)
            fprintf(fout, "\nIts a draw!\n");
        else if(queueEmpty(player1))
            fprintf(fout, "\nPlayer 2 Wins\n");
        else if(queueEmpty(player2))
            fprintf(fout, "\nPlayer 1 Wins\n");

        //Releases the queues and stack
        player1 = freeQueue(player1);
        player2 = freeQueue(player2);
        stack = freeStack(stack);
    }

    fclose(fin);
    fclose(fout);
}
