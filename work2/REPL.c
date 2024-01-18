#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_EXPRESSION_LENGTH 1000
#define STACK_SIZE 100

const char* format(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '-') {
            if (i == 0) {
                char* temp = (char*)malloc(strlen(str) + 2);
                strcpy(temp, "0");
                strcat(temp, str);
                str = temp;
            } else if (str[i - 1] == '(') {
                char* temp = (char*)malloc(strlen(str) + 2);
                strncpy(temp, str, i);
                temp[i] = '0';
                strcpy(temp + i + 1, str + i);
                str = temp;
            }
        }
    }
    return str;
}

int getPriority(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(const char *infix, char *postfix) {
    char stack[STACK_SIZE];
    int top = -1;
    int postfixIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i]) || infix[i] == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[postfixIndex++] = infix[i++];
            }
            postfix[postfixIndex++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[postfixIndex++] = stack[top--];
            }
            top--; // 弹出 '('
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            while (top >= 0 && getPriority(stack[top]) >= getPriority(infix[i])) {
                postfix[postfixIndex++] = stack[top--];
            }
            stack[++top] = infix[i];
        }
    }

    while (top >= 0) {
        postfix[postfixIndex++] = stack[top--];
    }

    postfix[postfixIndex] = '\0';
}

double evaluatePostfix(const char *postfix) {
    double stack[STACK_SIZE];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i]) || postfix[i] == '.') {
            stack[++top] = atof(&postfix[i]);
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                i++;
            }
        } else if (postfix[i] == ' ') {
            continue;
        } else {
            double operand2 = stack[top--];
            double operand1 = stack[top--];
            switch (postfix[i]) {
                case '+':
                    stack[++top] = operand1 + operand2;
                    break;
                case '-':
                    stack[++top] = operand1 - operand2;
                    break;
                case '*':
                    stack[++top] = operand1 * operand2;
                    break;
                case '/':
                    stack[++top] = operand1 / operand2;
                    break;
            }
        }
    }

    return stack[0];
}

double calculateExpression(const char *expression) {
    char postfix[MAX_EXPRESSION_LENGTH];
    infixToPostfix(format(expression), postfix);
    return evaluatePostfix(postfix);
}

// int main() {
//     double result = calculateExpression("-3-7*2");
//     printf(" Result: %lf\n", result);
//     return 0;
// }

int main() {
    FILE *inputFile = fopen("calculate.txt", "r");
    FILE *tempFile = fopen("temp_calculate.txt", "w");

    char expression[MAX_EXPRESSION_LENGTH];
    while (fgets(expression, sizeof(expression), inputFile)) {
        expression[strcspn(expression, "\n")] = '\0';
        double result = calculateExpression(expression);
        fprintf(tempFile, "%s=%lf\n", expression, result);
    }

    fclose(inputFile);
    fclose(tempFile);

    if (remove("calculate.txt") == 0) {
        if (rename("temp_calculate.txt", "calculate.txt") != 0) {
            printf("Error renaming file.\n");
        }
    } else {
        printf("Error removing file.\n");
        return 1;
    }

    return 0;
}