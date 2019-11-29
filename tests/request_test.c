//
// Created by mahmood on 12/28/2017.
//
#include <stdio.h>
#include "test_utilities.h"
#include "../request.h"

static Student initStudent1(){
    Student student1;
    StudentResult studentResult=createStudent(&student1,11111111,"omar",
                                              "cohen");
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    return student1;
}

static Student initStudent2(){
    Student student1;
    StudentResult studentResult=createStudent(&student1,22222222,"mahmoud",
                                              "nassar");
    ASSERT_TEST(studentResult==STUDENT_SUCCESS);
    return student1;
}

static bool testCreateRequest(){
    Student student1=initStudent1();
    Student student2=initStudent2();
    Request request1;
    RequestResult requestResult=createRequest(&request1,NULL,student2);
    ASSERT_TEST(requestResult==REQUEST_NULL_PARAMETER);
    requestResult=createRequest(&request1,student1,NULL);
    ASSERT_TEST(requestResult==REQUEST_NULL_PARAMETER);
    requestResult=createRequest(&request1,NULL,NULL);
    ASSERT_TEST(requestResult==REQUEST_NULL_PARAMETER);
    requestResult=createRequest(&request1,student1,student2);
    ASSERT_TEST(requestResult==REQUEST_SUCCESS);
    requestDestroy(request1);
    destroyStudent(student1);
    destroyStudent(student2);
    return true;
}

static bool testCompareRequests(){
    Student student1=initStudent1();
    Student student2=initStudent2();
    Request request1,request2,request3;
    RequestResult requestResult=createRequest(&request1,student1,student2);
    ASSERT_TEST(requestResult==REQUEST_SUCCESS);
    requestResult=createRequest(&request2,student1,student2);
    ASSERT_TEST(requestResult==REQUEST_SUCCESS);
    requestResult=createRequest(&request3,student2,student1);
    ASSERT_TEST(requestResult==REQUEST_SUCCESS);
    ASSERT_TEST(requestCompareRequests(request1,request2)==1);
    ASSERT_TEST(requestCompareRequests(request2,request1)==1);
    ASSERT_TEST(requestCompareRequests(request2,request3)!=1);
    ASSERT_TEST(requestCompareRequests(request1,request3)!=1);
    requestDestroy(request1);
    requestDestroy(request2);
    requestDestroy(request3);
    destroyStudent(student1);
    destroyStudent(student2);
    return true;
}

static bool testRequestCopy(){
    Student student1=initStudent1();
    Student student2=initStudent2();
    Request request1,request2;
    RequestResult requestResult=createRequest(&request1,student1,student2);
    ASSERT_TEST(requestResult==REQUEST_SUCCESS);
    request2=requestCopy(request1);
    ASSERT_TEST(request2!=  NULL);
    requestDestroy(request1);
    requestDestroy(request2);
    destroyStudent(student1);
    destroyStudent(student2);
    return true;
}

static bool testRequestDestroy(){
    //already tested
    return true;
}

int main(){
    RUN_TEST(testCreateRequest);
    RUN_TEST(testCompareRequests);
    RUN_TEST(testRequestCopy);
    RUN_TEST(testRequestDestroy);
    return 0;
}