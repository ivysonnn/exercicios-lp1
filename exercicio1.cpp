#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14;

class FiguraEspacial{
    protected: 
        double length;
        double width;
        double height;

        bool checkValue(double value) {
            return value > 0;
        } ;
    public:
        FiguraEspacial(double l = 0, double w = 0, double h = 0) : length(l), width(w), height(h) {} 
        virtual double area() const = 0;
        virtual double volume() const = 0;
        virtual ~FiguraEspacial() = default;

};

class Piramide : public FiguraEspacial {
    public:
       Piramide(double l, double w, double h) : FiguraEspacial(l, w, h) {}
        double area() const override {
            // Área da base (quadrada)
            double areaBase = length * width;
            // Altura inclinada da pirâmide
            double alturaInclinada = sqrt(pow(height, 2) + pow(length / 2, 2));
            // Área lateral da pirâmide (quatro triângulos)
            double areaLateral = 2 * length * alturaInclinada + 2 * width * alturaInclinada;

            return areaBase + areaLateral;
        }

       double volume() const override {
        return (1.0/3.0) * length * width * height;
       }
};

class Cubo : public FiguraEspacial {
    public:
        Cubo(double edges) : FiguraEspacial(edges, edges, edges) {
            if(!checkValue(edges)) {
                throw invalid_argument("O valor deve ser maior que zero.");
            }
        }

        double area() const override {
            return 6 * pow(length, 2);
        }

        double volume() const override {
            return pow(length, 3);
        }
};

class Paralelepipedo : public FiguraEspacial {
    public:
        Paralelepipedo(double l, double w, double h) : FiguraEspacial(l, w, h) {
            if(!checkValue(l) || !checkValue(w) || !checkValue(h)) {
                throw invalid_argument("Os valores devem ser maiores que zero.");
            }
        }

        double area() const override {
            return (2 * length * width) + (2 * length * height) + (2 * width * height);
        }

        double volume() const override {
            return length * width * height;
        }
};

class Esfera : public FiguraEspacial {
    public: 
        Esfera(double r) : FiguraEspacial(r, 0, 0) {
            if(!checkValue(r)) {
                throw invalid_argument("Os valores devem ser maiores que zero.");
            }
        }

        double area() const override {
            return 4 * PI * pow(length, 2);
        }

        double volume() const override {
            return (4/3) * PI * pow(length, 3);
        }
};

int main() {
    try {
        FiguraEspacial* cubo = new Cubo(8.2);
        cout << "Volume Cubo..........: " << cubo->volume() << endl;
        FiguraEspacial* esfera = new Esfera(5);
        cout << "Volume Esfera........: " << esfera->volume() << endl;
        FiguraEspacial* piramide = new Piramide(3, 5, 7);
        cout << "Volume Pirâmide......: " << piramide->volume() << endl;
        FiguraEspacial* paralelepipedo = new Paralelepipedo(2, 4, 6);
        cout << "Volume Paralelepipedo: " << paralelepipedo->volume() << endl;
        cout << endl;

        cout << "Area Cubo..........: " << cubo->area() << endl; 
        cout << "Area Esfera........: " << esfera->area() << endl;
        cout << "Area Pirâmide......: " << piramide->area() << endl;
        cout << "Area Paralelepípedo: " << paralelepipedo->area() << endl;

        delete cubo;
        delete esfera;
        delete piramide;
        delete paralelepipedo;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}