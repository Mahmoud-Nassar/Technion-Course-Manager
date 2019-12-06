CC = gcc
ADT_OBJS = course_manager.o student.o semester.o grade_sheet.o request.o friends.o
PROG_OBJS = main.o $(ADT_OBJS)
TESTS_OBJS = course_manager_test.o student_test.o semester_test.o \
grade_sheet_test.o request_test.o friends_test.o
LIST_OBJS = list_mtm.o list_mtm_test.o
OBJS = $(PROG_OBJS) $(TESTS_OBJS) $(LIST_OBJS)

TESTS = course_manager_test student_test semester_test grade_sheet_test \
request_test friends_test
PROG_EXE = mtm_cm
LIST_EXE = list_mtm_test
EXE = $(TESTS) $(PROG_EXE) $(LIST_EXE)

DEBUG_FLAG = #-g#
COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG 
LIBS = -L.  -lmtm

TEST_PATH = ./tests/
LIST_PATH = ./list_mtm/
TEST_UTILS = $(TEST_PATH)test_utilities.h
TEST_GCC = $(CC) $(COMP_FLAG) -c $(TEST_PATH)$*.c

$(PROG_EXE) : $(PROG_OBJS)
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(PROG_OBJS) $(LIBS) -o $@
	
$(LIST_EXE) : $(LIST_OBJS)
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(LIST_OBJS) -o $@
	
tests: $(TESTS)  $(LIST_EXE)

clean:
	rm -f $(EXE) $(OBJS)

#---------Program mtm_cm and course Manager ADTS object files---------#	

course_manager.o: course_manager.c course_manager.h student.h \
 grade_sheet.h list.h set.h friends.h request.h
	$(CC) -c $(COMP_FLAG) $*.c
	
student.o: student.c student.h grade_sheet.h list.h semester.h set.h \
 mtm_ex3.h
	$(CC) -c $(COMP_FLAG) $*.c

semester.o: semester.c list.h semester.h grade_sheet.h set.h mtm_ex3.h
	$(CC) -c $(COMP_FLAG) $*.c
	
grade_sheet.o: grade_sheet.c grade_sheet.h mtm_ex3.h
	$(CC) -c $(COMP_FLAG) $*.c

friends.o: friends.c student.h grade_sheet.h list.h friends.h set.h \
 mtm_ex3.h
	$(CC) -c $(COMP_FLAG) $*.c
	
request.o: request.c request.h student.h grade_sheet.h list.h
	$(CC) -c $(COMP_FLAG) $*.c
	
main.o: main.c mtm_ex3.h course_manager.h student.h grade_sheet.h list.h
	$(CC) -c $(COMP_FLAG) $*.c

#---------list object files---------#

list_mtm.o: $(LIST_PATH)list_mtm.c $(LIST_PATH)list_mtm.h
	$(CC) -c $(COMP_FLAG) $(LIST_PATH)$*.c

list_mtm_test.o: $(TEST_PATH)list_mtm_test.c $(TEST_UTILS) $(LIST_PATH)list_mtm.h
	$(CC) -c $(COMP_FLAG) $(TEST_PATH)$*.c

#---------tests objects files---------#


course_manager_test.o: $(TEST_PATH)course_manager_test.c course_manager.h \
 student.h grade_sheet.h list.h $(TEST_UTILS)
	$(TEST_GCC)	 

student_test.o: $(TEST_PATH)student_test.c $(TEST_UTILS) student.h grade_sheet.h \
 list.h	semester.h
	$(TEST_GCC)

semester_test.o: $(TEST_PATH)semester_test.c list.h set.h $(TEST_UTILS) \
 grade_sheet.h semester.h grade_sheet.h set.h mtm_ex3.h
	$(TEST_GCC)	
	
grade_sheet_test.o: $(TEST_PATH)grade_sheet_test.c $(TEST_UTILS) grade_sheet.h
	$(TEST_GCC)

request_test.o: $(TEST_PATH)request_test.c $(TEST_UTILS) request.h student.h \
 grade_sheet.h list.h semester.h
	$(TEST_GCC)

friends_test.o: $(TEST_PATH)friends_test.c set.h friends.h student.h grade_sheet.h \
 list.h semester.h $(TEST_UTILS)
	$(TEST_GCC)
	
#---------tests exe---------#

course_manager_test: course_manager_test.o $(ADT_OBJS)
	$(CC) $@.o $(ADT_OBJS) $(COMP_FLAGS) $(LIBS) -o $@
	
student_test: student_test.o student.o semester.o grade_sheet.o
	$(CC) $@.o student.o semester.o grade_sheet.o $(COMP_FLAG) $(LIBS) -o $@
	
semester_test: semester_test.o semester.o grade_sheet.o
	$(CC) $@.o semester.o grade_sheet.o $(COMP_FLAG) $(LIBS) -o $@

grade_sheet_test: grade_sheet_test.o grade_sheet.o
	$(CC) $@.o grade_sheet.o $(COMP_FLAGS) \
	$(LIBS) -o $@
	
request_test: request_test.o request.o grade_sheet.o student.o semester.o
	$(CC) $@.o  request.o grade_sheet.o student.o semester.o $(COMP_FLAGS) \
	$(LIBS) -o $@

friends_test: friends_test.o grade_sheet.o student.o semester.o
	$(CC) $@.o grade_sheet.o student.o semester.o friends.o $(COMP_FLAG) $(LIBS) -o $@	
	