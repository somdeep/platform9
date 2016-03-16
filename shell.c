#include <stdlib.h>
#include <time.h>
#include "apue.h"
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <stdio.h>  
#include <unistd.h> 


static void sig_int(int);       

int
main(int argc,char * argv[])
{
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
        printf("\n%%");
        gets(buf);
        //printf("%s\n",buf );
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
        // printf("%s\n",first );
        // printf("%s\n",second );
       
        i=0;j=0;

        char* token = strtok(first, delimit);
        while (token) 
        {
            
            execArgs[i]=token;    
             token = strtok(NULL, delimit);
            i++;    

        }
    
        execArgs[i]=NULL;
        // printf("%s\n",first );
        // printf("%s\n",second );
        
        i=0;
        token=NULL;


        char *t = strtok(second, delimit);
        while (t) 
        {
            
            sec[i]=t;    
             t= strtok(NULL, delimit);
            i++;    

        }

        sec[i]=NULL;
        int p[2];
        pipe(p);


       
                if ((pid=fork()) == 0) {      /* child */
                        // execvp("ls", argv);
                        
                    if(sec[0])
                    {     
                        close(STDOUT_FILENO);         
                        close(p[0]);
                        dup2(p[1],STDOUT_FILENO);      
                    }
                        execvp(execArgs[0], execArgs);

                        err_ret("couldn't execute: %s", execArgs);
                         exit(127);
                    }

                if(sec[0])
                {    
                    
                if (fork() == 0) {      /* second child */
                        // execvp("ls", argv);
                         
                        close(STDIN_FILENO);         
                        close(p[1]);
                        dup2(p[0],STDIN_FILENO);      
                        execvp(sec[0], sec);

                        err_ret("couldn't execute: %s", sec);
                        exit(127);
                    }
                }

                /* parent */
                close(p[0]);
                close(p[1]);
                if ((pid = waitpid(-1, &status, WNOHANG)) < 0)
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