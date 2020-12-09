#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128
#define TIME 1

char prompt[] = "> ";
char delimiters[] = " \t\r\n";
extern char **environ;

void sigintHandler(int sig_num){// taken from geeksforgeeks.com
	signal(SIGINT, sigintHandler);
	fflush(stdout);
}
static void command(char* tok){
	int x = fork();
	char* delim = " ";
	char* temp = tok;
	char *toks[100];
	char* token = strtok(0, delim);
	int i = 1;
	toks[0] = "test";
	int pipe = 0; //false by default
	FILE* p;
	while(token){
		toks[i] = token;
		if(toks[i][0] == '>')
			pipe = 1;
		token = strtok(0, delim);
		i++;
	}
	toks[i] = NULL;
	if(pipe == 1){
		p = popen("echo \"Test\" >&1", "r");
	}
	else if(x < 0){
		fprintf(stderr, "fork error");
		exit(1);
	}else if(x == 0){
		if (pipe == 0)
			execvp(temp, toks);
		else{
			printf("pipe process");
	//		FILE* p;
//			p = popen("echo \"Test\"", "r");
		}
		//sleep(TIME);
//		kill(x, SIGKILL);
		
	}else{
//		printf("else toks[i-1]: %s \n", toks[i-1]);
		if(strcmp(toks[i-1], "&")==0){
//			printf("if");
			wait(NULL);
		}
		wait(NULL);
	}
	if(pipe == 1)
		pclose(p);
	sleep(TIME);
	kill(x, SIGKILL);
}
int main() {
	signal(SIGINT, sigintHandler);


    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    char s[100];
	const char delim[4] = " ";
	const char enter[4] = "\n";
	int def = 0;	
    while (true) {
      
        do{ 
            // Print the shell prompt.
//		prompt = getcwd(s,100);
            printf("%s> ", getcwd(s,100));
            fflush(stdout);

            // Read input from stdin and store it in command_line. If there's an
            // error, exit immediately. (If you want to learn more about this line,
            // you can Google "man fgets")
	
	
 
	if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
        }
	char* no_enter_line = strtok(command_line, enter);
	char* tok = strtok(no_enter_line, delim);
	def = 0;
	switch(tok[0]){
		case 'c':;
			if(tok[1] == 'd'){
				tok = strtok(0, delim);
				chdir(tok);
			}else{
				//printf("def = 1");
				def = 1;
			}
			break;
		case 'p': //pwd
			if(tok[1] == 'w')
				printf("%s\n", getcwd(s,100));
			else
				def = 1;
			break;
	    	case 'e': //echo or exit or env
			switch(tok[1]){
				case 'c': //echo
					tok = strtok(0, delim);
					//printf("\n");
					while(tok != 0 && tok != NULL){
						printf("%s ", tok);
						tok = strtok(0, delim);
					}
					printf("\n");
					for(char **current = environ; *current; current++){
						puts(*current);
					}
					break;
				case 'x': //exit
					exit(0);
					break;
				case 'n': //env
					for(char **current = environ; *current; current++){
						puts(*current);
					}
					break;
				default:
					printf("invalid command");
			}
			break;
		case 's': //setenv
			tok = strtok(0, delim);
			printf("%s ", tok);
			putenv(tok);	
			break;
		default:
			command(tok);
		
			//printf("invalid command");
 	      }
		if(def == 1){
			command(tok);
		}
	}while(command_line[0] == 0x0A);  // while just ENTER pressed

      
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 
        
			  // 0. Modify the prompt to print the current working directory
			  
			
        // 1. Tokenize the command line input (split it on whitespace)

      
        // 2. Implement Built-In Commands
      
    
        // 3. Create a child process which will execute the command line input

  
        // 4. The parent process should wait for the child to complete unless its a background process
      
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}
