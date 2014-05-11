#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gol.h"


char bmpfileheader[15];
char * bmpDIBHeader;
long DIB_head_size;
int remain;			//liczba pustych bitów w wierszu pliku bmp

int allocArray(bool *** array, int size){
	*array = (bool**) malloc((size+2)*sizeof(bool *));
	for (int i = 0; i < (size+2); i++){
		(*array)[i] = (bool*)malloc((size+2)* sizeof(bool));
	}


	return 0;

}

int initialArray(bool **array){
	for (int i = 0; i < arrayDimension + 2; i++){
		for (int j = 0; j < arrayDimension + 2; j++){
		array[i][j] = 0;
		}
	}
	return 0;
}
int deallocArray(bool *** array, int size){

	for (int i = 0; i < (size+2); i++){
		free((*array)[i]);
	}
	free(*array);
	return 0;
}

/*Wczytanie  pliku, sprawdzenie poprawnośći, alokacja tablicy wejsciowej*/

int ReadFile(char* inputFile, int &arrayDimension){

	
	FILE *fptr;
	if ((fptr=fopen(inputFile, "r")) == NULL){
		printf("Nie udało się otworzyć pliku wehscuiwego %s\n", inputFile);
		return(1);
	}

	//wczytanie headera
	fread(bmpfileheader,1,14,fptr);
	bmpfileheader[14] = '\0';
	fread(&DIB_head_size, 1, 4, fptr);
	printf("headSize: %d\n", DIB_head_size);
	fseek(fptr, -4, SEEK_CUR);
	bmpDIBHeader = (char *) malloc((DIB_head_size+1) * sizeof(char));
	fread(bmpDIBHeader, 1, DIB_head_size, fptr);
	bmpDIBHeader[DIB_head_size] = '\0';
	printf("dib header : %s |koniec\n", bmpDIBHeader);

	int ret_code;
	fseek(fptr, 10, SEEK_SET);
	long int offset; //początkowy adres bitow w tabeli pikseli
	ret_code = fread(&offset, 4, 1, fptr);

	/*Sprawdzanie wymiarów pliku wejściowego*/
	long int biWidth;
	ret_code = fseek(fptr, 18 , SEEK_SET);
	ret_code = fread(&biWidth, 1, 4, fptr);
	long int biHeight;
	ret_code = fread(&biHeight, 1, 4, fptr);
        
        int planes;
        fread(&planes,1,2,fptr);
        printf("planes = %d\n",planes);
        int bitsPerPixel;
        fread(&bitsPerPixel,1,2,fptr);
        printf("Bits per Pixel= %d\n", bitsPerPixel);
        long int compression;
        fread(&compression,1,4,fptr);
        printf("Compression = %d\n",compression);
        long int imageSize;
        fread(&imageSize,1,4,fptr);
        printf("Image Size= %d\n", imageSize);
	
        
        
        if (biHeight != biWidth){
		printf("UWAGA!: Plik wejściowy powinien mieć wymiar nxn");
		return 111;
	}
  
	else{
		arrayDimension = biHeight;
		allocArray(&inputArray, arrayDimension);
		initialArray(inputArray);
		/*W plikach bmp wielkość wiersza jest zawsze zaokrąglana do 4
		bajtow więc obliczam ile zer zostanie dopisancyh na koncu
		każdego wiersza*/
		if ((remain=((arrayDimension*3)% 4 ))!= 0){ remain = 4 - remain; }
		else{ remain = 0; }

		printf("Reszta z dzielenia przez 4 = %d\n", remain);
		
		/*Ustawiam wskaźnik pliku na początek mapy bitowej*/
		printf("biHeight: %d\n", biHeight);
		fseek(fptr, offset, SEEK_SET);
		/*Przeglądanie mapy bitowej*/
		int i,j;
		/*pliki bmp sa zapisywane do góry nogami ale to nie  przeszkadza
		bo i tak trzeba je zapisać do góry nogami. Można je przetworzyć 
		do góry nogami*/

		for (i = 1; i <= arrayDimension; i++){
			for (j = 1; j <=arrayDimension; j++){
				int tmp = (int)fgetc(fptr);
				tmp += (int)fgetc(fptr);
				tmp += (int)fgetc(fptr);
				if (tmp!=765){ //jeżeli punkt nie jest całkowicie biały to jest czarny
					inputArray[i][j] = true;
					//printf(" 1 ");
				}
				else{
					inputArray[i][j] = false;
					//printf(" 0 ");
				}
			}
			if (remain != 0){
                            
				fseek(fptr, remain , SEEK_CUR);
			}
			//printf("\n\n");
		}
                char ca;
                while((ca=fgetc(fptr))!=EOF){
                    
                    printf("1%c", &ca);
                }
		fclose(fptr);
		return 0;
	}
        
 
}

/* Przetwarzanie tablicy - główny algorytm*/

int ProcessArray(bool** inArr, bool ** outArr){
	int tmp = 0;
	for (int i = 1; i < (arrayDimension+1);i++){
		
		for (int j = 1; j < (arrayDimension + 1); j++){
			tmp = 0;
			tmp += (int)inArr[i + 1][j - 1];
			tmp += (int)inArr[i][j - 1];
			tmp += (int)inArr[i - 1][j - 1];
			tmp += (int)inArr[i - 1][j];
			tmp += (int)inArr[i - 1][j + 1];
			tmp += (int)inArr[i][j + 1];
			tmp += (int)inArr[i + 1][j + 1];
			tmp += (int)inArr[i + 1][j];
			
			if (inArr[i][j] == 0){ 
				switch (tmp) {
				case 3 :
					outArr[i][j] = 1;
					break;
				default :
					outArr[i][j] = 0;
				}
			}
			else {
	
				if (tmp < 2){
					outArr[i][j] = 0;
				}
				else{
					if (tmp < 4){
						outArr[i][j] = 1;
					}
					else{
						outArr[i][j] = 0;
					}
				}
			}
		}

	}

	return 0;
}


int SaveArrayToFile(bool **someArr){

	FILE *fptr;
	char str[15];
	sprintf(str, "out%d.bmp", currIterNum);
	if ((fptr = fopen(str, "w")) == NULL){
		printf("Nie udało się otworzyć pliku sample_input.bmp\n");
		return(1);
	}
	fwrite(bmpfileheader, 1, 14, fptr);
	fwrite(bmpDIBHeader, 1, DIB_head_size, fptr);
	int black = 0;
	int white = 255;
        int i,j;
	for (i = 1; i <arrayDimension+1; i++){
		for (j = 1; j <arrayDimension+1; j++){
			if (someArr[i][j] == false){
				fwrite(&white, 1, 1, fptr);
				fwrite(&white, 1, 1, fptr);
				fwrite(&white, 1, 1, fptr);
			}
			else{
				fwrite(&black, 1, 1,fptr);
				fwrite(&black, 1, 1, fptr);
				fwrite(&black, 1, 1, fptr);
			}
		}
		for (j = 0; j < remain; j++){
			fwrite(&black, 1, 1, fptr);
		}

	}

	fclose(fptr);
	return 0;
}


int ShiftArrays(bool ** inputArr, bool ** outputArr){
	bool ** tempArray = inputArr;
	inputArr = outputArr;
	outputArr = tempArray;
	return 0;
}

int freeMem(){
	free(bmpDIBHeader);
	return 0;
}