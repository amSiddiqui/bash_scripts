// This program shows the working of cat command
// To copy out files pass file name from command line, eg: ./a.out file1 file2

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

void filecopy(int ,int );

#define STDIN 0
#define STDOUT 1

int main(int argc,char *argv[])
{
    int fd;
    // If no arguments are passed then take input from STDIN
    if(argc == 1)
        filecopy(STDIN, STDOUT);
    else{
        // Else read all the file and output them to STDOUT
        while(--argc > 0){
            fd = open(*++argv,O_RDONLY);
            filecopy(fd, STDOUT);
            close(fd);
        }
    }
    return 0;
}

void filecopy(int ifd,int ofd)
{
    // This function read from file descriptor ifd and writes in file descriptor ofd
    int n;
    char buf[BUFSIZ];
    while((n=read(ifd,buf,BUFSIZ)) > 0)
    write(ofd,buf,n);
}
