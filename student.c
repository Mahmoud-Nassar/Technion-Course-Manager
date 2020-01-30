#include "student.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "semester.h"
#include "mtm_ex3.h"
#define MIN_GRADE  0
#define MAX_GRADE   100
#define MIN_STUDENT_ID  1
#define MAX_STUDENT_ID  999999999
#define MIN_COURSE_ID   1
#define MAX_COURSE_ID   999999
#define MAX_COURSE_SPORT_ID 399999
#define MIN_COURSE_SPORT_ID 390000


struct student_t {
    int student_id;
    char *first_name;
    char *last_name;
    Set courses_id;
    List semesters;
};

/**************************** static functions declaration ***************/

static bool isSemesterExist(Student student, int semester_id);
/**
 * assumes that all the parameters are not NULL
 * adds to list (valid_grades) the last grade that the student got in specific
 *  course
 * @param student- the student with the grades to be returned
 * @param semesters- semesters to search in
 * @param course- pointer to the id of course which its last grade should be
 * returned
 * @param valid_grades- list to add to , in case a grade was found matching
 * the requirements
 * @return 	STUDENT_OUT_OF_MEMORY in case of bad allocation, otherwise
 * STUDENT_SUCCESS
 */
static StudentResult studentGetAllValidGradesHelper(Student student ,List
            semesters,int*
            course,List valid_grades);

/** assumes that student is not NULL
 * returns a list contains all the valid grades of student ,NULL if the is
 * not any
 * valid grade :
 *      for sports-course : the last grade student had in a certain and semester
 *      for other courses : the last grade student had in a certain course
 * @param student- the student with the grades to be returned
 * @param out-the output parameter for the returned list
 * @return STUDENT_OUT_OF_MEMORY in case of bad allocation
 * STUDENT_NULL_PARAMETER if output is NULL, otherwise
 * STUDENT_SUCCESS
 */
static StudentResult studentGetAllValidGrades(Student student, List *out);

/**
 * compares two semesters by there id
 * @param semester1- first semester to compare
 * @param semester2- second semester to compare
 * @param sortkey- key for the comparing
 * @return number bigger than 1 if id of semester 1 is closer (to the value in
 * sort key) than id of semester 2 , number lower than 1 if id of semester 2 is
 * closer (to the value in sort key) than id of semester 1, 0 id the two id`s
 * are equal
 */
static int semesterCompareCondtion(ListElement semester1, ListElement semester2,
                                   ListSortKey sortkey);

/** function that copies the same string in variable str to copy
 * (with allocation) ,and returns a pointer
 * (char *) to the new string allocated by the function.
 * the function does not handel NULL parameter case.
 * returns NULL in case of bad allocation.
 */
static char *stringDuplicate(const char *str);

/** function for copying course id
 * the function creates a new course id by allocating
 * @param Course_id- course id to be copied
 * @return NULL if NULL was sent or allocation failed
 * new allocated course id in case of success
 */
static SetElement courseIdCopyFunction(SetElement course_id);

/**
 * deallocates course id
 * @param course_id- course id to be allocated
 */
static void courseIdDestroyFunction(SetElement course_id);

/** assumes that course_id1 and course_id2 are not NULL
 * function to compare two courses id
 * @param course_id1- first course id for comparing
 * @param course_id2- second course id for comparing
 * @return 1 if course_id1 > course_id2 , -1 if course_id2 > course_id1
 * 0 if course_id1 = course_id2
 */
static int courseIdCompareFunction(SetElement course_id1,
                                   SetElement course_id2);

/** function for copying semester
 * the function creates a new semester by allocating
 * @param semester- semester to be copied
 * @return NULL if NULL was sent or allocation failed
 * new allocated semester in case of success
 */
static ListElement semesterCopyFunction(ListElement semester);

/**
 * deallocates semester
 * @param semester- semester to be allocated
 */
static void semesterDestroyFunction(ListElement semester);

/** assumes that ALL the parameters are not NULL
 * allocates course id set and semesters list for student
 * @param student -student which his list and set should be allocated
 * @param compare_course_id_function- function compares two courses id
 * @param copy_semester_function- function copies semester
 * @param free_semester_function- function frees semester
 * @param copy_course_id_function- function copies course id
 * @param free_course_id_function-function frees course id
 * @return STUDENT_OUT_OF_MEMORY in case of bad allocation
 * STUDENT_SUCCESS otherwise
 */
static StudentResult allocateListAndSet(Student student,
                                        compareSetElements
                                        compare_course_id_function,
                                        CopyListElement copy_semester_function,
                                        freeSetElements free_semester_function,
                                        copySetElements copy_course_id_function,
                                        freeSetElements
                                        free_course_id_function);

/**
 * assumes that student is not NULL
 * if key=1
 *  * prints the highest grades of student
 * number of grades printed is lower than or equal to amount
 * if student does`nt have grades nothing is printed
 * order of printing :
 *      higher grades appears first , if two grades were equal , grade with
 *      lower semester number appears first , if semester numbers were
 *      also equal , the grade with lower course id appears first
 * if key=0
 * * prints the lowest grades of student
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
static StudentResult studentReport(Student student, int amount, FILE *output,
		CompareListElements compare);

/**
 * assumes that student is not NULL
 * sums total effective course points
 * and  total effective course grades (each grade is multiplied by the number
 * of course points, multiplied by 2)
 * @param student -student which his sums should be calculated
 * @param effective_points_x2_ptr- output parameter for effective points sum
 * @param effective_grade_sum_x2- output parameter for effective grades sum
 */
static StudentResult studentCalculateEffective(Student student,
                                               int *effective_points_x2_ptr,
                                               int *effective_grade_sum_x2_ptr);

/** function for copying grade sheet
 * the function creates a new grade sheet by allocating
 * @param grade_sheet- grade sheet to be copied
 * @return NULL if NULL was sent or allocation failed
 * new allocated grade sheet in case of success
 */
static ListElement studentCopyGradeSheet(ListElement grade_sheet);

/**
 * Deallocates a grade sheet
 * @param grade_sheet- grade sheet to be deallocated
 */
static void studentDestroyGradeSheet(ListElement grade_sheet);


/** assumes semesters are not NULL
 * @param semesters - list which it`s reversed copy should returned
 * @return a reversed copy (by allocation) of the semesters list
 */
static List semeterReverseList(List semesters);

/** assumes that all the parameters are not NULL
 * compares between to grade sheets
 * @param grade_sheet1- first grade sheet to be compared
 * @param grade_sheet2- second grade sheet to be compared
 * @return a positive value if semester id
 * of grade_sheet1 grater than semester id of grade_sheet2 ,negative value in
 * the opposite case if the two semester id`s also equal returns a positive
 * value if course id of grade_sheet1 grater than course id of grade_sheet2 ,
 * negative value in the opposite case .otherwise returns 0
 */
static int gradeSheetCompareCondtionHelper(ListElement grade_sheet1,
                                           ListElement grade_sheet2);

/** assumes that all the parameters are not NULL
 * compares between to grade sheets
 * @param grade_sheet1- first grade sheet to be compared
 * @param grade_sheet2- second grade sheet to be compared
 * @param sortkey- pointer to the value to calculate distance from
 * @return  a positive value if course id of grade_sheet1 grater than course
 * id of grade_sheet2 negative value in the opposite case ,if the two course
 * id`s was equal ,return a positive value if semester id
 * of grade_sheet1 grater than semester id of grade_sheet2 ,negative value in
 * the opposite case if the two semester id`s also equal returns 0.
 */
static int gradeSheetCleanCompareCondtion(ListElement grade_sheet1,
                                          ListElement grade_sheet2,
                                          ListSortKey sortkey);
/** assumes that all the parameters are not NULL
 * compares between to grade sheets
 * @param grade_sheet1- first grade sheet to be compared
 * @param grade_sheet2- second grade sheet to be compared
 * @param sortkey- pointer to the value to calculate distance from
 * @return positive value if the distance between grade of grade_sheet1 and
 *  sortkey  grater than the distance between grade of grade_sheet2 and sortkey,
 *  negative value in the opposite case, if the two grades are equal returns
 *  a positive value if semester id
 * of grade_sheet1 grater than semester id of grade_sheet2 ,negative value in
 * the opposite case if the two semester id`s also equal returns a positive
 * value if course id of grade_sheet1 grater than course id of grade_sheet2 ,
 * negative value in the opposite case .otherwise returns 0
 */
static int gradeSheetWorstCompareCondtion(ListElement grade_sheet1,
                                          ListElement grade_sheet2,
                                              ListSortKey sortkey);
/** assumes that all the parameters are not NULL
 * compares between two grade sheets
 * @param grade_sheet1- first grade sheet to be compared
 * @param grade_sheet2- second grade sheet to be compared
 * @param key- pointer to the value to calculate distance from
 * @return positive value if the distance between grade of grade_sheet2 and
 *  sort  grater than the distance between grade of grade_sheet1 and key,
 *  negative value in the opposite case, if the two grades are equal returns
 *  a positive value if semester id
 * of grade_sheet1 grater than semester id of grade_sheet2 ,negative value in
 * the opposite case if the two semester id`s also equal returns a positive
 * value if course id of grade_sheet1 grater than course id of grade_sheet2 ,
 * negative value in the opposite case .otherwise returns 0
 */
static int gradeSheetBestCompareCondtion(ListElement grade_sheet1,
                                         ListElement grade_sheet2,
                                         ListSortKey key);

/**
 * assumes that student is not NULL
 * updates the courses id set in student to contain only id`s of courses that
 * student has at least one grade in 0
 * @param student- student to update its courses id set
 */
static void studentUpdateCoursesIdSet(Student student);

/************************************************************************/
/**************************** static functions implementation ***********/
static bool isSemesterExist(Student student, int semester_id){
	assert(student !=NULL);
	  LIST_FOREACH(Semester, current, student->semesters) {
	        if (semesterGetId(current) == semester_id) {
	        	return true;
	        }
	  }
	  return false;
}

static StudentResult studentAddSemester(Student student, int semester_id){
	assert(student!=NULL);
	  Semester new_semester=NULL;
	   SemesterResult create_result=createSemester(semester_id, &new_semester);
	    		if (create_result==SEMESTER_INVALID_PARAMETERS){
	    			return STUDENT_INVALID_PARAMETERS;
	    		 }
	    		if (create_result==SEMESTER_OUT_OF_MEMORY){
	    			return STUDENT_OUT_OF_MEMORY;
	    		 }
	            listInsertLast(student->semesters, new_semester);
	            int sort_key = 0;
	            listSort(student->semesters, semesterCompareCondtion,&sort_key);
	            destroySemester(new_semester);
	            return STUDENT_SUCCESS;
}

static void  studentRemoveSemester(Student student, int semester_id){
	assert(student!=NULL);
	  LIST_FOREACH(Semester, current, student->semesters) {
	        if (semesterGetId(current) == semester_id) {
	        	 listRemoveCurrent(student->semesters);
	        }
	  }
}

static int semesterCompareCondtion(ListElement semester1, ListElement
semester2,ListSortKey key) {
    int id1 = (semesterGetId(semester1) - *(int *) key);
    int id2 = (semesterGetId(semester2) - *(int *) key);
    return id2 - id1;
}

static StudentResult studentGetAllValidGrades(Student student, List *out){
    assert(student != NULL);
    List semesters = NULL;
    List valid_grades = listCreate(studentCopyGradeSheet,
                                   studentDestroyGradeSheet);
    if (valid_grades == NULL) return STUDENT_OUT_OF_MEMORY;
    SET_FOREACH(int*, current_course, student->courses_id) {
        /*semesters = semeterReverseList
                (student->semesters);
        if (semesters == NULL) {
            listDestroy(valid_grades);
            return STUDENT_OUT_OF_MEMORY;
        }*/
        StudentResult studentResult=studentGetAllValidGradesHelper(student,
                                        student->semesters,current_course
                                        ,valid_grades);
        if (studentResult!=STUDENT_SUCCESS){
            listDestroy(valid_grades);
            return studentResult;
        }
        listDestroy(semesters);
    }
    *out = valid_grades;
    return STUDENT_SUCCESS;
}

static StudentResult studentGetAllValidGradesHelper(Student student ,List
                        semesters,int*
                        course,List valid_grades){
        assert(student!=NULL  && semesters!=NULL
               && course!=NULL && valid_grades!=NULL) ;
        LIST_FOREACH(Semester, current_semester, semesters) {
            GradeSheet gradeSheet = semesterGetCourseValidGradeSheet(
                    current_semester, *course);
            if (gradeSheet != NULL) {
                if (listInsertFirst(valid_grades, gradeSheet) ==
                    LIST_OUT_OF_MEMORY) {
                    listDestroy(valid_grades);
                    return STUDENT_OUT_OF_MEMORY;
                }
                listInsertAfterCurrent(valid_grades, gradeSheet);
                if (*course < MAX_COURSE_SPORT_ID &&
                    *course > MIN_COURSE_SPORT_ID) {
                    removeGradeSheet(gradeSheet);
                    continue;
                }
                removeGradeSheet(gradeSheet);
                break;
            }
            removeGradeSheet(gradeSheet);
        }
    return STUDENT_SUCCESS;
}

static int gradeSheetCleanCompareCondtion(ListElement grade_sheet1,
                                        ListElement grade_sheet2,
                                        ListSortKey sortkey) {
    assert(grade_sheet1 != NULL && grade_sheet2 != NULL && sortkey != NULL);
    int course_id1 = gradeSheetGetCourseId(grade_sheet1) - *(int *) sortkey;
    int course_id2 = gradeSheetGetCourseId(grade_sheet2) - *(int *) sortkey;
    if (course_id1 != course_id2) {
        return course_id1 - course_id2;
    }
    if (gradeSheetGetSemesterId(grade_sheet1) <
        gradeSheetGetSemesterId(grade_sheet2))
        return -1;
    else if (gradeSheetGetSemesterId(grade_sheet1) >
             gradeSheetGetSemesterId(grade_sheet2))
        return 1;
    return 0;
}

static int gradeSheetCompareCondtionHelper(ListElement grade_sheet1,
                                         ListElement grade_sheet2){
    if (gradeSheetGetSemesterId(grade_sheet1) <
        gradeSheetGetSemesterId(grade_sheet2))
        return -1;
    else if (gradeSheetGetSemesterId(grade_sheet1) >
             gradeSheetGetSemesterId(grade_sheet2))
        return 1;
    if (gradeSheetGetCourseId(grade_sheet1) <
        gradeSheetGetCourseId(grade_sheet2))
        return -1;
    else if (gradeSheetGetCourseId(grade_sheet1) >
             gradeSheetGetCourseId(grade_sheet2))
        return 1;
    return 0;
}

static int gradeSheetBestCompareCondtion(ListElement grade_sheet1,
                                         ListElement grade_sheet2,
                                         ListSortKey sortkey){
    assert(grade_sheet1 != NULL && grade_sheet2 != NULL && sortkey != NULL);
    assert(grade_sheet1 != NULL && grade_sheet2 != NULL && sortkey != NULL);
    int grade1=gradeSheetGetCourseGrade(grade_sheet1)-*(int*)sortkey;
    int grade2=gradeSheetGetCourseGrade(grade_sheet2)-*(int*)sortkey;
    if (grade1!=grade2)
        return grade2-grade1;
    return gradeSheetCompareCondtionHelper(grade_sheet1,grade_sheet2);
}

static int gradeSheetWorstCompareCondtion(ListElement grade_sheet1,
                                         ListElement grade_sheet2,
                                         ListSortKey sortkey) {
    assert(grade_sheet1 != NULL && grade_sheet2 != NULL && sortkey != NULL);
    assert(grade_sheet1 != NULL && grade_sheet2 != NULL && sortkey != NULL);
    int grade1 = gradeSheetGetCourseGrade(grade_sheet1) - *(int *) sortkey;
    int grade2 = gradeSheetGetCourseGrade(grade_sheet2) - *(int *) sortkey;
    if (grade1 != grade2)
        return grade1 - grade2;
    return gradeSheetCompareCondtionHelper(grade_sheet1, grade_sheet2);
}

static char *stringDuplicate(const char *str) {
    assert(str != NULL);
    char *copy = malloc(strlen(str) + 1);
    return copy ? strcpy(copy, str) : NULL;
}

static SetElement courseIdCopyFunction(SetElement course_id) {
    if (course_id != NULL) {
        int *allocated_course_id = malloc(sizeof(*allocated_course_id));
        if (allocated_course_id == NULL) {
            return NULL;
        }
        *allocated_course_id = *(int *) course_id;
        return allocated_course_id;
    }
    return NULL;
}

static void courseIdDestroyFunction(SetElement course_id) {
    free(course_id);
}

static int
courseIdCompareFunction(SetElement course_id1, SetElement course_id2) {
    assert(course_id1 != NULL && course_id2 != NULL);
    int id1 = *(int *) course_id1;
    int id2 = *(int *) course_id2;
    if (id1 > id2) {
        return 1;
    }
    if (id2 > id1) {
        return -1;
    }
    return 0;
}

static ListElement semesterCopyFunction(ListElement semester) {
    if (semester != NULL) {
        return CopySemester(semester);
    }
    return NULL;
}

static void semesterDestroyFunction(ListElement semester) {
    destroySemester(semester);
}

static StudentResult allocateListAndSet(Student student,
                                        compareSetElements
                                        compare_course_id_function,
                                        CopyListElement copy_semester_function,
                                        freeSetElements free_semester_function,
                                        copySetElements copy_course_id_function,
                                        freeSetElements
                                        free_course_id_function) {
    assert(compare_course_id_function != NULL &&
           copy_semester_function != NULL &&
           free_semester_function != NULL && copy_course_id_function != NULL &&
           free_course_id_function != NULL);
    student->courses_id = setCreate(copy_course_id_function,
                                    free_course_id_function,
                                    compare_course_id_function);
    if (student->courses_id == NULL) {
        return STUDENT_OUT_OF_MEMORY;
    }
    student->semesters = listCreate(copy_semester_function,
                                    free_semester_function);
    if (student->semesters == NULL) {
        return STUDENT_OUT_OF_MEMORY;
    }
    return STUDENT_SUCCESS;
}

static StudentResult studentReport(Student student, int amount, FILE *output,
                                  CompareListElements compare) {
    assert(student != NULL);
    int key=0;
    if (output == NULL) return STUDENT_INVALID_PARAMETERS;
    if (amount<=0) return STUDENT_INVALID_PARAMETERS;
    List gradeSheetList;
    StudentResult studentResult = studentGetAllValidGrades(student,
                                                           &gradeSheetList);
    if (studentResult != STUDENT_SUCCESS) return studentResult;
    if (gradeSheetList != NULL) {
        listSort(gradeSheetList, compare, &key);
        LIST_FOREACH(GradeSheet, current_grade, gradeSheetList) {
            if (amount == 0) {
                break;
            }
            gradeSheetPrintInfo(output, current_grade);
            amount--;
        }
    }
    listDestroy(gradeSheetList);
    return STUDENT_SUCCESS;
}

static StudentResult studentCalculateEffective(Student student,
                                               int *effective_points_x2_ptr,
                                               int *effective_grade_sum_x2_ptr){
    assert(student != NULL);
    List valid_grades = NULL;
    StudentResult studentResult = studentGetAllValidGrades(student,
                                                           &valid_grades);
    if (studentResult != STUDENT_SUCCESS) return studentResult;
    LIST_FOREACH(GradeSheet, current_grade, valid_grades) {
        int point = gradeSheetGetCoursePointsX2(current_grade);
        *effective_points_x2_ptr += point;
        *effective_grade_sum_x2_ptr +=
                point * gradeSheetGetCourseGrade(current_grade);

    }
    listDestroy(valid_grades);
    return STUDENT_SUCCESS;
}

static ListElement studentCopyGradeSheet(ListElement grade_sheet) {
    if (grade_sheet == NULL) return NULL;
    return CopyGradeSheet(grade_sheet);
}

static void studentDestroyGradeSheet(ListElement grade_sheet) {
    removeGradeSheet(grade_sheet);
}

static List semeterReverseList(List semesters) {
    assert(semesters != NULL);
    List new = listCreate(semesterCopyFunction, semesterDestroyFunction);
    if (new == NULL) return NULL;
    LIST_FOREACH(Semester, current, semesters) {
        ListResult listResult = listInsertFirst(new, current);
        if (listResult == LIST_OUT_OF_MEMORY) {
            listDestroy(new);
            return NULL;
        }
    }
    return new;
}

static void studentUpdateCoursesIdSet(Student student){
    assert(student!=NULL);
    SET_FOREACH(int*,current_course,student->courses_id){
        bool exists=false;
        LIST_FOREACH(Semester,current_semester,student->semesters){
             GradeSheet grade_sheet=semesterGetCourseValidGradeSheet(
                    current_semester,*current_course);
            if (grade_sheet!=NULL){
                exists=1;
            }
            removeGradeSheet(grade_sheet);
        }
        if (exists==0){
            setRemove(student->courses_id,current_course);
        }
    }
}
/************************************************************************/
/************************************************************************/
StudentResult createStudent(Student *student, int student_id,
                               char *first_name, char *last_name) {

    if (student == NULL || last_name == NULL || first_name == NULL) {
        return STUDENT_INVALID_PARAMETERS;
    }
    Student new_student = malloc(sizeof(*new_student));
    if (new_student == NULL){
    	return STUDENT_OUT_OF_MEMORY;
    }

   new_student->first_name = stringDuplicate(first_name);
   new_student->last_name = stringDuplicate(last_name);
   StudentResult allocating_result = allocateListAndSet(new_student,
		   courseIdCompareFunction, semesterCopyFunction,
		   semesterDestroyFunction,courseIdCopyFunction
		   ,courseIdDestroyFunction);
	if (new_student->first_name == NULL||new_student->last_name==NULL  ||
			allocating_result != STUDENT_SUCCESS) {
		destroyStudent(new_student);
	   	return STUDENT_OUT_OF_MEMORY;
	   	    }
    if (student_id > MAX_STUDENT_ID || student_id < MIN_STUDENT_ID) {
    	destroyStudent(new_student);
        return STUDENT_INVALID_PARAMETERS;
    }
    new_student->student_id = student_id;
    *student = new_student;
    return STUDENT_SUCCESS;
}

Student copyStudent(Student student) {
    assert(student != NULL);
    Student new_student = NULL;
    createStudent(&new_student, student->student_id, student->first_name,
                     student->last_name);
    return new_student;
}

void destroyStudent(Student student) {
    if (student != NULL) {
        free(student->first_name);
        free(student->last_name);
        setDestroy(student->courses_id);
        listDestroy(student->semesters);
    }
    free(student);
}

char *studentGetFirstName(Student student) {
    assert(student != NULL);
    return stringDuplicate(student->first_name);
}

char *studentGetLastName(Student student) {
    assert(student != NULL);
    return stringDuplicate(student->last_name);
}

int studentGetId(Student student) {
    assert(student != NULL);
    return student->student_id;
}

StudentResult studentGetMaxGradeInCourse(Student student,int course_id,
                                         GradeSheet *out) {
    assert(student != NULL);
    if (out == NULL) {
    	return STUDENT_INVALID_PARAMETERS;
    }
    GradeSheet current_grade = NULL, max_grade = NULL;
    LIST_FOREACH(Semester, current_semester, student->semesters) {
        current_grade = semesterGetCourseMaxGrade(current_semester, course_id);
        if (current_grade != NULL) {
            if (max_grade == NULL || gradeSheetGetCourseGrade(current_grade) >
                                     gradeSheetGetCourseGrade(max_grade)) {
                removeGradeSheet(max_grade);
                max_grade =CopyGradeSheet(current_grade);
            }
        }
        removeGradeSheet(current_grade);
    }
    *out = max_grade;
    return STUDENT_SUCCESS;
}

StudentResult studentAddGradeSheet(Student student, int semester_id,
                                   int course_id, char *points, int grade) {
    assert(student != NULL);
    bool already_exist=isSemesterExist(student,  semester_id);
    if(!already_exist){
    	StudentResult add_result=studentAddSemester( student,semester_id);
    	if(add_result!= STUDENT_SUCCESS){
    		return add_result;
    	}
    }
    LIST_FOREACH(Semester, current, student->semesters) {
        if (semesterGetId(current) == semester_id) {
        	SemesterResult add_result=semesterAddGrade(current,
        			course_id,student->student_id, points, grade);
        	if (add_result!=SEMESTER_SUCCESS && !already_exist){
        		studentRemoveSemester(student,semester_id);
        	}
        	if (add_result==SEMESTER_INVALID_PARAMETERS){
        		return STUDENT_INVALID_PARAMETERS;
        	 }
        	if (add_result==SEMESTER_OUT_OF_MEMORY){

        		return STUDENT_OUT_OF_MEMORY;
        	 }
        	break;
        }
   }
    setAdd(student->courses_id, &course_id);
	return STUDENT_SUCCESS;
}

StudentResult studentUpdateGradeSheet(Student student, int course_id,
                                     int new_grade) {
    assert(student != NULL);
    LIST_FOREACH(Semester, current, student->semesters) {
        if (semesterIsCourseIdExist(current, course_id)) {
            SemesterResult update_result = semesterUpdateGrade(current,
                                                               course_id,
                                                               new_grade);
            if (update_result == SEMESTER_INVALID_PARAMETERS) {
                return STUDENT_INVALID_PARAMETERS;
            }
            return STUDENT_SUCCESS;
        }
    }
    return STUDENT_COURSE_DOES_NOT_EXIST;
}

StudentResult studentRemoveGradeSheet(Student student,int course_id,
                                      int semester) {
    assert(student != NULL);
	LIST_FOREACH(Semester, current, student->semesters) {
		if (semesterGetId(current) == semester) {
			SemesterResult remove_result =
					semesterRemoveGrade(current,course_id);
			 if (remove_result == SEMESTER_COURSE_DOES_NOT_EXIST) {
					return STUDENT_COURSE_DOES_NOT_EXIST;
				}
			 if (remove_result == SEMESTER_INVALID_PARAMETERS) {
					return STUDENT_INVALID_PARAMETERS;
				}
			 studentUpdateCoursesIdSet(student);
            if (semesterTotalPointsX2(current)==0){
                studentRemoveSemester(student,semesterGetId(current));
            }
			 return STUDENT_SUCCESS;
        }
    }
	return STUDENT_COURSE_DOES_NOT_EXIST;
 }

StudentResult studentPrintInfo(Student student, FILE *output) {
    assert(student != NULL);
    if (output == NULL) {
    	return STUDENT_INVALID_PARAMETERS;
    }
    mtmPrintStudentInfo(output, student->student_id, student->first_name,
                        student->last_name);
    return STUDENT_SUCCESS;
}

StudentResult studentReportFull(Student student, FILE *output) {
    assert(student != NULL);
    if (output == NULL) {
    	return STUDENT_INVALID_PARAMETERS;
    }
    int total_points_x2=0, failed_points_x2=0, total_points_x2_counter = 0,
            failed_points_x2_counter = 0, effective_points_x2_counter = 0,
            effective_grade_sum_x2_counter = 0;
    studentPrintInfo(student, output);
    List current_semester_reverse = semeterReverseList(student->semesters);
    if (current_semester_reverse == NULL) {
    	return STUDENT_OUT_OF_MEMORY;
    }
    LIST_FOREACH(Semester, current_semester,current_semester_reverse ) {
        semesterPrintsAllGrades(output, current_semester, student->courses_id);
        failed_points_x2 = semesterTotalFailed_points_x2(current_semester);
        total_points_x2 = semesterTotalPointsX2(current_semester);
        total_points_x2_counter += total_points_x2;
        failed_points_x2_counter += failed_points_x2;
    }
    listDestroy(current_semester_reverse);
    StudentResult studentResult = studentCalculateEffective(student,
    		&effective_points_x2_counter,&effective_grade_sum_x2_counter);
    if (studentResult != STUDENT_SUCCESS){
    	return studentResult;
    }
    mtmPrintSummary(output, total_points_x2_counter,failed_points_x2_counter,
                   effective_points_x2_counter, effective_grade_sum_x2_counter);
    return STUDENT_SUCCESS;
}

StudentResult studentReportClean(Student student, FILE *output) {
    assert(student != NULL);
    if (output == NULL) {
    	return STUDENT_INVALID_PARAMETERS;
    }
    List gradeSheetList;
    studentPrintInfo(student, output);
    studentGetAllValidGrades(student, &gradeSheetList);
    int sort_key = 0, effective_points_x2=0,effective_grade_sum_x2=0;
    if (gradeSheetList != NULL) {
        listSort(gradeSheetList, gradeSheetCleanCompareCondtion, &sort_key);
        if (gradeSheetList != NULL) {
            LIST_FOREACH(GradeSheet, current_grade, gradeSheetList) {
                int points=gradeSheetGetCoursePointsX2(current_grade);
                effective_points_x2+=points;
                gradeSheetPrintInfo(output, current_grade);
                effective_grade_sum_x2+=(
                        points*gradeSheetGetCourseGrade(current_grade));
            }
        }
    }
    mtmPrintCleanSummary(output,effective_points_x2,effective_grade_sum_x2);
    listDestroy(gradeSheetList);
    return STUDENT_SUCCESS;
}

StudentResult studentReportBest(Student student, int amount, FILE *output) {
    return studentReport(student, amount,output, gradeSheetBestCompareCondtion);
}

StudentResult studentReportWorst(Student student, int amount, FILE *output) {

    return studentReport(student,amount,output, gradeSheetWorstCompareCondtion);
}

StudentResult studentFacultyRequest(Student student,int course_id,
		char *request,FILE* output){
    assert(student != NULL && request!=NULL && output!=NULL);
    if(strcmp(request, "remove_course") == 0 &&
    		!setIsIn(student->courses_id, &course_id)){
    	 return STUDENT_COURSE_DOES_NOT_EXIST;
    }
    if (strcmp(request, "cancel_course")==0 ||
    		strcmp(request,"register_course")==0 ||
			strcmp(request, "remove_course") == 0) {
        mtmFacultyResponse(output, "your request was rejected");
        return STUDENT_SUCCESS;
    }
    return STUDENT_INVALID_PARAMETERS;
}
