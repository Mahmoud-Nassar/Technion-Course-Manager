
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "student.h"
#include "friends.h"
#include "set.h"
#include "mtm_ex3.h"
#define MIN_COURSE_ID   1
#define MAX_COURSE_ID   999999

struct friends_t{
	Student student;
	Set student_friends;
	
};

/*******************static functions*******************************************/
/*
* copies an existing friend
* @param: friends to be copied
* @return: a copy of the friends, NULL if friends is NULL or memory
* allocation failed
*/
static SetElement copySetStudentFriends(SetElement friend);

/*
 * frees a friend ,does nothing if friend is NULL.
 * @param: friend - friend to be freed
*/
static void freeSetStudentFriends(SetElement friend);


/*
 * compares between two existing friends by their id
 * @param: friend1, friend2 - two friends to compare
 * @return: 0 if the friends id are equal, positive number if the id of friend1
 * is greater than the id of friend2, negative number otherwise
 */
static int compareSetStudentFriends(SetElement friend1,SetElement friend2);

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

static void Get_student_info(Friends friends ,int friend_id,
		char ** first_name,char ** last_name);

static int compareListGrades(ListElement grade1, ListElement grade2,
		ListSortKey key);
static List  getMaxGrades(Friends friends,int course_id);
/*******************static functions implementation***************************/
static SetElement copySetStudentFriends(SetElement friend){
	assert(friend!=	NULL);
	return friend;
}

static void freeSetStudentFriends(SetElement friend){
}

static int compareSetStudentFriends(SetElement friend1,SetElement friend2){
	assert(friend1!=NULL && friend2!=NULL);
	Student freind_1=(Student)friend1;
	Student freind_2=(Student)friend2;
	int friend1_id=studentGetId(freind_1);
	int friend2_id=studentGetId(freind_2);
	return friend1_id-friend2_id;
}

static ListElement copyListGradeSheet(ListElement grade_sheet){
	if(grade_sheet == NULL){
		return NULL;
	}
	return CopyGradeSheet(grade_sheet);
}

static void freeListGradeSheet(ListElement grade_sheet){
	removeGradeSheet(grade_sheet);
}

static void Get_student_info(Friends friends ,int friend_id,
		char ** first_name,char ** last_name){
	assert(friends != NULL && first_name!= NULL && last_name!= NULL);
	SET_FOREACH(Student,current_student,friends->student_friends){
		if(friend_id==studentGetId(current_student)){
			*first_name= studentGetFirstName(current_student);
			*last_name= studentGetLastName(current_student);
			if(first_name == NULL || last_name==NULL){
				free(first_name);
				free(last_name);
				first_name=NULL;
				last_name=NULL;
			}
			break;
		}
	}
}

static int compareListGrades(ListElement grade1, ListElement grade2,
		ListSortKey key){
	assert(key!=NULL&&grade1!=NULL &&grade2!=NULL);
	GradeSheet  grade_1=(GradeSheet)grade1 ;
	GradeSheet	grade_2=(GradeSheet)grade2;
	int course_grade1=gradeSheetGetCourseGrade(grade_1)-0;
	int course_grade2=gradeSheetGetCourseGrade(grade_2)-0;
	if(course_grade1>course_grade2){
		return -1;
	}
	if(course_grade1==course_grade2){
		if(gradeSheetGetSemesterId(grade_1)>gradeSheetGetSemesterId(grade_2)){
			return 1;
		}
	}
	return 1;

}

static List  getMaxGrades(Friends friends,int course_id){
	assert(friends != NULL && course_id>MIN_COURSE_ID &&
				course_id<MAX_COURSE_ID);
	List max_grades=listCreate(copyListGradeSheet,freeListGradeSheet);
	if(max_grades==NULL){
		return NULL;
	}
	SET_FOREACH(Student,current_student,friends->student_friends){
		GradeSheet grade=NULL;
		studentGetMaxGradeInCourse(current_student,course_id,&grade);
		if (grade !=NULL){
			ListResult add_result= listInsertLast(max_grades,grade);
			removeGradeSheet(grade) ;
			if(add_result==LIST_OUT_OF_MEMORY){
				listDestroy(max_grades);
					return NULL;
			}
		}
	}
	int key=0;
	ListResult sort_result= listSort(max_grades,compareListGrades,&key);
	if (sort_result==LIST_OUT_OF_MEMORY){
		listDestroy(max_grades);
		return NULL;
	}
	return max_grades;
}
/*****************************************************************************/
FriendsResult friendsCreate(Student student,Friends * friends){
	if (student==NULL || friends==NULL){
		return FRIENDS_INVALID_PARAMETERS;
	}
	Friends new_friends=malloc(sizeof(*new_friends));
	if(new_friends==NULL){
		return FRIENDS_OUT_OF_MEMORY;
	}
	new_friends->student_friends=setCreate(copySetStudentFriends,
			freeSetStudentFriends,compareSetStudentFriends);
	if(new_friends->student_friends==NULL){
		destroyFriends(new_friends);
		return FRIENDS_OUT_OF_MEMORY;
	}
	new_friends->student=student;
	*friends=new_friends;
	return FRIENDS_SUCCESS;
}

FriendsResult friendsAddFriend(Friends friends,Student student){
	assert(friends != NULL && student!= NULL );
	SetResult add_result=setAdd(friends->student_friends, student);
	if(add_result==SET_ITEM_ALREADY_EXISTS){
		return FRIENDS_ALREADY_FRIEND;
	}
	if(add_result==SET_OUT_OF_MEMORY){
		return FRIENDS_OUT_OF_MEMORY;
	}
	return FRIENDS_SUCCESS;
}

FriendsResult friendsRemoveFriend(Friends friends,Student student){
	assert(friends != NULL && student!=NULL);
	SetResult remove_result= setRemove(friends->student_friends,student);
	int student_to_remove_id=studentGetId(friends->student);
	int student_remove_from_id=studentGetId(student);
	if (remove_result == SET_ITEM_DOES_NOT_EXIST ||
			student_to_remove_id==student_remove_from_id){
		return FRIENDS_NOT_FRIEND;
	}
	return SET_SUCCESS;
}

Student friendsGetStudent(Friends friends){
	assert(friends != NULL);
	return friends->student;
}

FriendsResult friendsPrintReference(FILE* output_channel,
		Friends friends,int course_id,int amount){
	assert(friends != NULL && course_id>MIN_COURSE_ID &&
			course_id<MAX_COURSE_ID);
	if (output_channel==NULL || amount <=0 ) return FRIENDS_INVALID_PARAMETERS;
	if (friends->student_friends==NULL){
		return FRIENDS_SUCCESS;
	}
	List max_grades= getMaxGrades(friends, course_id);
	if(max_grades==NULL){
		return FRIENDS_OUT_OF_MEMORY;
	}
	LIST_FOREACH(GradeSheet,current_grade,max_grades){
		if(amount==0 ){
			break;
		}
		char * first_name=NULL;
		char * last_name=NULL;
		int friend_id=gradeSheetGetStudentId(current_grade);
		Get_student_info( friends ,friend_id,
				&first_name,& last_name);
		if( first_name==NULL  && last_name==NULL ){
			listDestroy(max_grades);
			return FRIENDS_OUT_OF_MEMORY;
		}
		 mtmPrintStudentName(output_channel,first_name,last_name);
		 free(first_name);
		 free(last_name);
		amount--;
	}
	listDestroy(max_grades);
	return FRIENDS_SUCCESS;
}

Friends copyFriends(Friends friends){
    if (friends == NULL) return NULL;
    Friends new_friends;
    assert(friends->student);
    friendsCreate(friends->student, &new_friends);
    new_friends->student_friends=setCopy(friends->student_friends);
    return new_friends;
}

void destroyFriends(Friends friends){
	if(friends != NULL){
		friends->student=NULL;
        setDestroy(friends->student_friends);
	}
	free(friends);
}
