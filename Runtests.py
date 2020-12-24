from os import listdir
from os.path import isfile, join
import sys
import subprocess
mypath = 'Tests/'

def getCaller(name):
  return "gcc Polygonate.c Vector.c Tests/" + name + " cmocka/src/cmocka.c -Wall -o Tests/" + name[:name.find('.')]

def runFile(fl):
  subprocess.call(getCaller(fl))
  exCommand = "Tests/" + fl[:fl.find('.')] + ".exe"
  subprocess.call(exCommand)

if len(sys.argv) == 1:
  onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]
  for c_file in onlyfiles:
    if c_file.find('.c') != -1:
      runFile(c_file)
else:
  fl = sys.argv[1]
  runFile(fl)