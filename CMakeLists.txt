# Versión de CMake mínima usada para generar el proyecto
cmake_minimum_required(VERSION 2.8)

# Definición del proyecto. Con CXX indico que todos los archivos son tratados como C++.
set(KEYWORD "tp0")  # Seteo el nombre del ejecutable
project(${KEYWORD} CXX)

# Seteo rutas del directorio de librerias y del directorio de código fuente
set(RUTA_RAIZ "${${KEYWORD}_SOURCE_DIR}")
set(RUTA_LIB "${RUTA_RAIZ}/lib")
set(RUTA_SRC "${RUTA_RAIZ}/src")

# Seteo una variable "SRC" donde coloco la rutas de los archivos fuente
set(SRC ${RUTA_SRC}/main.cpp ${RUTA_SRC}/rocks.cpp ${RUTA_SRC}/mon.cpp ${RUTA_SRC}/jason.cpp)

# Seteo los nombres de las librerías
set(LIBS rocksdb bz2 snappy z pthread rt mongoose jsoncpp)

####################

# Pruebo correr un script de prueba. TODO: Desde acá se instalarán todas las librerías necesarias para compilar el proyecto
# execute_process(COMMAND ${RUTA_RAIZ}/script.sh)

####################

# Chequeo la existencia de todas las librerias agregadas
foreach(LIB ${LIBS})
   find_library(LIBRERIA${LIB} ${LIB})
   if (LIBRERIA${LIB}) #False si es 0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, vacio, o si termina en "-NOTFOUND". Caso contrario es TRUE.
      message(STATUS "Librería |${LIB}| encontrada en |${LIBRERIA${LIB}}|")         
   else (LIBRERIA${LIB})
      message(FATAL_ERROR "No se encontró la librería |${LIB}|. Verificar existencia.")
   endif (LIBRERIA${LIB})
endforeach(LIB ${LIBS})

# Nombre del ejecutable resultante de la compilación. Los demás argumentos son los archivos fuente (sin los headers)
add_executable(${KEYWORD} ${SRC})

# Incluyo la ruta de las librerías para el compiler
include_directories(${RUTA_LIB})

# Vinculo la ruta de las librerías y los nombres de las mismas para el linker
link_directories(${RUTA_LIB})
target_link_libraries(${KEYWORD} ${LIBS})

# Línea agregada para hacer uso de ISO C++11 que requiere la librería RocksDB. Agrega al compilador el feature "cxx_range_for"
target_compile_features(${KEYWORD} PRIVATE cxx_range_for)

