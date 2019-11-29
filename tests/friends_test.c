/*
 * friend_test.c
 *
 *  Created on: Jan 1, 2018
 *      Author: Reham
 */

#include "../set.h"
#include "../friends.h"
#include "test_utilities.h"
#include <string.h>
#include <malloc.h>

Friends initilizeFriends(){
	Student student=NULL;
	StudentResult  studentResult=
			createStudent(&student,11111111,"omar","nassar");
    ASSERT_TEST(studentResult== STUDENT_SUCCESS);
    ASSERT_TEST(student!= NULL);

	Friends friends =NULL;
	FriendsResult create_result= friendsCreate(student,&friends);
	ASSERT_TEST(create_result== FRIENDS_SUCCESS);
	return friends;
}

static bool testCreateFriends(){
	Student student=NULL;
	StudentResult  studentResult=
			createStudent(&student,11111111,"omar","nassar");
    ASSERT_TEST(studentResult== STUDENT_SUCCESS);
	Friends friends =NULL;
	FriendsResult create_result= friendsCreate(NULL,&friends);
	ASSERT_TEST(create_result== FRIENDS_INVALID_PARAMETERS);
	create_result= friendsCreate(student,NULL);
	ASSERT_TEST(create_result== FRIENDS_INVALID_PARAMETERS);
	create_result= friendsCreate(student,&friends);
	ASSERT_TEST(create_result== FRIENDS_SUCCESS);
	destroyStudent(student);
	destroyFriends(friends);
	return true;
}

static bool testAddFriend(){
	Friends new_friends=initilizeFriends();
    ASSERT_TEST(new_friends != NULL);
	Student student=NULL;
	StudentResult  studentResult=
			createStudent(&student,11111111,"nissan","israel");
    ASSERT_TEST(studentResult== STUDENT_SUCCESS);
    ASSERT_TEST(student!= NULL);
    FriendsResult add_result= friendsAddFriend(new_friends,student);
    ASSERT_TEST(add_result== FRIENDS_SUCCESS);
    add_result= friendsAddFriend(new_friends,student);
    ASSERT_TEST(add_result== FRIENDS_ALREADY_FRIEND);
    Student current=friendsGetStudent(new_friends);
    char* first_name=studentGetFirstName(current);
    ASSERT_TEST(strcmp(first_name,"omar")==0);
    free (first_name);
	destroyStudent(current);
	destroyStudent(student);
	destroyFriends(new_friends);
	return true;
}

static bool testFriendsGetStudent(){
	Friends new_friends=initilizeFriends();
	Student current=friendsGetStudent(new_friends);
	char* first_name=studentGetFirstName(current);
	ASSERT_TEST(strcmp(first_name,"omar")==0);
    free (first_name);
	destroyStudent(current);
	destroyFriends(new_friends);
	return true;
}

static bool testRemoveFriends(){
	Friends new_friends=initilizeFriends();
	    ASSERT_TEST(new_friends != NULL);
		Student student=NULL;
		StudentResult  studentResult=
				createStudent(&student,11111111,"nissan","israel");
	    ASSERT_TEST(studentResult== STUDENT_SUCCESS);
	    ASSERT_TEST(student!= NULL);
	    FriendsResult add_result= friendsAddFriend(new_friends,student);
	    ASSERT_TEST(add_result== FRIENDS_SUCCESS);
	    add_result= friendsAddFriend(new_friends,student);
	    ASSERT_TEST(add_result== FRIENDS_ALREADY_FRIEND);
	    Student current=friendsGetStudent(new_friends);
	    friendsRemoveFriend(new_friends,student);
	     add_result= friendsAddFriend(new_friends,student);
	    ASSERT_TEST(add_result== FRIENDS_SUCCESS);
		destroyStudent(current);
		destroyStudent(student);
		destroyFriends(new_friends);
		return true;
}

static bool testFriendsPrintReference() {
    Friends new_friends = initilizeFriends();
    ASSERT_TEST(new_friends != NULL);
    Student student1 = NULL, student2 = NULL, student3 = NULL, student4 = NULL;
    StudentResult studentResult =
            createStudent(&student1, 3, "jeje", "israel");
    ASSERT_TEST(studentResult == STUDENT_SUCCESS);
    studentResult = createStudent(&student2, 221, "soso", "electric");
    ASSERT_TEST(studentResult == STUDENT_SUCCESS);
    studentResult = createStudent(&student3, 1, "nina", "homework");
    ASSERT_TEST(studentResult == STUDENT_SUCCESS);
    studentResult = createStudent(&student4, 441, "lana", "far");
    ASSERT_TEST(studentResult == STUDENT_SUCCESS);
    FriendsResult add_result = friendsAddFriend(new_friends, student1);
    ASSERT_TEST(add_result == FRIENDS_SUCCESS);
    add_result = friendsAddFriend(new_friends, student2);
    ASSERT_TEST(add_result == FRIENDS_SUCCESS);
    add_result = friendsAddFriend(new_friends, student3);
    ASSERT_TEST(add_result == FRIENDS_SUCCESS);
    add_result = friendsAddFriend(new_friends, student4);
    ASSERT_TEST(add_result == FRIENDS_SUCCESS);
    StudentResult add_grade =
            studentAddGradeSheet(student1, 8, 234122, "6.5", 95);
    ASSERT_TEST(add_grade == STUDENT_SUCCESS);
    add_grade = studentAddGradeSheet(student2, 6, 234122, "6.5", 66);
    ASSERT_TEST(add_grade == STUDENT_SUCCESS);
    add_grade = studentAddGradeSheet(student3, 1, 234122, "4.5", 95);
    ASSERT_TEST(add_grade == STUDENT_SUCCESS);
    add_grade = studentAddGradeSheet(student4, 8, 234106, "3.5", 75);
    ASSERT_TEST(add_grade == STUDENT_SUCCESS);
    printf("\n");
    FriendsResult print_result = friendsPrintReference(stdout,
                                                       new_friends, 234122, 3);
    ASSERT_TEST(print_result == FRIENDS_SUCCESS);

    studentRemoveGradeSheet(student4, 8, 234106);
    studentRemoveGradeSheet(student3, 1, 234122);
    studentRemoveGradeSheet(student2, 6, 234122);
    studentRemoveGradeSheet(student1, 8, 234122);
    Student current = friendsGetStudent(new_friends);
    destroyFriends(new_friends);
    destroyStudent(current);
    destroyStudent(student1);
    destroyStudent(student2);
    destroyStudent(student3);
    destroyStudent(student4);
    return true;
}

static bool testFriendsDestroy(){
    //already tested
    return true;
}

int main(){
	RUN_TEST(testCreateFriends);
	RUN_TEST(testAddFriend);
	RUN_TEST(testFriendsGetStudent);
	RUN_TEST(testRemoveFriends);
	RUN_TEST(testFriendsPrintReference);
	RUN_TEST(testFriendsDestroy);
	return true;
}
