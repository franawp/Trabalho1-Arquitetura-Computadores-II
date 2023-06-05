#include <bits/stdc++.h>
#include <interpretador.h>
#include <memoria.h>
//#include <instructionFeatch.h>
using namespace std;

struct Exception {
    string mensagens;
    int codigo;
};

Memoria *umaMemoria = new Memoria ();
unsigned contadorPC = 0;



bitset<32> instructionFeatch (unsigned endereco) {
    contadorPC++;
    return umaMemoria->getInstrucao(endereco);
}




void coletarInstrucoesArquivo () {

}

int ehInstrucaoValida (string instrucao) {
    /* Verificar se a instrução de entrada é valida */
    return 0;
}

string corrigirInstrucao () {

}

void coletarInstrucoesTerminal (vector<pair<int,string>> listaInstrucoes) {
    /* O primeiro elemento da tupla pair<int,string> representa
     * o endereço que essa instrução será armazenada na memória,
     * enquanto o segundo é a instrução em si.
     */
    string instrucao;
    int contador = 0;

    cin >> instrucao;

    while (instrucao != "halt") {
        listaInstrucoes.push_back({contador,instrucao});

        cin >> instrucao;
        contador ++;
    }
}

int main () {
    vector<pair<int,string>> listaInstrucoes;


    coletarInstrucoesTerminal(listaInstrucoes);

    for (pair<int,string> umaInstrucao : listaInstrucoes) {
        try {
            int codeValidation = ehInstrucaoValida(umaInstrucao.second);

            if (codeValidation != 0) {
                Exception newException;
                newException.mensagens = "A instrucao " + umaInstrucao.second + " está errada!";
                newException.codigo = codeValidation;

                throw newException;
            }
            else {
                bitset<32> instrucao = interpretarInstrucao(umaInstrucao.second);
            }
        }
        catch (const Exception newException) {
            cout << newException.mensagens << endl;
            cout << "Digite a instrução novamente: ";
            string instrucaoCorrigida;
            cin >> instrucaoCorrigida;

            /* Verificar novamente e interpretar */
        }
        /* Bloco IF */
        bitset<32> instrucao = umaMemoria->getInstrucao(4);
        contadorPC++;
    }

    return 0;
}