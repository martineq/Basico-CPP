#include <iostream>
#include <stdio.h>
#include <string.h>
#include "jason.h" //Header de la clase de prueba

using namespace std;

void Jason::EjemploUno() {

	// Crea desde el principio
	Json::Value fromScratch;
	Json::Value array;
	array.append("hello");
	array.append("world");
	fromScratch["hello"] = "world";
	fromScratch["number"] = 2;
	fromScratch["array"] = array;
	fromScratch["object"]["hello"] = "world";

	Salida(fromScratch);

	// Escribe en manera legible
	Json::StyledWriter styledWriter;
	std::cout << styledWriter.write(fromScratch);

	// Parseo

	// Escribe en forma compacta
	Json::FastWriter fastWriter;
	std::string jsonMessage = fastWriter.write(fromScratch);

	Json::Value parsedFromString;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonMessage, parsedFromString);
	if (parsingSuccessful){
	    std::cout << styledWriter.write(parsedFromString) << std::endl;
	}

	cout << "¡Hola Mundo! - JsonCpp" << endl;

}

void Jason::Salida(const Json::Value & value){
    std::cout << value["hello"];
    std::cout << value["number"];
    std::cout << value["array"][0] << value["array"][1];
    std::cout << value["object"]["hello"];
}
