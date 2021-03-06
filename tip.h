/**
 * @file tip.h
 * @brief Header file for tip library.
 * @author Bipin Mathew
 * @version 
 * @date 2015-03-31
 */


#ifndef TIP_H
#define TIP_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

/**
 * \def TIP_INT
 * Used in type argument to tip and ftip functions to specify column of type int
 * */

/**
 * \def TIP_FLOAT
 * Used in type argument to tip and ftip functions to specify column of type double
 * */

/**
 * \def TIP_STR
 * Used in type argument to tip and ftip functions to specify column of type string
 * */

#define TIP_INT 0 
#define TIP_FLOAT 1
#define TIP_STR 2

/**
 * @brief A structure to hold columns of type int.
 */
typedef struct col_int{
    unsigned long numrows; /**< number of rows in column */
    long *d; /**< pointer to the actual data */
} col_int;

/**
 * @brief A structure to hold columns of type double.
 */
typedef struct col_double{
    unsigned long numrows; /**< number of rows in column */
    double *d; /**< pointer to the actual data */
} col_double;

/**
 * @brief A structure to hold columns of type str.
 */
typedef struct col_str{
    unsigned long _numrows; /**< internal count of number of rows in column */
    unsigned long numrows; /**<  actual number of rows in column */
    unsigned long _numbytes; /**< internal count of bytes in column */
    unsigned long numbytes; /**< total number of bytes loaded */
    unsigned long *offset; /**< array containing offsets to the end of each string. For example d[offset[i]-1] is the last character of the ith record for this column of strings.*/
    unsigned char *d; /**< pointer to the actual data */
} col_str;

int realloccols(int numcols,const int type[],void ***cols,int numrows);
int initcols(int numcols, const int type[], void ***cols,int numrows);

/**
 * @brief free memory associated with parsed column data.
 *
 * @param[in] numcols number of cols in parsed data.
 * @param[in] type[] type of columns can be TIP_INT, TIP_FLOAT, TIP_STRING
 * @param[in] cols array of pointers to allocated data.
 *
 * @return 0 in all cases.
 */
int freecols(int numcols,const int type[],void ***cols);
/**
 * @brief Parse character delimited file.
 *
 * @param[in] fp FILE pointer
 * @param[in] numcols number of cols in data
 * @param[in] type[] type of columns can be TIP_INT, TIP_FLOAT, TIP_STRING
 * @param[out] cols on return will point to an array of pointers of type col_int,
 * col_double or col_str depending on the types.
 * @param[in] delim character delimiter to use in parsing file.
 * @param[in] eordelim end of row delimiter.
 * @param[in] skiprecs number of rows to skip.
 *
 * @return number of records parsed.
 */
unsigned long ftip(FILE *fp,int numcols,const int type[], void ***cols, unsigned char delim, unsigned char eordelim,unsigned long skiprecs);

/**
 * @brief Parse character delimited memory area.
 *
 * @param[in] buff pointer to memory area to parse.
 * @param[in] buffsize number of bytes to parse.
 * @param[in] numcols number of cols in data
 * @param[in] type[] type of columns can be TIP_INT, TIP_FLOAT, TIP_STRING
 * @param[out] cols on return will point to an array of pointers of type col_int,
 * float_col or col_str depending on the types.
 * @param[in] delim character delimiter to use in parsing file.
 * @param[in] eordelim end of row delimiter.
 * @param[in] skiprecs number of rows to skip.
 *
 * @return number of records parsed.
 */
unsigned long tip(const char *buff,unsigned long buffsize,int numcols,const int type[], void ***cols, unsigned char delim, unsigned char eordelim,unsigned long skiprecs);

long fsize(FILE *fp);



#endif
