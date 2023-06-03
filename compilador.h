#include <bits/stdc++.h>
using namespace std;

typedef pair<unsigned,bitset<32>> tupla_endereco_instrucao;

vector<string> instrucoes_validas = {
    "add", "sub", "zeros", "xor",
    "or", "passnota", "and", "asl",
    "asr", "lsl", "lsr", "passa",
    "lch", "lcl", "load", "store",
    "jal", "jr", "beq", "bne", "j"
};

vector<string> warning;
vector<string> errors;

tupla_endereco_instrucao* compliar_instrucao (vector<string> instrucoes, unsigned quantidadeInstrucoes) {
    tupla_endereco_instrucao* instrucoes_compiladas = new tupla_endereco_instrucao[quantidadeInstrucoes];
    unsigned acumulador_posicao_memoria;
    vector<string> instrucoes_splitadas;

    for (const string &instrucao : instrucoes) {
        istringstream splitar_instrucao(instrucao);

        string string_auxiliar;
        while (splitar_instrucao >> string_auxiliar) {
            instrucoes_splitadas.push_back(string_auxiliar);
        }

        if (find(instrucoes_validas.begin(), instrucoes_validas.end(), 
            instrucoes_splitadas[0]) != instrucoes_validas.end()) {
            
        }
        else {
            throw "Instrucao não encontrada";
        }
    }



    return instrucoes_compiladas;
}