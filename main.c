#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdbool.h>

struct student {
    char name[75];
    char surname[75];
    int number;
    int primeFactor;
    char nameAndSurname[200];
} student;

int tempPrimeFactor, *tempPrimeFactorPointer, charactersLenght, offset = 3;
bool error = false;

char File_encryptedText[200];
char File_decryptedText[200];
char tempEncryptedText[200];
char characters[26] =  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


void readInfo (){
    
    printf("\nOnly enter your name  :  ");
    scanf("%s", student.name);
    printf("\nOnly enter your surname  :  ");
    scanf("%s",student.surname);
    printf("\nEnter your student number :  ");
    scanf("%d", &student.number);
    printf("\nEnter the largest prime factor of your student number  :  ");
    scanf("%d", &tempPrimeFactor);
}




void mergeText (){
    
    strcat(student.nameAndSurname,student.name);
    strcat(student.nameAndSurname,"_");
    strcat(student.nameAndSurname,student.surname);
}

void toLower (){
    
    for (int i = 0; i < strlen(student.nameAndSurname); ++i) {
        student.nameAndSurname[i] = tolower(student.nameAndSurname[i]);
    }
}

void checkText (){

    int nameAndSurnameLenght = strlen(student.nameAndSurname) ;
    int charactersLenght = strlen(characters);
    bool isHave;
    
    for(int currentCharacter=0; currentCharacter<nameAndSurnameLenght ; currentCharacter++){
        isHave = false;
        for(int alphabetCharacter=0; alphabetCharacter<charactersLenght; alphabetCharacter++){
            if(student.nameAndSurname[currentCharacter]==characters[alphabetCharacter] || student.nameAndSurname[currentCharacter]=='_'){
                isHave = true;
    			break;
    	    }
	    }
	   if(isHave == false){
                error = true;
                break;
        }
    }
}


void encrypt (){
    
 
    int nameAndSurnameLenght = strlen(student.nameAndSurname) ;
    int charactersLenght =  strlen(characters);
    
    for(int currentCharacter=0; currentCharacter<nameAndSurnameLenght ; currentCharacter++){
        for(int alphabetCharacter=0; alphabetCharacter<charactersLenght; alphabetCharacter++){
            if(student.nameAndSurname[currentCharacter]==characters[alphabetCharacter]){
                alphabetCharacter += offset;
    			alphabetCharacter %= charactersLenght;
    			tempEncryptedText[currentCharacter]=characters[alphabetCharacter]; 
    			break;
    	    }
    	    else if (student.nameAndSurname[currentCharacter]=='_'){
            	tempEncryptedText[currentCharacter]='_'; 
                break;
    	    }
	    }
    }
}


void fileWrite (){
    
    FILE *WFile = fopen("encrypted-text.txt", "w+");
    fprintf(WFile,"%s\t",tempEncryptedText);
    fclose(WFile);
}

void findPrimeFactor (){
    
     int number = student.number;
     for(int i = 2; number > 1; i++){
        while(number % i == 0){
            student.primeFactor = i;
            number = number / i;
        }
     }
}

void fileRead (){
 
    FILE *RFile = fopen("encrypted-text.txt", "r+");
    fscanf(RFile, "%s", File_encryptedText);
    fclose(RFile);
}

void decrypt (){

    int charactersLenght = strlen(characters);
    int File_encryptedTextLenght = strlen(File_encryptedText);

    for(int currentCharacter=0; currentCharacter<File_encryptedTextLenght ; currentCharacter++){
        for(int alphabetCharacter=0; alphabetCharacter<charactersLenght; alphabetCharacter++){
            if(File_encryptedText[currentCharacter]==characters[alphabetCharacter]){
                for(int i=0; i<offset; i++){
                    if(alphabetCharacter==0){
                        alphabetCharacter=charactersLenght;
                    }
                    alphabetCharacter -= 1;
                }
    			alphabetCharacter %= charactersLenght;
    			File_decryptedText[currentCharacter]=characters[alphabetCharacter]; 
    			break;
    	    }
    	    else if (File_encryptedText[currentCharacter]=='_'){
    	        
    	        File_decryptedText[currentCharacter]='_'; 
    	        break;
    	        
    	    }
	    }
    }
}


int main(){
    tempPrimeFactorPointer=&tempPrimeFactor;
    readInfo();
    mergeText();
    toLower();
    checkText();
    
    if(error == true){
          printf("\n\n\n\t You entered the wrong name or surname. \n\n");
          return 0;
    }
    
    encrypt();
    fileWrite();
    findPrimeFactor();
    
    if(student.primeFactor == *tempPrimeFactorPointer && student.primeFactor != '\0'){
        fileRead();
        decrypt();
        printf("\n\tEncrypted Text : %s",File_encryptedText);
        printf("\n\tDecrypted Text : %s",File_decryptedText);
        printf("\n\tStudent Number : %d",student.number);
        printf("\n\tLargest prime factor : %d",student.primeFactor);
        printf("\n\tLargest prime factor (Pointer) : %d",*tempPrimeFactorPointer);
        return 0;
    }
    else{
        printf("\n\n\n\t You entered an incorrect password\n\n");
        return 0;
    }
}

