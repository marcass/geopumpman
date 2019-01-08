# geopumpman
Manage climate in home using a geothermal heatpump, solvers, predictive weather models and PID control

## Components

### Software

* Predictor of thermal requirements
   * Weather data, eg https://pypi.org/project/weather-api/
* Observer of climate conditions, eg https://github.com/marcass/esp32-sensornet
   * Temperature sensors
      * In slab
      * In lower storey/upper storey
      * Outside
   * Lux sensors (light ingress)
* Controller of heating/cooling plant
   * PID control on heating/cooling demand
   * Solvers, eg https://github.com/Pyomo
   * Extended Kalman filter?
* Heating/cooling plant
   * Fail-safes
* UI (web?)

### Hardware
* Comission ground source heatpump
* containerise software for easier hardware transition 
* Standard brain running linux

# Links
* https://www.researchgate.net/publication/327136772_A_Python-Based_Toolbox_for_Model_Predictive_Control_Applied_to_Buildings
* https://filterpy.readthedocs.io/en/latest/kalman/ExtendedKalmanFilter.html
