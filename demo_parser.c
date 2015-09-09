/* Author: Dan Wilder (sentient)
 *
 */

#include <stdlib.h>   // abort() , NULL
#include <stdio.h>    // printf() , fprintf()
#include <ctype.h>    // isprint()
#include <unistd.h>   // getopt() , opterr , optint , optarg , optopt

void DisplayUsage(char *);

/*****************************************************************************
 *    main()                                                                 *
 *****************************************************************************/

int main(int argc, char **argv) {

  int c; 
  int index;
  
  // Presence of option character will set correspond flag
  char aflag = 0;
  char tflag = 0;
  char *tvalue = NULL;

  opterr = 0; // prevents the default error messages of getopt() 
  
  while ((c = getopt (argc, argv, "abt:")) != -1) { // Set option flags 
    switch (c) {

    case 'a':
      aflag = 1;
      break;

    case 't':
      tflag = 1;
      tvalue = optarg;
      break;

    case '?': // getopt detected invalid option character or missing target
      if (optopt == 't')
        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint (optopt))
        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

      return 1; // Error!

    default:
      abort (); // Critical Error!
    }
  }

  if (argc == 1)
    DisplayUsage(argv[0]);

  /********Shift Execution based on option flags********/

  else {
    printf ("aflag = %d, tflag = %d, tvalue = %s\n",
             aflag, tflag, tvalue);  
  }

  /*****************************************************/


  /********* Process non-option argv arguments *********/

  for (index = optind; index < argc; index++) { // Process non-option arguments
    printf ("Non-option argument \"%s\" @ argv[%d]\n", argv[index], index);
  }

  /*****************************************************/

  return 0;
}

/*****************************************************************************
 *    DisplayUsage()                                                         *
 *****************************************************************************/

void DisplayUsage(char *programName) {
  printf("\nSYNOPSIS\n    %s [-at] [t-target]\n", programName);      
  printf("\nDESCRIPTION\n    Demo command line parser\n\n");   
}
