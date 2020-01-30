//
// Created by mahmood on 1/1/2018.
//

#include <stdio.h>
#include "../course_manager.h"
#include "test_utilities.h"

static bool testCreateCourseManager(){
    CourseManager courseManager;
    CourseManagerResult courseManagerResult= createCourseManager(&courseManager);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
     courseManagerResult=courseManagerSendFriendRequest
            (courseManager,231455);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager,
                                                         231455,"reject");
    ASSERT_TEST(courseManagerResult== COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerAddStudent(courseManager,1,"mahmoud",
                                                "nas");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,125,"5",70);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerAddStudent(){
    CourseManager courseManager;
    CourseManagerResult courseManagerResult=createCourseManager(&courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student1","student1`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student1","student`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_ALREADY_EXISTS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,-1,"student1","student`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerAddStudent
            (courseManager,1000000000,"student1","student`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerAddStudent
            (courseManager,12,"student1","student2`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerRemoveStudent(){
    CourseManager courseManager;
    CourseManagerResult courseManagerResult=createCourseManager(&courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveStudent(courseManager,-9);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_DOES_NOT_EXIST);
    courseManagerResult=courseManagerRemoveStudent(courseManager,1000000000);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_DOES_NOT_EXIST);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student1","student1`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveStudent(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student2","student2`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveStudent(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,12,"student2","student2`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student1","student1`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveStudent(courseManager,12);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveStudent(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerStudentLogIn(){
    CourseManager courseManager;
    CourseManagerResult courseManagerResult=createCourseManager(&courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student1","student1`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_ALREADY_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,1);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_ALREADY_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,1);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_DOES_NOT_EXIST);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerStudentLogOut(){
    CourseManager courseManager;
    CourseManagerResult courseManagerResult=createCourseManager(&courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student1","student1`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static CourseManager initCourseManager(){
    CourseManager courseManager;
    CourseManagerResult courseManagerResult=createCourseManager(&courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,15456,"student1","student1`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,3333,"student2","student2`s last name");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    return courseManager;
}

static bool testCourseManagerSendFriendRequest(){
    CourseManager courseManager = initCourseManager();
    CourseManagerResult courseManagerResult=courseManagerSendFriendRequest(
            courseManager,1321212);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,-9456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_DOES_NOT_EXIST);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_ALREADY_REQUESTED);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager,15456,
                                                         "accept");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_ALREADY_FRIEND);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerHandelFriendRequest(){
    CourseManager courseManager = initCourseManager();
    CourseManagerResult courseManagerResult=courseManagerHandelFriendRequest
            (courseManager,-7,"sdsd");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerHandelFriendRequest
            (courseManager,1010,"sdsd");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_DOES_NOT_EXIST);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager,15456,
                                                         "g");
    printf("%d \n",courseManagerResult );
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_ALREADY_FRIEND);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager,15456,
                                                         "g");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager,15456,
                                                         "accept");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    /** students with ids 15456 and 3333 are now friends */
    courseManagerResult=courseManagerHandelFriendRequest
            (courseManager,3333,"sdsd");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_ALREADY_FRIEND);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerStudentUnfriend(){
    CourseManager courseManager = initCourseManager();
    CourseManagerResult courseManagerResult=courseManagerStudentUnfriend
            (courseManager,18541);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentUnfriend
            (courseManager,18541);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_DOES_NOT_EXIST);
    courseManagerResult=courseManagerStudentUnfriend
            (courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_NOT_FRIEND);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager,15456,
                                                         "g");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager,15456,
                                                         "accept");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    /** students with ids 15456 and 3333 are now friends */
    courseManagerResult=courseManagerStudentUnfriend
            (courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentUnfriend
            (courseManager,3333);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_NOT_FRIEND);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerAddAndRemoveGradeSheet(){
    CourseManager courseManager = initCourseManager();
    CourseManagerResult courseManagerResult=  courseManagerAddGradeSheet
            (courseManager,-1, 234122,"5",100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn
            (courseManager,15456);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=  courseManagerAddGradeSheet(courseManager,-1,
                                                     234122,"5",100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,-1,"5",100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,-1,234122,"5",
                                       100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,1000000000
            ,"5", 100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122,"5",
                                       -4);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122,"5",
                                       500);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122,"5..",
                                       100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122,"v5"
                                                           ".3.5", 100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122, "5"
                                                           ".25", 100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122,
                                                   "-5.25", 100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122,
                                                   "5*25", 100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1718,234122,
                                                   "5.5", 90);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1718,234141
            ,"5.0", 10);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1718,234118,
                                                   "5", 70);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1718,234122,
                                                   "5.5", 100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,1111,1718);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,234122
            ,1713);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,1111,1713);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,234122
            ,1718);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,-1,100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,
                                                      234122,1718);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,
                                                      234112,1718);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,
                                                      234118,1718);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,
                                                      234141,1718);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static CourseManager initCourseManager2(){
    CourseManager courseManager;
    CourseManagerResult courseManagerResult=createCourseManager(&courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,111111118,"Ariel","Wershal");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddStudent
            (courseManager,222222226,"Eran","Channover");
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerSendFriendRequest(courseManager,222222226);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,222222226);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerHandelFriendRequest(courseManager
            ,111111118, "accept");
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234122
            ,"3.0", 100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult= courseManagerAddGradeSheet(courseManager,1,104012,"5.5"
            ,84);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,104167,"5.0",
                                                   43);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,104167,"5.0",
                                                   71);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234114,"4",
                                                   88);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,234145,"3",
                                                   98);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,1,394808,"1",
                                                   92);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,104013,"5.5",
                                                   66);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,104013,"5.5",
                                                   63);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,114071,"3.5",
                                                   98);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,234118,"3.0",
                                                   98);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,234122,"3.0",
                                                   28);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,234122,"3.0",
                                                   96);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,234141,"3.0",
                                                   73);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,2,394806,"1.0",
                                                   96);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,3,94412,"4.0",
                                                   80);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,3,104134,"2.5",
                                                   82);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,3,134058,"3.0",
                                                   70);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,3,234218,"3.0",
                                                   75);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,3,234262,"3.0",
                                                   94);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,3,234293,"4.0",
                                                   71);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,3,394902,"1.5",
                                                   96);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,125001,"3.0",
                                                   69);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,134020,"3.5",
                                                   56);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,134020,"3.5",
                                                   76);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,234123,"4.5",
                                                   94);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,234247,"3.0",
                                                   95);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,234267,"3.0",
                                                   60);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,234267,"3.0",
                                                   68);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,236353,"3.0",
                                                   78);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,4,394902,"1.5",
                                                   92);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,234107,"4.0",
                                                   51);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,234107,"4.0",
                                                   63);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,234900,"2.0",
                                                   74);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,236327,"3.0",
                                                   77);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,236334,"3.0",
                                                   64);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,236334,"3.0",
                                                   68);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,236343,"3.0",
                                                   80);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,236360,"3.0",
                                                   71);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,324440,"2.0",
                                                   79);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,5,394902,"1.5",
                                                   97);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,94591,"3.5",
                                                   86);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,234319,"3.0",
                                                   93);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,236370,"3.0",
                                                   90);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,236504,"3.0",
                                                   89);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,236604,"2.0",
                                                   65);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,236653,"3.0",
                                                   87);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,324290,"2.0",
                                                   73);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,6,394902,"1.5",
                                                   93);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerAddGradeSheet(courseManager,7,104174,"3.5",
                                                   25);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,7,104174,"3.5",
                                                   90);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,7,236350,"3.0",
                                                   84);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,7,236503,"3.0",
                                                   71);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,7,236603,"2.0",
                                                   71);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,7,236703,"3.0",
                                                   44);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);

    courseManagerResult=courseManagerAddGradeSheet(courseManager,7,394902,"1.5",
                                                   98);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerRemoveGradeSheet(courseManager,125001,4);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,236703,100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    return courseManager;
}

static bool testCourseManagerUpdateGradeSheet(){
    CourseManager courseManager=initCourseManager2();
    CourseManagerResult courseManagerResult=
            courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,394902,-1);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,394902,900);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,394902,-1);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,311102,-9);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,311102,9);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,394902,100);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerUpdateGradeSheet(courseManager,394902,19);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerReportFull(){
    CourseManager courseManager=initCourseManager2();
    CourseManagerResult courseManagerResult=
            courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportFull(courseManager,NULL);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportFull(courseManager,NULL);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerReportFull(courseManager,stdout);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerReportClean(){
    CourseManager courseManager=initCourseManager2();
    CourseManagerResult courseManagerResult=
            courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportClean(courseManager,NULL);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportClean(courseManager,NULL);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerReportClean(courseManager,stdout);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerReportBest(){
    CourseManager courseManager=initCourseManager2();
    CourseManagerResult courseManagerResult=
            courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportBest(courseManager,NULL,-9);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportBest(courseManager,stdout,-1);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerReportBest(courseManager,NULL,7);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerReportBest(courseManager,stdout,3);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerReportWorst(){
    CourseManager courseManager=initCourseManager2();
    CourseManagerResult courseManagerResult=
            courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportWorst(courseManager,NULL,-9);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult=courseManagerReportWorst(courseManager,stdout,-1);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerReportWorst(courseManager,NULL,7);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult=courseManagerReportWorst(courseManager,stdout,3);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerPrintReference(){
    CourseManager courseManager = initCourseManager2();
    CourseManagerResult courseManagerResult =
            courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerPrintReference(courseManager, 104164,
                                                     2, stdout);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerPrintReference(courseManager, 104164,
                                                      2, NULL);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult = courseManagerPrintReference(courseManager, 234122,
                                                      3, stdout);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    destroyCourseManager(courseManager);
    return true;
}

static bool testCourseManagerFacultyRequest() {
    CourseManager courseManager = initCourseManager2();
    CourseManagerResult courseManagerResult =
            courseManagerStudentLogOut(courseManager);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerFacultyRequest(courseManager, 104164,
                                                      "remove_course", stdout);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_STUDENT_NOT_LOGGED_IN);
    courseManagerResult=courseManagerStudentLogIn(courseManager,111111118);
    ASSERT_TEST(courseManagerResult==COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerFacultyRequest(courseManager, 104164,
                                                      "invalid_request",
                                                      stdout);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_INVALID_PARAMETER);

    courseManagerResult = courseManagerAddGradeSheet(courseManager, 1, 104167,
                                                     "5.0",
                                                     43);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerFacultyRequest(courseManager, 104167,
                                                      "invalid_request",
                                                      stdout);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_INVALID_PARAMETER);
    courseManagerResult = courseManagerAddGradeSheet(courseManager, 1, 104167,
                                                     "5.0",
                                                     71);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);

    courseManagerResult = courseManagerFacultyRequest(courseManager, 104167,
                                                      "remove_course", stdout);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerRemoveGradeSheet(courseManager, 104167,
                                                        1);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerFacultyRequest(courseManager, 104167,
                                                      "course_remove", stdout);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_INVALID_PARAMETER);
    /*  this should print "Faculty response: your request was rejected" */
    courseManagerResult = courseManagerFacultyRequest(courseManager, 104167,
                                                      "cancel_course", stdout);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    /*  this should print "Faculty response: your request was rejected" */
    courseManagerResult = courseManagerFacultyRequest(courseManager, 104167,
                                                      "register_course",
                                                      stdout);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    /*  this should print "Faculty response: your request was rejected" */
    courseManagerResult = courseManagerRemoveGradeSheet(courseManager, 104167,
                                                        1);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_SUCCESS);
    courseManagerResult = courseManagerFacultyRequest(courseManager, 1,
                                                      "remove_course", stdout);
    ASSERT_TEST(courseManagerResult == COURSE_MANAGER_COURSE_DOES_NOT_EXIST);
    destroyCourseManager(courseManager);
    return true;
}

static bool testDestroyCourseManager() {
    //already tested
    return true;
}
int main() {
    RUN_TEST(testCreateCourseManager);
    RUN_TEST(testCourseManagerAddStudent);
    RUN_TEST(testCourseManagerRemoveStudent);
    RUN_TEST(testCourseManagerStudentLogIn);
    RUN_TEST(testCourseManagerStudentLogOut);
    RUN_TEST(testCourseManagerSendFriendRequest);
    RUN_TEST(testCourseManagerHandelFriendRequest);
    RUN_TEST(testCourseManagerStudentUnfriend);
    RUN_TEST(testCourseManagerAddAndRemoveGradeSheet);
    RUN_TEST(testCourseManagerUpdateGradeSheet);
    RUN_TEST(testCourseManagerReportFull);
    RUN_TEST(testCourseManagerReportClean);
    RUN_TEST(testCourseManagerReportBest);
    RUN_TEST(testCourseManagerReportWorst);
    RUN_TEST(testCourseManagerPrintReference);
    RUN_TEST(testCourseManagerFacultyRequest);
    RUN_TEST(testDestroyCourseManager);
}
