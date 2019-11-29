//
// Created by mahmood on 12/29/2017.
//
#include <assert.h>
#include "course_manager.h"
#include "set.h"
#include "friends.h"
#include "request.h"
#include <malloc.h>
#include "string.h"


#define MIN_STUDENT_ID  1
#define MAX_STUDENT_ID  999999999

struct courseManager_t {
    Student current;
    Set students;
    Set requests;
    Set friends;
};
/**************************** static functions declaration ***************/
/**
 * assumes that courseManager is not NULL
 * returns the student that is in the system and have id equals to student id
 * ,if no student was found return NULL
 * @param courseManager-the system described above
 * @param student_id -id of the student to return
 */
static Student getStudentById(CourseManager courseManager,int student_id);
/** assumes that courseManger is not NULL
 * handel some errors that could occur in handling a friend request
 * @param courseManager-system which contains the two student described above
 * @param sender- student who sent the request that should be
 * handle
 * @return COURSE_MANAGER_ALREADY_LOGGED_IN- if student with same id as
 * student_id was logged in
 * COURSE_MANAGER_STUDENT_DOES_NOT_EXIST-if no student with id equals
 * to sender_id was found
 * COURSE_MANAGER_ALREADY_FRIEND- if the student with sender_id and the
 * connected are already friends, or the connected student`s id equals to
 * sender_id
 * COURSE_MANAGER_SUCCESS
 */
static CourseManagerResult courseManagerHandelFriendRequestErrors(CourseManager
                                  courseManager,Student sender);
/**
 * return ture if student1 is a friend with student2
 * @param courseManager- the system which contains the two students
 * @param student1- student to check id he is a friend with student 2
 * @param student2- student to check id he is a friend with student 1
 */
static bool courseManagerCheckIfFriends(CourseManager courseManager,Student
                                    student1,Student student2);
/** assumes that courseManager is not NULL, and both student1 and student2
 * exists in the system
 * adds student1 and student2 as a friends , and removes all the requests
 * sent from the connected student1 to student2
 * @param courseManager-system which contains the two student described above
 * @param student1- student to add as a friend to student2
 * @param student2- student to add as a friend to student1
 */
static void courseManagerStudentAddFriend(CourseManager courseManager,
                                          Student student1,Student student2);
/** assumes that courseManager is nor NULL
* Erases all the friends connections and the requests between
* student_to_remove and all other students in the system
* @param courseManager- the system described above
* @param student_to_remove-student to remove his connections
*/
static void RemoveStudentConnections(CourseManager courseManager,Student
        student_to_remove);
/** assumes that student1 and student2 are not NULL
 * @param student1-first student to compare
 * @param student2-second student to compare
 * @return  A positive integer student1 is greater;
 * 0 if they're equal;
 * A negative integer student2 is greater.
 */
static int courseManagerCompareStudent(SetElement student1,SetElement student2);
/**
 * copies a student
 * @param student1-student to copy
 * @return NULL in case of bad allocation
 */
static SetElement courseManagerCopyStudent(SetElement student1);
/**
 * deallocates a student
 * @param student1-student to deallocate
 */
static void courseManagerFreeStudent(SetElement student1);
/** assumes that Request1 and Request2 are not NULL
 * @param Request1-first student to compare
 * @param Request2-second student to compare
 * @return  A positive integer Request1 is greater;
 * 0 if they're equal;
 * A negative integer Request2 is greater.
 */
static int courseManagerCompareRequest(SetElement request1,SetElement request2);
/**
 * copies a Request
 * @param Request-Request to copy
 * @return NULL in case of bad allocation
 */
static SetElement courseManagerCopyRequest(SetElement request);
/**
 * deallocates a Request
 * @param Request-Request to deallocate
 */
static void courseManagerFreeRequest(SetElement request);
/** assumes that Friends1 and Friends2 are not NULL
 * @param Friends1-first student to compare
 * @param Friends2-second student to compare
 * @return  A positive integer Friends1 is greater;
 * 0 if they're equal;
 * A negative integer Friends2 is greater.
 */
static int courseManagerCompareFriends(SetElement friends1,SetElement friends2);
/**
 * copies a Friends
 * @param Friends1-Friends1 to copy
 * @return NULL in case of bad allocation
 */
static SetElement courseManagerCopyFriends(SetElement friends1);
/**
 * deallocates a Friends
 * @param Friends1-Friends to deallocate
 */
static void courseManagerFreeFriends(SetElement friends1);
/**************************** static functions implementation ************/
/*************************************************************************/
static Student getStudentById(CourseManager courseManager,int student_id){
    assert(courseManager!=NULL);
    SET_FOREACH(Student,current_student,courseManager->students){
        if (studentGetId(current_student)==student_id){
            return current_student;
        }
    }
    return NULL;
}

static void RemoveStudentConnections(CourseManager courseManager,Student
                    student_to_remove){
    assert(courseManager!=NULL);
    SET_FOREACH(Friends,current_friends,courseManager->friends){
        friendsRemoveFriend(current_friends,student_to_remove);
        if (!courseManagerCompareStudent(student_to_remove,friendsGetStudent
                (current_friends))){
            setRemove(courseManager->friends,current_friends);
        }
    }
    SET_FOREACH(Request,current_request,courseManager->requests){
        if (!courseManagerCompareStudent(student_to_remove,requestGetReceiver
           (current_request))||!courseManagerCompareStudent
              (student_to_remove,requestGetSender(current_request))){
            setRemove(courseManager->requests,current_request);
        }
    }
}
static void courseManagerStudentAddFriend(CourseManager courseManager,
                                          Student student1,Student student2){
    assert(courseManager!=NULL);
    SET_FOREACH(Request,current_request,courseManager->requests){
        if (!courseManagerCompareStudent(requestGetSender(current_request),
           student1)&&!courseManagerCompareStudent(requestGetReceiver
               (current_request),student2)){
            setRemove(courseManager->requests,current_request);
        }
    }
    SET_FOREACH(Friends,current_friends,courseManager->friends){
        if (!courseManagerCompareStudent(friendsGetStudent(current_friends),
                                                  student1)){
            friendsAddFriend(current_friends,student2);
        }
        if (!courseManagerCompareStudent(friendsGetStudent(current_friends),
                                         student2)){
            friendsAddFriend(current_friends,student1);
        }
    }
}
static CourseManagerResult courseManagerHandelFriendRequestErrors(CourseManager
                                courseManager,Student sender){
    assert(courseManager!=NULL);
    if (!courseManager->current) return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;

    if (sender == NULL) return COURSE_MANAGER_STUDENT_DOES_NOT_EXIST;
    if (courseManagerCheckIfFriends(courseManager,courseManager->current
            ,sender)) {
        return COURSE_MANAGER_ALREADY_FRIEND;
    }
    return COURSE_MANAGER_SUCCESS;
}

static bool courseManagerCheckIfFriends(CourseManager courseManager,Student
                                            student1, Student student2){
    assert(courseManager != NULL && student1 != NULL && student2 != NULL);
    if (studentGetId(student1)==studentGetId(student2)){
        return true;
    }
    int id1 = studentGetId(student1);
    SET_FOREACH(Friends, current_friends, courseManager->friends) {
        if (studentGetId(friendsGetStudent(current_friends)) == id1) {
            FriendsResult friendsResult = friendsAddFriend(current_friends,
                                                           student2);
            if (friendsResult == FRIENDS_ALREADY_FRIEND) {
                return 1;
            }
            if (friendsResult==FRIENDS_SUCCESS){
                friendsRemoveFriend(current_friends,student2);
            }
        }
    }
    return 0;
}

static int courseManagerCompareStudent(SetElement student1,SetElement student2){
    assert(student1!=NULL && student2!=NULL);
    if (studentGetId(student1)>studentGetId(student2)) return 1;
    if (studentGetId(student1)<studentGetId(student2)) return -1;
    return 0;
}

static SetElement courseManagerCopyStudent(SetElement student1){
    if (student1==NULL) return NULL;
    return copyStudent(student1);
}

static void courseManagerFreeStudent(SetElement student1){
    destroyStudent(student1);
}

static int courseManagerCompareRequest(SetElement Request1,SetElement Request2){
    if (studentGetId(requestGetSender(Request1))>
            studentGetId(requestGetSender(Request2))){
        return 1;
    }
    if (studentGetId(requestGetSender(Request1))<
        studentGetId(requestGetSender(Request2))){
        return -1;
    }
    else {
        if (studentGetId(requestGetReceiver(Request1))>
            studentGetId(requestGetReceiver(Request2))){
            return 1;
        }
        if (studentGetId(requestGetReceiver(Request1))<
            studentGetId(requestGetReceiver(Request2))){
            return -1;
        }
    }
    return 0;
}

static SetElement courseManagerCopyRequest(SetElement request){
    if (request==NULL) return NULL;
    return requestCopy(request);
}

static void courseManagerFreeRequest(SetElement request){
    requestDestroy(request);
}

static int courseManagerCompareFriends(SetElement friends1,SetElement friends2){
    assert(friends1!=NULL && friends2!=NULL);
    return courseManagerCompareStudent(friendsGetStudent(friends1),
                                       friendsGetStudent(friends2));
}

static SetElement courseManagerCopyFriends(SetElement friends1){
    return friends1;
}

static void courseManagerFreeFriends(SetElement friends1){
    destroyFriends(friends1);
}
/************************************************************************/
/************************************************************************/
CourseManagerResult createCourseManager(CourseManager* courseManager_ptr){
    assert(courseManager_ptr!=NULL);
    CourseManager allocate_course_manager=malloc(sizeof(
                                                 *allocate_course_manager));
    if (!allocate_course_manager) return COURSE_MANAGER_OUT_OF_MEMORY;
    allocate_course_manager->current=NULL;
    allocate_course_manager->students=NULL;
    allocate_course_manager->requests=NULL;
    allocate_course_manager->friends=NULL;
    allocate_course_manager->students=setCreate(courseManagerCopyStudent,
                     courseManagerFreeStudent,courseManagerCompareStudent);
    if (allocate_course_manager->students==NULL) {
        destroyCourseManager(allocate_course_manager);
        return COURSE_MANAGER_OUT_OF_MEMORY;
    }
    allocate_course_manager->requests=setCreate(courseManagerCopyRequest,
                                                courseManagerFreeRequest,
                                                courseManagerCompareRequest);
    if (allocate_course_manager->requests==NULL) {
        destroyCourseManager(allocate_course_manager);
        return COURSE_MANAGER_OUT_OF_MEMORY;
    }
    allocate_course_manager->friends=setCreate(courseManagerCopyFriends,
                                               courseManagerFreeFriends,
                                               courseManagerCompareFriends);
    if (allocate_course_manager->friends==NULL) {
        destroyCourseManager(allocate_course_manager);
        return COURSE_MANAGER_OUT_OF_MEMORY;
    }
    *courseManager_ptr=allocate_course_manager;
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerAddStudent(CourseManager courseManager,
                                            int student_id,char *first_name,
                                            char *last_name) {
    assert(courseManager != NULL);
    Student new_student;
    StudentResult create_result = createStudent(&new_student, student_id,
                                                first_name, last_name);
    if (create_result==STUDENT_OUT_OF_MEMORY) {
        return COURSE_MANAGER_OUT_OF_MEMORY;
    }
    if (create_result==STUDENT_INVALID_PARAMETERS) {
        return COURSE_MANAGER_INVALID_PARAMETER;
    }
    SetResult add_result = setAdd(courseManager->students, new_student);
    destroyStudent(new_student);
    if (add_result==SET_OUT_OF_MEMORY) return COURSE_MANAGER_OUT_OF_MEMORY;
    if (add_result==SET_ITEM_ALREADY_EXISTS) {
        return COURSE_MANAGER_STUDENT_ALREADY_EXISTS;
    }
    Friends new_student_Friends;
    Student student = getStudentById(courseManager, student_id);
    friendsCreate(student, &new_student_Friends);
    if (!new_student_Friends) return COURSE_MANAGER_OUT_OF_MEMORY;
    if (setAdd(courseManager->friends,new_student_Friends) ==SET_OUT_OF_MEMORY){
        destroyFriends(new_student_Friends);
        return COURSE_MANAGER_OUT_OF_MEMORY;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerRemoveStudent(CourseManager courseManager,
                                               int student_id){
    assert(courseManager!=NULL);
    Student student_to_remove=NULL;
    SET_FOREACH(Student,current_student,courseManager->students){
        if (studentGetId(current_student)==student_id){
            student_to_remove=current_student;
        }
    }
    if (student_to_remove==NULL) return COURSE_MANAGER_STUDENT_DOES_NOT_EXIST;
    if (student_id > MAX_STUDENT_ID || student_id < MIN_STUDENT_ID){
        return COURSE_MANAGER_INVALID_PARAMETER;
    }
    Friends new_studen_Friends;
    friendsCreate(student_to_remove,&new_studen_Friends);
    if (!new_studen_Friends) return COURSE_MANAGER_OUT_OF_MEMORY;
    if (courseManager->current&&studentGetId(courseManager->current)
                               ==student_id){
        courseManager->current=NULL;
    }
    RemoveStudentConnections(courseManager,student_to_remove);
    setRemove(courseManager->friends,new_studen_Friends);
    destroyFriends(new_studen_Friends);
    setRemove(courseManager->students, student_to_remove);
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerStudentLogIn(CourseManager courseManager
        ,int student_id){
    assert(courseManager!=NULL);
    if (courseManager->current) return COURSE_MANAGER_ALREADY_LOGGED_IN;
    Student student_to_connect=NULL;
    SET_FOREACH(Student,current_student,courseManager->students){
        if (studentGetId(current_student)==student_id){
            student_to_connect=current_student;
        }
    }
    if (student_to_connect==NULL) return COURSE_MANAGER_STUDENT_DOES_NOT_EXIST;
    courseManager->current=student_to_connect;
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerStudentLogOut(CourseManager courseManager) {
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    courseManager->current=NULL;
    return COURSE_MANAGER_SUCCESS;
}


CourseManagerResult courseManagerSendFriendRequest(CourseManager courseManager
        ,int receiver_id) {
    if (!courseManager->current) return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    assert(courseManager != NULL);
    Student receiver = NULL;
    SET_FOREACH(Student, current_student, courseManager->students) {
        if (studentGetId(current_student) == receiver_id) {
            receiver = current_student;
        }
    }
    if (receiver == NULL) return COURSE_MANAGER_STUDENT_DOES_NOT_EXIST;
    Request new_request;
    RequestResult requestResult=createRequest(&new_request,
                                            courseManager->current, receiver);
    if (requestResult==REQUEST_OUT_OF_MEMORY) {
        return COURSE_MANAGER_OUT_OF_MEMORY;
    }
    if (courseManagerCheckIfFriends(courseManager,courseManager->current
            ,receiver)){
        requestDestroy(new_request);
        return COURSE_MANAGER_ALREADY_FRIEND;
    }
    SetResult add_result=setAdd(courseManager->requests,new_request);
    requestDestroy(new_request);
    if (add_result==SET_OUT_OF_MEMORY) return COURSE_MANAGER_OUT_OF_MEMORY;
    if (add_result==SET_ITEM_ALREADY_EXISTS){
        return COURSE_MANAGER_ALREADY_REQUESTED;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerHandelFriendRequest(CourseManager courseManager
        ,int sender_id,char* action){
    assert(courseManager!=NULL);
    Student sender = NULL;
    SET_FOREACH(Student, current_student, courseManager->students) {
        if (studentGetId(current_student) == sender_id) {
            sender = current_student;
        }
    }
    CourseManagerResult courseManagerResult=
        courseManagerHandelFriendRequestErrors(courseManager,sender);
    if (courseManagerResult!=COURSE_MANAGER_SUCCESS) return courseManagerResult;
    SET_FOREACH(Request,current_request,courseManager->requests){
        if (studentGetId(requestGetSender(current_request))==sender_id
            &&studentGetId(requestGetReceiver(current_request))
              ==studentGetId(courseManager->current)){
            if (!strcmp(action,"accept")){
                courseManagerStudentAddFriend(courseManager,sender,
                                              courseManager->current);
                return COURSE_MANAGER_SUCCESS;
            }
            else if (strcmp(action,"reject")!=0){
                return COURSE_MANAGER_INVALID_PARAMETER;
            }
            setRemove(courseManager->requests,current_request);
            return COURSE_MANAGER_SUCCESS;
        }
    }
    return COURSE_MANAGER_NOT_REQUESTED;
}

CourseManagerResult courseManagerStudentUnfriend(CourseManager courseManager,
                                                 int student2_id) {
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    Student student2 = NULL;
    SET_FOREACH(Student, current_student, courseManager->students) {
        if (studentGetId(current_student) == student2_id) {
            student2 = current_student;
        }
    }
    if (student2 == NULL) return COURSE_MANAGER_STUDENT_DOES_NOT_EXIST;
    SET_FOREACH(Friends, curreny_friends, courseManager->friends) {
        FriendsResult  remove_Result=FRIENDS_SUCCESS;
        if (studentGetId(friendsGetStudent(curreny_friends))
            == studentGetId(courseManager->current)) {
            remove_Result = friendsRemoveFriend(curreny_friends, student2);
        }
        if (studentGetId(friendsGetStudent(curreny_friends)) == student2_id) {
            remove_Result = friendsRemoveFriend(curreny_friends,
                    courseManager->current);
        }
        if (remove_Result == FRIENDS_NOT_FRIEND) {
            return COURSE_MANAGER_NOT_FRIEND;
        }
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerAddGradeSheet(CourseManager courseManager,
                                               int semester,int course_id,
                                               char* points,int grade){
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult add_result=studentAddGradeSheet(courseManager->current,
                                                  semester,course_id,points,
                                                  grade);
    if (add_result==STUDENT_OUT_OF_MEMORY) return COURSE_MANAGER_OUT_OF_MEMORY;
    if (add_result==STUDENT_INVALID_PARAMETERS){
        return COURSE_MANAGER_INVALID_PARAMETER;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerRemoveGradeSheet(CourseManager courseManager,
                                    int course_id,int semester){
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult remove_result=studentRemoveGradeSheet(courseManager->current,
                             course_id,semester);
    switch (remove_result) {
        case STUDENT_COURSE_DOES_NOT_EXIST :
            return COURSE_MANAGER_COURSE_DOES_NOT_EXIST;
        case STUDENT_INVALID_PARAMETERS :
            return COURSE_MANAGER_INVALID_PARAMETER;
        case  STUDENT_OUT_OF_MEMORY :
            return COURSE_MANAGER_OUT_OF_MEMORY;
        default:
            return COURSE_MANAGER_SUCCESS;
    }
}

CourseManagerResult courseManagerUpdateGradeSheet(CourseManager courseManager,
                                                  int course_id,
                                                  int new_grade) {
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult update_result = studentUpdateGradeSheet(
            courseManager->current, course_id, new_grade);
    switch (update_result) {
        case STUDENT_COURSE_DOES_NOT_EXIST :
            return COURSE_MANAGER_COURSE_DOES_NOT_EXIST;
        case STUDENT_INVALID_PARAMETERS :
            return COURSE_MANAGER_INVALID_PARAMETER;
        case STUDENT_OUT_OF_MEMORY:
            return COURSE_MANAGER_OUT_OF_MEMORY;
        default :
            return COURSE_MANAGER_SUCCESS;
    }
}

CourseManagerResult courseManagerReportFull(CourseManager courseManager, FILE
                *output) {
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult report_result = studentReportFull(courseManager->current,
                                                    output);
    if (report_result == STUDENT_INVALID_PARAMETERS) {
        return COURSE_MANAGER_INVALID_PARAMETER;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerReportClean(CourseManager courseManager, FILE
*output) {
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult report_result = studentReportClean(courseManager->current,
                                                     output);
    if (report_result == STUDENT_INVALID_PARAMETERS) {
        return COURSE_MANAGER_INVALID_PARAMETER;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerReportBest(CourseManager courseManager, FILE
    *output,int amount){
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult report_result = studentReportBest(courseManager->current
            ,amount,output);
    if (report_result==STUDENT_INVALID_PARAMETERS) {
            return COURSE_MANAGER_INVALID_PARAMETER;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerReportWorst(CourseManager courseManager, FILE
*output,int amount){
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult report_result = studentReportWorst(courseManager->current
            ,amount,output);
    if  (report_result==STUDENT_INVALID_PARAMETERS) {
            return COURSE_MANAGER_INVALID_PARAMETER;
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerPrintReference(CourseManager courseManager,int
                    course_id,int amount,FILE *output) {
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    Friends friends1 = NULL;
    SET_FOREACH(Friends, currnet_frineds, courseManager->friends) {
        if (studentGetId(friendsGetStudent(currnet_frineds))
            == studentGetId(courseManager->current)) {
            friends1 = currnet_frineds;
        }
    }
    if (friends1 != NULL) {
        FriendsResult report_result =
                friendsPrintReference(output,friends1,course_id,amount);
        if (report_result == FRIENDS_INVALID_PARAMETERS) {
            return COURSE_MANAGER_INVALID_PARAMETER;
        }
    }
    return COURSE_MANAGER_SUCCESS;
}

CourseManagerResult courseManagerFacultyRequest(CourseManager courseManager,
                                          int course_id, char *request,
                                          FILE* output) {
    assert(courseManager != NULL);
    if (courseManager->current == NULL) {
        return COURSE_MANAGER_STUDENT_NOT_LOGGED_IN;
    }
    StudentResult report_result = studentFacultyRequest(courseManager->current,
                                                        course_id, request,
                                                        output);
    switch (report_result) {
        case STUDENT_INVALID_PARAMETERS :
            return COURSE_MANAGER_INVALID_PARAMETER;
        case STUDENT_COURSE_DOES_NOT_EXIST :
            return COURSE_MANAGER_COURSE_DOES_NOT_EXIST;
        case STUDENT_OUT_OF_MEMORY :
            return COURSE_MANAGER_OUT_OF_MEMORY;
        default :
            return COURSE_MANAGER_SUCCESS;
    }
}

void destroyCourseManager(CourseManager courseManager){
    if (courseManager!=NULL){
        courseManager->current=NULL;
        setDestroy(courseManager->friends);
        setDestroy(courseManager->students);
        setDestroy(courseManager->requests);
    }
    free(courseManager);
}