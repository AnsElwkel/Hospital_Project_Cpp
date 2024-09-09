#include <iostream>

struct Patient {
    std::string name;
    bool status;
};

struct Menu {
    Menu() {
        fillMenu();
    }

    void fillMenu() {
        menuList[0] = "Add new patient",
                menuList[1] = "Print all patients",
                menuList[2] = "Get next patient",
                menuList[3] = "Exit";
    }

    void showMenu() {
        for (int i = 0; i < 4; i++)
            std::cout << i + 1 << ") " << menuList[i] << std::endl;
    }

private:
    std::string menuList[4];
};

bool validInput(int from, int to, int input) {
    if (from <= input && input <= to)
        return true;
    return false;
}

struct Hospital {
    Menu menu;

    int operations(int op) {
        if (op == 1) {
            std::string name;
            int spec;
            bool status;
            std::cout << "Enter specialization , name , status: ";
            std::cin >> spec >> name >> status;
            while (!validInput(1, 20, spec)) {
                std::cout << "Invalid specialization (choose specialization from 1 to 20): ";
                std::cin >> spec;
                std::cout << std::endl;
            }
            while (!validInput(0, 1, status)) {
                std::cout << "Invalid status (Enter 0 for regular or 1 for urgent): ";
                std::cin >> status;
                std::cout << std::endl;
            }

            if (!addNewPatient(name, status, spec))
                std::cout << "Sorry we can't add more patients for this specialization\n";
        } else if (op == 2) {
            printAllPatients();
        } else if (op == 3) {
            int spec;
            std::cout << "Enter specialization: ";
            std::cin >> spec;
            while (!validInput(1, 20, spec)) {
                std::cout << "Invalid specialization (choose specialization from 1 to 20) \n";
                std::cout << "Enter specialization: ";
                std::cin >> spec;
            }

            getNextPatient(spec);
        } else
            return -1;

        return 0;
    }

    bool addNewPatient(const std::string &_name, int _status, int spec) {
        --spec;
        if (lastIdx[spec] > 4)
            return false;
        if (_status == 0) {
            patientsInHospital[spec][lastIdx[spec]].name = _name;
            patientsInHospital[spec][lastIdx[spec]].status = _status;
            ++lastIdx[spec];
        } else {
            int put = 0;
            for (int i = lastIdx[spec]; !put and ~i; --i) {
                if (patientsInHospital[spec][i].status == 1) put = i + 1;
            }

            for (int i = lastIdx[spec] + 1; i > put; --i)
                patientsInHospital[spec][i] = patientsInHospital[spec][i - 1];
            patientsInHospital[spec][put].name = _name;
            patientsInHospital[spec][put].status = _status;
            ++lastIdx[spec];
        }
        return true;
    }

    void printAllPatients() const {
        std::cout << "*********************************************" << std::endl;
        for (int i = 0; i < 20; i++) {
            if (!lastIdx[i]) continue;

            std::cout << "There are " << lastIdx[i] << " patients in specialization \n";
            for (int j = 0; j < lastIdx[i]; j++)
                std::cout << patientsInHospital[i][j].name << ' ' << (patientsInHospital[i][j].status == 0
                                                                          ? "regular"
                                                                          : "urgent") << "\n";
        }
        std::cout << "\n\n";
    }

    void getNextPatient(int spec) {
        --spec;
        if (!lastIdx[spec])
            return std::cout << "No patients at the moment. Have rest, Dr \n", void();
        std::cout << patientsInHospital[spec][0].name << " please go with the Dr" << "\n";
        for (int i = 0; i < lastIdx[spec]; i++)
            patientsInHospital[spec][i] = patientsInHospital[spec][i + 1];
        --lastIdx[spec];
        std::cout << std::endl;
    }

private:
    Patient patientsInHospital[20][5]{};
    int lastIdx[20]{};
};

//To enter choice of operation
int enterChoice(Hospital &hospital) {
    int op = 1;
    std::cout << "Enter choice: \n";
    hospital.menu.showMenu();
    std::cin >> op;
    std::cout << std::endl;
    if (op == 4) return 0;
    while (!validInput(1, 4, op)) {
        std::cout << "Invalid choice \n";
        std::cout << "Enter choice: ";
        std::cin >> op;
        std::cout << std::endl;
    }
    return op;
}

int main() {
    Hospital hospital;
    while (true)
        hospital.operations(enterChoice(hospital));

    return 0;
}
