// Łukasz Belka nr. indeksu 156162
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int numberOfOcens = 5;

struct STUDENT {
    string imie;
    string nazwisko;
    double oceny[numberOfOcens];
    double srednia;
};

int getNumberOfStudents(string, bool &);
void randomOcens(STUDENT[], int, int, int, int);

int main() {
    cout << "Lukasz Belka nr. indeksu 156162, grupa D1, semestr 2, rok 1" << endl;

    bool cantOpenFileFlag;
    int N = getNumberOfStudents("done.txt", cantOpenFileFlag);

    STUDENT* tabStudents = new STUDENT[N];
    cout << N << endl;

    srand(time(0));

    int minNum, maxNum;
    minNum = 1;
    maxNum = 5;

    randomOcens(tabStudents, N, minNum, maxNum, numberOfOcens);
    
    // for(int i = 0; i<=N; i++){
    //     for(int j=0; j<=numberOfOcens; j++){
    //     cout<< tabStudents[i].nazwisko << " ocena " << tabStudents[i].oceny << endl;
    //     }
    // }
    delete[] tabStudents;

    return 0;
}

void randomOcens(STUDENT tab[], int N, int minNum, int maxNum, int numberOfOcens) {
    srand(time(0));
    maxNum = maxNum * 10;
    minNum =  minNum * 10;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfOcens; j++) {
            tab[i].oceny[j] = (rand() % (maxNum - minNum) + minNum) / 10.0;

            cout << tab[i].oceny[j]<< "     ";
        }
    }
}

int getNumberOfStudents(string filename, bool &cantOpenFileFlag) {
    ifstream file(filename);
    int L = 0;
    int userInput = 0;
    cout << "Ilu chcesz wczytać studentów? " << endl;
    cin >> userInput;
    if (file.is_open()) {
        string line;
        while (getline(file, line)){
            L++;
        }
    } else {
        cout << "Ups, coś poszło nie tak. Nie mogę otworzyć pliku. Zamykam." << endl;
        cantOpenFileFlag = true;
    }
    if(userInput > L){
        cout << "Podana liczba przekracza maksymalną liczbę wczytanych studentów: " << L << endl;
        return L;
    } else {
        return userInput;
    }
}
