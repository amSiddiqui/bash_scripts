// This program implements redirection
// It redirects input to a file descriptor
// And also redirects output to a new file descriptor

// Make sure that a file with filename file1 exists in current working directory

// A new file file2 will be created that has output
// 1 50 412
// 1: number of lines
// 50: number of words
// 412: size of file in bytes

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#define STDIN 0 // Keyboard
#define STDOUT 1 // Monitor

int main(){
    int fd1, fd2;
    // Open file to read from 
	fd1 = open("file1", O_RDONLY);
    // Open file to write in, if not exist then create with file perm 0664
	fd2 = open("file2", O_WRONLY | O_CREAT, 0664);
    // Close standard input
	close(STDIN);
    // Close standard output
	close(STDOUT);
    // duplicate file 1 so that new standard output is fd1
	dup(fd1);
    // duplicate file 2 so that new standard in is fd2
	dup(fd2);
    // Execute wc
	execlp("wc", "wc", 0, NULL);
	return 0;
}

