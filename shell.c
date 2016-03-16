#include <stdlib.h>
#include <time.h>
#include "apue.h"
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <stdio.h>  
#include <string.h> 
#include "makeargv.c"
// Shell command interpreter: Write a tool to implement bash-like functionality.
// The tool should  
// 1. Allow user to execute any commands, display output/errors
// after command is executed.
// 2. All user to chain multiple commands together. For
// example -- ls -l | wc -l --> output of ls command is read by 'wc' and # of files
// in current directory are printed as output.  
// User should be able to start
// interactive shell, execute multiple commands and press a key combination (e.g.
// ^D) to exit the shell.  
// locate *.txt | xargs grep 'abc' --> output of locate
// command (file names) is sent as input to grep which then searches string 'abc'
// in that file. The net result is that the command outputs lines with text 'abc'
// from all .txt files in current directory

static void sig_int(int);       

int
main(int argc,char * argv[])
{
         
         // if(argc>2)
         // {
         //    printf("\nOnly single argument supported\n");
         //    exit(0);
         // }
        char    buf[MAXLINE];   /* from apue.h */
        pid_t   pid;
        int     status;
       
         if (signal(SIGINT, sig_int) == SIG_ERR)
                err_sys("signal error");

     
        while(1)
        {    
        printf("Enter command : \n");
        //("%s",buf);
        gets(buf);
        printf("%s\n",buf );
        char *execArgs[20];

        int i=0;
        int len=strlen(buf);
        char delimit[]={' '};
        char *dup=strdup(buf);
        char delim;
      

        char* token = strtok(buf, delimit);
        while (token) {
            printf("token: %s\n", token);
            printf("%s\n",buf );
            delim=dup[token-buf+strlen(token)];
            printf("delim : %c\n", delim);
            
            execArgs[i]=token;
            // if(delim=='|')
            // {
            //     execArgs[++i]=malloc(sizeof(delim));
            //     *execArgs[i]=delim;
            // }    
             token = strtok(NULL, delimit);
            i++;

        }
    
        execArgs[i]=NULL;



        
        
                if ((pid = fork()) < 0) {
                        err_sys("fork error");
                } else if (pid == 0) {      /* child */
                        // execvp("ls", argv);
                         
                         
                       
                        execvp(execArgs[0], execArgs);

                        err_ret("couldn't execute: %s", execArgs);
                         exit(127);
                    }
                /* parent */
                if ((pid = waitpid(pid, &status, 0)) < 0)
                        err_sys("waitpid error");

      
        
    
            }
            
        
        exit(0);
}



void
sig_int(int signo)
{
        printf("interrupt\n%% ");
}