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
            cout << "bancoRegistradores: \n";
            for (int i=0; i<32; i++) {
                cout << i << " " << bancoRegistradores[i].to_ulong() << endl;
            }

            delete[]memoriaInstrucoes;
            delete[]bancoRegistradores;
            delete[]memoriaDados;
        }

/* -- Métodos que envolvem operação na memória -- */
        bitset<32> getInstrucao (unsigned endereco) {
            return memoriaInstrucoes[endereco].second;
        }

        void escritaMemoriaDados (bitset<16> dado, unsigned endereco) {
            memoriaDados[endereco].first = true;
            memoriaDados[endereco].second = dado;
        }

        bitset<16> getMemoriaDados (unsigned endereco) {
            if (memoriaDados[endereco].first) {
                return memoriaDados[endereco].second;
            }
            else {
                return 0b0;
            }
        }

/* -- Métodos que envolvem o banco de registradores --*/
        void escritaBancoRegistradores (bitset<32> dado, unsigned numeroRegistrador) {
            bancoRegistradores[numeroRegistrador] = dado;
        }

        bitset<32> getValorRegistrador (unsigned numeroRegistrador) {
            return bancoRegistradores[numeroRegistrador];
        }
};