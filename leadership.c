#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void err_sys(char* message)
{
perror(message);	
exit(EXIT_FAILURE);
}	
void main(int argc,char* argv[])
{
pid_t pid,pgid,child_pid;
int i,res;

pid=getpid();
pgid=getpgrp();
printf("Parent.My PID is : %d,My group PID is : %d\n",pid,pgid);
res=setpgid(0,0);

if(res==-1){
err_sys("setpgid");
}
printf("Parent.I am the group leader now \n");

for(int i=0;i<3;i++){
child_pid=fork();
if(child_pid<0){
err_sys("fork");
}
if(child_pid==0){
break;
}
}

if(child_pid==0){
pid=getpid();
pgid=getpgrp();

printf("I am the Child %d .My PID is : %d,My group PID is : %d \n",i,pid,pgid);
sleep(1);
res=setpgid(0,0);

if(res==-1){
err_sys("setpgrp");
}

pid=getpid();
pgid=getpgrp();

printf("Child %d.Iam independent now.My PID is:%d,My group id:%d\n",i,pid,pgid);
printf("Child %d exiting\n",i);
exit(EXIT_SUCCESS);
}
printf("parent sleeping. \n");
sleep(3);
printf("Parent, exiting ");
return EXIT_SUCCESS;
}	
	
