import serial.tools.list_ports as lp
from pymodbus.client import ModbusSerialClient
from enum import Enum

def find_plc() -> str:
    coms = ""
    for s in lp.comports():
        if s.vid == 0x2E8A and s.pid in [9,10,11,15,0xc0,0xf00a]:
            coms = s.device
        if s.vid == 0x239A and s.pid in [0x8120,0x80f4]:
            coms = s.device            
        if len(coms):
            print(f"Found Raspberry Pico on {s.device}")                        
            break
    return coms                       

def bits_to_ints(bits: list[bool], bits_per_int: int) -> list[int]:
    """Convert list of booleans to list of 16-bit integers"""
    result = []
    for i in range(0, len(bits), bits_per_int):
        chunk = bits[i:i + bits_per_int]
        # Convert chunk to integer
        value = 0
        for j, bit in enumerate(chunk):
            if bit:  # If bit is True/1
                value |= (1 << j)  # Set the j-th bit
        result.append(value)
    return result

class MemoryType(Enum):
    I16=16 # 16bit input registers
    I32=32 # 32bit input registers
    I64=64 # 64bit input registers

class PLC_ModBusInterface:
    def __init__(self, device_id: int = 1):
        self.id = device_id
        self.connected = False

    def connect(self):
        serial_port = find_plc()
        if len(serial_port):
            self.client = ModbusSerialClient(port=serial_port, baudrate=115200)
            self.connected = self.client.connect()
            if not self.connected:
                print(f"Failed to connect to PicoPLC via serial port {serial_port}")
            else:
                print(f"Successfully connected to PicoPLC via serial port {serial_port}")

    # ---- I/O Usage ---- #
    # I/O functions reads/writes 'n' registers from the 'start' address

    # Read registers %IX (code: 0x02)
    def read_inputs(self, start: int, n: int) -> list[bool]:
        return self.client.read_discrete_inputs(start, count=n, device_id=self.id).bits
    
    # Read registers %IW (code: 0x04)
    def read_analogue_inputs(self, start: int, n: int) -> list[int]:
        data = self.client.read_input_registers(start, count=n, device_id=self.id)
        # Convert received bits (16 per int) to integers
        return bits_to_ints(data.bits, 16)

    # Read registers %QX (code: 0x01)
    def read_outputs(self, start: int, n: int) -> list[bool]:
        return self.client.read_coils(start, count=n, device_id=self.id).bits

    # Read registers %QW (code: 0x03)
    def read_analogue_outputs(self, start: int, n: int) -> list[int]:
        data = self.client.read_holding_registers(start, count=n, device_id=self.id)
        return bits_to_ints(data.bits, 16)

    # Write registers %QX (code: 0x0F)
    def write_outputs(self, start: int, bits: list[bool]):
        self.client.write_coils(start, bits, device_id=self.id)

    # Write registers %QW (code: 0x10)
    def write_analogue_outputs(self, start: int, values: list[int]):
        self.client.write_registers(start, values, device_id=self.id)

    # Memory Registers:
    # read code: 0x03
    # write code: 0x10
    # I16 - address range 32-51
    # I32 - address range 52-91
    # I64 - address range 92-171
    offsets = { # Use Memory type enum to easily determine the correct offset
        MemoryType.I16: 32,
        MemoryType.I32: 52,
        MemoryType.I64: 92,
    }
    def read_memory(self, type: MemoryType, start: int, n: int) -> list[int]:
        offset = self.offsets[type]
        data = self.client.read_holding_registers(offset + start, count=n, device_id=self.id)
        return bits_to_ints(data.bits, type.value)

    def write_memory(self, type: MemoryType, start: int, values: list[int]):
        offset = self.offsets[type]
        self.client.write_registers(offset + start, values, device_id=self.id)

