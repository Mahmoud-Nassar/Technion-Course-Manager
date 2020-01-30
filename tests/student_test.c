//
// Created by mahmood on 12/24/2017.
//

#include <stdio.h>
#include "test_utilities.h"
#include "../student.h"
#include <string.h>
#include <malloc.h>

static bool testCreateStudent(){
    StudentResult studentResult= createStudent(NULL,11111111,"omar","nassar");
    ASSERT_TEST(studentResult == STUDENT_INVALID_PARAMETERS);
    Student student1= NULL;
    char *first_name= NULL;
    char *last_name= NULL;
    studentResult=createStudent(&student1,11111111,first_name,"nassar");
    ASSERT_TEST(studentResult == STUDENT_INVALID_PARAMETERS );
    first_name="omar";
    studentResult=createStudent(&student1,11111111,first_name,last_name);
    ASSERT_TEST(studentResult == STUDENT_INVALID_PARAMETERS);
    studentResult=createStudent(&student1,1000000000,"omar","nassar");
    ASSERT_TEST(studentResult== STUDENT_INVALID_PARAMETERS);
    studentResult=createStudent(&student1,-4,"omar","nassar");
    ASSERT_TEST(studentResult== STUDENT_INVALID_PARAMETERS);
    studentResult=createStudent(&student1,0,"omar","nassar");
    ASSERT_TEST(studentResult== STUDENT_INVALID_PARAMETERS);
    studentResult=createStudent(&student1,11111111,"omar","nassar");
    ASSERT_TEST(studentResult== STUDENT_SUCCESS);
    char *student1_first_name=studentGetFirstName(student1);
    char *student1_last_name=studentGetLastName(student1);
    ASSERT_TEST(strcmp("omar",student1_first_name)==0);
    ASSERT_TEST(strcmp("nassar",student1_last_name)==0);
    ASSERT_TEST(studentGetId(student1)==11111111);
    free(student1_first_name);
    free(student1_last_name);
    destroyStudent(student1);
    return true;
}

static Student initStudent(){
    Student student1;
    StudentResult studentResult=createStudent(&student1,11111111,"omar",
                                                 "cohen");
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    return student1;
}

static Student initStudent2(){
    Student student1=initStudent();
    StudentResult studentResult= studentAddGradeSheet(student1,1,104012,"5.5",84);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1,104167,"5.0",
                                       43);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1,104167,"5.0",
                                       71);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1,234114,"4",
                                       88);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1,234145,"3",
                                       98);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1,394808,"1",
                                       92);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,104013,"5.5",
                                       66);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,104013,"5.5",
                                       63);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,114071,"3.5",
                                       98);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,234118,"3.0",
                                       98);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,234122,"3.0",
                                       28);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,234122,"3.0",
                                       96);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,234141,"3.0",
                                       73);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,2,394806,"1.0",
                                       96);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,3,94412,"4.0",
                                       80);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,3,104134,"2.5",
                                       82);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,3,134058,"3.0",
                                       70);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,3,234218,"3.0",
                                       75);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,3,234262,"3.0",
                                       94);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,3,234293,"4.0",
                                       71);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,3,394902,"1.5",
                                       96);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,125001,"3.0",
                                       69);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,134020,"3.5",
                                       56);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,134020,"3.5",
                                       76);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,234123,"4.5",
                                       94);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,234247,"3.0",
                                       95);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,234267,"3.0",
                                       60);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,234267,"3.0",
                                       68);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,236353,"3.0",
                                       78);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,4,394902,"1.5",
                                       92);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,234107,"4.0",
                                       51);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,234107,"4.0",
                                       63);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,234900,"2.0",
                                       74);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,236327,"3.0",
                                       77);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,236334,"3.0",
                                       64);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,236334,"3.0",
                                       68);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,236343,"3.0",
                                       80);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,236360,"3.0",
                                       71);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,324440,"2.0",
                                       79);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,5,394902,"1.5",
                                       97);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,6,94591,"3.5",
                                       86);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,6,234319,"3.0",
                                       93);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,6,236370,"3.0",
                                       90);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,6,236504,"3.0",
                                       89);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,6,236604,"2.0",
                                       65);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,6,236653,"3.0",
                                       87);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,6,324290,"2.0",
                                       73);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,6,394902,"1.5",
                                       93);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,7,104174,"3.5",
                                       25);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,7,104174,"3.5",
                                       90);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,7,236350,"3.0",
                                       84);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,7,236503,"3.0",
                                       71);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,7,236603,"2.0",
                                       71);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,7,236703,"3.0",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentAddGradeSheet(student1,7,394902,"1.5",
                                       98);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentRemoveGradeSheet(student1,125001,4);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    return student1;
}

static bool testCopyStudent(){
    Student student1=initStudent();
    Student student1_copy=copyStudent(student1);
    char *student1_first_name=studentGetFirstName(student1);
    char *student1_last_name=studentGetLastName(student1);
    char *student1_copy_first_name=studentGetFirstName(student1_copy);
    char *student1_copy_last_name=studentGetLastName(student1_copy);
    ASSERT_TEST(strcmp(student1_copy_first_name,student1_first_name)==0);
    ASSERT_TEST(strcmp(student1_copy_last_name,student1_last_name)==0);
    ASSERT_TEST(studentGetId(student1_copy)==studentGetId(student1));
    ASSERT_TEST(studentGetId(student1_copy)==studentGetId(student1));
    destroyStudent(student1);
    ASSERT_TEST(strcmp(student1_copy_first_name,student1_first_name)==0);
    ASSERT_TEST(strcmp(student1_copy_last_name,student1_last_name)==0);
    destroyStudent(student1_copy);
    free(student1_copy_first_name);
    free(student1_copy_last_name);
    free(student1_last_name);
    free(student1_first_name);
    return true;
}

static bool testStudentGradeSheetAddAndRemove(){
    Student student1=initStudent();
    StudentResult studentResult=studentAddGradeSheet
    		(student1,-1,234122,"5",100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,-1,"5",100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,-1,234122,"5",
                                                     100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,1000000000,"5",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,234122,"5",
                                       -4);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,234122,"5",
                                       500);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,234122,"5..",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,234122,"5.3.5",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,234122,"5.25",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentAddGradeSheet(student1,1,234122,"-5.25",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentAddGradeSheet(student1,1,234122,"5*25",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentAddGradeSheet(student1,1718,234122,"5.5",
                                       90);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1718,234141,"5.0",
                                       10);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1718,234118,"5",
                                       70);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentAddGradeSheet(student1,1718,234122,"5.5",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentRemoveGradeSheet(student1,1111,1718);
    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
    studentResult=studentRemoveGradeSheet(student1,234122,1713);
    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
    studentResult=studentRemoveGradeSheet(student1,1111,1713);
    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
    studentResult=studentRemoveGradeSheet(student1,234122,1718);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    GradeSheet student1_gradeSheet=NULL;
    studentResult=studentAddGradeSheet(student1,1,-1,"5",
                                       100);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentGetMaxGradeInCourse(student1,234122,&student1_gradeSheet);
    ASSERT_TEST(gradeSheetGetCourseGrade(student1_gradeSheet)==90);
    studentResult=studentRemoveGradeSheet(student1,234122,1718);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentRemoveGradeSheet(student1,234112,1718);
    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
    studentResult=studentRemoveGradeSheet(student1,234118,1718);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentRemoveGradeSheet(student1,234141,1718);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    destroyStudent(student1);
    removeGradeSheet(student1_gradeSheet);
    return true;
}

static bool testStudentUpdateGradeSheet(){
    Student student1=initStudent2();
    StudentResult studentResult=studentUpdateGradeSheet(student1,394902,900);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentUpdateGradeSheet(student1,394902,-1);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentUpdateGradeSheet(student1,311102,-9);
    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
    studentResult=studentUpdateGradeSheet(student1,311102,9);
    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
    studentResult=studentUpdateGradeSheet(student1,394902,100);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentUpdateGradeSheet(student1,394902,19);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    destroyStudent(student1);
    return true;
}

static bool testStudentGetFirstName(){
    //already Tested
    return true;
}

static bool testStudentGetLastName(){
    //already Tested
    return true;
}

static bool testStudentGetId(){
    //already Tested
    return true;
}

static bool testStudentReportFull(){
    Student student1=initStudent2();
    StudentResult report_result=studentReportFull(student1,NULL);
    ASSERT_TEST(report_result==STUDENT_INVALID_PARAMETERS);
    report_result=studentReportFull(student1,stdout);
    ASSERT_TEST(report_result==STUDENT_SUCCESS);
    destroyStudent(student1);
    return true;
     }

static bool testStudentReportClean(){
    Student student1=initStudent2();
    StudentResult report_result=studentReportClean(student1,NULL);
    ASSERT_TEST(report_result==STUDENT_INVALID_PARAMETERS);
    report_result=studentReportClean(student1,stdout);
    ASSERT_TEST(report_result==STUDENT_SUCCESS);
    destroyStudent(student1);
    return true;
}

static bool testStudentReportBest(){
    Student student1=initStudent2();
    StudentResult studentResult=studentReportBest(student1,-1,stdout);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentReportBest(student1,7,NULL);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentReportBest(student1,3,stdout);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    destroyStudent(student1);
    return true;
}

static bool testStudentReportWorst(){
    Student student1=initStudent2();
    StudentResult studentResult=studentReportWorst(student1,-1,stdout);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentReportWorst(student1,7,NULL);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentReportWorst(student1,3,stdout);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    destroyStudent(student1);
    return true;
}

static bool testStudentFacultyRequest() {
    Student student1 = initStudent();
    StudentResult studentResult=studentFacultyRequest(student1,104164,
                                                      "remove_course",stdout);

    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
     studentResult=studentFacultyRequest(student1,104164,
                                                      "invalid_request",stdout);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);

    studentResult=studentAddGradeSheet(student1,1,104167,"5.0",
                                       43);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentFacultyRequest(student1,104167,
                                        "invalid_request",stdout);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    studentResult=studentAddGradeSheet(student1,1,104167,"5.0",
                                       71);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);

    studentResult=studentFacultyRequest(student1,104167,
                                                     "remove_course",stdout);
   ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentRemoveGradeSheet(student1,104167,1);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
     studentResult=studentFacultyRequest(student1,104167,
                                                      "course_remove",stdout);
    ASSERT_TEST(studentResult==STUDENT_INVALID_PARAMETERS);
    /*  this should print "Faculty response: your request was rejected" */
    studentResult=studentFacultyRequest(student1,104167,
                                        "cancel_course",stdout);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    /*  this should print "Faculty response: your request was rejected" */
    studentResult=studentFacultyRequest(student1,104167,
                                        "register_course",stdout);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    /*  this should print "Faculty response: your request was rejected" */
    studentResult=studentRemoveGradeSheet(student1,104167,1);
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    studentResult=studentFacultyRequest(student1,1, "remove_course",stdout);
    ASSERT_TEST(studentResult==STUDENT_COURSE_DOES_NOT_EXIST);
    destroyStudent(student1);
    return true;
}

static bool testStudentDestroy(){
    //already tested
    return true;
}

int main(){
    RUN_TEST(testCreateStudent);
    RUN_TEST(testCopyStudent);
    RUN_TEST(testStudentGradeSheetAddAndRemove);
    RUN_TEST(testStudentUpdateGradeSheet);
    RUN_TEST(testStudentGetFirstName);
    RUN_TEST(testStudentGetLastName);
    RUN_TEST(testStudentGetId);
    RUN_TEST(testStudentReportFull);
    RUN_TEST(testStudentReportClean);
    RUN_TEST(testStudentReportBest);
    RUN_TEST(testStudentReportWorst);
    RUN_TEST(testStudentFacultyRequest);
    RUN_TEST(testStudentDestroy);
    return 0;
}
