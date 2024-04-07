#include <stdio.h>
#include <stdlib.h> //rand() func used for RNG
#include <time.h>   //time() func used for seeding
#include <argp.h>   //Command line argument parsing and handling
#include "funcs.h"  //Function declaration list

int ret_val, num, diff, num_ans, num_range_min, num_range_max, attempts;
char ans, *diffStr;
/* Additional strings to be attached to the help document. */
char doc[] = "Num-Guesser is a random number guessing game written in C.\vOnly one argument may be passed to the program at a time. If multiple arguments are passed, they will be ignored.";
/* Empty string that would contain command usage information. */
const char args_doc[] = "";
/* Program version string to be printed with -v or --version */
const char *argp_program_version = "Num-Guesser v1.21";
/* Email address to report bugs to. Attached to the bottom of the help document. */
const char *argp_program_bug_address = "<xatra169@gmail.com>";

/* A structure of possible arguments that can be passed to the program to allow for different outcomes. */
const struct argp_option options[] = {
    {"dont-show-num", 'n', 0, 0,
     "Prevents the program from displaying what the correct number was after a game over.\n"},
    {"show-exit-code", 's', 0, 0,
     "Prints the exit code when the program terminates.\n"},
    {0, 'r', 0, OPTION_ALIAS},
    {"difficulty", 'd', "1-3", 0,
     "Chooses the difficulty of the game, skipping the difficulty select phase. Accepts any value from 1-3 (inclusive).\n"},
    {"help", 'h', 0, 0,
     "Prints command syntax and command descriptions, then terminates.\n"},
    {"usage", 0, 0, OPTION_ALIAS},
    {"version", 'v', 0, 0,
     "Prints the version of the program, then terminates.\n"},
    {0}};

/* A structure of variables that can be modfied by arguments passed to the program. */
struct arguments
{
   /* Determines whether or not to show the correct number at the end of a game. */
   int showNum;
} arguments;

/* Parse command line arguments and execute statements based on the argument passed. */
error_t parse_opt(int key, char *arg, struct argp_state *state)
{
   /* A pointer to the arguments structure that allows variables contained within to be manipulated by parse_opt. */
   struct arguments *arguments = state->input;
   switch (key)
   {
   default:
      return ARGP_ERR_UNKNOWN;
      break;
   case 'd':
      if (atoi(arg) == 1)
         attempts = 10;
      else if (atoi(arg) == 2)
         attempts = 5;
      else if (atoi(arg) == 3)
         attempts = 1;
      exit(ret_val = rngSet());
      break;
   case 'h':
      argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
      exit(0);
      break;
   case 'v':
      fprintf(state->out_stream, "%s\n", argp_program_version);
      exit(0);
      break;
   case 'n':
      arguments->showNum = 0;
      if (attempts == 0.5)
         exit(ret_val);
      else
         exit(ret_val = diffChoose());
      break;
   case 'r':
   case 's':
      if (attempts == 0.5)
         fprintf(stdout, "Process exited with status code %d\n", ret_val);
      else
         fprintf(stdout, "Process exited with status code %d\n",
                 (ret_val = diffChoose()));
      exit(ret_val);
      break;
   }
}

/* A structure that contains the option declarations, parse function, command usage documentation, and additional help strings. */
struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char *argv[])
{
   arguments.showNum = 1;
   srand(time(NULL));
   argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &arguments);
   return diffChoose();
}

/* Returns a random unsigned value between min and max. */
unsigned int rng(unsigned int min, unsigned int max)
{
   return (rand() % ((max + 1) - min) + min);
}

/* Create the difficulty selection prompt, scan for answer, and repeat until answer is anything besides 'n'. */
int diffChoose()
{
   fprintf(stdout,
           "Choose a difficulty. \n(1) - Easy (10 attempts)\n(2) - Normal (5 attempts)\n(3) - Hard (1 attempt)\nSelection: ");
   scanf("%1d", &diff);
   switch (diff)
   {
   case 1:
      attempts = 10;
      diffStr = "Easy";
      break;
   default:
      attempts = 5;
      diffStr = "Normal";
      break;
   case 3:
      attempts = 1;
      diffStr = "Hard";
      break;
   }
   fprintf(stdout,
           "You selected %s. You will have %d attempt(s) to get the number correct.\n",
           diffStr, attempts);
   fprintf(stdout, "Is this correct? (y/n): ");
   scanf("%1s", &ans);
   if (ans == 'n')
   {
      while (ans != 'y')
         diffChoose();
   }
   return rngSet();
}

/* Prepare random values for next function */
int rngSet()
{
   num = rng(1, 100);
   num_range_min = num - rng(1, 10);
   num_range_max = num + rng(1, 10);
   game();
   return 0;
}

/* Scan for player input and check if given answer is equal to num. */
void game()
{
   if (attemptChk())
   {
      fprintf(stdout,
              "\nNumber is between %d and %d. (Attempts left: %d)\n Answer: ",
              num_range_min, num_range_max, attempts);
      scanf("%3d", &num_ans);
      if (num_ans == num)
         fprintf(stdout, "Correct!\n\a");
      else
      {
         while (num_ans != num && attempts > 0)
         {
            attempts--;
            game();
         }
      }
   }
   else
   {
      fprintf(stdout, "\nYou ran out of attempts!\n\a");
      if (arguments.showNum == 1)
         fprintf(stdout, "The correct number was %d.\n", num);
   }
}

/* Check if attempt count is greater than 0. */
int attemptChk()
{
   if (attempts <= 0)
      return 0;
   else
      return 1;
}
