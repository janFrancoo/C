#include <unistd.h>

#define BUFF_SIZE (1024)   /* for client read/write */
#define BACKLOG     (12)   /* maximum number of concurrent clients */
enum {false, true};        /* 0 and 1, respectively */
typedef unsigned bool;     /* bool aliases unsigned int */

/* declarations for functions in utils.c */
void error_msg(const char* msg, bool halt_flag);
int create_server_socket(bool non_blocking);
void announce_client(struct in_addr* addr);
void generate_echo_response(char request[ ], char response[ ]);
