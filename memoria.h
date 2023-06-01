#include <bits/stdc++.h>
using namespace std;

class Memoria {
    private:
        bitset<32> *memoriaInstrucoes;
        bitset<16> *bancoRegistradores;

    public:
/* -- Construtor e Destrutor -- */
        Memoria () {
            memoriaInstrucoes = new bitset<32>[64*1024];
            bancoRegistradores = new bitset<16>[32];
        }

        ~Memoria () {
            delete[]memoriaInstrucoes;
            delete[]bancoRegistradores;
        }

/* -- Métodos que envolvem operação na memória -- */
        bitset<32> getInstrucao (int contadorPC) {
            return memoriaInstrucoes[contadorPC];
        }

        void escritaMemoria (bitset<32> dado, unsigned posicao) {
            memoriaInstrucoes[posicao] = dado;
        }

/* -- Métodos que envolvem o banco de registradores --*/
        void escritaBancoRegistradores (bitset<16> dado, unsigned numeroRegistrador) {
            bancoRegistradores[numeroRegistrador] = dado;
        }

        bitset<16> getValorRegistrador (unsigned numeroRegistrador) {
            return bancoRegistradores[numeroRegistrador];
        }
};