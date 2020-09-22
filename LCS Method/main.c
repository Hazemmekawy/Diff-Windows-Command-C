/**
 *  @file main.c
 *  @author Hazem Mekawy
 *  @brief Implementation of "diff" Linux command.
 *  @date 15/09/2020
 *  @version 1.0
 */


/*********************** FILE INCLUSIONS ***********************/
#include "Diff.h"

/**
 *  @name  main
 *  @brief Program main entry.
 *  
 *  @param [in] argc: Number of arguments passed to the command.
 *  @param [in] argv: Values of the arguments passed to the command.
 *  
 *  @return Program's state.
 */
int main(int argc, char *argv[])
{
	/* In case of wrong option entry, usage message is displayed */
	if(argv[1] == NULL)
	{
		printf("\nUsage: diff [option] file1 file2\n");
		printf("\nOptions:\n\t-u \t: Unified Format\n\t--help\t: A brief about the program.\n");
		return 1;
	}
	/* Checking wether the option is unified format */
	else if(strcmp(argv[1], "-u") == 0)
	{
		/* Initialization and Parsing of Fikes */
		if(initFiles(argv[2], argv[3]))	
			return 1; /* In case of error in opening files */
			
		/* Execution of the diff command */
		diff();
		
		/* Closing the files */
		closeFiles();
	}
	/* Checking wether the option is help */
	else if(strcmp(argv[1], "--help") == 0) 
	{
		printf("\nHelp! : This command outputs the differences between two files.\n");
	}
	/* In case of wrong option entry, usage message is displayed */
	else
	{
		printf("Usage: diff [option] file1 file2\n");
		printf("Options:\n\t-u \t: Unified Format.\n\t--help\t: A brief about the program.\n");
	}

	
	return 0;
}


