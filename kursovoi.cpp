#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int MAX_STUD = 1000;
const int MAX_PAN = 50;
const int MAX_ID = 2000;
const string FAIL_ATY = "students.txt";

struct Pan {
    string aty;
    int baga;
};

struct Student {
    int id;
    string aty_zhoni;
    string toby;
    vector<Pan> pander;
};


vector<Student> studentter;

string matinOku(string surak) {
    string text;
    while (true) {
        cout << surak;
        getline(cin, text);
        if (text == "") {
            cout << "Бос сөз енгізуге болмайды." << endl;
        } else {
            return text;
        }
    }
}

int sanOku(string surak, int minSan, int maxSan) {
    int san;
    while (true) {
        cout << surak;
        cin >> san;

        if (cin.fail() == true) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Тек сан енгізіңіз!" << endl;
            continue;
        }

        cin.ignore(1000, '\n');

        if (san < minSan || san > maxSan) {
            cout << "Санды " << minSan << " мен " << maxSan << " аралығында енгізіңіз." << endl;
            continue;
        }

        return san;
    }
}

int studTabu(int id) {
    int n = studentter.size();
    for (int i = 0; i < n; i++) {
        if (studentter[i].id == id) {
            return i;
        }
    }
    return -1;
}

double ortashaBaga(int index) {
    int panSany = studentter[index].pander.size();
    if (panSany == 0) {
        return 0;
    }

    double kosyndy = 0;
    for (int i = 0; i < panSany; i++) {
        kosyndy +=  studentter[index].pander[i].baga;
    }

    double ortasha = kosyndy / panSany;
    return ortasha;
}

string dengei (double ortasha) {
    if (ortasha >= 90) {
        return "Үздік";
    }
    if (ortasha >= 70) {
        return "Жақсы";
    }
    if (ortasha >= 50) {
        return "Қанағаттанарлық";
    }
    else  {
        return "Үлгерімі төмен";
}
 
} 
void birStudKorsetu(int index) {
    cout << endl;
    cout << "ID: " << studentter[index].id
         << " | " << studentter[index].aty_zhoni
         << " | Тобы: " << studentter[index].toby << endl;

    int panSany = studentter[index].pander.size();
    for (int i = 0; i < panSany; i++) {
        cout << i + 1 << ". " << studentter[index].pander[i].aty
             << ": " << studentter[index].pander[i].baga << endl;
    }

    double ortasha = ortashaBaga(index);
    cout << "Орташа балл: " << ortasha << " | " << dengei (ortasha) << endl;
}

void studKorsetu() {
    int n = studentter.size();
    if (n == 0) {
        cout << "Тізім бос." << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        birStudKorsetu(i);
    }
}

void studKosu() {
    int n = studentter.size();
 
    int id = sanOku("ID: ", 1, MAX_ID);
    int barMa = studTabu(id);
    if (barMa >= 0) {
        cout << "Бұл ID бұрын тіркелген." << endl;
        return;
    }

    Student zhanaStud;
    zhanaStud.id = id;
    zhanaStud.aty_zhoni = matinOku("Аты-жөні: ");
    zhanaStud.toby = matinOku("Тобы: ");
    int panSany = sanOku("Пән саны (1-50): ", 1, MAX_PAN);

    for (int i = 0; i < panSany; i++) {
        cout << i + 1 << "-пән:" << endl;
        Pan pan;
        pan.aty = matinOku("Пән атауы: ");
        pan.baga = sanOku("Бағасы (0-100): ", 0, 100);
        zhanaStud.pander.push_back(pan);
    }

    studentter.push_back(zhanaStud);
    cout << "Студент қосылды." << endl;
}

void studIzdeu() {
    int id = sanOku("Ізделетін ID: ", 1, MAX_ID);
    int index = studTabu(id);

    if (index == -1) {
        cout << "Студент табылмады." << endl;
    } else {
        birStudKorsetu(index);
    }
}

void uzdikTomenKorsetu() {
    int tandau = sanOku("1 - үздік, 2 - үлгерімі төмен: ", 1, 2);
    bool tabyldy = false;
    int n = studentter.size();

    for (int i = 0; i < n; i++) {
        double ortasha = ortashaBaga(i);
        if (tandau == 1 && ortasha >= 90) {
            birStudKorsetu(i);
            tabyldy = true;
        }
        if (tandau == 2 && ortasha < 50) {
            birStudKorsetu(i);
            tabyldy = true;
        }
    }

    if (tabyldy == false) {
        cout << "Бұл санатта студент жоқ." << endl;
    }
}

void studOzgertu() {
    int id = sanOku("Өзгертілетін ID: ", 1, MAX_ID);
    int index = studTabu(id);

    if (index == -1) {
        cout << "Студент табылмады." << endl;
        return;
    }

    int tandau = sanOku("1 - аты-жөні, 2 - тобы, 3 - бағасы: ", 1, 3);

    if (tandau == 1) {
        studentter[index].aty_zhoni = matinOku("Жаңа аты-жөні: ");
    } else if (tandau == 2) {
        studentter[index].toby = matinOku("Жаңа тобы: ");
    } else {
        birStudKorsetu(index);
        int panSany = studentter[index].pander.size();
        int nomir = sanOku("Пәннің реттік нөмірі: ", 1, panSany);
        studentter[index].pander[nomir - 1].baga = sanOku("Жаңа баға (0-100): ", 0, 100);
    }

    cout << "Мәлімет өзгертілді." << endl;
}

void studelete() {
    int id = sanOku("Өшірілетін ID: ", 1, MAX_ID);
    int index = studTabu(id);

    if (index == -1) {
        cout << "Студент табылмады." << endl;
        return;
    }

    birStudKorsetu(index);
    int rastau = sanOku("Өшіру: 1 - иә, 0 - жоқ: ", 0, 1);

    if (rastau == 1) {
        studentter.erase(studentter.begin() + index);
        cout << "Студент өшірілді." << endl;
    } else {
        cout << "Өшіру тоқтатылды." << endl;
    }
}

void esepKorsetu() {
    int n = studentter.size();
    if (n == 0) {
        cout << "Студент саны: 0. Орташа үлгерім анықталмаған." << endl;
        cout << "Үздік: 0" << endl;
        cout << "Үлгерімі төмен: 0" << endl;
        return;
    }

    double kosyndy = 0;
    int uzdik = 0;
    int tomen = 0;

    for (int i = 0; i < n; i++) {
        double ortasha = ortashaBaga(i);
        kosyndy += ortasha;
        if (ortasha >= 90) {
            uzdik++;
        }
        if (ortasha < 50) {
            tomen++;
        }
    }

    cout << "Студент саны: " << n << endl;
    cout << "Жалпы орташа: " << kosyndy / n << endl;
    cout << "Үздік: " << uzdik << endl;
    cout << "Үлгерімі төмен: " << tomen << endl;
}

void failgaSaktau() {
    ofstream fout(FAIL_ATY);
    if (fout.is_open() == false) {
        cout << "Сақтау қатесі." << endl;
        return;
    }

    int n = studentter.size();
    fout << n << endl;

    for (int i = 0; i < n; i++) {
        fout << studentter[i].id << endl;
        fout << studentter[i].aty_zhoni << endl;
        fout << studentter[i].toby << endl;

        int panSany = studentter[i].pander.size();
        fout << panSany << endl;

        for (int j = 0; j < panSany; j++) {
            fout << studentter[i].pander[j].aty << endl;
            fout << studentter[i].pander[j].baga << endl;
        }
    }

    fout.close();
    cout << "Сақталды." << endl;
}

void faildanOku() {
    ifstream fin(FAIL_ATY);
    if (fin.is_open() == false) {
        return;
    }

    int studSany;
    fin >> studSany;
    fin.ignore();

    for (int i = 0; i < studSany; i++) {
        Student stud;
        fin >> stud.id;
        fin.ignore();

        getline(fin, stud.aty_zhoni);
        getline(fin, stud.toby);

        int panSany;
        fin >> panSany;
        fin.ignore();

        for (int j = 0; j < panSany; j++) {
            Pan pan;
            getline(fin, pan.aty);
            fin >> pan.baga;
            fin.ignore();
            stud.pander.push_back(pan);
        }

        studentter.push_back(stud);
    }

    fin.close();
    cout << "Файлдан оқылды: " << studentter.size() << " студент." << endl;
}

void menuKorsetu() {
    cout << endl;
    cout << "===== СТУДЕНТТЕР ҮЛГЕРІМІ =====" << endl;
    cout << "1. Студент қосу" << endl;
    cout << "2. Тізім және орташа балдар" << endl;
    cout << "3. Үздік / үлгерімі төмен студенттер" << endl;
    cout << "4. ID бойынша іздеу" << endl;
    cout << "5. Мәлімет өзгерту" << endl;
    cout << "6. Студентті өшіру" << endl;
    cout << "7. Үлгерім туралы есеп" << endl;
    cout << "8. Файлға сақтау" << endl;
    cout << "9 . Сақтап шығу" << endl;
}

int main() {
    faildanOku();

    while (true) {
        menuKorsetu();
        int tandau = sanOku("Таңдау: ", 0, 9);

   switch (tandau) {
    case 1 :
    studKosu();
    break; 
     case 2 :
    studKorsetu();
    break; 
     case 3 :
    uzdikTomenKorsetu();
    break; 
     case 4 :
    studIzdeu();
    break; 
     case 5 :
    studOzgertu();
    break; 
     case 6 :
    studelete();
    break; 
     case 7:
    esepKorsetu();
    break; 
     case 8 :
    failgaSaktau();
    break; 
   }
        
    }

    return 0;

}
