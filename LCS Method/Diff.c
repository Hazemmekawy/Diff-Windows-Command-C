/**
 *  @file Diff.c
 *  @author Hazem Mekawy
 *  @brief Source file for the implementation of File Parsing and Longest Common Subsequence Algorithm.
 *  @date 15/09/2020
 *  @version 1.0
 */


/*********************** FILE INCLUSIONS ***********************/
#include "Diff.h"

/*********************** TYPE DEFINITIONS **********************/
typedef struct
{
	FILE *fp; 				/* File decriptor */
	int NumLines; 			/* Number of lines */
	char **Lines; 			/* Array to save the lines of the file */
	struct stat filestat; 	/* Structure that holds the file time data */
}fileInfo_t;


/**************** STATIC FUNCTIONS DECLARATIONS ***************/
static int countLines(FILE *fp);
static int max (int a, int b);
static void readLines(fileInfo_t *file);
static void freeData(fileInfo_t *file);
static void LCS_fillTable(void);
static void findDifference(char **s1, char **s2, int x,  int y);

/********************** GLOBAL VARIABLES *********************/
static fileInfo_t File1;			/* Info of file 1 */
static fileInfo_t File2;			/* Info of file 2 */
static char buffer[BUFSZ] = "";		/* buffer to hold the value of lines being read from file */
static int LCS[1024][1024];			/* Longest Common Subsequence Matrix */


/***************** APPLICATION INTERFACES ********************/
/**
 *  @name  initFiles
 *  @brief Intialization and Parsing of Files.
 *  
 *  @param [in] file1_name: Name of File1.
 *  @param [in] file2_name: Name of File2.
 *  
 *  @return State of initialization.
 */
int initFiles(char *file1_name, char *file2_name)
{	
	/* Creating file1 descriptor */
	File1.fp = fopen(file1_name, "r");
	
	/* validate file1 open for reading */
	if(!File1.fp) 
	{  
		/* Display an error message in case of failure to open file1 */
        fprintf (stderr, "error: Failed to open file1.\n");
		printf("\nUsage: diff [option] file1 file2\n");
		printf("\nOptions:\n\t-u \t: Unified Format.\n\t--help\t: A brief about the program.\n");
        return 1;
    }
	
	/* Creating file2 descriptor */
	File2.fp = fopen(file2_name, "r");
	
	/* validate file2 open for reading */
	if(!File2.fp) 
	{  
		/* Display an error message in case of failure to open file2 */
		fprintf (stderr, "error: Failed to open file2.\n");
		printf("\nUsage: diff [option] file1 file2\n");
		printf("\nOptions:\n\t-u \t: Unified Format.\n\t--help\t: A brief about the program.\n");
		return 1;
    }
	
	/* Reading the Time Data details of the file */
	stat(file1_name,&File1.filestat);
	stat(file2_name,&File2.filestat);
	
	/* Counting the lines in the files */
	File1.NumLines = countLines(File1.fp);
	File2.NumLines = countLines(File2.fp);
	
	/* rewind the file pointer to the beginning of the file */
	fseek(File1.fp, 0, SEEK_SET);
	fseek(File2.fp, 0, SEEK_SET);
	
	/* Reading the files */
	readLines(&File1);
	readLines(&File2);
	
	/* Printing the file contents */
	printf("\n\nFile1:\tNumOfLines: %d\n", File1.NumLines);
	for(int j=0; j<File1.NumLines; j++)
		printf(">>%s\n",File1.Lines[j]);
	printf("\n\n");
	
	printf("-----------------\nFile2:\tNumOfLines: %d\n", File2.NumLines);
	for(int j=0; j<File2.NumLines; j++)
		printf(">>%s\n",File2.Lines[j]);
	
	printf("\n\n\n");
	
	/* Displaying File modification time */
	printf("+++ file1\t%s", ctime(&File1.filestat.st_mtime));
	printf("--- file2\t%s", ctime(&File2.filestat.st_mtime));
	return 0;
}

/**
 *  @name  diff
 *  @brief Implementation of diff linux command.
 *  
 *  @return void
 */
void diff(void)
{
	/* Filling the LCS matrix */
	LCS_fillTable();
	
	/* Finding the differences between the two files */
	findDifference(File1.Lines, File2.Lines, File1.NumLines, File2.NumLines);
}

/**
 *  @name  closeFiles
 *  @brief Close the files and free the dynamically allocated data.
 *  
 *  @return void
 */
void closeFiles(void)
{
	/* Free the dynamically allocated data */
	freeData(&File1);
	freeData(&File2);
	
	/* Closing the files */
	fclose(File1.fp);
	fclose(File2.fp);
}


/********************** STATIC FUNCTIONS **********************/

/**
 *  @name  readLines
 *  @brief Reading the lines of the file.
 *  
 *  @param [in] file: Pointer to the structure of the file being read.
 *  
 *  @return void
 */
static void readLines(fileInfo_t *file)
{
	size_t n = 1;
	int index=0;
	
	/* Dynamic allocation of the text */
	file->Lines = (char**)malloc((file->NumLines) * sizeof(char*));
	
	/* Read each line in file */
	while(fgets (buffer, BUFSZ, file->fp))  
	{       
        size_t len = strlen(buffer);           /* get buffer length */
        if (len && buffer[len-1] == '\n')      /* check last char is '\n' */
            buffer[--len] = 0;                 /* overwrite with null-character */
        else 								/* line too long or non-POSIX file end, handle as required */
		{   
            //printf("%d\tline[%2zu] : %s\n", len, n, buffer);
			file->Lines[index] = (char *)malloc((strlen(buffer)+1) * sizeof(char));
			strcpy(file->Lines[index], buffer);
			index++;
            continue;
        }   /* output line (or "empty" if line was empty) */
        //printf ("%d\tline[%2zu] : %s\n",len,  n++, len ? buffer : "empty");
		
		/* Dynamic allocation of the line string */
		file->Lines[index] = (char *)malloc((strlen(buffer)+1) * sizeof(char));
		strcpy(file->Lines[index], buffer);
		index++;
    }
}

/**
 *  @name  freeData
 *  @brief Free the dynamically allocated data of the files.
 *  
 *  @param [in] file: Structure of the file being freed.
 *  
 *  @return void
 */
static void freeData(fileInfo_t *file)
{
	for(int i=0; i<file->NumLines; i++)
	{
		free(file->Lines[i]);
	}
	free(file->Lines);
}

/**
 *  @name  LCS_fillTable
 *  @brief Filling the LCS Table according to the Longest Common Subsequence Algorithm.
 *  
 *  @return void
 */
static void LCS_fillTable(void)
{
    for(int i = 0; i <= File1.NumLines; i++)
	{
        for(int j = 0; j <= File2.NumLines; j++)
		{
            /* Starting row and column are filled with 0 */
            if (i == 0 || j == 0)
                LCS[i][j] = 0;

            /* if current character of string1 and string2 matches 
             * then LCS index == 1 + diagonally previous value */
            else if (strcmp(File1.Lines[i-1], File2.Lines[j-1]) == 0)
                LCS[i][j] = LCS[i-1][j-1] + 1;
            
            /* if not matches, then it will be max of above or previous index*/
            else
                LCS[i][j] = max(LCS[i-1][j],LCS[i][j-1]);
        }
    }
	
	// /* Displaying LCS table */
    // for(int i = 0; i <= File1.NumLines; i++) {
        // printf("[ ");
        // for(int j = 0; j <= File2.NumLines; j++ ) {
            // printf("%d ",LCS[i][j]);
        // }
        // printf("]\n");
    // }	
}

/**
 *  @name  findDifference
 *  @brief Find the difference between two files based on the LCS Matrix.
 *  
 *  @param [in] s1: Array of strings of file1.
 *  @param [in] s2: Array of strings of file2.
 *  @param [in] x:  Size of array of file1.
 *  @param [in] y:  Size of array of file2.
 *  
 *  @return void
 */
static void findDifference(char **s1, char **s2, int x,  int y)
{
    /* if last string of s1 == s2 */
    if( x > 0 && y > 0 && strcmp(s1[x-1], s2[y-1]) == 0)
    {
        findDifference(s1, s2, x-1, y-1);
        printf(" %s\n",s1[x-1]);
    }

    /* if char of *s2 not in *s1 */
    else if(y > 0 && (x == 0 || LCS[x][y-1] >= LCS[x-1][y]))
    {
        findDifference(s1, s2, x, y-1);
        printf(" +%s\n",s2[y-1]);
    }

    /* if char of *s1 not in *s2 */
    else if(x > 0 && (y == 0 || LCS[x][y-10] < LCS[x-1][y]))
    {
        findDifference(s1, s2, x-1, y);
        printf(" -%s\n",s1[x-1]);
    }
}

/**
 *  @name  max
 *  @brief getting the max between 2 values.
 *  
 *  @param [in] a: First value.
 *  @param [in] b: Second value.
 *  
 *  @return max value
 */
static int max(int a, int b) 
{
    return (a > b) ? a : b;
}

/**
 *  @name  countLines
 *  @brief Counting the lines of the file.
 *  
 *  @param [in] fp: File descriptor.
 *  
 *  @return count of the lines.
 */
static int countLines(FILE *fp)
{
	int count = 0;
	char ch = 0;
	while (fgets(buffer, BUFSZ, fp))
		count++;
	
	return count;
}



