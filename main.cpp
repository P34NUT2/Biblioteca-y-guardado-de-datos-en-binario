#include "Encabezado.h" 
#include <iostream>
#include <fstream>
#include <sstream>

//funcion global id;
int id = 1;

////declaracion de funciones
std::vector<Book> cargarDatos(const std::string& ruta_archivo);
void guardarLibrosEnBinario(const std::vector<Book>& books, const std::string& archivoBinario);
std::vector<Book> cargarLibrosDesdeBinario(const std::string& archivoBinario);
bool buscarLibroPorID(int idBuscado, const std::string& archivoBinario);
int encontrarEstudiante(std::vector<Student>& students); 

int main() 
{
    /////////////////////////////////////////////////////////////////////
    //creacion del .txt para binario OJO solo se usa la primera vez al ejecutar el codigo
    ///*std::ofstream archivo("libreria.txt", std::ios::binary);

    //if (!archivo)
    //{
    //    std::cerr << "el archivo no se pouede abrir";
    //    std::exit(1);
    //}*/
    //
    //creacion del archivo .dat al igual que la anterior solo se debe correr una vez
    ///*std::ofstream binario("libreria.dat", std::ios::binary);

    //if (!binario)
    //{
    //    std::cerr << "el archivo no se pouede abrir";
    //    std::exit(1);
    //}*/
    //
    /////////////////////////////////////////////////////////////////////

	std::string ruta_csv = "C:\\Users\\josev\\Desktop\\Escritorio\\Escuela\\4to semestre\\Estrucura de datos\\Mis codigos\\best-selling-books.csv";
	//creamos un vector tipo clase books para tener los libros
    std::vector<Book> books = cargarDatos(ruta_csv);
    //creamos otro vector ahora clase student para la insercion y manipulacion de los miembros mas facil
    std::vector<Student> students;
    
    //creacion de 10 estudiantes que pide el proeycto
    students.emplace_back("Ana Lu ;)", 2454);
    students.emplace_back("Caro ;)", 1789); 
    students.emplace_back("Carlos", 3456); 
    students.emplace_back("Marta", 2345); 
    students.emplace_back("Javier", 4567); 
    students.emplace_back("Elena", 8901); 
    students.emplace_back("Miguel", 5678); 
    students.emplace_back("Sofia", 6789); 
    students.emplace_back("Andres", 1234); 
    students.emplace_back("Valeria", 3450); 

    //txt que hice para ver que esta pasando y comos e escribe en binario
    std::string ruta_txt = "libreria.txt";
    std::string ruta_dat = "libreria.dat";


    //funcion para guardar los libros en binario
    //guardarLibrosEnBinario(books, ruta_txt); /// esta solo se ejecuta igual una vez solo para ver en el txt como se guarda en binario
    //ademas de que se usa para modifcar guarad los bytes en el archivo
    
    //para que la memoria binaria se quede como este  
    guardarLibrosEnBinario(books, ruta_dat);//pruebas lo comento por un momento 
    std::vector<Book> libros_bin = cargarLibrosDesdeBinario(ruta_dat);
    

    std::cout << "El tamno del libro en bytres es: " << sizeof(books[1]) << std::endl;

    ////////////////////////////////////////////////////
    ///menu dell programa
    int opcion = 0;
    do {
        std::cout << std::endl;
        std::cout << std::endl << "------ Menu------ " << std::endl;
        std::cout << "1. Agregar estudiante" << std::endl;
        std::cout << "2. Solicitar prestamo" << std::endl;
        std::cout << "3. Devolver prestamo" << std::endl;
        std::cout << "4. Reporte de libros no disponibles" << std::endl;
        std::cout << "5. Reporte de estudiantes con prestamos" << std::endl;
        std::cout << "6. Reporte de estudiantes sin prestamos" << std::endl;
        std::cout << "7. Mostrar todos los estudiantes" << std::endl;
        std::cout << "8. Mostrar todos los libros" << std::endl;
        std::cout << "9. Mostrar y buscar libros por ID" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;
        std::cout << "---------------------------" << std::endl;
        std::cout << std::endl;

        switch (opcion) {
        case 1: 
        {
            std::cout << "Opcion 1: Agregar estudiante" << std::endl;

            std::string nombre;
            int matricula;

            std::cout << "Nombre del estduainte: "; 
            std::cin >> nombre; 
            std::cout << std::endl << "Matricula(solo numeros): "; 
            std::cin >> matricula;

            //agregamos los nuevos datos a la clase
            students.emplace_back(nombre, matricula);

            break;
        }

        case 2: 
        {
            std::cout << "Opcion 2: Solicitar prestamo" << std::endl;
            int index = encontrarEstudiante(students);
            if (index != -1)
            {
                int book_id;
                std::cout << "Que libro quiere solicitar seleccione el ID: ";
                std::cin >> book_id;
                students[index].solicitarPrestamo(ruta_dat, book_id);
            }
            else
            {
                std::cout << "Vuelva a intentar" << std::endl;
            }

            break; 
        }
            
        case 3: 
        {
            std::cout << "Opcion 3: Devolver prestamo" << std::endl;
            int index = encontrarEstudiante(students);
            if (index != -1)
            {
                int book_id;
                students[index].mostrarPrestamos();
                std::cout << "Que libro quieres devolver seleccione el ID: ";
                std::cin >> book_id;
                students[index].devolverPrestamo(ruta_dat, book_id);
            }
            else
            {
                std::cout << "Vuelva a intentar" << std::endl;
            }
            break;
        }

        case 4: 
        {
            std::cout << "Opcion 4: Reporte de libros no disponibles" << std::endl;
            //vector para la info de los libros en binario aca lo uso para refrescar la memoria
            std::vector<Book> libros_bin = cargarLibrosDesdeBinario(ruta_dat);
            bool condicion = false;
            std::cout << "Los libros no disponibles son:" << std::endl;
            for (auto& libro : libros_bin)
            {
                if (libro.disponible() == false)
                {
                    libro.mostrarInfo();
                    condicion = true;
                }
            }

            if (condicion == false)
            {
                std::cout << "Todos los libros estan disponibles" << std::endl;
            }

            break;
        }
            

        case 5: 
        {
            std::cout << "Opcion 5: Reporte de estudiantes con prestamos" << std::endl << std::endl;
            bool condicion = false;
            for (auto& student : students)
            {
                if (student.getCantidadPrestados() > 0)
                {
                    std::cout << "%%%%%%%%%%%%%%%%%%%%% Estudiante %%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
                    student.mostrarDatos();
                    student.mostrarPrestamos();
                    std::cout << std::endl;
                    condicion = true;
                }
            }
            if (condicion == false)
            {
                std::cout << "No hay prestamos" << std::endl;
            }
            break;
        }
            
        case 6: 
        {
            std::cout << "Opcion 6: Reporte de estudiantes sin prestamos" << std::endl;
            for (auto& student : students)
            {
                if (student.getCantidadPrestados() == 0)
                {
                    std::cout << "%%%%%%%%%%%%%%%%%%%%% sin prestamos %%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
                    student.mostrarDatos();
                }
            }
            break;
        }
            
        case 7: 
        {
            std::cout << "Opcion 7: Mostrar todos los estudiantes" << std::endl;
            for (auto& student : students)
            {
                student.mostrarDatos();
            }

            std::cout << "Cantidad de estudiantes: " << students.size() << std::endl;
            break;

        }
            
        case 8: 
        {
            //vector para la info de los libros en binario
            std::vector<Book> libros_bin = cargarLibrosDesdeBinario(ruta_dat);

            for (auto& libro : libros_bin)
            {
                libro.mostrarInfo();
            }

            break;
        }
            
        case 9: 
        {
            std::cout << "Opcion 9: Mostrar y buscar libros por ID" << std::endl;
            int id_book;
            std::cout << "Que libro quieres consultar seleccione el ID: ";
            std::cin >> id_book;
            std::cout << std::endl;
            buscarLibroPorID(id_book, ruta_dat);
            break;
        }

        case 0:
            // Salir del programa
            std::cout << "Saliendo del programa..." << std::endl;
            break;

        default:
            std::cout << "Opcion invalida. Intenta de nuevo." << std::endl;
            break;
        }
    } while (opcion != 0);
   
	return 0;
}

/////////////////////////////////////funciones
//Esta funcion lee el CSV y mete los atributos a las clases Book
std::vector<Book> cargarDatos(const std::string& ruta_archivo) {
    std::vector<Book> books;
    std::ifstream archivo(ruta_archivo);
    std::string linea;
    char delimitador = ',';

    if (!archivo.is_open()) {
        std::cerr << "No se encontraron datos en el archivo o el archivo está vacío." << std::endl;
        return books;
    }

    std::getline(archivo, linea);  // Descarta la cabesera al simplemente leer primero la linea 
                                   //ya entra en el while con otra linea hasta repetir

    while (std::getline(archivo, linea)) {
        std::stringstream stream(linea);
        std::string titulo, autor, lenguaje, anio, ventas, genero;

        std::getline(stream, titulo, delimitador);
        std::getline(stream, autor, delimitador);
        std::getline(stream, lenguaje, delimitador);
        std::getline(stream, anio, delimitador);
        std::getline(stream, ventas, delimitador);
        std::getline(stream, genero, delimitador);

        //parcheamos y las casillas vacias le metemos na
        if (titulo.empty()) titulo = "N/A";
        if (autor.empty()) autor = "N/A";
        if (lenguaje.empty()) lenguaje = "N/A";
        if (anio.empty()) anio = "N/A";
        if (ventas.empty()) ventas = "0";
        if (genero.empty()) genero = "N/A";
        
        //con este metodo o funcion crea una nueva clase y en orden conforme a los datos que les vallamos pasando
        books.emplace_back(id, titulo, autor, lenguaje, anio, ventas, genero);
        id++;
    }

    archivo.close();
    return books;
}

/////funcion para guardar todos los libros en un archivo binario
void guardarLibrosEnBinario(const std::vector<Book>& books, const std::string& archivoBinario) 
{
    std::ofstream outFile(archivoBinario, std::ios::binary);

    if (!outFile.is_open()) {
        std::cerr << "Error al abrir el archivo binario para guardar los libros." << std::endl;
        return;
    }

    for (const auto& book : books) {
        book.escribirEnArchivoBinario(outFile);
    }

    outFile.close();
    std::cout << "Libros guardados exitosamente en el archivo binario." << std::endl;
} 

////////esta funcion lee los libros en archivo binario
//esta funcion sirve y no por que reinterpreta lso datos y los vuelve a meter en una calse book es decir crea nuevas 
// no es muy efeiciente pero lee el archivo binario
std::vector<Book> cargarLibrosDesdeBinario(const std::string& archivoBinario) 
{
    std::vector<Book> books;
    std::ifstream inFile(archivoBinario, std::ios::binary);

    if (!inFile.is_open()) {
        std::cerr << "Error al abrir el archivo binario para cargar los libros." << std::endl;
        return books;
    }

    Book libro;
    while (inFile.read(reinterpret_cast<char*>(&libro), sizeof(Book))) {
        books.push_back(libro);
    }

    inFile.close();
    return books;
}

///////buscar id en el archivo binario
bool buscarLibroPorID(int idBuscado, const std::string& archivoBinario) {
    std::ifstream inFile(archivoBinario, std::ios::binary);

    if (!inFile.is_open()) {
        std::cerr << "Error al abrir el archivo binario para buscar el libro." << std::endl;
        return false;
    }

    Book libro;
    int tamano_enbits = sizeof(Book);

    // Acceso aleatorio usando `seekg` se pone el menos 1 por que el incide real empieza de 0 y 
    // seekg actualiza el puntero donde se lee en bits se multiplica por que cada clase en este caso vale 128 bits y
    //cada vez que se avanza un obejto se multiplica para ir de 128 en 128 por la pocision y asi lo encuentra para no ir secuencialmente
    //formula inidice ID*tamanoen bits = posicion en bit cada que se multiplica la cuanto ocupa en posicion se mueve al byte 
    // y de ahi empieza la lectura
    std::streampos posición = (idBuscado - 1) * tamano_enbits;
    inFile.seekg(posición);

    if (inFile.read(reinterpret_cast<char*>(&libro), tamano_enbits)) {
        if (libro.getID() == idBuscado) {
            libro.mostrarInfo();
            return true;
        }
    }

    std::cerr << "Libro con ID " << idBuscado << " no encontrado." << std::endl;
    return false;
}

//para encontrar estudiantes
int encontrarEstudiante(std::vector<Student>& students) 
{
    int id_student = -1;
    std::cout << "Ingresa el ID o matricula del estudiante: ";
    std::cin >> id_student;

    for (int i = 0; i < students.size(); i++) {
        if (id_student == students[i].getMatricula()) {
            std::cout << "Estudiante encontrado" << std::endl;
            students[i].mostrarDatos();
            return i; // Retorna el índice del estudiante encontrado
        }
    }

    std::cout << "Estudiante no encontrado" << std::endl;
    return -1; // Retorna -1 si no encuentra al estudiante 
}