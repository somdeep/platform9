#include <stdlib.h>
#include <time.h>
#include "apue.h"
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <stdio.h>  

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
        char    buf[MAXLINE];
       /* from apue.h */
        char    first[MAXLINE];
        char    second[MAXLINE];
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
        int flag=0;
        char *sec[10];
        int j=0;


        for(i=0;i<len;i++)
        {
            if(buf[i]=='|')
                break;
            first[i]=buf[i];

        }

        first[i]='\0';
        i++;
        while(i<len)
        {
            second[j++]=buf[i];
            i++;

        }

        second[j]='\0';

       
        i=0;j=0;

        char* token = strtok(first, delimit);
        while (token) 
        {
            printf("token: %s\n", token);
            delim=dup[token-first+strlen(token)];
            printf("delim : %c\n", delim);
            
            execArgs[i]=token;    
             token = strtok(NULL, delimit);
            i++;    

        }
    
        execArgs[i]=NULL;

        i=0;
        token = strtok(second, delimit);
        while (token) 
        {
            printf("token: %s\n", token);
            delim=dup[token-second+strlen(token)];
            printf("delim : %c\n", delim);
            
            sec[i]=token;    
             token = strtok(NULL, delimit);
            i++;    

        }

        sec[i]=NULL;
        
                if ((pid = fork()) < 0) {
                        err_sys("fork error");
                } else if (pid == 0) {      /* child */
                        // execvp("ls", argv);
                         
                         
                       
                        execvp(sec[0], sec);

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
        printf("Exiting\n");

        exit(0);
}