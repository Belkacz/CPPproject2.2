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
void getStudents(STUDENT[], int, string, bool &);
void randomOcens(STUDENT[], int, int, int, int);
double avgRaiting(STUDENT[], int, int);
int studentsOverAvg(STUDENT[], int, int, double);
void diplayStudentsData(STUDENT[], int, int, double);

int main() {
    cout << "Lukasz Belka nr. indeksu 156162, grupa D1, semestr 2, rok 1" << endl;

    bool cantOpenFileFlag = false;
    int N = getNumberOfStudents("done.txt", cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        return 0;
    }

    STUDENT* tabStudents = new STUDENT[N];
    cout << N << endl;

    getStudents(tabStudents, N, "done.txt", cantOpenFileFlag);

    srand(time(0));

    int minNum, maxNum;
    minNum = 1;
    maxNum = 5;

    randomOcens(tabStudents, N, minNum, maxNum, numberOfOcens);

    double avgRaitingAll = 0;
    avgRaitingAll = avgRaiting(tabStudents, N, numberOfOcens);
    cout << "srednia ocena wszystkich studentow wynosi " << avgRaitingAll << endl;

    int numSutudentsOverAvg = 0;
    numSutudentsOverAvg = studentsOverAvg(tabStudents, N, numberOfOcens, avgRaitingAll);
    cout << "liczba studnetow studentow powyzej wynosi " << avgRaitingAll << endl;

    diplayStudentsData(tabStudents, N, numberOfOcens, avgRaitingAll);
    // for(int i = 0; i<=N; i++){
    //     for(int j=0; j<=numberOfOcens; j++){
    //     cout<< tabStudents[i].nazwisko << " ocena " << tabStudents[i].oceny << endl;
    //     }
    // }
    delete[] tabStudents;

    return 0;
}

void getStudents(STUDENT tab[], int N, string filename, bool& cantOpenFileFlag) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            string name;
            string surname;

            file >> name >> surname;

            tab[i].imie = name;
            tab[i].nazwisko = surname;

            cout << "123";
            cout << name;
        }
    } else {
        cout << "Ups, coś poszło nie tak. Nie mogę otworzyć pliku. Zamykam." << endl;
        cantOpenFileFlag = true;
    }
    file.close();
}

// void getStudents(STUDENT tab[], int N, string filename, bool &cantOpenFileFlag){
//     ifstream file(filename);
//     if (file.is_open()) {
//         while(file.peek()!=EOF){
//             string zmienna; 
//             file >> zmienna;

//             cout << zmienna << " 123 ";
//             zmienna = "";
//         }
//     } else {
//         cout << "Ups, cos poszło nie tak. Nie mogę otworzyć pliku. Zamykam." << endl;
//         cantOpenFileFlag = true;
//     }
// }

void diplayStudentsData(STUDENT tab[], int N, int numberOfOcens, double avgRaitingAll){
    cout<< "Dane studentow w czytelnym sposobie " << endl;
        for (int i = 0; i < N; i++) {
            cout << "Imie: " << tab[i].imie << " Nazwisko: " << tab[i].nazwisko << " Srednia: " << tab[i].srednia << " Oceny: ";
            for (int j = 0; j < numberOfOcens; j++) {
                cout<< tab[i].oceny[j] << ", ";
            }
        }
}

int studentsOverAvg(STUDENT tab[], int N, int numberOfOcens, double avgRaitingAll){
    double sumRainngStudnet = 0;
    int numSutudentsOverAvg = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < numberOfOcens; j++) {
                sumRainngStudnet += tab[i].oceny[j];
            }
            tab[i].srednia = sumRainngStudnet / numberOfOcens;
            sumRainngStudnet = 0;
            if(tab[i].srednia > avgRaitingAll){
                numSutudentsOverAvg++;
            }
        }
    return numSutudentsOverAvg;
}

double avgRaiting(STUDENT tab[], int N, int numberOfOcens){
    double avgRaitingAll = 0;
    double sumRainngAll = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfOcens; j++) {
            sumRainngAll += tab[i].oceny[j];
        }
    }
    sumRainngAll = sumRainngAll / (N * numberOfOcens);
    return sumRainngAll;
}

void randomOcens(STUDENT tab[], int N, int minNum, int maxNum, int numberOfOcens) {
    srand(time(0));
    // maxNum = maxNum * 10;
    // minNum =  minNum * 10;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfOcens; j++) {
            //tab[i].oceny[j] = (rand() % (maxNum - minNum) + minNum) / 10.0;
            tab[i].oceny[j] = (rand() % (maxNum - minNum) + minNum);
            int halfFlag = rand() % 2;
            if(halfFlag == 1){
                tab[i].oceny[j] += 0.5;
            }
        }
    }
}

int getNumberOfStudents(string filename, bool &cantOpenFileFlag) {
    ifstream file(filename);
    int L = 0;
    int userInput = 0;
    cout << "Ilu chcesz wczytać studentow? " << endl;
    cin >> userInput;
    if (file.is_open()) {
        string line;
        while (getline(file, line)){
            L++;
        }
    } else {
        cout << "Ups, cos poszło nie tak. Nie mogę otworzyć pliku. Zamykam." << endl;
        cantOpenFileFlag = true;
    }
    if(userInput > L){
        cout << "Podana liczba przekracza maksymalną liczbę wczytanych studentow: " << L << endl;
        return L;
    } else {
        return userInput;
    }
}
