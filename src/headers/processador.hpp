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
    bitset<32> registradorA;
    bitset<32> registradorB;
    bitset<8> registradorC;
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
            bitset<8> enderecoFonteA;
            bitset<8> enderecoFonteB;
            string tipo;

            tipo = tipoOperacao (registradores.opcode);

            if (tipo == "R") {  
                for (int i=7; i>=0; i--) {
                    registradores.opcode[i] = instrucao[i + 24];
                    enderecoFonteA[i] = instrucao[i + 16];
                    enderecoFonteB[i] = instrucao[i + 8];
                    registradores.registradorC[i] = instrucao[i];
                }    
                        
                registradores.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
                registradores.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
            }

            else if (tipo == "I") {
                for (int i=7; i>=0; i--) {
                    registradores.opcode[i] = instrucao[i + 24];
                    registradores.registradorC[i] = instrucao[i];
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
            bitset<32> result;

            if (registradorIDEX.opcode == 0b00000001) { // Instrução de ADD
                pair<bool,bitset<32>> soma = somaBinaria(registradorIDEX.registradorA,registradorIDEX.registradorB);
                
                if (soma.first) {
                    /* flag de overflow */
                }
                else {
                    result = soma.second;
                }
            }

            else if (registradorIDEX.opcode == 0b00000010) {
                somaBinaria(registradorIDEX.registradorA, complementoDeDois(registradorIDEX.registradorB));
            }

            else if (registradorIDEX.opcode == 0b00000011) {

            }

            else if (registradorIDEX.opcode == 0b00000100) {
                result = registradorIDEX.registradorA ^ registradorIDEX.registradorB;
            }

            else if (registradorIDEX.opcode == 0b00000101) {
                result = registradorIDEX.registradorA | registradorIDEX.registradorB;
            }

            else if (registradorIDEX.opcode == 0b00000110) {
                result = ~registradorIDEX.registradorA;
            }

            else if (registradorIDEX.opcode == 0b00000111) {
                result = registradorIDEX.registradorA & registradorIDEX.registradorB;

            }

            else if (registradorIDEX.opcode == 0b00001000) { // shift aritmetico para a esquerda
                
            }

            else if (registradorIDEX.opcode == 0b00001001) {

            }

            else if (registradorIDEX.opcode == 0b00001010) {

            }

            else if (registradorIDEX.opcode == 0b00001011) {

            }

            else if (registradorIDEX.opcode == 0b00001100) { //copia
                //move(registradorA, registradorB)
            }

            else if (registradorIDEX.opcode == 0b00001101) {

            }

            else if (registradorIDEX.opcode == 0b00001110) {

            }

            else if (registradorIDEX.opcode == 0b00001111) {

            }

            else if (registradorIDEX.opcode == 0b00010000) { //load

            }

            else if (registradorIDEX.opcode == 0b00010001) { //store

            }

            else if (registradorIDEX.opcode == 0b00010010) {

            }

            else if (registradorIDEX.opcode == 0b00010011) {

            }

            else if (registradorIDEX.opcode == 0b00010100) {

            }

            else if (registradorIDEX.opcode == 0b00010101) {

            }
            else if (registradorIDEX.opcode == 0b00010110) {

            }
            else if (registradorIDEX.opcode == 0b00010111) {

            }
            else if (registradorIDEX.opcode == 0b00011000) {

            }
            else if (registradorIDEX.opcode == 0b00011001) {

            }
            else if (registradorIDEX.opcode == 0b00010101) {

            }
            else if (registradorIDEX.opcode == 0b00011010) {

            }
            else if (registradorIDEX.opcode == 0b00011011) {

            }
            else if (registradorIDEX.opcode == 0b00011100) {

            }
            else if (registradorIDEX.opcode == 0b00011101) {

            }
            else if (registradorIDEX.opcode == 0b00011110) {

            }
            else if (registradorIDEX.opcode == 0b00011111) {

            }

            resultado.second = result;

            return resultado;
        }

        /* PRONTO */
        void writeBack (pair<bitset<8>, bitset<32>> dados) {
            /* Adicionar Flag RegWrite */
            memoriaProcessador->escritaBancoRegistradores(dados.second,dados.first.to_ulong());
        }

/* -- Métodos auxiliares -- */
        string tipoOperacao (bitset<8> opcode) {
            map <bitset<8>,string> hashOpcode = {
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
                {0b00010101,"J"}  //J
            };

            return hashOpcode[opcode];
        }

        bitset<32> complementoDeDois (bitset<32> registrador) {
            registrador.flip();
            bool carry = 1;
            int i = 0;

            while (carry) {
                if (!registrador[i]) {
                    registrador[i] = 0b1;
                    carry = 0;
                }
                else {
                    registrador[i] = 0b0;
                }
                i++;
            }
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
                    carry = 0b0;
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

        //copy
        void move(bitset<32> registradorCopia, bitset<32> registradorCopiado){
            registradorCopia = registradorCopiado;
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
                writeBack(registradorMEMWB);
            }
        }
};