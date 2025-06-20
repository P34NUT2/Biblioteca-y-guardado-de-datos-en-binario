#pragma once
#include <string>
#include <cstring>
#include <vector>
#include <tuple>

////////////////////////////////////////////////////////////////////////
//clase Book
class Book
{
public:
	//creo un constructor predeterminado para iniciar objetos con valores por defecto
	Book();

	//cosntructor por paramtros para crear obejtos con los atributos que yo quiera
	//se pasan los char por constante y apuntador por que un arreglo es un apuntador;
	Book(int ID, const std::string& _titulo, const std::string& _autor, const std::string& _lenguaje,
		const std::string& _anio, const std::string& _ventas, const std::string& _genero,
		int cantidad_disponible = 5);

	//metodos
	void mostrarInfo();
	void reducir_copias();
	void aumentar_copias();
	void escribirEnArchivoBinario(std::ofstream& outFile) const;
	void leerDesdeArchivoBinario(std::ifstream& inFile);
	bool disponible();
	//estos metodos son para accedeer a los atributos privados
	int getID() const;
	std::string  getTitulo();
	int getCantidad();


private:
	//metodos privados 
	//se usan los char como arreglos para poder medirlos y manejar la longuitud fija con arreglos binarios;
	//en este caso un promedio de 100bits

	int ID; //4
	char titulo[100];
	char autor[100];
	char lenguaje[50];
	char ventas[50];
	char genero[100];
	char anio[50];
	int cantidad_disponible;
};

////////////////////////////////////////////////////////////////////////////
/////clase student
class Student
{
public:
	//constructor clase student
	Student(const std::string& nombre, int matricula, int catidadPrestamos = 0);

	//atributo publico
	//este vector de tuplsa tendra dos cosas ID del libro y el titulo
	std::vector<std::tuple<int, std::string>> prestamos;
	int catidadPrestamos;

	//metodos
	void mostrarDatos(); 
	void solicitarPrestamo(const std::string& archivoBinario, int bookID);
	void devolverPrestamo(const std::string& archivoBinario, int bookID);
	void mostrarPrestamos();
	int getCantidadPrestados();
	//metodos para acceder a atributos privados
	int getMatricula();

private:
	std::string nombre;
	int matricula;
};