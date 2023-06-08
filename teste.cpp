#include <bits/stdc++.h>
using namespace std;

int main () {
    bitset<7> numero = 35;
    cout << numero << endl;
    return 0;
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