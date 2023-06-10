#include <bits/stdc++.h>
#include <memoria.hpp>
using namespace std;

struct Flags {
    bool overflow;
    bool neg;
    bool zero;
    bool carry;
    bool memRead;
    bool memWrite;
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
            Quadrupla registradorIDEX;
            bitset<8>enderecoFonteA;
            bitset<8>enderecoFonteB;
            string tipo;
            
            for (int i=31; i>=0; i--) {
                for (int j=7; j>=0; j--, i--) {
                    registradorIDEX.opcode[j] = instrucao[i];
                }

                for (int j=7; j>=0; j--, i--) {
                    enderecoFonteA[j] = instrucao[i];
                }

                for (int j=7; j>=0; j--, i--) {
                    enderecoFonteB[j] = instrucao[i];
                }

                for (int j=7; j>=0; j--, i--) {
                    registradorIDEX.registradorC[j] = instrucao[i];
                }
            }

            tipo = tipoOperacao (registradorIDEX.opcode);

            /* controle = {overflow, neg, zero, carry, memRead, memWrite } */
            if (tipo == "soma") {             
                controle = {false,true,true,true,false,false};
                registradorIDEX.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
                registradorIDEX.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
            }

            else if (tipo == "zero") {
                controle = {false,false,true,false,false,false};
                registradorIDEX.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
                registradorIDEX.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
            }

            else if (tipo == "logica") {
                controle = {false,true,true,false,false,false};
                registradorIDEX.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
                registradorIDEX.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
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
                controle = {false,false,false,false,false,true};
            }
            
            else if (tipo == "jr") {
                controle = {false,false,false,false,false,true};
            }
            
            else if (tipo == "branch") {
                controle = {false,false,false,false,false,true};
            }
            
            return {controle,registradorIDEX};
        }

        /* METADE PRONTO */
        pair<bitset<8>, bitset<32>> execMemoria (pair<Flags,Quadrupla> decoder) {
            Flags controle = decoder.first;
            Quadrupla registradorIDEX = decoder.second;
            pair<bitset<8>,bitset<32>> resultado;
            bitset<32> result;

            if (registradorIDEX.opcode == 0b00000001) { // Instrução de ADD
                result = registradorIDEX.registradorA | registradorIDEX.registradorB;
            }

            else if (registradorIDEX.opcode == 0b00000010) {
                
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

            return resultado;
        }

        /* PRONTO */
        void writeBack (pair<bitset<8>, bitset<32>> dados) {
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

        }
};