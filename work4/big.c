#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 50

void initNumber(char* number) {
    for (int i = 0; i < N; i++) {
        number[i] = '0' + rand() % 10;
    }
} 

void printNumber(char* number) {
    for (int i = 0; i < N; i++) {
        printf("%c ", number[i]);
    }
    printf("\n");
}

void printResult(char* result) {
    for (int i = 0; i < 2 * N; i++) {
        printf("%c ", result[i]);
    }
    printf("\n");
}

void bigAdd(char* result, char* num1, char* num2) {
    int carry = 0;
    for (int i = N - 1; i >= 0; i--) {
        int digitSum = (num1[i] - '0') + (num2[i] - '0') + carry;
        result[i + N] = (digitSum % 10) + '0';
        carry = digitSum / 10;
    }
    result[N - 1] = carry + '0'; // 加法多一位
}

void bigMul(char* result, char* num1, char* num2) {
    int temp[N * 2];
    memset(temp, 0, sizeof(temp));

    for (int i = N - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            temp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
            temp[i + j] += temp[i + j + 1] / 10;
            temp[i + j + 1] %= 10;
        }
    }

    for (int i = 0; i < N * 2; i++) {
        result[i] = temp[i] + '0';
    }
}

int main() {
    char n1[N];
    srand(time(NULL));
    initNumber(n1);
    printNumber(n1);

    char n2[N];
    srand(time(NULL) + 666);
    initNumber(n2);
    printNumber(n2);

    char r1[N * 2];
    memset(r1, '-', sizeof(r1));
    bigAdd(r1, n1, n2);
    printResult(r1);

    char r2[N * 2];
    memset(r2, '-', sizeof(r2));
    bigMul(r2, n1, n2);
    printResult(r2);
}