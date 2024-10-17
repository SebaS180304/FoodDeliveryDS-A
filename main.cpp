#include "Pedidos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

// class node: un valor y un puntero a otro nodo
template <class T>
class Node
{
public:
    //	valor almacenado
    T value; // <--- Nota que es de tipo T

    Node<T> *prev; //	dir del nodo anterior
    Node<T> *next; //	dir del nodo siguiente

    Node(T value)
    {
        this->value = value;
        this->prev = NULL;
        this->next = NULL;
    }
};

//  Clase lista enlazada simple:
//	puntero al primer nodo y tamaño total
template <class T>
class List
{
    Node<T> *first; // puntero al primer nodo
    Node<T> *last;  //	puntero al ultimo nodo
    int size;

public:
    List()
    {
        this->first = NULL;
        this->last = NULL;
        this->size = 0;
    }

    int getSize() { return size; }
    void showList();
    void showListReverse();

    void insertFirst(T);
    void insertLast(T);
    void deleteFirst();

    Node<T> *getFirst();
    Node<T> *getLast();

    void showList2(int);
};

template <class T>
void List<T>::showList2(int max)
{
    Node<T> *aux = first;
    int i = 0;
    cout << "Size: " << this->size << endl;
    while (i < max && aux != nullptr)
    {
        cout << "Nodo[" << i << "]:" << endl;
        aux->value.imprimePedido();
        aux = aux->next;
        i++;
    }
    cout << endl << endl;
}

template <class T>
Node<T> *List<T>::getFirst()
{
    return first;
}

template <class T>
Node<T> *List<T>::getLast()
{
    return last;
}

// inserta al inicio
template <class T>
void List<T>::deleteFirst()
{
    if (size == 0) return;
    
    Node<T> *aux = first;

    if (size == 1) {
        first = last = NULL;
    } else {
        Node<T> *second = first->next;
        second->prev = last;
        last->next = second;
        first = second;
    }

    delete aux;
    size--;
}

// inserta al inicio
template <class T>
void List<T>::insertFirst(T newValue)
{
    Node<T> *node = new Node<T>(newValue);

    if (size == 0)
    {
        first = last = node;
    }
    else
    {
        node->next = first;
        first->prev = node;
        first = node;
    }

    first->prev = last;
    last->next = first;
    size++;
}

// inserta al final
template <class T>
void List<T>::insertLast(T newValue)
{
    Node<T> *node = new Node<T>(newValue);

    if (size == 0)
    {
        first = last = node;
    }
    else
    {
        node->prev = last;
        last->next = node;
        last = node;
    }

    first->prev = last;
    last->next = first;
    size++;
}

template <class T>
void List<T>::showList()
{
    if (size == 0) {
        cout << "La lista está vacía" << endl;
        return;
    }

    Node<T> *aux = first;
    int i = 0;

    cout << "Size: " << size << endl;

    do {
        cout << aux->value << "\t";
        aux = aux->next;
        i++;
    } while (i < size && aux != first);

    cout << endl << endl;
}

template <class T>
void List<T>::showListReverse()
{
    if (size == 0) {
        cout << "La lista está vacía" << endl;
        return;
    }

    Node<T> *aux = last;
    int i = 0;

    cout << "Reverse. Size: " << size << endl;

    do {
        cout << aux->value << "\t";
        aux = aux->prev;
        i++;
    } while (i < size && aux != last);

    cout << endl << endl;
}

//	Una clase stack, con una lista enlazada doble dentro
template <class T>
class Stack
{
public:
    List<T> lista; // Tiene una lista dentro, que guarda cosas de tipo T

    Stack() {} // Un constructor que no hace nada

    void show();
    bool isEmpty();
    void push(T);
    T pop();
};

//	Mostrar es solo llamar a la funcion show de la lista
template <class T>
void Stack<T>::show()
{
    this->lista.showList();
}

//	isEmpty evalua si la lista tiene 0 elementos
template <class T>
bool Stack<T>::isEmpty()
{
    return lista.getSize() == 0;
}

// push: agrega un elemento en el top de la stack,
// aka, el inicio de la lista
template <class T>
void Stack<T>::push(T item)
{
    this->lista.insertFirst(item);
}

//	pop: consulta y guarda el primer elemento de la lista
//	elimina el top de la lista y devuelve el valor guardado
template <class T>
T Stack<T>::pop()
{
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    T topValue = lista.getFirst()->value;
    lista.deleteFirst();
    return topValue;
}

//	compara elementos en la particion de L a R
//	reorganizandolos de acuerdo a las comparaciones con pivot
//	pivot es el ultimo de la particion
template <class T>
Node<T> *partition(List<T> &datos, Node<T> *L, Node<T> *R)
{
    Node<T> *j = L;
    Node<T> *i = L->prev; // Inicializar i como el nodo anterior a L
    Node<T> *pivot = R;

    //	Compara con pivot e intercambios
    while (j != R)
    {
        if (j->value < pivot->value)
        {
            i = (i == NULL) ? L : i->next;
            // Intercambio manual sin usar swap
            T temp = i->value;
            i->value = j->value;
            j->value = temp;
        }
        j = j->next;
    }

    i = (i == NULL) ? L : i->next;
    // Intercambio manual sin usar swap
    T temp = i->value;
    i->value = pivot->value;
    pivot->value = temp;

    return i; //	Devuelve la direccion de donde quedo el valor pivote
}

//	quicksort
//	Reordena por particiones iterativamente
template <class T>
void quickSort(List<T> &datos)
{
    Stack<Node<T> *> stack;

    Node<T> *L = datos.getFirst();
    Node<T> *R = datos.getLast();
    Node<T> *pivot = NULL;

    stack.push(L);
    stack.push(R);

    while (!stack.isEmpty())
    {
        R = stack.pop();
        L = stack.pop();

        pivot = partition(datos, L, R);

        if (L != pivot && L != pivot->prev)
        {
            stack.push(L);
            stack.push(pivot->prev);
        }

        if (R != pivot && R != pivot->next)
        {
            stack.push(pivot->next);
            stack.push(R);
        }
    }
}

// Función para contar cuántas órdenes hay en el archivo
int numOrdenes()
{
    ifstream dbo("orders.txt");
    if (dbo.fail())
    {
        cout << "El archivo no pudo ser abierto... Cerrando programa" << endl;
        exit(1);
    }

    int i = 0;
    string sline;
    // Contar cuántas líneas hay en el archivo
    while (getline(dbo, sline))
    {
        i++;
    }

    dbo.close();
    return i;
}

// Función para obtener el número del mes
int obtenerMes(string mes)
{
    if (mes == "ene")
        return 1;
    else if (mes == "Feb")
        return 2;
    else if (mes == "Mar")
        return 3;
    else if (mes == "Abr")
        return 4;
    else if (mes == "May")
        return 5;
    else if (mes == "Jun")
        return 6;
    else if (mes == "Jul")
        return 7;
    else if (mes == "Ago")
        return 8;
    else if (mes == "Sep")
        return 9;
    else if (mes == "Oct")
        return 10;
    else if (mes == "Nov")
        return 11;
    else if (mes == "Dic")
        return 12;
    return -1; // Si no coincide ningún mes
}

// Función para guardar la información de los pedidos en la lista
void leePedidos(List<Pedidos> &pedidos, int ordenes)
{
    ifstream dbo;
    int mes, dia, hr, min, seg, i;
    string n, o, sline;

    // Verifica que el archivo se haya abierto correctamente
    dbo.open("orders.txt", ios::in);
    if (dbo.fail())
    {
        cout << "El archivo no pudo ser abierto... Cerrando programa" << endl;
        exit(1);
    }

    // Lee línea a línea
    while (getline(dbo, sline) && pedidos.getSize() < ordenes)
    {
        string line = sline;

        // Se obtiene el mes
        i = line.find(" ");
        string mesStr = line.substr(0, i);
        mes = obtenerMes(mesStr);

        // Obtiene el día
        line = line.substr(i + 1);
        i = line.find(" ");
        dia = stoi(line.substr(0, i));

        // Obtiene la hora
        line = line.substr(i + 1);
        i = line.find(" ");
        string hora = line.substr(0, i);
        sscanf(hora.c_str(), "%d:%d:%d", &hr, &min, &seg);

        // Obtiene el nombre (lo que sigue a "R:")
        line = line.substr(i + 1); // Saltar la hora
        i = line.find("R:");
        line = line.substr(i + 2); // Saltar "R:"

        i = line.find("O:");                   // Buscar "O:" para separar el nombre de la orden
        string nombre = line.substr(0, i - 1); // Eliminar el espacio adicional

        // Obtiene la orden (lo que sigue a "O:")
        string orden = line.substr(i + 2); // Saltar "O:"

        // Crear un objeto de la clase Pedidos con los datos obtenidos
        Pedidos nuevoPedido(mes, dia, hr, min, seg, nombre, orden);
        pedidos.insertLast(nuevoPedido);
    }
    dbo.close();
}

int main()
{
    int ordenes = numOrdenes();

    List<Pedidos> pedidos;
    cout << "Ordenes Registradas: " << ordenes << endl << endl;

    leePedidos(pedidos, ordenes);
    cout << "Lista original:" << endl;
    pedidos.showList2(10);

    quickSort(pedidos);
    
    cout << "Lista ordenada:" << endl;
    pedidos.showList2(10);

    return 0;
}