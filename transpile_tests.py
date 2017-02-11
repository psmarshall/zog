# Use gozzer.py to transpile all .human files in the
# programs folder into .gozz files.

import glob
from subprocess import check_output

human_files = glob.glob("programs/*.human")

for file in human_files:
  #print file
  new_file_path = file[:-5]
  new_file_path += "gozz"
  #print " --> " + new_file_path
  gozzified = check_output(["python", "gozzer.py", file, "decode"])
  new_file = open(new_file_path, "w")
  new_file.write(gozzified)