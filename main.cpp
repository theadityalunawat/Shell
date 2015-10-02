#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"
#include "exe.h"
#include "free.h"
#include "redirect.h"
#include "redirectin.h"
#include<fstream>
#include<iostream>
using namespace std;
int count1=0;
int count2=0;



char **parse_redirect_inflag(char *enter)
{
 int i;
 
 char **A;
 A=(char **)malloc(sizeof(char*) * 100 );
 for( i=0 ; i<100 ; i++)
  {
 	A[i]=(char *)malloc(1024);
 
  }
 
 
 const char t[2]="<";
 char *token;
 token=strtok(enter,t);
  i=0;
 while(token != NULL)
  {
   
   strcpy(A[i],token);
   i++;
   count2++;
   token=strtok(NULL,t);
  }
  A[i]='\0';
  return A;
}

char **parse_redirect(char *enter)
{
 int i;
 
 char **A;
 A=(char **)malloc(sizeof(char*) * 100 );
 for( i=0 ; i<100 ; i++)
  {
 	A[i]=(char *)malloc(1024);
 
  }
 
 
 const char t[2]=">";
 char *token;
 token=strtok(enter,t);
  i=0;
 while(token != NULL)
  {
   strcpy(A[i],token);
   i++;
   count2++;
   token=strtok(NULL,t);
  }
  A[i]='\0';
  return A;
}


char **parse_simple(char *enter)
{
 int i;
 
 char **A;
 A=(char **)malloc(sizeof(char*) * 100 );
 for( i=0 ; i<100 ; i++)
  {
 	A[i]=(char *)malloc(1024);
 
  }
 
 
 const char t[2]=" ";
 char *token;
 token=strtok(enter,t);
  i=0;
 while(token != NULL)
  {
   strcpy(A[i],token);
   i++;
   count2++;
   token=strtok(NULL,t);
  }
  A[i]='\0';
  return A;
}


char **parse_pipe(char *enter)
{
 int i,j;

 char **A;
 A=(char **)malloc(sizeof(char*) * 100 );
 for( i=0 ; i<100 ; i++)
  {
 	A[i]=(char *)malloc(1024);

  }
 const char t[2]="|";
 char *token;
 token=strtok(enter,t);
  i=0;
 while(token != NULL)
  {
   strcpy(A[i],token);
   i++;
   count2++;
   token=strtok(NULL,t);
  }
   A[i]='\0';
  return A;
}


int main()
{ 
    
    int i, command,len,count=0;
	char inputString[5000];
	char curDir[5000];
	char **collect;
	char hm[100];
	strcpy(hm,getenv("HOME"));  
    chdir(hm);
    char his[500];
    strcpy(his,hm);
    strcat(his,"/");
    char his1[500];
    strcpy(his1,his);
    strcat(his,"history.txt");
    strcat(his1,"history1.txt");
    ofstream fout;
    ofstream fout1;
	fout.open(his);
	fout.close();
	fout1.open(his1);
	fout1.close();
	while(1)
	{   ofstream fout,fout1;
	    fout.open(his,ios::app|ios::in|ios::out);
	    fout1.open(his1,ios::app|ios::in|ios::out);
	     
	    
		 getcwd(curDir,5000);
		 printf("%s@%s~$", getlogin(),curDir);
		fgets(inputString,4999,stdin);
		len=strlen(inputString);
		inputString[len-1]='\0';
		if(inputString[0] != '!')
		{
		 count1=count1+1;
		 fout << count1 <<" ";
		 fout <<inputString<<"\n";
		 fout1 <<inputString<<"\n";
		}
		int pipe_flag=0,redirect_inflag=0,redirect_outflag=0;
		  if(inputString[0] == '!')
	        {
	        
	          if(inputString[1]=='!')
               {
                  int count3=0;

	          ifstream fin;
              fin.open(his1,ios::in);
              
              string line;
              for (i = 1; getline(fin, line);i++)
                   count3++;
                   fin.close();
                 fin.open(his1,ios::in);
                   int st=count3;
          
               for (i = 1; getline(fin, line);i++)
                {
                 if(i == st)
                  {
                    char abc[500];
                     strcpy(abc,line.c_str());
                     strcpy(inputString,abc);
                     
                  }
                }
               }
	         else if(inputString[1] !='-')
	         {
	         int b=(int)inputString[1];
	         b=b-48;
	         ifstream fin;
             fin.open(his1,ios::in);
              
             string line;
 
               for (i = 1; getline(fin, line);i++)
                {
                 if(i == b)
                  {
                    char abc[500];
                     strcpy(abc,line.c_str());
                     strcpy(inputString,abc);
                     
                  }
                }
               }
             
              else
              {
              int count3=0;
              int b=(int)inputString[2];
	          b=b-48;
	          b=b-1;
	          ifstream fin;
              fin.open(his1,ios::in);
              
              string line;
              for (i = 1; getline(fin, line);i++)
                   count3++;
                   fin.close();
                 fin.open(his1,ios::in);
                   int st=count3-b;
                   printf("%d\n",st);
               for (i = 1; getline(fin, line);i++)
                {
                 if(i == st)
                  {
                    char abc[500];
                     strcpy(abc,line.c_str());
                     strcpy(inputString,abc);
                     
                  }
                }
              }
	        }
	     for(int s=0;s<len-1;s++)
	      {
	       if(inputString[s] == '|')
	        {
	         pipe_flag=1;
	         collect=parse_pipe(inputString);
	         break;
	        }
	          
	      }
	      for(int s=0;s<len-1;s++)
	      {
	       if(inputString[s] == '>')
	        {
	         redirect_outflag=1;
	         collect=parse_redirect(inputString);
	         break;
	        }
	          
	      }
	      for(int s=0;s<len-1;s++)
	      {
	       if(inputString[s] == '<')
	        {
	         redirect_inflag=1;
	         collect=parse_redirect_inflag(inputString);
	         break;
	        }
	          
	      }
	      
	      if(pipe_flag == 0 && redirect_outflag == 0 && redirect_inflag==0)
	          collect=parse_simple(inputString);
	        
		
		if(strcmp(inputString,"exit") == 0)
	      {
	       
	       printf("Bye...");
	       printf("\n");
	      exit(0);
	      }

	      if(strcmp(inputString,"pwd")== 0)
	      {
	       getcwd(curDir,5000);
	       printf("%s",curDir);
	       printf("\n");
	      }
	     
	      else if(strcmp(collect[0],"cd") == 0)
	     {
	      strcpy(curDir,collect[1]);
	      chdir(collect[1]);
	     
	     }
	      else if(strcmp(inputString,"history") == 0)
	       {
	        char **temp;
	        temp=(char**)malloc(sizeof(char*)*3);
	        for(i=0;i<2;i++)
	        temp[i]=(char*)malloc(1024);
	        strcpy(temp[0],"cat");
	        strcpy(temp[1],his);
	        temp[3]='\0';
	        int por=functions(temp);
	       }
	      else if(collect[0][0]=='e' && collect[0][1]=='c')
          {
          if(collect[1][0]=='$')
	       {
	        int i,j;
			char H[50];
			j=0;
			for(i=1;i<strlen(collect[1]);i++)
			 H[j++]=collect[1][i];
			 //char pPath[50];
			char *pPath=getenv(H);
			if (pPath!=NULL)
			printf ("%s\n",pPath);
			else
			 printf("\n");
	       }
	      }
	    else
	    {
	     
	         if(pipe_flag == 1)
	           ex(collect,count2);
	            else if(redirect_inflag == 1)
	         {    
	          redirect_in(collect,count2);
	         }
	         else if(redirect_outflag == 1)
	           redirect(collect,count2);
	           else if(redirect_inflag == 1)
	            redirect_in(collect,count2);
	        else
	       {
	        int other=functions(collect);
	       }
	    } 
	  
	    fout.close(); 
	    fout1.close(); 
	}
	free(collect);
	
	return 0;
}

