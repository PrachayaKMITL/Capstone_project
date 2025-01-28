import bluetooth

def connect_to_esp32_bluetooth(mac_address, port=1):
    """
    Establishes a Bluetooth connection to the ESP32.
    
    Args:
        mac_address (str): The MAC address of the ESP32.
        port (int): The RFCOMM port (usually 1).

    Returns:
        bluetooth.BluetoothSocket: The Bluetooth socket object.
    """
    try:
        print(f"Connecting to ESP32 at {mac_address}...")
        bt_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        bt_socket.connect((mac_address, port))
        print("Bluetooth connection established.")
        return bt_socket
    except Exception as e:
        print(f"Failed to connect to Bluetooth: {e}")
        return None

def send_data_via_bluetooth(bt_socket, data):
    """
    Sends data to the ESP32 over Bluetooth.
    
    Args:
        bt_socket (bluetooth.BluetoothSocket): The Bluetooth socket object.
        data (str): The data to send.
    """
    try:
        print(f"Sending data: {data}")
        bt_socket.send(data)
        print("Data sent.")
    except Exception as e:
        print(f"Failed to send data via Bluetooth: {e}")

def main():
    # Replace with your ESP32's MAC address
    esp32_mac_address = "CC:DB:A7:8F:CC:BE"  # Current ESP32 Bluetooth address

    # Establish connection
    bt_socket = connect_to_esp32_bluetooth(esp32_mac_address)

    if bt_socket:
        try:
            # Send a test message
            send_data_via_bluetooth(bt_socket, "Hello, ESP32!")
        finally:
            # Close the connection
            bt_socket.close()
            print("Bluetooth connection closed.")

if __name__ == "__main__":
    main()
