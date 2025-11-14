# Summary

The documentation provided in this repository is my work submitted for the Automation and Embedded Systems course I took at EIT.
Each part is a different deliverable.<br>
The case-study was on a controller for an industrial water boiler, where we had to implement:

- controls for changing the heat setting, and starting/stoping heating.
- 6 LED display for communicating the current setting and temperature.
- A bang-bang PID control loop to keep the temperature at the sent-point.
- A servo representing a water valve, opening and closing at a rate of 18 deg/s when heating is off/on.
- Emergency stop mechanism for safety purposes.

We didn't actually have access to a boiler, so I simulated temperature to test the control loop.

- Using real world physics equations in part 2.
- Using simple linear equation in part 3, because implementing real world physics in FBD is silly.

I had an idea to modify a cheap electric kettle, but ran out of time and it was outside of the assessments scope.

## Documentation

- [Part 1](Part1/Part1.md)
- [Part 2](Part2/Part2.md)
- [Part 3](Part3/Part3.md)
- [Part 4](Part4/Part4.md)
