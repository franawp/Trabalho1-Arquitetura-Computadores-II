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

        void writeBack () {

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

    cout << "Digite o nome do arquivo (Exemplo: \"texte.txt\"): ";
    cin >> nomeArquivo;


    ifstream arquivoEntrada (nomeArquivo);

    try {
        if (arquivoEntrada) {

        }
        else {
            
        }
    }
    catch (const char* exepction) {

    }
    return listaInstrucoes;
}



int main () {
    return 0;
}