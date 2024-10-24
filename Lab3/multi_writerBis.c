#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#define PERM 0644   /* UNIX */

int main(int argc, char *argv[]) {
    int pid, nchildren, nblocks, status, ret, j, k;
    int bufsize = 200;
    long long expected;
    long long calculated;
    char error[bufsize];
    int fd;
    char ch;

    if (argc != 3) {
        snprintf(error, bufsize, "Invalid arguments!\n");
        perror(error);
        exit(1);
    }
    
    nblocks = atoi(argv[1]);

    if (nblocks <= 0) {
        perror("Number of blocks can't be < 1");
        exit(2);
    }

    /* Create file */ 
    if ((fd = creat (argv[2], PERM)) < 0 ) {
        perror("creat");
        exit(3);
    }
    
    for (j = 0; j < nchildren; j++) {
        if ((pid=fork()) < 0) {
        	perror("fork");
		    exit(4);
        }


    	lseek(fd, 0L, SEEK_END);

        if (pid == 0) {

            for (k = 0; k < nblocks; k++) {
                ch = '0' + j;

                if (write(fd, &ch, 1) != 1) {
                    perror("write");
                    exit(-1);
    		    }  
	        }
            exit(0);
        }
    }

    for (j = 0; j < nchildren; j++) {
     	pid = wait(&status);
        if (pid < 0) {
        	perror("wait");
            exit(6);
        }

        if ((status & 0xFF) != 0) {
            snprintf(error, bufsize, "Error in child %d\n", pid);
	    	perror(error);
        } else { 
		    ret=(int)((status >> 8) & 0xFF);
            snprintf(error, bufsize, "Child %d returned %d\n", pid, ret);
            perror(error);
        }
    }

    return 0;
}