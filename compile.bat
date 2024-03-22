@echo off
REM Create the Compiled directory if it doesn't exist
if not exist Compiled mkdir Compiled

REM Compile File Handler
gcc -c -g FileManager/file_handler.c -o Compiled/file_handler.o

REM For CSV
gcc -c -g FileManager/CSV/CSV_createMatrix.c -o Compiled/CSV_createMatrix.o
gcc -c -g FileManager/CSV/CSV_Helpers.c -o Compiled/CSV_Helpers.o
gcc -c -g FileManager/CSV/CSV_saveMatrix.c -o Compiled/CSV_saveMatrix.o

REM For JSON
gcc -c -g FileManager/JSON/JSON_CreateMatrix.c -o Compiled/JSON_CreateMatrix.o
gcc -c -g FileManager/JSON/JSON_Helpers.c -o Compiled/JSON_Helpers.o
gcc -c -g FileManager/JSON/JSON_saveMatrix.c -o Compiled/JSON_saveMatrix.o

REM For Blocks
gcc -c -g FileManager/Blocks/blocks.c -o Compiled/blocks.o

REM Compile Floyd-Warshall
gcc -c -g Floyd-Warshall/floyd_version_7_8.c -o Compiled/floyd_version_7_8.o
gcc -c -g Floyd-Warshall/FW_Lib_Functions.c -o Compiled/FW_Lib_Functions.o

REM Compile main program
gcc -O0 -g -fopenmp main.c Compiled/file.o Compiled/CSV_createMatrix.o Compiled/CSV_Functions.o Compiled/CSV_saveMatrix.o Compiled/JSON_CreateMatrix.o Compiled/JSON_Functions.o Compiled/JSON_saveMatrix.o Compiled/floyd_version_7_8.o Compiled/FW_Lib_Functions.o -o main_executable

echo Compilation complete!
