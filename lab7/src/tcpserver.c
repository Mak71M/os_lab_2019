#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERV_PORT 10050
#define BUFSIZE 100
#define SADDR struct sockaddr

int main(int argc, char *argv[]) {
  int port = -1;
  int buff_size = -1; 
  const size_t kSize = sizeof(struct sockaddr_in);
  while (true){
    int current_optind = optind ? optind : 1;
    static struct option options[] = {{"port", required_argument, 0, 0},
                                      {"buff_size", required_argument, 0, 0},
                                      {0, 0, 0, 0}};
    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);
    if (c == -1)
      break;
    
    switch(c){
      case 0:
        switch(option_index){
          case 0:
            port = atoi(optarg);
            break;
          case 1:
            buff_size = atoi(optarg);
            break;
          default:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case '?':
        printf("Unknown argument\n");
        break;
      default:
        fprintf(stderr, "getopt returned character code 0%o?\n", c);
    }
  }

   if (port == -1 || buff_size == -1) {
    printf("Using: --port 20001 --buff_size 100\n");
    port = SERV_PORT;
    buff_size = BUFSIZE;
    printf("The default params are port = %d and buff_size %d\n", SERV_PORT, BUFSIZE);
  }
  
  int lfd, cfd;
  int nread;
  char buf[buff_size];
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;

  if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  memset(&servaddr, 0, kSize);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(lfd, (SADDR *)&servaddr, kSize) < 0) {
    perror("bind");
    exit(1);
  }

  if (listen(lfd, 5) < 0) {
    perror("listen");
    exit(1);
  }

  while (1) {
    unsigned int clilen = kSize;

    if ((cfd = accept(lfd, (SADDR *)&cliaddr, &clilen)) < 0) {
      perror("accept");
      exit(1);
    }
    printf("connection established\n");

    while ((nread = read(cfd, buf, buff_size)) > 0) {
      write(1, &buf, nread);
    }

    if (nread == -1) {
      perror("read");
      exit(1);
    }
    close(cfd);
  }
}