#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const double G = 9.81;
const double C = 12.5;
const double M = 65.1;

double analitik(double t) {
    return ((G * M) / C) * (1 - exp(-C * t / M));
}

double sayisal(double t) {
    if (t == 0) {
        return 0;
    }
    return sayisal(t - 1) + (G - (C / M) * sayisal(t - 1));
}

void writeDataToFile() {
    ofstream dataFile("veriler.txt");
    for (int i = 0; i <= 30; i++) {
        dataFile << i << " " << analitik(i) << " " << sayisal(i) << "\n";
    }
    dataFile.close();
}

int main(int argc, char **argv) {  
    writeDataToFile();

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot 'veriler.txt' using 1:2 with lines title 'Analitik', '' using 1:3 with lines title 'Sayısal'\n");
        fflush(gnuplotPipe);
        cout << "Grafik çizimi tamamlandı.\n";
    } else {
        cerr << "gnuplot bağlantısı yapılamadı!\n";
        return 1;
    }

    return 0;
}
