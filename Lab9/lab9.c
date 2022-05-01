#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list.
// Each string in the node is declared as a character pointer variable, so they need to be dynamically allocated using the malloc() function, 
// and deallocated using the free() function after use.

typedef struct node {
    char *artist;
    char *songName;
    char *genre;
    struct node *next;
} Node;

const int MAX_LENGTH = 1024; // The max length of any user input.

// Declarations of linked list functions
void inputStringFromUser(char *prompt, char *s, int arraySize); // Gets input from user.
void songNameDuplicate(char *songName); // Prints a message when a duplicate of the song is found in the library.
void songNameFound(char *songName); // Prints a message when a song name was found in the personal music library.
void songNameNotFound(char *songName); // Prints a message when a song name was not found in the personal music library.
void songNameDeleted(char *songName); // Prints a message when a song was deleted in the personal music library.
void artistFound(char *artist); // Prints a message when a artist name was found in the personal music library.
void artistNotFound(char *artist); // Prints a message when a artist name was not found in the personal music library.
void printMusicLibraryEmpty(void); // Prints a message when the personal music library is empty.
void printMusicLibraryTitle(void); // Prints the title of the music library.
void printList(Node *head); 
void songSearch(Node *head, char songToFind[MAX_LENGTH]); 
bool songAlreadyInList(Node *head, char songToFind[MAX_LENGTH]); 
Node *insertNewNode(Node *head, char songName[MAX_LENGTH], char artist[MAX_LENGTH], char genre[MAX_LENGTH]); 
Node *deleteSong(Node *head, char songToDelete[MAX_LENGTH]); 
Node *eraseList(Node *head); 

int main(void) 
{
    // Declare the head of the linked list.
    Node *head = NULL;
    
    char *songName, *artist, *genre;
    
    artist = (char *) malloc(MAX_LENGTH * sizeof (char));
    genre = (char *) malloc(MAX_LENGTH * sizeof (char));
    songName = (char*) malloc(MAX_LENGTH * sizeof (char));
    
    // Announce at the start of the program
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");

    char response;
    
    char input[MAX_LENGTH + 1];
    
    do 
    {
        inputStringFromUser("\nCommand", input, MAX_LENGTH); // Response is the first character entered by user.
        response = toupper(input[0]); // Convert to uppercase to simplify later comparisons.

        if (response == 'I') // Insert a song into the linked list and order it alphabeticallly by song name.
        {
            char *promptName = "Song name";
            char *promptArtist = "Artist";
            char *promptGenre = "Genre";

            inputStringFromUser(promptName, songName, MAX_LENGTH);
            inputStringFromUser(promptArtist, artist, MAX_LENGTH);
            inputStringFromUser(promptGenre, genre, MAX_LENGTH);
            
            if (!songAlreadyInList(head, songName)) 
            {
                head = insertNewNode(head, songName, artist, genre);
            } 
            
            else
            {
                songNameDuplicate(songName);
            }
        }
        
        else if (response == 'D') // Delete a song from the list.
        {
            char *prompt = "\nEnter the name of the song to be deleted";
            
            inputStringFromUser(prompt, songName, MAX_LENGTH);
            head = deleteSong(head, songName);
        }
        
        else if (response == 'S') // Search for a song by its name.
        {
            char *prompt = "\nEnter the name of the song to search for";

            inputStringFromUser(prompt, songName, MAX_LENGTH);
            songSearch(head, songName);
        }
        
        else if (response == 'P') // Print the music library.
        {
            printList(head);
        }
        
        else if (response == 'Q') // do nothing, we'll catch this below
        {
            ; 
        }
        
        else // do this if no command matched ...
        {
            printf ("\nInvalid command.\n");
        }
        
    } while (response != 'Q'); // Delete the entire linked list.

    head = eraseList(head);
    printList(head); // Print the linked list to confirm deletion.

    return 0;
}

// The following are the function definitions for the declared variables used in the main code.

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) 
{
    int i = 0;
    char c;

    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name that is already in the personal music library.
void songNameDuplicate(char *songName) 
{
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName) 
{
    printf("\nThe song name '%s' was found in the music library.\n\n", songName);
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound(char *songName) 
{
    printf("\nThe song name '%s' was not found in the music library.\n", songName);
}

// Function to call when a song name that is to be deleted in the personal music library.
void songNameDeleted(char *songName) 
{
    printf("\nDeleting a song with name '%s' from the music library.\n", songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) 
{
    printf("\nMy Personal Music Library: \n");
}
//My functions begin: 
//This fucntion has been developed to implement the P command
void printList(Node *head) 
{
    Node *current = head;
    //when empty 
    if (current == NULL)
    {
        printMusicLibraryEmpty();
    }
    //print
    else 
    {
        printMusicLibraryTitle();
        //iterate throughout the list
        while (current != NULL)
        {
            printf("\n");
            printf("%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            current = current -> next;
        }
    }
}

//This fucntion has been developed to implement the S command. It shall search through the list for a song, if found print, else print error message. 
void songSearch(Node *head, char songToFind[MAX_LENGTH]) 
{
    //empty
    if (head == NULL)
    {
        songNameNotFound(songToFind);
        return;
    }
    
    Node *current = head;
    
    while (current != NULL) 
    {
        //iterate through all the nodes
        if (strcmp(current -> songName, songToFind) == 0) 
        {
            songNameFound(songToFind);
            printf("\n");
            printf("%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            return;
        }
        current = current -> next;
    }
    //not found
    songNameNotFound(songToFind);
    return;
}

//Helper function: If the song exists in the linked list
bool songAlreadyInList(Node *head, char songToFind[MAX_LENGTH])
{   //when head is empty
    if (head == NULL)
    {
        return false;
    }   
    
    Node *current = head;
    while (current != NULL) 
    {
        if (strcmp(current->songName, songToFind) == 0)
        {
            return true; //exists
        }
        
        current = current -> next;
    }
    
    return false;
}

//This function has been developed to implement the I Fucntion. It takes in the input data from the user as paramenters and inserts it into the list
Node *insertNewNode(Node *head, char songName[MAX_LENGTH], char artist[MAX_LENGTH], char genre[MAX_LENGTH]) 
{
    Node *next = head; //to insert first node
    if (head == NULL || strcmp(head -> songName, songName) > 0) 
    {
        Node *insert = (Node *) malloc( sizeof(Node));
        insert -> songName = (char *) malloc(MAX_LENGTH * sizeof(char));
        insert -> artist = (char *) malloc(MAX_LENGTH * sizeof(char));
        insert -> genre = (char *) malloc(MAX_LENGTH * sizeof(char));
        if (insert != NULL) 
        {
            strcpy(insert -> songName, songName);
            strcpy(insert -> artist, artist);
            strcpy(insert -> genre, genre);
            insert -> next = next;
        }
        return insert;
    }
    
    Node *current = head;
    //to insert in the order
    while (current -> next != NULL && strcmp(current -> next -> songName, songName) < 0) 
    {
        current = current -> next;
    }
    
    Node *insert = (Node *) malloc(sizeof (Node));
    insert -> songName = (char *) malloc(MAX_LENGTH * sizeof (char));
    insert -> artist = (char *) malloc(MAX_LENGTH * sizeof (char));
    insert -> genre = (char *) malloc(MAX_LENGTH * sizeof (char));
    if (insert != NULL) 
    {
        strcpy(insert -> songName, songName);
        strcpy(insert -> artist, artist);
        strcpy(insert -> genre, genre);
        insert->next = current->next;
    }
    current -> next = insert;
    return head;
}

//This function has been developed to implement the D command
Node *deleteSong(Node *head, char songToDelete[MAX_LENGTH]) 
{
    if (head == NULL)
    {
        songNameNotFound(songToDelete);
        return NULL;
    }
    
    //In case the first node has been commanded to be deleted
    if (strcmp(head -> songName, songToDelete) == 0) 
    {
        Node *secondNode = head -> next;
        songNameDeleted(head -> songName);
        free(head -> songName);
        free(head -> artist);
        free(head -> genre);
        free(head); 
        return secondNode;
    }
    
    bool songFound = false;
    
    Node *current = head;
    
    while (!songFound && current -> next != NULL) 
    {
        if (strcmp(current -> next -> songName, songToDelete) == 0)
        {
            songFound = true;
        }
        
        else
        {
            current = current -> next;
        }
    }
    
    //if node exists
    if (current -> next != NULL) 
    {
        Node *songToRemove = current -> next;
        current -> next = current -> next -> next;
        songNameDeleted(songToRemove -> songName);
        free(songToRemove -> songName);
        free(songToRemove -> artist);
        free(songToRemove -> genre);
        free(songToRemove); 
    } else songNameNotFound(songToDelete);
    
    return head;
}

//This function has been developed for implementing the Quit Q command
Node *eraseList(Node *head) 
{
    if (head == NULL)
    {
        return head;
    }
    
    while (head != NULL) 
    {
        Node *firstNode = head;
        head = head -> next;
        songNameDeleted(firstNode -> songName);
        free(firstNode -> songName);
        free(firstNode -> artist);
        free(firstNode -> genre);
        free(firstNode); 
    }

    return head;
}