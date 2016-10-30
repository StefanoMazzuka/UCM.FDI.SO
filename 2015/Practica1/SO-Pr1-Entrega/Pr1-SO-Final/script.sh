#!/bin/sh
if test -e mitar ; then
	echo "Mi tar existe"
else
	echo "Mi tar no existe"
	exit 1
fi
if [ -x mitar ] ; then
	echo "Mi tar es ejecutable"
else
	echo "Mi tar no es ejecutable"
	exit 1
fi
if test -d tmp ; then
	echo "Existe tmp, borraremos todo"
	rm -r tmp
else
	echo "No existe directorio tmp, lo creamos y entramos dentro."
fi
mkdir tmp
cd tmp
echo "Hola Mundo" > fich1.txt
head -10 /etc/passwd > fich2.txt
head -c 1024 /dev/urandom > fich3.txt
.././mitar -c -f fichtar.mtar fich1.txt fich2.txt fich3.txt
mkdir out
cp fichtar.mtar out
cd out
../.././mitar -x -f fichtar.mtar

diff fich1.txt ../fich1.txt
if [ $? -eq 0 ] ; then
	echo "fich1.txt ES igual que fich1.txt"
else	
	cd ../../
	echo "fich1.txt NO ES igual que fich1.txt"
	exit 1
fi

diff fich2.txt ../fich2.txt
if [ $? -eq 0 ] ; then
	echo "fich2.txt ES igual que fich2.txt"
else	
	cd ../../
	echo "fich2.txt NO ES igual que fich2.txt"
	exit 1
fi

diff fich3.txt ../fich3.txt
if [ $? -eq 0 ] ; then
	
	echo "fich3.txt ES igual que fich3.txt"
else	
	cd ../../
	echo "fich3.txt NO ES igual que fich3.txt"
	exit 1
fi
cd ../../
echo "Correcto"
exit 0
