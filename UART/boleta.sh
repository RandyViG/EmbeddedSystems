#!/bin/bash

NUM_BOLETA=$1

#     (A  B  C  D  E  F  G)
GPIOS=(14 15 18 23 24 25 8)

BOLETA1=(2 0 1 4 1 7 0 8 2 5)
BOLETA2=(2 0 1 7 6 3 0 1 8 2)
BOLETA3=(2 0 1 7 6 3 1 5 7 1)

#       (A B C D E F G)
DIGITO0=(1 1 1 1 1 1 0)
DIGITO1=(0 1 1 0 0 0 0)
DIGITO2=(1 1 0 1 1 0 1)
DIGITO3=(1 1 1 1 0 0 1)
DIGITO4=(0 1 1 0 0 1 1)
DIGITO5=(1 0 1 1 0 1 1)
DIGITO6=(1 0 1 1 1 1 1)
DIGITO7=(1 1 1 0 0 0 0)
DIGITO8=(1 1 1 1 1 1 1)
DIGITO9=(1 1 1 1 0 1 1)

function habilitaGPIO (){
	for i in ${GPIOS[*]}
	do
		if [ ! -d /sys/class/gpio/gpio$i ]
		then
			echo $i > /sys/class/gpio/export
			sleep 1
		fi
	done
}

function deshabilitaGPIO (){
	for i in ${GPIOS[*]}
	do
		if [ ! -d /sys/class/gpio/gpio$i ]
		then
			echo $i > /sys/class/gpio/unexport
		fi
	done
}

function configGPIO (){
	for j in ${GPIOS[*]}
	do
		if [ -d /sys/class/gpio/gpio$j ]
		then
			echo "out" > /sys/class/gpio/gpio$j/direction
		fi

	done
}

function numberDisplay (){
	TEMPORAL="DIGITO$1[@]"
	declare -a DIGITO=( "${!TEMPORAL}" );

	echo "Escribiendo el digito $1"

	for (( k = 0; k < ${#GPIOS[*]}; k++ ))
	do
		echo "${DIGITO[k]}" > /sys/class/gpio/gpio${GPIOS[k]}/value
	done
}

habilitaGPIO
configGPIO

while [ 1 ]
do
	AUX="BOLETA$1[@]"
	declare -a BOLETA=( "${!AUX}" )

	for l in ${BOLETA[*]}
	do
		numberDisplay $l
		sleep 1
	done
	echo "-----------------------"
done

deshabilitaGPIO

exit 0

