import smbus
import time

bus = smbus.SMBus(1)  # Use I2C bus 1 on Pi Zero W

sensor1_addr = 0x18
sensor2_addr = 0x10
distance_reg = 0x00

def read_tf_luna_distance(addr):
    try:
        data = bus.read_i2c_block_data(addr, distance_reg, 9)
        # Distance is in bytes 0 (low) and 1 (high)
        distance = data[0] + (data[1] << 8)
        return distance
    except Exception as e:
        print(f"Error reading from 0x{addr:02X}: {e}")
        return None

while True:
    dist1 = read_tf_luna_distance(sensor1_addr)
    dist2 = read_tf_luna_distance(sensor2_addr)

    print(f"Sensor 1 (0x18): {dist1} cm" if dist1 is not None else "Sensor 1 Error")
    print(f"Sensor 2 (0x10): {dist2} cm" if dist2 is not None else "Sensor 2 Error")
    print("-" * 30)
    time.sleep(0.5)