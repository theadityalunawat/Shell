void free(char **B)
{
 int i;
 for(i=0;i<100;i++)
 {
  free(B[i]);
 }
}
