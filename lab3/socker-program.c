#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>
int main(){
int sockfd;
struct sockaddr_in my_addr;
sockfd=socket(PF_INET,SOCK_STREAM,0);
printf("Value of sockfd is :%d\n",sockfd);
if(sockfd==-1)
{
printf("Unuccessful.\n");
}
else
{
printf("Socket creation successful.\n");
}
my_addr.sin_family=AF_INET;
my_addr.sin_port=htons(4000);
my_addr.sin_addr.s_addr=INADDR_ANY;
int b=bind(sockfd,(struct sockaddr*)&my_addr,sizeof(my_addr));
printf("Value of bind is :%d\n",b);
if(b==-1)
{
printf("Bind Unuccessful.");
}
else
{
printf("Bind Successful.");
}

return 0;
}