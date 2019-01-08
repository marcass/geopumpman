# geopumpman
Manage climate in home using a geothermal heatpump, solvers, predictive weather models and PID control

## Components
* Predictor of thermal requirements
   * Weather data
* Observer of climate conditions
   * Temperature sensors
      * In slab
      * In lower storey/upper storey
      * Outside
   * Lux sensors (light ingress)
* Controller of heating/cooling plant
   * PID control on heating/cooling demand
   * Solvers, eg https://github.com/Pyomo
* Heating/cooling plant
   * Fail-safes
