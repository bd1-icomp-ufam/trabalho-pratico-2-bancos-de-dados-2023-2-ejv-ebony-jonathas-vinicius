#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv){
    if (argc != 2)
    {
        fprintf(stderr,"Nº de argumentos inválido, precisa ser 1\n");
        exit(1);
    }

     int ID = atoi(argv[1]);

    return 0;
}