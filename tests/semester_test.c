/*
 * Semester_test.c
 *
 *  Created on: Dec 22, 2017
 *      Author: Reham
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../list.h"
#include "../set.h"
#include "test_utilities.h"
#include "../grade_sheet.h"
#include "../semester.h"
#include "../mtm_ex3.h"




static Semester initGradeSheet(){
	Semester semester=NULL;
	int semester_id=1;
	int	student_id=208666555;
	int course_id,grade;
	char* points;
	SemesterResult test1=createSemester(semester_id,&semester);
	ASSERT_TEST(test1==SEMESTER_SUCCESS);
	course_id=104012,grade=84;
	points="5.5";
	SemesterResult test2= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test2==SEMESTER_SUCCESS);
	course_id=104167,grade=44;
	points="5";
	SemesterResult test3= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test3==SEMESTER_SUCCESS);
	course_id=234114,grade=88;
	points="4.0";
	SemesterResult test4= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test4==SEMESTER_SUCCESS);
	course_id=234145,grade=98;
	points="3";
	SemesterResult test5= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test5==SEMESTER_SUCCESS);
	course_id=394808,grade=92;
	points="1";
	SemesterResult test6= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test6==SEMESTER_SUCCESS);
	course_id=104012,grade=95;
	points="5.5";
	SemesterResult test7= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test7==SEMESTER_SUCCESS);
	course_id=394808,grade=93;
	points="5.5";
	SemesterResult test8= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test8==SEMESTER_SUCCESS);
	return semester;
}

static bool testCreateSemester(){
	Semester semester=NULL;
	int semester_id=-5;
	SemesterResult test1=createSemester(semester_id,&semester);
	ASSERT_TEST(test1==SEMESTER_INVALID_PARAMETERS); //invalid semester id
	semester_id=2;
	SemesterResult test2=createSemester(semester_id,  NULL);
	ASSERT_TEST(test2==SEMESTER_INVALID_PARAMETERS); //invalid semester
	SemesterResult test3=createSemester(semester_id,&semester);
	ASSERT_TEST(test3==SEMESTER_SUCCESS);
	destroySemester(semester);
	return true;
}

static bool testCopySemester(){
	Semester semester=initGradeSheet();
	Semester semester_copy=CopySemester(semester);
	ASSERT_TEST(semester_copy != NULL);
	destroySemester(semester_copy);
	destroySemester(semester);
	return true;
}

static bool testSemesterAddGrade(){
	Semester semester=NULL;
	int semester_id=3;
	SemesterResult test1=createSemester(semester_id,&semester);
	ASSERT_TEST(test1==SEMESTER_SUCCESS);
	int course_id=-10,student_id=77,grade=17;
	char*  points=NULL;
	SemesterResult test2= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // points is invalid
	points="3.6";
	ASSERT_TEST(test2==SEMESTER_INVALID_PARAMETERS);
	SemesterResult test3= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // points is invalid
	ASSERT_TEST(test3==SEMESTER_INVALID_PARAMETERS);
	points="5.5";
	SemesterResult test4= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // course_id is invalid
	ASSERT_TEST(test4==SEMESTER_INVALID_PARAMETERS);
	course_id=11111111;
	SemesterResult test5= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // course_id is invalid
	ASSERT_TEST(test5==SEMESTER_INVALID_PARAMETERS);
	course_id=55;
	student_id=-4;
	SemesterResult test6= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // student_id is invalid
	ASSERT_TEST(test6==SEMESTER_INVALID_PARAMETERS);
	student_id=1000000000;
	SemesterResult test7= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // student_id is invalid
	ASSERT_TEST(test7==SEMESTER_INVALID_PARAMETERS);
	student_id=208777048;
	grade=-10;
	SemesterResult test8= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // student_id is invalid
	ASSERT_TEST(test8==SEMESTER_INVALID_PARAMETERS);
	grade=110;
	SemesterResult test9= semesterAddGrade(semester, course_id ,student_id,
			points, grade); // student_id is invalid
	ASSERT_TEST(test9==SEMESTER_INVALID_PARAMETERS);
	grade=99;
	SemesterResult test10= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test10==SEMESTER_SUCCESS);
	destroySemester(semester);
	return true;
}

static bool testSemesterIsCourseIdExist(){
	Semester semester=initGradeSheet();
	ASSERT_TEST(semesterIsCourseIdExist(semester,104012));
	ASSERT_TEST(semesterIsCourseIdExist(semester,104167));
	ASSERT_TEST(semesterIsCourseIdExist(semester,234114));
	ASSERT_TEST(semesterIsCourseIdExist(semester,234145));
	ASSERT_TEST(!semesterIsCourseIdExist(semester,1));
	destroySemester(semester);
	return true;
}

static bool testSemesterRemoveGrade(){
	Semester semester=initGradeSheet();
	ASSERT_TEST(semesterIsCourseIdExist(semester,104012));
	semesterRemoveGrade(semester,104012);
	ASSERT_TEST(!semesterIsCourseIdExist(semester,1));
	destroySemester(semester);
	return true;

}

static bool testSemesterGetCourseMaxGrade(){
	Semester semester=initGradeSheet();
	GradeSheet max_grade1=semesterGetCourseMaxGrade(semester,104012);
	ASSERT_TEST(max_grade1!=NULL);
	ASSERT_TEST(gradeSheetGetCourseId(max_grade1)==104012);
	ASSERT_TEST(gradeSheetGetCourseGrade(max_grade1)==95);
	int course_id=104012,student_id=123456789,grade=97;
	char* points="3.5";
	SemesterResult add_result= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(add_result==SEMESTER_SUCCESS);// now max grade is 97
	GradeSheet max_grade2=semesterGetCourseMaxGrade(semester,104012);
	ASSERT_TEST(gradeSheetGetCourseId(max_grade2)==104012);
	ASSERT_TEST(gradeSheetGetCourseGrade(max_grade2)==97);
	removeGradeSheet(max_grade1);
	removeGradeSheet(max_grade2);
	destroySemester(semester);
	return true;

}

static bool testSemesterGetCourseValidGradeSheet(){
	Semester semester=initGradeSheet();
	GradeSheet valid_grade1=semesterGetCourseValidGradeSheet(semester,394808);
	ASSERT_TEST(gradeSheetGetCourseId(valid_grade1)==394808);
	ASSERT_TEST(gradeSheetGetCourseGrade(valid_grade1)==93);
	int course_id=394808,student_id=123456789,mark=66;
	char* points="3.5";
	SemesterResult add_result= semesterAddGrade(semester, course_id ,student_id,
			points, mark);
	ASSERT_TEST(add_result==SEMESTER_SUCCESS);// now max grade is 97
	GradeSheet valid_grade2=semesterGetCourseValidGradeSheet(semester,394808);
	ASSERT_TEST(gradeSheetGetCourseId(valid_grade2)==394808);
	ASSERT_TEST(gradeSheetGetCourseGrade(valid_grade2)==66);
	removeGradeSheet(valid_grade1);
	removeGradeSheet(valid_grade2);
	destroySemester(semester);
	return true;
}

int testSemesterGetId(){
	Semester semester=initGradeSheet();
	int semester_id=semesterGetId(semester);
	ASSERT_TEST(semester_id==1);
	destroySemester(semester);
	return true;
}

static bool testSemesterTotalPointsX2(){
	Semester semester=NULL;
	int semester_id=1;
	int	student_id=208666555;
	int course_id,grade;
	char* points;
	SemesterResult test1=createSemester(semester_id,&semester);
	ASSERT_TEST(test1==SEMESTER_SUCCESS);
	course_id=104012,grade=84;
	points="5.5";
	SemesterResult test2= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test2==SEMESTER_SUCCESS);
	course_id=104167,grade=71;
	points="5";
	SemesterResult test3= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test3==SEMESTER_SUCCESS);
	course_id=104012,grade=71;
	points="5";
	SemesterResult test4= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test4==SEMESTER_SUCCESS);
	int total_points_X2=semesterTotalPointsX2(semester);
	ASSERT_TEST(total_points_X2==31);
	destroySemester(semester);
	return true;

}

static bool testSemesterTotalFailed_points_x2(){
	Semester semester=NULL;
	int semester_id=1;
	int	student_id=208666555;
	int course_id,grade;
	char* points;
	SemesterResult test1=createSemester(semester_id,&semester);
	ASSERT_TEST(test1==SEMESTER_SUCCESS);
	course_id=104012,grade=55;
	points="5.5";
	SemesterResult test2= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test2==SEMESTER_SUCCESS);
	course_id=104167,grade=40;
	points="5";
	SemesterResult test3= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test3==SEMESTER_SUCCESS);
	course_id=104012,grade=71;
	points="5";
	SemesterResult test4= semesterAddGrade(semester, course_id ,student_id,
			points, grade);
	ASSERT_TEST(test4==SEMESTER_SUCCESS);
	int failed=semesterTotalFailed_points_x2(semester);
	ASSERT_TEST(failed==10);
	destroySemester(semester);
	return true;

}

static SetElement copyIntger (SetElement num){
	int* new_num=malloc(sizeof(*new_num));
	if (new_num == NULL){
		return NULL;
	}
	*new_num=*(int*)num;
	return new_num;
}

static void freeIntger (SetElement num){
		free((int*)num);
}


static int compareIntger (SetElement num1,SetElement num2){
		int value1=*(int*)num1;
		int value2=*(int*)num2;
		return value1-value2;

}

static bool testSemesterPrintsAllGrades(){
	printf("\n");
	Semester semester=initGradeSheet();
	Set courses=setCreate(copyIntger,freeIntger,compareIntger);
	int course_num=104012;
	SetResult add_result=setAdd(courses,&course_num);
	ASSERT_TEST(add_result==SET_SUCCESS);
	course_num=104167;
	add_result=setAdd(courses,&course_num);
	ASSERT_TEST(add_result==SET_SUCCESS);
	course_num=234114;
	add_result=setAdd(courses,&course_num);
	ASSERT_TEST(add_result==SET_SUCCESS);
	course_num=234145;
	add_result=setAdd(courses,&course_num);
	ASSERT_TEST(add_result==SET_SUCCESS);
	course_num=394808;
	add_result=setAdd(courses,&course_num);
	ASSERT_TEST(add_result==SET_SUCCESS);
	semesterPrintsAllGrades(stdout,semester,courses);
	setDestroy(courses);
	destroySemester(semester);
	return true;
}

int main(){
	RUN_TEST(testCreateSemester);
	RUN_TEST(testCopySemester);
	RUN_TEST(testSemesterAddGrade);
	RUN_TEST(testSemesterIsCourseIdExist);
	RUN_TEST(testSemesterRemoveGrade);
	RUN_TEST(testSemesterGetCourseMaxGrade);
	RUN_TEST(testSemesterGetCourseValidGradeSheet);
	RUN_TEST(testSemesterGetId);
	RUN_TEST(testSemesterTotalPointsX2);
	RUN_TEST(testSemesterTotalFailed_points_x2);
	RUN_TEST(testSemesterPrintsAllGrades);
	return true;
}
