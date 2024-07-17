from pymodbus.client.serial import ModbusSerialClient

# Modbus slave address of your battery system
slave_address = 0x01

# Configure serial port (replace with your RS485 adapter's port)
#port = "/dev/ttyUSB0"
port= "COM20"

# Baud rate (common baud rates for Modbus RTU are 9600, 19200, 38400)
baudrate = 9600

# Create Modbus client
client = ModbusSerialClient(method="rtu", port=port, baudrate=baudrate)

# Read battery voltage (assuming register address 0x01)
read_data = client.read_holding_registers(0x01, 1)
battery_voltage = read_data.registers[0] / 10  # Assuming voltage is scaled by 10 in the register

# Print battery voltage
print(f"Battery Voltage: {battery_voltage} V")

# Close Modbus connection
client.close()
