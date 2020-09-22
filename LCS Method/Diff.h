/**
 *  @file Diff.h
 *  @author Hazem Mekawy
 *  @brief Header file for the implementation of File Parsing and Longest Common Subsequence Algorithm.
 *  @date 15/09/2020
 *  @version 1.0
 */
 
 
#ifndef MYLCS_H
#define MYLCS_H


/*********************** FILE INCLUSIONS ***********************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <time.h>

/******************** MACRO DEFINITIONS ********************/
#define BUFSZ 	4096

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
int initFiles(char *file1_name, char *file2_name);

/**
 *  @name  diff
 *  @brief Implementation of diff linux command.
 *  
 *  @return void
 */
void diff(void);

/**
 *  @name  closeFiles
 *  @brief Close the files and free the dynamically allocated data.
 *  
 *  @return void
 */
void closeFiles(void);

#endif /* MYLCS_H */