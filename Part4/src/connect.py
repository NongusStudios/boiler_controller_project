from plc_modbus_interface import PLC_ModBusInterface

plc = PLC_ModBusInterface()
plc.connect()
if not plc.connected:
    exit()

