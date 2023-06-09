#include <bits/stdc++.h>
using namespace std;

int main () {
    bitset<8> instrucao1;
    bitset<8> instrucao2;
    bitset<8> instrucao3;
    bitset<8> instrucao4;
    bitset<32> completa = 0b011001011101000111010011;

    for (int i=31; i>=0; i--) {
        for (int j=7; j>=0; j--, i--) {
            instrucao1[j] = completa[i];
        }

        for (int j=7; j>=0; j--, i--) {
            instrucao2[j] = completa[i];
        }

        for (int j=7; j>=0; j--, i--) {
            instrucao3[j] = completa[i];
        }

        for (int j=7; j>=0; j--, i--) {
            instrucao4[j] = completa[i];
        }
    }

    cout << instrucao1 << endl << instrucao2 << endl << instrucao3 << endl << instrucao4 << endl;
}

/*
int main () {
    vector<string> instrucoes = {
        "add r3, r2, r1",
        "sub r3, r2, r1"
    };
    vector<string> instrucoes_splitadas;

    for (const string& instrucao : instrucoes) {
        istringstream splitar_instrucao(instrucao);

        string string_auxiliar;
        vector<string> instrucoes_splitadas;

        while (splitar_instrucao >> string_auxiliar) {
            instrucoes_splitadas.push_back(string_auxiliar);
        }

        for (string& temp : instrucoes_splitadas) {
            auto posicaoVirgula = find(temp.begin(), temp.end(), ',');
            if (posicaoVirgula != temp.end()) {
                temp.erase(posicaoVirgula);
            }
            cout << temp << endl;
        }
    }

    return 0;
}
*/
/* 
void loadingBar(int progress, int total, int barWidth) {
    float percent = static_cast<float>(progress) / total;
    int numChars = static_cast<int>(percent * barWidth);

    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < numChars)
            cout << "=";
        else if (i == numChars)
            cout << ">";
        else
            cout << " ";
    }
    cout << "] " << static_cast<int>(percent * 100.0) << "%\r";
    cout.flush();
}

int main() {
    int total = 100;
    int barWidth = 40;

    for (int i = 0; i <= total; ++i) {
        loadingBar(i, total, barWidth);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << endl << "Concluído!" << endl;

    return 0;
}
*/