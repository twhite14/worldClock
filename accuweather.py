import json
import urllib
from apiKeys import * #accuweatherKey, lat, long

class thisURLOpener(urllib.FancyURLopener):
  version = 'trustmethisisntpython27'

urllib._urlopener = thisURLOpener()

daily = 'http://apidev.accuweather.com/forecasts/v1/daily/1day/335315?apikey=c3e7df4f2d6a40698cc75fac1b6a2c83'

dailyJson = urllib.urlopen(daily).read()
dailyParsed = json.loads(dailyJson)
min = dailyParsed['DailyForecasts'][0]['Temperature']['Minimum']['Value']
max = dailyParsed['DailyForecasts'][0]['Temperature']['Maximum']['Value']


hourly = 'http://apidev.accuweather.com/forecasts/v1/hourly/1hour/335315?apikey=c3e7df4f2d6a40698cc75fac1b6a2c83'

hourlyJson = urllib.urlopen(hourly).read()
hourlyParsed = json.loads(hourlyJson)
precipProb =  hourlyParsed[0]['PrecipitationProbability']

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

rainStr = "PRCP:%2d%%" % precipProb;

with open("transfer.txt", "w") as transfer:
  transfer.write(tempStr + rainStr);
