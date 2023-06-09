struct Flags {
    bitset<8>* opcode;
    bitset<8>* registradorA;
    bitset<8>* registradorB;
    bitset<8>* registradorC;
    bool overflow;
    bool neg;
    bool zero;
    bool carry;
    bool memRead;
    bool memWrite;
};

Flags instructionDecoder(Flags *flags,bitset<32>instrucao){
    

    Flags controles;
    return controles;
}