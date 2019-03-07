// Sessional Program 1
// WAP using pipe in which Child process writes a filename into the pipe
// and the Parent process counts the number of characters in the file
// and displays the count on the monitor

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

#define STDIN 0
#define STDOUT 1
#define PIPEIN 0
#define PIPEOUT 1


void filewrite (int, int);

int main(int argc, char const *argv[])
{
    // Input file name from command line
    if ( argc < 2) {
        fprintf(stderr, "Please enter one file name.\n");
        return 1;
    }
    else if (argc > 2) {
        fprintf(stderr, "Please enter only one filename.\n");
        return 1;
    }
    char *filename = (char *)calloc(strlen(argv[1]), sizeof(char));
    strcpy(filename, argv[1]);
    
    // Create a pipe
    int pf[2];
    if (pipe(pf) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    // Create a child process
    pid_t pid;
    pid = fork();
    if( pid < 0 ){
        // Error case
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    if (pid == 0){
        // Child process
        // Write file name into the pipe
        close(pf[PIPEIN]);
        write(pf[PIPEOUT], filename, strlen(filename)+1 );
        close(pf[PIPEIN]);
    }
    else if (pid > 0){
        // Parent process
        // Wait for child to finish
        wait(NULL);
        // read file name from pipe
        close(pf[PIPEOUT]);
        char file[100];
        char buff[BUFSIZ];
        int n; // holds the number of bytes read from pipe
        while((n = read(pf[PIPEIN], buff, BUFSIZ) > 0)){
            strcat(file, buff);
        }
        // open file and read number of character
        int fd;
        fd = open(filename, O_RDONLY);
        if (fd < 0){
            fprintf(stderr, "File open Error.\nPlease Check if the file exists or if you have permessions to open it.\n");
            return 1;
        }
        int size = 0;
        n = 0;
        while((n = read(fd, buff, BUFSIZ)) > 0){
            size += n;
        } 
        printf("File Size in bytes: %d\n", size);
        close(pf[PIPEIN]);
        close(fd);
    }
    return 0;
}
