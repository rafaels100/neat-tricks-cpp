#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
En este approach hago un split a mano de cada linea. Las lineas son palabras separadas por un espacio.
Lo que hago es leer linea por linea con getline(), done cada linea (line) resultante de esa lectura es una string con palabras separadas por espacios.
Luego, hago un split de la string para separarla en las palabras que la componen. Uso como delimitador el espacio.
El truco es ir encontrando los espacios y luego ir cortando la string original, para no incluir todo lo anterior. De esa forma, cuando llegue al final
y ya no queden espacios delimitadores, solo me quedara la palabra del final, pues habre cortado todo lo anterior.
*/


int main(){
  ifstream inputFile("input.txt");
  
  if (!inputFile.is_open()) {
    cerr << "Error opening file!" << endl;
    return 1;
  }
  
  string line;
  vector<vector<string>> lineas;
  //itero por cada linea de la file con getline
  while (getline(inputFile, line)) {
    //creo un vector de strings donde guardare las strings que spliteo con el delimitador espacio
    vector<string> linea;
    string token;
    int pos = 0;
    //busco la posicion donde esta el delimitador espacio. Si la encuentro, significa que no llego hasta el final, hasta la posicion \0 de la string. Ahi entro
    while((pos = line.find(' ')) != string::npos) {
      //me quedo desde el ppio de la string original (0 inclusive) hasta la posicion donde esta el delimitador (pos no inclusive).
      token = line.substr(0, pos);
      //guardo la string en el vector de palabras spliteadas
      linea.push_back(token);
      //elimino esta palabra (mas el espacio) de la string line original, para buscar una nueva palabra en la proxima iteracion. Elimino hasta pos + 1 para que incluya al 
      //espacio (el delimitador de 1 caracter) en la eliminacion
      line.erase(0, pos + 1);
    }
    //al salir del while ya no encontro espacios en la string line. Esto significa que solo queda una palabra, pues elimine todo lo anterior.
    //guardo esa palabra, que es la string original line achurada.
    linea.push_back(line);
    //una vez que salgo del for, agrego esta linea 'vectorizada' a mi lista de lineas
    lineas.push_back(linea);
  }
  //asi solucione el problema de la ultima palabra que tenia en el aproach de ir char por char, pues la ultima palabra es lo que queda de la string line
  //original luego de cortarla en los delimitadores sucesivamente.
  
  inputFile.close();
  cout << "Contenido del vector de vectores de strings: " << endl;
  for (vector<string> &linea : lineas) {
    for (string &palabra : linea) {
      cout << palabra << " ";
    }
    cout << endl;
  }
  return 0;
}
