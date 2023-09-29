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
    timeout=20\
)
print("connected to: " + ser.portstr)
print("Creating csv file")
contador = 0
valores = []
file = open(fileName, mode='w', newline='')
filewrite = csv.writer(file)
filewrite.writerow(encabezado)
num_datos = 8  # Número de datos que se esperan recibir antes de cerrar el puerto
contador_datos = 0  # Contador de datos recibidos
while True:
    linea_serie = ser.readline().decode().strip()
    print("Valor actual de medicion: " + linea_serie)
    valores.append(linea_serie)
    contador_datos += 1  # Incrementar el contador de datos recibidos
    contador += 1
    print("Contador de datos: " + str(contador_datos))
    if contador == 4:
        print("Escribiendo una nueva linea en el CSV")
        contador = 0
        filewrite.writerow(valores)
        valores = []
    if contador_datos >= num_datos:
        break
ser.close()
file.close()