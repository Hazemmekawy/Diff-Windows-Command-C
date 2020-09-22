#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <time.h>


//////TYPEDEFS
typedef struct
{
	FILE *fp; // file decriptor
	int NumLines; //Number of lines
	int *States; // Array to save the state of each line
	char **Lines; // Array to save the lines of the file
	struct stat filestat; //structure that holds the file time data
	
}fileInfo_t;

/* Implementation of Unified Format */

fileInfo_t File1;
fileInfo_t File2;

int countLines(FILE *fptr)
{
	int count = 0;
	char ch = 0;
	while(ch != EOF)
    {
        //Count whenever new line is encountered
        if (ch == '\n')
        {
            count++;
        }
        //take next character from file.
        ch = getc(fptr);
    }
	return count+1;
}

char isFileValid(char *filename)
{
  struct stat buffer;   
  return (stat (filename, &buffer) == 0);
}
void freeData(fileInfo_t *file)
{
	for(int i=0; i<file->NumLines; i++)
	{
		free(file->Lines[i]);
	}
	free(file->Lines);
}

void readLines(fileInfo_t *file)
{
	char temp[1024]={0};
	file->Lines = (char**)malloc(file->NumLines * sizeof(char*));
	if(file->Lines)
	{
		for(int i=0; i<file->NumLines; i++)
		{
			//Note we can dynamically allocate the arrays by getting the strlen and strcpy
			fscanf(file->fp,"%[^\n]\n",temp);
			file->Lines[i] = (char *)malloc(strlen(temp) * sizeof(char));
			strcpy(file->Lines[i], temp);
			memset(temp, 0, 1024);
		}		
	}
	else
	{
		printf("Dynamic allocation is Unavialabe\n");
	}
}

void initFiles(char *file1_name, char *file2_name)
{
	//Init Structure
	
	//Creating file descriptors
	File1.fp = fopen(file1_name, "r");
	File2.fp = fopen(file2_name, "r");	
	
	//Updating time
	stat(file1_name,&File1.filestat);
	stat(file2_name,&File2.filestat);
	
	//Counting the lines in the file
	File1.NumLines = countLines(File1.fp);
	File2.NumLines = countLines(File2.fp);
	
	//rewind the file pointer to the beginning of the file
	fseek(File1.fp, 0, SEEK_SET);
	fseek(File2.fp, 0, SEEK_SET);
	
	readLines(&File1);
	readLines(&File2);
}

void closeFiles(void)
{
	freeData(&File1);
	freeData(&File2);
	fclose(File1.fp);
	fclose(File2.fp);
}

int main(int argc,char *argv[])
{
	int F1_index=0, F2_index=0;
	int broke = 0;
	
	if(strcmp(argv[1], "-u") == 0)
	{
		if(isFileValid(argv[3]))
		{
			if(isFileValid(argv[3]))
			{
				initFiles(argv[2], argv[3]);	
				
				printf("File1:\tNumOfLines: %d\n", File1.NumLines);
				for(int j=0; j<File1.NumLines; j++)
					printf(">>%s\n",File1.Lines[j]);
				
				
				printf("-----------------\nFile2:\tNumOfLines: %d\n", File2.NumLines);
				for(int j=0; j<File2.NumLines; j++)
					printf(">>%s\n",File2.Lines[j]);
				printf("\n\n");
				
				printf("Changes Log:\n\n");
				//printf("\t\t\tF1: %d F2: %d\n", F1_index, F2_index);
				while(F2_index < File2.NumLines) //Maximum looping for the reference file
				{
					if(F1_index!=File1.NumLines && F2_index!=File2.NumLines && strcmp(File2.Lines[F2_index], File1.Lines[F1_index]) == 0) //They're the same
					{
						printf("  %s\n", File2.Lines[F2_index]);
						F1_index++;
						F2_index++;
						//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
					}
					else // They're not the same
					{
						if(File2.NumLines>File1.NumLines && F1_index == 0) // case of additions before the first line
						{
							printf("+ %s\n", File2.Lines[F2_index]);
							F2_index++;
							//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
						}
						else if(File2.NumLines<File1.NumLines && F1_index == 0)
						{
							printf("- %s\n", File1.Lines[F1_index]);
							F1_index++;
							//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
						}
						else if (F2_index == File2.NumLines-1 && F1_index < File1.NumLines) // case of additions in the middle SIZE1>2
						{
							printf("- %s\n", File1.Lines[F1_index]);
							F1_index++;
							//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
						}
						else if (F1_index == File1.NumLines-1 && F2_index < File2.NumLines) // case of additions in the middle SIZE1<2
						{
							if(strcmp(File1.Lines[File1.NumLines-1], File2.Lines[File2.NumLines-1]) == 0)
							{
								while(F2_index<File2.NumLines-1)
								{
									printf("+ %s\n", File2.Lines[F2_index]);
									F2_index++;
									//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
								}	
							}
							else
							{
								printf("- %s\n", File1.Lines[F1_index]);
								F1_index++;
								//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
							}
						}
						else if (F1_index == File1.NumLines && F2_index < File2.NumLines) // case of additions after the last line
						{
							printf("+ %s\n", File2.Lines[F2_index]);
							F2_index++;
							//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
						}
						else // case of removing lines
						{
							printf("- %s\n", File1.Lines[F1_index]);
							F1_index++;
							//printf("\t\tF1: %d F2: %d\n", F1_index, F2_index);
						}
					}
					//broke++;
					//printf("BROKE_VAL: %d\n", broke);
				}
				//printf("IT BROKE AFTER %d\n", broke);
			}
			else
			{
				printf("Error, Unable to validate file2\n");
			}	
		}
		else
		{
			printf("Error, Unable to validate file1\n");
		}
	}
	else if(strcmp(argv[1], "--help") == 0)
	{
		printf("Help! : This command outputs the difference between two files.\n");
	}
	else
	{
		printf("Usage: diff [option] file1 file2\n");
		printf("options:\n\t-u \t: Unified Format\n\t--help\t: A brief about the program.\n");
	}
	closeFiles();
	return 0;
}


///////////***********************
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <time.h>
/*
file 1:					file 2:
-----------------------------------                       
apples                  apples
oranges              	kiwis
kiwis                  	carrots
carrots                 grapefruits
//////////////////////////////////////////////////
--- file1.txt   2014-08-21 17:58:29.764656635 -0400
+++ file2.txt   2014-08-21 17:58:50.768989841 -0400
@@ -1,4 +1,4 @@
 apples
-oranges
 kiwis
 carrots
+grapefruits
*/

int** LCS = NULL;

typedef struct
{
	FILE *fp; // file decriptor
	int NumLines; //Number of lines
	char **Lines; // Array to save the lines of the file
	struct stat filestat; //structure that holds the file time data
	
}fileInfo_t;

fileInfo_t File1;
fileInfo_t File2;

////////////////////////////////////////////////////////

int countLines(FILE *fptr)
{
	int count = 0;
	char ch = 0;
	while(ch != EOF)
    {
        //Count whenever new line is encountered
        if (ch == '\n')
        {
            count++;
        }
        //take next character from file.
        ch = getc(fptr);
    }
	return count+1;
}

void readLines(fileInfo_t *file)
{
	char temp[1024]={0};
	file->Lines = (char**)malloc(file->NumLines * sizeof(char*));
	if(file->Lines)
	{
		for(int i=0; i<file->NumLines; i++)
		{
			//Note we can dynamically allocate the arrays by getting the strlen and strcpy
			fscanf(file->fp,"%[^\n]\n",temp);
			file->Lines[i] = (char *)malloc(strlen(temp) * sizeof(char));
			strcpy(file->Lines[i], temp);
			memset(temp, 0, 1024);
		}		
	}
	else
	{
		printf("Dynamic allocation is Unavialabe\n");
	}
}

char isFileValid(char *filename)
{
  struct stat buffer;   
  return (stat (filename, &buffer) == 0);
}

void initFiles(char *file1_name, char *file2_name)
{
	//Init Structure
	
	//Creating file descriptors
	File1.fp = fopen(file1_name, "r");
	File2.fp = fopen(file2_name, "r");	
	
	//Updating time
	stat(file1_name,&File1.filestat);
	stat(file2_name,&File2.filestat);
	
	//Counting the lines in the file
	File1.NumLines = countLines(File1.fp);
	File2.NumLines = countLines(File2.fp);
	
	//rewind the file pointer to the beginning of the file
	fseek(File1.fp, 0, SEEK_SET);
	fseek(File2.fp, 0, SEEK_SET);
	
	readLines(&File1);
	readLines(&File2);
	
	printf("File1:\tNumOfLines: %d\n", File1.NumLines);
	for(int j=0; j<File1.NumLines; j++)
		printf(">>%s\n",File1.Lines[j]);
	
	
	printf("-----------------\nFile2:\tNumOfLines: %d\n", File2.NumLines);
	for(int j=0; j<File2.NumLines; j++)
		printf(">>%s\n",File2.Lines[j]);
	printf("\n\n");
	
	
}

void freeData(fileInfo_t *file)
{
	for(int i=0; i<file->NumLines; i++)
	{
		free(file->Lines[i]);
	}
	free(file->Lines);
}

void closeFiles(void)
{
	freeData(&File1);
	freeData(&File2);
	fclose(File1.fp);
	fclose(File2.fp);
}




////////////////////////////////////////////////////////

char max (int a, int b) {
    return (a > b) ? a : b;
}

//x,y refre to the matrix sizes
void LCS_fillTable(void)
{
	/* Dynamic Allocation for the LCS Table */
	LCS = (int**)malloc((File1.NumLines + 1) * sizeof(int*));
	
	for(int i=0; i <= File1.NumLines; i++)
		LCS[i] = (int*)malloc((File2.NumLines + 1) * sizeof(int));
	
    for (int i =  0; i <= File1.NumLines; i++)
	{
        for (int j = 0; j <= File2.NumLines; j++)
		{
            /* Starting row and col are filled with 0 */
            if (i == 0 || j == 0)
                LCS[i][j] = 0;

            /* if current character of s1 and s2 matches 
             * then LCS index == 1 + diagonally previous value */
            else if (strcmp(File1.Lines[i-1], File2.Lines[j-1]) == 0)
                LCS[i][j] = LCS[i-1][j-1] + 1;
            
            /* if not matches, then it will be max of above or previous index*/
            else
                LCS[i][j] = max(LCS[i-1][j],LCS[i][j-1]);
        }		
    }
	
	/* displaying lcs table */
    for (int i = 0; i <= File1.NumLines; i++) {
        printf("[ ");
        for (int j = 0; j <= File2.NumLines; j++ ) {
            printf("%d ",LCS[i][j]);
        }
        printf("]\n");
    }	
}


/* diff to display the difference */
void diff(char s1[][20], char s2[][20], int x,  int y)
{
    /* if last char of s1 == s2 */
    if ( x > 0 && y > 0 && strcmp(s1[x-1], s2[y-1]) == 0)
    {
        diff(s1, s2, x-1, y-1);
        printf(" %s\n",s1[x-1]);
    }

    /* if char of *s2 not in *s1 */
    else if (y > 0 && (x == 0 || LCS[x][y-1] >= LCS[x-1][y]))
    {
        diff(s1, s2, x, y-1);
        printf(" +%s\n",s2[y-1]);
    }

    /* if char of *s1 not in *s2 */
    else if (x > 0 && (y == 0 || LCS[x][y-10] < LCS[x-1][y]))
    {
        diff(s1, s2, x-1, y);
        printf(" -%s\n",s1[x-1]);
    }
}

int main(int argc, char **argv)
{
	if(strcmp(argv[1], "-u") == 0)
	{
		if(isFileValid(argv[3]))
		{
			if(isFileValid(argv[3]))
			{
				initFiles(argv[2], argv[3]);	
			
				LCS_fillTable();
			

			}
			else
			{
				printf("Error, Unable to validate file2\n");
			}	
		}
		else
		{
			printf("Error, Unable to validate file1\n");
		}
	}
	else if(strcmp(argv[1], "--help") == 0)
	{
		printf("Help! : This command outputs the difference between two files.\n");
	}
	else
	{
		printf("Usage: diff [option] file1 file2\n");
		printf("options:\n\t-u \t: Unified Format\n\t--help\t: A brief about the program.\n");
	}
	closeFiles();
	
	return 0;
}
