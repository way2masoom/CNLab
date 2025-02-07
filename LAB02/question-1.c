// Write a C program to swap the content of 2 variables entered through the 
// command line using function and pointer.


#include<stdio.h>
int main()
{
    int num1,num2;
    printf("Enter the first Number :");
    scanf("%d",&num1);

    printf("Enter the Second Number :");
    scanf("%d",&num2);
    printf("Number Before Swap ");
    printf("Num1 = %d  and num2= %d \n",num1,num2);

    // Swapping Two number
    int temp=num1;
    num1=num2;
    num2=temp;

    printf("Num1 = %d  and num2= %d",num1,num2);



 return 0;
}