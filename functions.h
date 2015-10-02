int functions(char **C)
{
 
 pid_t pid;
 pid=fork();
  if(pid == -1)
    return 0;
  else if(pid == 0)
   {
    execvp(C[0],C);
    printf("Command not found\n");
   }
   else
   {
    wait(NULL);
   }
   return 1;
}
