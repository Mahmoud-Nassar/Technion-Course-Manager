#ifndef FRIENDREQUEST_H_
#define FRIENDREQUEST_H_
#include <stdbool.h>
#include "student.h"
typedef struct request_t* Request;

typedef enum {
	REQUEST_OUT_OF_MEMORY,
	REQUEST_NULL_PARAMETER,
	REQUEST_SUCCESS,
} RequestResult;

/**
 * Creates a new request
 * @param: sender - the student who sent the request
 * @param: receiver - the student who received the request
 * @param: request - output parameter to return the new allocated Request
 * @return: REQUEST_NULL_PARAMETER if sender receiver,or request are NULL,
 * REQUEST_OUT_OF_MEMORY if memory allocation failed,REQUEST_SUCCESS otherwise.
 */
RequestResult createRequest(Request* request,Student sender ,Student receiver);
/**
 * return the sender of the request (without coping)
 * @param request- the request described above
 */
Student requestGetSender(Request request);
/**
 * return the receiver of the request (without coping)
 * @param request- the request described above
 */
Student requestGetReceiver(Request request);

/**
 * Request must not be NULL
 * Copies a Request
 * @param: Request to be copied
 * @return: NULL in case of bad allocation
 * a new copy of the Request otherwise
 */
Request requestCopy(Request request);

/**
 * request1 & request1 must not be NULL
 * Compares between two requests .
 * @param: Request1 to be compared
 * @param: Request2 to be compared with
 * @return: 1 if the are equal,0 otherwise
 */
bool requestCompareRequests(Request request1,Request request2);

/**
 *Deallocates a request.
 *@param: request to be removed
 */
void requestDestroy(Request request);

#endif /* FRIENDREQUEST_H_ */
