#!/bin/bash
#Este script configura el BCM_GPI 16 usando el FHS

GPIO=16

# export 
# Sirve para exportar el control del GPIO desde el kernel 
# al espacio de usuario, escribiendo su número al archivo.
function habilita_GPIO(){
	if [ ! -d /sys/class/gpio/gpio$GPIO ]
	then 
		echo $GPIO > /sys/class/gpio/export
		sleep 1
	fi 
}

# unexport
# Revierte el efecto de exportar al espacio de usuario,
# escribiendo su número al archivo.
function deshabilita_GPIO(){
	if [ -d /sys/class/gpio/gpio$GPIO ]
	then 
		echo $GPIO > /sys/class/gpio/unexport
	fi 
}

habilita_GPIO
# direction
# Atributo que configura la dirección de entrada (in) o 
# salida (out) del gpio
echo "out" > /sys/class/gpio/gpio$GPIO/direction
while [ 1 ]
do
	# value
	# Atributo que permite escribir un valor digital 
	# al  GPIO
	echo "1" > /sys/class/gpio/gpio$GPIO/value
	sleep 1
	echo "0" > /sys/class/gpio/gpio$GPIO/value
	sleep 1
done
deshabilita_GPIO
