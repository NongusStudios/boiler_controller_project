from nicegui import ui
from connect import plc
from plc_modbus_interface import MemoryType
import time

# Globals
PLC_POLL_INTERVAL = 0.3
DISPLAY_COUNT = 6
MAX_SETTING = 10

temp_setting = 0
display = []
heating_status_display = None

class Circle(ui.element):
    def __init__(self, r: int, color: str):
        super().__init__("div")
        self.style(f"border-radius: 50%; width: {r}px; height: {r}px; background-color: {color};")
    def set_color(self, color: str):
        self.style(f"background-color: {color};")
        self.update()

def poll_plc():
    # Read LED display %QX0.1-6 and update HMI display 
    out = plc.read_outputs(1, 6)[:6]
    #out.reverse()

    i = 0
    for pin in out:
        if pin:
            display[i].set_color("orange")
        else:
            display[i].set_color("black")
        i += 1

    # Read status led
    if plc.read_outputs(7, 1)[0]:
        heating_status_display.set_color("green")
    else:
        heating_status_display.set_color("black")


def signal_register(addr: int):
    plc.write_memory(MemoryType.I16, addr, [1])
    time.sleep(0.02)                 # Janky method of simulating a button press
    plc.write_memory(MemoryType.I16, addr, [0])

def gui():
    global heating_status_display

    ui.page_title("Boiler Controller")

    with ui.header():
        ui.label("Boiler Controller").style("font-size: 16pt;")

    with ui.grid(columns=2):
        with ui.column(): # Control Column
            with ui.button_group():
                ui.button("Start/Stop", on_click=lambda: signal_register(0))
                ui.button("Emergency Stop", color="red", on_click=lambda: signal_register(1))
            ui.label("Temperature Control:")
            with ui.button_group():
                ui.button("-", color="red", on_click=lambda: signal_register(3))
                ui.button("+", color="green", on_click=lambda: signal_register(2)) 
            ui.label("Heating Status:")
            heating_status_display = Circle(32, "black")

        with ui.column(): # Display Column
            with ui.grid(columns=2).classes('items-center gap-4'):
                with ui.column().classes('gap-0 justify-between h-full'):
                    for i in range(0, MAX_SETTING+1):
                        ui.label(f"{180-i*10}")
                with ui.column().classes('gap-0 justify-between h-full'):
                    for i in range(0, DISPLAY_COUNT):
                        display.append(Circle(32, "black"))
    ui.timer(PLC_POLL_INTERVAL, poll_plc)
    ui.run(reload=False, show=False)

gui()