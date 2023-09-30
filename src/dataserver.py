#!/usr/bin/python3
import serial
import csv
fileName = "output.csv"
encabezado = ["Tension1", "Tension2", "Tension3", "Tension4"] 
ser = serial.Serial(
    port='/tmp/ttyS1',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
    timeout=200\
)
print("connected to: " + ser.portstr)
print("Creating csv file")
contador = 0
valores = []
file = open(fileName, mode='w', newline='')
filewrite = csv.writer(file)
filewrite.writerow(encabezado)
num_datos = int(input("Por favor digite la cantidad de datos a medir, luego ENTER: "))  # Filas de datos a recibir
datos_totales = num_datos*4
contador_datos = 0
contador_datos_towrite = 0
while True:
    linea_serie = ser.readline().decode().strip()
    print("Valor actual de medicion: " + linea_serie)
    valores.append(linea_serie)
    contador_datos_towrite += 1
    if contador_datos_towrite == 4:
        print("Escribiendo una nueva linea en el CSV")
        filewrite.writerow(valores)
        valores = []
        contador_datos_towrite = 0
        contador_datos += 1
    if contador_datos >= num_datos:
        break
ser.close()
file.close()
