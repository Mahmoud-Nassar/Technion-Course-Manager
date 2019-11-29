//
// Created by mahmood on 12/29/2017.
//
#ifndef INC_19_12_2017_COURSEMANAGER_H
#define INC_19_12_2017_COURSEMANAGER_H
#include <stdio.h>
#include "student.h"
typedef struct courseManager_t* CourseManager;

typedef enum {
    COURSE_MANAGER_OUT_OF_MEMORY,
    COURSE_MANAGER_STUDENT_NOT_LOGGED_IN,
    COURSE_MANAGER_ALREADY_LOGGED_IN,
    COURSE_MANAGER_STUDENT_DOES_NOT_EXIST,
    COURSE_MANAGER_STUDENT_ALREADY_EXISTS,
    COURSE_MANAGER_NOT_FRIEND,
    COURSE_MANAGER_ALREADY_FRIEND,
    COURSE_MANAGER_NOT_REQUESTED,
    COURSE_MANAGER_ALREADY_REQUESTED,
    COURSE_MANAGER_COURSE_DOES_NOT_EXIST,
    COURSE_MANAGER_INVALID_PARAMETER,
    COURSE_MANAGER_SUCCESS,
}CourseManagerResult;

/** assumes that courseManager_ptr is not NULL
 * Creates a new course manager , with no students and grades
 * @param courseManager_ptr- output parameter for the new created course
 * manager
 * @return COURSE_MANAGER_OUT_OF_MEMORY-in case of bad allocation, otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult createCourseManager(CourseManager* courseManager_ptr);

/**
 * assumes that courseManager is not NULL
 * adds a new student to the system
 * @param courseManager- the system to add the new student to
 * @param student_id- id of the new student
 * @param first_name- first name of the new student
 * @param last_name- last name of the new student
 * @return COURSE_MANAGER_INVALID_PARAMETER -if student id less than 1  or
 * bigger than 999999999
 * COURSE_MANAGER_STUDENT_ALREADY_EXISTS-if there is already student in the
 * system with id equals to parameter student_id
 * COURSE_MANAGER_OUT_OF_MEMORY - in cas of bad allocation otherwise,
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerAddStudent(CourseManager courseManager,
                                            int student_id,char *first_name,
                                            char *last_name);

/** assumes that courseManager is not NULL
 * removes the student with student id from the system
 * @param courseManager- system to remove student from
 * @param student_id- id of the student to remove
 * @return COURSE_MANAGER_INVALID_PARAMETER -if student id less than 1 or
 * bigger than 999999999
 * COURSE_MANAGER_STUDENT_DOES_NOT_EXIST-if no student with id equals
 * to student_id was found, otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerRemoveStudent(CourseManager courseManager,
                                                int student_id);

/** assumes that courseManager is not NULL
 * connects the student with id equal to student_id to the system
 * @param courseManager- system to connect student to
 * @param student_id- id of the student to connect
 * @return COURSE_MANAGER_ALREADY_LOGGED_IN- if student with same id as
 * student_id was logged in
 * COURSE_MANAGER_STUDENT_STUDENT_NOT_EXIST-if no student with id equals
 * to student_id was found, otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerStudentLogIn(CourseManager courseManager
                                            ,int student_id);
/** assumes that courseManager is not NULL
 * log out the connected student from the system
 * @param courseManager- system to log out the student from
 * @return COURSE_MANAGER_NOT_LOGGED_IN- if no student was logged in
 * COURSE_MANAGER_STUDENT_STUDENT_NOT_EXIST-if no student with id equals otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerStudentLogOut(CourseManager courseManager);

/** assumes that courseManager is not NULL
 * sends a friend request from the connected student to the student with id
 * same as receiver_id
 * @param courseManager-system which contains the two student described above
 * @param receiver_id- id of student to send friend request to
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_STUDENT_DOES_NOT_EXIST-if no student with id equals
 * to receiver_id was found
 * COURSE_MANAGER_ALREADY_FRIEND- if the student with receiver_id and the
 * connected are already friends, or the connected student`s id equals to
 * receiver_id
 * COURSE_MANAGER_ALREADY_REQUESTED- if the connected student has sent a
 * request to student with id same as receiver_id, and the request has not
 * been handled yet, otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerSendFriendRequest(CourseManager courseManager
                                                    ,int receiver_id);

/** assumes that courseManager is not NULL
 * handles the request sent from student with sender_id to the connected
 * student
 * @param courseManager-system which contains the two student described above
 * @param sender_id- id of the student who sent the request that should be
 * handle
 * @param action- the action that should be done to the request described above
 * valid action : is a on of the stings :
 *              1)"accept"
 *              2)"reject"
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_STUDENT_DOES_NOT_EXIST-if no student with id equals
 * to sender_id was found
 * COURSE_MANAGER_ALREADY_FRIEND- if the student with sender_id and the
 * connected are already friends, or the connected student`s id equals to
 * sender_id
 * COURSE_MANAGER_NOT_REQUESTED- if there is no request from student with
 * sender_id and the connected student that has not been handled yet
 * COURSE_MANAGER_INVALID_PARAMETER- if the action was not valid, otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerHandelFriendRequest(CourseManager courseManager
                                                 ,int sender_id,char* action);

/** assumes that CourseManager is not NULL
 * unfriend the connected student and the student with id same as student2_id
 * @param courseManager- Course manager that contains the two students
 * @param student2_id-id indicates which student should be unfriend
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_STUDENT_DOES_NOT_EXIST - if no student with id same as
 * student2_id was found in the system
 * COURSE_MANAGER_NOT_FRIEND - if the two student already not friends , or
 * the connected student`s id equals to student2_id ,otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerStudentUnfriend(CourseManager courseManager,
                                                 int student2_id);

/** assumes that CourseManager is not NULL
 * adds a new grade to the sheet of the connected student
 * in case of success the grade is added as the last grade of giving semester
 * @param courseManager- the system which the student is connected to
 * @param semester-semester of the added grade
 * @param course_id-id of the course Which the student got the grade in
 * @param points-points of the course Which the student got the grade in
 * @param grade-grade that the student got
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_OUT_OF_MEMORY in case of bad allocation
 * COURSE_MANAGER_INVALID_PARAMETER if semester or course id was a negative number ,
 * course id bigger than 1000000 ,grade not in (0-100) range,or invalid
 * points parameter
 * valid points parameter:
 * 1)string with characters between 0 and 9
 * 2)string with characters between 0 and 9 except the last two characters
 * which is '.0' or '.5'
 * otherwise COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerAddGradeSheet(CourseManager courseManager,
                                               int semester,int course_id,
                                               char* points,int grade);

/** assumes that CourseManager is not NULL
 * removes the last grade the connected student had in course with id equals to
 * course_id
 * @param courseManager- the system which the student is connected to
 * @param course_id-id of the course which the student got the grade in
 * @param semester-number of semester the student got the grade in
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_NULL_PARAMETER if student or points was NULL
 * COURSE_MANAGER_COURSE_DOES_NOT_EXIST if no grade in the
 * specified semester and course was found otherwise
 * otherwise COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerRemoveGradeSheet(CourseManager courseManager,
                                                  int course_id,int semester);

/** assumes that CourseManager is not NULL
 * for specified course,searches for last semester connected student ever had a
 * grade in and updates it
 * @param courseManager- the system which the student is connected to
 * @param course_id-id of the course which the student got the grade in
 * @return  COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_COURSE_DOES_NOT_EXIST if no grade in the
 * specified semester and course was found otherwise
 * COURSE_MANAGER_INVALID_PARAMETERS if new_grade not in the range (0-100),
 * otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerUpdateGradeSheet(CourseManager courseManager,
                                                 int course_id,int new_grade);

/** assumes that CourseManager is not NULL
 * prints data and grades sheet of connected student .
 * grades are sorted by number of semester , grades in the same semester
 * sorted  by the time they were added to the sheet
 * after printing all the grades of semester , semester summary is printed
 * after printing all the grades of student , grades sheet summary is printed
 * @param courseManager- the system which the student is connected to
 * @param output-the output chanel (for the printing)
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_INVALID_PARAMETER- if output was null,otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerReportFull(CourseManager courseManager, FILE
*output);

/** assumes that CourseManager is not NULL
 * prints valid grades of connected student
 * valid grade :
 *      for sports-course : the last grade student had in a certain and semester
 *      for other courses : the last grade student had in a certain course
 * printing order : the grades are ordered by course id , two course with the
 * same id are order by number of semester
 * @param courseManager- the system which the student is connected to
 * @param output-the output chanel (for the printing)
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_INVALID_PARAMETER- if output was null,otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerReportClean(CourseManager courseManager,FILE
*output);

/** assumes that CourseManager is not NULL
 * prints the highest grades of connected student
 * number of grades printed is lower than or equal to amount
 * if student does`nt have grades nothing is printed
 * order of printing :
 *      higher grades appears first , if two grades were equal , grade with
 *      lower semester number appears first , if semester numbers were
 *      also equal , the grade with lower course id appears first
 * @param courseManager- the system which the student is connected to
 * @param output-the output chanel (for the printing)
 * @param amount-max number of names to print
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in or output was NULL
 * COURSE_MANAGER_INVALID_PARAMETERS if amount < 0 ,otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerReportBest(CourseManager courseManager,
                                      FILE *output,int amonut);

/** assumes that CourseManager is not NULL
 * prints the lowest grades of connected student
 * number of grades printed is lower than or equal to amount
 * if student does`nt have grades nothing is printed
 * order of printing :
 *      lower grades appears first , if two grades were equal , grade with
 *      lower semester number appears first , if semester numbers were
 *      also equal , the grade with lower course id appears first
 * @param courseManager- the system which the student is connected to
 * @param output- the output chanel (for the printing)
 * @param amount-max number of names to print
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_NULL_PARAMETER if output is NULL ,otherwise
 * COURSE_MANAGER_INVALID_PARAMETERS if amount < 0 ,otherwise
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerReportWorst(CourseManager courseManager
        ,FILE *output,int amount);

/**
 * prints (using mtmPrintStudentName function) the names of the students (in
 * friends of the connected student) that has the highest grades in the
 * course with id equals to parameter courser_id, number of names printed is
 * lower than or equal to amount
 * the order of printing: student with higher grade appears
 * first ,if 2 students has the same grade , the student with the lower id
 * number appears first.
 * @param courseManager- the system which the student is connected to
 * @param course_id-id of the course related to the search
 * @param amount- the number of names to be printed, if the number of
 * @param output- the output chanel (for the printing)
 * the students that had a grade in such course was lower , prints only the
 * relevant names .if no student was found with a grade in the course nothing
 * is printed.
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * COURSE_MANAGER_INVALID_PARAMETERS if amount < 0 ,otherwise
 * if output is NULL
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerPrintReference(CourseManager courseManager,int
        course_id,int amount,FILE *output);


/** assumes that CourseManager is not NULL
 * the function does the request described in parameter request for the
 * connected student
 * @param courseManager- the system which the student is connected to
 * @param course_id- id of the course related to the request
 * @param request- request of the student it can be one of the following stings:
 * "cancel_course", "register_course", "remove_course"
 * @param output- output chanel in case printing a message is needed
 * @return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN - if no student was
 * logged in
 * 	COURSE_MANAGER_COURSE_DOES_NOT_EXIST if request was "remove_course" , but no
 * 	grade found in specified course
 * COURSE_MANAGER_INVALID_PARAMETER if request was not expected format otherwise
 * if request is NULL
 * COURSE_MANAGER_SUCCESS
 */
CourseManagerResult courseManagerFacultyRequest(CourseManager courseManager,
                                    int course_id, char *request,FILE* output);

/**
 * deallocates a CourseManager
 * @param courseManager- CourseManager to deallocate
 */
void destroyCourseManager(CourseManager courseManager);

#endif //INC_19_12_2017_COURSEMANAGER_H
