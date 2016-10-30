#!/bin/bash


cd ../gantt-plot
chmod +x ./generate_gantt_chart
chmod +x ./gantt.py
cd ../schedsim

		
make clean
make


echo "1.- Que fichero desea simular: "
read fichero
while [ ! -e examples/$fichero ] || [ ! -f examples/$fichero ] ; do
	echo "Fallo, el fichero no existe o no es regular"
	echo "1.- Que fichero desea simular: "
	read fichero
done


echo "2.- Numero de CPUs que desea usar: "
read maxCPUs
while [ $maxCPUs -gt 8 ] || [ $maxCPUs -lt 1 ] ; do
	echo "Fallo, maximo 8 CPUs, minimo 1 CPU"
	echo "2.- Numero de CPUs que desea usar: "
	read maxCPUs
done


echo "************************************************************************"
echo "****** --> Simulamos '"$fichero"' con un maximo de "$maxCPUs" CPUs <--******"
echo "************************************************************************"
read p


echo "Creando directorio resultados..."
if test -d resultados ; then
	rm -r resultados
fi
mkdir resultados
read p

echo "Falta bucle exterior"
for cpus in `seq 1 1 $maxCPUs`
do
	echo "hola" $cpus
	./schedsim -i examples/$fichero -n $cpus	
	
	for i in `seq 1 1 $cpus`
	do
		echo "Adios" $i
		mv CPU_$i.log resultados/rr-CPU_$i.log
	done	
	
	read p
	cd ../gantt-plot
	./generate_gantt_chart ../schedsim/resultados/*.log
	cd ../schedsim
	read p

done
	

















