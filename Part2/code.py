import time
import digitalio
import board
import pwmio
from adafruit_motor import servo

def clamp(v, m, ma):
    if v > ma:
        return ma
    elif v < m:
        return m
    return v

# shared data
heating_on = False
element_on = False

TEMP_SETTING_COUNT = 11
temperature_setting = 0

# --- Simulation Constants ---
BASE_TEMP = 21.0    # Ambient temperature (°C)
MASS = 100.0        # Mass of water (kg)
C_P = 4180.0        # Specific heat capacity of water (J/kg·K)

# --- Heating & Cooling Parameters ---
HEATING_POWER_WATTS = 2800.0*1000.0  # J/s (2800 kW) Insanely powerful

# Un-realistic cooling time for testing (5 min)
COOLING_TIME_CONSTANT = 5.0*60.0  # seconds (tau)

raw_temperature = BASE_TEMP

def simulate_temperature(dt):
    global raw_temperature, element_on
    if dt <= 0:
        return
        
    # 1. Calculate energy ADDED by heater (Joules)
    energy_in = HEATING_POWER_WATTS * int(element_on) * dt
    
    # 2. Calculate energy LOST to environment (Joules)
    # Newton's Law of Cooling: Q_out = (m * c_p / τ) * (T - T_amb) * dt
    energy_out = (MASS * C_P / COOLING_TIME_CONSTANT) * (raw_temperature - BASE_TEMP) * dt
    
    # 3. Calculate net energy change
    net_energy = energy_in - energy_out
    
    # 4. Convert energy change to temperature change
    # ΔT = Q_net / (m * c_p)
    delta_temp = net_energy / (MASS * C_P)
    
    raw_temperature += delta_temp
    raw_temperature = max(BASE_TEMP, raw_temperature)

def get_setpoint() -> float:
    return 80.0 + temperature_setting * 10

class Process:
    # 'elapsed' is the elapsed time in seconds between executions
    def __init__(self, elapsed: float):
        self.elapsed = elapsed
        # time since last execution
        self.since = 0.0

    # returns true when enough time has elapsed
    def increment(self, dt: float) -> bool:
        self.since += dt
        return self.since >= self.elapsed
    
    def reset(self):
        self.since = 0.0

    def execute(self):
        pass

class ButtonState:
    PRESSED = 0
    RELEASED = 1
    DEBOUNCE = 2

class Button:
    DEBOUNCE_THRESHOLD = 0.02 # Time (s) to wait for button output to stabilise
    COOLDOWN = 0.2 # Time (s) to wait after an event before polling again

    def __init__(self, pin):
        self.btn = digitalio.DigitalInOut(pin)
        self.btn.direction = digitalio.Direction.INPUT
        self.btn.pull = digitalio.Pull.DOWN
        self.state = ButtonState.RELEASED
        self.debounce_timer = 0.0
        self.cooldown = 0.0
        self.last_raw_value = False

    def poll(self, since) -> int:
        """
        Args:
            since: time since last call to pressed
        """
        # wait for cooldown after event
        if self.cooldown > 0.0:
            self.cooldown -= since
            return -1

        current_value = self.btn.value
        is_press_event = (self.state == ButtonState.RELEASED and current_value)
        is_release_event = (self.state == ButtonState.PRESSED and not current_value)                    
        if is_press_event or is_release_event:
                self.debounce_timer = self.DEBOUNCE_THRESHOLD
                self.state = ButtonState.DEBOUNCE
                self.last_raw_value = current_value
        elif self.state == ButtonState.DEBOUNCE:
            if current_value != self.last_raw_value:
                # Check for instability and reset
                self.debounce_timer = self.DEBOUNCE_THRESHOLD
                self.last_raw_value = current_value

            if self.debounce_timer > 0.0:
                self.debounce_timer -= since
            else:
                if current_value:
                    #print("DEBOUNCE resolved to PRESSED. Triggering event.")
                    self.state = ButtonState.PRESSED
                    self.cooldown = self.COOLDOWN # set cooldown
                else:
                    self.state = ButtonState.RELEASED
                    #print("DEBOUNCE resolved to RELEASED. Triggering event.")

                return self.state
        return -1

class PID:
    def __init__(self, Kp: float, Ki: float, Kd: float, setpoint: float, output_limits=(0, 1)):
        self.Kp = Kp
        self.Ki = Ki
        self.Kd = Kd
        self.setpoint = setpoint
        self.output_limits = output_limits  # Clamp output between 0 (0%) and 1 (100%)
        
        # Initialize state variables
        self.integral = 0
        self.previous_error = 0

    def compute(self, process_variable: float, dt: float): # dt: Delta Time, time since last compute.
        # Calculate error
        error = self.setpoint - process_variable
        
        # Proportional term
        P = self.Kp * error
        
        # Integral term
        self.integral += error * dt
        I = self.Ki * self.integral
        
        # Derivative term
        derivative = (error - self.previous_error) / dt
        D = self.Kd * derivative
        self.previous_error = error
        
        # Calculate and clamp total output
        output = P + I + D
        output = clamp(output, self.output_limits[0], self.output_limits[1])
        
        # Anti-windup: Clamp the integral term if output is saturated
        if output == self.output_limits[0] or output == self.output_limits[1]:
            # Stop integrating if we are at the output limit
            self.integral -= error * dt 
        
        return output

class InputHandler(Process):
    """
    A process for handling buttons and builtin debouncing.
    """

    def __init__(self, pins, cb):
        """
        Args:
            pins: List of input pins to poll
            cb: Callback function to execute when a pin goes low -> high
                This function should take the following args:
                    pin: An integer that describes which pin was activated by index
                    state: ButtonState
        """
        super().__init__(0.01) # Poll pins every frame
        self.callback = cb
        self.btns = []
        for pin in pins:
            self.btns.append(Button(pin))
    
    def execute(self):
        idx = 0
        for btn in self.btns:
            state = btn.poll(self.since)
            if state != -1:
                self.callback(idx, state)
            idx += 1

status_led = digitalio.DigitalInOut(board.GP16)
status_led.direction = digitalio.Direction.OUTPUT

def round_to(n, mult):
    return mult * round(n/mult)

# Handles 6 LED display
class Display(Process):
    TEMP_SETTING_LUT = [
        [1, 0, 0, 0, 0, 0], # 80C
        [1, 1, 0, 0, 0, 0], # 90C
        [0, 1, 0, 0, 0, 0], # 100C
        [0, 1, 1, 0, 0, 0], # 110C
        [0, 0, 1, 0, 0, 0], # 120C
        [0, 0, 1, 1, 0, 0], # 130C
        [0, 0, 0, 1, 0, 0], # 140C
        [0, 0, 0, 1, 1, 0], # 150C
        [0, 0, 0, 0, 1, 0], # 160C
        [0, 0, 0, 0, 1, 1], # 170C
        [0, 0, 0, 0, 0, 1]  # 180C
    ]

    def __init__(self):
        super().__init__(0.1)
        pins = [board.GP15, # led 1
                    board.GP14, # led 2
                    board.GP13, # led 3
                    board.GP12, # led 4
                    board.GP11, # led 5
                    board.GP10] # led 6 
        self.leds = [digitalio.DigitalInOut(pin) for pin in pins]
        for led in self.leds:
            led.direction = digitalio.Direction.OUTPUT
    
    def execute(self):
        global temperature_setting, heating_on, raw_temperature
        
        idx = temperature_setting
        rnd_temp = round_to(raw_temperature, 10)
        if heating_on and rnd_temp >= 80:
            temp = clamp(rnd_temp, 80, 180) # Round to nearest 10 and clamp between settings to avoid out-of bounds list access
            idx = int((temp - 80) / 10) # turn rounded temp into an index for LUT
        elif heating_on: # Don't show a reading until temperature has reached 80
            for led in self.leds:
                led.value = 0
            return

        for led, set in zip(self.leds, self.TEMP_SETTING_LUT[idx]):
            led.value = set
        
class Valve(Process):
    CLOSE_ANGLE = 0
    OPEN_ANGLE = 180 * 0.80 # 80% of max angle
    RATE = 18 # 18deg/s

    def __init__(self):
        super().__init__(0.05)
        self.pwm = pwmio.PWMOut(board.GP20, duty_cycle=2**16-1, frequency=50)
        self.valve = servo.Servo(self.pwm)
        self.valve.angle = self.CLOSE_ANGLE
        self.angle = self.CLOSE_ANGLE
    
    def execute(self):
        global heating_on
        if heating_on and self.angle != self.OPEN_ANGLE:
            self.angle += self.RATE * self.since
        elif self.angle != self.CLOSE_ANGLE:
            self.angle -= self.RATE * self.since
        else:
            return # The angle shouldn't be updated when it doesn't need to be.
        self.angle = clamp(self.angle, self.CLOSE_ANGLE, self.OPEN_ANGLE)
        self.valve.angle = self.angle

class TempControl(Process):
    def __init__(self):
        super().__init__(0.01)
        self.pid = PID(2.0, 0.1, 1.5, 80.0)
    
    def execute(self):
        global heating_on, element_on

        if heating_on:
            self.pid.setpoint = get_setpoint()
            element_on = bool(self.pid.compute(raw_temperature, self.since))
        else:
            element_on = False


def on_off_cb(pin, state):
    global heating_on, status_led, temperature_setting
    if state == ButtonState.PRESSED:
        heating_on = not heating_on
        status_led.value = heating_on

def set_temp_cb(pin, state):
    global temperature_setting
    diff = [-1, 1]
    if state == ButtonState.PRESSED and not heating_on:
        temperature_setting = clamp(temperature_setting + diff[pin], 0, TEMP_SETTING_COUNT-1)

# list of active processes
processes = [
    InputHandler([board.GP17], on_off_cb),
    InputHandler([board.GP18, board.GP19], set_temp_cb),
    Display(),
    Valve(),
    TempControl()
]

last = time.monotonic()
elapsed = 0.0
while True:
    now = time.monotonic()
    dt = now - last
    last = now

    simulate_temperature(dt)
    print(f"\r{raw_temperature}    ", end='')

    for process in processes:
        if process.increment(dt):
            process.execute()
            process.reset()


