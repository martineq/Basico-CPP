############################################################
# Dockerfile de prueba
# Basado en Ubuntu
############################################################

# Setea la imagen base como Ubuntu
FROM ubuntu

# Autor: mart / Mantiene: mart
MAINTAINER mart mart

# Imprimo un hola mundo
RUN echo "¡Hola mundo! - Desde el Dockerfile"

# Hago un ls -a
RUN ls -a
