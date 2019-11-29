#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"
#include "semester.h"
#include "mtm_ex3.h"
#include "grade_sheet.h"

#define MIN_COURSE_ID   1
#define MAX_COURSE_ID   999999
#define MIN_GRADE  0
#define MAX_GRADE   100
#define MIN_STUDENT_ID  1
#define MAX_STUDENT_ID  999999999
#define MAX_COURSE_SPORT_ID 399999
#define MIN_COURSE_SPORT_ID 390000


struct semester_t{
	int semester_id;
	List semester_grades;
};

/*
 * copies an existing grade sheet
 * @param: grade_sheet - grade_sheet to be copied
 * @return: a copy of the grade_sheet, NULL if memory allocation failed or the
 *  grade_sheet is NULL.
 */
static ListElement copyListGradeSheet(ListElement grade_sheet);

/*
 * frees an existing grade sheet and it's inner allocations, does nothing if the
 * grade_sheet is NULL.
 * @param: grade_sheet - grade_sheet to be freed
 */
static void freeListGradeSheet(ListElement grade_sheet);

/**
* semester and effective_grade_sum_x2 and effective_points_x2 must not be NULL
* calculate the sum of the effective course grades and the number of total
* effective course points, when each grade is multiplied by the number of course
* points, multiplied by 2,and counts the number of total effective course points
* , multiplied by 2
* @param:semester - the semester to be calculated
* @param:@effective_grade_sum_x2 - pointer to the out put that will be
* calculated
* @param:effective_points_x2 - pointer to the out put that will be calculated
* return :SEMESTER_OUT_OF_MEMORY if memory allocation failed ,
* SEMESTER_SUCCESS otherwise.
*/
static SemesterResult  semesterTotalEffectiveGradeAndCoursePointsX2
        (Semester semester,int* effective_grade_sum_x2,int* effective_points_x2,
         Set course_id) ;

/**
 *
 * @param gradesheets
 * @return
 */
static List semeterReverseList(List gradesheets);

static SemesterResult semesterGetAllValidGrades(Semester semester, List *out,
                                                Set courses_id);
/**********************static function implementation**************************/
static ListElement copyListGradeSheet(ListElement grade_sheet){
	if(grade_sheet == NULL){
		return NULL;
	}
	return CopyGradeSheet(grade_sheet);
}

static void freeListGradeSheet(ListElement grade_sheet){
	removeGradeSheet(grade_sheet);
}

static SemesterResult  semesterTotalEffectiveGradeAndCoursePointsX2
(Semester semester,int* effective_grade_sum_x2,int* effective_points_x2,Set
                    course_id) {
    assert(semester != NULL && effective_grade_sum_x2
           &&effective_points_x2!=NULL);
    List grade_sheet = semester->semester_grades;
    if (listGetSize(grade_sheet) == 0) {
        return SEMESTER_SUCCESS;
    }
    assert(semester->semester_grades!=NULL);
    List valid_grades;
    SemesterResult semesterResult=semesterGetAllValidGrades(semester,
                                                            &valid_grades,
                                                            course_id);
    if (semesterResult==SEMESTER_OUT_OF_MEMORY) return semesterResult;
    LIST_FOREACH(GradeSheet,current_grade,valid_grades){
        int point=gradeSheetGetCoursePointsX2(current_grade);
        *effective_points_x2+=point;
        *effective_grade_sum_x2+=point*gradeSheetGetCourseGrade(current_grade);
    }
    listDestroy(valid_grades);
    return SEMESTER_SUCCESS;
}

static List semeterReverseList(List gradesheets){
    assert(gradesheets!=NULL);
    List new=listCreate(copyListGradeSheet,freeListGradeSheet);
    if (new==NULL) return NULL;
    LIST_FOREACH(GradeSheet,current,gradesheets){
        listInsertFirst(new,current);
    }
    return new;
}

static SemesterResult semesterGetAllValidGrades(Semester semester, List *out,
                                                Set courses_id){
    assert(semester != NULL);
    GradeSheet gradeSheet;
    List valid_grades = listCreate(copyListGradeSheet,
                                   freeListGradeSheet);
    if (valid_grades==NULL) return SEMESTER_OUT_OF_MEMORY;
    SET_FOREACH(int*,current_course,courses_id) {
        gradeSheet=semesterGetCourseValidGradeSheet(semester,
                                                    *current_course);
        if (gradeSheet!=NULL){
            if (listInsertFirst(valid_grades,gradeSheet)==
                LIST_OUT_OF_MEMORY){
                return SEMESTER_OUT_OF_MEMORY;
            }
            listInsertAfterCurrent(valid_grades,gradeSheet);
        }
        removeGradeSheet(gradeSheet);
    }
    *out=valid_grades;
    return SEMESTER_SUCCESS;
}

/******************************************************************************/
SemesterResult createSemester(int semester_id, Semester* semester){
	if(semester_id <= 0 || semester==NULL){
		return SEMESTER_INVALID_PARAMETERS;
	}
	*semester= malloc(sizeof(**semester));
	if(*semester==NULL){
		return SEMESTER_OUT_OF_MEMORY;
	}
	(*semester)->semester_grades=listCreate(copyListGradeSheet,freeListGradeSheet);
	if((*semester)->semester_grades == NULL){
		destroySemester(*semester);
		return SEMESTER_OUT_OF_MEMORY;
	}
	(*semester)->semester_id=semester_id;
	return SEMESTER_SUCCESS;
}

Semester CopySemester(Semester semester){
	assert(semester!=NULL);
	Semester semester_copy=malloc(sizeof(*semester_copy));
	if(semester_copy== NULL) {
		return NULL;
	}

	if(semester->semester_grades == NULL){
		semester_copy->semester_grades = NULL;
        semester_copy->semester_id=semester->semester_id;
		return semester_copy;
	}
	List copy_list=listCopy(semester->semester_grades);
	if(copy_list== NULL){
		destroySemester(semester_copy);
		return NULL;
	}
	semester_copy->semester_grades=copy_list;
    semester_copy->semester_id=semester->semester_id;
	return semester_copy;
}

void destroySemester(Semester semester){
	if(semester != NULL){
		listDestroy(semester->semester_grades);
	}
	free(semester);
}

bool semesterIsCourseIdExist(Semester semester ,int course_id){
	assert(semester!=NULL);
	LIST_FOREACH(GradeSheet,currentGradeSheet,semester->semester_grades){
		 if (gradeSheetGetCourseId(currentGradeSheet)==course_id){
			 return true;
		 }
	 }
	return false;
}

SemesterResult semesterAddGrade(Semester semester, int course_id ,
		int  student_id,char* points,int grade){
	assert(semester!=NULL);
	GradeSheet new_grade_sheet;
	GradeSheetResult create_result=createGradeSheet(course_id,
			semester->semester_id,student_id,points, grade,&new_grade_sheet);
	if(create_result != GRADE_SHEET_SUCCESS){
		if(create_result==GRADE_SHEET_INVALID_PARAMETERS){
			return SEMESTER_INVALID_PARAMETERS;
		}
		return SEMESTER_OUT_OF_MEMORY;
	}
	ListResult add_result=listInsertFirst
			(semester->semester_grades, new_grade_sheet);
	removeGradeSheet(new_grade_sheet);
	if(add_result!= LIST_SUCCESS){
		return SEMESTER_OUT_OF_MEMORY;
	}
	return SEMESTER_SUCCESS;
}

SemesterResult semesterRemoveGrade(Semester semester, int course_id){

	assert(semester!=NULL);
	if(!semesterIsCourseIdExist(semester,course_id)){
		return SEMESTER_COURSE_DOES_NOT_EXIST;
	}

	if(course_id<MIN_COURSE_ID ||course_id>MAX_COURSE_ID ){
		return SEMESTER_INVALID_PARAMETERS;
	}
	LIST_FOREACH(GradeSheet,currentGradeSheet,semester->semester_grades){
			 if (course_id == gradeSheetGetCourseId(currentGradeSheet)){
				 listRemoveCurrent(semester->semester_grades);
				 break;
			 }
	}
	return SEMESTER_SUCCESS;
}

SemesterResult semesterUpdateGrade(Semester semester, int course_id ,
								   int new_grade){
	assert(semester!= NULL);
	if(course_id<MIN_COURSE_ID|| course_id>MAX_COURSE_ID
			||new_grade>MAX_GRADE || new_grade <MIN_GRADE){
		return SEMESTER_INVALID_PARAMETERS;
	}
	LIST_FOREACH(GradeSheet,currentGrade,semester->semester_grades){
		if (gradeSheetGetCourseId(currentGrade)==course_id){
			gradeSheetUpdateGrade(currentGrade,new_grade);
			return SEMESTER_SUCCESS;
		}
	}
	return SEMESTER_COURSE_DOES_NOT_EXIST;
}

GradeSheet semesterGetCourseMaxGrade(Semester semester, int course_id){
	assert(semester!=NULL);
	int max_grade=0;
	GradeSheet max_grade_sheet=NULL,temp_grade_sheet=NULL;
	LIST_FOREACH(GradeSheet,currentGradeSheet,semester->semester_grades){
		 if (gradeSheetGetCourseId(currentGradeSheet)==course_id){
			 int current_grade=
					 gradeSheetGetCourseGrade(currentGradeSheet);
			 if (current_grade>max_grade){
				 temp_grade_sheet =currentGradeSheet;
				 max_grade=current_grade;
			 }
		 }
	}
	 if(temp_grade_sheet!= NULL){
		 max_grade_sheet=CopyGradeSheet(temp_grade_sheet);
	 }
	 return max_grade_sheet;
}

GradeSheet semesterGetCourseValidGradeSheet(Semester semester, int course_id){
	assert(semester!=NULL);
	if(course_id<MIN_COURSE_ID ||course_id>MAX_COURSE_ID ){
		return NULL;
	}
	LIST_FOREACH(GradeSheet,currentGradeSheet,semester->semester_grades){
		 if (gradeSheetGetCourseId(currentGradeSheet)==course_id){
			 return CopyGradeSheet(currentGradeSheet);
		 }
	 }
	return NULL;
}

int semesterGetId(Semester semester){
	assert(semester!=NULL);
	return semester->semester_id;
}

int semesterTotalPointsX2(Semester semester){
	assert(semester!=NULL);
	int total_pointsX2=0;
	LIST_FOREACH(GradeSheet,currentGradeSheet,semester->semester_grades){
		total_pointsX2+=gradeSheetGetCoursePointsX2(currentGradeSheet);
	}

	return total_pointsX2;
}

int semesterTotalFailed_points_x2(Semester semester){
	assert(semester!=NULL);
	int total_failedX2=0;
	LIST_FOREACH(GradeSheet,currentGradeSheet,semester->semester_grades){
		if (gradeSheetGetCourseGrade(currentGradeSheet)<55){
			total_failedX2+=gradeSheetGetCoursePointsX2(currentGradeSheet);
		}
	}
	return total_failedX2;
}

SemesterResult semesterPrintsAllGrades(FILE* output_channel,Semester
                                            semester,Set course_id) {
	assert(semester!=NULL && output_channel!=NULL);
	List current_semester_reverse=semeterReverseList(
			semester->semester_grades);
    if (current_semester_reverse==NULL) return SEMESTER_OUT_OF_MEMORY;
	LIST_FOREACH(GradeSheet,currentGradeSheet,current_semester_reverse){
		gradeSheetPrintInfo(output_channel,currentGradeSheet);
	}
	listDestroy(current_semester_reverse);
	int effective_grade_sum_x2=0,effective_points_x2=0;
	SemesterResult effective_result=semesterTotalEffectiveGradeAndCoursePointsX2
			(semester,&effective_grade_sum_x2,&effective_points_x2,course_id);
	if(effective_result != SEMESTER_SUCCESS)
		return SEMESTER_OUT_OF_MEMORY;
	int total_points_x2=semesterTotalPointsX2(semester);
	int failed_points_x2=semesterTotalFailed_points_x2(semester);
	mtmPrintSemesterInfo(output_channel,semester->semester_id,
						 total_points_x2, failed_points_x2,effective_points_x2,
						 effective_grade_sum_x2);
	return SEMESTER_SUCCESS;
}
