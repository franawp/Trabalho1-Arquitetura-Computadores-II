#include <bits/stdc++.h>
using namespace std;

class Memoria {
    private:
        pair<bool,bitset<32>> *memoriaInstrucoes;
        pair<bool,bitset<16>> *memoriaDados;
        bitset<32> *bancoRegistradores;

    public:
/* -- Construtor e Destrutor -- */
        Memoria (vector<pair<unsigned,bitset<32>>> listaInstrucoes) {
            memoriaInstrucoes = new pair<bool,bitset<32>>[64*1024];
            
            for (pair<unsigned,bitset<32>> instrucao : listaInstrucoes) {
                memoriaInstrucoes[instrucao.first] = {true,instrucao.second};
            }

            memoriaDados = new pair<bool,bitset<16>>[64*1024];
            bancoRegistradores = new bitset<32>[32];
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

        void escritaMemoriaDados (bitset<16> dado, unsigned posicao) {
            memoriaDados[posicao].first = true;
            memoriaDados[posicao].second = dado;
        }

/* -- Métodos que envolvem o banco de registradores --*/
        void escritaBancoRegistradores (bitset<32> dado, unsigned numeroRegistrador) {
            bancoRegistradores[numeroRegistrador] = dado;
        }

        bitset<32> getValorRegistrador (unsigned numeroRegistrador) {
            return bancoRegistradores[numeroRegistrador];
        }
};