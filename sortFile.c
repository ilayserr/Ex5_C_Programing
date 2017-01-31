
/************************
Name : Ilay Serr
Email : ilay92@gmail.com
************************/

/*********************************************************
*  sortFile.c                                            *
*  ~~~~~~~~~~~~                                          *
*  second part is a file implementing data structure     *
*  and functions for string list                         *
*  First part is a sort of the second part               *
*********************************************************/

/*** use only these C libraries ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>    // for isspace()



/*********************************************************
   numStrsInList                             (Problem 1.1)
   returns number of strings in list.
*********************************************************/
int numStrsInList(const char* strList);

/*********************************************************
   strListLen                                (Problem 1.2)
   returns number of characters in list.
   includes separating '\0's and excludes terminating '\0's
*********************************************************/
int strListLen(const char* strList);

/*********************************************************
   emptyStrList                              (Problem 1.3)
   writes an empty string list in a given array (buffer).
   buffer size should be at least 2
*********************************************************/
void emptyStrList(char* target);

/*********************************************************
   strListFromWords                          (Problem 1.4)
   writes a new string list into a given array (buffer)
   using words in a given source string.
   returns number of srings in list
   - if buffSize<2, returns -1 (and does nothing
   - if buffSize is too small to hold the entire list, writes
     an empty list and returns 0
*********************************************************/
int strListFromWords(const char* source, char* target, int buffSize);

/*********************************************************
   createStrList                             (Problem 1.5)
   creates a new string list using words in a given string.
   allocates required space (exactly)
   returns pointer to new string list
   (or NULL if allocation failed)
*********************************************************/
char* createStrList(const char* str);

/*********************************************************
   nextStrInList                             (Problem 1.6)
   returns pointer to next string in list.
   - if previous call to function was with different list,
     returns pointer to first string in list.
   - if previous call to function was with same list,
     returns pointer to next string in list
     (following the string returned by the previous call).
     If that string was the last one, then returns NULL.
   - if function is called with NULL pointer, then it re-sets
     the identity of the previous list.
*********************************************************/
char* nextStrInList(char* strList);


/*********************************************************
   strcmpInList                              (Problem 2.1)
   compares two string list according to k indicating
   which string to use as key.
*********************************************************/
int strcmpInList(char* strList1, char* strList2, int k);

/*********************************************************
   strListCmp                                (Problem 2.2)
   compares two string list according to a prioritized
   list of keys
*********************************************************/
int strListCmp(char* strList1, char* strList2, const int keys[], int numKeys);

/*********************************************************
   strListSort                               (Problem 2.3)
   sorts an array of string lists according to a
   prioritized list of keys in ascending lex. order.
*********************************************************/
void strListSort(char** strListArr, int numLists, const int keys[], int numKeys);

/*********************************************************
   printStrLists                             (Problem 2.4)
   prints a list of string lists in sequence.
   prints each list in a separate line and uses tab character
   as delimiter between strings in list
*********************************************************/
void printStrLists(char** strListArr, int numLists);

/*********************************************************
   string2posInt                             (Problem 2.5)
   returns positive integer number that is written in
   string. If string does not represent a positive number
   then the function returns 0.
*********************************************************/
int string2posInt(const char* str);



/*********************************************************
   testProblem1
   function for testing code for Problem 1
   implemented below
   compare results against testProblem1.out
*********************************************************/
void testProblem1(void);

/*********************************************************
   testProblem2
   function for testing code for Problem 2
   implemented below
   compare results against testProblem1.out
*********************************************************/
void testProblem2(void);


/* First part */
/*********************************************************
   main
   use main to call testing procedures
*********************************************************/
/*
int main() {
   // choose tresting procedure you want to run 
   testProblem1();
   // testProblem2();
   return 0;
}
*/

int main(int argc , char** argv) {
   int numLines = 0, i;

   // checking if the number of arguments is valid
   if (argc < 3) {
      fprintf(stderr, "Usage: ./sortFile file key1 [key2 ... ]\n");
      return 1; 
   }

   // declaring the variables and allocating memorry
   FILE* file;
   int* keys = malloc ((argc - 1) * sizeof(int));
   char* strList = malloc((201) * sizeof(char));
   char** list = malloc((201) * (1000) * sizeof(char));

   // checking if the user want the standard input
   if (*argv[1] == '-') file = stdin;
   else file = fopen(argv[1], "r");

   // trying to open the file
   if(!file) {
      fprintf(stderr, "Could not open input file %s for reading\n", argv[1]);
      return 1;   
   }

   // inserting the numbers into an array while checking validity
   for (i = 0; i < argc - 2; i++) {
      int num = string2posInt(argv[i + 2]);

      if (num < 1 || num != atof(argv[i + 2])) {
         fprintf(stderr, "key %s is not a positive integer\n", argv[i + 2]);
         return 1;
      }
      keys[i] = num;
   }

   // inserting the file lines into the allocated array
   i = 0;
   while(fgets(strList,200,file)) {
      list[i] = createStrList(strList);
      i++;
   }

   // using functions 2.3 and 2.4
   numLines = i;
   strListSort(list, numLines, keys, argc - 2);
   printStrLists(list, numLines);

   //freeing memorry
   fclose(file);
   free(keys);
   free(strList);
   free(list);

   return 0;
}


/************************************
Function numStrsInList
Params:
- strList - the given pointer to the list
- count - counts the number of "words" in the list
- len - an index of the location in the list
A function that counts the number of "words" in a given list
Return value: the number of "words"
***********************************/
  
int numStrsInList(const char* strList) {
   int count = 1, len = 0;
   if ((strList[len] == '\0') && (strList[len + 1] == '\0')) 
      return 0;
   while (1) {
      if (strList[len] == '\0') {
         if (strList[len + 1] == '\0') {
            return count;
         } else {
            count++;
         }
      }
      len++;
   }
   return 0;
}     


/************************************
Function strListLen
Params:
- strList - the given pointer to the list
- len - an index of the location in the list
A function that counts the number of characters in a given list
Return value: the number of characters
***********************************/

int strListLen(const char* strList) {
   int len = 0;
   while (1) {
      if (strList[len] == '\0') {
         if (strList[len + 1] == '\0') {
            return len;
         }
      }
      len++;
   }
   return 0;
}

/************************************
Function emptyStrList
Params:
- target - the given pointer to the list
A function that makes an empty list
Return value: nothing
***********************************/

void emptyStrList(char* target) {
   target[0] = '\0';
   target[1] = '\0';
   return;
}


/************************************
Function strListFromWords
Params:
- source - the given pointer to the string
- target - the given pointer to the string list
- buffSize - the size of target
- count - a counter of the number of "words/strings in the list
  useing count is more efficient than using the function "numStrsInList"
A function that copy the string from 'source' to 'target'
Return value: the number of "words" in target (after making it)
***********************************/

int strListFromWords(const char* source, char* target, int buffSize) {
   int count = 0;
   if (buffSize < 2) return -1;
   while (isspace(*source)) source++; 
   if (*source != '\0') count = 1;
   while (*source) {
      if (isspace(*source)) {
         *target = '\0';
         while (isspace(*source)) source++;
         if (*source == '\0') return count;
         count++;
      } else {
         *target = *source;
         source++;
      }
      target++;
   }
   *target = '\0';
   *(target + 1) = '\0';
   while (isspace(*source)) source++; 
   if (*source != '\0'){
      emptyStrList(target);
      return 0;   
   }
   return count;
}


/************************************
Function createStrList
Params:
- str - the given pointer to the string
- len - an index of the location in the list
- count - a counter of the number of charcters while shrinking the spaces
A function that creates a string list in a newly allocated array from words
in a given string str. the allocated space is as effiecient as possible
(no extra spaces).
Return value: a pointer to the start of the new string list
***********************************/

char* createStrList(const char* str) {
   int count = 0, len = 0; 
   while (isspace(str[len])) len++;
   while (str[len]) {
      if (isspace(str[len])) {
         while (isspace(str[len])) len++;
         count++;
      }
      count++;
      len++;
   }
   count += 2;
   char *target = malloc (count * sizeof(char));
   strListFromWords(str , target, count);
   return target;
}



/************************************
Function nextStrInList
Params:
- strList - the given pointer to the string
- last - a pointer to the last list called
- p - a pointer to the last string 
A function that return the next word in a string already called by the function
or NULL if it is the last word in the string. or the first word in the string
if it's the first time the function called the list.
Return value: a pointer to the word requested by the orders given.
***********************************/

char* nextStrInList(char* strList) {
   static char* last = NULL;
   static char* p = NULL;
   if (last == strList && strList != NULL) {
      while (*p != '\0') p++;
      p++;
      if (*p == '\0') return NULL;
      else return p;
   } else {
      p = strList;
      last = strList;
      return strList;
   }
}
       
/*  Second part */

/************************************
Function strcmpInList
Params:
- strList1 - the pointer for the first list
- strList2 - the pointer for the second list
- k - the index of the word to compare
- i - an index to run in the for loop
- str1 - a pointer to the strList1 list
- str2 - a pointer to the strList2 list
A function that compare the k'th word in two strings and return 1 if the word in the 
first list is bigger, 0 if equal and -1 otherwise.
Return value: 1/0/-1 according to what word is bigger
***********************************/
int strcmpInList(char* strList1, char* strList2, int k) {
   char* str1 = NULL;
   char* str2 = NULL;
   int i;
   nextStrInList(NULL);
   for (i = 0; i < k; i++) {
         str1 = nextStrInList(strList1);
   }
   for (i = 0; i < k; i++) { 
      str2 = nextStrInList(strList2);
   } 
   if (str1 == NULL && str2 == NULL) return 0;
   else if (str1 == NULL) return -1;
   else if (str2 == NULL) return 1;
   if (strcmp(str1 ,str2) > 0) return 1;
   else if (strcmp(str1 ,str2) < 0) return -1;
   else return 0; 
}


/************************************
Function strListCmp
Params:
- strList1 - the pointer for the first list
- strList2 - the pointer for the second list
- keys - a pointer to an array of integers representing the word indecis to check
- numKeys - the size of the keys array
- i - an index to run in the for loop
- res - the result of the comparisson in the strcmpInList function
A function that compare the word in two strings according to the order of the
indices given and return 1 if the word in the first list is bigger, 0 if equal
and -1 otherwise. (compare a word at a time at the order given)
uses the strCmpInList function.
Return value: 1/0/-1 according to what list is bigger
***********************************/
int strListCmp(char* strList1, char* strList2, const int keys[], int numKeys) {
   int i, res = 0;
   for (i = 0; i < numKeys; i++) {
      res = strcmpInList(strList1, strList2, keys[i]);
      if (res != 0) return res;
   }
   return 0;
}


/************************************
Function strListSort
Params:
- strListArr - a pointer to an array of lists
- numLists - the number of lists in the array
- keys - a pointer to an array of integers representing the word indecis to check
- numKeys - the size of the keys array
- i - an index to run in the for loop
- j - an index to run in the for loop
- temp - a temporary variable of type char* ro use in the swap
A function that sorts a given array of lists by size using an insertion sort.
using the function strListCmp to determine whice list is bigger
***********************************/
void strListSort(char** strListArr, int numLists, const int keys[], int numKeys) {
   int i ,j;
   char* temp;
   for (i = 0; i < numLists; i++) {
      j = i;
      while ((j > 0) && (strListCmp(strListArr[j - 1], strListArr[j], keys, 
                                             numKeys) == 1)) {
         temp = strListArr[j - 1];
         strListArr[j - 1] = strListArr[j];
         strListArr[j] = temp;
         j--;
      }
   }
}

/************************************
Function printStrLists
Params:
- strListArr - a pointer to an array of lists
- numLists - the number of lists in the array
- i - an index to run in the for loop
- j - an index to run in the for loop
- num - a variable that indicate how many words there is in the current list.
A function that prints a given array of lists. each list in a different line.
***********************************/
void printStrLists(char** strListArr, int numLists) { 
   int num ,i ,j;
   nextStrInList(NULL);
   for (i = 0; i < numLists; i++) {
      num = numStrsInList(strListArr[i]);
      for (j = 0; j < num - 1; j++) {
         printf("%s\t", nextStrInList(strListArr[i]));
      }
      printf("%s\n", nextStrInList(strListArr[i]));
   }
}

/************************************
Function string2posInt
Params:
- str - the pointer for the first list
- num - the number to be returned
A function that convert a given string into a number
Return value: the number converted
***********************************/
int string2posInt(const char* str) {
   int num = atoi(str);
   return num;
}


/*********************************************************************************/
/**********            TESTING PROCEDURES BELOW THIS LINE             ************/
/*********************************************************************************/


/*** buffer size for two testing procedures ***/
#define LEN 100

/*********************************************************
   testProblem1
   use this main function to test your code for Problem 1
   against expected output file - testProblem1.out
*********************************************************/
void testProblem1(void) {
   
   char sentence[LEN] = "\tThis is a long sentence\n\twith more than 10 words.\t\n\t1st word is \"This\"";
   char list[LEN];
   char *str, *list2;
   
   int nStrings, nChars;
   
   printf(" 1) Creating new string list with following sentence:\n%s\n",sentence);
   nStrings = strListFromWords(sentence, list, LEN);
   nChars = strListLen(list);
          

   
   printf(" 2) List has %d strings and %d chars\n",nStrings, nChars);
   if(nStrings == numStrsInList(list)) {
      printf(" 3) Number of strings returned by strListFromWords is identical to number returned by numStrsInList\n");
   } else {
      printf(" 3) Number of strings returned by strListFromWords = %d and number returned by numStrsInList = %d\n", nStrings, numStrsInList(list));
      printf("    ---  You should not reach this condition! ---\n");
   }

   nStrings = numStrsInList(sentence);
   nChars = strListLen(sentence);
   printf(" 4) The sentence string itself is a \"list\" with %d string and %d chars\n\n",nStrings, nChars);

   


   printf(" 5) Applying nextStrInList iteratively on string list...\n");
   nStrings = 1;
   while(NULL != (str = nextStrInList(list))) {
      printf("     String no. %2d in list is '%s'\n",nStrings++,str);
   } // end of while(str)

   if(!str) {
      printf(" 6) Applying nextStrInList one more time yields NULL\n\n");
   } else {
      printf("      --- You should never reach this condition! ---\n\n");
   }

   printf(" 7) Resetting nextStrInList using NULL list.\n");
   nextStrInList(NULL);
   
   // what do you expect this would do?
   printf(" 8) Applying nextStrInList iteratively again, but doing this a bit differently (with differernt outcome)...\n");
   str = list;
   while(NULL != (str = nextStrInList(str))) {
      printf("     Next string is '%s'\n",str);
   }
   
   printf("\n");
   printf(" 9) writing new list with string = 'Hello world !'\n");
   nStrings = strListFromWords("Hello world !", list, LEN);
   nChars = strListLen(list);
   printf("10) List has %d strings and %d chars\n",nStrings, nChars);
   if(nStrings == numStrsInList(list)) {
      printf("11) Number of strings returned by strListFromWords is identical to number returned by numStrsInList\n");
   } else {
      printf("11) Number of strings returned by strListFromWords = %d and number returned by numStrsInList = %d\n", nStrings, numStrsInList(list));
      printf("    ---  You should not reach this condition! ---\n");
   }

   printf("12) creating list2 with string = 'Hello world !'\n");
   list2 = createStrList("Hello world !");
   if(!list2) {
      printf("Memory allocation problem. Need to abort\n");
      return;
   }
   nStrings = numStrsInList(list2); 
   nChars = strListLen(list2);
   printf("13) List2 has %d strings and %d chars\n\n",nStrings, nChars);

   
   str = nextStrInList(list2);
   printf("14) Applying nextStrInList on list2 produces 1st word: '%s'\n",str);
   str = nextStrInList(list);
   printf("15) Applying nextStrInList on list produces 1st word (different list): '%s'\n",str);
   str = nextStrInList(list);
   printf("16) Applying nextStrInList on list once more produces 2nd word:        '%s'\n\n",str);

   printf("17) Freeing list2\n");
   free(list2);

   printf("18) Emptying list\n");
   emptyStrList(list);
   nStrings = numStrsInList(list);
   nChars = strListLen(list);
   printf("18) Emptied list has %d strings and %d chars\n\n",nStrings, nChars);
   
   str = nextStrInList(list);
   printf("18) Applying nextString on list (now empty) produces an odd result: %s\n",str);
   
   printf("Done.\n");

   return;
}
/*** end of testProblem1 ***/

/*********************************************************
   testProblem2()
   use this main function to test your code for Problem 2
   against expected output file - testProblem2.out
*********************************************************/
void testProblem2(void) {

   char list1[LEN], list2[LEN];
   char *str1 = "Hello world, how are you?";
   char* str2 = "Hello world, where is everyone going?";
   int keys[] = {3,1,2,7,5,4,6};
   int i, numKeys = sizeof(keys)/sizeof(int);
   int *myKeys, nK;

   
   printf(" 1) Writing list1 using string: '%s'\n",str1);
   strListFromWords(str1,list1,LEN);
   printf(" 2) list has %d strings and %d characters\n",numStrsInList(list1), strListLen(list1));
   
   printf(" 3) Writing list2 using string: '%s'\n",str2);
   strListFromWords(str2,list2,LEN);
   printf(" 4) list has %d strings and %d characters\n",numStrsInList(list2), strListLen(list2));
   
   printf("\n");
   printf(" 5) comparing list1 and list2 according to different keys:\n\n");

   for(i=0; i<numKeys; i++) {
      printf("      key = %d --> strcmpInList = %d\n",keys[i],strcmpInList(list1,list2,keys[i]));
   }
   
   printf("\n");
   printf(" 6) comparing list1 and list2 according to different prioritized key lists:\n");
  
   myKeys=keys;
   nK=numKeys;
   printf("     keys =  {");
   for(i=0; i<nK; i++) printf(" %d",myKeys[i]);
   printf("} --> strListCmp = %d\n",strListCmp(list1,list2,myKeys, nK));

   myKeys=keys+1;
   nK=numKeys-1;
   printf("     keys =  {");
   for(i=0; i<nK; i++) printf(" %d",myKeys[i]);
   printf("} --> strListCmp = %d\n",strListCmp(list1,list2,myKeys, nK));

   myKeys=keys+1;
   nK=3;
   printf("     keys =  {");
   for(i=0; i<nK; i++) printf(" %d",myKeys[i]);
   printf("} --> strListCmp = %d\n",strListCmp(list1,list2,myKeys, nK));

   printf("Done.\n");
 
   
   return;
}
/*** end of testProblem2 ***/
