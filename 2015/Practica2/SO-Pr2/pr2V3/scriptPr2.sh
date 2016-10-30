#!/bin/sh

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
