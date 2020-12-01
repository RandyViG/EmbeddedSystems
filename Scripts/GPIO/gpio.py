#Este script configura el BCM_GPIO 16 usando python
#EL BCM_GPIO 17 corresponde con la terminal 36 del conector
#de 40 pines de la raspberry

import RPi.GPIO as GPIO
import time

PIN = 36

#Se inicializa los GPIOS
GPIO.setmode( GPIO.BOARD )
#Se configura el BCM_GPIO 16 como salida usando la terminal 36
GPIO.setup( PIN, GPIO.OUT )

#Se escribe un valor digital al BCM_GPIO 16
while( True ):
    GPIO.output( PIN, GPIO.HIGH )
    time.sleep( 1 )
    GPIO.output( PIN, GPIO.LOW )
    time.sleep( 1 )

