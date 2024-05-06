#include <stdio.h>
#include <string.h>
#include <stdbool.h>
struct Stack {
    char data[20];
    int top;
};

void initialize(struct Stack* stack) {
    stack->top = -1;
}

void push(struct Stack* stack, char c) {
    if (stack->top < 19) {
        stack->data[++stack->top] = c;
    }
}

char pop(struct Stack* stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0'; 
}

// Check if a string is a palindrome
bool isPalindrome(const char* str) {
    struct Stack stack;
    initialize(&stack);
    int len = strlen(str);
   int i;
    for (i = 0; i < len; ++i) {
        push(&stack, str[i]);
    }

    for ( i = 0; i < len; ++i) {
        char c = pop(&stack);
        if (c != str[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    char a[20];
    printf("Enter a string: ");
    scanf("%s", a);

    if (isPalindrome(a)) {
        printf("%s is a palindrome.\n", a);
    } else {
        printf("%s is not a palindrome.\n", a);
    }

    return 0;
}
