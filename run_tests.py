# Run all tests in programs/.

import glob
from subprocess import check_output, CalledProcessError
from sys import argv
from os.path import isfile

script, binary = argv

gozz_files = glob.glob("programs/*.gozz")



failed = 0
passed = 0

for test_file in gozz_files:
  expect_file_path = test_file[:-4]
  expect_file_path += "expect"

  try:
    actual_output = check_output([binary, test_file])
  except CalledProcessError, e:
    actual_output = e.output

  if isfile(expect_file_path):
    expected = open(expect_file_path, "r").read()
  else:
    expected = ""

  if expected != actual_output:
    failed += 1
    if expected == "":
      print "Failed! " + test_file + " Expected nothing, got:"
      print actual_output
    else:
      print "Failed! " + test_file + " Expected:"
      print expected
      print "Got:"
      print actual_output
  else:
    passed += 1
    print "Passed! " + test_file

print
print "{} / {} tests passed.".format(passed, passed + failed)