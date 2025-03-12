#include "stack.h"
#include "utils.h"
#include "validations.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define STR_SIZE 1024

int getPriority(char operator) {
    switch (operator) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    }
}

int toRpn(char * expression, char * output) {
    Stack * stack = initStack();
    stack->top = NULL;

    int i = 0, j = 0;
    int prevtype = -1;
    int isopen = 0;

    while (expression[i] != '\0') {
        char token = expression[i];

        if (!validateToken(token))
            return 0;
    

        if (isdigit(token)) {
            if (prevtype != -1 && !validatePreviousToken(1, prevtype))
                return 0;

            while (isdigit(expression[i])) {
                output[j] = expression[i];
                j++;
                i++;
            }
            output[j] = ' ';
            j++;
            prevtype = 1;
            continue;
        }


        if (token == '(') {
            if (prevtype != -1 && !validatePreviousToken(3, prevtype))
                return 0;
            push(stack, token);
            prevtype = 3;
            isopen++;
        } else if (token == ')') {
            if ((prevtype != -1 && !validatePreviousToken(4, prevtype)) || !isopen)
                return 0;

            while (!isEmpty(stack) && tops(stack) != '(') {
                output[j] = (char)pop(stack);
                j++;
                output[j] = ' ';
                j++;
            }
            if (!isEmpty(stack))
                pop(stack);

            prevtype = 4;
            isopen--;
        } else if (isOperand(token)) {
            if (prevtype != -1 && !validatePreviousToken(2, prevtype))
                return 0;

            while (!isEmpty(stack) && getPriority((char)tops(stack)) >= getPriority(token)) {
                output[j] = (char)pop(stack);
                j++;
                output[j] = ' ';
                j++;
            }
            push(stack, token);
            prevtype = 2;
        }

        i++;
    }

    if ((prevtype != -1 && !validatePreviousToken(5, prevtype)) || isopen)
        return 0;

    while (!isEmpty(stack)) {
        output[j] = pop(stack);
        j++;
        output[j] = ' ';
        j++;
    }
    output[j] = '\0';

    return 1;
}

int calculateRpn(char * expression, char * string) {
    Stack * stack = initStack();

    int i = 0;
    while (expression[i] != '\0') {
        char token = expression[i];
        if (isdigit(token) || token == '.') {
            char * endptr;
            int num = strtol(&expression[i], &endptr, 10);
            push(stack, num);
            i = endptr - expression;
        }

        else if (isOperand(token)) {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            int result = 0;

            switch (token) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/': {
                    if (operand2 == 0) {
                        printf("division by zero\n");
                        free(string);
                        free(expression);
                        exit(0);
                    }
                    result = operand1 / operand2;
                    break;
                }
            }
            push(stack, result);
            i++;
        } else if (token == ' ')
            i++;
    }

    return pop(stack);
}


int main() {
    char * string = generateString(STR_SIZE);

    fgets(string, STR_SIZE, stdin);

    rmnline(string);

    if (!strlen(string)) {
        free(string);
        printf("syntax error\n");
        return 0;
    }

    char * rpn_expression = generateString(STR_SIZE);

    int result = toRpn(string, rpn_expression);
    
    if (!result) {
        free(string);
        free(rpn_expression);
        printf("syntax error\n");
        return 0;
    }

    printf("%d\n", calculateRpn(rpn_expression, string));

    free(string);
    free(rpn_expression);
    return 0;
}
