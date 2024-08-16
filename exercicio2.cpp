#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <iomanip>
#include <random>
#include <algorithm> 

using namespace std;

class Frog {
private:
    int id;
    int numberOfJumps;
    int totalNumberOfJumps;
    int numberOfTestsPlayed;
    int wins;
    int draws;
    int quantity;
    string name;
    double distanceTraveled;
    double maxJumpDistance; 

public:
    static double totalRaceDistance;

    Frog() : id(0), numberOfJumps(0), totalNumberOfJumps(0), numberOfTestsPlayed(0), wins(0), draws(0), quantity(0), name(""), distanceTraveled(0.0), maxJumpDistance(5.0) {}

    // Construtor parametrizado
    Frog(int id, int numberOfJumps, int totalNumberOfJumps, int numberOfTestsPlayed, int wins, int draws, int quantity, string name, double distanceTraveled, double maxJumpDistance)
        : id(id), numberOfJumps(numberOfJumps), totalNumberOfJumps(totalNumberOfJumps), numberOfTestsPlayed(numberOfTestsPlayed), wins(wins), draws(draws), quantity(quantity), name(name), distanceTraveled(distanceTraveled), maxJumpDistance(maxJumpDistance) {}

    int getId() const { return id; }
    int getNumberOfJumps() const { return numberOfJumps; }
    int getTotalNumberOfJumps() const { return totalNumberOfJumps; }
    int getNumberOfTestsPlayed() const { return numberOfTestsPlayed; }
    int getWins() const { return wins; }
    int getDraws() const { return draws; }
    int getQuantity() const { return quantity; }
    string getName() const { return name; }
    double getDistanceTraveled() const { return distanceTraveled; }
    double getMaxJumpDistance() const { return maxJumpDistance; }
    static double getTotalRaceDistance() { return totalRaceDistance; }

    void setId(int id) { this->id = id; }
    void setNumberOfJumps(int numberOfJumps) { this->numberOfJumps = numberOfJumps; }
    void setTotalNumberOfJumps(int totalNumberOfJumps) { this->totalNumberOfJumps = totalNumberOfJumps; }
    void setNumberOfTestsPlayed(int numberOfTestsPlayed) { this->numberOfTestsPlayed = numberOfTestsPlayed; }
    void setWins(int wins) { this->wins = wins; }
    void setDraws(int draws) { this->draws = draws; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setName(string name) { this->name = name; }
    void setDistanceTraveled(double distanceTraveled) { this->distanceTraveled = distanceTraveled; }
    void setMaxJumpDistance(double maxJumpDistance) { this->maxJumpDistance = maxJumpDistance; }
    static void setTotalRaceDistance(double distance) { totalRaceDistance = distance; }

    void jump() {
        random_device rd;  
        mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(1, maxJumpDistance);

        int jumpDistance = distr(gen);
        distanceTraveled += jumpDistance;
        
        numberOfJumps++;
    }
};

void printCentered(string text, int width) {
    int padLeft = (width - text.length()) / 2;
    int padRight = width - text.length() - padLeft;
    cout << setw(padLeft + text.length()) << setfill(' ') << right << text;
    cout << setw(padRight) << setfill(' ') << " ";
}

double Frog::totalRaceDistance = 250;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    vector<Frog*> positions;
    vector<Frog*> frogsInRace = {
        new Frog(1 , 0, 0, 2, 1, 0, 0, "Roberto"  , 0, 25),
        new Frog(2 , 0, 0, 0, 0, 0, 0, "Cleiton"  , 0, 25),
        new Frog(3 , 0, 0, 1, 0, 0, 0, "Cavalo"   , 0, 25),
        new Frog(4 , 0, 0, 2, 0, 1, 0, "Irineu"   , 0, 25),
        new Frog(5 , 0, 0, 7, 3, 4, 0, "Chaves"   , 0, 25),
        new Frog(6 , 0, 0, 3, 2, 0, 0, "Girafales", 0, 25),
        new Frog(7 , 0, 0, 9, 6, 1, 0, "Clotilde" , 0, 25),
        new Frog(8 , 0, 0, 5, 3, 2, 0, "Bruxa 71" , 0, 25),
        new Frog(9 , 0, 0, 8, 6, 0, 0, "Kiko"     , 0, 25),
        new Frog(10, 0, 0, 3, 1, 2, 0, "NhoNho"   , 0, 25)
    };

    while (positions.size() < frogsInRace.size()) {
        for (Frog* f : frogsInRace) {
            auto it = std::find(positions.begin(), positions.end(), f);
            if (it == positions.end()) { // Verifica se o sapo já terminou a corrida
                if (f->getDistanceTraveled() < Frog::totalRaceDistance) {
                    f->jump();
                    if (f->getDistanceTraveled() >= Frog::totalRaceDistance) {
                        if (positions.size() == 0) {
                            f->setWins(f->getWins() + 1);
                        }
                        positions.push_back(f);
                    }
                }
            }
        }
    }   

    cout << "Pos |";
    printCentered("Nome", 25); 
    cout << "|";
    printCentered("Total de Pulos", 25);  
    cout << endl;

    cout << "---------------------------------------------------" << endl;

    for (int i = 0; i < positions.size(); i++) {
        cout << setw(2) << setfill('0') << i + 1 << "° |";
        printCentered(positions[i]->getName(), 25);
        cout << "|";
        printCentered(to_string(positions[i]->getNumberOfJumps()), 25);
        cout << endl;
    }
    

    return 0;
}
