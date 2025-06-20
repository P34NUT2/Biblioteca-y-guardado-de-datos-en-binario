#include "Encabezado.h" 
#include <iostream>
#include <fstream>
#include <sstream>

///////////////////////////////////////////////////////////////////Book
//constructor predeterminado para inicliazar los parametros solo sirve para medir cuanto mide o cuesta en bytes
Book::Book() : ID(0), cantidad_disponible(0) {
    // Inicializar los atributos de tipo char[] usando strncpy_s
    strncpy_s(titulo, sizeof(titulo), "N/A", _TRUNCATE);
    strncpy_s(autor, sizeof(autor), "N/A", _TRUNCATE);
    strncpy_s(lenguaje, sizeof(lenguaje), "N/A", _TRUNCATE);
    strncpy_s(anio, sizeof(anio), "0", _TRUNCATE);
    strncpy_s(ventas, sizeof(ventas), "0.0", _TRUNCATE);
    strncpy_s(genero, sizeof(genero), "N/A", _TRUNCATE); 
}

//constructor de la clase book con parametroz
Book::Book(int ID, const std::string& _titulo, const std::string& _autor, const std::string& _lenguaje,
    const std::string& _anio, const std::string& _ventas, const std::string& _genero,
    int cantidad_disponible)
    : ID(ID), cantidad_disponible(cantidad_disponible) {

    strncpy_s(titulo, sizeof(titulo), _titulo.c_str(), _TRUNCATE);
    strncpy_s(autor, sizeof(autor), _autor.c_str(), _TRUNCATE);
    strncpy_s(lenguaje, sizeof(lenguaje), _lenguaje.c_str(), _TRUNCATE);
    strncpy_s(anio, sizeof(anio), _anio.c_str(), _TRUNCATE);
    strncpy_s(ventas, sizeof(ventas), _ventas.c_str(), _TRUNCATE);
    strncpy_s(genero, sizeof(genero), _genero.c_str(), _TRUNCATE);
}

void Book::mostrarInfo()
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "ID: " << this->ID << std::endl;
    std::cout << "Titulo: " << std::string(this->titulo) << std::endl;
    std::cout << "Autor: " << std::string(this->autor) << std::endl;
    std::cout << "Lenguaje: " << std::string(this->lenguaje) << std::endl;
    std::cout << "Anio de publicación: " << std::string(this->anio) << std::endl;
    std::cout << "Ventas: " << std::string(this->ventas) << " millones" << std::endl;
    std::cout << "Genero: " << std::string(this->genero) << std::endl;
    std::cout << "Copias disponibles: " << this->cantidad_disponible << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

void Book::escribirEnArchivoBinario(std::ofstream& outFile) const 
{
    outFile.write(reinterpret_cast<const char*>(this), sizeof(Book));
}

// Método para leer desde archivo binario
void Book::leerDesdeArchivoBinario(std::ifstream& inFile) 
{
    inFile.read(reinterpret_cast<char*>(this), sizeof(Book));
}

//como los atributos son privados necesitamos un metodo para acceder el valor por fuera
int Book::getID() const {return ID;}

std::string Book::getTitulo() {return this->titulo;}

int Book::getCantidad() {return this->cantidad_disponible;}

void Book::reducir_copias() 
{ 
    if (cantidad_disponible > 0) {
        cantidad_disponible--; // Reducir una copia solo si hay disponibles
    }
}

void Book::aumentar_copias() 
{ 
    if (cantidad_disponible < 5) {
        cantidad_disponible++; // Aumentar una copia solo si no excede el límite
    }
}

bool Book::disponible()
{
    if (this->cantidad_disponible == 0)
    {
        std::cout << "Libro no dsiponible" << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////////
//para calse student

//constructor
Student::Student(const std::string& nombre, int matricula, int catidadPrestamos) : nombre(nombre),
    matricula(matricula), catidadPrestamos(catidadPrestamos) {}

void Student::mostrarDatos() 
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Matricula: " << this->matricula << std::endl;
    std::cout << "Nombre: " << this->nombre << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

void Student::solicitarPrestamo(const std::string& archivoBinario, int bookID) {
    std::fstream file(archivoBinario, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo binario para solicitar prestamo." << std::endl;
        return;
    }

    // Acceso aleatorio usando `seekg` se pone el menos 1 por que el incide real empieza de 0 y 
    // seekg actualiza el puntero donde se lee en bits se multiplica por que cada clase en este caso vale 128 bits y
    //cada vez que se avanza un obejto se multiplica para ir de 128 en 128 por la pocision y asi lo encuentra para no ir secuencialmente
    //formula inidice ID*tamanoen bits = posicion en bit cada que se multiplica la cuanto ocupa en posicion se mueve al byte 
    // y de ahi empieza la lectura
    Book libro;
    int bytes_book = sizeof(Book);
    std::streampos posición = (bookID - 1) * bytes_book;

    // Mover el puntero al registro correspondiente
    file.seekg(posición);

    // Leer el libro desde el archivo
    if (!file.read(reinterpret_cast<char*>(&libro), bytes_book)) {
        std::cerr << "No se encontro el libro con ID " << bookID << "." << std::endl;
        return;
    }

    // Verificar disponibilidad del libro
    if (libro.getCantidad() <= 0) {
        std::cout << "El libro '" << libro.getTitulo() << "no esta disponible para prestamo." << std::endl;
        return;
    }

    // Reducir la cantidad disponible y registrar el préstamo
    libro.reducir_copias();
    //para la tupla se puede hacer con emplace_back pero asi lo veo mas claro
    prestamos.push_back(std::make_tuple(bookID, libro.getTitulo()));

    // Mover el puntero de escritura para actualizar el registro
    file.seekp(posición);
    file.write(reinterpret_cast<const char*>(&libro), bytes_book);

    std::cout << "Prestamo exitoso del libro: " << libro.getTitulo() << std::endl;
    
    

    file.close(); 
}

int Student::getMatricula() { return this->matricula; }

void Student::mostrarPrestamos() 
{
    if (!prestamos.empty()) {
        std::cout << "La cantidad de prestamos es: " << prestamos.size() << " y son los siguientes:" << std::endl;

        for (auto& prestamo : prestamos) {
            std::cout << "ID: " << std::get<0>(prestamo) << ", Libro: " << std::get<1>(prestamo) << std::endl;
        }
    }
    else {
        std::cout << "No hay prestamos registrados." << std::endl;
    }
    
}

int Student::getCantidadPrestados() { return prestamos.size(); }

void Student::devolverPrestamo(const std::string& archivoBinario, int bookID) {
    auto it = std::find_if(prestamos.begin(), prestamos.end(), [&](const std::tuple<int, std::string>& prestamo) {
        return std::get<0>(prestamo) == bookID;
        });

    if (it == prestamos.end()) {
        std::cout << "No se encontró un préstamo con el ID " << bookID << "." << std::endl;
        return;
    }

    std::fstream file(archivoBinario, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo binario para devolver el libro." << std::endl;
        return;
    }

    int bytes_book = sizeof(Book);
    std::streampos posición = (bookID - 1) * bytes_book;
    file.seekg(posición);

    Book libro;
    if (!file.read(reinterpret_cast<char*>(&libro), bytes_book)) {
        std::cerr << "No se pudo leer el libro con ID " << bookID << "." << std::endl;
        return;
    }

    libro.aumentar_copias();
    file.seekp(posición);
    file.write(reinterpret_cast<const char*>(&libro), bytes_book);

    // Guardar el título antes de eliminar el préstamo
    std::string tituloLibro = std::get<1>(*it);
    prestamos.erase(it);

    std::cout << "El libro '" << tituloLibro << "' ha sido devuelto exitosamente." << std::endl;

    file.close();
}