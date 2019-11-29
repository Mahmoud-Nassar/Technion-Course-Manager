#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "mtm_ex3.h"
#include "course_manager.h"
#define MIN_CRITICAL_ERROR 0
#define MAX_CRITICAL_ERROR 2

/*
 * Function checkCommandLineParameters: function checks if the command line
 * structure is as follows:
 * mtm_cm [-i <input_file>] [-o <output_file>]
 * with taking into consideration that the input and output files are optional
 * (if there was no flags -i/-o respectively) and with allowing changing order
 * between [-i <input_file>] and [-o <output_file>].
 * @param: argc and argv of the main program
 * @return: true if all parameters are valid, false otherwise.
 */
bool checkCommandLineParameters(int argc, char** argv);
/* Function initInputFile:
 * @param: argc and argv of the main program
 * @return: input file that has all the instructions, which is stdin in case no
 * input file has been specified within the command line parameters, otherwise
 * it's the file that appears after -i in the command line parameters.
 */
FILE* initInputFile(int argc, char** argv);
/* Function initOutputFile:
 * @param: argc and argv of the main program
 * @return:output file of the program, which is stdout in case no
 * output file has been specified within the command line parameters, otherwise
 * it's the file that appears after -o in the command line parameters.
 */
FILE* initOutputFile(int argc, char** argv);
 /*
  * prints a suitable error message and checks if the error is a critical error
  * (by critical error we mean the Error that we should exit the program
  * when it happens):MTM_OUT_OF_MEMORY ,MTM_INVALID_COMMAND_LINE_PARAMETERS
  * MTM_CANNOT_OPEN_FILE
  * @param: error - error code
  * @return: true if the error is critical, false otherwise
  */
bool isCriticalError(MtmErrorCode error);

/* Functions readCommands:
 * @param: input file of the program
 * @param:output file of the program
 * @param:course_manager the manager of the course that has all the legal commands 
	reads the first word of the command and check if the read command is legal
	if yes,then call command functions to submit the command 
	if the command is illegal prints the error message to the stderr 
	and if it is a critical error then returns to the main.
 */
void readCommands(FILE* input, FILE* output, CourseManager course_manager);

/* Functions gradeSheetReadCommand:
 * @param: input file of the program
 * @param:course_manager the manager of the course that has all the legal commands 
	reads the sub command of grade_sheet  and check if the grade_sheet sub command is legal
	if yes,then call the relevant function from the course_manager  
	@return - the result of the command (as CourseManager enum)
 */
CourseManagerResult gradeSheetReadCommand(CourseManager course_manager,
										  FILE* input);

/* Functions studentReadCommand:
 * @param: input file of the program
 * @param:course_manager the manager of the course that has all the legal commands 
	reads the sub command of student  and check if the student sub command is legal
	if yes,then call the relevant function from the course_manager  
	@return - the result of the command (as CourseManager enum)
 */
CourseManagerResult studentReadCommand(CourseManager course_manager,
									   FILE* input);

/* Functions studentReadCommand:
 * @param: input file of the program
 * @param:course_manager the manager of the course that has all the legal commands 
 * @param:output file of the program to insert the output into  
	reads the sub command of report  and check if the report sub command is legal
	if yes,then call the relevant function from the course_manager  
	@return - the result of the command (as CourseManager enum)
 */
CourseManagerResult reportReadCommand(CourseManager course_manager, FILE* input
        ,FILE* output);

/* Function convertCourseMangerError:
*  @param:result -enum of course manager to be converted to enum of the main
* convert enum of course manager to enum of the main
*/
MtmErrorCode convertCourseMangerError (CourseManagerResult result);

bool checkCommandLineParameters(int argc, char** argv){
	if(argc==3){
		if((strcmp("-i",argv[1])!=0)&&(strcmp("-o", argv[1])!=0)){

			return false;
		}
	}
	if(argc==5){
		return (((strcmp("-i",argv[1])==0)&&(strcmp("-o", argv[3])==0)) ||
				((strcmp("-o",argv[1])==0)&&(strcmp("-i", argv[3])==0)));
	}
	return true;
}

FILE* initInputFile(int argc, char** argv) {
	if (argc == 1||((argc==3)&&(strcmp(argv[1],"-o")==0))){
		return stdin;
	}
	if (argc == 3){
		return fopen(argv[2], "r");
	}
	assert(argc == 5);
	if((strcmp(argv[1],"-i")==0)){
		return fopen(argv[2], "r");
	}
	if((strcmp(argv[3],"-i")==0)){
		return fopen(argv[4], "r");
	}
	return stdin;
}

FILE* initOutputFile(int argc, char** argv) {
	if (argc == 1||((argc==3)&&(strcmp(argv[1],"-i")==0))){
		return stdout;
	}
	if (argc == 3){
		return fopen(argv[2], "w");
	}
	assert(argc == 5);
	if((strcmp(argv[1],"-o")==0)){
		return fopen(argv[2], "w");
	}
	if((strcmp(argv[3],"-o")==0)){
		return fopen(argv[4], "w");
	}
	return stdout;
}

bool isCriticalError(MtmErrorCode error){
	if(error>=MIN_CRITICAL_ERROR && error<= MAX_CRITICAL_ERROR){
		return true;
	}
	return false;
}

void readCommands(FILE* input, FILE* output, CourseManager course_manager){
	char command[MAX_LEN+1];
	CourseManagerResult result1;
	while(fscanf(input,"%s[^\n]",command)!=EOF){
		if(command[0] == '#'){
			fscanf(input,"%*[^\n]\n");
			 continue;
		} else if(strcmp(command, "student") == 0){
			result1 = studentReadCommand(course_manager,input);
			
		} else if(strcmp(command, "grade_sheet") == 0){
			result1 = gradeSheetReadCommand(course_manager,input);
			
		} else if(strcmp(command, "report")==0){
			result1 = reportReadCommand(course_manager,input,output);
			
		} 
		 else {
			MtmErrorCode code = MTM_INVALID_COMMAND_LINE_PARAMETERS;
			mtmPrintErrorMessage(stderr,code);
			return;
		}
		if(result1!=COURSE_MANAGER_SUCCESS){
			MtmErrorCode current_code=convertCourseMangerError(result1);
			mtmPrintErrorMessage(stderr,current_code);
			if(isCriticalError(current_code)){
				assert(result!=MTM_NULL_PARAMETER);
				return;
			}
		}
	}
	return;
}

CourseManagerResult studentReadCommand(CourseManager course_manager, FILE* input){
	char sub_command [MAX_LEN+1];
	fscanf(input ," %s ", sub_command);
	if(strcmp(sub_command,"add") == 0){
		int id;
		char first_name[MAX_LEN+1];
		char last_name[MAX_LEN+1];
		fscanf(input, " %d %s %s ", &id, first_name,last_name);
		return courseManagerAddStudent(course_manager,id,first_name,last_name);
	}
	
	if(strcmp(sub_command,"remove")==0){
		int id;
		fscanf(input, " %d ",&id);
		return courseManagerRemoveStudent(course_manager, id);
	}
	
	if(strcmp(sub_command,"login")==0){
	int id;
	fscanf(input, " %d ", &id);
	return courseManagerStudentLogIn(course_manager, id);
	}
	
	if(strcmp(sub_command,"logout")==0){
	return courseManagerStudentLogOut(course_manager);
	}
	
	if(strcmp(sub_command,"friend_request")==0){
	int other_id;
	fscanf(input, " %d ", &other_id);
	return courseManagerSendFriendRequest(course_manager, other_id);
	}
	
	if(strcmp(sub_command,"handle_request")==0){
	int other_id;
	char action[MAX_LEN+1];
	fscanf(input, " %d %s ", &other_id,action);
	return courseManagerHandelFriendRequest(course_manager,other_id,action);
	}
	
	if(strcmp(sub_command,"unfriend")==0){
	int other_id;
	fscanf(input, " %d ", &other_id);
	return courseManagerStudentUnfriend(course_manager, other_id);
	}

	return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

CourseManagerResult gradeSheetReadCommand(CourseManager course_manager,
										  FILE* input){
	char sub_command [MAX_LEN+1];
	fscanf(input ," %s ", sub_command);
	if(strcmp(sub_command,"add") == 0){
		int semester;
		int course_id;
		char points[MAX_LEN+1];
		int grade;
		fscanf(input, " %d %d %s %d ", &semester, &course_id, points,&grade);
		return courseManagerAddGradeSheet(course_manager,semester,course_id,points,grade);
	}
	
	if(strcmp(sub_command,"remove")==0){
		int semester;
		int course_id;
		fscanf(input, " %d %d ",&semester,&course_id);
		return courseManagerRemoveGradeSheet(course_manager,course_id,semester);
	}
	
	if(strcmp(sub_command,"update")==0){
	int course_id;
	int new_grade;
	fscanf(input, " %d %d ", &course_id,&new_grade);
	return courseManagerUpdateGradeSheet(course_manager,course_id, new_grade);
	}
	
	return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}
	
CourseManagerResult reportReadCommand(CourseManager course_manager, FILE* input
		,FILE* output){
	char sub_command [MAX_LEN+1];
	fscanf(input ," %s ", sub_command);
	if(strcmp(sub_command,"full") == 0){
	return courseManagerReportFull(course_manager,output);
	}
	
	if(strcmp(sub_command,"clean")==0){
		return courseManagerReportClean(course_manager,output);
	}
	
	if(strcmp(sub_command,"best")==0){
	int amount;
	fscanf(input, " %d ", &amount);
	return courseManagerReportBest(course_manager,output, amount);
	}
	
	if(strcmp(sub_command,"worst")==0){
	int amount;
	fscanf(input, " %d ", &amount);
	return courseManagerReportWorst(course_manager,output, amount);
	}
	
	if(strcmp(sub_command,"reference")==0){
	int course_id;
	int amount;
	fscanf(input, " %d %d ", &course_id, &amount);
	return courseManagerPrintReference(course_manager,course_id, amount,output);
	}
	if(strcmp(sub_command,"faculty_request")==0){
	int course_id;
	char request[MAX_LEN+1];
	fscanf(input, " %d %s ", &course_id, request);
	return courseManagerFacultyRequest(course_manager,course_id, request,output);
	}
	
	return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

MtmErrorCode convertCourseMangerError (CourseManagerResult result) {
    switch (result) {
        case COURSE_MANAGER_OUT_OF_MEMORY:
            return MTM_OUT_OF_MEMORY;
        case COURSE_MANAGER_STUDENT_NOT_LOGGED_IN:
            return MTM_NOT_LOGGED_IN;
        case COURSE_MANAGER_ALREADY_LOGGED_IN:
            return MTM_ALREADY_LOGGED_IN;
        case COURSE_MANAGER_STUDENT_DOES_NOT_EXIST:
            return MTM_STUDENT_DOES_NOT_EXIST;
        case COURSE_MANAGER_STUDENT_ALREADY_EXISTS:
            return MTM_STUDENT_ALREADY_EXISTS;
        case COURSE_MANAGER_NOT_FRIEND:
            return MTM_NOT_FRIEND;
        case COURSE_MANAGER_ALREADY_FRIEND:
            return MTM_ALREADY_FRIEND;
        case COURSE_MANAGER_NOT_REQUESTED:
            return MTM_NOT_REQUESTED;
        case COURSE_MANAGER_ALREADY_REQUESTED:
            return MTM_ALREADY_REQUESTED;
        case COURSE_MANAGER_COURSE_DOES_NOT_EXIST:
            return MTM_COURSE_DOES_NOT_EXIST;
        default:
            return MTM_INVALID_PARAMETERS;
    }
}

/* main program: mtm_cm
 * Command Line Parameters: mtm_cm [-i <input_file>] [-o <output_file>]
 * -i <input_file> (optional): to set input file as the program input, input
 * will be set to stdin if no input file was specified.
 * -o <output_file> (optional): to set output file for the program output,
 * output will be set to stdout if no output file was specified.
 * @Possible Errors:.MTM_INVALID_COMMAND_LINE_PARAMETERS
	if the command line parameters are
 * invalid.
 * MTM_CANNOT_OPEN_FILE if opening the input file or the output file has failed
 */
int main(int argc, char** argv){
	if((argc%2==0 )||(argc > 5)||(!checkCommandLineParameters(argc,argv))){
		mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
		return 0;
	}
	FILE* input = initInputFile(argc, argv);
	if(!input){
		mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
		return 0;
	}
	FILE* output = initOutputFile(argc, argv);
	if (!output) {
		fclose(input);
		mtmPrintErrorMessage(stderr,MTM_CANNOT_OPEN_FILE);
	}
	CourseManager course_manager = NULL;
	CourseManagerResult result = createCourseManager(&course_manager);
	if(result!=COURSE_MANAGER_SUCCESS){
		mtmPrintErrorMessage(stderr,MTM_OUT_OF_MEMORY);
		fclose(input);
		fclose(output);
		return 0;
	}
	readCommands(input,output,course_manager);
	destroyCourseManager(course_manager);
	fclose(input);
	fclose(output);
	return 0;
}