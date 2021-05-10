#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]){
  int server;
  int sender;
  int receiver;

  struct sockaddr_in server_addr;
  struct sockaddr_in sender_addr;
  struct sockaddr_in receiver_addr;

  socklen_t addr_n = sizeof(sender_addr);

  server = socket(PF_INET, SOCK_STREAM, 0);
  if (server == -1){
    printf("socket err\n");
    return 0;
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(argv[1]));

  if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
    printf("bind err\n");
    return 0;
  }

  if (listen(server, 5) == -1){
    printf("listen err\n");
    return 0;
  }

  sender = accept(server, (struct sockaddr *)&sender_addr, &addr_n);

  if (sender == -1){
    printf("accept err\n");
    return 0;
  }

  receiver = accept(server, (struct sockaddr *)&receiver_addr, &addr_n);

  if (receiver == -1){
    printf("accept err\n");
    return 0;
  }

  printf("2 clients are connected\n");

  char sender_msg[] = "READY: You are a sender.\n";
  char receiver_msg[] = "READY: You are a receiver.\n";
  char senders_msg[100] = {0,};


  write(sender, sender_msg, sizeof(sender_msg));
  write(receiver, receiver_msg, sizeof(receiver_msg));

  if (read(sender, senders_msg, sizeof(senders_msg)-1) == -1){
    printf("read err\n");
    return 0;
  }

  printf("\n`%s`\nreceived from sender\n\n", senders_msg);

  write(receiver, senders_msg, sizeof(senders_msg));

  printf("message relayed\n");

  close(server);
  close(sender);
  close(receiver);

  return 0;
}



