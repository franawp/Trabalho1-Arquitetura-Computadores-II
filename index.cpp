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

struct Flags {
    bitset<8>* opcode;
    bitset<8>* registradorA;
    bitset<8>* registradorB;
    bitset<8>* registradorC;
    bool overflow;
    bool neg;
    bool zero;
    bool carry;
    bool memRead;
    bool memWrite;
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

        vector<string> abrirArquivo () {
            vector<string> teste;
            return teste;
        }
};







int main () {
    return 0;
}