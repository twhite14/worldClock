import json
import urllib
from apiKeys import * #accuweatherKey

locations =  ['State College', 'Tokyo', 'Santa Monica', 'Greenwich']
latitudes =  [40.7934,  35.6895,  34.0195,   51.4778]
longitudes = [-77.8600, 139.6917, -118.4912, -0.001472]

class thisURLOpener(urllib.FancyURLopener):
  version = 'trustmethisisntpython27'

urllib._urlopener = thisURLOpener()

baseRequest = 'http://apidev.accuweather.com/forecasts/v1/%s/%s/%s?apikey=%s' #% (type, frequency, key lat, long, accuweatherKey)

writeMe = ''
i = 0;

for place in locations:
  geoPos = 'http://apidev.accuweather.com/locations/v1/cities/geoposition.json?q=%f,%f&apikey=%s' % (latitudes[i], longitudes[i], accuweatherKey)
  geoPosJ = urllib.urlopen(geoPos).read()
  print geoPosJ
  geoPosP = json.loads(geoPosJ)
  key = geoPosP['Key']

  daily  = baseRequest % ('daily',   '1day', key, accuweatherKey)
  print daily
  print ''
  hourly = baseRequest % ('hourly', '1hour', key, accuweatherKey)
  print hourly
  print ''


  dailyJ = urllib.urlopen(daily).read()
  dailyP = json.loads(dailyJ)
  print dailyP
  min = dailyP['DailyForecasts'][0]['Temperature']['Minimum']['Value']
  max = dailyP['DailyForecasts'][0]['Temperature']['Maximum']['Value']
  hourlyJ = urllib.urlopen(hourly).read()
  hourlyP = json.loads(hourlyJ)
  precipProb = hourlyP[0]['PrecipitationProbability']

  max = int(max);
  min = int(min);
  precipProb = int(precipProb);

  if(max >= 100 and min >= 100):
    tempStr = "T:%3d/%3dF " % (max, min);
  elif(max < 0 and min < 0):
    tempStr = "T:%-2d/%-2dF " % (max, min);
  elif(max >= 100 and min < 0):
    tempStr = "T:%3d/%-2dF " % (max, min);
  elif(max >= 100 and min > 0):
    tempStr = " T:%3d/%2dF " % (max, min);
  elif(max < 100 and min < 0):
    tempStr = " T:%2d/%-2F " % (max, min);
  else:
    tempStr = "  T:%2d/%2dF " % (max, min);

  if(precipProb == 100):
    precipProb = 99;

  precipStr = "PRCP:%2d%%" % precipProb;
  writeMe = writeMe + tempStr + precipStr
  i += 1

with open("transfer.txt", "w") as transfer:
  transfer.write(writeMe)
