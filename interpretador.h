#include <bits/stdc++.h>
using namespace std;

class Interpretador {
    private:
        static map<string,bitset<8>> hashOpcode;
        map<string,bitset<8>> hashOpcode = {
            {"add", 0b00},
            {"sub", 0b01},
            {"zeros", 0b10},
            {"xor", 0b11},
            {"or", 0b11},
            {"passnota", 0b11},
            {"and", 0b11},
            {"asl", 0b11},
            {"asr", 0b11},
            {"lsl", 0b11},
            {"lsr", 0b11},
            {"passa", 0b11},
            {"lch", 0b11},
            {"lcl", 0b11},
            {"load", 0b11},
            {"store", 0b11},
            {"jal", 0b11},
            {"jr", 0b11},
            {"beq", 0b11},
            {"bne", 0b11},
            {"j", 0b11},
            {"nova1", 0b11},
            {"nova2", 0b11},
            {"nova3", 0b11},
            {"nova4", 0b11},
            {"nova5", 0b11},
            {"nova6", 0b11},
            {"nova7", 0b11},
            {"nova8", 0b11},
            {"nova9", 0b11},
            {"nova10", 0b11},
            {"nova11", 0b11}
        };

        static vector<string> splitar (string instrucao) {
            /* Variaveis auxiliares */
            vector<string> instrucoesSplitadas;
            string auxiliar;

            /* Separando a instrucao por espacos */
            istringstream splitador(instrucao);

            /* Adicionando as instrucoes splitadas no vetor */
            while (splitador >> auxiliar) {
                instrucoesSplitadas.push_back(auxiliar);
            }

            return instrucoesSplitadas;
        }

        static bool ehUmLabel (string operando) {
            return operando == "adress";
        }

        static string qTipoInstrucao (vector<string> instrucao) {
            /* nao está pronto */
            return "j";
        }

        static bitset<32> gerarBinario (vector<string> instrucao) {
            string tipoInstrucao;
            bitset<32> binario;

            tipoInstrucao = qTipoInstrucao(instrucao);

            if (tipoInstrucao == "R") {
                bitset<8> opcode = hashOpcode[instrucao[0]];
                bitset<8> ra = stoi(instrucao[1]);
                bitset<8> rb = stoi (instrucao[2]);
                bitset<8> rc = stoi (instrucao[3]);
            }
            else if (tipoInstrucao == "I") {
                bitset<8> opcode = hashOpcode[instrucao[0]];
                bitset<16> rb;
                bitset<8> rc;
            }
            else if (tipoInstrucao == "J") {
                bitset<8> opcode = hashOpcode[instrucao[0]];
                bitset<24> adress;
            }
        
            return binario;
        }
    

    public:
/* A função do interpretador é converter a instrucoes que foram lidas do arquivo 
* em sua representação em binário de 32 bits bitset<32> e retornar uma tupla contendo
* o endereço que ela será salva na memoria e o seu valor.
*/
        static vector<pair<unsigned,bitset<32>>> interpretarInstrucoes (vector<string> listaInstrucoes) {
            /* Inicializando variáveis */
            unsigned enderecoAtual = 0;
            vector<pair<unsigned,bitset<32>>> instrucoesCompiladas;
            vector<vector<string>> instrucoesSplitadas;

            for (string umaInstrucao : listaInstrucoes) {
                instrucoesSplitadas.push_back(splitar(umaInstrucao));
            }

            for (vector<string> umaInstrucao : instrucoesSplitadas) {
                /* Se a instrucao for um label, irá alterar a posição da memória */
                if (ehUmLabel(umaInstrucao[0])) {
                    enderecoAtual = stoi(umaInstrucao[1]);
                }

                instrucoesCompiladas.push_back({
                    enderecoAtual,gerarBinario(umaInstrucao)
                });
                enderecoAtual++;
            }

            return instrucoesCompiladas;
        }

};
/*
adress 0
*/