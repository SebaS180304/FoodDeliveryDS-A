// Inclusión de bibliotecas necesarias
#include "Pedidos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

// Definición de la clase Node para la lista doblemente enlazada circular
template <class T>
class Node
{
public:
    T value;
    Node<T> *prev;
    Node<T> *next;

    // Constructor que inicializa el nodo con un valor
    Node(T value)
    {
        this->value = value;
        this->prev = NULL;
        this->next = NULL;
    }
};

// Definición de la clase List para manejar la lista doblemente enlazada circular
template <class T>
class List
{
    Node<T> *first;
    Node<T> *last;
    int size;

public:
    // Constructor que inicializa una lista vacía
    List()
    {
        this->first = NULL;
        this->last = NULL;
        this->size = 0;
    }

    // Métodos para manipular la lista
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

// Método para mostrar los primeros 'max' elementos de la lista
// Complejidad de tiempo: O(n), donde n es el número de elementos a mostrar
// Complejidad de espacio: O(1)
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
    cout << endl
         << endl;
}

// Métodos para obtener el primer y último nodo de la lista
// Complejidad de tiempo: O(1)
// Complejidad de espacio: O(1)
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

// Método para eliminar el primer elemento de la lista
// Complejidad de tiempo: O(1)
// Complejidad de espacio: O(1)
template <class T>
void List<T>::deleteFirst()
{
    if (size == 0)
        return;

    Node<T> *aux = first;

    if (size == 1)
    {
        first = last = NULL;
    }
    else
    {
        Node<T> *second = first->next;
        second->prev = last;
        last->next = second;
        first = second;
    }

    delete aux;
    size--;
}

// Método para insertar un elemento al inicio de la lista
// Complejidad de tiempo: O(1)
// Complejidad de espacio: O(1)
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

// Método para insertar un elemento al final de la lista
// Complejidad de tiempo: O(1)
// Complejidad de espacio: O(1)
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

// Método para mostrar la lista en orden
// Complejidad de tiempo: O(n), donde n es el número de elementos en la lista
// Complejidad de espacio: O(1)
template <class T>
void List<T>::showList()
{
    if (size == 0)
    {
        cout << "La lista está vacía" << endl;
        return;
    }

    Node<T> *aux = first;
    int i = 0;

    cout << "Size: " << size << endl;

    do
    {
        cout << aux->value << "\t";
        aux = aux->next;
        i++;
    } while (i < size && aux != first);

    cout << endl
         << endl;
}

// Método para mostrar la lista en orden inverso
// Complejidad de tiempo: O(n), donde n es el número de elementos en la lista
// Complejidad de espacio: O(1)
template <class T>
void List<T>::showListReverse()
{
    if (size == 0)
    {
        cout << "La lista está vacía" << endl;
        return;
    }

    Node<T> *aux = last;
    int i = 0;

    cout << "Reverse. Size: " << size << endl;

    do
    {
        cout << aux->value << "\t";
        aux = aux->prev;
        i++;
    } while (i < size && aux != last);

    cout << endl
         << endl;
}

// Definición de la clase Stack que utiliza la lista doblemente enlazada
template <class T>
class Stack
{
public:
    List<T> lista;

    Stack() {}

    void show();
    bool isEmpty();
    void push(T);
    T pop();
};

// Métodos de la clase Stack
template <class T>
void Stack<T>::show()
{
    this->lista.showList();
}

template <class T>
bool Stack<T>::isEmpty()
{
    return lista.getSize() == 0;
}

template <class T>
void Stack<T>::push(T item)
{
    this->lista.insertFirst(item);
}

template <class T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        throw std::out_of_range("Stack is empty");
    }
    T topValue = lista.getFirst()->value;
    lista.deleteFirst();
    return topValue;
}

// Función de partición para QuickSort
// Complejidad de tiempo: O(n), donde n es el número de elementos entre L y R
// Complejidad de espacio: O(1)
template <class T>
Node<T> *partition(List<T> &datos, Node<T> *L, Node<T> *R)
{
    Node<T> *j = L;
    Node<T> *i = L->prev;
    Node<T> *pivot = R;

    while (j != R)
    {
        if (j->value < pivot->value)
        {
            i = (i == NULL) ? L : i->next;
            T temp = i->value;
            i->value = j->value;
            j->value = temp;
        }
        j = j->next;
    }

    i = (i == NULL) ? L : i->next;
    T temp = i->value;
    i->value = pivot->value;
    pivot->value = temp;

    return i;
}

// Implementación de QuickSort
// Complejidad de tiempo: O(n log n) en promedio, O(n^2) en el peor caso
// Complejidad de espacio: O(log n) debido a la pila de recursión
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

// Función para contar el número de órdenes en el archivo
// Complejidad de tiempo: O(n), donde n es el número de líneas en el archivo
// Complejidad de espacio: O(1)
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
    while (getline(dbo, sline))
    {
        i++;
    }

    dbo.close();
    return i;
}

// Función para convertir el nombre del mes a su número correspondiente
// Complejidad de tiempo: O(1)
// Complejidad de espacio: O(1)
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
    return -1;
}

// Función para leer los pedidos del archivo y almacenarlos en la lista
// Complejidad de tiempo: O(n), donde n es el número de líneas en el archivo
// Complejidad de espacio: O(n), donde n es el número de pedidos leídos
void leePedidos(List<Pedidos> &pedidos, int ordenes)
{
    ifstream dbo;
    int mes, dia, hr, min, seg, i;
    string n, o, sline;

    dbo.open("orders.txt", ios::in);
    if (dbo.fail())
    {
        cout << "El archivo no pudo ser abierto... Cerrando programa" << endl;
        exit(1);
    }

    while (getline(dbo, sline) && pedidos.getSize() < ordenes)
    {
        string line = sline;

        // Extracción de datos de cada línea
        i = line.find(" ");
        string mesStr = line.substr(0, i);
        mes = obtenerMes(mesStr);

        line = line.substr(i + 1);
        i = line.find(" ");
        dia = stoi(line.substr(0, i));

        line = line.substr(i + 1);
        i = line.find(" ");
        string hora = line.substr(0, i);
        sscanf(hora.c_str(), "%d:%d:%d", &hr, &min, &seg);

        line = line.substr(i + 1);
        i = line.find("R:");
        line = line.substr(i + 2);

        i = line.find("O:");
        string nombre = line.substr(0, i - 1);

        string orden = line.substr(i + 2);

        // Creación y adición del nuevo pedido a la lista
        Pedidos nuevoPedido(mes, dia, hr, min, seg, nombre, orden);
        pedidos.insertLast(nuevoPedido);
    }
    dbo.close();
}

// Función para buscar pedidos por nombre de restaurante
// Complejidad de tiempo: O(n), donde n es el número de pedidos en la lista
// Complejidad de espacio: O(m), donde m es el número de pedidos encontrados
void buscarPorRestaurante(List<Pedidos> &pedidos)
{
    string nombreBuscado;
    cout << "Ingrese el nombre del restaurante a buscar: ";
    getline(cin, nombreBuscado);

    List<Pedidos> resultados;
    Node<Pedidos> *actual = pedidos.getFirst();
    int contador = 0;

    do
    {
        if (actual->value.getNombre() == nombreBuscado)
        {
            resultados.insertLast(actual->value);
            contador++;
        }
        actual = actual->next;
    } while (actual != pedidos.getFirst());

    if (contador > 0)
    {
        cout << "Se encontraron " << contador << " registros para el restaurante " << nombreBuscado << " :" << endl;
        quickSort(resultados);
        resultados.showList2(contador);
    }
    else
    {
        cout << "No se encontraron registros para el restaurante " << nombreBuscado << "." << endl;
    }
}

// Función para guardar los pedidos ordenados en un archivo
// Complejidad de tiempo: O(n), donde n es el número de pedidos en la lista
// Complejidad de espacio: O(1)
void guardarPedidosOrdenados(List<Pedidos> &pedidos, string &nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    Node<Pedidos> *actual = pedidos.getFirst();
    do
    {
        archivo << actual->value.getMesStr() << " "
                << actual->value.getDia() << " "
                << actual->value.getHr() << ":" << actual->value.getMin() << ":" << actual->value.getSeg() << " "
                << "R:" << actual->value.getNombre() << " "
                << "O:" << actual->value.getOrden() << endl;
        actual = actual->next;
    } while (actual != pedidos.getFirst());

    archivo.close();
    cout << "Pedidos ordenados guardados en " << nombreArchivo << endl;
}

// Función principal
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

    buscarPorRestaurante(pedidos);

    string nombreArchivo = "orden(ados).txt";
    guardarPedidosOrdenados(pedidos, nombreArchivo);

    return 0;
}