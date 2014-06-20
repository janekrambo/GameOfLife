#ifndef GOL_H_INCLUDED
#define GOL_H_INCLUDED

int ReadFile(char* inputFile, int &arrayDimension);
int allocArray(bool *** array, int size);
int deallocArray(bool *** array, int size);
int ProcessArray(bool** inArr, bool ** outArr);
int SaveArrayToFile(bool** outputArray);
int initialArray(bool** array);
int ShiftArrays(bool ** inputArr, bool ** outputArr);
int freeMem();

extern bool ** inputArray;
extern bool ** outputArray;
extern int arrayDimension;
extern int currIterNum;

#endif // GOL_H_INCLUDED
