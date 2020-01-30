

#ifndef GRADESHEET_H_
#define GRADESHEET_H_



typedef enum {
	GRADE_SHEET_OUT_OF_MEMORY,
	GRADE_SHEET_INVALID_PARAMETERS,
	GRADE_SHEET_SUCCESS,
}GradeSheetResult;

typedef struct gradeSheet_t* GradeSheet;
/**
 * Creates a new Grade Sheet
 * @param: course_id - the course id for which the grade sheet is related
 * @param: semester_id - the semester id for which the grade sheet is related
 * @param: student_id - student id,must be in range [1,999999999]
 * @param: points - the number of course points(string format)
 * @param: grade -grade should be in range [0,100]
 * @param: grade_sheet- pointer to the gradeSheet that will be created
 * @return:
 * GRADE_SHEET_INVALID_PARAMETERS  if student ,points or grade_sheet are NULL,
 * or if the course id  and  student id are out of range 1-10^6 and  1-10^9
 * respectively or  semester id<=0,  GRADE_SHEET_OUT_OF_MEMORY if memory
 * allocation failed,GRADE_SHEET_SUCCESS otherwise.
 */
GradeSheetResult createGradeSheet(int course_id, int semester_id,
		int student_id, char* points,int grade,GradeSheet* grade_sheet);

/* grade_sheet must not be NULL
 *  copies dynamically an existing grade_sheet.
 * @param: grade_sheet - grade_sheet to be copied
 * @return:a copy of the grade_sheet,NULL if memory allocation failed.
 */
GradeSheet CopyGradeSheet(GradeSheet grade_sheet);

/*
 *remove a grade sheet with deallocating inner allocations.
 *@param: grade sheet to be removed
 */
void removeGradeSheet(GradeSheet grade_sheet);

/**
 * grade_sheet must not be NULL
 * @param: grade sheet
 * @return: the semester id of the grade sheet
 */
int gradeSheetGetStudentId(GradeSheet grade_sheet);

/**
 * grade_sheet must not be NULL
 * @param: grade sheet
 * @return: the course id of the grade sheet
 */
int gradeSheetGetCourseId(GradeSheet grade_sheet);

/**
 * grade_sheet must not be NULL
 * @param: grade sheet
 * @return:the course points of the grade sheet parameter(numerical value)
 *         multiplied by 2.
 */
int gradeSheetGetCoursePointsX2(GradeSheet grade_sheet);

/**
 * grade_sheet must not be NULL
 * @param: grade sheet
 * @return: the grade of the grade sheet
 */
int gradeSheetGetCourseGrade(GradeSheet grade_sheet);

/**
 * grade_sheet must not be NULL
 * @param: grade sheet
 * @return: semester id of the grade sheet
 */
int gradeSheetGetSemesterId(GradeSheet grade_sheet);

/**
 * grade_sheet must not be NULL.
 * update the grade of the grade sheet parameter.
 * @param: grade_sheet - the grade sheet for which the grade will be updated
 * @param: new_grade - the new grade which will be inserted
 * GRADE_SHEET_INVALID_PARAMETERS if new_grade is out of range 0<=grade<=100
 * GRADE_SHEET_SUCCESS otherwise.
 */
GradeSheetResult gradeSheetUpdateGrade(GradeSheet grade_sheet, int new_grade);

/**
 * grade_sheet and output_channel must not be NULL
 * Prints grade sheet details.
 * @param: output_channel - File descriptor for the output channel.
 * @param: grade sheet to be printed
 */
void gradeSheetPrintInfo (FILE* output_channel,GradeSheet grade_sheet);



#endif /* GRADESHEET_H_ */
