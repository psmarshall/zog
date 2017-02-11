# Take a gozz program and make it human readable.
# Also encodes human readable programs into GozzLang
# when you provide a second argument.

from sys import argv

encode = False
if len(argv) == 3:
  script, filename, _ = argv
  encode = True;
else:
  script, filename = argv

txt = open(filename)

str = txt.read()

list = []
list.append(('Gozz@', 'putchar'))
list.append(('Gozz$', 'putint'))
list.append(('@Gozz', 'readchar'))
list.append(('$Gozz', 'readint'))
list.append(('Gozz&', 'swap'))
list.append(('Gozz:', 'function:'))
list.append(('Gozz!', 'endFunction'))
list.append(('Gozz>', 'loop'))
list.append(('<Gozz', 'endLoop'))
list.append(('Gozz?', 'if'))
list.append(('Gozz/', 'return'))

list.append(('Gozz', 'f1()'))
list.append(('GozZ', 'f2()'))
list.append(('GoZz', 'f3()'))
list.append(('GoZZ', 'f4()'))
list.append(('GOzz', 'f5()'))
list.append(('GOzZ', 'f6()'))
list.append(('GOZz', 'f7()'))
list.append(('GOZZ', 'dupe'))

list.append(('gozz', 'add'))
list.append(('gozZ', 'sub'))
list.append(('goZz', 'div'))
list.append(('goZZ', 'mult'))
list.append(('gOzz', 'not'))
list.append(('gOzZ', 'equals'))
list.append(('gOZz', 'and'))
list.append(('gOZZ', 'or'))

for i, (gozz, human) in enumerate(list):
  if encode:
    str = str.replace(human, gozz)
  else:
    str = str.replace(gozz, human)

print str
