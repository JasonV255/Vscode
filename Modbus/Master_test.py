import minimalmodbus
import serial
import sys

port = 'COM15'
slave_id = 1

try:
    instrument = minimalmodbus.Instrument(port=port, slave=slave_id)
    print("Connected")
except:
    print(f"Could not connect to device on port {port}")
    sys.exit(1)

