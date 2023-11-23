#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void seedGenerator();
void trimString(char *str);
bool openCreateFile(char* fileName, FILE* fl);
void genPwd(FILE* fl, char* fileName, const char* numbers, const char* letter, const char* LETTER, const char* symbols);
void assignChar(char* pwd, int pos, const char* src, int n);

int main(int argc, char const *argv[])
{   
    #pragma region  
        const char numbers[] = "0123456789"; 
        const char letter[] = "abcdefghijklmnoqprstuvwyzx"; 
        const char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
        const char symbols[] = "!@#$^&*?"; 
    #pragma endregion
    
    int nPassword;

    char fileName[50];

    FILE* fl = NULL;

    printf("Quante password vuoi generare? ");
    scanf("%d", &nPassword);
    
    printf("Nome del file: ");
    scanf("%50s", fileName);
    
    for (size_t i = 0; i < nPassword; i++)
    {
        genPwd(fl, fileName, numbers, letter, LETTER, symbols);
    }
    
    return 0;
}

void seedGenerator(){
    srand(time(NULL));
}

void trimString(char *str){
    int i = 0, index = -1;

    while (str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }
    str[index+1] = '\0';
}

void assignChar(char* pwd, int pos, const char* src, int n){
    pwd[pos] = src[rand()%n];
}

void genPwd(FILE* fl, char* fileName, const char* numbers, const char* letter, const char* LETTER, const char* symbols){

    char serviceName [50];
    int length;
    int randomizer;
    
    printf("\nNome del servizio: ");
    scanf("%50s", serviceName);

    do{
        printf("Lunghezza password: ");
        scanf("%d", &length);
        fflush(stdin);
    } while (length <=0);

    char password [length];
    seedGenerator();

    for (size_t i = 0; i < length; i++)
    {   
        randomizer = rand() %4+1;
        switch (randomizer)
        {
        case 1:
            assignChar(password, i, numbers, 10);
            break;
        
        case 2:
            assignChar(password, i, letter, 26);
            break;

        case 3:
            assignChar(password, i, LETTER, 26);
            break;

        case 4:
            assignChar(password, i, symbols, 8);
            break;
        }
    }
    fl = fopen(fileName, "a");
    fprintf(fl, "%s\n%s\n----------------------------------\n\n" ,serviceName,password);
    fclose(fl);
}
