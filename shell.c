#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main()
{
    char *stringuri[1024];
    char *stringuri1[1024];
    char *stringuri2[1024];
    char *stringuri3[1024];
    char *string=NULL;
    size_t len;
    ssize_t n;
    while((n=getline(&string,&len,stdin))!=-1)
    {
        string[strlen(string)-1]='\0';
        int i=0;
        char *sign="nimic";
        while(i<strlen(string))
        {
            if(string[i]=='&' && string[i+1]=='&')
            {
                stringuri1[0]=strtok(string,"&&");
                stringuri1[1]=strtok(NULL,"&&");
                sign="&&";
                break;
            }
            if(string[i]=='|' && string[i+1]=='|')
            {
                stringuri1[0]=strtok(string,"||");
                stringuri1[1]=strtok(NULL,"||");
                sign="||";
                break;
            }
            i++;
        }
        if(strcmp(sign,"nimic")==0)
        {
            i=0;
            stringuri1[i]=strtok(string," ");
            while(stringuri1[i]!=NULL)
            {
                i++;
                stringuri1[i]=strtok(NULL," ");
            }

            pid_t pid = fork(); 
            if (pid == -1)
            { 
                printf("\nCopilul nu a putut fi creat"); 
                continue;
            } else
                if (pid==0)
                { 
                    if(execvp(stringuri1[0],stringuri1)<0)
                    { 
                        printf("\nComanda nu a putut fi executata"); 
                    } 
                    exit(0); 
                } else
                    {
                        wait(NULL); 
                    }
            continue;
        }
        
        i=0;
        stringuri2[i]=strtok(stringuri1[0]," ");
        while(stringuri2[i]!=NULL)
        {
            i++;
            stringuri2[i]=strtok(NULL," ");
        }
        i=0;
        stringuri3[i]=strtok(stringuri1[1]," ");
        while(stringuri3[i]!=NULL)
        {
            i++;
            stringuri3[i]=strtok(NULL," ");
        }

        pid_t pid = fork(),pid2; 
        if(pid<0)
        {
            printf("\nCopilul nu a putut fi creat");
            continue;
        } 
        if(pid==0)
        {
            if(execvp(stringuri2[0],stringuri2)<0)
            {
                printf("\nComanda nu a putut fi executata");
            } 
            exit(0);
        }
        else
        {
            pid2 = fork(); 
            if(pid2<0)
            { 
                printf("\nCopilul nu a putut fi creat");
                continue;
            } 
            if(pid2==0)
            { 
                if(execvp(stringuri3[0],stringuri3)<0)
                {
                    printf("\nComanda nu a putut fi executata");
                }
                exit(0);
            }
            else
            { 
                wait(NULL);
            } 
        } 
    }
}