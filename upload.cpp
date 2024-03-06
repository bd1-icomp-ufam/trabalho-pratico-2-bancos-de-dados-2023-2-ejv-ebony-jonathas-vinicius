#include "arquivo_hash.hpp"
#include "artigo.hpp"
#include "constantes.hpp"
#include <filesystem>
#include <cstdlib>
#include <cstdio>
#include <cstring>

int main(int argc, char** argv){
    if (argc != 2)
    {
        fprintf(stderr,"Nº de argumentos inválido, precisa ser 1\n");
        exit(1);
    }

    char* nomeArquivo = argv[1];

    FILE* fp = fopen(nomeArquivo, "r");

    namespace fs = std::filesystem;
    if(!fs::is_directory("arquivos") || !fs::exists("arquivos")) {
        fs::create_directory("arquivos");
    }

    FILE* arquivo_dados = fopen(nome_arquivo_dados, "wb");
    ArquivoHash hash(nome_arquivo_hash, numero_buckets, ArquivoHash::Modo::escrita);

    char linha[5000];

    off_t offset = 0;

    while(fgets(linha, 5000, fp) != NULL) {
        bool pegando_proxima = false;
        bool ignora_linha = false;
        while(true){
            if(pegando_proxima) {
                int tam = strlen(linha);
                fgets(linha + tam, 5000 - tam, fp);
            }
            int colunas = 1;
            char ultimo = '\0';
            int aspas = 0;
            for(int i = 0; linha[i]!='\0'; i++) {
                if(linha[i]==';' && (aspas == 0 || (ultimo == '"' && aspas%2==0))) {
                    colunas++;
                    aspas=0;
                }
                if(linha[i]=='"') aspas++;
                ultimo = linha[i];
            }
            if(colunas < 7) {
                pegando_proxima = true;
                printf("linha com menos colunas que o esperado, juntando com a próxima\n");
                continue;
            }
            if(colunas > 7) {
                ignora_linha = true;
                printf("linha com mais colunas do que o esperado, ignorando\n");
            }
            break;
        }
        if(ignora_linha) continue;

        auto atg = csv_para_artigo(linha);

        fwrite(&atg, sizeof(artigo), 1, arquivo_dados);
        hash.insere(atg.id, offset);

        offset += sizeof(artigo);
    }

    printf("Terminou de inserir\n");
    return 0;
}
