#include <iostream>
#include <cstdio>
#include <string>
#include <assert.h>
#include <unistd.h>
#include "rocks.h"  //Header de la clase de prueba
#include "rocksdb/db.h"  //Header de la librería
#include "rocksdb/slice.h"  //Header de la librería
#include "rocksdb/options.h"  //Header de la librería

using namespace std;
using namespace rocksdb;

void Rocks::EjemploUno() {

	// Uso la librería rocksdb
	rocksdb::DB *db;
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb/", &db);
	assert(status.ok());

	cout << "¡Hola Mundo! - RocksDB" << endl;

}

void Rocks::EjemploDos() {

	std::string kDBPath = "/tmp/testdb/"; //get_current_dir_name(); kDBPath+="tempBD";

	DB* db;
	Options options;

	// Optimiza RocksDB. This is the easiest way to get RocksDB to perform well
	options.IncreaseParallelism();
	options.OptimizeLevelStyleCompaction();

	// Crea la BD si no existiera antes
	options.create_if_missing = true;

	// Abre la BD
	Status s = DB::Open(options, kDBPath, &db);
	assert(s.ok());

	// Uso del Put()
	s = db->Put(WriteOptions(), "key1", "value");
	assert(s.ok());
	std::string value;

	// Uso del Get()
	s = db->Get(ReadOptions(), "key1", &value);
	assert(s.ok());
	assert(value == "value");

	// Aplico un grupo de actualizaciones atómicas
	{
	WriteBatch batch;
	batch.Delete("key1");
	batch.Put("key2", value);
	s = db->Write(WriteOptions(), &batch);
	}

	s = db->Get(ReadOptions(), "key1", &value);
	assert(s.IsNotFound());

	db->Get(ReadOptions(), "key2", &value);
	assert(value == "value");

	delete db;

	cout << "¡Hola Mundo! - RocksDB" << endl;

}

