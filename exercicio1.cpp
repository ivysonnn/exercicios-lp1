#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14;

class Area {
    public:        
        // Cubo
        double area(double edge) {
            return 6 * pow(edge, 2);
        } 

        // Esfera
        double area(int radius) {
            return 4 * PI * pow(radius, 2);
        }

        // Pirâmide
        double area(double baseArea, double sideArea) {
            return  baseArea + sideArea;
        }

        // Paralelepípedo
        double area(double edge1, double edge2, double edge3) {
            double a1 = 2 * edge1 * edge2;
            double a2 = 2 * edge1 * edge3;
            double a3 = 2 * edge2 * edge3;

            return a1 + a2 + a3;
        } 
};

class Volume {
    public:        
        // Cubo
        double volume(double edge) {
            return pow(edge, 3);
        } 

        // Esfera
        double volume(int radius) {
            return (4.0 / 3.0) * PI * pow(radius, 3);
        }

        // Pirâmide
        double volume(double baseArea, double sideArea) {
            return (1.0 / 3.0) * baseArea * sideArea;
        }

        // Paralelepípedo
        double volume(double edge1, double edge2, double edge3) {
            return edge1 * edge2 * edge3;
        } 
};

int main() {
    Volume *volume = new Volume();
    Area *area = new Area();

    cout << "Volume Cubo..........: " << volume->volume(3.5) << endl; 
    cout << "Volume Esfera........: " << volume->volume(5) << endl;
    cout << "Volume Pirâmide......: " << volume->volume(3.0, 5.0) << endl;
    cout << "Volume Paralelepípedo: " << volume->volume(2.0, 4.0, 6.0) << endl;
    cout << endl;
    cout << "Area Cubo..........: " << area->area(8.2) << endl; 
    cout << "Area Esfera........: " << area->area(15) << endl;
    cout << "Area Pirâmide......: " << area->area(4, 8.0) << endl;
    cout << "Area Paralelepípedo: " << area->area(5.0, 6.0, 7.0) << endl;
}