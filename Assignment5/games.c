//Alan Birmaher
//COP 3502C-0001
//Assignment #5
//11/11/12

//Header Files to include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Establishes person data type
typedef struct person{
    char name[20];
    char game[20];
} Person;

//Establishes node data type
typedef struct Node{
    Person data;
    struct Node * left;
    struct Node * right;
} Node;

//Files
FILE* IFP;
FILE* OFP;

//Declare Functions
Node* createNode(char tempName[], char tempGame[]);
Node* add(Node* root, Node* element);
Node* removeNode(Node* root, char name[]);
Node* findNode(Node* root, char name[]);
Node* parent(Node* root, Node* node);
Node* minVal(Node* root);
Node* maxVal(Node* root);
int isLeaf(Node* node);
int hasOnlyLeftChild(Node* node);
int hasOnlyRightChild(Node* node);
void printGame(Node* root, char gameName[]);
void print(Node* root);
void part2(Person* players, int counter);
void mergeSort(Person* players, int start, int end);
void merge(Person* players, int start, int mid, int end);

//Main function
void main(){

    //Opens our files
    IFP = fopen("party.txt", "r");
    OFP = fopen("partygames.out", "w");

    //Sets aside space for variables
    Node* root = NULL;
    char gameIn[20];
    char nameIn[20];
    char option[20];

    //For part 2
    Person* players=NULL;
    int counter=0;
    int count;

    //Do while loop to run until option two has been selected and executed
    do{
        //Reads in the option from the file
        fscanf(IFP,"%s ", &option);

        //If ADD is the command
        if(strcmp(option,"ADD")==0){
            fscanf(IFP,"%s %s ", &nameIn, &gameIn);        //Scans in information
            Node* element= createNode(nameIn, gameIn);     //Creates a node with the info
            root=add(root, element);                       //Root element

            //For part 2

            //Increments the counter for the array
            counter++;

            //If this is the first person to be added
            if(counter==1){

                //Allocate Memory
                players = (Person*)malloc(sizeof(Person));

                //Put the data into the array
                strcpy(players[0].name,nameIn);
                strcpy(players[0].game,gameIn);

            }

            else{

                //Reallocates memory
                players=(Person*)realloc(players,counter*sizeof(Person));

                //Puts the data into the array
                strcpy(players[counter-1].name,nameIn);
                strcpy(players[counter-1].game,gameIn);

            }
        }

        //If Remove is the command
        else if(strcmp(option,"REMOVE")==0){
            fscanf(IFP,"%s ", &nameIn);         //Scans in information

            //Part 2

            //Set up variables for use
            int i, j;

            //Decreases the number of elements in our array
            counter--;

            //Alocates memory for a temporary array
            Person* temp = (Person*)malloc(counter * sizeof(Person));

            //Reads through the array and takes out the node to delete
            for(i=0;i<counter+1;i++){
                if(strcmp(players[i].name,nameIn)!=0){
                    if(i>counter-1)
                        j=i-1;
                    else
                        j=i;

                        //Copies the values into out temporary array
                        temp[j]=players[i];
                }
            }

            //Frees the memory for the array and original array pointer set equal to new array
            free(players);
            players=temp;
        }

        //If PRINTGAME is the command
        else if(strcmp(option,"PRINTGAME")==0){
            fscanf(IFP,"%s ", &gameIn);         //Reads from file
            fprintf(OFP,"%s:\n",gameIn);        //Prints to file
            printGame(root, gameIn);            //Calls print game function
            fprintf(OFP,"\n");                  //Prints a blank line in file
        }

        //If PRINT is the command
        else if(strcmp(option,"PRINT")==0){
            fprintf(OFP,"Print:\n");            //Prints the heading
            print(root);                        //Prints whats in the tree to file
            fprintf(OFP,"\n");                  //Prints a blank line to file
        }

        //If PART2 is the command
        else if(strcmp(option,"PART2")==0){

            //Runs the PART2 function of the program
            part2(players,counter);
        }

        //If none of the options were selected
        else{
            //Tells the user if there was incorrect file input
            printf("Incorrect file input, try again.");
        }

    }while(strcmp(option,"PART2")!=0);          // While option is not part 2

    //Close files
    fclose(IFP);
    fclose(OFP);

    //Return
    return;

}

//This function creates a temporary node with the file input
//Precondition: There must exist a name and game to put into a node
//Postcondition: A node with the new information is returned
Node* createNode(char tempName[], char tempGame[]){

    Node* temp=(Node*)malloc(sizeof(Node));     //Allocates memory for temporary node
    strcpy(temp->data.game, tempGame);          //Copies information into temp
    strcpy(temp->data.name, tempName);
    temp->left=NULL;                            //Sets the left and right parts of the struct to NULL
    temp->right=NULL;
    return temp;                                //Returns the temp node
}

//This command adds a new person
//Precondition: There must exist a node with the new information
//Postcondition: A node with the new information is returned in the correct location
Node* add(Node* root, Node* element){

    //If the root does not exist yet return the element
    if(root == NULL)
        return element;

    //If the root does exist
    else
    {
        //Decides which side to place the node on in a tree
        if(strcmp(element->data.name, root -> data.name) > 0)
            root -> right = add(root->right, element);
        else
            root -> left = add(root->left, element);

        //Returns the node
        return root;
    }
}

//This command should remove the person with the indicated name
//Precondition: There must exist a name and node matching that name
//Postcondition: The new tree's node is returned
Node* removeNode(Node* root, char name[]){

    //Sets up the variables and nodes
    Node* delnode;
    Node* new_del_node;
    Node* save_node;
    Node* par;
    char save_val[20];

    //Calls findNode and returns into delnode
    delnode=findNode(root, name);

    //If delnode is NULL
    if(delnode == NULL)
        return root;        //Reutns the root

    //Saves the parent of the node into par
    par=parent(root, delnode);

    //Removes the node and rebuilds other connections
    if(isLeaf(delnode)){
        if(par==NULL){
            free(root);                                     //Free memory
            return NULL;
        }
        if(strcmp(name, root -> data.name) <= 0){       //Left
            free(par->left);
            par->left=NULL;
        }
        else{
            free(par->right);                           //Right
            par->right=NULL;
        }
        return root;                                    //Returns root
    }

    if(hasOnlyLeftChild(delnode)){
        if(par==NULL){
            save_node=delnode->left;
            free(delnode);
            return save_node;
        }
        if(strcmp(name, root -> data.name)<=0){
            save_node=par->left;
            par->left=par->left->left;
            free(save_node);
        }
        else{
            save_node=par->right;
            par->right=par->right->right;
            free(save_node);
        }
        return root;
    }

    if(hasOnlyRightChild(delnode)){
        if(par==NULL){
            save_node=delnode->right;
            free(delnode);
            return save_node;
        }
        if(strcmp(name, root -> data.name)<=0){
            save_node=par->left;
            par->left=par->left->right;
            free(save_node);
        }
        else{
            save_node=par->right;
            par->right=par->right->right;
            free(save_node);
        }
        return root;
    }

    new_del_node=minVal(delnode->right);
    strcpy(save_val,new_del_node->data.name);
    removeNode(root,save_val);
    strcpy(delnode->data.name,save_val);
    return root;
}

//This function finds a specific node
//Precondition: There must exist a name for comparison and a root node to explore from
//Postcondition: The correct node is returned
Node* findNode(Node* root, char name[]){

    //If the root is NULL
    if(root!=NULL){
        if(strcmp(root->data.name, name)==0)    //If name and the input name match
            return root;                        //Return root

        if(strcmp(root->data.name, name)<=0)
            return findNode(root->left, name);  //Goes left in search of node (recursion)
        else
            return findNode(root->right, name); //Goes right in search of node (recursion)
    }

    //If root is not NULL return NULL
    else
        return NULL;
}

//This function finds what the parent of a node is
//Precondition: There must exist a root and node
//Postcondition: The parent node is returned
Node* parent(Node* root, Node* node){

    //If root is NULL or same as node
    if(root==NULL||root==node)
        return NULL;            //Reutnr NULL

    //If right or left matches node
    if(root->left==node||root->right==node)
        return root;            //Reutrn root

    //If the name from node is less than the root one
    if(strcmp(node -> data.name, root -> data.name) <= 0)
        return parent(root->left, node);    //Calls parent function
    else
        return parent(root->right, node);   //Callc parent function

    return NULL;
}

//Finds the minimum value in the tree
//Precondition: There must exist a root node to explore from
//Postcondition: A node with minimum value is returned
Node* minVal(Node* root){

    //If there is no left root
    if(root->left==NULL)
        return root;                //Return root

    else
        return minVal(root->left);  //Recurses minValue
}

//Finds the maximum value in the tree
//Precondition: There must exist a root node to explore from
//Postcondition: A node with maximum value is returned
Node* maxVal(Node* root){

    //I the right root is NULL
    if(root->right==NULL)               //If root right is NULL
        return root;                    //Returns the root
    else
        return maxVal(root->right);     //Recurses the function
}

//Returns a binary if the node is a leaf or not
//Precondition: There must exist a node to examine
//Postcondition: A binary value depending on if the node is a leaf
int isLeaf(Node* node){

    //Returns if the left or right node is NULL
    return(node->left==NULL&&node->right==NULL);
}

//Checks if a node has only a left child
//Precondition: There must exist a node to examine
//Postcondition: A binary value is returned
int hasOnlyLeftChild(Node* node){

    //Returns if left node exists but right does not
    return(node->left!=NULL&&node->right==NULL);
}

//Checks if a node has only a right child
//Precondition: There must exist a node to examine
//Postcondition: A binary value is returned
int hasOnlyRightChild(Node* node){

    //Returns whether left is not null and right isn't NULL
    return(node->left==NULL&&node->right!=NULL);
}

//This function prints the names of all the people whose favorite game is indicated
//Precondition: There must exist a root node and game name for comparison
//Postcondition: The list of names is printed to the output file
void printGame(Node* root, char gameName[]){

    //If root is not NULL
    if(root!=NULL){
        printGame(root->left, gameName);            //Recurssion

        //If they are the same thing print to file
        if(strcmp(gameName,root->data.game)==0)
            fprintf(OFP,"%s\n", root->data.name);

        //Recusion
        printGame(root->right, gameName);
    }

}

//Print the names of all the people in the BST with their favorite game
//Precondition: There must exist a node to examine
//Postcondition: The list of names/ games is printed to the output file
void print(Node* root){

    //If root is not NULL
    if(root!=NULL){
        print(root->left);                      //Recursion with left root
        fprintf(OFP,"%s ",root->data.name);     //Prints name to file
        fprintf(OFP,"%s\n",root->data.game);    //Prints game to file
        print(root->right);                     //Recursion with right root
    }
}

//This command should begin part two of the program
//Precondition: Thats there be an array to examine and a counter value
//Postcondition: The list of people and their games printed to file alphabetically
void part2(Person* players, int counter){

    //Setting up variables
    int i=0;
    char temp[20];

    //Print the part 2 header
    fprintf(OFP,"---PART 2---\n");

    //Calls the merge sort function to sort the array
    mergeSort(players,0,counter-1);

    //Loop to print whole array
    for(i=0; i<counter;i++){

        //Checks to see if the player still has the same game and if not
        //prints the new game name
        if(strcmp(temp, players[i].game)!=0){
            strcpy(temp, players[i].game);
            fprintf(OFP,"%s\n", temp);
        }

        //prints the person's name to the file
        fprintf(OFP, "\t%s\n", players[i].name);
    }
}

//Combines two arrays into one sorted one
//Precondition: Thats there be an array to examine and a start and end value
//Postcondition: A sorted array is the result
void mergeSort(Person* players, int start, int end){

    //Variables
    int mid;

    //If start is less than end
    if(start<end){
        mid=(start+end)/2;                  //Calculate mid
        mergeSort(players, start, mid);     //Calls merge sort
        mergeSort(players, mid+1, end);     //Calls merge sort
        merge(players, start, mid+1, end);  //Calls merge
    }
}

//Breaks array into 2 and sorts those and then sorts the two toegther
//Precondition: Thats there be an array to examine and a start, middle and end value
//Postcondition: A sorted array is the result
void merge(Person* players, int start, int mid, int end){

    //Variables
    Person* temp;
    int i;
    int length;
    int count1;
    int count2;
    int mc;

    //Memory allocation for temp
    temp = (Person*)calloc(length, sizeof(Person));

    //Sets values to variables
    count1 = start;
    count2 = mid;
    mc = 0;

    //While count is less than mid and count2 is less than or equal to end
    while((count1<mid)||(count2<=end)){

        //If count is more than end or count1 is less than mid and pleayers names are less than 0
        if(count2>end||(count1<mid&&(strcmp(players[count1].game,players[count2].game)<0))){
            temp[mc]=players[count1];           //Players[count1] into temp[mc]
            count1++;                           //Adds 1 to count1
            mc++;                               //Adds 1 to mc
        }
        else{
            temp[mc]=players[count2];
            count2++;                           //Adds 1 to count2
            mc++;                               //Adds 1
        }
    }

    //Cycles through the array copying values
    for(i=start;i<=end;i++)
        players[i]=temp[i-start];


    //Free memory
    free(temp);
}
