#include <bits/stdc++.h>
#include "memoria.hpp"
using namespace std;

struct Flags {
    bool overflow;
    bool neg;
    bool zero;
    bool carry;
    bool memRead;
    bool memWrite;
    bool regWrite;
};

struct Sextupla {
    bitset<8> opcode;

    bitset<8> numeroRegistradorA;
    bitset<8> numeroRegistradorB;
    bitset<8> numeroRegistradorC;

    bitset<16> constante;
    bitset<24> endereco;
};

class Processador {
    private:
/* Atributos */
        Memoria *memoriaProcessador;
        unsigned contadorPC;

/* -- 4 Rotinas principais -- */
        /* PRONTO */
        bitset<32> instructionFeatch () {
            bitset<32> instrucao = memoriaProcessador->getInstrucao(contadorPC);
            contadorPC++;
            return instrucao;
        }

        /* PRONTO */
        Sextupla instructionDecoder (bitset<32>instrucao) {
            /* Variáveis */
            Sextupla registradores;
            string tipo;

            tipo = formatoInstrucao (registradores.opcode.to_ulong());

            if (tipo == "R") {
                for (int i=7; i>=0; i--) {
                    registradores.opcode[i] = instrucao[i + 24];
                    registradores.numeroRegistradorA[i] = instrucao[i + 16];
                    registradores.numeroRegistradorB[i] = instrucao[i + 8];
                    registradores.numeroRegistradorC[i] = instrucao[i];
                }    
            }

            else if (tipo == "I") {
                for (int i=7; i>=0; i--) {
                    registradores.opcode[i] = instrucao[i + 24];
                    registradores.numeroRegistradorC[i] = instrucao[i];
                }
                for (int i=16; i>=0; i--) {
                    registradores.constante[i] = instrucao[i + 8];
                }
            }

            else if (tipo == "J") {
                for (int i=7; i>=0; i--) {
                    registradores.opcode[i] = instrucao[i + 24];
                }
                for (int i=24; i>=0; i--) {
                    registradores.endereco[i] = instrucao[i];
                }
            }
            
            return registradores;
        }

        /* METADE PRONTO */
        pair<bitset<8>, bitset<32>> execMemoria (Sextupla registradorIDEX) {
            pair<bitset<8>,bitset<32>> resultado;

            pair<string,string> tipo = tipoInstrucao(registradorIDEX.opcode.to_ulong());

            if (tipo.second == "aritmetica") {
                return operacaoAritmetica (registradorIDEX, tipo.first);
            }

            else if (tipo.second == "logica") {
                return operacaoLogica (registradorIDEX, tipo.first);
            }

            else if (tipo.second == "shift") {
                return operacaoShift (registradorIDEX, tipo.first);
            }

            else if (tipo.second == "branch") {
                return operacaoBranch (registradorIDEX, tipo.first);
            }

            else if (tipo.second == "memoria") {
                return operacaoMemoria (registradorIDEX, tipo.first);
            }

            else if (tipo.second == "address") {
                return {0b0, 0b0};
            }

            else if (tipo.second == "abortar") {
                return {0b11111111,0b11111111111111111111111111111111};
            }

            return {0b0,0b0};
        }

        /* PRONTO */
        void writeBack (pair<bitset<8>, bitset<32>> dados) {
            memoriaProcessador->escritaBancoRegistradores(dados.second,dados.first.to_ulong());
        }

/* -- Métodos auxiliares -- */
        pair<bitset<8>,bitset<32>> operacaoMemoria (Sextupla registradorIDEX, string tipo) {
            if (tipo == "load") { 
                bitset<32> endereco = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> dado (memoriaProcessador->getMemoriaDados(endereco.to_ulong()).to_ulong());
                
                return {registradorIDEX.numeroRegistradorC, dado};
            }

            else if (tipo == "store") {
                bitset<16> dado (memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorC.to_ulong()).to_ulong());
                
                memoriaProcessador->escritaMemoriaDados(dado,registradorIDEX.numeroRegistradorA.to_ulong());

                return {0b0, 0b0};
            }

            return {0b0, 0b0};
        }

        pair<bitset<8>,bitset<32>> operacaoAritmetica (Sextupla registradorIDEX, string tipo) {
            if (tipo == "add") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                pair<bool,bitset<32>> soma = somaBinaria(valorDeA,valorDeB);
                
                if (soma.first) {
                    /* flag de overflow */
                }
                else {
                    return {registradorIDEX.numeroRegistradorC,soma.second};
                }
            }

            else if (tipo == "sub") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                pair<bool,bitset<32>> sub = subtracaoBinaria(valorDeA,valorDeB);
                
                if (sub.first) {
                    /* flag de overflow */
                }
                else {
                    return {registradorIDEX.numeroRegistradorC,sub.second};
                }
            }

            else if (tipo == "zeros") {
                return {registradorIDEX.numeroRegistradorC,0b0};
            }

            else if (tipo == "passa") {
                bitset<32> conteudoRegistradorA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                return {registradorIDEX.numeroRegistradorC,conteudoRegistradorA};
            }
        }

        pair<bitset<8>,bitset<32>> operacaoLogica (Sextupla registradorIDEX, string tipo) {
            if (tipo == "xor") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC,(valorDeA ^ valorDeB)};
            }

            else if (tipo == "or") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC,(valorDeA | valorDeB)};
            }

            else if (tipo == "passnota") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());

                return {registradorIDEX.numeroRegistradorC, ~valorDeA};
            }

            else if (tipo == "and") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC,(valorDeA & valorDeB)};
            }

            else if (tipo == "nand") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC,~(valorDeA & valorDeB)};
            }

            else if (tipo == "xnor") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC, ~(valorDeA ^ valorDeB)};
            }

            else if (tipo == "nor") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC,~(valorDeA | valorDeB)};
            }
        }

        pair<bitset<8>,bitset<32>> operacaoBranch (Sextupla registradorIDEX, string tipo) {
            if (tipo == "jal") {
                bitset<32> contadorPCAtual (contadorPC + 1);
                bitset<8> registrador31 (31);

                return {registrador31,contadorPCAtual};

                atualizarContadorPc(registradorIDEX.endereco.to_ulong());
            }

            else if (tipo == "jr") {
                bitset<32> conteudoRc = memoriaProcessador->getValorRegistrador(31);
                atualizarContadorPc(conteudoRc.to_ulong());

                return {0b0, 0b0};
            }

            else if (tipo == "beq") {
                bitset<32> zero(0b0);
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorDeC = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorC.to_ulong());

                if (subtracaoBinaria(valorDeA, valorDeB).second == zero) {
                    atualizarContadorPc (valorDeC.to_ulong());
                }

                return {0b0,0b0};
            }

            else if (tipo == "bne") {
                bitset<32> zero(0b0);
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorDeC = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorC.to_ulong());

                if (subtracaoBinaria(valorDeA, valorDeB).second != zero) {
                    atualizarContadorPc (valorDeC.to_ulong());
                }

                return {0b0,0b0};
            }

            else if (tipo == "j") {
                atualizarContadorPc(registradorIDEX.endereco.to_ulong());

                return {0b0, 0b0};
            }

            else if (tipo == "bgt") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorDeC = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorC.to_ulong()); //endereço

                bool ehMaior; //Caso queira saber se é maior ou não, ou tratar essa informação

                for (int i = valorDeA.size()-1; i >= 0; i--) {
                    if (valorDeA[i] < valorDeB[i]) {
                        ehMaior = true;
                        atualizarContadorPc(valorDeC.to_ulong());
                        break;
                    } else if (valorDeA[i] > valorDeB[i]) {
                        ehMaior = false;
                        break;
                    }
                }
                
                return {0b0, 0b0};
            }

            else if (tipo == "blt") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> valorDeB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorDeC = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorC.to_ulong()); //endereço

                bool ehMaior; //Caso queira saber se é maior ou não, ou tratar essa informação

                for (int i = valorDeA.size()-1; i >= 0; i--) {
                    if (valorDeA[i] > valorDeB[i]) {
                        ehMaior = false;
                        atualizarContadorPc(valorDeC.to_ulong());
                        break;
                    } else if (valorDeA[i] < valorDeB[i]) {
                        ehMaior = true;
                        break;
                    }
                }
                
                return {0b0, 0b0};
            }
        }

        pair<bitset<8>,bitset<32>> operacaoShift (Sextupla registradorIDEX, string tipo) {
            if (tipo == "asl") { 
                bitset<32> valorB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                
                return {registradorIDEX.numeroRegistradorC, valorA << valorB.to_ulong()};
            }

            else if (tipo == "asr") {
                bitset<32> valorB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bool ultimoBit = valorA[31];

                bitset<32> novoValor (valorA >> valorB.to_ullong());

                for (int i=31, j=0; j<valorB.to_ulong(); j++, i--) {
                    novoValor[i] = ultimoBit;
                }

                return {registradorIDEX.numeroRegistradorC , novoValor};
            }

            else if (tipo == "lsl") {
                bitset<32> valorB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());

                return {registradorIDEX.numeroRegistradorC, valorA << valorB.to_ulong()};
            }

            else if (tipo == "lsr") {
                bitset<32> valorB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());

                return {registradorIDEX.numeroRegistradorC, valorA >> valorB.to_ulong()};
            }
        }

        pair<bitset<8>,bitset<32>> operacaoConstante (Sextupla registradorIDEX, string tipo) {
            if (tipo == "lch") {
                bitset<32> valor;

                for (int i=15; i>=0; i++) {
                    valor[i] = registradorIDEX.constante[i];
                }

                return {registradorIDEX.numeroRegistradorC, valor};
            }

            else if (tipo == "lcl") {
                bitset<32> valor;

                for (int i=0; i<16; i++) {
                    valor[i] = registradorIDEX.constante[i];
                }

                return {registradorIDEX.numeroRegistradorC, valor};
            }

            else if (tipo == "addi") {
                bitset<32> valorB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                
                return {registradorIDEX.numeroRegistradorC, somaBinaria(valorA,valorB).second};
            }

            else if (tipo == "subi") {
                bitset<32> valorB = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());
                bitset<32> valorA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                
                return {registradorIDEX.numeroRegistradorC, subtracaoBinaria(valorA,valorB).second};
            }

            else if (tipo == "andi") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> constante = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC,(valorDeA & constante)};
            }

            else if (tipo == "ori") {
                bitset<32> valorDeA = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorA.to_ulong());
                bitset<32> constante = memoriaProcessador->getValorRegistrador(registradorIDEX.numeroRegistradorB.to_ulong());

                return {registradorIDEX.numeroRegistradorC,(valorDeA | constante)};
            }
        }

        pair<string,string> tipoInstrucao (uint8_t opcode) {
            map <uint8_t,pair<string,string>> hashInstrucao = {
                {0b00000000,{"address","label"}},
                {0b00000001,{"add","aritmetica"}},
                {0b00000010,{"sub","aritmetica"}},
                {0b00000011,{"zeros","aritmetica"}},
                {0b00000100,{"xor","logica"}},
                {0b00000101,{"or","logica"}},
                {0b00000110,{"passnota","logica"}},
                {0b00000111,{"and","logica"}},
                {0b00001000,{"asl","shift"}},
                {0b00001001,{"asr","shift"}},
                {0b00001010,{"lsl","shift"}},
                {0b00001011,{"lsr","shift"}},
                {0b00001100,{"passa","aritmetica"}},
                {0b00001101,{"lch","constante"}},
                {0b00001110,{"lcl","constante"}},
                {0b00001111,{"load","memoria"}},
                {0b00010000,{"store","memoria"}},
                {0b00010001,{"jal","branch"}},
                {0b00010010,{"jr","branch"}},
                {0b00010011,{"beq","branch"}},
                {0b00010100,{"bne","branch"}},
                {0b00010101,{"j","branch"}},
                {0b00010110,{"bgt","branch"}},
                {0b00010111,{"blt","branch"}},
                {0b00011000,{"nand","logica"}},
                {0b00011001,{"nor","logica"}},
                {0b00011010,{"xnor","logica"}},
                {0b00011011,{"addi","constante"}},
                {0b00011100,{"subi","constante"}},
                {0b00011101,{"andi","constante"}},
                {0b00011110,{"ori","contante"}},
                {0b11111111,{"halt","abortar"}} 
            };

            if (hashInstrucao.find(opcode) == hashInstrucao.end()) {
                return {"",""};
            }

            return hashInstrucao[opcode];
        }

        string formatoInstrucao (uint8_t opcode) {
            map <uint8_t,string> hashOpcode = {
                {0b00000000,"E"},  //Address
                {0b00000001,"R"}, //Add
                {0b00000010,"R"}, //Sub
                {0b00000011,"R"}, //Zera
                {0b00000100,"R"}, //Xor
                {0b00000101,"R"}, //Or
                {0b00000110,"R"}, //Not
                {0b00000111,"R"}, //And
                {0b00001000,"R"}, //Shift left
                {0b00001001,"R"}, //Shift Right
                {0b00001010,"R"}, //Shift Logico Left
                {0b00001011,"R"}, //Shift Logico Right
                {0b00001100,"R"}, //Copia ....
                {0b00001101,"I"}, //lch
                {0b00001110,"I"}, //lcl
                {0b00001111,"R"}, //Load
                {0b00010000,"R"}, //Store
                {0b00010001,"J"}, //jal
                {0b00010010,"R"}, //Jr
                {0b00010011,"R"}, //Beq
                {0b00010100,"R"}, //Bne
                {0b00010101,"J"}, //J
                {0b00010110,"R"}, //bgt
                {0b00010111,"R"}, //blt
                {0b00011000,"R"}, //nand
                {0b00011001,"R"}, //nor
                {0b00011010,"R"}, //xnor
                {0b00011011,"I"}, //addi
                {0b00011100,"I"}, //subi
                {0b00011101,"I"}, //andi
                {0b00011110,"I"}, //ori
                {0b11111111,"J"}  //halt
            };


            if (hashOpcode.find(opcode) == hashOpcode.end()) {
                return "X";
            }

            return hashOpcode[opcode];
        }

        bitset<32> complementoDeDois (bitset<32> registrador) {
            registrador.flip();
            return somaBinaria(registrador,0b1).second;
        }

        pair<bool,bitset<32>> somaBinaria (bitset<32> registrador1, bitset<32> registrador2) {
            bitset<32> resultado;
            bitset<1> bitAuxiliar;
            bitset<1> carry;
            bool overflow = false;

            for (int i=0; i<32; i++) {
                if (registrador1[i] & registrador2[i] & carry[0] ) {
                    resultado[i] = 0b1;
                    carry = 0b1;
                    if (i == 31) {
                        overflow = true;
                    }
                }
                else if (registrador1[i] & registrador2[i] || registrador2[i] & carry[0] || registrador1[i] & carry[0]) {
                    resultado[i] = 0b0;
                    carry = 0b1;
                }
                else if (registrador1[i] | registrador2[i] || registrador2[i] | carry[0] || registrador1[i] | carry[0]) {
                    resultado[i] = 0b1;
                    carry = 0b0;
                }
                else {
                    resultado[i] = 0b0;
                    carry = 0b0;
                }
            }

            return {overflow,resultado};
        }

        pair<bool,bitset<32>> subtracaoBinaria (bitset<32> registrador1, bitset<32> registrador2) {
            return somaBinaria(registrador1,complementoDeDois(registrador2));
        }

        void atualizarContadorPc (unsigned novoContador) {
            contadorPC = novoContador;
        }

    public:
/* -- Construtor e Destrutor -- */
        Processador (vector<pair<unsigned,bitset<32>>> instrucoesCompiladas) {
            memoriaProcessador = new Memoria (instrucoesCompiladas);
            contadorPC = 0;
        }

        ~Processador () {
            delete[] memoriaProcessador;
        }
/* -- Método principal-- */
        void executarInstrucoes () {
            bitset<32> registradorIFID;
            Sextupla registradorIDEX;
            pair<bitset<8>, bitset<32>> registradorMEMWB;

            while (true) {
                registradorIFID = instructionFeatch();
                /* Parar de executar a hora que buscar uma instrução e nao achar nada */
                if (registradorIFID.none()) {
                    break;
                }

                registradorIDEX = instructionDecoder(registradorIFID);
                registradorMEMWB = execMemoria(registradorIDEX);

                if (!registradorMEMWB.first.none()) {
                    writeBack(registradorMEMWB);
                }
            }
        }
};