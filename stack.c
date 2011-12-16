/* Checks whether a user input consists of properly nested parathesis
 * and/or curly brackets by simulating a stack structure */

#include <stdbool.h>        /* C99 only */
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

/* external variables */
int contents[STACK_SIZE];
int top = 0;
char ch;

/* prototypes */
void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(char ch);
int pop(void);
void stack_overflow(void);
void stack_underflow(void);
void check_illegal_chars(char ch);
bool match_pairs(char ch);
void load_stack(void);

int main(void)
{
    bool matched;

    printf("\nThis is a program designed to test whether the series of"
           " parenthesis and/or curly brackets you enter are properly" 
           " nested.\n");
    printf("\nPlease enter a nested series of parenthesis and/or curly"
           " brackets: ");

    load_stack();

    matched = match_pairs(ch);

    if (matched) {
        printf("\nProperly nested.\n");
    } else {
        printf("\nNot properly matched.\n");
    }

    return 0;
}

void make_empty(void)
{
    top = 0;
}

bool is_empty(void)
{
    return top <= 0;
}

bool is_full(void)
{
    return top >= STACK_SIZE;
}

void push(char ch)
{
    if (is_full())
        stack_overflow();
    else 
        contents[top++] = ch;
}

int pop(void)
{
    if (is_empty())
        stack_underflow();
    else
        return contents[--top];
}

void stack_overflow(void)
{
    printf("\nSorry, but you can no longer enter numbers: stack full.\n");
}

void stack_underflow(void)
{
    printf("\nSorry, but you can no longer pop numbers: stack empty.\n");
}

void check_illegal_chars(char ch)
{
    switch (ch) {
        case '(': case '{':
        case ')': case '}':         return;
        default:                    printf("\nSorry, illegal characters.\n");
                                    exit(EXIT_FAILURE);
    }
}

bool match_pairs(char ch) {

    while ((ch != '\n') && (ch != '(') && (ch != '{')) {
        check_illegal_chars(ch);
        while (ch == ')') {
            if (pop() != '(') {
                return false;
            }
            ch = getchar();
        }

        while (ch == '}') {
            if (pop() != '{') {
                return false;
            }
            ch = getchar();
        }
    }

    if (is_empty()) {
        return true;
    } else {
        printf("\nMore left operators than right operators.\n");
        return false;
    }
}

void load_stack(void)
{
    while (((ch = getchar()) != '\n') && (ch != ')') && (ch != '}')) {
        check_illegal_chars(ch);
        if (is_full()) {
            stack_overflow();
        } else { 
            push(ch);
        }
    }
}
