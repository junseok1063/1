#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h> 

#define MAX_LEN_LINE    100

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    
    char *user_name;
    struct passwd *user_pw;

    user_name =getlogin();
    user_pw = getpwnam( user_name);
    char hostname[50];
    int host_len=50;
    if (gethostname(hostname, host_len)==1){
        printf("gethostname Error!\n");
        exit(1);
    }
    char *cwd;
    char wd[BUFSIZ];

    cwd = getcwd(NULL, BUFSIZ);
    
    int cycle=0;
    
    while (true) {
        char *s;
        int len;
        char username=user_pw->pw_name;
        printf("%c[1;32m",27);
        printf("%s@%s",user_pw->pw_name,hostname);
        printf("%c[0m",27);
        printf(":");
        printf("%c[1;34m",27);
        printf("~%s",cwd);
        printf("%c[0m",27);
        printf("$ ");
        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        len = strlen(command);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        if(strncmp(command, "exit", strlen(command))==0) {
            return -1;
        }
        char ChangHomeDir[MAX_LEN_LINE]={"/home/%s",username};
        if(strncmp(command, "cd",strlen(command))==0){
           cwd=chdir(ChangeHomeDir);
        }
        if(strncmp(command,"cd %s"))
      
        printf("%d\n", len);
        
        printf("[%s]\n", command);

      
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */
            ret = execve(args[0], args, NULL);
            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        } 
        cycle+=1;
        printf("number of time :%d\n",cycle);
    }
    return 0;
}