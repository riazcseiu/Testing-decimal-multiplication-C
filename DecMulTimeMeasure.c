/* ------------------------------------------------------------------ */
/* Decimal Number Multiplication Testing tools                       */
/* ------------------------------------------------------------------ */
/* Riaz ul haque Mian , DSL, NAIST  */
/* ----------------------------------------------------------------+- */
/*                                                 right margin -->|  */

// DecMulTimeMeasure.c -- first read string form text file as input
//  convert the string to decFloat 64 bit format decDobule,
// Multiply the Number together, and write  the result to another
// text file outplut.txt. 
//#define _CRT_SECURE_NO_DEPRECATE
#define  DECNUMDIGITS 34           // work with up to 34 digits
#include"decDouble.h"
#include <stdio.h>                 // for printf
#include <time.h>
#include <string.h>


unsigned long read_cycles(void)
{
	     unsigned long cycles;
	     asm volatile ("rdcycle %0" : "=r" (cycles));
             return cycles;
}



int main() {
	decDouble a, b , c,d, temp1,temp2;// working numbers 64 bit format
	decContext set;                  // working context

	char string1[DECDOUBLE_String]; // 25 for 64 bit String1 is type of numeric string
	decContextDefault(&set, DEC_INIT_DECDOUBLE); // initialize as 64 bit operation

	   //setep 1
	  //--------------- reading form text file

	FILE *ptr_file_read, *ptr_file_readB,*ptr_file_write , *Mptr_file_write;
	char buf[26]; //
	char bufB[26];
	char multiplicand[9000][26];
	char multiplaier[9000][26];
	int num;
	
	//-------------replace file name here -------------------

	        char fileNameA [40] = "final_result_b.txt";
		char fileNameB [40] = "final_result_b.txt";
	
        //-----------------------------------------------------   


        ptr_file_read = fopen(fileNameA, "r"); //Name of the input file
	
	if (!ptr_file_read)
	{ 
		printf("problem reading inputA.txt");
	    return 1;
	}
	ptr_file_readB = fopen(fileNameB, "r"); //Name of the input file
	if (!ptr_file_read)
	{
		printf("problem reading inputB.txt");
		return 1;
	}

	ptr_file_write = fopen("output.txt", "a+");

	if (!ptr_file_write)
	{
		printf("problem Writing Output.txt");
		return 1;
	}

	Mptr_file_write = fopen("Moutput.txt", "a+");

	if (!ptr_file_write)
	{
		printf("problem Writing MOutput.txt");
		return 1;
	}
	//while (fgets(buf, 100, ptr_file_read) != NULL) //read untill new line

	for (int i = 0; fgets(buf, 100, ptr_file_read) != NULL; i++) //read untill new line
	{
	    // buf[strcspn(buf, "\n")] = 0; //remove \n from string
	     buf[strcspn(buf, "\r\n")] = 0; 
		   strcpy(multiplicand[i], buf); // assign multiplicand max 100
	}
	        fclose(ptr_file_read); // complete all  cover all string
//now multiplicand[] has all the multiplicand which 
		   
	 //------- end reading form tex file 
			for (int i = 0; fgets(bufB, 100, ptr_file_readB) != NULL; i++) //read untill new line
			{
			    //	bufB[strcspn(bufB, "\n")] = 0; //remove \n from string
			     bufB[strcspn(bufB, "\r\n")] = 0; 
				strcpy(multiplaier[i], bufB); // assign multiplicand max 100
			}
			fclose(ptr_file_readB); // complete all  cover all string

		//step 2 calculation in both method
      
          unsigned long cyclestart,cycleend, modcyclestart,modcycleend; // declare for clock test


	clock_t begin_decimal = 0; //initialize time
	clock_t end_decimal = 0;
        int c1 = 0;
      
 
    for (c1 = 0 ; c1<5;c1++) //input loop changing input
	{
	    
		int i = 0;
			decDoubleFromString(&a, multiplicand[c1], &set);
			decDoubleFromString(&b, multiplaier[c1], &set);
			temp1 = a; temp2 = b; 
			begin_decimal = clock();
			for(int m=0;m<5;m++) //doing the same operation repet
			{ 
				a = temp1; b = temp2;
                                 cyclestart = read_cycles();

				decDoubleMultiply(&a, &a, &b, &set);    // a=aXb
				
				 cycleend = read_cycles();

                  printf("Took %lu cycles\n", cycleend - cyclestart);

				//	decDoubleAdd(&a, &a, &b , &set);
				
			}
		    end_decimal = clock();
			fprintf(ptr_file_write, "%lf \n", (double)( end_decimal- begin_decimal) / CLOCKS_PER_SEC);
			decDoubleToString(&a, string1);
            printf("Exsisting function \n");
	    //  printf("test\n");	    
	    // printf(" %s\n",  string1);
	    // printf(" %s\n",  multiplicand[c1]);
	    // printf(" %s\n",  multiplicand[c1+1]);
	    
    printf("%s x %s => %s\n", multiplicand[c1], multiplaier[c1], string1);
	}
	
  
 // printf ("time modify: % lf \n",(double)(end_decimal-begin_decimal)/CLOCKS_PER_SEC);


 
 //solution with exsisting function
  clock_t begin_modify=0;
  clock_t end_modify = 0;


  int c2 = 0;

  for (c2 = 0 ; c2<5;c2++)
	{
	    
	  int i = 0;
	  decDoubleFromString(&c, multiplicand[c2], &set);
	  decDoubleFromString(&d, multiplicand[c2 + 1], &set);
	  temp1 = c; temp2 = d;
	  begin_modify = clock();
	  for (int m = 0; m<5; m++) //doing the same operation repet
	  {
		  c = temp1; d = temp2;
                 modcyclestart = read_cycles();

		  MdecDoubleMultiply(&c, &c, &d, &set);    // a=aXb

	  	 modcycleend = read_cycles();

                  printf("Took %lu cycles mod \n", modcycleend - modcyclestart);


	  }
	  end_modify = clock();
	  fprintf(Mptr_file_write, "%lf \n", (double)(end_modify- begin_modify) / CLOCKS_PER_SEC);
	  decDoubleToString(&c, string1);
	  printf("Modify function \n");
	  
	  printf("%s x %s => %s\n", multiplicand[c2], multiplicand[c2 + 1], string1);
	}
	
 clock_t end=clock();
 // printf ("time exsisting %lf \n",(double)(end-begin)/CLOCKS_PER_SEC);




  //step 3  // ------------ writing result in text file

   
	
     
     // fprintf(ptr_file_write,"%lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
     
			

		fclose(ptr_file_write);

      
	  getchar();
  return 0;
 
  } // main 

