#include "test_utilities.h"
#include "../list_mtm/list_mtm.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define LEN 10
#define STR_ARRAY_SIZE 5

static ListElement copyString(ListElement str){
	if(str == NULL){
		return NULL;
	}
	char* copy = malloc(strlen(str)+1);
	return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str){
	free(str);
}

static ListElement copyInt(ListElement element){
	if(element == NULL){
		return NULL;
	}
	int* newInt = malloc(sizeof(int));
	if (newInt == NULL) { return NULL; }
	*newInt = *(int*)element;
	return newInt;
}

static void freeInt(ListElement element){
	free(element);
}

static bool isLongerThan(ListElement element,ListFilterKey number) {
	char* string = element;
    return strlen(string) > *(int*)number;
}

static bool isGreaterThan(ListElement element,ListFilterKey number){
	int value = *(int*)element;
	return value > *(int*)number;
}

static int compareString(ListElement str1, ListElement str2,ListSortKey key){
    char key_char=*(char*)key;
    char* str1_key=strchr(str1,key_char);
    char* str2_key=strchr(str2,key_char);
    if (str1_key==NULL && str2_key!=NULL) return 0;
    else if (str1_key!=NULL && str2_key==NULL) return 1;
	return strcmp(str1, str2);
}

static int compareInt(ListElement number1, ListElement number2,ListSortKey key){
    int value=*(int*)key;
    int number1_value=(*(int*)number1);
    int number2_vlaue=(*(int*)number2);
    if (number1_value == value && number2_vlaue!=value) return 1;
    if (number1_value != value && number2_vlaue==value) return 0;
	return (number1_value-number2_vlaue);
}

static bool initStringList(List *list_of_strings){
	*list_of_strings = listCreate(copyString, freeString);
	ASSERT_TEST(*list_of_strings!=NULL);
	char* array[STR_ARRAY_SIZE] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0; i <STR_ARRAY_SIZE; ++i){
		ASSERT_TEST(listInsertFirst(*list_of_strings, array[i])==LIST_SUCCESS);
	}
	return true;
}

static bool initIntList(List *list_of_ints){
	*list_of_ints = listCreate(copyInt, freeInt);
	ASSERT_TEST(*list_of_ints!=NULL);
	for(int i=1; i<=LEN; i++){
		ASSERT_TEST(listInsertFirst(*list_of_ints,&i) == LIST_SUCCESS);
	}
	return true;
}

static bool compareIterators(ListElement iterator_before,
		ListElement iterator_after){

	return iterator_after==iterator_before;
}

static bool testListCreate() {
	//official course tests
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,freeString) == NULL);
	//ours
	List list_of_ints = listCreate(copyInt, freeInt);
	List list_of_strings = listCreate(copyString, freeString);
	ASSERT_TEST(list_of_ints!=NULL);
	ASSERT_TEST(list_of_strings!=NULL);
	ASSERT_TEST(listGetCurrent(list_of_ints)== NULL);
	ASSERT_TEST(listGetCurrent(list_of_strings)== NULL);
	listDestroy(list_of_ints);
	listDestroy(list_of_strings);
	return true;
}

static bool testListDestroy() {
	//ours
	listDestroy(NULL);
	List list_of_strings = NULL;
	initStringList(&list_of_strings);
	listDestroy(list_of_strings);
	return true;
}

static bool testlistCopy(){
	//ours
	List copy_list = listCopy(NULL);
	ASSERT_TEST(copy_list==NULL);
	List list_of_strings = NULL;
	initStringList(&list_of_strings);
	ASSERT_TEST(listGetFirst(list_of_strings)!=NULL);
	ASSERT_TEST(listGetNext(list_of_strings)!=NULL);
 	copy_list = listCopy(list_of_strings);
	ASSERT_TEST(copy_list!=NULL);
	char* array[STR_ARRAY_SIZE] = {"aaa","bbb","NI","hello mister fish","I"};
	int i = STR_ARRAY_SIZE-1;
	LIST_FOREACH(char *,iterator,copy_list){
		char* word = (char*) iterator;
		ASSERT_TEST(strcmp(word,array[i])==0);
		i--;
	}
	listDestroy(list_of_strings);
	listDestroy(copy_list);
	return true;
}

static bool testListGetSize(){
	//official course tests
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	//ours
	ASSERT_TEST(listGetSize(NULL) == -1);
	List empty_list = listCreate(copyString, freeString);
	ASSERT_TEST(listGetSize(empty_list) == 0);
	listDestroy(empty_list);
	List list_of_ints = NULL;
	initIntList(&list_of_ints);
	listGetFirst(list_of_ints);
	ListElement initial_iterator =listGetCurrent(list_of_ints);
	ASSERT_TEST(listGetSize(list_of_ints) == LEN);
	ListElement current_iterator = listGetCurrent(list_of_ints);
	ASSERT_TEST(compareIterators(initial_iterator, current_iterator));
	listDestroy(list_of_ints);
	return true;
}

static bool testListGetFirst() {
	ASSERT_TEST(listGetFirst(NULL) == NULL);
	List list = listCreate(copyInt, freeInt);
	ASSERT_TEST(listGetFirst(list) == NULL);
	for(int i=0; i<=LEN; i++){
		ASSERT_TEST(listInsertFirst(list,&i) == LIST_SUCCESS);
	}
	ListElement first = listGetFirst(list);
	ASSERT_TEST(first!=NULL);
	ASSERT_TEST(*(int*)first == LEN);
	listDestroy(list);
	return true;
}

static bool testListGetNext() {
	ASSERT_TEST(listGetNext(NULL) == NULL);
	List list = listCreate(copyInt, freeInt);
	ASSERT_TEST(list != NULL);
	ASSERT_TEST(listGetNext(list) == NULL);
	int value = LEN;
	ASSERT_TEST(listInsertFirst(list,&value) == LIST_SUCCESS);
	ASSERT_TEST(listGetNext(list) == NULL);
	listGetFirst(list);
	value--;
	ASSERT_TEST(listInsertLast(list,&value) == LIST_SUCCESS);
	ListElement next = listGetNext(list);
	ASSERT_TEST(next != NULL);
	ASSERT_TEST(*(int*)next == value);
	*(int*)next = LEN+1;
	listGetFirst(list);
	ASSERT_TEST(*(int*)listGetNext(list) == *(int*)next);
	ASSERT_TEST(listGetNext(list) == NULL);
	listDestroy(list);
	return true;
}

static bool testListInsertFirst() {
	ListResult result = listInsertFirst(NULL,NULL);
	ASSERT_TEST(result==LIST_NULL_ARGUMENT);
	List list = listCreate(copyInt, freeInt);
	result = listInsertFirst(list,NULL);
	ASSERT_TEST(result==LIST_NULL_ARGUMENT);
	ListElement initial_iterator =listGetCurrent(list);
	for(int i=0; i<=LEN; i++){
		result = listInsertFirst(list,&i);
		ASSERT_TEST(list!=NULL && result==LIST_SUCCESS);
	}
	ListElement current_iterator = listGetCurrent(list);
	ASSERT_TEST(compareIterators(initial_iterator, current_iterator));
	int i = LEN;
	LIST_FOREACH(int *,iterator,list){
		ASSERT_TEST(iterator!=NULL);
		int x = *(int*)iterator;
		ASSERT_TEST(x == i);
		i--;
	}
	ASSERT_TEST(i==-1);
	listDestroy(list);
	return true;
}

static bool testListInsertLast(){
	ListResult result = listInsertLast(NULL,NULL);
	ASSERT_TEST(result==LIST_NULL_ARGUMENT);
	List list = listCreate(copyInt, freeInt);
	result = listInsertLast(list,NULL);
	ASSERT_TEST(result==LIST_NULL_ARGUMENT);
	ListElement initial_iterator =listGetCurrent(list);
	for(int i=0; i<=LEN; i++){
		result = listInsertLast(list,&i);
		ASSERT_TEST(list!=NULL && result==LIST_SUCCESS);
	}
	ListElement current_iterator = listGetCurrent(list);
	ASSERT_TEST(compareIterators(initial_iterator, current_iterator));
	int i = 0;
	LIST_FOREACH(int *,iterator,list){
		int x = *(int*)iterator;
		ASSERT_TEST(x == i);
		i++;
	}
	ASSERT_TEST(i==(LEN+1));
	listDestroy(list);
	return true;
}

static bool testListFilter(){
	//official course tests
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	int key = 5;
	List filtered = listFilter(list,isLongerThan, &key);
	ASSERT_TEST(listGetSize(filtered) == 1);
	ASSERT_TEST(strcmp(listGetFirst(filtered),a[3])==0);
	listDestroy(list);
	listDestroy(filtered);
	//ours
	int filter_key = LEN-5;
	ASSERT_TEST(listFilter(NULL,isGreaterThan,&filter_key)==NULL);
	List my_list = NULL;
	ASSERT_TEST(initIntList(&my_list));
	ASSERT_TEST(listFilter(my_list,NULL,&filter_key)==NULL);
	List filtered_list = listFilter(my_list,isGreaterThan,&filter_key);
	ASSERT_TEST(filtered_list!=NULL);
	ASSERT_TEST(*(int*)listGetFirst(filtered_list)==LEN);
	ASSERT_TEST(listGetSize(filtered_list)==5);
	int i = LEN;
	LIST_FOREACH(int *,iterator,filtered_list){
		int x = *(int*)iterator;
		ASSERT_TEST(x == i);
		i--;
	}
	listDestroy(my_list);
	listDestroy(filtered_list);
	return true;
}

static bool testListGetCurrent(){
	//ours
	ASSERT_TEST(listGetCurrent(NULL)==NULL);
	List my_list = NULL;
	ASSERT_TEST(initIntList(&my_list));
	ASSERT_TEST(listGetCurrent(my_list)==NULL);
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ListElement current_element = listGetCurrent(my_list);
	ASSERT_TEST(current_element!=NULL);
	ASSERT_TEST(*(int*)current_element==LEN);
	ASSERT_TEST(listGetNext(my_list)!=NULL);
	current_element = listGetCurrent(my_list);
	ASSERT_TEST(current_element!=NULL);
	ASSERT_TEST(*(int*)current_element==LEN-1);
	listDestroy(my_list);
	return true;
}

static bool testListInsertBeforeCurrent(){
	ASSERT_TEST(listInsertBeforeCurrent(NULL,NULL)== LIST_NULL_ARGUMENT);
	List my_list = NULL;
	ASSERT_TEST(initIntList(&my_list));
	ASSERT_TEST(listInsertBeforeCurrent(my_list,NULL)==LIST_NULL_ARGUMENT);
	int number = LEN+1;
	ASSERT_TEST(listInsertBeforeCurrent(NULL,&number)== LIST_NULL_ARGUMENT);
	ASSERT_TEST(listGetCurrent(my_list)== NULL);
	ASSERT_TEST(listInsertBeforeCurrent(my_list,&number)==LIST_INVALID_CURRENT);
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ASSERT_TEST(listGetNext(my_list)!=NULL);
	ListElement initial_iterator = listGetCurrent(my_list);
	ASSERT_TEST(listInsertBeforeCurrent(my_list,&number)==LIST_SUCCESS);
	ListElement current_iterator = listGetCurrent(my_list);
 	ASSERT_TEST(compareIterators(initial_iterator,current_iterator));
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ListElement inserted_element = listGetNext(my_list);
	ASSERT_TEST(inserted_element!=NULL);
	ASSERT_TEST(*(int*) inserted_element == number);
	listDestroy(my_list);
	return true;
}

static bool testListInsertAfterCurrent(){
	ASSERT_TEST(listInsertAfterCurrent(NULL,NULL)== LIST_NULL_ARGUMENT);
	List my_list = NULL;
	ASSERT_TEST(initIntList(&my_list));
	ASSERT_TEST(listInsertAfterCurrent(my_list,NULL)==LIST_NULL_ARGUMENT);
	int number = LEN+1;
	ASSERT_TEST(listInsertAfterCurrent(NULL,&number)== LIST_NULL_ARGUMENT);
	ASSERT_TEST(listGetCurrent(my_list)== NULL);
	ASSERT_TEST(listInsertAfterCurrent(my_list,&number)==LIST_INVALID_CURRENT);
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ASSERT_TEST(listGetNext(my_list)!=NULL);
	ListElement initial_iterator = listGetCurrent(my_list);
	ASSERT_TEST(listInsertAfterCurrent(my_list,&number)==LIST_SUCCESS);
	ListElement current_iterator = listGetCurrent(my_list);
	ASSERT_TEST(compareIterators(initial_iterator,current_iterator));
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ASSERT_TEST(listGetNext(my_list)!=NULL);
	ListElement inserted_element = listGetNext(my_list);
	ASSERT_TEST(inserted_element!=NULL);
	ASSERT_TEST(*(int*) inserted_element ==LEN+1);
	listDestroy(my_list);
	return true;
}

static bool testListRemoveCurrent(){
	ASSERT_TEST(listRemoveCurrent(NULL)== LIST_NULL_ARGUMENT);
	List my_list = NULL;
	ASSERT_TEST(initIntList(&my_list));
	ASSERT_TEST(listRemoveCurrent(my_list)==LIST_INVALID_CURRENT);
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ASSERT_TEST(listRemoveCurrent(my_list)==LIST_SUCCESS);
	ASSERT_TEST(listRemoveCurrent(my_list)==LIST_INVALID_CURRENT);
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ASSERT_TEST(*(int*)listGetFirst(my_list)==LEN-1);
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ASSERT_TEST(listGetNext(my_list)!=NULL);
	ASSERT_TEST(listRemoveCurrent(my_list)==LIST_SUCCESS);
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ListElement next_element = listGetNext(my_list);
	ASSERT_TEST(next_element!=NULL);
	ASSERT_TEST(*(int*)next_element==LEN-3);
	listDestroy(my_list);
	return true;
}

static bool testListClear(){
	ASSERT_TEST(listClear(NULL)==LIST_NULL_ARGUMENT);
	List my_list = NULL;
	ASSERT_TEST(initIntList(&my_list));
	ASSERT_TEST(listClear(my_list)==LIST_SUCCESS);
	ASSERT_TEST(listGetCurrent(my_list)== NULL);
	listDestroy(my_list);
	return true;
}

static bool testListSort(){
	//official course tests
	char* a[5] = {"aaa","NI","hello mister fish","z", "bbb"};
	List list1 = listCreate(copyString,freeString);
	for (int i=0;i<5; ++i){
		listInsertFirst(list1,a[i]);
	}
    char character='z';
	listSort(list1,compareString,&character);
	ASSERT_TEST(strcmp(listGetFirst(list1),"NI") == 0);
	ASSERT_TEST(strcmp(listGetNext(list1),"aaa") == 0);
	ASSERT_TEST(strcmp(listGetNext(list1),"bbb") == 0);
	ASSERT_TEST(strcmp(listGetNext(list1),"hello mister fish") == 0);
	ASSERT_TEST(strcmp(listGetNext(list1),"z") == 0);
	listDestroy(list1);
	//ours
	List my_list = NULL;
    int int_key=10;
	ASSERT_TEST(listSort(NULL,NULL,&character)==LIST_NULL_ARGUMENT);
	ASSERT_TEST(listSort(my_list,NULL,&character)==LIST_NULL_ARGUMENT);
	ASSERT_TEST(listSort(NULL,compareInt,&int_key)==LIST_NULL_ARGUMENT);
	ASSERT_TEST(initIntList(&my_list));
	ASSERT_TEST(listGetFirst(my_list)!=NULL);
	ASSERT_TEST(listGetNext(my_list)!=NULL);
	ASSERT_TEST(listSort(my_list,compareInt,&int_key)==LIST_SUCCESS);
	ASSERT_TEST((listGetCurrent(my_list)!=NULL));
	ASSERT_TEST(*(int*)(listGetCurrent(my_list))== 2);
	int i = 1;
	LIST_FOREACH(int *,iterator,my_list){
		int x = *(int*)iterator;
		ASSERT_TEST(x == i);
		i++;
	}
	ASSERT_TEST(i == LEN+1);
	listDestroy(my_list);
	return true;
}

int main (int argv, char** arc){
	setvbuf (stdout, NULL, _IONBF, 0);

	RUN_TEST(testlistCopy);
	RUN_TEST(testListCreate);
	RUN_TEST(testListDestroy);
	RUN_TEST(testListGetSize);
	RUN_TEST(testListGetFirst);
	RUN_TEST(testListGetNext);
	RUN_TEST(testListInsertFirst);
	RUN_TEST(testListInsertLast);
	RUN_TEST(testListFilter);
	RUN_TEST(testListGetCurrent);
	RUN_TEST(testListInsertBeforeCurrent);
	RUN_TEST(testListInsertAfterCurrent);
	RUN_TEST(testListRemoveCurrent);
	RUN_TEST(testListClear);
	RUN_TEST(testListSort);
	return 0;
}




