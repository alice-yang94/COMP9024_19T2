#include "week1.h"

int main(void)
{
    int fiveDigitNum = fiveDigit();
    if (fiveDigitNum == EXIT_FAILURE)
    {
        printf("Five digit is not found!\n");
    }
    else
    {
        printf("fiveDigit: %d\n", fiveDigitNum);
    }

    float innerProd = innerProdFun(
        (float[]){1.1, 1.4, 1.5},
        (float[]){1.0, 1.0, 1.0},
        3);

    printf("innerProd: %f\n", innerProd);

    float a[M][N] = {
        {1, 2, 3, 4},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    float b[N][P] = {
        {1, 0, 0, 0},
        {2, 0, 0, 0},
        {3, 0, 0, 0},
        {4, 0, 0, 0}};

    float c[M][P];
    matrixProduct(a, b, c);
    printf("matrixProduct: \n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < P; j++)
        {
            printf(" %f", c[i][j]);
        }
        printf("\n");
    }

    able();

    collatzeFib();

    int max = fastMax(1,3,2);
    printf("\nmax: %d\n", max);

    return EXIT_SUCCESS;
}

int fastMax(int num1, int num2, int num3) {
    int max12 = num1 * (num1>=num2) + num2 * (num1<num2);
    int max = max12 * (max12>num3) + num3 * (num3>=max12);
    return max; 
}

void collatzeFib(void) {
    int Fib[FIB_MAX];
    Fib[0] = 1;
    Fib[1] = 1;
    for (int i = 2; i < FIB_MAX; i++) {
        Fib[i] = Fib[i-1] + Fib[i-2];
    }
    for (int i = 0; i < FIB_MAX; i++) {
        printf("Fib[%d] = %d:", i+1, Fib[i]);
        collatze(Fib[i]);
        putchar('\n');
    }
}

void collatze(int n) {
    if (n != 1) {   
        if (n%2 == 0) {
            n = n/2;
            printf(" %d", n);
            collatze(n);
        } else {
            n = 3*n + 1;
            printf(" %d", n);
            collatze(n);
        }
    }
}

void able(void)
{
    int count = 0;
    char str[5] = "abel";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j != i)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (k != j && k != i)
                    {
                        int l = 0+1+2+3-i-j-k;
                        printf("%c%c%c%c\n",str[i],str[j],str[k],str[l]);
                        count ++;
                    }
                }
            }
        }
    }
    printf("Total: %d strings\n", count);
}


void matrixProduct(float a[M][N], float b[N][P], float c[M][P])
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < P; j++)
        {
            c[i][j] = 0.0;
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

float innerProdFun(float a[], float b[], int n)
{
    int i;
    float innerProd = 0.0;
    for (i = 0; i < n; i++)
    {
        innerProd += a[i] * b[i];
    }
    return innerProd;
}

int fiveDigit(void)
{
    /* 5-digit num: 10000-99999 */
    /* 4 * abcde = edcba: num < 25000 and e != (0 || 5) */
    int num;
    for (num = MIN_NUM; num < MAX_NUM; num++)
    {
        int currNum = num;
        int lastDigit = currNum % 10;

        if (lastDigit != 0 && lastDigit != 5)
        {
            int numTimes4 = currNum * 4;
            if (numTimes4 >= 10000)
            {
                int reversedNum = lastDigit * 10000;
                currNum -= lastDigit;
                int i;
                for (i = 4; i > 0; i--)
                {
                    int currDigit = currNum / pow(10, i);
                    currNum -= currDigit * pow(10, i);
                    reversedNum += currDigit * pow(10, 4 - i);
                }

                if (reversedNum == numTimes4)
                {
                    return num;
                }
            }
        }
    }
    return EXIT_FAILURE;
}