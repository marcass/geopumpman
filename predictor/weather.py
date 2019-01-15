import pyowm
import creds

owm = pyowm.OWM(creds.key)  # You MUST provide a valid API key

# Have a pro subscription? Then use:
# owm = pyowm.OWM(API_key='your-API-key', subscription_type='pro')

  # {
  #   "id": 7910038,
  #   "name": "Dunedin City",
  #   "country": "NZ",
  #   "coord": {
  #     "lon": 170.243683,
  #     "lat": -45.640511
  #   }
  # },

# observation = owm.weather_at_place('Dunedin City,NZ')
observation = owm.weather_at_id(7910038)

w = observation.get_weather()
# print(w)                      # <Weather - reference time=2013-12-18 09:20,
                              # status=Clouds>

# Weather details
wind = w.get_wind()                  # {'speed': 4.6, 'deg': 330}
# print(wind)
w.get_humidity()              # 87
temp = w.get_temperature('celsius')  # {'temp_max': 10.5, 'temp': 9.7, 'temp_min': 9.0}
print(temp)

# Search current weather observations in the surroundings of
# lat=22.57W, lon=43.12S (Rio de Janeiro, BR)
# observation_list = owm.weather_around_coords(-22.57, -43.12)

# Get forecast
fc = owm.three_hours_forecast('Dunedin, NZ')
f = fc.get_forecast()

sunny = fc.when_sun()
print(sunny)
