#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Advisory {
public:
    virtual void giveAdvice() = 0;
    virtual ~Advisory() {}
};

class Crop : public Advisory {
protected:
    string name;
    float area;
    string season;
    float yieldPerAcre;

    static int count;

public:
    Crop() {
        name = "";
        area = 0.0;
        season = "";
        yieldPerAcre = 0.0;
        count++;
    }

    Crop(string n, float a, string s, float y) {
        if (a < 0 || y < 0) {
            throw "Invalid input values!";
        }
        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;
        count++;
    }

    virtual ~Crop() {
        count--;
    }

    static void showCount() {
        cout << "\nTotal crops: " << count << endl;
    }

    virtual float calculateTotalYield() {
        return area * yieldPerAcre;
    }

    virtual void display() {
        cout << "\nCrop Name: " << name;
        cout << "\nArea: " << area << " acres";
        cout << "\nSeason: " << season;
        cout << "\nYield per acre: " << yieldPerAcre;
        cout << "\nTotal Yield: " << calculateTotalYield() << endl;
    }

    bool operator>(Crop &c) {
        return this->calculateTotalYield() > c.calculateTotalYield();
    }

    string getName() {
        return name;
    }
};

int Crop::count = 0;

class CerealCrop : public Crop {
    string fertilizerType;

public:
    CerealCrop() : Crop() {
        fertilizerType = "";
    }

    CerealCrop(string n, float a, string s, float y, string f) : Crop(n, a, s, y) {
        fertilizerType = f;
    }

    void display() {
        Crop::display();
        cout << "Fertilizer: " << fertilizerType << endl;
    }

    void giveAdvice() {
        cout << "Tip for " << name << ": Use nitrogen-rich fertilizer and water timely.\n";
    }

    void writeToFile(ofstream &fout) {
        fout << "Cereal " << name << " " << area << " " << season << " " << yieldPerAcre << " " << fertilizerType << "\n";
    }
};

class VegetableCrop : public Crop {
    string irrigationFreq;

public:
    VegetableCrop() : Crop() {
        irrigationFreq = "";
    }

    VegetableCrop(string n, float a, string s, float y, string ir) : Crop(n, a, s, y) {
        irrigationFreq = ir;
    }

    void display() {
        Crop::display();
        cout << "Irrigation: " << irrigationFreq << endl;
    }

    void giveAdvice() {
        cout << "Tip for " << name << ": Ensure regular drip irrigation and pest control.\n";
    }

    void writeToFile(ofstream &fout) {
        fout << "Vegetable " << name << " " << area << " " << season << " " << yieldPerAcre << " " << irrigationFreq << "\n";
    }
};

int main() {
    try {
        CerealCrop c1("Wheat", 10.0, "Rabi", 15.5, "Urea");
        VegetableCrop c2("Tomato", 3.0, "Kharif", 45.0, "Daily");

        Crop::showCount();

        Crop *ptr;

        ptr = &c1;
        ptr->display();
        ptr->giveAdvice();

        ptr = &c2;
        ptr->display();
        ptr->giveAdvice();

        if (c1 > c2) {
            cout << "\n" << c1.getName() << " has higher total yield than " << c2.getName() << endl;
        } else {
            cout << "\n" << c2.getName() << " has higher total yield than " << c1.getName() << endl;
        }

        ofstream fout("data.txt");
        if (fout.is_open()) {
            c1.writeToFile(fout);
            c2.writeToFile(fout);
            fout.close();
        }

        ifstream fin("data.txt");
        if (fin.is_open()) {
            string type, name, season, extra;
            float area, yieldVal;

            cout << "\n--- Data from file ---";
            while (fin >> type >> name >> area >> season >> yieldVal >> extra) {
                cout << "\n" << type << " | " << name << " | " << area << " | " << season << " | " << yieldVal << " | " << extra;
            }
            fin.close();
            cout << endl;
        }
    }
    catch (const char* msg) {
        cout << "\nError: " << msg << endl;
    }

    return 0;
}