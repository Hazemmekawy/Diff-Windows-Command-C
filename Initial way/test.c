#include<stdio.h>
#include<string.h>


////////////////////////////
#define TEST			3
////////////////////////////

//TEST 1 RESULTS
/*
file 1:					file 2:
-----------------------------------                       
Ubuntu                  Kubuntu
Arch Linux              Ubuntu
Debian                  Debian
CentOS                  Arch Linux
Fedora                  Centos
.						Fedora

//////////////////////////////////////////////////

--- file1	2019-11-25 21:00:26.422426523 +0100
+++ file2	2019-11-25 21:00:36.342231668 +0100
@@ -1,6 +1,7 @@
+Kubuntu
 Ubuntu
-Arch Linux
 Debian
-CentOS
+Arch Linux
+Centos
 Fedora


//TEST 2 RESULTS

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




//TEST 3 RESULTS

file 1:					file 2:
-----------------------------------                       
Hazem Mekawy            Bteee5a
Dexter Fawzy        	Hazem Mekawy
Peter george           	Dexter Fawzy
Manga Alfons            Peter grge
.                       Manga Alf

//////////////////////////////////////////////////
--- file1       2020-09-15 20:22:36.973631702 +0000
+++ file2       2020-09-15 20:23:35.458843451 +0000
@@ -1,4 +1,5 @@
+Bteee5a
 Hazem Mekawy
 Dexter Fawzy
-Peter george
-Manga Alfons
+Peter grge
+Manga Alf




//TEST 4 RESULTS

file 1:				file 2:
-------------------------------                       
a            		a
b        			d
c           	

//////////////////////////////////////////////////
--- file1       2020-09-15 20:56:07.732880835 +0000
+++ file2       2020-09-15 20:56:26.378543177 +0000
@@ -1,3 +1,2 @@
 a
-b
-c
+d



//TEST 5 RESULTS
file 1:															file 2:
----------------												-------------------
The Way that can be told of is not the eternal Way;		|		The Nameless is the origin of Heaven and Earth;
The name that can be named is not the eternal name.     |       The named is the mother of all things.
The Nameless is the origin of Heaven and Earth;         |       
The Named is the mother of all things.                  |       Therefore let there always be non-being,
Therefore let there always be non-being,                |         so we may see their subtlety,
  so we may see their subtlety,                         |       And let there always be being,
And let there always be being,                          |         so we may see their outcome.
  so we may see their outcome.                          |       The two are the same,
The two are the same,                                   |       But after they are produced,
But after they are produced,                            |         they have different names.
  they have different names.                            |       They both may be called deep and profound.
.                                                       |       Deeper and more profound,
.                                                       |       The door of all subtleties!

--- lao	2002-02-21 23:30:39.942229878 -0800
+++ tzu	2002-02-21 23:30:50.442260588 -0800
@@ -1,7 +1,6 @@
-The Way that can be told of is not the eternal Way;
-The name that can be named is not the eternal name.
 The Nameless is the origin of Heaven and Earth;
-The Named is the mother of all things.
+The named is the mother of all things.
+
 Therefore let there always be non-being,
   so we may see their subtlety,
 And let there always be being,
@@ -9,3 +8,6 @@
 The two are the same,
 But after they are produced,
   they have different names.
+They both may be called deep and profound.
+Deeper and more profound,
+The door of all subtleties!



//TEST 6 RESULTS
file 1:															file 2:
----------------												-------------------
Here i got on the journey for the first time,					Here i got on the journey for the first time,
to be with the people i                                         Sag me name.
Love and adore.                                                 to be with the people i
Long time no see.                                               My name is Heisenberg
 .                                                              Love and adore.
 .                                                              Long time no see.

--- file1       2020-09-16 19:49:26.983075091 +0000
+++ file2       2020-09-16 19:48:39.287082017 +0000
@@ -1,4 +1,6 @@
 Here i got on the journey for the first time,
+Sag me name.
 to be with the people i
+My name is Heisenberg
 Love and adore.
 Long time no see.


*/

int main(void)
{ 



#if TEST == 1
	#define SIZE1	5
	#define SIZE2	6
	char File1[SIZE1][20] = {"Ubuntu", "Arch Linux", "Debian", "CentOS", "Fedora"};
	char File2[SIZE2][20] = {"Kubuntu", "Ubuntu", "Debian", "Arch Linux", "Centos", "Fedora"};
#endif

#if TEST == 2
	#define SIZE1	4
	#define SIZE2	4
	char File1[SIZE1][20] = {"apples", "oranges", "kiwis", "carrots"};
	char File2[SIZE2][20] = {"apples", "kiwis", "carrots", "grapefruits"};
#endif

#if TEST == 3	
	
	#define SIZE1	4
	#define SIZE2	5
	char File1[SIZE1][20] = {"Hazem Mekawy", "Dexter Fawzy", "Peter george", "Manga Alfons"};
	char File2[SIZE2][20] = {"Bteee5a", "Hazem Mekawy", "Dexter Fawzy", "Peter grge", "Manga Alf"};
#endif


#if TEST == 4	
	
	#define SIZE1	3
	#define SIZE2	2
	char File1[SIZE1][20] = {"a", "b", "c"};
	char File2[SIZE2][20] = {"a", "d"};
#endif


#if TEST == 5	
	
	#define SIZE1	4
	#define SIZE2	4
	char File1[SIZE1][20] = {"cat", "mv", "comm", "cp"};
	char File2[SIZE2][20] = {"cat", "cp", "diff", "comm"};
#endif




#if TEST == 6	
	#define SIZE1	11
	#define SIZE2	13
	char File1[SIZE1][100] = {"The Way that can be told of is not the eternal Way;"
	, "The name that can be named is not the eternal name."
	, "The Nameless is the origin of Heaven and Earth;"
	, "The Named is the mother of all things."
	, "Therefore let there always be non-being,"
	, "  so we may see their subtlety,"
	, "And let there always be being,"
	, "  so we may see their outcome."
	, "The two are the same,"
	, "But after they are produced,"
	, "  they have different names."};

	char File2[SIZE2][100] = {"The Nameless is the origin of Heaven and Earth;"
	,"The named is the mother of all things."
	,""
	,"Therefore let there always be non-being,"
	,"  so we may see their subtlety,"
	,"And let there always be being,"
	,"  so we may see their outcome."
	,"The two are the same,"
	,"But after they are produced,"
	,"  they have different names."
	,"They both may be called deep and profound."
	,"Deeper and more profound,"
	,"The door of all subtleties!"};
	
#endif	
	
	int F1_index=0, F2_index=0;
	int broke = 0;
	while(F2_index < SIZE2 && broke<20) //Maximum looping for the reference file
	{
		
		if(strcmp(File2[F2_index], File1[F1_index]) == 0) //They're the same
		{
			printf("  %s", File2[F2_index]);
			printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
			F1_index++;
			F2_index++;
		}
		else // They're not the same
		{
			if(SIZE2>SIZE1 && F1_index == 0) // case of additions before the first line
			{
				printf("+ %s", File2[F2_index]);
				printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
				F2_index++;
			}
			else if(SIZE2<SIZE1 && F1_index == 0)
			{
				printf("- %s", File1[F1_index]);
				printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
				F1_index++;
			}
			else if (F2_index == SIZE2-1 && F1_index < SIZE1) // case of additions in the middle SIZE1>2
			{
					printf("- %s", File1[F1_index]);
					printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
					F1_index++;
			}
			else if (F1_index == SIZE1-1 && F2_index < SIZE2) // case of additions in the middle SIZE1<2
			{
				if(strcmp(File1[SIZE1-1], File2[SIZE2-1]) == 0)
				{
					while(F2_index<SIZE2-1)
					{
						printf("+ %s", File2[F2_index]);
						printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
						F2_index++;
					}	
				}
				else
				{
					printf("- %s", File1[F1_index]);
					printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
					F1_index++;
				}
			}
			
			else if (F1_index == SIZE1 && F2_index < SIZE2) // case of additions after the last line
			{
				printf("+ %s", File2[F2_index]);
				printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
				F2_index++;
			}
			else // case of removing lines
			{
				printf("- %s", File1[F1_index]);
				printf("\t\tF1: %d F1: %d\n", F1_index, F2_index);
				F1_index++;
			}
		}
		broke++;
	}
	printf("IT BROKE AFTER %d\n", broke);
	return 0;
}












// void printFormat(void)
// {
	// int Iterator = 0;
	
	// /* Printing the files modification time data */
	// printf("*** file1\t\t %s\n", ctime(&File1.filestat.st_mtime));
	// printf("--- file2\t\t %s\n", ctime(&File2.filestat.st_mtime));
	// printf("***************\n");
	
	// /* Printring File1 Changes */
	// printf("*** 1,%d ****", File1.NumLines);
	
	// for(Iterator=0; Iterator<File1.NumLines; Iterator++)
	// {
		// if(File1.States[Iterator] == 1)//added
			// printf("+ ");
		// else if(File1.States[Iterator] == 2)//changed
			// printf("! ");
		// else if(File1.States[Iterator] == 3)//removed
			// printf("- ");
		// else
			// printf("  ");
		
		// printf("%s\n", File1.Lines[Iterator]);
	// }
	
	// /* Printing File2 Changes */
	// printf("--- 1,%d ----", File2.NumLines);
	// for(Iterator=0; Iterator<File2.NumLines; Iterator++)
	// {
		// if(File2.States[Iterator] == 1)//added
			// printf("+ ");
		// else if(File2.States[Iterator] == 2)//changed
			// printf("! ");
		// else if(File2.States[Iterator] == 3)//removed
			// printf("- ");
		// else
			// printf("  ");
		
		// printf("%s\n", File2.Lines[Iterator]);
	// }
// }


