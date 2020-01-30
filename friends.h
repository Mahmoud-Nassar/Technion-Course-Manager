

#ifndef FRIENDS_H_
#define FRIENDS_H_
#include "student.h"

typedef enum {
    FRIENDS_OUT_OF_MEMORY,
    FRIENDS_INVALID_PARAMETERS,
    FRIENDS_ALREADY_FRIEND,
    FRIENDS_NOT_FRIEND,
    FRIENDS_SUCCESS,
} FriendsResult;

typedef struct friends_t *Friends;

/*
 * creates a new Friends
 * @param student -a student that we create friends for.
 * @param friends- pointer to the friends that will be created

 * @return FRIENDS_INVALID_PARAMETERS one of the parameter is null,
 * FRIENDS_OUT_OF_MEMORY if memory allocation failed,otherwise returns
 * FRIENDS_SUCCESS
*/
FriendsResult friendsCreate(Student student,Friends * friends);

/**
 * friends and student should be not NULL
 * adds student as a new friend to the friends list of student
 * @param friends - all the friends of one student
 * @param student-student to be added  as a new friend to the student's friend
 *  list
 * FRIENDS_ALREADY_FRIEND if student already exists in the
 * friends list
 * FRIENDS_OUT_OF_MEMORY if memory allocation failed
 * FRIENDS_SUCCESS if student was successfully added
 */
Student friendsGetStudent(Friends friends);

FriendsResult friendsAddFriend(Friends friends,Student student);

/**
 * friends should be not NULL
 * stop the friend ship with parameter student,in other word remove student
 * from the friends list of student
 * @param friends - the friends to be remove student from
 * @param student-student to be removed from the  parameter friends
 * FRIENDS_INVALID_PARAMETERS if student is null
 * FRIENDS_NOT_FRIEND if student does not exist in the
 * friends
 * FRIENDS_SUCCESS if student was successfully removed
 */
FriendsResult friendsRemoveFriend(Friends friends,Student student);

/**
 * prints (using mtmPrintStudentName function) the names of the students (in
 * the friends  that has the highest grades in the
 * course with id equals to parameter courser_id, number of names printed is
 * lower than or equal to amount.
 * the order of printing: student with higher grade appears
 * first ,if 2 students has the same grade , the student with the lower id
 * number appears first.
 * @param friends-student's friends
 * @param course_id-id of the course related to the search
 * @param amount- the number of names to be printed, if the number of
 * the students that had a grade in such course was lower , prints only the
 * relevant names .if no student was found with a grade in the course nothing
 * is printed.
 * @return FRIENDS_INVALID_PARAMETERS if amount < 0 ,otherwise
 * FRIENDS_SUCCESS
 */
FriendsResult friendsPrintReference(FILE* output_channel,Friends friends,
		int course_id,int amount);

/**
 * copies a friendse
 * @param friends
 * @return NULL if NULL was passed or memory problem occurred
 * a new allocated Friends otherwise
 */
Friends copyFriends(Friends friends);

/**
 * Deallocates an existing Friends.
 * @param friends- friends to be deallocated
 */
void destroyFriends(Friends friends);



#endif /* FRIENDS_H_ */
