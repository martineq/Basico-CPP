#######################################
# Dockerfile para el uso del Servidor #
# Basado en Ubuntu 14.04              #
#######################################

# Setea la imagen base (Ubuntu oficial)
FROM ubuntu

# Autor: mart / Mantiene: mart
MAINTAINER mart mart

# Copio carpetas. TODO: Ver que contenido copiar.
COPY ./ /home

# En el RUN hago las siguientes tareas:
# 1) Instalo las programas necesarios
# 2) Instalo las dependencias necesarias
# 3) Limpio el directorio luego del apt-get
# 4) Instalo la librería RocksDB manualmente
# 5) Instalo la librería Mongoose manualmente
# 6) Instalo la librería jsoncpp manualmente
RUN apt-get update && apt-get install -y \
		build-essential \
		python \
		git \
		cmake \
		wget \
		unzip \
		valgrind \
		tree \
		vim \
		nano \
		joe \
		libsnappy-dev \
		zlib1g-dev \
		libbz2-dev \
		libgflags-dev \
		tar \
		curl \
		lcov && \
	rm -rf /var/lib/apt/lists/* && \
	cd /home && \
	mkdir temp_install && \
	cd temp_install && \
	wget https://github.com/facebook/rocksdb/archive/v3.13.1.zip && \
	unzip v3.13.1.zip && \
	cd rocksdb-3.13.1 && \
	make static_lib && \
	cd .. && \
	rm v3.13.1.zip && \
	wget https://github.com/cesanta/mongoose/archive/master.zip && \
	unzip master.zip && \
	cd mongoose-master && \
	gcc -c mongoose.c && \
	ar rvs libmongoose.a mongoose.o && \
	sudo cp libmongoose.a /usr/lib && \
	cd .. && \
	rm master.zip && \
	wget https://github.com/open-source-parsers/jsoncpp/archive/master.zip && \
	unzip master.zip && \
	cd jsoncpp-master && \
	python amalgamate.py && \
	cd dist && \
	gcc -c jsoncpp.cpp && \
	ar rvs libjsoncpp.a jsoncpp.o && \
	sudo cp libjsoncpp.a /usr/lib && \
	cd ../.. && \
	rm master.zip && \
	cd ..
# TODO: Para seguir agregando comandos en la misma línea acordarse de agregar el " && \" en la línea de arriba
#	 && \
#	 && \

# Defino el directorio de trabajo
WORKDIR /home

# Defino el comando estándar
CMD ["bash"]
