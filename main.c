#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

//#include "Matrix/matrix.h"
#include "DataType/dataType.h"
#include "FileReader/file.h"
#include "Matrix/matrix.h"

void print_matrix(void*, int, DataType);

int main(int argc, char *argv[]) {
    int size;
    FILE *file;
    int c;
    int dataTypeFlag = 0;

    static struct option long_options[] = {
            {"path", required_argument, 0, 'p'},
            //{"absolute-path", required_argument, 0, 'a'},
            //{"relative-path", required_argument, 0, 'r'},
            {"char",           no_argument, 0, 'c'},
            {"int",           no_argument, 0, 'i'},
            {"float",         no_argument, 0, 'f'},
            {"double",        no_argument, 0, 'd'},
            {0, 0, 0, 0}
    };

    int option_index = 0;

//    while ((c = getopt_long(argc, argv, "a:r:cifd", long_options, &option_index)) != -1) {
    while ((c = getopt_long(argc, argv, "p:cifd", long_options, &option_index)) != -1) {
        switch (c) {
            case 'p':
                file = getFile(optarg);
                if (file == NULL) {
                    return -1;
                }
                break;
            case 'c':
            case 'i':
            case 'f':
            case 'd':
                if (dataTypeFlag) {
                    fprintf(stderr, "Error: only one data type argument can be used at a time.\n");
                    exit(EXIT_FAILURE);
                }
                dataTypeFlag = 1;

                switch(c) {
                    case 'c':
                        setDataType(TYPE_CHAR);
                        break;
                    case 'i':
                        setDataType(TYPE_INT);
                        break;
                    case 'f':
                        setDataType(TYPE_FLOAT);
                        break;
                    case 'd':
                        setDataType(TYPE_DOUBLE);
                        break;
                }
                break;

            default:
                fprintf(stderr, "Usage: %s --path path -c -i -f -d\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    printf("File Type: %s\n", fileTypeToString());

    if(getDataType() == UNDEFINED){
        printf("Auto-Detecting Data Type...\n");
        AutoDetectDataType(getFileType(), file);
    }

    printf("Selected %s\n", dataTypeToString());

    // Calculation of matrix size
    calculateMatrixSize(getFileType(), file);
    printf("Matrix Size: %d X %d\n", getCols(), getRows());

    void * matrix = createMatrix(getFileType(), getDataType(), file, getCols(), getRows());
    print_matrix(matrix, getCols(), getDataType());

    // Closes the file
    fclose(file);

    // Free memory
    //free(matrix);

    return 0;
}

void print_matrix(void* matrix, int size, DataType dataType) {
    int i, j;
    switch(dataType) {
        case TYPE_INT:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%d ", ((int*)matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        case TYPE_FLOAT:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%f ", ((float*)matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        case TYPE_DOUBLE:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%lf ", ((double*)matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        case TYPE_CHAR:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%c ", ((char*)matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        default:
            printf("Unsupported data type for printing.\n");
            break;
    }
}
