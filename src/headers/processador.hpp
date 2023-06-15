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

struct Septupla {
    bitset<8> opcode;

    bitset<32> dadoRegistradorA;
    bitset<32> dadoRegistradorB;
    bitset<32> dadoRegistradorC;

    bitset<8> numeroRegistradorC;

    bitset<8> imediate;

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
        Septupla instructionDecoder (bitset<32>instrucao) {
            /* Variáveis */
            Septupla registradores;
            string tipo;
            bitset<8> numeroRegistradorA;
            bitset<8> numeroRegistradorB;

            for (int i=31, j=7; i>=24; i--, j--) {
                registradores.opcode[j] = instrucao[i];
            }

            tipo = formatoInstrucao (registradores.opcode.to_ulong());


            if (tipo == "R3") {
                for (int i=7; i>=0; i--) {
                    numeroRegistradorA[i] = instrucao[i + 16];
                    numeroRegistradorB[i] = instrucao[i + 8];
                    registradores.numeroRegistradorC[i] = instrucao[i];
                }

                registradores.dadoRegistradorA = memoriaProcessador->getValorRegistrador(numeroRegistradorA.to_ulong());
                registradores.dadoRegistradorB = memoriaProcessador->getValorRegistrador(numeroRegistradorB.to_ulong());
            }

            else if (tipo == "R3i") {
                for (int i=7; i>=0; i--) {
                    numeroRegistradorA[i] = instrucao[i + 16];
                    registradores.numeroRegistradorC[i] = instrucao[i];

                    registradores.imediate[i] = instrucao[i + 8];
                }
                
                registradores.dadoRegistradorA = memoriaProcessador->getValorRegistrador(numeroRegistradorA.to_ulong());
            }

            else if (tipo == "R2") {
                for (int i=7; i>=0; i--) {
                    numeroRegistradorA[i] = instrucao[i + 16];
                    registradores.numeroRegistradorC[i] = instrucao[i];
                }

                registradores.dadoRegistradorA = memoriaProcessador->getValorRegistrador(numeroRegistradorA.to_ulong());
            }

            else if (tipo == "R1") {
                for (int i=7; i>= 0; i--) {
                    registradores.numeroRegistradorC[i] = instrucao[i];
                }

                registradores.dadoRegistradorC = memoriaProcessador->getValorRegistrador(registradores.numeroRegistradorC.to_ulong());
            }

            else if (tipo == "I") {
                for (int i=7; i>=0; i--) {
                    registradores.numeroRegistradorC[i] = instrucao[i];
                }

                for (int i=16; i>=0; i--) {
                    registradores.constante[i] = instrucao[i + 8];
                }
            }

            else if (tipo == "J") {
                for (int i=24; i>=0; i--) {
                    registradores.endereco[i] = instrucao[i];
                }
            }
            
            return registradores;
        }

        /* METADE PRONTO */
        pair<bitset<8>, bitset<32>> execMemoria (Septupla registradorIDEX) {

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

            else if (tipo.second == "constante") {
                return operacaoConstante (registradorIDEX, tipo.first);
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
        pair<bitset<8>,bitset<32>> operacaoMemoria (Septupla registradorIDEX, string tipo) {
            if (tipo == "load") { 
                bitset<32> endereco = registradorIDEX.dadoRegistradorA;
                bitset<32> dado (memoriaProcessador->getMemoriaDados(endereco.to_ulong()).to_ulong());
                
                return {registradorIDEX.numeroRegistradorC, dado};
            }

            else if (tipo == "store") {
                bitset<16> dado (registradorIDEX.dadoRegistradorA.to_ulong());
                memoriaProcessador->escritaMemoriaDados(dado,registradorIDEX.numeroRegistradorC.to_ulong());

                return {0b0, 0b0};
            }

            return {0b0, 0b0};
        }

        pair<bitset<8>,bitset<32>> operacaoAritmetica (Septupla registradorIDEX, string tipo) {
            if (tipo == "add") {
                pair<bool,bitset<32>> soma = somaBinaria(registradorIDEX.dadoRegistradorA,registradorIDEX.dadoRegistradorB);
                
                if (soma.first) {
                    /* flag de overflow */
                }

                else {
                    return {registradorIDEX.numeroRegistradorC,soma.second};
                }
            }

            else if (tipo == "sub") {
                pair<bool,bitset<32>> sub = subtracaoBinaria(registradorIDEX.dadoRegistradorA,registradorIDEX.dadoRegistradorB);
                
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
                return {registradorIDEX.numeroRegistradorC,registradorIDEX.dadoRegistradorA};
            }

            return {0b0,0b0};
        }

        pair<bitset<8>,bitset<32>> operacaoLogica (Septupla registradorIDEX, string tipo) {
            if (tipo == "xor") {
                return {registradorIDEX.numeroRegistradorC,(registradorIDEX.dadoRegistradorA ^ registradorIDEX.dadoRegistradorB)};
            }

            else if (tipo == "or") {
                return {registradorIDEX.numeroRegistradorC,(registradorIDEX.dadoRegistradorA | registradorIDEX.dadoRegistradorB)};
            }

            else if (tipo == "passnota") {
                return {registradorIDEX.numeroRegistradorC, ~registradorIDEX.dadoRegistradorA};
            }

            else if (tipo == "and") {
                return {registradorIDEX.numeroRegistradorC,(registradorIDEX.dadoRegistradorA & registradorIDEX.dadoRegistradorB)};
            }

            else if (tipo == "nand") {
                return {registradorIDEX.numeroRegistradorC,~(registradorIDEX.dadoRegistradorA & registradorIDEX.dadoRegistradorB)};
            }

            else if (tipo == "xnor") {
                return {registradorIDEX.numeroRegistradorC, ~(registradorIDEX.dadoRegistradorA ^ registradorIDEX.dadoRegistradorB)};
            }

            else if (tipo == "nor") {
                return {registradorIDEX.numeroRegistradorC,~(registradorIDEX.dadoRegistradorA | registradorIDEX.dadoRegistradorB)};
            }

            return {0b0,0b0};
        }

        pair<bitset<8>,bitset<32>> operacaoBranch (Septupla registradorIDEX, string tipo) {
            if (tipo == "jal") {
                bitset<32> contadorPCAtual (contadorPC + 1);
                bitset<8> registrador31 (31);

                atualizarContadorPc(registradorIDEX.endereco.to_ulong());

                return {registrador31,contadorPCAtual};
            }

            else if (tipo == "jr") {
                atualizarContadorPc(registradorIDEX.dadoRegistradorC.to_ulong());

                return {0b0, 0b0};
            }

            else if (tipo == "beq") {
                bitset<32> zero(0b0);

                if (subtracaoBinaria(registradorIDEX.dadoRegistradorA, registradorIDEX.dadoRegistradorB).second == zero) {
                    atualizarContadorPc (registradorIDEX.dadoRegistradorC.to_ulong());
                }

                return {0b0,0b0};
            }

            else if (tipo == "bne") {
                bitset<32> zero(0b0);

                if (subtracaoBinaria(registradorIDEX.dadoRegistradorA, registradorIDEX.dadoRegistradorB).second != zero) {
                    atualizarContadorPc (registradorIDEX.dadoRegistradorC.to_ulong());
                }

                return {0b0,0b0};
            }

            else if (tipo == "j") {
                atualizarContadorPc(registradorIDEX.endereco.to_ulong());

                return {0b0, 0b0};
            }

            else if (tipo == "bgt") {
                for (int i=31; i >= 0; i--) {
                    if (registradorIDEX.dadoRegistradorA[i] && !registradorIDEX.dadoRegistradorB[i]) {
                        atualizarContadorPc(registradorIDEX.dadoRegistradorC.to_ulong());
                        break;
                    } 
                    
                    else if ((registradorIDEX.dadoRegistradorA[i] && registradorIDEX.dadoRegistradorB[i]) || 
                            (!registradorIDEX.dadoRegistradorA[i] && !registradorIDEX.dadoRegistradorB[i])) {
                        continue;
                    }
                    
                    else {
                        break;
                    }
                }
                
                return {0b0, 0b0};
            }

            else if (tipo == "blt") {
                for (int i=31; i >= 0; i--) {
                    if (!registradorIDEX.dadoRegistradorA[i] && registradorIDEX.dadoRegistradorB[i]) {
                        atualizarContadorPc(registradorIDEX.dadoRegistradorC.to_ulong());
                        break;
                    } 
                    
                    else if ((registradorIDEX.dadoRegistradorA[i] && registradorIDEX.dadoRegistradorB[i]) || 
                            (!registradorIDEX.dadoRegistradorA[i] && !registradorIDEX.dadoRegistradorB[i])) {
                        continue;
                    }
                    
                    else {
                        break;
                    }
                }
                
                return {0b0, 0b0};
            }
        }

        pair<bitset<8>,bitset<32>> operacaoShift (Septupla registradorIDEX, string tipo) {
            if (tipo == "asl") { 
                return {registradorIDEX.numeroRegistradorC, registradorIDEX.dadoRegistradorA << registradorIDEX.dadoRegistradorB.to_ulong()};
            }

            else if (tipo == "asr") {
                bool ultimoBit = registradorIDEX.dadoRegistradorA[31];

                bitset<32> novoValor (registradorIDEX.dadoRegistradorA >> registradorIDEX.dadoRegistradorB.to_ullong());

                for (unsigned long i=31, j=0; j<registradorIDEX.dadoRegistradorB.to_ulong(); j++, i--) {
                    novoValor[i] = ultimoBit;
                }

                return {registradorIDEX.numeroRegistradorC , novoValor};
            }

            else if (tipo == "lsl") {
                return {registradorIDEX.numeroRegistradorC, registradorIDEX.dadoRegistradorA << registradorIDEX.dadoRegistradorB.to_ulong()};
            }

            else if (tipo == "lsr") {
                return {registradorIDEX.numeroRegistradorC, registradorIDEX.dadoRegistradorA >> registradorIDEX.dadoRegistradorB.to_ulong()};
            }

            return {0b0,0b0};
        }

        pair<bitset<8>,bitset<32>> operacaoConstante (Septupla registradorIDEX, string tipo) {
            if (tipo == "lch") {
                bitset<32> valor (registradorIDEX.constante.to_ulong());

                return {registradorIDEX.numeroRegistradorC, valor};
            }

            else if (tipo == "lcl") {
                bitset<32> valor (registradorIDEX.constante.to_ulong());

                return {registradorIDEX.numeroRegistradorC, valor};
            }

            else if (tipo == "addi") {
                bitset<32> dadoImediato (registradorIDEX.imediate.to_ulong());
                return {registradorIDEX.numeroRegistradorC, somaBinaria(registradorIDEX.dadoRegistradorA,dadoImediato).second};
            }

            else if (tipo == "subi") {
                bitset<32> dadoImediato (registradorIDEX.imediate.to_ulong());
                return {registradorIDEX.numeroRegistradorC, subtracaoBinaria(registradorIDEX.dadoRegistradorA,dadoImediato).second};
            }

            else if (tipo == "andi") {
                bitset<32> dadoImediato (registradorIDEX.imediate.to_ulong());
                return {registradorIDEX.numeroRegistradorC,(registradorIDEX.dadoRegistradorA & dadoImediato)};
            }

            else if (tipo == "ori") {
                bitset<32> dadoImediato (registradorIDEX.imediate.to_ulong());
                return {registradorIDEX.numeroRegistradorC,(registradorIDEX.dadoRegistradorA | dadoImediato)};
            }

            return {0b0,0b0};
        }

        pair<string,string> tipoInstrucao (unsigned opcode) {
            map <unsigned,pair<string,string>> hashInstrucao = {
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

        string formatoInstrucao (unsigned opcode) {
            map <unsigned,string> hashOpcode = {
                {0b00000000,"E"},  //Address
                {0b00000001,"R3"}, //Add
                {0b00000010,"R3"}, //Sub
                {0b00000011,"R1"}, //Zera
                {0b00000100,"R3"}, //Xor
                {0b00000101,"R3"}, //Or
                {0b00000110,"R2"}, //Not
                {0b00000111,"R3"}, //And
                {0b00001000,"R3"}, //Shift left
                {0b00001001,"R3"}, //Shift Right
                {0b00001010,"R3"}, //Shift Logico Left
                {0b00001011,"R3"}, //Shift Logico Right
                {0b00001100,"R2"}, //Copia ....
                {0b00001101,"I"}, //lch
                {0b00001110,"I"}, //lcl
                {0b00001111,"R2"}, //Load
                {0b00010000,"R2"}, //Store
                {0b00010001,"J"}, //jal
                {0b00010010,"R1"}, //Jr
                {0b00010011,"RB"}, //Beq
                {0b00010100,"RB"}, //Bne
                {0b00010101,"J"}, //J
                {0b00010110,"RB"}, //bgt
                {0b00010111,"RB"}, //blt
                {0b00011000,"R3"}, //nand
                {0b00011001,"R3"}, //nor
                {0b00011010,"R3"}, //xnor
                {0b00011011,"R3i"}, //addi
                {0b00011100,"R3i"}, //subi
                {0b00011101,"R3i"}, //andi
                {0b00011110,"R3i"}, //ori
                {0b11111111,"H"}  //halt
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
            delete memoriaProcessador;
        }
/* -- Método principal-- */
        void executarInstrucoes () {
            bitset<32> registradorIFID;
            Septupla registradorIDEX;
            pair<bitset<8>, bitset<32>> registradorMEMWB;

            while (true) {
                registradorIFID = instructionFeatch();

                /* Parar de executar a hora que buscar uma instrução e nao achar nada */
                if (registradorIFID.all()) {
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