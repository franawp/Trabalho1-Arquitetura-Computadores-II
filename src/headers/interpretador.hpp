#include <bits/stdc++.h>
using namespace std;

class Interpretador {
    private:
        static map<string,bitset<8>> hashOpcode;

        static vector<string> splitar (string instrucao) {
            /* Variaveis auxiliares */
            vector<string> instrucoesSplitadas;
            string auxiliar;

            /* Separando a instrucao por espacos */
            istringstream splitador(instrucao);

            /* Adicionando as instrucoes splitadas no vetor */
            while (splitador >> auxiliar) {
                /* removendo os R e , das instrucoes */
                for (int i=0; i<auxiliar.size(); i++) {
                    if (auxiliar[i] == 'R' || auxiliar[i] == ',') {
                        auxiliar.erase(next(auxiliar.begin(),i));
                    }
                }
                instrucoesSplitadas.push_back(auxiliar);
            }

            return instrucoesSplitadas;
        }

        static bool ehUmLabel (string operando) {
            return operando == "address";
        }

        static string qTipoInstrucao (vector<string> instrucao) {
            /* nao está pronto */
            return "R";
        }

        static bitset<32> gerarBinario (vector<string> instrucao) {
            string tipoInstrucao;
            bitset<32> binario;

            tipoInstrucao = qTipoInstrucao(instrucao);

            if (tipoInstrucao == "R") {
                bitset<8> opcode(hashOpcode[instrucao[0]]);
                bitset<8> ra(stoi(instrucao[1]));
                bitset<8> rb(stoi(instrucao[2]));
                bitset<8> rc(stoi(instrucao[3]));
                
                for (int i=7; i>=0; i--) {
                    binario[i+24] = opcode[i];
                    binario[i+16] = ra[i];
                    binario[i+8] = rb[i];
                    binario[i] = rc[i];
                }
            }
            else if (tipoInstrucao == "I") {
                bitset<8> opcode(hashOpcode[instrucao[0]]);
                bitset<16> rb(instrucao[2]);
                bitset<8> rc(instrucao[1]);
                
                for (int i=7; i>=0; i--) {
                    binario[i+24] = opcode[i];
                    binario[i] = rc[i];
                }
                for (int i=16; i>=0; i--) {
                    binario[i+8] = rb[i];
                }
            }
            else if (tipoInstrucao == "J") {
                bitset<8> opcode(hashOpcode[instrucao[0]]);
                bitset<24> adress(instrucao[1]);
                
                for (int i=7; i>=0; i--) {
                    binario[i+24] = opcode[i];
                }
                for (int i=24; i>=0; i--) {
                    binario[i] = adress[i];
                }
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

map<string,bitset<8>> Interpretador::hashOpcode = {
    {"add", 0b00000001}, {"sub", 0b00000010},
    {"zeros", 0b00000011}, {"xor", 0b00000100},
    {"or", 0b00000101}, {"passnota", 0b00000110},
    {"and", 0b00000111},{"asl", 0b00001000},
    {"asr", 0b00001001},{"lsl", 0b00001010},
    {"lsr", 0b00001011},{"passa", 0b00001100},
    {"lch", 0b00001110},{"lcl", 0b00001111},
    {"load", 0b00010000},{"store", 0b00010001},
    {"jal", 0b00010010},{"jr", 0b00010011},
    {"beq", 0b00010100},{"bne", 0b00010101},
    {"j", 0b00010110},{"nova1", 0b11},
    {"nova2", 0b11},{"nova3", 0b11},
    {"nova4", 0b11},{"nova5", 0b11},
    {"nova6", 0b11},{"nova7", 0b11},
    {"nova8", 0b11},{"nova9", 0b11},
    {"nova10", 0b11},{"halt", 0b11111111}   
};