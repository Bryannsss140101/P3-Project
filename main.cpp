/*
#include <iostream>
#include <conio.h>
#include <unordered_map>
#include "src/main/trie/Trie.h"

#include "src/main/csv/Csv.h"
#include "src/main/dataframe/DataFrame.h"
#include "src/main/searcher/Searcher.h"
#include "src/main/suggestion-system/SuggestionSystem.h"

using namespace std;

int main() {
    Searcher searcher("mpst_full_data.csv");

    searcher.find("Scar");

    for (auto s = searcher.get_suggestions(); const auto &e: s) {
        cout << s << endl;
    }

    _getch();

    return 0;
}
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "json.hpp"


#include <typeinfo>

#include "src/main/searcher/Searcher.h"

using json = nlohmann::json;
using namespace std;


//Clase Usuario
class User {
private:
    string username;
    string password;
    string email;
    unordered_set<string> peliculasLike;
    unordered_set<string> verMasTarde;

public:
    User() {
    }

    User(string username, string password, string email) {
        this->username = username;
        this->password = password;
        this->email = email;
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getEmail() const { return email; }

    void addPeliculaLike(const string &pelicula) {
        peliculasLike.insert(pelicula);
    }

    void addVerMasTarde(const string &pelicula) {
        verMasTarde.insert(pelicula);
    }

    // Getters para los unordered_sets
    unordered_set<string> getPeliculasLike() const {
        return peliculasLike;
    }

    unordered_set<string> getVerMasTarde() const {
        return verMasTarde;
    }
};


unordered_map<string, User> UsersData;

//Genera la sesion actual, se basa en Singleton
class UserSession {
private:
    static UserSession *instance;
    static User *currentUser;

    UserSession() {
    }

public:
    static UserSession *getInstance() {
        if (instance == nullptr) {
            instance = new UserSession();
        }
        return instance;
    }

    void loginSesion(string email) {
        currentUser = &UsersData[email];
    }

    void logout() {
        currentUser = nullptr;
    }

    static User *getCurrentUser() {
        return currentUser;
    }
};

//Guardado y Cargado de Datos
//---------------------------------------------------------------------------------------------------------------------------------
// Función para cargar usuarios desde un archivo JSON
void loadUsersFromJSON(const string &filePath) {
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Advertencia: El archivo JSON no existe. Creando un archivo vacío..." << endl;

        // Crear un archivo JSON inicial vacío
        json emptyData = {{"users", json::array()}};
        ofstream outputFile(filePath);
        if (outputFile.is_open()) {
            outputFile << emptyData.dump(4); // Formateo con indentación
            outputFile.close();
            cerr << "Archivo JSON inicial creado en: " << filePath << endl;
        } else {
            cerr << "Error: No se pudo crear el archivo JSON." << endl;
            return;
        }
        return; // Terminar porque no hay datos para cargar
    }

    json jsonData;
    try {
        inputFile >> jsonData;
    } catch (const json::exception &e) {
        cerr << "Error: Problema al leer el archivo JSON: " << e.what() << endl;
        inputFile.close();
        return;
    }

    for (const auto &user: jsonData["users"]) {
        string username = user["username"];
        string password = user["password"];
        string email = user["email"];

        // Convertir los arrays JSON en unordered_sets
        unordered_set<string> peliculasLike(user["peliculasLike"].begin(), user["peliculasLike"].end());
        unordered_set<string> verMasTarde(user["verMasTarde"].begin(), user["verMasTarde"].end());

        // Crear el usuario con los nuevos atributos
        User newUser(username, password, email);

        // Agregar las películas al usuario
        for (const auto &pelicula: peliculasLike) {
            newUser.addPeliculaLike(pelicula);
        }
        for (const auto &pelicula: verMasTarde) {
            newUser.addVerMasTarde(pelicula);
        }

        UsersData[email] = newUser;
    }
    inputFile.close();
}

// Función para guardar usuarios en un archivo JSON
void saveUsersDataToJSON(const string &filePath) {
    json jsonData;

    for (const auto &[email, user]: UsersData) {
        json userJson = {
            {"username", user.getUsername()},
            {"password", user.getPassword()},
            {"email", email},
            {"peliculasLike", vector<string>(user.getPeliculasLike().begin(), user.getPeliculasLike().end())},
            {"verMasTarde", vector<string>(user.getVerMasTarde().begin(), user.getVerMasTarde().end())}
        };
        jsonData["users"].push_back(userJson);
    }

    ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo JSON para escritura." << endl;
        return;
    }

    outputFile << jsonData.dump(4); // Escribir el JSON con formato
    outputFile.close();
    // cout << "Datos de usuarios guardados en " << filePath << endl;
}

//Verifica que se agregue el nuevo usuario correctamente
bool registerUser(const string &username, const string &password, const string &email) {
    // Verificar si el email ya existe
    if (UsersData.find(email) != UsersData.end()) {
        cout << "Error: El email ya está registrado." << endl;
        return false;
    }

    // Crear un nuevo usuario y agregarlo al mapa
    UsersData[email] = User(username, password, email);
    cout << "Usuario agregado exitosamente." << endl;
    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------

//Inicio de Sesion y Creacion de Usuarios
//---------------------------------------------------------------------------------------------------------------------------------
//Funcion que verifica que lo datos de inicio sean correctos
bool verificarDatosUsuario(const string &email, const string &password) {
    if (UsersData[email].getPassword() == password) {
        return true;
    } else {
        cout << "Contrasena incorrecta." << endl;
        return false;
    }
}

// Función para verificar si el correo está registrado
bool verificarCorreoRegistrado(const string &email) {
    return UsersData.find(email) != UsersData.end();
}

// Función que maneja el proceso de inicio de sesión
bool ingresar(UserSession *actualSesion) {
    string password, email;

    // Intentos de ingreso
    int intentos = 0;
    while (intentos < 3) {
        // Permite hasta 3 intentos
        cout << "Ingresa el email: ";
        cin >> email;

        // Verificar si el correo ya está registrado
        if (!verificarCorreoRegistrado(email)) {
            cout << "El correo no está registrado." << endl;
            return false; // Si el correo no está registrado, no se puede continuar
        }

        cout << "Ingresa el password: ";
        cin >> password;

        // Verificar si los datos son correctos
        if (verificarDatosUsuario(email, password)) {
            cout << "Ingreso exitoso." << endl;
            actualSesion->loginSesion(email);
            return true; // Ingreso exitoso, se retorna true
        } else {
            cout << "Datos incorrectos." << endl;
            intentos++;
        }

        // Preguntar si desea intentar de nuevo después de un fallo
        if (intentos < 3) {
            char respuesta;
            cout << "¿Quieres intentar nuevamente? (s/n): ";
            cin >> respuesta;
            if (respuesta == 'n' || respuesta == 'N') {
                cout << "No se ha podido ingresar sesión. Saliendo..." << endl;
                return false; // Usuario no quiere intentar más
            }
        }
    }

    // Si llega a este punto, el usuario ha superado el límite de intentos
    cout << "Se han agotado los intentos." << endl;
    return false; // No se logró ingresar sesión después de 3 intentos
}

// Función para crear un nuevo usuario y los guarda en en JSON
void crearUsuario(const string &datapath) {
    string email, username, password;
    char opcion;

    while (true) {
        // Pedir el email, nombre de usuario y contraseña
        cout << "Ingresa tu email: ";
        cin >> email;

        // Verificar si el email ya está registrado
        if (UsersData.find(email) != UsersData.end()) {
            cout << "El email ya está registrado." << endl;
            cout << "¿Quieres intentar con otro email? (s/n): ";
            cin >> opcion;
            if (opcion == 'n' || opcion == 'N') {
                cout << "Operación cancelada." << endl;
                return; // Salir si el usuario no quiere continuar
            }
            continue; // Volver a pedir el email
        }

        cout << "Ingresa tu nombre de usuario: ";
        cin >> username;

        // Verificar si el nombre de usuario ya está tomado
        bool usernameExists = false;
        for (const auto &entry: UsersData) {
            if (entry.second.getUsername() == username) {
                cout << "El nombre de usuario ya está en uso." << endl;
                usernameExists = true;
                break;
            }
        }

        if (usernameExists) {
            cout << "¿Quieres intentar con otro nombre de usuario? (s/n): ";
            cin >> opcion;
            if (opcion == 'n' || opcion == 'N') {
                cout << "Operación cancelada." << endl;
                return; // Salir si el usuario no quiere continuar
            }
            continue; // Volver a pedir el nombre de usuario
        }

        cout << "Ingresa tu contraseña: ";
        cin >> password;

        // Crear un nuevo objeto User y agregarlo a la base de datos
        UsersData[email] = User(username, password, email);
        saveUsersDataToJSON(datapath);
        cout << "Usuario creado exitosamente." << endl;
        break; // Salir del bucle si el usuario se ha creado correctamente
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

//Clase Peliculas
class Pelicula {
private:
    string titulo; // Título de la película
    string sinopsis; // Sinopsis de la película
    unordered_set<string> tags; // Tags (etiquetas) asociadas a la película
    string id; // ID único de la película
    int likes; // Número de likes

public:
    // Constructor
    Pelicula(const string &titulo, const string &sinopsis, const unordered_set<string> &tags, const string &id)
        : titulo(titulo), sinopsis(sinopsis), tags(tags), id(id), likes(0) {
    }

    // Métodos para obtener los atributos
    string getTitulo() const { return titulo; }
    string getSinopsis() const { return sinopsis; }
    unordered_set<string> getTags() const { return tags; }
    string getId() const { return id; }
    int getLikes() const { return likes; }

    // Métodos para modificar likes
    void addLike() { likes++; } // Incrementar un like
    void subLike() { if (likes > 0) likes--; } // Reducir un like (mínimo 0 para evitar negativos)
};

//---------------------------------------------------------------------------------------------------------------------------------









void buscarPeliculas() {
    UserSession* actualSesion;
    while (true) {
        cout << "Buscador: ";
        string input;
        cin.ignore();
        getline(cin, input);
        cout << "\n";

        // Suponiendo que `Searcher` es una clase que maneja la búsqueda de las películas.
        Searcher searcher("mpst_full_data.csv");
        searcher.find(input);
        auto suggestions = searcher.get_suggestions();

        // Mostrar las sugerencias y sus índices
        cout << "Sugerencias encontradas:\n";
        for (size_t i = 0; i < suggestions.size(); ++i) {
            const auto &e = suggestions[i];
            const auto index = searcher.get_dataframe().search("title", e);
            cout << index << " " << searcher.get_dataframe().get_data("title", index) << endl;
        }

        // Solicitar al usuario que seleccione un índice
        cout << "Seleccione el índice de la película que le interesa: ";
        int seleccion;
        cin >> seleccion;


        // Mostrar detalles de la película seleccionada
        cout << seleccion << " " << searcher.get_dataframe().get_data("title", seleccion) << endl;
        cout << "\nGéneros: ";
        string genres = searcher.get_dataframe().get_data("tags", seleccion);
        cout << genres << endl;

        // Mostrar la sinopsis completa
        cout << "Sinopsis completa: " << searcher.get_dataframe().get_data("plot_synopsis", seleccion) << endl;

        // Opciones adicionales
        cout << "\n¿Qué desea hacer?\n";
        cout << "1. Buscar otra película\n";
        cout << "2. Darle like\n";
        cout << "3. Agregar a favoritos\n";
        cout << "4. Salir\n";

        int opcion;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Volver al inicio del bucle para buscar otra película
                continue;
            case 2:
                // Llamar a la función para dar "like"
                actualSesion->getCurrentUser()->addPeliculaLike(searcher.get_dataframe().get_data("title", seleccion));
                cout << "¡Le diste like a la película!" << endl;
                break;
            case 3:
                // Llamar a la función para agregar a favoritos
                actualSesion->getCurrentUser()->addVerMasTarde(searcher.get_dataframe().get_data("title", seleccion));
                cout << "Película agregada a ver más tarde" << endl;
                break;
            case 4:
                // Salir del bucle y de la función
                cout << "Saliendo del buscador..." << endl;
                return;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
                break;
            }

    }
}

//Imprime las peliculas ver más tarde del usuario actual
void verMasTarde() {
    UserSession* actualSesion;
    if (!actualSesion) {
        cout << "Error: No hay una sesión activa.\n";
        return;
    }

    // Suponiendo que `Searcher` es una clase que maneja la búsqueda de las películas.
    Searcher searcher("mpst_full_data.csv");

    // Obtener las películas de "ver más tarde" del usuario actual
    auto peliculasVerMasTarde = actualSesion->getCurrentUser()->getVerMasTarde();
    if (peliculasVerMasTarde.empty()) {
        cout << "No tienes películas en tu lista de 'ver más tarde'.\n";
        return;
    }

    while (true) {
        cout << "Películas en tu lista de 'ver más tarde':\n";
        for (const auto& pelicula : peliculasVerMasTarde) {
            const auto index = searcher.get_dataframe().search("title", pelicula);
            if (index != -1) {
                cout << index << " " << searcher.get_dataframe().get_data("title", index) << endl;
            } else {
                cout << "Película no encontrada en la base de datos: " << pelicula << endl;
            }
        }

        // Solicitar al usuario que seleccione un índice
        cout << "\nSeleccione el índice de la película que le interesa, o -1 para salir: ";
        int seleccion;
        cin >> seleccion;

        if (seleccion == -1) {
            cout << "Saliendo del menú 'ver más tarde'.\n";
            break;
        }

        // Mostrar detalles de la película seleccionada
        cout << seleccion << " " << searcher.get_dataframe().get_data("title", seleccion) << endl;
        cout << "\nGéneros: ";
        string genres = searcher.get_dataframe().get_data("tags", seleccion);
        cout << genres << endl;

        cout << "Sinopsis completa: " << searcher.get_dataframe().get_data("plot_synopsis", seleccion) << endl;


        // Opciones adicionales
        cout << "\n¿Qué desea hacer?\n";
        cout << "1. Buscar otra película\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opción: ";

        int opcion;
        cin >> opcion;

        if (opcion == 2) {
            cout << "Saliendo del menú 'ver más tarde'.\n";
            break;
        } else if (opcion != 1) {
            cout << "Opción no válida. Intente nuevamente.\n";
        }
    }
}

// Función para crear mostrar el Menu del la plataforma de streaming
void menu() {
    int choice; // Variable para almacenar la elección del usuario

    while (true) {
        // Mostrar el menú
        cout << "============================= \n";
        cout << "   Plataforma de Películas    \n";
        cout << "============================= \n";
        cout << "\n";
        cout << "1. Buscar Películas\n";
        cout << "2. Ver más tarde\n";
        cout << "3. Ver películas que te gustaron\n";
        cout << "4. Salir\n";
        cout << "\n";

        // Solicitar la opción al usuario
        cout << "Selecciona una opción: ";
        cin >> choice;

        // Procesar la elección
        switch (choice) {
            case 1:
                buscarPeliculas();
                break;
            case 2:
                verMasTarde();
                break;
            case 3:
                //verLikes();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                return; // Salir del bucle y terminar el programa
            default:
                cout << "Opción inválida, por favor elige otra.\n";
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------


UserSession *UserSession::instance = nullptr;
User *UserSession::currentUser = nullptr;

int main() {
    bool login = false;
    string datapath = "users.json";
    loadUsersFromJSON(datapath);

    UserSession *actualSesion = UserSession::getInstance();


    // for(auto& e : UsersData){
    //     cout<< UsersData[e.first].getUsername() << endl;
    //     cout<< UsersData[e.first].getEmail() << endl;
    //     cout<< UsersData[e.first].getPassword() << endl;
    // }

    while (true) {
        int choice;
        cout << "============================= \n";
        cout << "   Plataforma de Películas    \n";
        cout << "============================= \n";
        cout << "\n";
        cout << "-----------------------------\n";
        cout << "1. Crear una cuenta\n";
        cout << "2. Iniciar sesión\n";
        cout << "3. Salir\n";
        cout << "-----------------------------\n";
        cout << "Selecciona una opción: ";
        cout << "\n";
        cin >> choice;

        if (choice == 1)
            crearUsuario(datapath);
        else if (choice == 2) {
            login = ingresar(actualSesion);
        } else if (choice == 3) {
            break;
        }

        if (login) {
            menu();
            //  cout<<"Bienvenido "<< UserSession::getCurrentUser()->getUsername()<<endl;
        }
    }


    return 0;
}
