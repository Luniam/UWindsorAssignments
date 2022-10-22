/**
 * Inage file rotator
 * Mainul Islam Mahi
 * Compile: gcc main.c -o main
 * Run: ./main /path/to/directory
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv) {
    //open the file
    int fd = open(argv[1], O_RDWR | O_CREAT);
    printf("fd = %d\n", fd);

    //Get total byte size
    off_t totalBytes;
    totalBytes = lseek(fd, 0, SEEK_END);
    printf("Total file size %lld\n", totalBytes);

    //Going to the beginning
    lseek(fd, 0, SEEK_SET);
    char header[100]; // not using the header because there is another easier solution
    read(fd, header, 100);

    long startPos = 15; //found from experimenting that the header is 15 bytes

    while (startPos <= totalBytes) {
        //read from start
        lseek(fd, startPos, SEEK_SET);
        int *startBuf = malloc(sizeof(int) * 1);
        read(fd, startBuf, 1);
        //read from end
        int *endBuf = malloc(sizeof(int) * 1);
        lseek(fd, totalBytes, SEEK_SET);
        read(fd, endBuf, 1);

        //write end to start
        lseek(fd, startPos, SEEK_SET);
        write(fd, endBuf, 1);

        //write start to end
        lseek(fd, totalBytes, SEEK_SET);
        write(fd, startBuf, 1);

        free(startBuf);
        free(endBuf);

        startPos++;
        totalBytes--;
    }

    //close the file
    close(fd);
    return 0;
}