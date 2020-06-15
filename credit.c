/*
This project involves verifying a credit card to be an:

1. American Express (starting with 34 or 37) or

2. a MasterCard (starting with 51, 52, 53, 54 or 55) or

3. a Visa (4).

We shall be applying the Luhn's algorithm which helps us to determine whether a credit card number is syntactically valid or not.
*/

//Include the header files
#include <stdio.h>
#include <cs50.h>
#include <math.h>

//Method declarations
long getNumber(long);
bool checkLength(long);
bool checkValid(long);
bool checkSum(long);
bool checkCard(long);

int count = 0; //A global variable to keep count of the number of digits in the card to be used throughout various methods.

string card = ""; //A global variable which stores the card type dynamically.


//Main method
int main(void)
{
    long number = 0; //Card number variable declaration & instantiation.

    number = getNumber(number); //Calls the getNumber(number) method.
    
    if (checkCard(number)) //The checkCard(number) verifies whether the entered number satisfies all the conditions for a credit card.
        printf("%s\n", card); //Prints the card type
    else
        printf("INVALID\n");
}


//This method prompts the user for input until a valid input is received.
long getNumber(long n)
{
    do
    {
        n = get_long("Credit Card Number: "); //get_long() from "cs50.h" automatically rejects any other input besides integer.
    }
    while(n<1);
    
    return n;
}


//This method verifies the length of the number entered to match the required number of digits for being a credit card.
bool checkLength(long n)
{
    do
    {
        n = n/10;
        count++;
    }
    while(n>0);
    
    if (count == 13 || count == 15 || count == 16)
        return true;
    else
        return false;
}


/*
This method checks the pre-condition (starting digit/digits verification) for a card number to be one of the 3 credit card types after the number 
of digits are verified.
*/
bool checkValid(long n)
{
    if (count == 13)
    {
        n = n/(pow(10, count-1)); //Captures the 1st digit of the 13 digit number.
        
        if (n == 4)
        {
            card = "VISA";
            return true;
        }
        else
            return false;
    }
    
    else if (count == 16)
    {
        n = n/(pow(10, count - 2)); //Captures the 1st 2 digits of the 16 digit number.
        
        long r = n/10; //Captures the 1st digit of the 16 digit number.
        
        if (n == 51 || n == 52 || n == 53 || n == 54 || n == 55)
        {
            card = "MASTERCARD";
            return true;
        }
        else if (r == 4)
        {
            card = "VISA";
            return true;
        }
        else
            return false;
    }
    
    else if (count == 15)
    {
        n = n/(pow(10, count-2)); //Captures the 1st 2 digits of the 15 digit number.
        
        if (n == 34 || n == 37)
        {
            card = "AMEX";
            return true;
        }
        else
            return false;
    }
    
    else
        return false;
}


//This method verifies whether the entered number satisfy the Luhn's algorithm used to validate the combination of credit card numbers.
bool checkSum(long n)
{
    int counter = 0; //Keeps count of number of digits in the entered number.
    
    long sum = 0;
    long alterSum = 0;
    
    //Applied Luhn's algorithm.
    do
    {
        n = n/10;
        counter++;
        
        if (counter%2)
            sum += n*2;
        else
            alterSum += n;
    }
    while (n>0);
    
    if ((sum + alterSum) % 10) //Checks if the total sum is divisible by 10 i.e. the possible last digit is 0.
        return true;
    else
        return false;
}


//This method verifies the entire conditions for the validity of the entered number to be a credit card number.
bool checkCard(long number)
{
    if (checkLength(number)) //Checks length of entered number.
    {
        if (checkValid(number)) //Checks pre-conditions to classify the entered number accordingly.
        {
            if (checkSum(number)) //Verifies if the entered number satisfies the Luhn's algorithm.
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}