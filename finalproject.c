/*
Members of the group:

1. Vansh Agrawal 2021A7PS2998H
2. Aryan Saluja 2021A7PS2947H
3. Ninad Agrawal 2021A7PS2948H
4. Abhishek Joshi 2021A7PS2727H
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char tree[129];
char prefixtext[100];
int h;
int atoms, atleft;
void treetoprefix(int i) /** converting the binary parse tree to prefix form*/
{
    static prei = 0; /**for every element in the tree starting from the toop node which branches into the first level,whenever the value in the node is not null print the particular value of then go to the correspnding //left branch i.e. 2*i and then the right branch i.e. 2*i+1 */
    if (tree[i] != NULL)
    {
        printf("%c", tree[i]);
        prefixtext[prei++] = tree[i]; /** made a new array containing the elements of the prefix expression using the array of the tree*/
        treetoprefix(2 * i);          /// go to the left branch
        treetoprefix((2 * i) + 1);    /// go to the right branch
    }
}
void treetoinfix(int i)
{
    if (tree[i] != NULL) /// statements to follow to inorder taversal in a v=binary parse tree
    {
        treetoinfix(2 * i);       /// first go to the left branch
        printf("%c", tree[i]);    /// print the value of the respective node
        treetoinfix((2 * i) + 1); /// then go to the right branch
    }
}
int height(int i)
{
    int h;
    if (tree[i] != NULL) /// statements to compute height of the tree
    {
        int h1 = height(2 * i) + 1;     /// height of the longest left branch including the top node hence the " +1 "
        int h2 = height(2 * i + 1) + 1; /// height of the longest right including the top node
        h = h1 > h2 ? h1 : h2;          /**compare the two computed heights and return the longest possible length of the path that is the height of the parse tree*/
    }
    else
    {
        return 1;
    }
    return h; /// return the value of the height
}

void treeprinter() /// to print the binary parse tree
{
    int y = 1;
    for (int x = 0; x <= h - 1; x++) /// loop to traverse the whole tree
    {
        int tempy = y;
        for (int z = pow(2, h - x); z > 0; z--)
        {
            printf(" ");
        }
        for (int z = 0; z < pow(2, x); z++) /// no of possible nodes from the xth row
        {
            if ((tree[y] >= 65 && tree[y] <= 90) || (tree[y] >= 97 && tree[y] <= 122) || tree[y] == '~' || tree[y] == '+' || tree[y] == '^' ||
                tree[y] == '>')
            {
                printf("\b");
                printf("%c", tree[y]); /// make alphabets and operators a node , if they exist
            }
            else
            {
                printf("\b");
                printf(".");
            }
            for (int e = pow(2, h - x + 1); e > 0; e--) /// no of nodes in the xth row of a tree of height h
            {
                printf(" ");
            }
            y = y + 1;
        }
        printf("\n");
        if (x < h - 1)
        {
            for (int y = pow(2, h - x - 1) + pow(2, h - x - 2); y > 0; y--) /**this loops prints out all the "DOTS" as in the possible spaces wherein the parse tree could traverse while the upper loop inputs all the corresponding values*/
            {
                printf(" ");
            }
            for (int z = 0; z < pow(2, x); z++)
            {
                printf("\b/");
                for (int y = pow(2, h - x - 1); y > 0; y--)
                {
                    printf(" ");
                }
                printf("\b\\");
                for (int y = pow(2, h - x) + pow(2, h - x - 1); y > 0; y--)
                {
                    printf(" ");
                }
            }
        }
        else
        {
            printf("\n");
        }
        printf("\n");
    }
}

void prefixtotree(char *a)
{
    memset(tree, 0, 129); /// fill 129 characters of tree array with the value 0.

    int l = strlen(prefixtext);
    int workid = 1; /// at the 0th index , the value stored is NULL
    atoms = 0;

    for (int i = 0; i < l; i++)
    {
        if ((a[i] >= 65 && a[i] <= 90) || (a[i] >= 97 && a[i] <= 122)) /// if any of the elemtns is an alphabet
        {
            atoms++;             /// no of atoms is incremented
            tree[workid] = a[i]; /// start filling the array tree in order of the traversal from the 1st index being the first node and so on..
            if (workid % 2 == 0)
            {
                workid = workid + 1; /// go to the next node on the same level
            }
            else
            {
                while (tree[workid / 2] && tree[workid + 1] == NULL && workid / 2 != (workid + 1) / 2) /// move to the upper branch and move onto the branch on the right of the upper level
                {                                                                                      /// when the branches on the left and the right are NULL under the current node
                    workid = workid / 2;
                }
                workid = workid + 1; /// move on the right node on the same level
            }
        }
        else if (a[i] == '~') /// in the case of a negation
        {

            tree[workid] = a[i];     /// update the tree array
            workid = workid * 2 + 1; /// move onto the right branch and ensure the correct order of traversal
        }
        else
        {
            tree[workid] = a[i];
            if (tree[2 * workid] == NULL) /// if the node in the lower left branch in NULL
            {
                workid = workid * 2; /// move onto the lower left branch or the left child of the node
            }
            else
            {
                workid = workid * 2 + 1; /// else move onto the lower right branch or the right child of the node
            }
        }
    }
}
void infixtotree(char *a) /// convert infix to parse tree
{
    atoms = 0;
    int l = strlen(a);
    int workid = 1;
    for (int i = 0; i <= l; i++)
    {
        if (a[i] == '(') /// if you see a '('
        {
            workid = workid * 2; /// move to the next level down from the current node
        }
        else if (a[i] == ')') /// if you see ')'
        {
            workid = workid / 2; /// move to the level up from the current node
        }
        else if ((a[i] >= 65 && a[i] <= 90) || (a[i] >= 97 && a[i] <= 122)) /// if there is any alphabet
        {
            atoms++;             /// no of atoms is incremented
            tree[workid] = a[i]; /// update the array of tree elements
            workid = workid / 2; /// move to the level up from the current node
        }
        else if (a[i] == '~') /// in the case of a negation
        {
            workid = workid / 2;     /// move to the level up from the current node
            tree[workid] = a[i];     /// update the tree array
            workid = workid * 2 + 1; /// move to the right branch
        }
        else
        {
            tree[workid] = a[i];     /// update the tree array
            workid = workid * 2 + 1; /// move to the right branch
        }
    }
}
void printTruthhead(int i) /// to print the truth table headers using the traversal along the parse tree
{

    if ((tree[i] >= 65 && tree[i] <= 90) || (tree[i] >= 97 && tree[i] <= 122)) /**to print the indivisual propositions in the truth table*/
    {
        printf("\t");
        printf("%c", tree[i]);
    }
    else if (tree[i] == '+' || tree[i] == '^' || tree[i] == '>' || tree[i] == '~') /**if an operator exists in tnext index then move on to the next level down in the parse tree*/
    {
        if (tree[i] != '~')
        {
            printTruthhead(i * 2); /// move on the next level down left branch
            printf("\t\t\b\b");
        }
        printTruthhead(i * 2 + 1); /// move onto the right branch under the current node
        printf("\t\t\b\b");
        treetoinfix(i);
    }
    else
    {
        printf("\t");
    }
}

int printTruthline(int i, int ln) /// to print the consecutive truth table lines and logic values
{

    if ((tree[i] >= 65 && tree[i] <= 90) || (tree[i] >= 97 && tree[i] <= 122))
    {

        if (((ln - 1) / ((int)(pow(2, atoms) / pow(2, atleft--))) % 2 + 1) == 1) /// ln = line number
        {
            printf("T\t\t");
            return 1;
        }
        else
        {
            printf("F\t\t");
            return 0;
        }
        // printf("\t");
    }
    else if (tree[i] == '+' || tree[i] == '^' || tree[i] == '>' || tree[i] == '~')
    {
        // printf("\t");
        int l = printTruthline(i * 2, ln);     /// expression on the left
        int r = printTruthline(i * 2 + 1, ln); /// expression on the right
        if (tree[i] == '^')                    /// if the operator is AND
        {
            if (l && r) /// both should be true
            {
                printf("T");
                printf("\t\t");
                return 1;
            }
            else
            {
                printf("F");
                printf("\t\t");
                return 0;
            }
        }
        else if (tree[i] == '+') /// if the operator is OR
        {
            if (l || r) /// either of them should be true
            {
                printf("T\t");
                printf("\t");
                return 1;
            }
            else
            {
                printf("F\t");
                printf("\t");
                return 0;
            }
        }
        else if (tree[i] == '~') /// if the operator is negation
        {
            if (r)
            {
                printf("F\t");
                printf("\t");
                return 0;
            }
            else
            {
                printf("T\t");
                printf("\t");
                return 1;
            }
        }
        else if (tree[i] == '>') /// if the operator is implication
        {
            if (!l || r)
            {
                printf("T\t");
                printf("\t");
                return 1;
            }
            else
            {
                printf("F\t");
                printf("\t");
                return 0;
            }
        }
    }
    else
    {
        // printf("\b");
        printf(" ");
    }
}
void truthtable()
{
    printf("atoms: %d\n", atoms);
    printTruthhead(1);
    for (int i = 1; i <= pow(2, atoms); i++)
    {
        printf("\n");
        printf("%d\t\b", i);
        atleft = atoms;
        printTruthline(1, i);
    }
}

char tval[100];
void gettruthval() /// to get truth values from user
{
    static int atfound = 0;
    printf("\ndont add spaces or commas for eg. for a,b,c, enter TFT ,etc.\nEnter value for "); /// giving instruction
    for (int i = 1; i < 129; i++)
    {
        if ((tree[i] >= 65 && tree[i] <= 90) || (tree[i] >= 97 && tree[i] <= 122))
        {
            printf("%c,", tree[i]); /// printing order for input
        }
    }
    tval[atfound] = getchar();
    while (tval[atfound] != '\n')
    {
        tval[++atfound] = getchar(); /// getting input
    }
}
int truthval(int i) /// to use the value gained gettruthval fuction to generate truth value for expression
{

    // char tval[atoms];
    static int atfound = 0;
    if ((tree[i] >= 65 && tree[i] <= 90) || (tree[i] >= 97 && tree[i] <= 122)) /// mostly same fuctionality as truthline function but using inputed values
    {
        if (tval[atfound] == 'F')
        {
            printf("F\t\t");

            atfound++;
            return 0;
        }
        else if ((tval[atfound] == 'T'))
        {
            printf("T\t\t");

            atfound++;
            return 1;
        }
    }
    else if (tree[i] == '+' || tree[i] == '^' || tree[i] == '>' || tree[i] == '~')
    {
        // printf("\t");
        int l = truthval(i * 2);
        int r = truthval(i * 2 + 1);
        if (tree[i] == '^')
        {
            if (l && r)
            {
                printf("T");
                printf("\t\t");
                return 1;
            }
            else
            {
                printf("F");
                printf("\t\t");
                return 0;
            }
        }
        else if (tree[i] == '+')
        {
            if (l || r)
            {
                printf("T\t");
                printf("\t");
                return 1;
            }
            else
            {
                printf("F\t");
                printf("\t");
                return 0;
            }
        }
        else if (tree[i] == '~')
        {
            if (r)
            {
                printf("F\t");
                printf("\t");
                return 0;
            }
            else
            {
                printf("T\t");
                printf("\t");
                return 1;
            }
        }
        else if (tree[i] == '>')
        {
            if (!l || r)
            {
                printf("T\t");
                printf("\t");
                return 1;
            }
            else
            {
                printf("F\t");
                printf("\t");
                return 0;
            }
        }
    }
}
char a[129], ch;
void main() /// main function
{

    printf("Enter expresion: "); /// user input
    int i = 0;
    ch = getchar();
    while (ch != '\n')
    {
        a[i++] = ch; /// a is an array to store the given user input expression
        ch = getchar();
    }

    infixtotree(a); /// convert to infix to parse tree
    treeprinter();
    printf("\ninfix to prefix: ");
    treetoprefix(1);

    h = height(1) - 1;
    printf("\n");
    printf("prefix to parse tree:  \n");
    prefixtotree(prefixtext);
    printf("\n");
    treeprinter();
    // for (int i = 0; i < 20; i++)
    // {
    //     printf("%d  %c\n", i, prefixtext[i]);
    // }
    printf("\n");
    printf("height of tree: %d\n", h);

    printf("\ntree to infix: ");
    // infixtotree(a);

    treetoinfix(1);
    printf("\n");
    // treeprinter();
    truthtable();
    printf("\n");
    gettruthval();
    printTruthhead(1);
    printf("\n\t");
    truthval(1);
}