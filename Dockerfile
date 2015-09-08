############################################################
# Dockerfile para el uso del Servidor
# Basado en Ubuntu
############################################################

# Setea la imagen base (Ubuntu oficial, versión 14.04)
FROM ubuntu:14.04

# Autor: mart / Mantiene: mart
MAINTAINER mart mart

# Copio las carpetas. Copio las carpetas de las librerias para luego compilarlas.
#COPY ./server /home

# En el RUN hago varias tareas
# 1) Instalo las dependencias necesarias
# 2) Limpio el directorio luego del apt-get
# 3) Instalo la librería RocksDB manualmente
# 4) Instalo la librería Mongoose manualmente
# 5) Instalo la librería jsoncpp manualmente
RUN apt-get update && apt-get install -y \
		build-essential \
		python \
		libsnappy-dev \
		zlib1g-dev \
		libbz2-dev \
		libgflags-dev \
		git \
		cmake \
		wget \
		unzip \
		tree && \
	rm -rf /var/lib/apt/lists/* && \
	cd /home && \
	wget https://github.com/facebook/rocksdb/archive/master.zip && \
	unzip master.zip && \
	cd rocksdb-master && \
	make static_lib && \
	sudo cp librocksdb.a /usr/local/lib && \
	cd .. && \
	rm -rf rocksdb-master && \
	rm master.zip && \
	wget https://github.com/cesanta/mongoose/archive/master.zip && \
	unzip master.zip && \
	cd mongoose-master && \
	gcc -c mongoose.c && \
	ar rvs libmongoose.a mongoose.o && \
	sudo cp libmongoose.a /usr/local/lib && \
	cd .. && \
	rm -rf mongoose-master && \
	rm master.zip && \
	wget https://github.com/open-source-parsers/jsoncpp/archive/master.zip && \
	unzip master.zip && \
	cd jsoncpp-master && \
	python amalgamate.py && \
	cd dist && \
	gcc -c jsoncpp.cpp && \
	ar rvs libjsoncpp.a jsoncpp.o && \
	sudo cp libjsoncpp.a /usr/local/lib && \
	cd ../.. && \
	rm -rf jsoncpp-master && \
	rm master.zip && \

# Defino el directorio de trabajo
WORKDIR /home

# Defino el comando estándar
CMD ["bash"]
