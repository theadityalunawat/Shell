void redirect(char **commands,int count)
{
 int i;
  int j=0,k=0;
 char *E[100][1024];


  for(i=0;i<count;i++)
  {

    char p[2]=" ";
    char *token;
    token=strtok(commands[i],p);
    int length=strlen(token);
     while(token != NULL)
      {
       E[k][j]=(char*)malloc(strlen(token));
       strcpy(E[k][j],token);
       j++;
       token=strtok(NULL,p);
      }
      E[k][j]=NULL;
      j=0;
      k++;
   }
 char curDirt[5000];
 getcwd(curDirt,5000);
 strcat(curDirt,"/");
 strcat(curDirt,E[k-1][j]);
  printf("%s\n",curDirt);
  int fd=open(curDirt,O_WRONLY | O_APPEND | O_CREAT,0664);
  
  	if(fork()==0)
	{
	 dup2(fd,1);
	 close(fd);
	 execvp(E[0][0],E[0]); 
	}
	else
     wait(NULL);
    

}

