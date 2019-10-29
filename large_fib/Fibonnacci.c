#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include "Fibonacci.h"

// Use bool since it's only true or false
bool leftRight(HugeInteger* a, HugeInteger* b)
{
    if(a->length > b->length)
    {
        return true;
    }
    else if(b->length > a->length)
    {
        return false;
    }

    // Check to see if digit is greater
    for(int n = (a->length-1); n >= 0; n--)
    {
        if(a->digits[n] > b->digits[n])
        {
            return true;
        }
        else if(b->digits[n] > a->digits[n])
        {
            return false;
        }
    }

    // HugeIntegers are equal
    return false;
}

// Returns the smaller integer
int theSmallest(int x, int y)
{
    if(x <= y) return x;
    else return y;
}

// Returns the biggest integer
int theBiggest(int x, int y)
{
    if(x >= y) return x;
    else return y;
}

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    // if p or q are null
    if(p == NULL || q == NULL)
    {
        return NULL;
    }


    // Allocate memory for huge integer
    HugeInteger* r = malloc(sizeof(HugeInteger));
    // Ensure huge integer was allocated memory
    if(r == NULL)
    {
        hugeDestroyer(r);
        return NULL;
    }

    // Finds largest length
    r->length = (theBiggest(p->length, q->length) + 1);
    r->digits = malloc(sizeof(int) * (r->length));
    if(r->digits == NULL)
    {
        // Ensure digits were allocated memory
        hugeDestroyer(r);
        return NULL;
    }

    int buffer = 0;

    // Loop
    int smallestLength = theSmallest(p->length, q->length);

    for(int i = 0; i < r->length; i++)
    {
        // Add the buffer to digits
        r->digits[i] = 0;
        r->digits[i] = r->digits[i] + buffer;
        buffer = 0;

        // As long as it is the smallest
        if(i < smallestLength)
        {
            r->digits[i] = r->digits[i] + (p->digits[i] + q->digits[i]);
            // If the element has more than 1 digit
            if(r->digits[i] > 9)
            {
                // Add one
                buffer++;
                // Minus 10 to digit
                r->digits[i] = r->digits[i] - 10;
            }
        }

            // Continue adding if huge integer is larger
        else if (i < theBiggest(p->length, q->length))
        {
            // If p is bigger than q
            if(p->length > q->length)
            {
                // Adding together
                r->digits[i] = r->digits[i] + p->digits[i];
                // If it has more than 1 digit
                if(r->digits[i] > 9)
                {
                    buffer++;
                    // Minus 10 again
                    r->digits[i] = r->digits[i] - 10;
                }
            }
                // if q is bigger than p :D
            else if (q->length > p->length)
            {
                // Adds together
                r->digits[i] = r->digits[i] + q->digits[i];
                // If it has more than 1 digit
                if(r->digits[i] > 9)
                {
                    // Add 1
                    buffer++;
                    // Minus 10
                    r->digits[i] = r->digits[i] - 10;
                }
            }
        }
    }
    // If there is empty element then the last element is garbage
    if(r->digits[r->length-1] > 0 && r->digits[r->length-1] <= 9)
    {
        return r;
    }
        // Create it with 1 less digit
    else
    {
        // Initiate z
        HugeInteger* z = malloc(sizeof(HugeInteger));
        if(z == NULL)
        {
            hugeDestroyer(r);
            hugeDestroyer(z);
            return NULL;
        }

        // Counts any leftover zeros
        int leftover = 0;

        // For every zero
        for(int i = r->length-1; i > 0 && r->digits[i] == 0; i--)
        {
            leftover = leftover + 1;
        }

        // Leftover + 1
        if(leftover > 0)
        {
            z->length = r->length - (leftover);
        }
        else
        {
            z->length = r->length - 1;
        }

        // Initialize z digits now
        z->digits = malloc(sizeof(int) * (z->length));

        if(z->digits == NULL)
        {
            hugeDestroyer(r);
            hugeDestroyer(z);
            return NULL;
        }

        // Whatever r is, put into z
        for(int i = 0; i < z->length; i++)
        {
            z->digits[i] = r->digits[i];
        }
        // Free r
        hugeDestroyer(r);
        return z;
    }
}

// if p is null, return null. if it is not, get rid of it
HugeInteger *hugeDestroyer(HugeInteger *p)
{
    if(p == NULL)
    {
        return NULL;
    }
    free(p->digits);
    free(p);
    return NULL;
}

// Convert string to huge integer
HugeInteger* parseString(char* str)
{
    // Allocate memory for HugeInteger
    HugeInteger* a = malloc(sizeof(HugeInteger));

    // if a is null free it
    if(a == NULL)
    {
        free(a);
        return NULL;
    }

    // If string is empty make it zero
    if(str == "") str = "0";
    if(str == NULL)
    {
        free(a);
        return NULL;
    }

    a->length = strlen(str);

    // Allocate memory for a->digits * a->length
    a->digits = malloc(sizeof(int) * a->length);

    // if p is null, free it
    if(a->digits == NULL)
    {
        hugeDestroyer(a);
        return NULL;
    }

    // Converting a character into an integer
    for(int i = (a->length-1), j = 0; i >= 0; i--)
    {
        a->digits[i] = (str[j]-'0');
        j++;
    }

    return a;
}

// Converting integer into huge integer
HugeInteger* parseInt(unsigned int n)
{
    HugeInteger* a = malloc(sizeof(HugeInteger));

    if(a == NULL)
    {
        free(a);
        return NULL;
    }

    // If n is not 0
    if(n != 0)
    {
        a->length = ((int)log10(n))+1;
    }
        // if n is zero
    else
    {
        a->length = 1;
    }

    // Allocate memory for an array of integers
    a->digits = malloc(sizeof(int) * a->length);

    // if a->digits is null, free everything
    if(a->digits == NULL)
    {
        hugeDestroyer(a);
        return NULL;
    }

    // Assign a temporary variable that cannot be negative
    unsigned int temp = n;

    // Put the integers into an array
    for(int i = 0; i < (a->length); i++)
    {
        a->digits[i] = (temp%10);
        temp = temp / 10;
    }

    return a;
}

// Converting a huge integer into a positive integer
unsigned int *toUnsignedInt(HugeInteger *p)
{
    // if p is empty
    if(p == NULL)
    {
        return NULL;
    }

    // initialize n
    unsigned int *n = malloc(sizeof(unsigned int));

    if(n==NULL)
    {
        free(n);
        return NULL;
    }

    // initialize maximum
    HugeInteger *maximum;

    maximum = parseInt(UINT_MAX);

    // If p is larger, free maximum & return null
    if(leftRight(p, maximum))
    {
        hugeDestroyer(maximum);
        return NULL;
    }

    // free maximum no matter what
    hugeDestroyer(maximum);

    // Placing all the digits in the huge integer to the unsigned integer
    *n = (unsigned int)p->digits[0];

    for(int i = 1, j = 10; i < p->length; i++)
    {
        *n = *n + p->digits[i] * j;
        j = j * 10;
    }
    return n;
}

// Fib function
HugeInteger *fib(int n)
{
    // Huge Integer pointer of pointers
    HugeInteger** f = (HugeInteger**)malloc(sizeof(HugeInteger*) * (n+1));

    // if f is null, free it & return null
    if(f == NULL)
    {
        free(f);
        return NULL;
    }

    // Initialize the first two positions of the array
    f[0] = parseInt(0);
    f[1] = parseInt(1);

    // Fib logic
    for (int i = 0; i <= n-2; i++)
    {
        // Next array position
        f[i+2] = hugeAdd(f[i],f[i+1]);
    }

    // free
    for(int i = 0; i < n; i++)
    {
        hugeDestroyer(f[i]);
    }

    // Last position
    return f[n];
}
