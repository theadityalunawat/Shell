void redirect_in(char **commands,int count)
{
 if(fork()==0)
 {
 int i;
  
   
 char *curDirt=(char*)malloc(5000);
  strcpy(curDirt,(char*)commands[1]);
  
  int fd=open(curDirt,O_RDWR | O_APPEND | O_CREAT,0664);
  
  	if(fork()==0)
	{
	 dup2(fd,0);
	 close(fd);
	 execvp(commands[0],commands); 
	 printf("Command not found\n");
	}
	else
     wait(NULL);
   }
   else
   wait(NULL);
}
