#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LOGIN_SUCCESS 1
#define LOGIN_FAIL 0
#define MAX_USERS 10
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef union
{
    int intValue;
    bool boolValue;
} FlagValue;

typedef struct
{
    char usernames[MAX_USERNAME];
    char passwords[MAX_PASSWORD];
    FlagValue activeFlag;
} Users;

Users users[MAX_USERS];
int numberOfUsers = 0;

void displayMenu()
{
    printf("\n======================================================\n");
    printf("          USER AUTHENTICATION & REGISTRATION          ");
    printf("\n======================================================\n");
    printf("1- User Login?\n");
    printf("2- User Registration?\n");
    printf("3- Exit?\n");
}

void registerUser()
{
    printf("\n-------User Registration---------\n");

    if (numberOfUsers < MAX_USERS)
    {
        printf("Enter a username: ");
        scanf("%49s", users[numberOfUsers].usernames);

        printf("Enter a password: ");
        scanf("%49s", users[numberOfUsers].passwords);

        printf("Please detect Your Flag (1/true for Active or 0/false for InActive): ");
        char input[10];
        scanf("%s", input);

        if (strcmp(input, "1") == 0 || strcmp(input, "true") == 0)
        {
            users[numberOfUsers].activeFlag.intValue = 1;
            users[numberOfUsers].activeFlag.boolValue = true;
        }
        else if (strcmp(input, "0") == 0 || strcmp(input, "false") == 0)
        {
            users[numberOfUsers].activeFlag.intValue = 0;
            users[numberOfUsers].activeFlag.boolValue = false;
        }
        else
        {
            printf("Invalid input. Please enter 0, 1, true, or false.\n");
            return;
        }

        printf("\nUser registered successfully!\n");

        numberOfUsers++;
    }
    else
    {
        printf("\nMaximum users reached. Registration not allowed.\n");
    }
}

int loginUser()
{
    printf("\n------------User Login--------------\n");

    char inputUsername[MAX_USERNAME];
    char inputPassword[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%49s", inputUsername);

    printf("Enter your password: ");
    scanf("%49s", inputPassword);

    for (int i = 0; i < numberOfUsers; i++)
    {
        if (strcmp(inputUsername, users[i].usernames) == 0 &&
            strcmp(inputPassword, users[i].passwords) == 0)
        {
            if (users[i].activeFlag.boolValue)
            {
                printf("\nWelcome, %s! :), You Logged In successfully.\n", users[i].usernames);
                return LOGIN_SUCCESS;
            }
            else
            {
                printf("\n inactive account :(, Please Try to Register Again with an Active flag!\n");
                return LOGIN_FAIL;
            }
        }
    }

    printf("\nInvalid credentials :(,  Please Try to Login/Register Again!\n");
    return LOGIN_FAIL;
}

int main()
{
    int userChoice;

    while (true)
    {
        displayMenu();

        printf("\nPlease! Make your choice: \n");
        while (scanf("%d", &userChoice) != 1)
        {
            printf("\nInvalid input, Please enter a number!\n");
            while (getchar() != '\n')
                ;
        }

        switch (userChoice)
        {
        case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            printf("Exiting the app... \n");
            exit(0);
        default:
            printf("\nInvalid choice, Please try again with a correct choice (1, 2, or 3)!\n");
        }

        if (numberOfUsers >= MAX_USERS)
        {
            printf("\nMaximum users reached. Registration not allowed.\n");
            printf("\nYou can log in with one of your emails you registered before\n");
            loginUser();
        }
    }

    return 0;
}