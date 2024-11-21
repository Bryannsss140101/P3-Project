#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class User{};

unordered_map <string,  User> UsersData;


class User {
    private:
    string username;
    string password; // Recuerda cifrarla para mayor seguridad
    string email;
    unordered_set<string> peliculasLike;
    unordered_set<string> verMasTarde;


    public:
    User(string username, string password, string email) {
        username = username;
        password = password;
        email = email;
    }

    // Getters y setters
    string getUsername() {
        return username;
    }

    string getPassword() {
       return password;
    }

    void setPassword(string password) {
        this->password = password;
    }

    string getEmail() {
        return email;
    }

    void setEmail(string email) {
        this->email = email;
    }

};



class UserSession {
    private:
    static UserSession* instance;
    static string* currentUser;

    UserSession() {}
    public:
    static UserSession* getInstance() {
        if (instance == nullptr) {
            instance = new UserSession();
        }
        return instance;
    }

    void login(string email) {
        *currentUser = UsersData[email];
    }

    void logout() {
        currentUser = nullptr;
    }

    string* getCurrentUser() {
        return currentUser;
    }
};



bool loginUser(string& email, string& password){
  auto it = UsersData.find(email);
  if (it == UsersData.end()){
    cout<<"Su correo no esta registrado."<<endl;
    return false;
  }
  if (UsersData[email].getPassword() == password){
    return true;
  }
  else{
    cout<<"Contrasena incorrecta."<<endl;
    return false;
  }
}

UserSession *UserSession::instance = nullptr;

int main(){
    
    UsersData["example@gmail.com"] = User("UglyCat", "example@gmail.com", "12345");
    UserSession* actualSesion = UserSession::getInstance();
    string email;
    string password;
    while (actualSesion->getCurrentUser() == nullptr){
      cout<<"Ingresa tu correo: ";
      cin>>email;
      cout<<"Ingresa tu contrasena: ";
      cin>>password;


      if(loginUser(email,password)){
        actualSesion->login(email);
      }
    }
    cout<<"Bienvenido :)";
  return 0;
}
