/*
MPC-MPG
1st Laboratory: introduction to C++
made by: Michal Svento, Ondrej Mokry

this is
multiline comment

*/

// this is single line comment
// Including libraries into your script
#include <iostream>
// #include "mylocalheaderfile.h"		// use "" for local header
// files, <> for standard libraries

using namespace std; // calling just cout , not std::cout => cleaner code

int num_array[10] = {
    1, 3, 3, 4, 2,
    6, 7, 8, 9, 10}; // global variable, visible for every function in this file

/* Functions */

/*
Multiply function without pointer
input: 2 int; output: 1 int
*/

// Task 4
// TODO: Here starts your code

/*
Sum function
This function will sum up all values in array
input: 1 int array, return
*/

int sum(int number_array[10], int arr_size) {

  // Local variables, after function call vars no longer exist.
  int sum = 0; // sum init
  int i;       // if I want to use i outside for cycle

  // cout << "index\tnumber\tsum\n"; // Uncomment if u want to make table header

  // Task 5: "for" cycle throught array
  // You can use indexing using array[index]
  // TODO: Here starts your code
  for (i = 0; i < arr_size; i++) {
    sum += number_array[i];
  }

  return sum;
}

/* Functions using pointers */

/* function: multiply with pointer
input: 2 int, 1 pointer to int; output: void */
void multiply_ptr(int a, int b, int *c) {
  *c = a * b;
  // Void don't return nothing
}
/* Sum and mean

function: Just as ilustrative  */

void sum_and_mean(int *number_array, int *sum, float *mean, int arr_size) {
  int *ptr = number_array;
  int i;
  cout << "\nArr size " << arr_size << endl;
  cout << "index\tnumber\tsum\n";
  // for cycle over the whole array
  for (i = 0; i < arr_size; i++) {
    *sum += *(ptr + i);
    cout << i << "\t" << *(ptr + i) << "\t" << *sum << endl;
  }

  // pointer to mean variable / owerwriting the value at given address
  *mean = float(*sum) / i;
}

int multiply(int a, int b) { return a * b; }

int main() {

  /* Variables */
  // Both local
  int a = 1; // with initiazation
  int b;     // without initiazation - other types float, string, boolean;

  /*
          Math operations:
          +		-
          *		/
          % modulo operation

  */

  // Console print, function cout
  cout << "This is MPG lab #" << a << endl << "Task 1" << endl;
  /*
  Task 1
         Make one example using division operation
         Use vars a,b
         Initiaze ans
         Then print out on console
 */

  b = 4;
  float ans = 0;
  // Task 1
  // TODO: Here starts your code
  // Advice: always watch out the types
  ans = (float)a / b;

  cout << "Result should be 0.25 and it is: " << ans << "\n\n";

  // Global vars: see in the beggining, num_array

  /* Pointers */
  // make connection with address where the variable is stored.
  // one of multiple usage: variant of the multiply function, without return,
  // storing solution in previously defined variable

  // Using pointers in arrays
  int *ptr = num_array; // In ptr i have Address of first value
  // int * ptr = &num_array[0];  Equivalent to prev line

  *(ptr + 4) = 5; // using * i change value on adress ptr + 4
  // ptr = &num_array[4]; Again equivalent
  //*ptr = 5;

  cout << "Task 2" << endl;
  /*
          Task 2
                  Change second value in array to 2
                  Use pointer ptr or initialize new pointer
  */

  // Task 2
  // TODO: Here starts your code
  *(ptr + 1) = 2;

  cout << "Second number in array should be 2 and it is: " << num_array[1]
       << "\n \n";

  /*
  How to write conditions:
          ==	equal			!= different
          >	greater			< smaller
          >=  greather or eq  <= smaller or eq

          also boolean: and, or
  */

  cout << "Task 3" << endl;
  /*
          Task 3
                  Verify if result of multiplication is positive and devisible
     by 3 Use if else As a result use variable below Print statement on console
  */

  int val = 7;
  // Task 3
  // TODO:  Here starts your code
  if (val >= 0 && val % 3 == 0) {
    cout << "Result is positive and devisible by 3" << endl;
  } else {
    cout << "Result is not positive or devisible by 3" << endl;
  }
  /* Functions */
  // should be defined before main function, code is compiling from heading to
  // bottom

  cout << "\nTask 4" << endl;
  /*
          Task 4
                  Write function multiply in the beginning of this script
                  It should takes as argument 2 integers and returns one integer
  */

  int c = 0, d = 0;
  // uncomment this block if u are happy with your multiply function
  // Task is in the begging
  c = multiply(a, b = 3); // classic function with int return
  cout << "Product of " << a << " and " << b << " without ptr is " << c
       << ".\n"; // Print on console

  // Example of same function using pointers
  multiply_ptr(a, b, &d); // & operator returns the address of what follows
  cout << "Product of " << a << " and " << b << " with ptr is " << d
       << endl; // Print on console

  /* Conditions */
  if (c == d) {
    cout << "Functions are equivalent \n";
  } else {
    cout << "Bad programmer, it should be the same! \n";
  }

  cout << "\nTask 5" << endl;
  /*
          Task 5
                  Complete sum function with for cycle
                  Task is under task 4
  */

  int arr_size = sizeof(num_array) / sizeof(int); // Size of array
  // Sum function
  int sum_0 = sum(num_array, arr_size);
  cout << "Sum of array is: " << sum_0 << ".\n";
  // not so good for memory

  // Function
  // INPUT: array of numbers, address of mean - we assign number to this var;
  // OUTPUT: sum as normal return and mean as pointer value.
  // Uncomment below for equivalent solution using pointers
  float mean;
  int sum_1 = 0;
  sum_and_mean(num_array, &sum_1, &mean, arr_size);
  cout << "Sum of array 1 is: " << sum_1 << ". Mean of array is " << mean
       << ".\n";
  int sum_2 = sum(num_array, arr_size);
  cout << "Sum of array 2 is: " << sum_2 << ".\n";

  return 0;
}
