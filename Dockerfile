############################################################
# Dockerfile de prueba
# Basado en Ubuntu
############################################################

# Setea la imagen base como Ubuntu
FROM ubuntu

# Autor: mart / Mantiene: mart
MAINTAINER mart mart

# Imprimo un hola mundo y un ls -a cuando se inicia el contenedor
CMD echo "¡Hola mundo! - Desde el Dockerfile"
CMD ls -a
