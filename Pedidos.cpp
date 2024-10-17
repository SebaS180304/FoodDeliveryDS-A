#include "Pedidos.h"

Pedidos::Pedidos(){
    mes = 0;
    dia = 0;
    hr = 0;
    min = 0;
    seg = 0;
    nombre = "";
    orden = "";
}

Pedidos::Pedidos(int mes, int dia, int hr, int min, int seg, string nombre, string orden){
    this-> mes = mes;
    this-> dia = dia;
    this-> hr = hr;
    this-> min = min;
    this-> seg = seg;
    this-> nombre = nombre;
    this-> orden = orden;
}

void Pedidos::setMes(int mes){
    this-> mes = mes;
}

void Pedidos::setDia(int dia){
    this-> dia = dia;
}

void Pedidos::setHr(int hr){
    this-> hr = hr;
}

void Pedidos::setMin(int min){
    this-> min = min;
}

void Pedidos::setSeg(int seg){
    this-> seg = seg;
}

void Pedidos::setNombre(string nombre){
    this-> nombre = nombre;
}

void Pedidos::setOrden(string orden){
    this-> orden = orden;
}

int Pedidos::getMes(){
    return mes;
}

int Pedidos::getDia(){
    return dia;
}

int Pedidos::getHr(){
    return hr;
}

int Pedidos::getMin(){
    return min;
}

int Pedidos::getSeg(){
    return seg;
}

string Pedidos::getNombre(){
    return nombre;
}

string Pedidos::getOrden(){
    return orden;
}

void Pedidos::imprimePedido(){
    cout << "Fecha de Pedido: " << dia << "/" << mes << " " << hr << ":" << min << ":" << seg << endl;
    cout << "Restaurante: " << nombre << endl;
    cout << "Orden: " << orden << endl;
}

string Pedidos::getMesStr(){
    if (mes == 1)
        return "ene";
    else if (mes == 2)
        return "Feb";
    else if (mes == 3)
        return "Mar";
    else if (mes == 4)
        return "Abr";
    else if (mes == 5)
        return "May";
    else if (mes == 6)
        return "Jun";
    else if (mes == 7)
        return "Jul";
    else if (mes == 8)
        return "Ago";
    else if (mes == 9)
        return "Sep";
    else if (mes == 10)
        return "Oct";
    else if (mes == 11)
        return "Nov";
    else if (mes == 12)
        return "Dic";
    return "";
}

int Pedidos::comparaFecha(Pedidos fecha){
    if (this->mes < fecha.mes)
        return -1;
    if (this->mes > fecha.mes)
        return 1;
    if (this->dia < fecha.dia)
        return -1;
    if (this->dia > fecha.dia)
        return 1;
    if (this->hr < fecha.hr)
        return -1;
    if (this->hr > fecha.hr)
        return 1;
    if (this->min < fecha.min)
        return -1;
    if (this->min > fecha.min)
        return 1;
    if (this->seg < fecha.seg)
        return -1;
    if (this->seg > fecha.seg)
        return 1;
    return 0; // Son iguales
}

bool Pedidos::operator<(Pedidos other){
    if (nombre != other.nombre)
        return nombre < other.nombre;
    if (mes != other.mes)
        return mes < other.mes;
    if (dia != other.dia)
        return dia < other.dia;
    if (hr != other.hr)
        return hr < other.hr;
    if (min != other.min)
        return min < other.min;
    return seg < other.seg;
}

    Pedidos::~Pedidos(){
    // Destructor
}