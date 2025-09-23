#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>



using namespace std;



int main(int argc, char *argv[]) {
    string nombres[80];
    string paises[80];
    string disciplinas[80];
    char generos[80];
    int medallas[80];

    int totalAtletas = 0;

    string rutaArchivo="archivo.csv";
    

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrirlo" << endl;
        return 1;
    }

    string linea;
    getline(archivo, linea); 

    while (getline(archivo, linea)) {
        if (linea.empty()){
        continue;
        } 

        stringstream ss(linea);
        string nombre, pais, disciplina, genero, medallasStr;

        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, disciplina, ',');
        getline(ss, genero, ',');
        getline(ss, medallasStr, ',');

        nombres[totalAtletas] = nombre;
        paises[totalAtletas] = pais;
        disciplinas[totalAtletas] = disciplina;
        generos[totalAtletas] = genero.empty() ? ' ' : genero[0];
        medallas[totalAtletas] = stoi(medallasStr);

        totalAtletas++;
    }
    archivo.close();

    int opcion = 0;
    

    while (opcion != 5) {
        
        cout << "\n--- MENU ---\n";
        cout << "1. Buscar atleta\n";
        cout << "2. Mostrar total de medallas por pais\n";
        cout << "3. Mostrar atleta con mas medallas\n";
        cout << "4. Agregar Atleta\n";
        cout << "5. Salir\n";
        cout << "Elige una opcion: ";
        
        
if (!(cin >> opcion)) {
    cin.clear();    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Entrada invalida" << endl;
    continue;
}
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion == 1) {
            string nombrebus;
            cout << "\n";
            cout << "Ingrese el nombre del atleta: ";
            getline(cin, nombrebus);

            bool encontrado = false;
            for (int i = 0; i < totalAtletas; i++) {
                if (nombres[i] == nombrebus) {
                    cout << "\n";
                    cout << "Nombre: " << nombres[i]<<endl;
                    cout << "Genero: " << generos[i]<<endl;
                    cout << "Disciplina: " << disciplinas[i]<<endl;
                    cout << "Pais: " << paises[i] << endl;
                    cout << "Medallas de oro: " << medallas[i] << endl;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "No se encontro al atleta" << endl;
            }
        }
        else if (opcion == 2) {
            cout << "\n";
            cout << "\nTotal de medallas de oro por pais:\n";
            for (int i = 0; i < totalAtletas; i++) {
                int suma = 0;
                bool contado = false;

                for (int j = 0; j < i; j++) {
                    if (paises[j] == paises[i]) {
                        contado = true;
                        break;
                    }
                }
                if (contado) {
                    continue;
                }

                for (int k = 0; k < totalAtletas; k++) {
                    if (paises[k] == paises[i]) {
                        suma += medallas[k];
                    }
                }
                cout << paises[i] << " = " << suma << " medallas" << endl;
            }
        }
        else if (opcion == 3) {
            if (totalAtletas == 0) {
                continue;
            }
            int medallasmax = 0;
            for (int i = 1; i < totalAtletas; i++) {
                if (medallas[i] > medallas[medallasmax]) {
                    medallasmax = i;
                }
            }
            cout << "El atleta con mas medallas es: " 
                 << nombres[medallasmax] 
                 << " (" << medallas[medallasmax] << " medallas)" << endl;
        }else if(opcion==4){
  if (totalAtletas >= 80) {
        cout << "No se pueden agregar mas atletas." << endl;
    } else {
        string nombre, pais, disciplina;
        char genero;
        int medallasOro;

        cout << "Ingrese nombre: ";
        getline(cin, nombre);
        cout << "Ingrese pais: ";
        getline(cin, pais);
        cout << "Ingrese disciplina: ";
        getline(cin, disciplina);
        cout << "Ingrese genero (M/F): ";
        cin >> genero;
        cout << "Ingrese numero de medallas de oro: ";
        cin >> medallasOro;
        cin.ignore();

        
        nombres[totalAtletas] = nombre;
        paises[totalAtletas] = pais;
        disciplinas[totalAtletas] = disciplina;
        generos[totalAtletas] = genero;
        medallas[totalAtletas] = medallasOro;
        totalAtletas++;

        
        ofstream archivoOut(rutaArchivo, ios::app);
        if (archivoOut.is_open()) {
            archivoOut << nombre << "," << pais << "," << disciplina << "," 
                       << genero << "," << medallasOro << "\n";
            archivoOut.close();
            cout << "Atleta agregado correctamente al archivo." << endl;
        } else {
            cout << "No se abre el archivo" << endl;
        }
    }  

         if (opcion == 5) {
            cout << "Saliendo..." << endl;
        }
        else {
            cout << "Por ingresa una opcion valida." << endl;
        }
    }
}

    return 0;
}
