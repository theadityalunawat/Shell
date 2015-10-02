void ex(char **commands,int count)
{
 int i;
  int j=0,k=0;
 char *E[100][1024];


  for(i=0;i<count;i++)
  {

    char p[2]=" ";
    char *token;
    token=strtok(commands[i],p);
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
//  printf("%s\n",E[0][0]);
//  printf("%s\n",E[0][1]);
//  printf("%s\n",E[1][0]);
//  printf("%s\n",E[1][1]);
//   
  int fd[2];
  if(fork() == 0)
  {   
  for(i=0;i<count-1;i++)
  {
  
   pipe(fd);
   
	if(fork()==0)
	{
	 
	 dup2(fd[1],1); 
	 execvp(E[i][0],E[i]);
	}
	 
	dup2(fd[0],0);
	close(fd[1]);
	
  }
   
    wait(NULL);
    execvp(E[i][0],E[i]);
  }
  
  else
    {
     wait(NULL);
    }
  
}
