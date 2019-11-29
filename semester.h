#ifndef SEMESTER_H_
#define SEMESTER_H_
#include <stdbool.h>
#include <stdio.h>
#include "grade_sheet.h"
#include "set.h"

typedef struct semester_t* Semester;

typedef enum {
	SEMESTER_OUT_OF_MEMORY,
	SEMESTER_INVALID_PARAMETERS,
	SEMESTER_COURSE_DOES_NOT_EXIST,
	SEMESTER_SUCCESS,
} SemesterResult;

/**
 * Creates a new semester
 * @param: semester_id - the semester id for which to be created
 * @param: pointer to the semester that will be created
 * SEMESTER_INVALID_PARAMETERS if the semester id is <=0
 * SEMESTER_OUT_OF_MEMORY if memory allocation failed,SEMESTER_SUCCESS
 * otherwise.
 */
SemesterResult createSemester(int semester_id, Semester* semester);

/* semester must not be NULL
 *  copies dynamically an existing semester.
 * @param: semester - semester to be copied
 * @return:a copy of the semester,NULL if memory allocation failed.
 */
Semester CopySemester(Semester semester);

/*
 *destroy a semester with deallocating inner allocations.
 *@param: semester to be removed
 */
void destroySemester(Semester semester);

/**
 * semester must not be NULL
 * searching a course  by it's id in the semester
 * @param: semester - to search for the course in it
 * @param: course_id - the course id to search
 * @return: true if the course id exists and false otherwise.
 */
bool semesterIsCourseIdExist(Semester semester ,int course_id);

/**
 * semester must not be NULL
 * Adds a new grade to the semester
 * @param: semester - the semester to which the grade will be added
 * @param: course_id - course id,should be in range [1,10^6]
 * @param: student_id -student id ,should be in range [1-10^9]
 * @param: points - the number of course points(should be not null and in the format
 *  format x x.0 x.5)
 * @param: grade -grade to be inserted ,should be in range [0-100]
 * * @return:SEMESTER_INVALID_PARAMETERS if the course id, student_id , grade
 *  or id are out of their range or points is not in the correct format
 * SEMESTER_OUT_OF_MEMORY if memory allocation failed,
 * SEMESTER_SUCCESS otherwise.
 */
SemesterResult semesterAddGrade(Semester semester, int course_id ,
		int student_id,char* points,int grade);

/**
 * semester must not be NULL
 * updates the grade of the course with the course id to the set of grades in
 * the semester
 * @param: semester - the semester to which the grade will be updated
 * @param: course_id - course id to which the grade will be updated,
 * should be in range [1,10^6]
 * @param: grade -the new grade to be inserted ,should be in range [0-100]
 * @return:SEMESTER_INVALID_PARAMETERS if the course id or grade are out of
 * their range .
 * SEMESTER_COURSE_DOSE_NOT_EXIST,if the course wasn't taken in the
 * semester
 * SEMESTER_SUCCESS otherwise.
 */
SemesterResult semesterUpdateGrade(Semester semester, int course_id ,
		int new_grade);

/**
 * semester must not be NULL
 * removes the last grade sheet of the course with the same id
 * that was added to the semester .
 * @param: semester - the semester which the grade  sheet will be deleted
 * from
 * @param: course_id - course id of the grade sheet that will be deletes
 * should be in range [1,10^6]
 * @return:SEMESTER_INVALID_PARAMETERS if the course id is out of  range
 * SEMESTER_COURSE_DOES_NOT_EXIST if no grade sheet to the relevant course id
 * in other word the course wasn't taken in the semester
 * SEMESTER_SUCCESS otherwise.
 */
SemesterResult semesterRemoveGrade(Semester semester, int course_id);

/**
 * semester must not be NULL
 * search the max grade that the student has got in the course that have
 * course id parameter.
 * @param: semester - the semester which to search the max grade
 * @param: course_id - course id to which the grade is relevant.
 * @return:NULL if there is no grade of the course, returns a new copy
 *  of grade otherwise.
 */
GradeSheet semesterGetCourseMaxGrade(Semester semester, int course_id);

/**
 * semester must not be NULL
 * search the valid grade sheet of course,the last grade  that was added
 *  to the semester.
 * @param: course_id - course id to which the grade  is relevant.
 * @return:NULL if there is no grade  of the course or course_id is invalid
 * or memory allocation failed, returns a new copy of grade otherwise.
 */
GradeSheet semesterGetCourseValidGradeSheet(Semester semester, int course_id);

/**
 * semester must not be NULL
 * @param: semester
 * @return: the id of the semester
 */
int semesterGetId(Semester semester);

/**
 * semester must not be NULL
 * calculate the number of total course points, multiplied by 2.
*  Courses taken multiple times are counted multiple times.
 * @param: semester - the semester to counts it's points
 * @return: the number of total course points, multiplied by 2.
 */
int semesterTotalPointsX2(Semester semester);

/**
 * semester must not be NULL
 * calculate the number of failed course points, multiplied by 2.
*  A failed course is a course with a grade lower than 55. Courses failed
*  multiple times are counted multiple times.
 * @param: semester - the semester to calculate it's failed points
 * @return:the number of failed course points, multiplied by 2.
 */
int semesterTotalFailed_points_x2(Semester semester);

/**
 * semester and output_channel must not be NULL
 * prints all the grades of the semester in the same order that they have been
 * added to semester.
 * @param: output_channel - File descriptor for the output channel.
 * @param: semester - the semester to print it's grades
 * @return:SEMESTER_OUT_OF_MEMORY if allocation failed .SEMESTER_SUCCESS
 * otherwise
 */
SemesterResult semesterPrintsAllGrades(FILE* output_channel,Semester
                                semester,Set course_id) ;
#endif /* SEMESTER_H_ */
