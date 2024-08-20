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
class Menu {
    public:
        int figureOption() {
            int option;
            cout << "           MENU          " << endl;
            cout << "=========================" << endl;
            cout << "1) Cubo" << endl;
            cout << "2) Esfera" << endl;
            cout << "3) Piramide" << endl;
            cout << "4) Paralelepipedo" << endl;
            cout << "Digite a opção desejada: ";
            cin >> option;
            return option;
        }

        FiguraEspacial* cubo() {
            double edges;
            cout << "Tamanho da aresta do cubo: ";
            cin >> edges;
            FiguraEspacial* cubo = new Cubo(edges);

            return cubo;
        }

        FiguraEspacial* esfera() {
            double raio;
            cout << "Tamanho do raio da esfera: ";
            cin >> raio;
            FiguraEspacial* esfera = new Esfera(raio);

            return esfera;
        }

        FiguraEspacial* piramide() {
            double length, width, height;
            cout << "Valores do tamanho, largura e altura(tamanho largura altura): ";
            cin >> length;
            cin >> width;
            cin >> height;
            FiguraEspacial* piramide = new Piramide(length, width, height);

            return piramide;
        }

        FiguraEspacial* paralelepipedo() {
            double length, width, height;
            cout << "Valores do tamanho, largura e altura(tamanho largura altura): ";
            cin >> length;
            cin >> width;
            cin >> height;
            FiguraEspacial* paralelepipedo = new Paralelepipedo(length, width, height);

            return paralelepipedo;
        }
};

int main() {
    Menu *menu = new Menu;
    FiguraEspacial* figura;
    
    //Criação das funções
    FiguraEspacial::Area areaPtr = &FiguraEspacial::area;
    FiguraEspacial::Volume volumePtr = &FiguraEspacial::volume;

    try {
        switch(menu->figureOption()) {
            case 1: 
                figura = menu->cubo();
                cout << "Volume Cubo..........: " << (figura->*volumePtr)() << endl;
                cout << "Area Cubo............: " << (figura->*areaPtr)() << endl; 
                break;
            case 2: 
                figura = menu->esfera();
                cout << "Volume Esfera........: " << (figura->*volumePtr)() << endl;
                cout << "Area Esfera..........: " << (figura->*areaPtr)() << endl; 
                break;
            case 3: 
                figura = menu->piramide();
                cout << "Volume Piramide......: " << (figura->*volumePtr)() << endl;
                cout << "Area Piramide........: " << (figura->*areaPtr)() << endl; 
                break;
            case 4: 
                figura = menu->paralelepipedo();
                cout << "Volume Paralelepipedo: " << (figura->*volumePtr)() << endl;
                cout << "Area Paralelepipedo..: " << (figura->*areaPtr)() << endl; 
                break;
            default: break;
        }
    } catch (invalid_argument& e) {
        cerr << "Erro: " << e.what() << endl;
    }

    delete figura;
    delete menu;

    return 0;
}