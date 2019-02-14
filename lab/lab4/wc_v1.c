// A program that counts using wc in a file or from keyboard

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

// Defining Standard Values
#define STDIN 0
#define STDOUT 1

// Function declaration
int count_words(int);

int main(int argc, char const *argv[])
{   
    if (argc == 1){
        // No arguments passed then read from keyboard
        printf("Number of words typed: %d\n", count_words(0));
    }else{
        // Read all the files and count the number of words in all of them
        int count = 0;
        int fd;
        while(--argc > 0){
            fd = open(*++argv,O_RDONLY);
            count += count_words(fd);
        }
        printf("Total number of words in all the files: %d\n", count);
    }
    return 0;
}

int count_words(int ifd)
{   
    // This function reads from file descriptor ifd and counts the number of spaces
    // Returns the value of count
    int n, i;
    int count = 0;
    char buf[BUFSIZ];
    while((n=read(ifd,buf,BUFSIZ)) > 0){
        for(i=0; i<n; i++){
            if(buf[i]==32 || buf[i]=='\n') count++;
        }
    }
    return count;
}

