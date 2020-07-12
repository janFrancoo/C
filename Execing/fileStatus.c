#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: status <path to file>\n");
    return -1;
  }
  
  struct stat status;
  memset(&status, 0, sizeof(struct stat));
  printf("File name: %s\n", argv[1]);
  stat(argv[1], &status); /* file name, pointer to stat struct */    /** line 1 **/

  /* Get time of last access -- in several steps for emphasis */
  time_t my_time = status.st_atime;
  char buffer[1024];
  ctime_r(&my_time, buffer);

  /* Get status: directory or regular */
  char* type;
  if (S_ISREG(status.st_mode)) type = "regular";
  else if (S_ISDIR(status.st_mode)) type = "directory";
  else type = "other (neither regular nor directory)";

  /* ower read/write status */
  int readable = status.st_mode & S_IRUSR;
  int writable = status.st_mode & S_IWUSR;
  char* readO  = (readable) ? "Owner readable" : "Not owner readable";
  char* writeO = (writable) ? "Owner writable" : "Not owner writable";

  /** Print information. **/
  printf("\nInformation about file %s", argv[1]);
  printf(":\n\n");

  printf("Owner ID:    %lu\n", (unsigned long) status.st_uid);
  printf("Group ID:    %lu\n", (unsigned long) status.st_gid);
  printf("Byte size:   %lu\n", (unsigned long) status.st_size);
  printf("Last access: %s",    buffer);
  printf("File type:   %s\n",  type);
  printf("Owner read:  %s\n",  readO);
  printf("Owner write: %s\n",  writeO);

  return 0;
}
