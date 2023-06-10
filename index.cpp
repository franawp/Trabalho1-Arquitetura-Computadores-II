#include <bits/stdc++.h>
#include <interpretador.hpp>
#include <processador.hpp>
using namespace std;

vector<string> abrirArquivo () {
    vector<string> listaInstrucoes;
    string nomeArquivo;
    string linhaArquivo;

    cout << "Digite o nome do arquivo (Exemplo: \"texte.txt\"): ";
    cin >> nomeArquivo;

    ifstream arquivoEntrada (nomeArquivo);

    try {
        if (arquivoEntrada) {
            while (getline(arquivoEntrada, linhaArquivo)) {
                /* Verificar se existe um comentário no código forncedido */
                if (find(linhaArquivo.begin(), linhaArquivo.end(), "#") != linhaArquivo.end()) {
                    /* Se o # for o primeiro elemento, a linha toda é descartada */
                    if ('#' == linhaArquivo[0]) {
                        continue; //Não adiciono nada a lista de comentarios
                    }
                    /* Caso contrario, concateno até achar o comentário */
                    else {
                        string auxliar = "";
                        int i=0;
                        while (linhaArquivo[i] != '#') {
                            auxliar+= linhaArquivo[i];
                            i++;
                        }
                        listaInstrucoes.push_back(auxliar);
                        continue; // Já adicionei a lista de instrucoes
                    }
                }
                listaInstrucoes.push_back(linhaArquivo);
            }
        }
        else {
            throw "Arquivo não aberto";
        }
    }
    catch (const char* exepction) {
        /* Corrigir arquivo */
    }
    return listaInstrucoes;
}


int main () {
    Processador *processadorUFLA_RISC;
    return 0;
}