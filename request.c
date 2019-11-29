#include "request.h"
#include <malloc.h>
#include "assert.h"
struct request_t{
	Student sender;
	Student receiver;
};
/**************************** static functions declaration ***************/
/**
 * student1 and student2 must not be NULL
 * compares two students by there id
 * @param student1-first student to be compared
 * @param student2-second student to be compared
 * @return 1 if student1 id > student2 id
 * -1 if student2 id > student1 id , 0 if the are equal
 */
int RequestCompareStudent(Student student1,Student student2);
/************************************************************************/
int RequestCompareStudent(Student student1, Student student2) {
	assert(student1 != NULL && student2 != NULL);
	if (studentGetId(student1) > studentGetId(student2)) {
		return 1;
	}
	if (studentGetId(student1) < studentGetId(student2)){
		return -1;
	}
	return 0;
}
/**************************** static functions implementation ***********/
RequestResult createRequest(Request* request,Student sender ,Student receiver){
	if (request == NULL || sender == NULL || receiver==NULL) {
		return REQUEST_NULL_PARAMETER;
	}
	Request allocated_request=malloc(sizeof(*allocated_request));
	if (allocated_request == NULL) return REQUEST_OUT_OF_MEMORY;
	allocated_request->receiver=receiver;
	allocated_request->sender=sender;
	*request=allocated_request;
	return REQUEST_SUCCESS;
}

Student requestGetSender(Request request){
	return request->sender;
}

Student requestGetReceiver(Request request){
	return request->receiver;
}


Request requestCopy(Request request){
	assert(request!=NULL);
	Request new_request;
	if (createRequest(&new_request,request->sender,request->receiver)==
            REQUEST_OUT_OF_MEMORY){
        return NULL;
    }
	return new_request;
}

bool requestCompareRequests(Request request1,Request request2){
	assert(request1!=NULL && request2!=NULL);
	Student request1_receiver=request1->receiver;
	Student request2_receiver=request2->receiver;
	Student request1_sender=request2->sender;
	Student request2_sender=request2->sender;
	if (RequestCompareStudent(request1_sender,request2_sender)!=0){
		return 0;
	}
	if (RequestCompareStudent(request1_receiver,request2_receiver)!=0){
		return 0;
	}
	return 1;
}

void requestDestroy(Request request){
    if (request!=NULL){
        request->sender=NULL;
        request->receiver=NULL;
    }
    free(request);
}
