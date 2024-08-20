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

        //Definição das funções ponteiros
        typedef double (FiguraEspacial::*Area)() const;
        typedef double (FiguraEspacial::*Volume)() const;
 
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
            if(!checkValue(edges)) { //checa se a aresta do cubo é maior que zero
                throw invalid_argument("O valor da aresta deve ser maior que zero.");
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
            if(!checkValue(l) || !checkValue(w) || !checkValue(h)) { // checa se os parametros passados são maiores que zero
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
            if(!checkValue(r)) { //checa se o raio fornecido é maior que zero
                throw invalid_argument("O raio da esfera deve ser maior que zero.");
            }
        }

        double area() const override {
            return 4 * PI * pow(length, 2);
        }

        double volume() const override {
            return (4.0/3.0) * PI * pow(length, 3);
        }
};

int main() {
    try {
        //Criação das figuras
        FiguraEspacial* cubo = new Cubo(8.2);
        FiguraEspacial* esfera = new Esfera(5);
        FiguraEspacial* piramide = new Piramide(3, 5, 7);
        FiguraEspacial* paralelepipedo = new Paralelepipedo(2, 4, 6);

        //Criação das funções ponteiros
        FiguraEspacial::Area areaPtr = &FiguraEspacial::area;
        FiguraEspacial::Volume volumePtr = &FiguraEspacial::volume;

        cout << "Volume Cubo..........: " << (cubo->*volumePtr)() << endl;
        cout << "Volume Esfera........: " << (esfera->*volumePtr)() << endl;
        cout << "Volume Pirâmide......: " << (piramide->*volumePtr)() << endl;
        cout << "Volume Paralelepipedo: " << (paralelepipedo->*volumePtr)() << endl;
        cout << endl;

        cout << "Area Cubo..........: " << (cubo->*areaPtr)() << endl; 
        cout << "Area Esfera........: " << (esfera->*areaPtr)() << endl;
        cout << "Area Pirâmide......: " << (piramide->*areaPtr)() << endl;
        cout << "Area Paralelepípedo: " << (paralelepipedo->*areaPtr)() << endl;

        //Liberação de memória das figuras
        delete cubo;
        delete esfera;
        delete piramide;
        delete paralelepipedo;
    } catch (const invalid_argument& e) {
        cerr << "Erro: " << e.what() << endl;
    }

    return 0;
}