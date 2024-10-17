#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <iostream>

using namespace std;

class Pedidos{
    private:
        int mes;
        int dia;
        int hr;
        int min;
        int seg;
        string nombre;
        string orden;

    protected:

    public:
        Pedidos();
        Pedidos(int mes, int dia, int hr, int min, int seg, string nombre, string orden);
        void setMes(int mes);
        void setDia(int dia);
        void setHr(int hr);
        void setMin(int min);
        void setSeg(int seg);
        void setNombre(string nombre);
        void setOrden(string orden);
        int getMes();
        int getDia();
        int getHr();
        int getMin();
        int getSeg();
        string getNombre();
        string getOrden();
        void imprimePedido();
        string getMesStr();
        int comparaFecha(Pedidos other);
        bool operator<(Pedidos other);
        virtual ~Pedidos();
};

#endif //PEDIDOS_H