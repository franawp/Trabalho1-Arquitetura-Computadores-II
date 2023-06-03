#include <iostream>
#include <chrono>
#include <thread>

void loadingBar(int progress, int total, int barWidth) {
    float percent = static_cast<float>(progress) / total;
    int numChars = static_cast<int>(percent * barWidth);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < numChars)
            std::cout << "=";
        else if (i == numChars)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(percent * 100.0) << "%\r";
    std::cout.flush();
}

int main() {
    int total = 100;
    int barWidth = 40;

    for (int i = 0; i <= total; ++i) {
        loadingBar(i, total, barWidth);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << std::endl << "Concluído!" << std::endl;

    return 0;
}
