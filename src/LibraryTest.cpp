#include <iostream>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "LibraryTest.h"  //Header de la clase de prueba

using namespace std;
using namespace rocksdb;


void LibraryTest::EjemploRocksDB() {

	cout << "------------------------" << endl;
	cout << " ¡Hola Mundo! - RocksDB " << endl;
	cout << "------------------------" << endl; cout << "RocksDB 00" << endl;

	std::string kDBPath = get_current_dir_name(); kDBPath+="/directorio_temporal_BD"; cout << "RocksDB 01" << endl;

	DB* db; cout << "RocksDB 02" << endl;
	Options options; cout << "RocksDB 03" << endl;

	// Optimiza RocksDB. This is the easiest way to get RocksDB to perform well
	/*.IncreaseParallelism();*/ cout << "RocksDB 04" << endl;
	/*options.OptimizeLevelStyleCompaction();*/ cout << "RocksDB 05" << endl;

	// Crea la BD si no existiera antes
	options.create_if_missing = true; cout << "RocksDB 06" << endl;

	// Abre la BD
	Status s = DB::Open(options, kDBPath, &db); cout << "RocksDB 07" << endl;
	assert(s.ok()); cout << "RocksDB 08" << endl;

	// Uso del Put()
	s = db->Put(WriteOptions(), "key1", "value"); cout << "RocksDB 09" << endl;
	assert(s.ok()); cout << "RocksDB 10" << endl;
	std::string value; cout << "RocksDB 11" << endl;

	// Uso del Get()
	s = db->Get(ReadOptions(), "key1", &value); cout << "RocksDB 12" << endl;
	assert(s.ok()); cout << "RocksDB 13" << endl;
	assert(value == "value"); cout << "RocksDB 14" << endl;

	// Aplico un grupo de actualizaciones atómicas
	{
	WriteBatch batch; cout << "RocksDB 15" << endl;
	batch.Delete("key1"); cout << "RocksDB 16" << endl;
	batch.Put("key2", value); cout << "RocksDB 17" << endl;
	s = db->Write(WriteOptions(), &batch); cout << "RocksDB 18" << endl;
	}

	s = db->Get(ReadOptions(), "key1", &value); cout << "RocksDB 19" << endl;
	assert(s.IsNotFound()); cout << "RocksDB 20" << endl;

	db->Get(ReadOptions(), "key2", &value); cout << "RocksDB 21" << endl;
	assert(value == "value"); cout << "RocksDB 22" << endl;

	delete db; cout << "RocksDB 23" << endl;

	cout << "Se creó y eliminó una base de datos en: " << kDBPath << endl;

	cout << "---------------" << endl;
	cout << " Fin - RocksDB " << endl;
	cout << "---------------" << endl;
}


void LibraryTest::EjemploJson() {

	cout << "------------------------" << endl;
	cout << " ¡Hola Mundo! - Jsoncpp " << endl;
	cout << "------------------------" << endl;

	// Crea desde el principio
	Json::Value fromScratch;
	Json::Value array;
	array.append("hello");
	array.append("world");
	fromScratch["hello"] = "world";
	fromScratch["number"] = 2;
	fromScratch["array"] = array;
	fromScratch["object"]["hello"] = "world";

	SalidaJson(fromScratch);

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

	cout << "---------------" << endl;
	cout << " Fin - Jsoncpp " << endl;
	cout << "---------------" << endl;
}

void LibraryTest::SalidaJson(const Json::Value & value){
    std::cout << value["hello"];
    std::cout << value["number"];
    std::cout << value["array"][0] << value["array"][1];
    std::cout << value["object"]["hello"];
}

void LibraryTest::EjemploMongoose() {

	struct mg_server *server;

	cout << "-------------------------" << endl;
	cout << " ¡Hola Mundo! - Mongoose " << endl;
	cout << "-------------------------" << endl;

	// Create and configure the server
	server = mg_create_server(NULL, ev_handler);
	mg_set_option(server, "listening_port", "8080");

	// Serve request. Hit Ctrl-C to terminate the program
	printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
	for (int i=0;i<3;i++) {
	cout << "Mongoose - Poll Cicle No:"<< i+1 << endl;
	mg_poll_server(server, 1000);
	}

	// Cleanup, and free server instance
	mg_destroy_server(&server);

	cout << "----------------" << endl;
	cout << " Fin - Mongoose " << endl;
	cout << "----------------" << endl;

}


int LibraryTest::ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:
      mg_printf_data(conn, "Hello! Requested URI is [%s]", conn->uri);
      return MG_TRUE;
    default: return MG_FALSE;
  }
}

