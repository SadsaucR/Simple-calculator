#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double parseFactor(const char** expr);
double parseTerm(const char** expr);
double parseExpression(const char** expr);

double parseFactor(const char** expr) {
    double result = 0.0;

    // 處理括號
    if (**expr == '(') 
    {
        (*expr)++;
        result = parseExpression(expr);
        if (**expr == ')') 
            (*expr)++;       
        else 
        {
            fprintf(stderr, "錯誤：缺少右括號\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (isdigit(**expr) || **expr == '.') 
    {
        // 解析數字
        result = atof(*expr);
        while (isdigit(**expr) || **expr == '.') 
            (*expr)++;
        
    }
    else 
    {
        fprintf(stderr, "錯誤：不正確的表達式\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

// 解析乘法和除法
double parseTerm(const char** expr) 
{
    double left = parseFactor(expr);

    while (**expr == '*' || **expr == '/') 
    {
        char op = *(*expr)++;
        double right = parseFactor(expr);

        if (op == '*') 
            left *= right;
        
        else 
        {
            if (right != 0) 
                left /= right;
            
            else 
            {
                fprintf(stderr, "錯誤：除數不能為零\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return left;
}

// 解析加法和減法
double parseExpression(const char** expr) 
{
    double left = parseTerm(expr);

    while (**expr == '+' || **expr == '-') 
    {
        char op = *(*expr)++;
        double right = parseTerm(expr);

        if (op == '+')        
            left += right;      
        else        
            left -= right;      
    }

    return left;
}

int main() 
{
    char expression[100];

    printf("輸入表達式：");
    fgets(expression, sizeof(expression), stdin);

    // 移除換行符
    for (int i = 0; expression[i] != '\0'; i++) 
    {
        if (expression[i] == '\n') 
        {
            expression[i] = '\0';
            break;
        }
    }

    const char* exprPtr = expression;
    double result = parseExpression(&exprPtr);

    printf("結果：%.2f\n", result);

    return 0;
}