#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    char str[15];
    struct node *next;
    struct node *prev;
};
struct node *STARTnode;
struct node *t;

char dictionary[58110][20];

struct BST
{
    int top;
    struct node *ptr[15];
    struct BST *lchild;
    struct BST *rchild;
};
struct BST *HEAD;

struct node *UNDO[10000];
int TOP = -1;

//GENERAL FUNCTIONS
void INSERTIinDLL(char str[]);
void PRINTdll();
void onlyWORD(char str1[], int size, char store[]);
void PRINTinFILE();
void APPENDfile();
void APPENDdll(char str[]);

//UNDO
void INSERTundo();
void PRINTundo();
void performUNDO();

//SPELL-CHECKER
void INSERT_dict();
int check_spelling(char word[]);
void file_traveresal();

//FINDandREPLACE
void CONSTRUCTbst();
void FINDandREPLACE(char toFind[], char toReplace[]);
void PRINTbst(struct BST *temp);

//main FUNCTION
int main()
{
    INSERT_dict();

    printf("\t\tTEXT-EDITOR\n\n");

    printf("Enter text and enter ` to terminate:\n");

    char para[10000];
    scanf("%[^`]", para);
    INSERTIinDLL(para);
    INSERTundo();
    PRINTinFILE();

    scanf(" %c");
    while (1)
    {
        printf("\nSelect operation you wish to perform\n");
        printf("1) UNDO\n2) Find and Replace\n3) Check Spelling error\n4) Add more to file\n5) Show the file content\n6) Exit\n");
        int n;
        scanf("%d", &n);
        if (n == 1)
        {
            performUNDO();
            PRINTinFILE();
            PRINTdll();
        }
        else if (n == 2)
        {
            CONSTRUCTbst();
            // PRINTbst(HEAD);
            char toFIND[15], toREPLACE[15];
            printf("Enter the word to replace: ");
            scanf("%s", toFIND);
            printf("Enter the word to replace with: ");
            scanf("%s", toREPLACE);
            FINDandREPLACE(toFIND, toREPLACE);
            PRINTinFILE();
        }
        else if (n == 3)
        {
            printf("Checking for incorrect word\n");
            file_traveresal();
        }
        else if (n == 4)
        {
            PRINTdll();
            printf("\n");
            APPENDfile();
            printf("\n");
            scanf(" %c");
        }
        else if (n == 5)
        {
            PRINTdll();
            printf("\n\n");
        }
        else if (n == 6)
        {
            break;
        }
        else
        {
            printf("Please enter correct choice!\n");
        }
    }
}

void INSERTIinDLL(char str[])
{
    int j = 0;
    char str1[15];
    for (int i = 0;; i++)
    {
        if (str[i] == ' ' || str[i] == '\n')
        {
            str1[j] = str[i];
            j++;
            str1[j] = '\0';
            j = 0;
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            strcpy(temp->str, str1);
            temp->next = NULL;
            temp->prev = NULL;
            if (STARTnode == NULL)
            {
                t = temp;
                t->next = NULL;
                t->prev = NULL;
                STARTnode = t;
            }
            else
            {
                t->next = temp;
                temp->prev = t;
                t = temp;
            }
        }
        else if (str[i] == '\0')
        {
            str1[j] = str[i];
            j++;
            str1[j] = '\0';
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            strcpy(temp->str, str1);
            temp->next = NULL;
            temp->prev = NULL;
            if (STARTnode == NULL)
            {
                t = temp;
                STARTnode = t;
            }
            else
            {
                t->next = temp;
                temp->prev = t;

                t = temp;
                t->next = NULL;
            }
            break;
        }
        else
        {
            str1[j] = str[i];
            j++;
        }
    }
}

void APPENDdll(char str[])
{
    int j = 0;
    char str1[15];
    for (int i = 0;; i++)
    {
        if (str[i] == ' ' || str[i] == '\n')
        {
            str1[j] = str[i];
            j++;
            str1[j] = '\0';
            j = 0;
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            strcpy(temp->str, str1);
            temp->next = NULL;
            temp->prev = NULL;

            t->next = temp;
            temp->prev = t;
            t = temp;
        }
        else if (str[i] == '\0')
        {
            str1[j] = str[i];
            j++;
            str1[j] = '\0';
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            strcpy(temp->str, str1);
            temp->next = NULL;
            temp->prev = NULL;

            t->next = temp;
            temp->prev = t;

            t = temp;
            t->next = NULL;
            break;
        }
        else
        {
            str1[j] = str[i];
            j++;
        }
    }
}

void PRINTdll()
{
    struct node *temp = STARTnode;
    while (temp != NULL)
    {
        /*
        char store[15];
        onlyWORD(temp->str, strlen(temp->str), store);
        printf("%s", store);*/
        printf("%s", temp->str);
        temp = temp->next;
    }
}

void onlyWORD(char str1[], int size, char store[])
{
    char str[15];
    strcpy(str, str1);
    while (size)
    {
        char temp = tolower(str[size - 1]);
        if (temp < 96 || temp > 123)
        {
            size--;
            str[size] = '\0';
        }
        else
        {
            str[size] = '\0';
            strcpy(store, str);
            return;
        }
    }
}

void PRINTinFILE()
{
    FILE *fp = fopen("try.txt", "w");
    struct node *current = STARTnode;

    while (current != NULL)
    {
        fprintf(fp, "%s", current->str);
        current = current->next;
    }
    fclose(fp);
}

void APPENDfile()
{
    char str[1000];
    scanf("%[^`]", str);
    // printf("This is file:\n\n%s", str);
    INSERTIinDLL(str);
    PRINTinFILE();
    INSERTundo();
    PRINTdll();
}

void INSERTundo()
{
    struct node *t1 = STARTnode;
    while (t1 != NULL)
    {
        TOP++;
        UNDO[TOP] = t1;
        t1 = t1->next;
    }
}

void PRINTundo()
{
    for (int i = 0; i <= TOP; i++)
    {
        printf("%s", UNDO[i]->str);
    }
}

void performUNDO()
{
    if (TOP == -1)
    {
        printf("No last action to undo\n");
        return;
    }
    if (UNDO[TOP]->prev != NULL)
    {
        struct node *temp1 = UNDO[TOP]->prev;
        temp1->next = NULL;
        TOP--;
    }
    else
    {
        UNDO[TOP] = NULL;
        STARTnode = NULL;
        TOP--;
    }
    if (t->prev != NULL)
    {
        t = t->prev;
    }
}

void INSERT_dict()
{
    FILE *f_dict = fopen("corncob_lowercase.txt", "r");
    if (f_dict != NULL)
    {
        int i = 0;
        while (!feof(f_dict))
        {
            fscanf(f_dict, "%s", dictionary[i]);
            i++;
        }
    }
}

int check_spelling(char word[])
{
    int tail = 0, head = 58110;
    int mid = (head + tail) / 2;
    while (tail < head)
    {
        int temp_mid = mid;
        // printf("This is tail: %s, %d, this is tail: %s, %d, this is mid: %d\n", dictionary[tail], tail, dictionary[head], head, mid);
        if (strcmpi(word, dictionary[mid]) == 0)
        {
            return 1;
        }
        else if (strcmpi(word, dictionary[mid]) > 0)
        {
            tail = mid;
            mid = (tail + head) / 2;
        }
        else
        {
            head = mid;
            mid = (tail + head) / 2;
        }
        if (mid == temp_mid)
        {
            return 0;
        }
    }
    if (tail == head && strcmpi(word, dictionary[mid]) == 0)
    {
        return 1;
    }
    else
        return 0;
}

void file_traveresal()
{
    struct node *temp1 = STARTnode;
    while (temp1 != NULL)
    {
        char str_temp[15];
        onlyWORD(temp1->str, strlen(temp1->str), str_temp);
        // printf("%s", str_temp);
        int x = check_spelling(str_temp);
        if (x == 0)
        {
            printf("%s is incorrect word.\n", str_temp);
        }
        temp1 = temp1->next;
    }
}

void CONSTRUCTbst()
{
    // printf("This time: \n");
    struct node *current = STARTnode;
    while (current != NULL)
    {
        // printf("Working on: %s\n", current->str);
        struct BST *temp = (struct BST *)malloc(sizeof(struct BST));
        temp->ptr[0] = current;
        temp->top = 0;
        temp->lchild = NULL;
        temp->rchild = NULL;

        if (HEAD == NULL)
        {
            HEAD = temp;
            current = STARTnode->next;
        }
        else
        {
            struct BST *curr = HEAD;
            while (1)
            {
                char str1[15];
                onlyWORD(curr->ptr[0]->str, strlen(curr->ptr[0]->str), str1);
                char str2[15];
                onlyWORD(current->str, strlen(current->str), str2);

                if (strcmpi(str2, str1) < 0)
                {
                    if (curr->lchild == NULL)
                    {
                        curr->lchild = temp;
                        current = current->next;
                        break;
                    }
                    else
                    {
                        curr = curr->lchild;
                    }
                }

                else if (strcmpi(str2, str1) > 0)
                {
                    if (curr->rchild == NULL)
                    {
                        curr->rchild = temp;
                        current = current->next;
                        break;
                    }
                    else
                    {
                        curr = curr->rchild;
                    }
                }

                else
                {
                    // printf("Entered, top: %d\n", curr->top);

                    curr->ptr[++curr->top] = current;
                    current = current->next;
                    break;
                }
            }
        }
    }
}

void FINDandREPLACE(char toFind[], char toReplace[])
{
    struct BST *curr = HEAD;
    while (1)
    {
        char str1[15];
        onlyWORD(curr->ptr[0]->str, strlen(curr->ptr[0]->str), str1);
        // printf("Currently working on: %s\n", str1);
        if (strcmpi(str1, toFind) > 0)
        {
            if (curr->lchild == NULL)
            {
                printf("Word not found!\n");
                return;
            }
            curr = curr->lchild;
        }
        else if (strcmpi(str1, toFind) < 0)
        {
            if (curr->rchild == NULL)
            {
                printf("Word not found!\n");
                return;
            }
            curr = curr->rchild;
        }
        else
        {
            for (int x = 0; x <= curr->top; x++)
            {
                // printf("This is %d \n", x);
                int i;
                char temp1[15];
                for (i = 0; i < strlen(toReplace); i++)
                {
                    temp1[i] = toReplace[i];
                }
                for (int j = 0; j < strlen(curr->ptr[x]->str); j++)
                {
                    char a = tolower(curr->ptr[x]->str[j]);
                    if (a < 97 || a > 122)
                    {
                        temp1[i] = a;
                        i++;
                    }
                }
                temp1[i] = '\0';
                strcpy(curr->ptr[x]->str, temp1);
                if (x == curr->top)
                    return;
            }
        }
    }
    printf("\nReplaced\n");
    PRINTdll();
}

void PRINTbst(struct BST *temp)
{
    if (temp == NULL)
    {
        return;
    }
    else
    {
        PRINTbst(temp->lchild);
        printf("%s-%d", temp->ptr[0]->str, temp->top);
        PRINTbst(temp->rchild);
    }
}
