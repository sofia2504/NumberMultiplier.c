// Sofia Beyerlein
// NID: so892224
// Homework 4 "homework4.c"
//  COP 3223C Section 1, Fall 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 1000

_Bool SumCIntegers(char* cx, char* cy, char* res)
{
    size_t len_cx = strlen(cx), len_cy = strlen(cy);
    unsigned char cur_sum = 0, cur_remainder = 0;
    long long int i = 0;
    if (len_cx < len_cy)
    {
        for (i = len_cx; i >= 0; i--)
            *(cx + i + (len_cy - len_cx)) = *(cx + i);
        for (i = 0; i < len_cy - len_cx; i++)
            *(cx + i) = '0';
        
    }
    else if (len_cy < len_cx)
    {
        for (i = len_cy; i >= 0; i--)
            *(cy + i + (len_cx - len_cy)) = *(cy + i);
        for (i = 0; i < len_cx - len_cy; i++)
            *(cy + i) = '0';
    }
    len_cx = (len_cx > len_cy ? len_cx : len_cy);
    if (len_cx == 0)
    {
        *res = '\0';
        
        return 1;
    }
    *(res + len_cx) = '\0';
    for (i = len_cx - 1; i >= 0; i--)
    {
        if (*(cx + i) < '0' || *(cx + i) > '9' || *(cy + i) < '0' || *(cy + i) > '9')
        {
            *res = '\0';
            
            return 0;  // Error: at least one of the summands is not a non-negative integer
        }
        cur_sum = *(cx + i) + *(cy + i) - 2 * '0' + cur_remainder;
        cur_remainder = cur_sum / 10;
        *(res + i) = cur_sum - (cur_remainder * 10) + '0';
    }
    // for i
    if (cur_remainder == 1)
    {
        if (len_cx == MAX_STR_LEN)    // Overflow
        {
            *res = '\0';
            return 0;
        }
        for (i = len_cx; i >= 0; i--)
            *(res + i + 1) = *(res + i);
        *res = '1';
    }
    
    return 1;
}


_Bool MultiplyCIntegers(char* cx, char* cy, char* res){
  //error empty strings
  if(cx==NULL || cy==NULL || strlen(cx)==0 || strlen(cy)==0)
    return 0;

  size_t cxLen= strlen(cx), cyLen= strlen(cy);

  //stores Sum Multiplication + 10 to see if it's greater than MAX_STR_LEN (add all numbers)
  char result[MAX_STR_LEN] = "0";

  //counts shifts of 0 when multiplying
  int cxI = 0;

  //printf("%s %s\n\n",cx,cy);

  for(int i= cxLen-1; i>=0; i--){
    //turns char into integer with '0'
    int a= cx[i] - '0';
    int carry = 0;
    //printf("a = %d\n", a);

    //store multiplication
    char *mult = calloc(MAX_STR_LEN,sizeof(char));
    //current index of mult array
    int multI = 0;

    for(int k= cyLen-1; k>=0; k--){
      //turns char into integer with '0'
      int b= cy[k] - '0';
      //printf("b = %d\n", b);
      int c = a*b + carry;
      
      //saves the number that is being carried
      carry = c /10;

      //number that is NOT being carried
      mult[multI] = (c % 10) + '0';
      //printf("%c ", mult[multI]);
      multI++;
    }
    
    //if there's no more numbers to multiply but theres a carry add the carry
    if(carry > 0){
      mult[multI] = carry + '0';
      multI++;
    }

    //store reverse string cause MULT was "backwards"
    
    int i = 0;
    int j = multI - 1;
    while(i<j){
      int resp = mult[i];
      mult[i] = mult[j];
      mult[j] = resp;
      i++;
      j--;
    }
    
    //accounts for the zeros when multiplying numbers 
    for(int pe = 0; pe < multI+cxI; pe++){
      if(mult[pe] == 0){
        mult[pe] = '0';
      }
      //printf("%c", t[pe]);
    }

    
    //stores copy of results
    char *temp = calloc(MAX_STR_LEN,sizeof(char));
    strcpy(temp,result);
    
    //adds all the numbers and stores them in result
    SumCIntegers(temp,mult,result);
    //printf("\n%s\n", result);

    //shifts one more zero
    cxI++;
  }
  //printf("%s", result);
  strcpy(res,result);

  //checks for overflow
  int size = strlen(result);
  //printf("%d", size);
  if(size > MAX_STR_LEN)
    return 0;


  return 1;
}

void GetFactorial(unsigned short n, char* res){
  char result[1000] = "1";
  strcpy(res,result);

  for(int i = n; i >= 1; i--){
    char a[1000] = "";
    //turns int to char
    sprintf(a, "%d", i);
    MultiplyCIntegers(a, result, res);
    //printf("hello) %s\n", res );
    //printf("index = %d\n", i);
    strcpy(result,res);
    //printf("2) %s * %s = %s\n", a, result, res );
  }
  printf("\n");
}

int main(void) {
  char* cx= malloc(MAX_STR_LEN);
  char* cy= malloc(MAX_STR_LEN);
  char* res= malloc(MAX_STR_LEN);

  cx= "600";
  cy= "23";

  int bol = MultiplyCIntegers(cy, cx, res);

  GetFactorial(50,res);

  printf("%s",res);

  return 0;
}