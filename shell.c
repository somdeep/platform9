#include<stdlib.h>
#include<time.h>
#include "apue.h"
#include <sys/wait.h>
#include <string.h>
#include<math.h>


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

        if(argc==1)
            strcpy(buf,"ls");
            
        else if(argc>1)
        strcpy(buf,argv[1]);

        char *execArgs[argc];

        for (int i = 0; i < argc-1; ++i)
        {
            execArgs[i]=argv[i+1];
        }
        execArgs[argc-1]=NULL;



       // printf("%s\n",buf );
        
                if ((pid = fork()) < 0) {
                        err_sys("fork error");
                } else if (pid == 0) {      /* child */
                        // execvp("ls", argv);
                         
                        execvp(argv[1], execArgs);

                        err_ret("couldn't execute: %s", argv);
                        exit(127);
                }
               /* parent */
                if ((pid = waitpid(pid, &status, 0)) < 0)
                        err_sys("waitpid error");

      
        
    
                
            
        
        exit(0);
}

void
sig_int(int signo)
{
        printf("interrupt\n%% ");
}