#include <memoria.h>

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
    int contador = 7;
    for(int i = 31; i > 23; i--){
        controle.opcode[contador] = instrucao[i];
        contador--;
    }
    contador = 7;
    for(int i = 23; i > 15; i--){
        enderecoFonteA[contador] = instrucao[i];
        contador--;
    }
    contador = 7;
    for(int i = 15; i > 7; i--){
        enderecoFonteB[contador] = instrucao[i];
        contador--;
    }
    contador = 7;
    for(int i = 7; i >= 0; i--){
        controle.registradorC[contador] = instrucao[i];
        contador--;
    }

    //Tratando as operações add e sub.
    if(controle.opcode == 0b00000001 or controle.opcode == 0b00000010){
        controle.carry = true;
        controle.neg = true;
        controle.zero = true;
        controle.carry = true;
        controle.memRead = false;
        controle.memWrite = false;
    }
    else if(controle.opcode == 0b00000011){ //Instrução de zero
        controle.zero = true;
        controle.carry = false;
        controle.neg = false;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = false;
    }
    //Instruções Lógicas
    else if(controle.opcode == 0b00000100 or controle.opcode == 0b00000101 or controle.opcode == 0b00000110 or controle.opcode == 0b00000111 or controle.opcode == 0b00001000 or controle.opcode == 0b00001001 or controle.opcode == 0b00001010 or controle.opcode == 0b00001011 or controle.opcode == 0b00001100){
        controle.zero = true;
        controle.carry = false;
        controle.neg = true;
        controle.carry = false;
        controle.memRead = false;
        controle.memWrite = false;
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
}