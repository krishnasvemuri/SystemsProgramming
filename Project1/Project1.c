/* Name : Krishna Sindhuri Vemuri G-Number : G01024066
   Class : CS 531 Section : 003 Professor : Harold Greenwald
   HomeWork Assignment 1 Date September 17th 2017
*/
/* The following program
        --- takes 10 strings as input from the user
        --- sorts the strings in either ascending or descending order according to the user's input.
        --- prints the strings in the sorted order
        --- prints the strings with lowest and highest ASCII values
*/
/* According to the specification of the assignment the following error checking is done in the program,
        --- do not accept new line as an input.
        --- do not accept just spaces as input.
        --- do not accept duplicate strings.
        --- do not accept strings that are empty or greater than 25 in size
*/

/* According the specification of the assignment at least two user defined functions need to be included.
The user defined functions used are as follows,
        --- sort_Ascending[This function sorts the array of strings in ascending order].
        --- sort_Descending[This function sorts the array of strings in descending order].
        --- letter[This function only takes either A or D as input and calls functions sort_Ascending, sort_Descending or itself to print the strings accordingly.]
*/
#include<stdio.h>
#include<string.h>
void sort_Ascending(char asc[10][26]);// Declared a user defined function to sort the input strings in ascending order
void sort_Descending(char des[10][26]);//Declared a user defined function to sort the input strings in descending order
void letter();// Declared a user defined function to take either A or D as user input and call the functions for sorting appropriately
        void main() {

                char str[10][26], // A two dimensional array used to store the 10 strings that are to be sorted of size 25 (+1 for the \0 character).
                        tstr[10][26], // A two dimensional array which is used to compare the contents of the original array str for error checking
                        temp[25], // The temporary variable used while sorting the strings using the bubble sort algorithm.
                        let [5], // A character variable used to sort the strings in either Ascending or Descending order using the user input
                        * count; // An array of characters used to count the numbers of spaces in error checking

                int i, j, k, space; // Loop control variables
                printf("Please enter the 10 strings that are to be sorted.");
                //The following code checks if the input string only consists of spaces.
                for (i = 0; i < 10; i++) {
                        printf("\n Please enter the string %d :\n", i + 1);
                        fgets(str[i], sizeof(str), stdin);
                        count = str[i];
                        for (space = 0; * count; count++) {
                                if ( * count != ' ')
                                        continue;
                                space++;
                        }
                        //The following code checks if the input already exists and prints an error message if it does.
                        for (j = 0; j < i; j++) {
                                if (strcmp(str[i], tstr[j]) == 0) {
                                        i--;
                                        printf("\nPlease do not enter duplicate strings\n");
                                }
                        }
                        //The following code checks the size of the input. It has to be less than or equal to 25 and should not be empty. If it is violated it prints an error message
                        if (((strlen(str[i])) < 1 || (strlen(str[i]) > 26))) {

                                i--;

                                printf("\nPlease enter a string whose size is between 1 and 25\n");

                        }
                        //The following code checks if the input is a newline i.e; if the user presses the ENTER key without typing any values then it prints an error message
                        else if (str[i] == NULL || * str[i] == '\n') {
                                i--;
                                printf("You have entered a newline, please enter printable characters only");
                        }
                        //The following code prints an error message if the input consists of only spaces.
                        else if (space == strlen(str[i] + 1)) {
                                i--;
                                printf("You have entered %d space(s), please enter printable characters only\n", space);
                        }
                        //After all the error checking, if the input is valid then the contents of str are copied to tstr so that it can be used in the duplicate string error checking.
                        else
                                strcpy(tstr[i], str[i]);

                }
                //The following code sorts the string using the bubble sort algorithm
                for (k = 0; k < 10; k++) {

                        for (j = k + 1; j < 10; j++) {

                                if (strcmp(str[k], str[j]) > 0) {

                                        strcpy(temp, str[k]);

                                        strcpy(str[k], str[j]);

                                        strcpy(str[j], temp);

                                }

                        }

                }
                //This is a function to print the array of strings in ascending order
                void sort_Ascending(char asc[10][26]) {

                                printf("\nThe strings in Ascending Order\n");

                                for (i = 0; i < 10; i++) {

                                        printf("%s\n", asc[i]);

                                }
                        }
                        //This is a function to print the array of strings in descending order
                void sort_Descending(char des[10][26]) {
                        printf("\nThe strings in Descending Order\n");

                        for (i = 9; i > -1; i--) {

                                printf("%s\n", des[i]);

                        }
                }
                printf("\nEnter A or D for ascending or descending order only \n");
                //This is the function that takes only either A or D as input and calls functions sort_Ascending, sort_Descending or itself to print the strings accordingly
                void letter() {

                        scanf("%s",
                                let);
                        if (strlen(let) != 1) {
                                printf("String too long please enter A or D only ");
                                letter();
                        } else if ((let [0] != 'A') && (let [0] != 'D')) {
                                printf("Enter only A or D");
                                letter(); //calls the function letter if the value is not either A or D
                        } else if (let [0] == 'A') {
                                sort_Ascending(str); // calls the function to sort strings in ascending order if the value is A.
                        } else if (let [0] == 'D') {
                                sort_Descending(str); // calls the function to sort the strings in descending order if the value is D.
                        }

                }
                letter();
                //Finally we print the strings with the lowest and highest ASCII values
                printf("The string with lowest ascii value is %s", str[0]);
                printf("The string with highest ascii value is %s", str[9]);
        }
