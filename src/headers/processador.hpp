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

struct Quadrupla {
    bitset<8> opcode;
    bitset<32> registradorA;
    bitset<32> registradorB;
    bitset<8> registradorC;
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

        /* QUASE PRONTO */
        pair<Flags,Quadrupla> instructionDecoder (bitset<32>instrucao) {
            /* Variáveis */
            Flags controle;
            Quadrupla registradores;
            bitset<8>enderecoFonteA;
            bitset<8>enderecoFonteB;
            string tipo;
            
            for (int i=31; i>=0; i--) {
                for (int j=7; j>=0; j--, i--) {
                    registradores.opcode[j] = instrucao[i];
                }

                for (int j=7; j>=0; j--, i--) {
                    enderecoFonteA[j] = instrucao[i];
                }

                for (int j=7; j>=0; j--, i--) {
                    enderecoFonteB[j] = instrucao[i];
                }

                for (int j=7; j>=0; j--, i--) {
                    registradores.registradorC[j] = instrucao[i];
                }
            }

            tipo = tipoOperacao (registradores.opcode);

            /* controle = {overflow, neg, zero, carry, memRead, memWrite } */
            if (tipo == "soma") {             
                controle = {true,true,true,true,false,false};
                registradores.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
                registradores.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
            }

            else if (tipo == "zero") {
                controle = {false,false,true,false,false,false};
                registradores.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
                registradores.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
            }

            else if (tipo == "logica") {
                controle = {false,true,true,false,false,false};
                registradores.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
                registradores.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
            }
            
            else if (tipo == "constante") {
                controle = {false,false,false,false,false,false};
            }
            
            else if (tipo == "load") {
                controle = {false,false,false,false,true,false};
            }
            
            else if (tipo == "store") {
                controle = {false,false,false,false,false,true};
            }
            
            else if (tipo == "jump") {
                controle = {false,false,false,false,false,false};
            }
            
            else if (tipo == "jr") {
                controle = {false,false,false,false,false,false};
            }
            
            else if (tipo == "branch") {
                controle = {false,false,false,false,false,false};
            }
            
            return {controle,registradores};
        }

        /* METADE PRONTO */
        pair<bitset<8>, bitset<32>> execMemoria (pair<Flags,Quadrupla> decoder) {
            Flags controle = decoder.first;
            Quadrupla registradorIDEX = decoder.second;
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

            else if (registradorIDEX.opcode == 0b00001000) {

            }

            else if (registradorIDEX.opcode == 0b00001001) {

            }

            else if (registradorIDEX.opcode == 0b00001010) {

            }

            else if (registradorIDEX.opcode == 0b00001011) {

            }

            else if (registradorIDEX.opcode == 0b00001100) {
                
            }

            else if (registradorIDEX.opcode == 0b00001101) {

            }

            else if (registradorIDEX.opcode == 0b00001110) {

            }

            else if (registradorIDEX.opcode == 0b00001111) {

            }

            else if (registradorIDEX.opcode == 0b00010000) {

            }

            else if (registradorIDEX.opcode == 0b00010001) {

            }

            else if (registradorIDEX.opcode == 0b00010010) {

            }

            else if (registradorIDEX.opcode == 0b00010011) {

            }

            else if (registradorIDEX.opcode == 0b00010100) {

            }

            else if (registradorIDEX.opcode == 0b00010101) {

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
            if (opcode == 0b00000001 or opcode == 0b00000010) {
                return "soma";
            }
            else if (opcode == 0b00000011) {
                return "zero";
            }
            else if (opcode == 0b00000100 or opcode == 0b00000101 or 
                    opcode == 0b00000110 or opcode == 0b00000111 or 
                    opcode == 0b00001000 or opcode == 0b00001001 or 
                    opcode == 0b00001010 or opcode == 0b00001011 or opcode == 0b00001100) {
                return "logica";
            }
            else if (opcode == 0b00001101 or opcode == 0b00001110) {
                return "constante";
            }
            else if (opcode == 0b0001111) {
                return "load";
            }
            else if (opcode == 0b00010000) {
                return "store";
            }
            else if (opcode == 0b00010001 or opcode == 0b00010101) {
                return "jump";
            }
            else if (opcode == 0b00010010) {
                return "jr";
            }
            else if (opcode == 0b00010011 or opcode == 0b00010100) {
                return "branch";
            }
            else {
                return "";
            }
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
            pair<Flags,Quadrupla> registradorIDEX;
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