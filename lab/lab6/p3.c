// Take Details of student.
// Save in a file.
// Print all the names of the student stored in that file.

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

#define NAMESIZE 20
#define AGESIZE 5
#define BRANCHSIZE 8
#define CITYSIZE 10
#define GSIZE 1

#define STDIN 0
#define STDOUT 1

int fileAppend(int, char*);
void appendSpaces(char*, int);

int main(int argc, char const *argv[])
{
    pid_t pid;
    char filename[20] = "student_record";

    // Child Takes input from the user and writes into the file.
    pid = fork();
    if (pid < 0){
        printf("Can't fork\n");
        return 1;
    }
    if (pid == 0){
        // Child process
        // Open file as write
        int fd = open(filename, O_APPEND | O_WRONLY);
        if ( fd <= 0){
            char detail[50];
            int no_of_student;
            char dum[3];
            printf("Enter the number of students: ");scanf("%d", &no_of_student);
            gets(dum);
            for(int i=0; i<no_of_student; i++){
                printf("Details of student %d\n", i+1);
                printf("Name: ");
                gets(detail);
                // Append spaces after detail
                appendSpaces(detail, NAMESIZE-strlen(detail));
                // Write in file
                fileAppend(fd, detail);
                printf("Age: ");
                gets(detail);
                // Append spaces after detail
                appendSpaces(detail, AGESIZE-strlen(detail));
                fileAppend(fd, detail);
                printf("Branch: ");
                gets(detail);
                // Append spaces after detail
                appendSpaces(detail, BRANCHSIZE-strlen(detail));
                fileAppend(fd, detail);
                printf("City: ");
                gets(detail);
                // Append spaces after detail
                appendSpaces(detail, CITYSIZE-strlen(detail));
                fileAppend(fd, detail);
                printf("Gender: ");
                gets(detail);
                // Append \r \n
                strcat(detail, "\r\n");
                fileAppend(fd, detail);
            }
            close(fd);
        }
        else {
            fprintf(stderr, "File does not exists\n");
            return 1;
        }
    }
    else{ 
        // Parent Part
        wait(NULL);

        // Read from the file and print all the names
        int line_length = AGESIZE + BRANCHSIZE + GSIZE + CITYSIZE + 2;
        int fd = open(filename, O_RDONLY);
        if ( fd <= 0){
            char read_name[20];
            printf("\nStudents\n");
            while(read(fd, read_name, NAMESIZE)){
            read_name[20] = '\0';
            printf("%s\n", read_name);
            lseek(fd, line_length, SEEK_CUR);
            }
            close(fd);
            printf("Process completed. File saved\n");
        }else{
            fprintf(stderr, "File does not exists\n");
            return 1;
        }
    }
    return 0;
}

int fileAppend(int fd, char data[]){
    write(fd, data, strlen(data));
}

void appendSpaces(char data[], int spaces){
    for(int i=0; i<spaces; i++){
        strcat(data, " ");
    }
}