#ifndef STUDENT_H_
#define STUDENT_H_
#include <stdbool.h>
#include <stdio.h>
#include "grade_sheet.h"
#include "list.h"
typedef struct student_t* Student;

typedef enum {
	STUDENT_OUT_OF_MEMORY,
	STUDENT_INVALID_PARAMETERS,
	STUDENT_COURSE_DOES_NOT_EXIST,
	STUDENT_SUCCESS,
} StudentResult;

/**
 * allocates a new student
 * @param student -output parameter to return the new allocated student
 * @param student_id -student id for the new allocated student
 * @param first_name -first name for the new allocated student
 * @param last_name -last name for the new allocated student
 * @return STUDENT_OUT_OF_MEMORY in case of bad allocation
 * STUDENT_INVALID_PARAMETERS -if student id less than 1  or bigger
 * than 999999999
 * STUDENT_NULL_PARAMETER if first_name ,last_name or student was NULL
 * otherwise STUDENT_SUCCESS
 */
StudentResult createStudent(Student *student,int student_id,
                               char* first_name, char* last_name);
/**
* student must not be NULL
* Copies a student
* @param: student to be copied
* @return: a new copy of the student ,NULL in case of allocation failed
*/
Student copyStudent(Student student);

/**
 * Deallocates a student
 * @param student-student to be deallocated
 */
void destroyStudent(Student student);

/**  student must not be NULL
 * @param student- student to return his first name
 * @return- a copy of the first name of student
 */
char *studentGetFirstName(Student student);

/**   student must not be NULL
 * @param student- student to return his last name
 * @return- a copy of the last name of student
 */
char *studentGetLastName(Student student);

/** assumes that student is not NULL
 * @param student- student to return his id
 * @return- id of student
 */
int studentGetId(Student student);

/** assumes that student is not NULL
 * adds a new grade to the sheet of an existing student
 * in case of success the grade is added as the last grade of giving semester
 * @param student-student to add the new grade to
 * @param semester-semester of the added grade
 * @param course_id-id of the course Which the student got the grade in
 * @param points-points of the course Which the student got the grade in
 * @param grade-grade that the student got
 * @return STUDENT_OUT_OF_MEMORY in case of bad allocation
 * STUDENT_NULL_PARAMETER if student or points was NULL
 * STUDENT_INVALID_PARAMETERS if semester or course id was a negative number ,
 * course id bigger than 1000000 ,grade not in (0-100) range,or invalid
 * points parameter
 * valid points parameter:
 * 1)string with characters between 0 and 9
 * 2)string with characters between 0 and 9 except the last two characters
 * which is '.0' or '.5'
 * otherwise STUDENT_SUCCESS
 */
StudentResult studentAddGradeSheet(Student student,int semester,
                                   int course_id,char* points,int grade);

/** assumes that student is not NULL
 * removes the last grade the student had in course with id equals to course_id
 * @param student-student which his grade should be deleted
 * @param course_id-id of the course which the student got the grade in
 * @param semester-the number of the semester the student got the grade in
 * @return STUDENT_COURSE_DOES_NOT_EXIST if no grade in the
 * specified semester and course was found otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentRemoveGradeSheet(Student student,int course_id,
									  int semester);
/** assumes that student is not NULL
 * for specified course,searches for last semester student ever had a grade in
 * and updates it
 * @param student-student which his grade should be updated
 * @param course_id-id of the course which the student got the grade in
 * @return STUDENT_COURSE_DOES_NOT_EXIST if no grade in the
 * specified semester and course was found otherwise
 * STUDENT_INVALID_PARAMETERS if new_grade not in the range (0-100), otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentUpdateGradeSheet(Student student,int course_id,
									  int new_grade);

/** assumes that student is not NULL
 * prints data of student
 * @param student- student that his data should be printed
 * @param output-the output chanel (for the printing)
 * @return 	STUDENT_NULL_PARAMETER if output is NULL ,otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentPrintInfo(Student student,FILE *output);

/** assumes that student is not NULL
 * prints data and grades sheet of student for all the semesters .
 * grades are sorted by number of semester , grades in the same semester
 * sorted  by the order we added them to the sheet
 * after printing all the grades of semester , semester summary is printed
 * after printing all the grades of student , grades  summary is printed
 * @param student- the student with the grades to be printed
 * @param output_channel - File descriptor for the output channel.
 * @return 	STUDENT_NULL_PARAMETER if output is NULL ,otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentReportFull(Student student, FILE *output);


/** assumes that student is not NULL
 * prints valid grades of student
 * valid grade :
 *      for sports-course : the last grade student had in a certain semester
 *      for other courses : the last grade student had in a certain course
 * printing order : the grades are ordered by course id , two course with the
 * same id are order by number of semester
 * @param student- the student with the grades to be printed
 * @param output_channel - File descriptor for the output channel.
 * @return 	STUDENT_NULL_PARAMETER if output is NULL ,otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentReportClean(Student student,FILE *output);



/** assumes that student is not NULL
 * prints the highest grades of student
 * number of grades printed is lower than or equal to amount
 * if student does`nt have grades nothing is printed
 * order of printing :
 *      higher grades appears first , if two grades were equal , grade with
 *      lower semester number appears first , if semester numbers were
 *      also equal , the grade with lower course id appears first
 * @param student - student that his grades should be printed
 * @param output-the output chanel (for the printing)
 * @return 	STUDENT_NULL_PARAMETER if output is NULL ,
 * 	STUDENT_INVALID_PARAMETERS if amount < 0 ,otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentReportBest(Student student,int amount,FILE *output);

/** assumes that student is not NULL
 * prints the lowest grades of student
 * number of grades printed is lower than or equal to amount
 * if student does`nt have grades nothing is printed
 * order of printing :
 *      lower grades appears first , if two grades were equal , grade with
 *      lower semester number appears first , if semester numbers were
 *      also equal , the grade with lower course id appears first
 * @param student- student that his grades should be printed
 * @param output- the output chanel (for the printing)
 * @return 	STUDENT_NULL_PARAMETER if output is NULL ,otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentReportWorst(Student student,int amount,FILE *output);

/** assumes that student is not NULL
 * gets the highest grade student ever got in the specified course
 * @param student- student with grades to search in
 * @param course_id- id of course to get highest grade in
 * @param out -output parameter for returned Gradesheet ,if no grade sheet
 * was founded ,output points to NULL
 * @return 	STUDENT_NULL_PARAMETER if out is NULL ,otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentGetMaxGradeInCourse(Student student,int course_id,
                                         GradeSheet* out);

/** student ,request,output is must not be NULL
 * if the request is legal prints "rejected was request your " to the output
 * @param student- student that submitted the request
 * @param course_id- id of the course related to the request
 * @param request- request of the student it can be one of the following:
 * "cancel_course", "register_course", "remove_course"
* @param output_channel - File descriptor for the output channel.
 * 	STUDENT_COURSE_DOES_NOT_EXIST if request was "remove_course" , but no
 * 	grade found in specified course.
 * STUDENT_INVALID_PARAMETER if request was not expected format otherwise
 * STUDENT_SUCCESS
 */
StudentResult studentFacultyRequest(Student student,
									int course_id, char *request,FILE* output);


#endif /* STUDENT_H_ */
