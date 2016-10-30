#!/bin/bash

chmod +x ./audita
./audita disco-virtual

echo "Pulsa enter para continuar. Apartado a)"
read p

echo "Copiando fuseLib.c y myFS.h a nuestro SF..."
cp src/fuseLib.c punto-montaje/
cp src/myFS.h punto-montaje

echo "Creando directorio temporal(copiasTemporales)..."
mkdir copiasTemporales

echo "Copiando fuseLib.c y myFS.h al directorio temporal..."
cp src/fuseLib.c copiasTemporales
cp src/myFS.h copiasTemporales/

echo "Pulsa enter para continuar. Apartado b)"
read p

./audita disco-virtual

diff src/fuseLib.c punto-montaje/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/myFS.h punto-montaje/myFS.h
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/fuseLib.c copiasTemporales/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/myFS.h copiasTemporales/myFS.h
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi


echo "Pulsa enter para continuar. Apartado c)"
read p

truncate -s 4500 copiasTemporales/fuseLib.c
truncate -s 4500 punto-montaje/fuseLib.c

echo "Pulsa enter para continuar. Apartado d)"
read p

./audita disco-virtual

diff src/fuseLib.c punto-montaje/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/fuseLib.c copiasTemporales/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi


echo "Pulsa enter para continuar. Apartado e)"
read p

echo "CarlosSalvadorAmoresMartinez_23 ----- AndresFelipeAguilarOchoa_69" > cf.txt
echo "Copiando cf.txt nuestro SF..."
cp cf.txt punto-montaje/

echo "Pulsa enter para continuar. Apartado f)"
read p

./audita disco-virtual

diff cf.txt punto-montaje/cf.txt
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

echo "Pulsa enter para continuar. Apartado g)"
read p

truncate -s 4097 copiasTemporales/myFS.h
truncate -s 4097 punto-montaje/myFS.h

echo "Pulsa enter para continuar. Apartado h)"
read p

./audita disco-virtual

diff src/myFS.h punto-montaje/myFS.h
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/myFS.h copiasTemporales/myFS.h
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

echo "HEMOS TERMINADO. PULSA ENTER"
read p








