#include <bits/stdc++.h>
#include <instructionDecoder.h>
using namespace std;

/* 
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
*/



pair<bitset<8>, bitset<32>> execMemoria (Flags controle,Memoria *memProcessador) {
    pair<bitset<8>,bitset<32>> resultado;
    bitset<32> result;

    if(controle.opcode == 0b00000001){ // Instrução de ADD
        result = controle.registradorA | controle.registradorB;
    }
    else if(controle.opcode == 0b00000010){
        
    }
    else if(controle.opcode == 0b00000011){

    }
    else if(controle.opcode == 0b00000100){
        result = controle.registradorA ^ controle.registradorB;
    }
    else if(controle.opcode == 0b00000101){
        result = controle.registradorA | controle.registradorB;

    }
    else if(controle.opcode == 0b00000110){
        result = ~controle.registradorA;
    }
    else if(controle.opcode == 0b00000111){
        result = controle.registradorA & controle.registradorB;

    }
    else if(controle.opcode == 0b00001000){

    }
    else if(controle.opcode == 0b00001001){

    }
    else if(controle.opcode == 0b00001010){

    }
    else if(controle.opcode == 0b00001011){

    }
    else if(controle.opcode == 0b00001100){
        
    }
    else if(controle.opcode == 0b00001101){

    }
    else if(controle.opcode == 0b00001110){

    }
    else if(controle.opcode == 0b00001111){

    }
    else if(controle.opcode == 0b00010000){

    }
    else if(controle.opcode == 0b00010001){

    }
    else if(controle.opcode == 0b00010010){

    }
    else if(controle.opcode == 0b00010011){

    }
    else if(controle.opcode == 0b00010100){

    }
    else if(controle.opcode == 0b00010101){

    }
    return resultado;
}