#!/bin/bash


cd ../gantt-gplot
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
echo "Directorio creado"
read p


listaDeSchedulersDisponibles=("PRIO" "RR"	)
for nameSched in ${listaDeSchedulersDisponibles[@]} 
do
	echo "Planificador ---> $nameSched <---"
	#read p
	for cpus in `seq 1 $maxCPUs` 
	do
		mkdir resultados/$nameSched-CPU-$cpus
		echo "Ejecutando planificador $nameSched con $cpus CPUs..."
		if [ "$nameSched" == "PRIO" ]; then
			./schedsim -i examples/$fichero -n $cpus -s $nameSched -p
		else
			./schedsim -i examples/$fichero -n $cpus -s $nameSched
		fi		
		for (( i=0; i<$cpus; i++ )) 
		do
			echo "Moviendo CPU-$cpus-_$i.log a resultados..."
			#mv CPU_$i.log resultados/$nameSched-CPU-$cpus-$i.log
			mv CPU_$i.log resultados/$nameSched-CPU-$cpus/$nameSched-CPU-$cpus-$i.log
		done
		
		cd ../gantt-gplot
		for (( j=0; j<$cpus; j++ ))
		do	
			echo "Generando gráfica de $nameSched-CPU-$cpus-$j.log..."
			#./generate_gantt_chart ../schedsim/resultados/$nameSched-CPU-$cpus-$j.log
			./generate_gantt_chart ../schedsim/resultados/$nameSched-CPU-$cpus/$nameSched-CPU-$cpus-$j.log
		done
		cd ../schedsim
	done	
done

exit 0
















