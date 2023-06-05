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
            //auto tipoInstrucao = mapeamentoOpcode(instrucao);
        }

        void exec () {

        }

        void writeBack () {

        }

    public:
/* -- Construtor e Destrutor -- */
        App () {
            memoriaProcessador = new Memoria ();
            contadorPC = 0;
        }

        ~App () {
            delete[] memoriaProcessador;
        }

        void executar () {
            bitset<32> registradorIFID;
            int registradorIDEX;

            while (true) {
                registradorIFID = instructionFeatch();
                registradorIDEX = instructionDecoder(registradorIFID);
                //registradorEXWB = execMemoria ()
            }
        }

        void abrirArquivo () {

        }
};







int main () {
    return 0;
}