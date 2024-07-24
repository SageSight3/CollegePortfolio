#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

int main (int argc, char** argv) {

    //argc is like string.length() in java, is 1 bigger than the largest index in the array
    //debugging, checking args
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }
    cout << "argc = " << argc << endl;
    cout << endl;
    //validate in and out files
    //in file check/inFile fd array creation

    int inFile_fds[argc-2];
    for (int arg = 0; arg < argc - 2; ++arg) {
        inFile_fds[arg] = open(argv[arg + 1], O_RDONLY);
        if (inFile_fds[arg]== -1) {
            cout << "inFile error: " << argv[arg + 1] << endl;
            exit(1);

            //close any opened files
            for (int inFile = 0; inFile < arg; ++inFile) {
                cout << "Closing " << argv[inFile + 1] << endl;
                close(inFile_fds[inFile]);
            }
        }
        cout << "inFile_fds[" << arg << "] " << inFile_fds[arg] << endl;
    }
    cout << endl;

    //out file check
    int outFile_fd = open(argv[argc - 1], O_RDONLY);
    if (outFile_fd > -1) {
        cout << "outFile: " << argv[argc - 1] << " already exists" << endl;
        close(outFile_fd);
        exit(1);
    }
    
    //out file creation
    outFile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644); //https://stackoverflow.com/questions/18415904/what-does-mode-t-0644-mean
    if (outFile_fd == -1) { //O_CREAT and S_IRWXG from https://man7.org/linux/man-pages/man2/open.2.html
        cout << "outFile no work: " << argv[argc - 1] << endl;
        close(outFile_fd);
        exit(1);
    }

    //get inFiles total size
    int outFileSize = 0;
    struct stat inFileInfo[argc-2]; //is array for inFile mapping
    for (int inFile = 0; inFile < argc - 2; ++inFile) {
        cout << "Getting size info on " << argv[inFile + 1] << endl;
        if (fstat(inFile_fds[inFile], &inFileInfo[inFile])) {
            cout << "Error getting info on " << argv[inFile + 1] << endl;
            // Close file descriptors:
            for (int openInFile = 0; openInFile < argc - 2; ++openInFile) {
                cout << "Closing " << argv[openInFile + 1] << endl;
                close(inFile_fds[openInFile]);
            }
            cout << "Closing " << argv[argc-1] << endl;
            close(outFile_fd);
            exit(1);
        }
        cout << "Size of " << argv[inFile + 1] << " " << inFileInfo[inFile].st_size << endl;

        outFileSize = outFileSize + inFileInfo[inFile].st_size;
    }
    cout << "outFileSize " << outFileSize << endl; //debug
    cout << endl;

    //truncate outFile to outFileSize
    if (ftruncate(outFile_fd, outFileSize)) {
        cout << "Error setting outFile size: " << argv[argc - 1] << endl;
        // Close file descriptors:
        for (int openInFile = 0; openInFile < argc - 1; ++openInFile) {
            close(inFile_fds[openInFile]);
        }
        close(outFile_fd);
        exit(1);
    }

    //copy in files into out file

    //map outFile and close descriptor
    char *outFile = static_cast<char*>(mmap(NULL, outFileSize, PROT_WRITE, MAP_SHARED, outFile_fd, 0));
    if (madvise(outFile, outFileSize, MADV_SEQUENTIAL) == -1) {
        cout << "outFile madvise failed" << endl;
    }
    //static_cast<char*> from https://stackoverflow.com/questions/23258521/invalid-conversion-from-void-to-char-when-using-mmap
    if (outFile == MAP_FAILED) {
        cout << "outFile map failed" << argv[argc - 1] << endl;
        // Close file descriptors:
        for (int openInFile = 0; openInFile < argc - 1; ++openInFile) {
            close(inFile_fds[openInFile]);
        }
        close(outFile_fd);
        exit(1);
    }
    close(outFile_fd);

    //map inFiles and copy them to outFile
    char *outWritePtr = outFile; //outWritePtr declared outside loop to remember position
    for (int inFileNum = 0; inFileNum < argc - 2; ++inFileNum) {
        cout << "Attempting to map " << argv[inFileNum + 1] << endl; //debug
        char *inFile = static_cast<char*>(mmap(NULL, inFileInfo[inFileNum].st_size, PROT_READ, MAP_PRIVATE, inFile_fds[inFileNum], 0));
        if (madvise(inFile, inFileInfo[inFileNum].st_size, MADV_SEQUENTIAL) == -1) { //needs to be as soon after mmap as possible, to give os as much time as can to process
            cout << "inFile madvise failed" << endl;
        }
        cout << "inFile " << inFileNum << " fd and size: " << inFile_fds[inFileNum] << " " << inFileInfo[inFileNum].st_size << endl; //debug
        if (inFile == MAP_FAILED) {
            cout << "inFile map failed" << argv[inFileNum + 1] << endl;
            // Close file descriptors and unmap outFile:
            munmap(outFile, outFileSize);
            for (int openInFile = 0; openInFile < argc - 1; ++openInFile) {
                close(inFile_fds[openInFile]);
            }
            exit(1);
        }
        close(inFile_fds[inFileNum]);

        //copy inFile contents to outFile
        char *inReadPtr = inFile;
        for (int ptrNum = 0; ptrNum < inFileInfo[inFileNum].st_size; ++ptrNum) {
            *outWritePtr++ = *inReadPtr++;
        }

        //unmap inFile
        munmap(inFile, inFileInfo[inFileNum].st_size);
    }
    munmap(outFile, outFileSize);
}