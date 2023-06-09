#include <bits/stdc++.h>
#include <memoria.h>
using namespace std;

struct Flags {
    bitset<8> opcode;
    bitset<32> registradorA;
    bitset<32> registradorB;
    bitset<8> registradorC;
    bool overflow;
    bool neg;
    bool zero;
    bool carry;
    bool memRead;
    bool memWrite;
};

Flags instructionDecoder(bitset<32>instrucao,Memoria *memoriaProcessador){
    Flags controle;
    bitset<8>enderecoFonteA;
    bitset<8>enderecoFonteB;
    for (int i=31; i>=0;) {
        for (int j=7; j>=0; j--, i--) {
            controle.opcode[j] = instrucao[i];
        }

        for (int j=7; j>=0; j--, i--) {
            enderecoFonteA[j] = instrucao[i];
        }

        for (int j=7; j>=0; j--, i--) {
            enderecoFonteB[j] = instrucao[i];
        }

        for (int j=7; j>=0; j--, i--) {
            controle.registradorC[j] = instrucao[i];
        }
    }

    //Tratando as operações add e sub.
    if(controle.opcode == 0b00000001 or controle.opcode == 0b00000010){
        controle.carry = true;
        controle.neg = true;
        controle.zero = true;
        controle.carry = true;
        controle.memRead = false;
        controle.memWrite = false;
        controle.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
        controle.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
    }
    else if(controle.opcode == 0b00000011){ //Instrução de zero
        controle.zero = true;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = false;
        controle.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
        controle.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
    }
    //Instruções Lógicas
    else if(controle.opcode == 0b00000100 or controle.opcode == 0b00000101 or controle.opcode == 0b00000110 or controle.opcode == 0b00000111 or controle.opcode == 0b00001000 or controle.opcode == 0b00001001 or controle.opcode == 0b00001010 or controle.opcode == 0b00001011 or controle.opcode == 0b00001100){
        controle.zero = true;
        controle.carry = false;
        controle.neg = true;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = false;
        controle.registradorA = memoriaProcessador->getValorRegistrador(enderecoFonteA.to_ulong());
        controle.registradorB = memoriaProcessador->getValorRegistrador(enderecoFonteB.to_ulong());
    }
    //Instruções de constante
    else if(controle.opcode == 0b00001101 or controle.opcode == 0b00001110){
        controle.zero = false;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = true; // talvez
    }
    //Instrução de Load
    else if(controle.opcode == 0b0001111){
        controle.zero = false;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = true;
        controle.memWrite = false;
    }
    // Instrução de Store
    else if(controle.opcode == 0b00010000){
        controle.zero = false;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = true;
    }
    // Intrução do tipo Jal e j
    else if(controle.opcode == 0b00010001 or controle.opcode == 0b00010101){
        controle.zero = false;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = true;
    }
    // Instrução do tipo jr
    else if(controle.opcode == 0b00010010){
        controle.zero = false;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = true;
    }
    // Instrução beq e bne
    else if(controle.opcode == 0b00010011 or controle.opcode == 0b00010100){
        controle.zero = false;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = true;
    }
    return controle;
}