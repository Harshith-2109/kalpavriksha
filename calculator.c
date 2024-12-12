#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Stack structure
typedef struct {
    int items[MAX];
    int top;
} Stack;

void push(Stack *s, int value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    } 
    else {
        printf("Invalid expression\n");
        exit(1);
    }
}

int pop(Stack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } 
    else {
        printf("Invalid expression\n");
        exit(1);
    }
}

int peek(Stack *s) {
    return (s->top >= 0) ? s->items[s->top] : -1;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void infix_to_postfix(const char *infix, char *postfix) {
    Stack stack = {.top = -1};
    int j = 0;

    for (int i = 0; infix[i]; i++) {
        
        if (infix[i] == ' ') continue;
        
        else if (isdigit(infix[i])) {
            
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; 
            i--; 
        
        } 
        
        else if (is_operator(infix[i])) {
            while (stack.top != -1 && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            push(&stack, infix[i]);
        }
        
        else{
            printf("Invalid expression");
            exit(0);
            
        }
    }

    while (stack.top != -1) {
        postfix[j++] = pop(&stack);
        postfix[j++] = ' '; 
    }

    postfix[j - 1] = '\0';
}

int evaluate_postfix(const char *postfix) {
    Stack stack = {.top = -1};
    char buffer[MAX];
    int i = 0;

    while (postfix[i]) {
        if (isdigit(postfix[i])) {
            
            int k = 0;
            while (isdigit(postfix[i])) {
                buffer[k++] = postfix[i++];
            }
            buffer[k] = '\0';
            push(&stack, atoi(buffer));
        } 
        else if (is_operator(postfix[i])) {
            int b = pop(&stack);
            int a = pop(&stack);

            if (postfix[i] == '/' && b == 0) {
                printf("Division by zero.\n");
                exit(1);
            }

            switch (postfix[i]) {
                case '+': push(&stack, a + b); break;
                case '-': push(&stack, a - b); break;
                case '*': push(&stack, a * b); break;
                case '/': push(&stack, a / b); break;
                case '^': push(&stack, (int)pow(a, b)); break;
            }
            i++;
        } 
        else {
            i++;
        }
    }

    return pop(&stack);
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter an equation : ");
    gets(infix); 

    infix_to_postfix(infix, postfix);
    

    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}