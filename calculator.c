#include <stdio.h>
#include <stdlib.h>


#define STACKLEN 100

int error = 0, result;


typedef struct {
    int items[STACKLEN];
    int top;
} Stack;

int is_digit(int digit){

    if(digit>=48 && digit<=57) return 1;

    return 0;
}

int is_stack_full(Stack *s){

    if (s->top < STACKLEN - 1) return 1;

    else {
        printf("Invalid expression\n");
        error = -1;
        return 0;
    }


}

void push(Stack *s, int value) {
    if (is_stack_full(s)) 
        s->items[++(s->top)] = value;
    
    
}

int is_stack_empty(Stack *s){

    if (s->top >= 0) return 1;

    else {
        printf("Invalid expression\n");
        error = -1;
        return 0;
    }


}

int pop(Stack *s) {
    if (is_stack_empty(s)) 
        return s->items[(s->top)--];
     
    
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
        default: return 0;
    }
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' ;
}

void infix_to_postfix(const char *infix, char *postfix) {
    Stack stack = {.top = -1};
    int j = 0;

    for (int i = 0; infix[i]; i++) {
        
        if (infix[i] == ' ') continue;
        
        else if (is_digit(infix[i])) {
            
            while (is_digit(infix[i])) {
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
            error = -1;
            break ;
            
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
    char buffer[STACKLEN];
    int i = 0;

    while (postfix[i]) {
        if (is_digit(postfix[i])) {
            
            int k = 0;
            while (is_digit(postfix[i])) {
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
                error = -1;
                break ;
            }

            switch (postfix[i]) {
                case '+': push(&stack, a + b); break;
                case '-': push(&stack, a - b); break;
                case '*': push(&stack, a * b); break;
                case '/': push(&stack, a / b); break;
                
            }
            i++;
        } 
        else {
            i++;
        }
    }

    if(error != -1) result = pop(&stack);
}

int main() {
    char infix[STACKLEN], postfix[STACKLEN];
    int result;
    printf("Enter an equation : ");
    gets(infix); 

    infix_to_postfix(infix, postfix);
    

    if(error != -1) result = evaluate_postfix(postfix);
    if(error != -1) printf("Result: %d\n", result);

    return 0;
}
