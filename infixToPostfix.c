#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_EXPR 256

static int precedence(char op)
{
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

static int to_postfix(const char *infix, char *postfix)
{
    char operators[MAX_EXPR];
    int top = -1, out = 0;
    for (int i = 0; infix[i] != '\0'; ++i) {
        char ch = infix[i];
        if (isspace((unsigned char)ch)) continue;
        if (isdigit((unsigned char)ch)) {
            postfix[out++] = ch;
            postfix[out++] = ' ';
        } else if (ch == '(') {
            operators[++top] = ch;
        } else if (ch == ')') {
            while (top >= 0 && operators[top] != '(') {
                postfix[out++] = operators[top--];
                postfix[out++] = ' ';
            }
            if (top < 0) return 0;
            --top;
        } else if (precedence(ch) != 0) {
            while (top >= 0 && precedence(operators[top]) != 0 &&
                   (precedence(operators[top]) > precedence(ch) ||
                    (precedence(operators[top]) == precedence(ch) && ch != '^'))) {
                postfix[out++] = operators[top--];
                postfix[out++] = ' ';
            }
            if (top == MAX_EXPR - 1) return 0;
            operators[++top] = ch;
        } else {
            return 0;
        }
        if (out >= MAX_EXPR - 2) return 0;
    }
    while (top >= 0) {
        if (operators[top] == '(') return 0;
        postfix[out++] = operators[top--];
        postfix[out++] = ' ';
    }
    if (out == 0) return 0;
    postfix[out - 1] = '\0';
    return 1;
}

static int integer_power(int base, int exponent, int *ok)
{
    int result = 1;
    if (exponent < 0) {
        *ok = 0;
        return 0;
    }
    while (exponent-- > 0) result *= base;
    return result;
}

static int evaluate(const char *postfix, int *result)
{
    int values[MAX_EXPR], top = -1;
    for (int i = 0; postfix[i] != '\0';) {
        if (isspace((unsigned char)postfix[i])) {
            ++i;
        } else if (isdigit((unsigned char)postfix[i])) {
            values[++top] = postfix[i++] - '0';
        } else {
            if (top < 1) return 0;
            int right = values[top--], left = values[top--], answer = 0;
            switch (postfix[i++]) {
            case '+': answer = left + right; break;
            case '-': answer = left - right; break;
            case '*': answer = left * right; break;
            case '/':
                if (right == 0) return 0;
                answer = left / right;
                break;
            case '%':
                if (right == 0) return 0;
                answer = left % right;
                break;
            case '^': {
                int ok = 1;
                answer = integer_power(left, right, &ok);
                if (!ok) return 0;
                break;
            }
            default: return 0;
            }
            values[++top] = answer;
        }
        if (top >= MAX_EXPR - 1) return 0;
    }
    if (top != 0) return 0;
    *result = values[top];
    return 1;
}

int main(void)
{
    char infix[MAX_EXPR], postfix[MAX_EXPR];
    int result;
    puts("Enter an infix expression with single-digit operands (for example 3+(4*2)):");
    if (fgets(infix, sizeof infix, stdin) == NULL) return 1;
    if (!to_postfix(infix, postfix)) {
        puts("Invalid or oversized expression.");
        return 1;
    }
    printf("Postfix: %s\n", postfix);
    if (!evaluate(postfix, &result)) {
        puts("Expression cannot be evaluated.");
        return 1;
    }
    printf("Value: %d\n", result);
    return 0;
}
