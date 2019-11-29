/*
 * grade_sheet_test.c
 *
 *  Created on: Dec 21, 2017
 *      Author: Reham
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "test_utilities.h"
#include "../grade_sheet.h"


static GradeSheet initGradeSheet(){
	int course_id=11,semester_id=6,student_id=77,grade=17;
	char* points="5.5";
	GradeSheet grade_sheet;
	GradeSheetResult create_Result =createGradeSheet
			( course_id, semester_id,student_id, points, grade,&grade_sheet);
	if (create_Result == GRADE_SHEET_SUCCESS){
		return  grade_sheet ;
	}
	return NULL;
}

static bool testCreateGradeSheet(){
	GradeSheet grade_sheet=NULL;
	int course_id=10,semester_id=5,student_id=77,grade=17;
	char* points="2.5";
	GradeSheetResult test1=createGradeSheet
			( course_id, semester_id,student_id, NULL, grade,&grade_sheet);
	ASSERT_TEST(test1==GRADE_SHEET_INVALID_PARAMETERS); //invalid points
	GradeSheetResult test2=createGradeSheet
		( course_id, semester_id,student_id, points, grade,NULL);
	ASSERT_TEST(test2==GRADE_SHEET_INVALID_PARAMETERS); //invalid grade_sheet
	GradeSheetResult test3=createGradeSheet
			( course_id, semester_id,student_id, points, grade,NULL);
	ASSERT_TEST(test3==GRADE_SHEET_INVALID_PARAMETERS); //invalid

	course_id=-5;
	GradeSheetResult test4=createGradeSheet
			( course_id, semester_id,student_id, points, grade,&grade_sheet);
	ASSERT_TEST(test4==GRADE_SHEET_INVALID_PARAMETERS);//invalid course id
	course_id=10000005;
	GradeSheetResult test5=createGradeSheet
			( course_id, semester_id,student_id, points, grade,&grade_sheet);
	ASSERT_TEST(test5==GRADE_SHEET_INVALID_PARAMETERS);//invalid course id

	course_id=20,semester_id=0;
	GradeSheetResult test6=createGradeSheet
			( course_id, semester_id,student_id, points, grade,&grade_sheet);
	ASSERT_TEST(test6==GRADE_SHEET_INVALID_PARAMETERS);//invalid semester id
	semester_id=12,grade=-10;
	GradeSheetResult test7=createGradeSheet
			( course_id, semester_id,student_id, points, grade,&grade_sheet);
	ASSERT_TEST(test7==GRADE_SHEET_INVALID_PARAMETERS);//invalid grade
	grade=122;
	GradeSheetResult test8=createGradeSheet
			( course_id, semester_id,student_id, points, grade,&grade_sheet);
	ASSERT_TEST(test8==GRADE_SHEET_INVALID_PARAMETERS);//invalid grade
	grade=97,points="3.7";
	GradeSheetResult test9=createGradeSheet
			( course_id, semester_id,student_id, points, grade,&grade_sheet);
	ASSERT_TEST(test9==GRADE_SHEET_INVALID_PARAMETERS);//invalid points
	points="3.5";
	GradeSheetResult test10=createGradeSheet
			(50,50,10,"2.5",9,&grade_sheet);
	ASSERT_TEST(test10==GRADE_SHEET_SUCCESS);
	removeGradeSheet(grade_sheet);
	return true;
}

static bool testCopyGradeSheet(){
	GradeSheet grade_sheet=initGradeSheet();
	ASSERT_TEST(grade_sheet!= NULL);
	GradeSheet grade_sheet_copy=CopyGradeSheet(grade_sheet);
	ASSERT_TEST(grade_sheet_copy != NULL);
	removeGradeSheet(grade_sheet);
	removeGradeSheet(grade_sheet_copy);
	return true;
}

static bool testGradeSheetGetStudentId(){
	GradeSheet grade_sheet=initGradeSheet();
	ASSERT_TEST(grade_sheet!= NULL);
	int student_id=gradeSheetGetStudentId(grade_sheet);
	ASSERT_TEST(student_id == 77);
	removeGradeSheet(grade_sheet);
	return true;
}

static bool testGradeSheetGetCourseId(){
	GradeSheet grade_sheet=initGradeSheet();
	ASSERT_TEST(grade_sheet!= NULL);
	int course_id=gradeSheetGetCourseId(grade_sheet);
	ASSERT_TEST(course_id == 11);
	removeGradeSheet(grade_sheet);
	return true;
}

static bool testGradeSheetGetCoursePointsX2(){
	GradeSheet grade_sheet=initGradeSheet();
	ASSERT_TEST(grade_sheet!= NULL);
	int course_points_X2=gradeSheetGetCoursePointsX2(grade_sheet);
	ASSERT_TEST(course_points_X2 == 11);
	removeGradeSheet(grade_sheet);
	return true;
}

static bool testGradeSheetGetCourseGrade(){
	GradeSheet grade_sheet=initGradeSheet();
	ASSERT_TEST(grade_sheet!= NULL);
	int course_grade=gradeSheetGetCourseGrade(grade_sheet);
	ASSERT_TEST(course_grade == 17);
	removeGradeSheet(grade_sheet);
	return true;
}


static bool testGradeSheetUpdateGrade(){
	GradeSheet grade_sheet=initGradeSheet();
	ASSERT_TEST(grade_sheet!= NULL);
	gradeSheetUpdateGrade(grade_sheet,99);
	int course_grade=gradeSheetGetCourseGrade(grade_sheet);
	ASSERT_TEST(course_grade == 99);
	removeGradeSheet(grade_sheet);
	return true;
}

static bool testGradeSheetPrintInfo(){
	GradeSheet grade_sheet=initGradeSheet();
	ASSERT_TEST(grade_sheet!= NULL);
	printf("\n");
	gradeSheetPrintInfo (stdout, grade_sheet);

	removeGradeSheet(grade_sheet);
	return true;
}


int main(){
	RUN_TEST(testCreateGradeSheet);
	RUN_TEST(testCopyGradeSheet);
	RUN_TEST(testGradeSheetGetStudentId);
	RUN_TEST(testGradeSheetGetCourseId);
	RUN_TEST(testGradeSheetGetCoursePointsX2);
	RUN_TEST(testGradeSheetGetCourseGrade);
	RUN_TEST(testGradeSheetUpdateGrade);
	RUN_TEST(testGradeSheetPrintInfo);
	return 0;
}
