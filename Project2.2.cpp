// Łukasz Belka nr. indeksu 156162
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int numberOfSchoolGrade = 5;

struct STUDENT {
    string imie;
    string nazwisko;
    double oceny[numberOfSchoolGrade];
    double srednia;
    int indeks;
};

int getNumberOfStudents(string, bool &);
void getStudents(STUDENT[], int, string, bool &);
void randomSchoolGrade(STUDENT[], int, int, int, int);
double avgRaiting(STUDENT[], int, int);
int studentsOverAvg(STUDENT[], int, int, double);
void displayStudentsData(STUDENT[], int, int, string);
void takeAndSortStudents(STUDENT[], STUDENT[], int, double);
void setStudents(STUDENT[], int, bool &);
void search(STUDENT[], int, int);


int main() {
    cout << "Lukasz Belka nr. indeksu 156162, grupa D1, semestr 2, rok 1" << endl;

    bool cantOpenFileFlag = false;
    int N = getNumberOfStudents("dane.txt", cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        return 0;
    }

    STUDENT* tabStudents = new STUDENT[N];

    //cout << N << endl;

    getStudents(tabStudents, N, "dane.txt", cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        return 0;
    }

    srand(time(0));

    int minNum, maxNum;
    minNum = 1;
    maxNum = 5;

    randomSchoolGrade(tabStudents, N, minNum, maxNum, numberOfSchoolGrade);

    double avgRaitingAll = 0;
    avgRaitingAll = avgRaiting(tabStudents, N, numberOfSchoolGrade);


    int numSutudentsOverAvg = 0;
    numSutudentsOverAvg = studentsOverAvg(tabStudents, N, numberOfSchoolGrade, avgRaitingAll);

    displayStudentsData(tabStudents, N, numberOfSchoolGrade, "Dane studentow ");
    cout << endl;
    cout << "srednia ocena wszystkich studentow wynosi " << avgRaitingAll << endl;
    cout << "liczba studnetow studentow powyzej wynosi " << numSutudentsOverAvg << endl;

    STUDENT* tabBestStudents = new STUDENT[numSutudentsOverAvg];
    takeAndSortStudents(tabStudents, tabBestStudents, N, avgRaitingAll);


    displayStudentsData(tabBestStudents, numSutudentsOverAvg, numberOfSchoolGrade,"Posortowane dane najlepszych studentow (powyzej sredniej) wedlug sredniej ");

    setStudents(tabBestStudents, numSutudentsOverAvg, cantOpenFileFlag);
    if(cantOpenFileFlag == true){
        return 0;
    }

    search(tabStudents, N, numberOfSchoolGrade);

    delete[] tabStudents;

    return 0;
}

void search(STUDENT tab[], int N, int numberOfSchoolGrade){
    int chose = 19;
    cout << endl;
    cout << " Podaj numer kategorii wysuzkiwania :" << endl;
    cout << " 1) Indeks " << endl;
    cout << " 2) Imie " << endl;
    cout << " 3) Nazwisko " << endl;
    cout << " 4) Srednia " << endl;
    cout << " 5) Konkretna ocena " << endl;
    cout << " 0) Wyjscie " << endl;
    cin >> chose;

    switch (chose){
        case 1:{
            int idxSerched = 0;
            cout << "Podaj nr. indeksu szukanej osoby " << endl;
            cin >> idxSerched;

            int searchCouter = 0;
            for(int i=0; i<N; i++){
                if(idxSerched == tab[i].indeks){
                    searchCouter ++;
                }
            }
            STUDENT* serchedStudentsTab = new STUDENT[searchCouter];
            int counter = 0;
            for(int i=0; i<N; i++){
                if(idxSerched == tab[i].indeks){
                    serchedStudentsTab[counter] = tab[i];
                    counter++;
                }
            }
            if(counter == 0){
                cout << "Nie znalezniono. Brak danych" << endl;
            } else {
                displayStudentsData(serchedStudentsTab, counter, numberOfSchoolGrade,"Dane osob znalezionych na podstawie indeksu: ");
            }
            delete[] serchedStudentsTab;
            break;
        }

        case 2:{
            string nameSerched = "";
            cout << "Podaj imie szukanej osoby " << endl;
            cin >> nameSerched;
            int searchCouter = 0;
            for(int i=0; i<N; i++){
                if(nameSerched == tab[i].imie){
                    searchCouter ++;
                }
            }
            STUDENT* serchedStudentsTab = new STUDENT[searchCouter];
            int counter = 0;
            for(int i=0; i<N; i++){
                if(nameSerched == tab[i].imie){
                    serchedStudentsTab[counter] = tab[i];
                    counter++;
                }
            }
            if(counter == 0){
                cout << "Nie znalezniono. Brak danych" << endl;
            } else {
                displayStudentsData(serchedStudentsTab, counter, numberOfSchoolGrade,"Dane osob znalezionych na podstawie imienia: ");
            }
            delete[] serchedStudentsTab;
            break;
        }

        case 3:{
            string nameSerched = "";
            cout << "Podaj nazwisko szukanej osoby " << endl;
            cin >> nameSerched;
            int searchCouter = 0;
            for(int i=0; i<N; i++){
                if(nameSerched == tab[i].nazwisko){
                    searchCouter ++;
                }
            }
            STUDENT* serchedStudentsTab = new STUDENT[searchCouter];
            int counter = 0;
            for(int i=0; i<N; i++){
                if(nameSerched == tab[i].nazwisko){
                    serchedStudentsTab[counter] = tab[i];
                    counter++;
                }
            }
            if(counter == 0){
                cout << "Nie znalezniono. Brak danych" << endl;
            } else {
                displayStudentsData(serchedStudentsTab, counter, numberOfSchoolGrade,"Dane osob znalezionych na podstawie nazwiska: ");
            }

            delete[] serchedStudentsTab;
            break;
        }

        case 4:{
            int fail = 1;
            double minAvg = 0;
            double maxAvg = 0;
            while (fail != 0){
                cout << "Podaj dolna granice sredniej " << endl;
                cin >> minAvg;
                cout << "Podaj gorna granice sredniej " << endl;
                cin >> maxAvg;
                if ( minAvg > maxAvg ){
                    cout << "Podana maksymalna wartosc jest mniejsza od minimalnej. Sprobuj ponownie" << endl;
                    fail = 1;
                } else {
                    fail = 0;
                    int searchCouter = 0;
                    for(int i=0; i<N; i++){
                        if(tab[i].srednia >= minAvg && tab[i].srednia <= maxAvg){
                            searchCouter ++;
                        }
                    }
                    STUDENT* serchedStudentsTab = new STUDENT[searchCouter];
                    int counter = 0;
                    for(int i=0; i<N; i++){
                        if(tab[i].srednia >= minAvg && tab[i].srednia <= maxAvg){
                            serchedStudentsTab[counter] = tab[i];
                            counter++;
                        }
                    }
                    if(counter == 0){
                        cout << "Nie znalezniono. Brak danych" << endl;
                    } else {
                        displayStudentsData(serchedStudentsTab, counter, numberOfSchoolGrade,"Dane osob znalezionych na podstawie sredniej: ");
                    }
                    delete[] serchedStudentsTab;
                }
            }
            break;
        }

        case 5:{
        int fail = 1;
        double minRaiting = 0;
        double maxRaiting = 0;
        while (fail != 0){
            cout << "Podaj dolna granice oceny " << endl;
            cin >> minRaiting;
            cout << "Podaj gorna granice oceny " << endl;
            cin >> maxRaiting;
            if ( minRaiting > maxRaiting ){
                cout << "Podana maksymalna wartosc jest mniejsza od minimalnej. Sprobuj ponownie" << endl;
                fail = 1;
            } else {
                fail = 0;
                int searchCouter = 0;
                for(int i=0; i<N; i++){
                    bool hasRaiting = false;
                    for(int j=0; j < numberOfSchoolGrade; j++){
                        if(tab[i].oceny[j] >= minRaiting && tab[i].oceny[j] <= maxRaiting){
                            hasRaiting = true;
                        }
                    }
                    if(hasRaiting){
                        searchCouter++;
                    }
                }
                STUDENT* serchedStudentsTab = new STUDENT[searchCouter];
                int counter = 0;
                for(int i=0; i<N; i++){
                    bool hasRaiting = false;
                    for(int j=0; j < numberOfSchoolGrade; j++){
                        if(tab[i].oceny[j] >= minRaiting && tab[i].oceny[j] <= maxRaiting){
                            hasRaiting = true;
                        }
                    }
                    if(hasRaiting){
                        serchedStudentsTab[counter] = tab[i];
                        counter++;
                    }
                }
                
                if(counter == 0){
                    cout << "Nie znalezniono. Brak danych" << endl;
                } else {
                    displayStudentsData(serchedStudentsTab, counter, numberOfSchoolGrade,"Dane osob znalezionych na podstawie sredniej: ");
                }
                delete[] serchedStudentsTab;
                }
            }
            break;
        }
    }
}

void setStudents(STUDENT tab[], int N, bool& cantOpenFileFlag){
    string filename = "";
    cout << endl;
    cout << "Podaj nazwe pliku do zapisanima najlepszych studentow "<< endl;
    cin >> filename;
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << tab[i].indeks << ' ' << tab[i].imie << ' ' << tab[i].nazwisko << ' ' << tab[i].srednia <<endl;
        }
    } else {
        cout << "Ups, cos poszlo nie tak. Nie moge otworzyc pliku. Zamykam." << endl;
        cantOpenFileFlag = true;
    }
    file.close();
}

void takeAndSortStudents(STUDENT tab[], STUDENT bestStudentstab[], int N, double avgRaitingAll){
    int counter = 0;
    for (int i = 0; i < N; i++) {
        if(tab[i].srednia > avgRaitingAll){
            bestStudentstab[counter] = tab[i];
            counter++;
        }
    }
    
    bool sorted = false;
    while (sorted == false){
        int actionCounter = 0;
        for (int i = 0; i < counter; i++) {
            if(i > 0 && bestStudentstab[i].srednia > bestStudentstab[i-1].srednia){
                STUDENT tempStudent;
                tempStudent = bestStudentstab[i-1];
                bestStudentstab[i-1] = bestStudentstab[i];
                bestStudentstab[i] = tempStudent;
                actionCounter ++;
            }
        }
        if(actionCounter == 0){
            sorted = true;
        }
    }
}

void getStudents(STUDENT tab[], int N, string filename, bool& cantOpenFileFlag){
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            string name;
            string surname;
            file >> name >> surname;
            tab[i].imie = name;
            tab[i].nazwisko = surname;
        }
    } else {
        cout << "Ups, cos poszlo nie tak. Nie moge otworzyc pliku. Zamykam." << endl;
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
//         cout << "Ups, cos poszlo nie tak. Nie moge otworzyc pliku. Zamykam." << endl;
//         cantOpenFileFlag = true;
//     }
// }

void displayStudentsData(STUDENT tab[], int N, int numberOfSchoolGrade, string text){
    cout << endl;
    cout<< text << endl;
    cout << endl;
        for (int i = 0; i < N; i++) {
            cout << "indeks nr. " << tab[i].indeks << ", Imie: " << tab[i].imie << ", Nazwisko: " << tab[i].nazwisko << ", Srednia: " << tab[i].srednia << ", Oceny: ";
            for (int j = 0; j < numberOfSchoolGrade; j++) {
                cout<< tab[i].oceny[j] << ", ";
            }
            cout << endl;
        }
}

int studentsOverAvg(STUDENT tab[], int N, int numberOfSchoolGrade, double avgRaitingAll){
    double sumRainngStudnet = 0;
    int numSutudentsOverAvg = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < numberOfSchoolGrade; j++) {
                sumRainngStudnet += tab[i].oceny[j];
            }
            tab[i].srednia = sumRainngStudnet / numberOfSchoolGrade;
            sumRainngStudnet = 0;
            if(tab[i].srednia > avgRaitingAll){
                numSutudentsOverAvg++;
            }
        }
    return numSutudentsOverAvg;
}

double avgRaiting(STUDENT tab[], int N, int numberOfSchoolGrade){
    double avgRaitingAll = 0;
    double sumRainngAll = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfSchoolGrade; j++) {
            sumRainngAll += tab[i].oceny[j];
        }
    }
    sumRainngAll = sumRainngAll / (N * numberOfSchoolGrade);
    return sumRainngAll;
}

void randomSchoolGrade(STUDENT tab[], int N, int minNum, int maxNum, int numberOfSchoolGrade) {
    srand(time(0));
    // maxNum = maxNum * 10;
    // minNum =  minNum * 10;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfSchoolGrade; j++) {
            tab[i].oceny[j] = (rand() % ((maxNum*2) - minNum) + minNum*2);
            //cout << tab[i].oceny[j] <<  " | " ;
            tab[i].oceny[j] = tab[i].oceny[j] / 2.0;
            // tab[i].oceny[j] = (rand() % (maxNum+1 - minNum) + minNum);

            // int halfFlag = rand() % 2;
            // if(halfFlag == 1){
            //     tab[i].oceny[j] += 0.5;
            // }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfSchoolGrade; j++) {
            //tab[i].oceny[j] = (rand() % (maxNum - minNum) + minNum) / 10.0;
            tab[i].indeks = (rand() % (999999 - 100000) + 100000);
        }
    }
}

int getNumberOfStudents(string filename, bool &cantOpenFileFlag) {
    ifstream file(filename);
    int L = 0;
    int userInput = 0;
    cout << "Ilu chcesz wczytac studentow? " << endl;
    cin >> userInput;
    if (file.is_open()) {
        string line;
        while (getline(file, line)){
            L++;
        }
    } else {
        cout << "Ups, cos poszlo nie tak. Nie moge otworzyc pliku. Zamykam." << endl;
        cantOpenFileFlag = true;
        return 0;
    }
    if(userInput > L){
        cout << "Podana liczba przekracza maksymalna liczbe wczytanych studentow: " << L << endl;
        return L;
    } else {
        return userInput;
    }
}
