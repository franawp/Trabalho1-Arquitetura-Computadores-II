#include <bits/stdc++.h>
#include <interpretador.h>
#include <memoria.h>
#include <instructionDecoder.h>
//#include <instructionFeatch.h>
using namespace std;

struct Exception {
    string mensagens;
    int codigo;
};



class App {
    private:
        Memoria *memoriaProcessador;
        unsigned contadorPC;

        /* -- 4 Rotinas principais -- */
        bitset<32> instructionFeatch () {
            bitset<32> instrucao = memoriaProcessador->getInstrucao(contadorPC);
            contadorPC++;
            return instrucao;
        }

        int instructionDecoder (bitset<32> instrucao) {
            
        }

        void exec () {

        }

        void writeBack (pair<bitset<8>, bitset<32>> dados) {

        }

    public:
/* -- Construtor e Destrutor -- */
        App () {
            contadorPC = 0;
        }

        ~App () {
            delete[] memoriaProcessador;
        }

        void executar () {
            bitset<32> registradorIFID;
            int registradorIDEX;

            vector<string> listaInstrucoes = abrirArquivo();

            vector<pair<unsigned,bitset<32>>> instrucoesCompiladas = Interpretador::interpretarInstrucoes(listaInstrucoes);
            /* Escrever tudo na memoria */
            memoriaProcessador = new Memoria (instrucoesCompiladas);

            while (true) {
                registradorIFID = instructionFeatch();
                registradorIDEX = instructionDecoder(registradorIFID);
                //registradorEXWB = execMemoria ()
            }
        }
};



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
    return 0;
}