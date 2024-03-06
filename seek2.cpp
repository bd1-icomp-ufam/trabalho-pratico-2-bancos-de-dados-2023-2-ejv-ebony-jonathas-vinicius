#include <cstdlib>
#include <cstdio>
#include <cstring>

int main(int argc, char** argv){
    if (argc != 2)
    {
        fprintf(stderr,"Nº de argumentos inválido, precisa ser 1\n");
        exit(1);
    }

    //tem que ter \0 no final, por isso 301
    char Titulo[301];
    strcpy(Titulo,argv[1]);


    return 0;
}