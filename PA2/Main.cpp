#include "SortingAnalysis.h"

/* 

Presorted operations:
  Obviously bubble sort is the most efficient here, as it only has to loop through the vector once.
  Insertion is second, as it only has to loop through the vector once, but it has to compare each element to the previous one.
  Selection is the least efficient, as it has to loop through the vector twice, and compare each element to every other element.
  Nothing too surprising here, but it does show that algorithm efficiency is not always dependent on the size of the array alone

Reverse/Random operations:
  Bubble sort now is the least efficient, as it has to continually swap elements, and it has to loop through the vector multiple times.
  Insertion sort is now the most efficient, it finds an element out of position at each iteration.
  Selection is now in the middle, it still has to loop n^2 times

Presorted Time:
  Almost no difference between these three, since the number of operations are all relatively close to each other

Reverse/Random Time:
  Insertion is the slowest here, which was surprising since bubble has significantly more operations
  This is likely because of constant memory reallocation, which I could improve on a later iteration of an insertion sort later on.
  The other two are very close in comparison, with selection being slightly faster than bubble.

  Overall, these algorithms each have their strengths and weaknesses, and it is important to know which one to use in which situation.
  None of theme are super efficient, but they are useful enough for small datasets and are simple to implement. 

*/

int main()
{
  run();
  return 0;
}