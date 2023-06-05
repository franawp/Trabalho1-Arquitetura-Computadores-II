#include <bits/stdc++.h>
using namespace std;

class Memoria {
    private:
        pair<bool,bitset<32>> *memoriaInstrucoes;
        pair<bool,bitset<32>> *memoriaDados;
        bitset<16> *bancoRegistradores;

    public:
/* -- Construtor e Destrutor -- */
        Memoria () {
            memoriaInstrucoes = new pair<bool,bitset<32>>[64*1024];
            memoriaDados = new pair<bool,bitset<32>>[64*1024];
            bancoRegistradores = new bitset<16>[32];
        }

        ~Memoria () {
            delete[]memoriaInstrucoes;
            delete[]bancoRegistradores;
            delete[]memoriaDados;
        }

/* -- Métodos que envolvem operação na memória -- */
        bitset<32> getInstrucao (int endereco) {
            return memoriaInstrucoes[endereco].second;
        }

        void escritaMemoriaDados (bitset<32> dado, unsigned posicao) {
            memoriaDados[posicao].first = true;
            memoriaDados[posicao].second = dado;
        }

/* -- Métodos que envolvem o banco de registradores --*/
        void escritaBancoRegistradores (bitset<16> dado, unsigned numeroRegistrador) {
            bancoRegistradores[numeroRegistrador] = dado;
        }

        bitset<16> getValorRegistrador (unsigned numeroRegistrador) {
            return bancoRegistradores[numeroRegistrador];
        }
};