/* 
 * File:   gol.h
 * Author: Jan Kowalski
 *
 * Created on 5 maja 2014, 19:23
 */

#ifndef GOL_H
#define	GOL_H

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

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GOL_H */

