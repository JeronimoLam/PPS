#include "FW_Lib_Functions.h"

void print_matrix(void*, int, DataType);
char* dataTypeToString(DataType);

FW_Matrix create_structure(DataType dataType, char * path){
    FW_Matrix FW;
    FILE* file = NULL;

    // Open the file and set file type
    file = getFile(path);
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open the file.\n");
        exit(EXIT_FAILURE);
    }
    FW.fileType = getFileType();
    printf("File Type: %s\n", fileTypeToString());

    // Autodetect of datatype if not specified
    if(dataType == UNDEFINED){
        printf("Auto-Detecting Data Type...\n");
        FW.datatype = AutoDetectDataType(FW.fileType, file);
    }
    else{
        FW.datatype = dataType;
    }

    printf("Selected %s\n", dataTypeToString(FW.datatype));

    // Calculation of matrix size
    calculateMatrixSize(&FW, file);
    FW.norm_size = (FW.cols > FW.rows) ? FW.cols : FW.rows;

    printf("Matrix Size: %d X %d\n", FW.cols, FW.rows);

    void * matrix = createMatrix(FW, file);
    print_matrix(matrix, FW.norm_size, FW.datatype);

    return FW;
}

void compute_FW(FW_Matrix FW){

}
void save_structure(){

}


//AUX Functions
void print_matrix(void* matrix, int size, DataType dataType) {
    int i, j;
    switch (dataType) {
        case TYPE_INT:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%d ", ((int *) matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        case TYPE_FLOAT:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%f ", ((float *) matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        case TYPE_DOUBLE:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%lf ", ((double *) matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        case TYPE_CHAR:
            for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++) {
                    printf("%c ", ((char *) matrix)[i * size + j]);
                }
                printf("\n");
            }
            break;
        default:
            printf("Unsupported data type for printing.\n");
            break;
    }
}

char* dataTypeToString(DataType dt) {
    const char *prefix = "Data Type: ";
    char *result = malloc(30);  // allocate enough memory for the prefix and the datatype string
    switch (dt) {
        case TYPE_INT:
            sprintf(result, "%s%s", prefix, "INT");
            break;
        case TYPE_FLOAT:
            sprintf(result, "%s%s", prefix, "FLOAT");
            break;
        case TYPE_DOUBLE:
            sprintf(result, "%s%s", prefix, "DOUBLE");
            break;
        case TYPE_CHAR:
            sprintf(result, "%s%s", prefix, "CHAR");
            break;
        case UNDEFINED:
        default:
            sprintf(result, "%s%s", prefix, "unknown");
    }
    return result;
}
