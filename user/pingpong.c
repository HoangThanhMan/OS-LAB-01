#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main()
{
	int p1[2], p2[2]; // p1: parent, p2: children
	
	char *ping = "ping";
	char *pong = "pong";
	char buff[512]={0};

	pipe(p1);
	pipe(p2);

	int child_id = fork();

	if(child_id==0) 
	{
		// Children
		close(p1[1]);
		close(p2[0]);
		
		write(p2[1], pong, strlen(pong));

		read(p1[0], buff, sizeof(buff));
		printf("%d: received %s\n", getpid(),buff);
		exit(0);  
	}
	else
	{
		// Parent
		close(p1[0]);
		close(p2[1]);
			
		write(p1[1], ping, strlen(ping));

		read(p2[0], buff, sizeof(buff));
		printf("%d: received %s\n", getpid(), buff);
		exit(0);	
	}
}

