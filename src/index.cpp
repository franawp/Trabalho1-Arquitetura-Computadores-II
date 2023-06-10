#include <bits/stdc++.h>
#include <stdexcept>
#include "headers/interpretador.hpp"
#include "headers/processador.hpp"

using namespace std;

vector<string> abrirArquivo () {
    vector<string> listaInstrucoes;
    string nomeArquivo;
    string linhaArquivo;

    cout << "Digite o nome do arquivo (Exemplo: \"texte.txt\"): ";
    cin >> nomeArquivo;

    ifstream arquivoEntrada ("arquivos/" + nomeArquivo);

    try {
        if (arquivoEntrada) {
            while (getline(arquivoEntrada, linhaArquivo)) {
                /* Verificar se existe um comentário no código forncedido */
                if (find(linhaArquivo.begin(), linhaArquivo.end(), '#') != linhaArquivo.end()) {
                    /* Se o # for o primeiro elemento, a linha toda é descartada */
                    if ('#' == linhaArquivo[0]) {
                        continue; //Não adiciono nada a lista de instrucoes
                    }

                    /* Caso contrario, concateno até achar o comentário */
                    else {
                        string auxiliar = "";
                        int i=0;
                        while (linhaArquivo[i] != '#') {
                            auxiliar+= linhaArquivo[i];
                            i++;
                        }

                        /* Remover espaços e \n após o ultimo número */
                        int j = auxiliar.size() - 1;
                        while (j >= 0 && (auxiliar[j] == ' ' || auxiliar[j] == '\n')) {
                            auxiliar.pop_back();
                            j--;
                        }

                        listaInstrucoes.push_back(auxiliar);
                        continue; // Já adicionei a lista de instrucoes
                    }
                }

                else if (linhaArquivo.size() == 0) {
                    continue;
                }

                int j = linhaArquivo.size() - 1;
                while (j >= 0 && (linhaArquivo[j] == ' ' || linhaArquivo[j] == '\n')) {
                    linhaArquivo.pop_back();
                    j--;
                }
                listaInstrucoes.push_back(linhaArquivo);
            }
        }
        else {
            throw runtime_error("arquivo nao aberto");
        }
    }
    catch (const exception &ex) {
        cout << ex.what() << endl;
        cout << "verifique se o arquivo está no diretório src/arquivos e tente novamente!" << endl;
        cout << "[s] Executar novamente\n" << "[n] Abortar execução\n";
        char opcao;
        cin >> opcao;

        if (opcao == 's' || opcao == 'S') {
            return abrirArquivo();
        }
        else {
            cout << "Finalizando" << endl;
        }
    }
    return listaInstrucoes;
}


int main () {
    vector<string> listaInstrucoes = abrirArquivo();
    vector<pair<unsigned,bitset<32>>> instrucoes = Interpretador::interpretarInstrucoes(listaInstrucoes);
    
    /*
    for (auto i : instrucoes) {
        cout << i.first << " " << i.second << endl;
    }
    */
    Processador *processadorUFLA_RISC;
    processadorUFLA_RISC = new Processador(instrucoes);

    processadorUFLA_RISC->executarInstrucoes();
    
    return 0;
}