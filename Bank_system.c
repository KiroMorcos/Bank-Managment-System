#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <direct.h>
#define MAX_ACCOUNTS 100
#define Max_Attempts 5
int actual_accounts;

typedef struct
{
    char name[20];
    char password[20];
} user;

typedef struct
{
    int month;
    int year;
} date;

typedef struct
{
    char account_number[20];
    char name[50];
    char mobile[12];
    char email[100];
    double balance;
    date date_opened;
} account;

int Login()
{
    user userinput;
    user readuser;
    int selection;
    int attempts = 0;
    FILE *f = fopen("users.txt", "r");
    if (f == NULL)
    {
        printf("ERROR opening users file !\n");
        return 0;
    }
    do
    {
        attempts++;
        printf("---------------------------------\n");
        printf("Enter Username :");
        gets(userinput.name);
        printf("Enter Password :");
        gets(userinput.password);
        while (!feof(f))
        {
            fscanf(f, "%s %s", readuser.name, readuser.password);
            if (strcmp(userinput.name, readuser.name) == 0 && strcmp(userinput.password, readuser.password) == 0)
            {
                fclose(f);
                printf("---------------------------------\n");
                printf("Logged In Successfully .\n");
                printf("---------------------------------\n");
                return 1;
            }
        }
        printf("---------------------------------\n");
        printf("Incorrect Username or Password .\n");
        printf("---------------------------------\n");
        if (attempts > Max_Attempts)
        {
            printf("Too many login attempts!!\nPlease try again later .\n");
            printf("---------------------------------\n");
            return 0;
        }
        do
        {
            printf("Choose an option:\n1-TRY AGAIN\n2-QUIT\n");
            printf("---------------------------------\n");
            scanf("%d", &selection);
            getchar();
        } while (selection != 1 && selection != 2);
        if (selection == 2)
            return 0;
        rewind(f);
    } while (1);
}

void load_accounts(account accounts[])
{
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL)
    {
        printf("There are no accounts .\n");
        return;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);
    char temp[size + 1];
    while (fgets(temp, size, f) != NULL)
    {
        char *token = strtok(temp, ",");
        strcpy(accounts[(actual_accounts)].account_number, token);
        token = strtok(NULL, ",");
        strcpy(accounts[(actual_accounts)].name, token);
        token = strtok(NULL, ",");
        strcpy(accounts[(actual_accounts)].email, token);
        token = strtok(NULL, ",");
        accounts[(actual_accounts)].balance = atof(token);
        token = strtok(NULL, ",");
        strcpy(accounts[(actual_accounts)].mobile, token);
        token = strtok(NULL, "-");
        accounts[(actual_accounts)].date_opened.month = atoi(token);
        token = strtok(NULL, "\n");
        accounts[(actual_accounts)].date_opened.year = atoi(token);
        actual_accounts++;
    }
    fclose(f);
}

void Print_Accounts(account accounts[], int index)
{
    char month[12];
    switch (accounts[index].date_opened.month)
    {
    case 1:
        strcpy(month, "January");
        break;
    case 2:
        strcpy(month, "February");
        break;
    case 3:
        strcpy(month, "March");
        break;
    case 4:
        strcpy(month, "April");
        break;
    case 5:
        strcpy(month, "May");
        break;
    case 6:
        strcpy(month, "June");
        break;
    case 7:
        strcpy(month, "July");
        break;
    case 8:
        strcpy(month, "August");
        break;
    case 9:
        strcpy(month, "September");
        break;
    case 10:
        strcpy(month, "October");
        break;
    case 11:
        strcpy(month, "November");
        break;
    case 12:
        strcpy(month, "December");
        break;
    }
    printf("---------------------------------\n");
    printf("Account Number : %s\n", accounts[index].account_number);
    printf("Name : %s\n", accounts[index].name);
    printf("E-mail : %s\n", accounts[index].email);
    printf("Balance : %.3lf$\n", accounts[index].balance);
    printf("Mobile : %s\n", accounts[index].mobile);
    printf("Date Opened : %s %d\n", month, accounts[index].date_opened.year);
    printf("---------------------------------\n");
}

void SAVE(account accounts[])
{
    int i;
    FILE *f = fopen("accounts.txt", "w");
    for (i = 0; i < (actual_accounts)-1; i++)
    {
        fprintf(f, "%s,", accounts[i].account_number);
        fprintf(f, "%s,", accounts[i].name);
        fprintf(f, "%s,", accounts[i].email);
        fprintf(f, "%.2lf,", accounts[i].balance);
        fprintf(f, "%s,", accounts[i].mobile);
        fprintf(f, "%d-%d\n", accounts[i].date_opened.month, accounts[i].date_opened.year);
    }
    fprintf(f, "%s,", accounts[i].account_number);
    fprintf(f, "%s,", accounts[i].name);
    fprintf(f, "%s,", accounts[i].email);
    fprintf(f, "%.2lf,", accounts[i].balance);
    fprintf(f, "%s,", accounts[i].mobile);
    fprintf(f, "%d-%d", accounts[i].date_opened.month, accounts[i].date_opened.year);
    fclose(f);
}

char *GenerateAccNum()
{
    char *Num = malloc(sizeof(char) * 11);
    srand(time(0));
    int i = 0;
    int n = (rand() % 10) + 1;
    itoa(n, Num, 10);
    i++;
    while (i < 10)
    {
        n = rand() % 10;
        itoa(n, Num + i, 10);
        i++;
    }
    return Num;
}

int Validate_AccNum(char *accnum)
{
    if (accnum == NULL)
    {
        printf("Invalid Account Number.\n");
        return 0;
    }
    int i;
    int size = strlen(accnum);
    if (size != 10)
    {
        printf("Invalid Account Number.\n");
        return 0;
    }
    for (i = 0; i < size; i++)
        if (!isdigit(accnum[i]))
        {
            printf("Invalid Account Number.\n");
            return 0;
        }
    return 1;
}

int Validate_Name(char *Name)
{
    if (Name == NULL)
    {
        printf("Invalid Name.\n");
        return 0;
    }
    int size = strlen(Name);
    for (int i = 0; i < size; i++)
    {
        if (!isalpha(Name[i]) && Name[i] != ' ')
        {
            printf("Invalid Name.\n");
            return 0;
        }
    }
    return 1;
}

int Validate_Phone(char *Phone)
{
    if (Phone == NULL)
    {
        printf("Invalid Phone Number.\n");
        return 0;
    }
    int size = strlen(Phone);
    for (int i = 0; i < size; i++)
    {
        if (!isdigit(Phone[i]))
        {
            printf("Invalid Phone Number.\n");
            return 0;
        }
    }
    if (size != 11)
    {
        printf("Invalid Phone Number.\n");
        return 0;
    }
    if (Phone[0] != '0' || Phone[1] != '1')
    {
        printf("Invalid Phone Number.\n");
        return 0;
    }
    if (Phone[2] != '2' && Phone[2] != '5' && Phone[2] != '1' && Phone[2] != '0')
    {
        printf("Invalid Phone Number.\n");
        return 0;
    }
    return 1;
}

int Validate_Mail(char *Mail)
{
    if (Mail == NULL)
    {
        printf("Invalid Email Address.\n");
        return 0;
    }
    int i;
    int atcount = 0;
    int length = strlen(Mail);
    for (i = 0; i < length; i++)
    {
        if (Mail[i] == '@')
        {
            atcount++;
        }
    }
    if (atcount != 1)
    {
        printf("Invalid Email Address.\n");
        return 0;
    }
    char *prefix = strtok(Mail, "@");
    char *domain = strtok(NULL, ".");
    int prefixlength = strlen(prefix);
    int domainlength = strlen(domain);
    for (i = 0; i < prefixlength; i++)
    {
        if (!isalnum(prefix[i]) && prefix[i] != '-' && prefix[i] != '_' && prefix[i] != '.')
        {
            printf("Invalid Email Address.\n");
            return 0;
        }
        if (prefix[i] == '-' || prefix[i] == '_' || prefix[i] == '.')
        {
            if (!isalnum(prefix[i + 1]))
            {
                printf("Invalid Email Address.\n");
                return 0;
            }
        }
    }
    for (i = 0; i < domainlength; i++)
    {
        if (!isalnum(domain[i]) && domain[i] != '-')
        {
            printf("Invalid Email Address.\n");
            return 0;
        }
    }
    domain = strtok(NULL, "\n");
    domainlength = strlen(domain);
    if (domainlength < 2)
    {
        printf("Invalid Email Address.\n");
        return 0;
    }
    for (i = 0; i < domainlength; i++)
    {
        if (!isalpha(domain[i]))
        {
            printf("Invalid Email Address.\n");
            return 0;
        }
    }
    return 1;
}

double Validate_Amount(char *Amount)
{
    if (Amount == NULL)
        return -1.0;
    int length = strlen(Amount);
    int num_dot = 0;
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(Amount[i]) && Amount[i] != '.')
            return -1.0;
        else if (Amount[i] == '.')
            num_dot++;
    }
    if (num_dot > 1)
        return -1.0;
    double realAmount = atof(Amount);
    return realAmount;
}

void ADD(account accounts[])
{
    int selection;
    int flag = 0;
    char name[50], email[100], mobile[12];
    actual_accounts++;
    char *Number = GenerateAccNum();
    do
    {
        for (int i = 0; i < actual_accounts; i++)
        {
            if (strcmp(accounts[i].account_number, Number) == 0)
            {
                flag = 1;
                Number = GenerateAccNum();
                break;
            }
        }
    } while (flag);
    do
    {
        printf("Enter Name: ");
        gets(name);
        if (Validate_Name(name) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_Name(name) == 0 && selection == 1);
    int validateMail;
    do
    {
        printf("Enter E-mail: ");
        gets(email);
        validateMail = Validate_Mail(email);
        if (validateMail == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (validateMail == 0 && selection == 1);
    do
    {
        printf("Enter Phone Number: ");
        gets(mobile);
        if (Validate_Phone(mobile) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_Phone(mobile) == 0 && selection == 1);
    do
    {
        printf("SAVE OR DISCARD ?\n1-SAVE\n2-DISCARD\n");
        scanf("%d", &selection);
        getchar();
        if (selection != 1 && selection != 2)
        {
            printf("Invalid selection .\n");
            printf("---------------------------------\n");
        }
    } while (selection != 1 && selection != 2);
    if (selection == 1)
    {
        strcpy(accounts[actual_accounts - 1].account_number, Number);
        strcpy(accounts[actual_accounts - 1].name, name);
        strcpy(accounts[actual_accounts - 1].mobile, mobile);
        strcpy(accounts[actual_accounts - 1].email, email);
        accounts[(actual_accounts)-1].balance = 0.0;
        time_t t = time(NULL);
        struct tm dateopened = *localtime(&t);
        accounts[(actual_accounts)-1].date_opened.month = dateopened.tm_mon + 1;
        accounts[(actual_accounts)-1].date_opened.year = dateopened.tm_year + 1900;
        SAVE(accounts);
        char *filename;
        strcpy(filename, accounts[actual_accounts - 1].account_number);
        strcat(filename, ".txt");
        FILE *F = fopen(filename, "w");
        fclose(F);
        return;
    }
    else
    {
        actual_accounts--;
        return;
    }
}

void Delete(account accounts[])
{
    int i;
    int flag = 0;
    char delaccnum[20];
    int selection;
    do
    {
        printf("Enter Account Number To DELETE : ");
        gets(delaccnum);
        if (Validate_AccNum(delaccnum) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_AccNum(delaccnum) == 0 && selection == 1);
    for (i = 0; i < actual_accounts; i++)
    {
        if (strcmp(delaccnum, accounts[i].account_number) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("Error, Cannot Find Entered Account Number .\n");
    else
    {
        if (accounts[i].balance > 0)
        {
            printf("Account with entered account number cannot be deleted .\n");
        }
        else
        {
            int selection;
            do
            {
                printf("Account Deleted Successfully .\n");
                printf("SAVE OR DISCARD ?\n1-SAVE\n2-DISCARD\n");
                scanf("%d", &selection);
                if (selection != 1 && selection != 2)
                {
                    printf("Invalid selection .\n");
                    printf("---------------------------------\n");
                }
                getchar();
            } while (selection != 1 && selection != 2);
            if (selection == 1)
            {
                account temp;
                for (i = i; i < (actual_accounts); i++)
                {
                    temp = accounts[i + 1];
                    accounts[i + 1] = accounts[i];
                    accounts[i] = temp;
                }
                (actual_accounts)--;
                SAVE(accounts);
                char *filename;
                strcpy(filename, delaccnum);
                strcat(filename, ".txt");
                remove(filename);
                return;
            }
            else
                return;
        }
    }
}

void MODIFY(account accounts[])
{
    int i;
    int flag = 0;
    int flag1 = 0, flag2 = 0, flag3 = 0;
    int selection;
    char accnum[20];
    char newName[50];
    char newMobile[12];
    char newEmail[100];
    do
    {
        printf("Enter Account Number: ");
        gets(accnum);
        if (Validate_AccNum(accnum) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_AccNum(accnum) == 0 && selection == 1);
    for (i = 0; i < actual_accounts; i++)
    {
        if (strcmp(accounts[i].account_number, accnum) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("Error, Cannot Find Entered Account Number .\n");
    else
    {
        do
        {
            printf("DO YOU WANT TO MODIFY NAME ?\n1-YES\n2-NO\n");
            scanf("%d", &selection);
            if (selection != 1 && selection != 2)
            {
                printf("Invalid selection .\n");
                printf("---------------------------------\n");
            }
            getchar();
        } while (selection != 1 && selection != 2);
        if (selection == 1)
        {
            do
            {
                printf("Enter New Name: ");
                gets(newName);
                if (Validate_Name(newName) == 0)
                {
                    do
                    {
                        printf("1-Try Again\n2-Exit\n");
                        scanf("%d", &selection);
                        getchar();
                        if (selection != 1 && selection != 2)
                            printf("Invalid Selection.\n");
                        else if (selection == 2)
                            return;
                    } while (selection != 1 && selection != 2);
                }
            } while (Validate_Name(newName) == 0 && selection == 1);
            flag1 = 1;
        }
        do
        {
            printf("DO YOU WANT TO MODIFY EMAIL ?\n1-YES\n2-NO\n");
            scanf("%d", &selection);
            if (selection != 1 && selection != 2)
            {
                printf("Invalid selection .\n");
                printf("---------------------------------\n");
            }
            getchar();
        } while (selection != 1 && selection != 2);
        if (selection == 1)
        {
            do
            {
                printf("Enter New Email: ");
                gets(newEmail);
                if (Validate_Mail(newEmail) == 0)
                {
                    do
                    {
                        printf("1-Try Again\n2-Exit\n");
                        scanf("%d", &selection);
                        getchar();
                        if (selection != 1 && selection != 2)
                            printf("Invalid Selection.\n");
                        else if (selection == 2)
                            return;
                    } while (selection != 1 && selection != 2);
                }
            } while (Validate_Mail(newEmail) == 0 && selection == 1);
            flag2 = 1;
        }
        do
        {
            printf("DO YOU WANT TO MODIFY PHONE NUMBER ?\n1-YES\n2-NO\n");
            scanf("%d", &selection);
            if (selection != 1 && selection != 2)
            {
                printf("Invalid selection .\n");
                printf("---------------------------------\n");
            }
            getchar();
        } while (selection != 1 && selection != 2);
        if (selection == 1)
        {
            do
            {
                printf("Enter New Phone Number: ");
                gets(newMobile);
                if (Validate_Phone(newMobile) == 0)
                {
                    do
                    {
                        printf("1-Try Again\n2-Exit\n");
                        scanf("%d", &selection);
                        getchar();
                        if (selection != 1 && selection != 2)
                            printf("Invalid Selection.\n");
                        else if (selection == 2)
                            return;
                    } while (selection != 1 && selection != 2);
                }
            } while (Validate_Phone(newMobile) == 0 && selection == 1);
            flag3 = 1;
        }
        do
        {
            printf("Modified Successfully .\n");
            printf("SAVE OR DISCARD ?\n1-SAVE\n2-DISCARD\n");
            scanf("%d", &selection);
            if (selection != 1 && selection != 2)
            {
                printf("Invalid selection .\n");
                printf("---------------------------------\n");
            }
            getchar();
        } while (selection != 1 && selection != 2);
        if (selection == 1)
        {
            if (flag1)
                strcpy(accounts[i].name, newName);
            if (flag2)
                strcpy(accounts[i].email, newEmail);
            if (flag3)
                strcpy(accounts[i].mobile, newMobile);
            SAVE(accounts);
            return;
        }
        else
            return;
    }
}

void SEARCH(account accounts[])
{
    int i, flag = 0;
    char accnum[20];
    int selection;
    do
    {
        printf("Enter Account Number: ");
        gets(accnum);
        if (Validate_AccNum(accnum) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_AccNum(accnum) == 0 && selection == 1);
    for (i = 0; i < (actual_accounts); i++)
    {
        if (strcmp(accnum, accounts[i].account_number) == 0)
        {
            flag = 1;
            Print_Accounts(accounts, i);
            break;
        }
    }
    if (!flag)
    {
        printf("Specified Account Not Found .\n");
        printf("---------------------------------\n");
    }
}

void ADVANCED_SEARCH(account accounts[])
{
    int i, j, k, flag, flag2 = 0;
    char Keyword[50];
    printf("---------------------------------\n");
    printf("Enter Keyword :");
    gets(Keyword);
    int size = strlen(Keyword);
    for (i = 0; i < size; i++)
        Keyword[i] = toupper(Keyword[i]);
    printf("Search Results :\n");
    for (j = 0; j < (actual_accounts); j++)
    {
        i = 0;
        k = 0;
        while (Keyword[i] != '\0')
        {
            if (Keyword[i] == toupper(accounts[j].name[k]))
            {
                flag = 1;
                i++;
                k++;
            }
            else if (accounts[j].name[k] == '\0')
            {
                flag = 0;
                break;
            }
            else
            {
                flag = 0;
                i = 0;
                k++;
            }
        }
        if (flag)
        {
            flag2 = 1;
            Print_Accounts(accounts, j);
        }
    }
    if (flag2 == 0)
    {
        printf("No Matches Found .\n");
        printf("---------------------------------\n");
    }
}

void WITHDRAW(account accounts[])
{
    int i;
    int flag = 0;
    char accnum[20];
    int selection;
    do
    {
        printf("Enter Account Number: ");
        gets(accnum);
        if (Validate_AccNum(accnum) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_AccNum(accnum) == 0 && selection == 1);
    for (i = 0; i < actual_accounts; i++)
    {
        if (strcmp(accnum, accounts[i].account_number) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("Error, Cannot Find Entered Account Number .\n");
    else
    {
        char Amount[100];
        double withAmount;
        do
        {
            printf("Enter Amount to be withdrawn: ");
            gets(Amount);
            withAmount = Validate_Amount(Amount);
            if (withAmount == -1.0)
            {
                do
                {
                    printf("Invalid Amount.\n1-Try Again\n2-Exit\n");
                    scanf("%d", &selection);
                    getchar();
                    if (selection != 1 && selection != 2)
                        printf("Invalid Selection.\n");
                    else if (selection == 2)
                        return;
                } while (selection != 1 && selection != 2);
            }
        } while (withAmount == -1.0 && selection == 1);
        if (withAmount <= 0 || withAmount > 10000 || withAmount > accounts[i].balance)
        {
            printf("Entered Amount Cannot Be Withdrawn .\n");
        }
        else
        {
            accounts[i].balance = accounts[i].balance - withAmount;
            printf("SUCCESSFUL TRANSACTION .\n");
            int selection;
            do
            {
                printf("SAVE OR DISCARD ?\n1-SAVE\n2-DISCARD\n");
                scanf("%d", &selection);
                if (selection != 1 && selection != 2)
                {
                    printf("Invalid selection .\n");
                    printf("---------------------------------\n");
                }
                getchar();
            } while (selection != 1 && selection != 2);
            if (selection == 1)
            {
                SAVE(accounts);
                char filename[20];
                strcpy(filename, accounts[i].account_number);
                strcat(filename, ".txt");
                FILE *f = fopen(filename, "a");
                fprintf(f, "Withdrawed %.3lf.\n", withAmount);
                fclose(f);
                return;
            }
            else
            {
                accounts[i].balance = accounts[i].balance + withAmount;
                return;
            }
        }
    }
}

void DEPOSIT(account accounts[])
{
    int i;
    int flag = 0;
    char accnum[20];
    int selection;
    do
    {
        printf("Enter Account Number: ");
        gets(accnum);
        if (Validate_AccNum(accnum) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_AccNum(accnum) == 0 && selection == 1);
    for (i = 0; i < actual_accounts; i++)
    {
        if (strcmp(accnum, accounts[i].account_number) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("Error, Cannot Find Entered Account Number .\n");
    else
    {
        char Amount[100];
        double depositAmm;
        do
        {
            printf("Enter Amount to be withdrawn: ");
            gets(Amount);
            depositAmm = Validate_Amount(Amount);
            if (depositAmm == -1.0)
            {
                do
                {
                    printf("Invalid Amount.\n1-Try Again\n2-Exit\n");
                    scanf("%d", &selection);
                    getchar();
                    if (selection != 1 && selection != 2)
                        printf("Invalid Selection.\n");
                    else if (selection == 2)
                        return;
                } while (selection != 1 && selection != 2);
            }
        } while (depositAmm == -1.0 && selection == 1);
        if (depositAmm <= 0 || depositAmm > 10000)
            printf("Entered Amount Cannot be Deposited .\n");
        else
        {
            accounts[i].balance = accounts[i].balance + depositAmm;
            printf("SUCCESSFUL TRANSACTION .\n");
            int selection;
            do
            {
                printf("SAVE OR DISCARD ?\n1-SAVE\n2-DISCARD\n");
                scanf("%d", &selection);
                if (selection != 1 && selection != 2)
                {
                    printf("Invalid selection .\n");
                    printf("---------------------------------\n");
                }
                getchar();
            } while (selection != 1 && selection != 2);
            if (selection == 1)
            {
                SAVE(accounts);
                char filename[20];
                strcpy(filename, accounts[i].account_number);
                strcat(filename, ".txt");
                FILE *f = fopen(filename, "a");
                fprintf(f, "Deposited %.3lf.\n", depositAmm);
                fclose(f);
                return;
            }
            else
            {
                accounts[i].balance = accounts[i].balance - depositAmm;
                return;
            }
        }
    }
}

void TRANSFER(account accounts[])
{
    int i;
    int flag = 0;
    char accnum1[20];
    int selection;
    do
    {
        printf("Enter Sender's Account Number: ");
        gets(accnum1);
        if (Validate_AccNum(accnum1) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_AccNum(accnum1) == 0 && selection == 1);
    for (i = 0; i < actual_accounts; i++)
    {
        if (strcmp(accnum1, accounts[i].account_number) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("Error, Cannot Find Entered Account Number .\n");
    else
    {
        int j;
        flag = 0;
        char accnum2[20];
        do
        {
            printf("Enter Reciever's Account Number: ");
            gets(accnum2);
            if (Validate_AccNum(accnum2) == 0)
            {
                do
                {
                    printf("1-Try Again\n2-Exit\n");
                    scanf("%d", &selection);
                    getchar();
                    if (selection != 1 && selection != 2)
                        printf("Invalid Selection.\n");
                    else if (selection == 2)
                        return;
                } while (selection != 1 && selection != 2);
            }
        } while (Validate_AccNum(accnum2) == 0 && selection == 1);
        for (j = 0; j < actual_accounts; j++)
        {
            if (strcmp(accnum2, accounts[j].account_number) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
            printf("Error, Cannot Find Entered Account Number .\n");
        else
        {
            char Amount[100];
            double transAmount;
            do
            {
                printf("Enter Amount to be withdrawn: ");
                gets(Amount);
                transAmount = Validate_Amount(Amount);
                if (transAmount == -1.0)
                {
                    do
                    {
                        printf("Invalid Amount.\n1-Try Again\n2-Exit\n");
                        scanf("%d", &selection);
                        getchar();
                        if (selection != 1 && selection != 2)
                            printf("Invalid Selection.\n");
                        else if (selection == 2)
                            return;
                    } while (selection != 1 && selection != 2);
                }
            } while (transAmount == -1.0 && selection == 1);
            if (transAmount <= 0 || transAmount > 10000 || transAmount > accounts[i].balance || strcmp(accnum1, accnum2) == 0)
                printf("Invalid Transfer Process.\n");
            else
            {
                accounts[i].balance = accounts[i].balance - transAmount;
                accounts[j].balance = accounts[j].balance + transAmount;
                printf("SUCCESSFUL TRANSACTION .\n");
                int selection;
                do
                {
                    printf("SAVE OR DISCARD ?\n1-SAVE\n2-DISCARD\n");
                    scanf("%d", &selection);
                    if (selection != 1 && selection != 2)
                    {
                        printf("Invalid selection .\n");
                        printf("---------------------------------\n");
                    }
                    getchar();
                } while (selection != 1 && selection != 2);
                if (selection == 1)
                {
                    SAVE(accounts);
                    char filename[20];
                    strcpy(filename, accounts[i].account_number);
                    strcat(filename, ".txt");
                    FILE *f = fopen(filename, "a");
                    fprintf(f, "Transferred %.3lf.\n", transAmount);
                    fclose(f);
                    strcpy(filename, accounts[j].account_number);
                    strcat(filename, ".txt");
                    f = fopen(filename, "a");
                    fprintf(f, "Received %.3lf.\n", transAmount);
                    fclose(f);
                    return;
                }
                else
                {
                    accounts[i].balance = accounts[i].balance + transAmount;
                    accounts[j].balance = accounts[j].balance - transAmount;
                    return;
                }
            }
        }
    }
}

void REPORT(account accounts[])
{
    int i;
    int flag = 0;
    int selection;
    char accnum[20];
    do
    {
        printf("Enter Account Number: ");
        gets(accnum);
        if (Validate_AccNum(accnum) == 0)
        {
            do
            {
                printf("1-Try Again\n2-Exit\n");
                scanf("%d", &selection);
                getchar();
                if (selection != 1 && selection != 2)
                    printf("Invalid Selection.\n");
                else if (selection == 2)
                    return;
            } while (selection != 1 && selection != 2);
        }
    } while (Validate_AccNum(accnum) == 0 && selection == 1);
    for (i = 0; i < actual_accounts; i++)
    {
        if (strcmp(accnum, accounts[i].account_number) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        printf("Account number entered not found.\n");
        return;
    }
    else
    {
        char filename[20];
        strcpy(filename, accounts[i].account_number);
        strcat(filename, ".txt");
        FILE *f = fopen(filename, "r");
        int lines = 0;
        char c;
        while (f != NULL && (c = fgetc(f)) != EOF)
        {
            if (c == '\n')
                lines++;
        }
        fseek(f, 0, SEEK_SET);
        while (f != NULL && (c = fgetc(f)) != EOF && lines > 5)
        {
            if (c == '\n')
                lines--;
        }
        printf("Account's Last five transactions:\n");
        printf("%c", c);
        while ((c = fgetc(f)) != EOF && lines > 0)
        {
            if (c == '\n')
            {
                lines--;
                printf("\n");
            }
            else
            {
                printf("%c", c);
            }
        }
        printf("\n");
    }
}

void SortByName(account accounts[]) // Sorting accounts Alphabetecally
{
    int i = 0;
    int j;
    int swapped;
    do
    {
        swapped = 0;
        for (j = 0; j < (actual_accounts - 1 - i); j++)
        {
            if (strcmp(accounts[j].name, accounts[j + 1].name) > 0)
            {
                account temp;
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
                swapped = 1;
            }
        }
        i++;
    } while (swapped);
}

void SortByBalance(account accounts[]) // Sorted Descendingly as default
{
    int i = 0;
    int swapped;
    int j;
    do
    {
        swapped = 0;
        for (j = 0; j < (actual_accounts - 1); j++)
        {
            if (accounts[j].balance < accounts[j + 1].balance)
            {
                swapped = 1;
                account temp;
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
        i++;
    } while (swapped);
}

void SortByDate(account accounts[]) // Latest first by default
{
    int i = 0;
    int swapped;
    int j;
    do
    {
        swapped = 0;
        for (j = 0; j < (actual_accounts - 1 - i); j++)
        {
            if (accounts[j].date_opened.year < accounts[j + 1].date_opened.year)
            {
                swapped = 1;
                account temp;
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
            else if (accounts[j].date_opened.year == accounts[j + 1].date_opened.year)
            {
                if (accounts[j].date_opened.month < accounts[j + 1].date_opened.month)
                {
                    swapped = 1;
                    account temp;
                    temp = accounts[j];
                    accounts[j] = accounts[j + 1];
                    accounts[j + 1] = temp;
                }
            }
        }
        i++;
    } while (swapped);
}

void PRINT(account accounts[])
{
    int selection;
    do
    {
        printf("Pick(1:2:3)\n1-Sort By Name\n2-Sort By Date\n3-Sort By Balance\n");
        scanf("%d", &selection);
        getchar();
    } while (selection != 1 && selection != 2 && selection != 3);
    if (selection == 1)
    {
        SortByName(accounts);
        for (int i = 0; i < actual_accounts; i++)
        {
            Print_Accounts(accounts, i);
        }
    }
    else if (selection == 2)
    {
        SortByDate(accounts);
        do
        {
            printf("Pick(1:2)\n1-Latest First\n2-Oldest First\n");
            scanf("%d", &selection);
            getchar();
        } while (selection != 1 && selection != 2);
        if (selection == 1)
            for (int i = 0; i < actual_accounts; i++)
            {
                Print_Accounts(accounts, i);
            }
        else
            for (int i = (actual_accounts - 1); i >= 0; i--)
            {
                Print_Accounts(accounts, i);
            }
    }
    else if (selection == 3)
    {
        SortByBalance(accounts);
        do
        {
            printf("Pick(1:2)\n1-Greatest To Least\n2-Least To Greatest\n");
            scanf("%d", &selection);
            getchar();
        } while (selection != 1 && selection != 2);
        if (selection == 1)
            for (int i = 0; i < actual_accounts; i++)
            {
                Print_Accounts(accounts, i);
            }
        else
            for (int i = (actual_accounts - 1); i >= 0; i--)
            {
                Print_Accounts(accounts, i);
            }
    }
}

int main(void)
{
    actual_accounts = 0;
    int flag = 0;
    account accounts[MAX_ACCOUNTS];
    int selection;
    do
    {
        printf("Choose an option:\n1-LOGIN\n2-QUIT\n");
        printf("=================================\n");
        scanf("%d", &selection);
        getchar();
        if (selection != 1 && selection != 2)
        {
            printf("Invalid selection .\n");
            printf("---------------------------------\n");
        }
    } while (selection != 1 && selection != 2);
    if (selection == 1)
    {
        if (Login())
        {
            load_accounts(accounts);
            do
            {
                printf("Choose an option:\n");
                printf("=================================\n");
                printf("1-ADD\t\t\t2-DELETE\n3-MODIFY\t\t4-SEARCH\n5-ADVANCED SEARCH\t6-WITHDRAW\n7-DEPOSIT\t\t8-TRANSFER\n9-REPORT\t\t10-PRINT\n11-QUIT\n");
                scanf("%d", &selection);
                getchar();
                printf("=================================\n");
                switch (selection)
                {
                case 1:
                    flag = 1;
                    ADD(accounts);
                    break;
                case 2:
                    flag = 1;
                    Delete(accounts);
                    break;
                case 3:
                    flag = 1;
                    MODIFY(accounts);
                    break;
                case 4:
                    flag = 1;
                    SEARCH(accounts);
                    break;
                case 5:
                    flag = 1;
                    ADVANCED_SEARCH(accounts);
                    break;
                case 6:
                    flag = 1;
                    WITHDRAW(accounts);
                    break;
                case 7:
                    flag = 1;
                    DEPOSIT(accounts);
                    break;
                case 8:
                    flag = 1;
                    TRANSFER(accounts);
                    break;
                case 9:
                    flag = 1;
                    REPORT(accounts);
                    break;
                case 10:
                    flag = 1;
                    PRINT(accounts);
                    break;
                case 11:
                    return 0;
                }
                if (!flag)
                {
                    printf("=================================\n");
                    printf("INVALID SELECTION.\n");
                    printf("=================================\n");
                }
            } while (1);
        }
        else
            return 0;
    }
    return 0;
}