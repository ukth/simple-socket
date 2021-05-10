#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]){
  int sock;
  int isSender = 0;

  struct sockaddr_in server_addr;

  char msg[100] = {0, };

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1){
    printf("socket err\n");
    return 0;
  }

  memset(&server_addr, 0, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  server_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
    printf("connect err\n");
    return 0;
  }

  if (read(sock, msg, sizeof(msg)-1) == -1){
    printf("read err\n");
    return 0;
  }
  printf("%s\n",msg);

  if (strstr(msg, "sender") != NULL){
    isSender = 1;
  }

  char user_msg[100] = {0,};
  if (isSender){
    scanf("%[^\n]",user_msg);
    write(sock, user_msg, sizeof(user_msg));
    printf("Message sent!\n");
  } else{
    if (read(sock, user_msg, sizeof(user_msg)-1) == -1){
      printf("read err\n");
      return 0;
    }
    printf("received message:\n%s\n",user_msg);
  }

  close(sock);
  return 1;

}



