#!/bin/bash

chmod +x ./audita
./audita disco-virtual

echo "Pulsa enter para continuar. Apartado a)"
read p

PM="./punto-montaje"
cpTmp="./copiasTemporales"

echo "Copiando fuseLib.c y myFS.h a nuestro SF..."
cp src/fuseLib.c $PM/
cp src/myFS.h $PM

echo "Creando directorio temporal(copiasTemporales)..."
mkdir $cpTmp

echo "Copiando fuseLib.c y myFS.h al directorio temporal..."
cp src/fuseLib.c $cpTmp
cp src/myFS.h $cpTmp/

echo "Pulsa enter para continuar. Apartado b)"
read p

./audita disco-virtual

diff src/fuseLib.c $PM/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/myFS.h $PM/myFS.h
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/fuseLib.c $cpTmp/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/myFS.h $cpTmp/myFS.h
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi


echo "Pulsa enter para continuar. Apartado c)"
read p

truncate -s 4500 cpTMP/fuseLib.c
truncate -s 4500 PM/fuseLib.c

echo "Pulsa enter para continuar. Apartado d)"
read p

./audita disco-virtual

diff src/fuseLib.c $PM/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi

diff src/fuseLib.c $cpTmp/fuseLib.c
if [ $? -eq 0 ] ; then
	echo "IGUALES"
else	
	echo "NO IGUALES"
fi


echo "Pulsa enter para continuar. Apartado e)"
read p

echo "CarlosAmores23FelipeAguilar69" > carlosFelipe.txt
echo "Copiando carlosFelipe.txt nuestro SF..."
cp carlosFelipe.txt $PM/


