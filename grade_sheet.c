/*
 * gradeSheet.c
 *
 *  Created on: Dec 19, 2017
 *      Author: Reham
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include "grade_sheet.h"
#include "mtm_ex3.h"
#define MIN_COURSE_ID   1
#define MAX_COURSE_ID   999999
#define MIN_STUDENT_ID  1
#define MAX_STUDENT_ID  999999999
#define MIN_GRADE  0
#define MAX_GRADE  100

struct gradeSheet_t{
	int course_id;
	int semester_id;
	int student_id;
	char* points;
	int grade;
};

/*************************** static functions deceleration ********************/
/**
 * stringDuplicate: copies the string (str)
 * @param: string to be copied;
 * @return: the new copy,NULL if memory allocation failed.
*/
static char* stringDuplicate(const char* str);

/**
 * checks if  points parameter is in the legal format
 * @param points- points to be checked
 * @return- false if points is not in one of the following format:
 *  x   , x.0 , x.5 (x is just a symbol for positive number)
 *	in otherwise returns true.
 */
static bool isPoinstLegal (char* points);

/**
 * the function assumes that the parameter point is not NULL and valid
 * valid point:
 * 1)string with characters between 0 and 9
 * 2)string with characters between 0 and 9 except the last two characters
 * which are '.0' or '.5'
 * @param points-string to be transformed to integer
 * @return the numerical value of parameter points*2
 */
static int convertPointsX2ToInteger(char *points);
/********************** static functions implementation **********************/
static char* stringDuplicate(const char* str){
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}

static bool isPoinstLegal(char* point){
	if(point!= NULL){
		char* ptr=point;
		int counter=0;
		while (*ptr!='\0' && *ptr !='.') {
			if (*ptr > '9'|| *ptr < '0' ) {
			   return false;
			}
			counter++;
			ptr++;
		}
		if (counter!=0){
			if(*ptr== '.'){
				ptr++;
				if  ((*ptr=='5' || *ptr=='0' )&& *(++ptr)=='\0' ){
						return true;
				}
				return false;
			}
			return true;
		}
		return false;
	}
	return false;
}

static int convertPointsX2ToInteger(char *points){
    assert(points!=NULL);
    char *ptr=points;
    int number=0;
    while (*ptr !='\0' && *ptr !='.') {
        number*=10;
        number+=*ptr-'0';

        ptr++;
    }
    number*=2;
    if (*ptr=='.' && *(++ptr)=='5'){
        number++;
    }
    return number;
}
/*****************************************************************************/
GradeSheetResult createGradeSheet(int course_id,int semester_id,
		int student_id,char* points,int grade,GradeSheet* grade_sheet){
	if(course_id<MIN_COURSE_ID || course_id>MAX_COURSE_ID||
			semester_id<=0 || grade<MIN_GRADE || grade>MAX_GRADE ||
			student_id<MIN_STUDENT_ID||student_id>MAX_STUDENT_ID||
			!isPoinstLegal(points) || grade_sheet==NULL){
		return GRADE_SHEET_INVALID_PARAMETERS;
	}
	*grade_sheet=malloc(sizeof(**grade_sheet));
	if(!*grade_sheet){
		return GRADE_SHEET_OUT_OF_MEMORY;
	}
	(*grade_sheet)->points=stringDuplicate(points);
	if((*grade_sheet)->points == NULL){
		removeGradeSheet(*grade_sheet);
		return GRADE_SHEET_OUT_OF_MEMORY;
	}
	(*grade_sheet)->course_id=course_id;
	(*grade_sheet)->grade=grade;
	(*grade_sheet)->semester_id=semester_id;
	(*grade_sheet)->student_id=student_id;
	return GRADE_SHEET_SUCCESS;
}

GradeSheet CopyGradeSheet(GradeSheet grade_sheet){
	assert(grade_sheet!= NULL);
	GradeSheet new_copy=NULL;
	createGradeSheet(grade_sheet->course_id,
			grade_sheet->semester_id,grade_sheet->student_id,
			grade_sheet->points,grade_sheet->grade,&new_copy);
	return new_copy;
}

void removeGradeSheet(GradeSheet grade_sheet){
	if(grade_sheet != NULL){
		free(grade_sheet->points);
	}
	free(grade_sheet);
}

int gradeSheetGetStudentId(GradeSheet grade_sheet){
	assert(grade_sheet!= NULL);
	return grade_sheet->student_id;
}

int gradeSheetGetCourseId(GradeSheet grade_sheet){
	assert(grade_sheet!= NULL);
	return grade_sheet->course_id;
}

int gradeSheetGetSemesterId(GradeSheet grade_sheet){
    assert(grade_sheet!= NULL);
    return grade_sheet->semester_id;
}

int gradeSheetGetCoursePointsX2(GradeSheet grade_sheet){
    assert(grade_sheet!=NULL && grade_sheet->points!=NULL &&
    		isPoinstLegal(grade_sheet->points));
    return convertPointsX2ToInteger(grade_sheet->points);
}

int gradeSheetGetCourseGrade(GradeSheet grade_sheet){
	assert(grade_sheet != NULL);
	return grade_sheet->grade;
}

GradeSheetResult gradeSheetUpdateGrade(GradeSheet grade_sheet, int new_grade){
	assert(grade_sheet!= NULL);
	if(new_grade<MIN_GRADE || new_grade>MAX_GRADE){
		return GRADE_SHEET_INVALID_PARAMETERS;
	}
	grade_sheet->grade=new_grade;
	return GRADE_SHEET_SUCCESS;
}

void gradeSheetPrintInfo (FILE* output_channel,GradeSheet grade_sheet){
	assert(grade_sheet!= NULL && output_channel!=NULL);
	int course_id=grade_sheet->course_id;
	int points_x2= convertPointsX2ToInteger(grade_sheet->points);
	int grade=grade_sheet->grade;
	mtmPrintGradeInfo(output_channel,course_id,points_x2,grade);
}
