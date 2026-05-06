import datetime
import time

test = str(datetime.date.today())

logfile = "Resistance-Log-" + test

# print(logfile)

hello = datetime.datetime.now().isoformat(sep='-',timespec='minutes')

print(hello)

currentTime = datetime.datetime.now()
testNew = currentTime.strftime("%H:%M")

# print(testNew)