#!/usr/bin/env python
# 0 = wahr != 0 ist falsch
import sys

def return_as_set(fname):
  f = open(fname,"r")
  ret = set()
  for line in f:
    eq = []
    diag = []
    splitstr = line.split(':')
    tmpline = ['','',(),()]
    if ((splitstr[0] == 'E') or (splitstr[0] == 'Em') or (splitstr[0] == 'D') or (splitstr[0] == 'Dm')):
      tmpline[0] = splitstr[0]
      i = 1;
      if (splitstr[i] == 'EQ'):
        tmpline[i] = splitstr[i]
        i=i+1
      diagstr = splitstr[i].split('},{')
      diagstr[0] = diagstr[0][2:len(diagstr[0])]
      diagstr[1] = diagstr[1][0:len(diagstr[1])-2]
      for diax in diagstr:
        diag.append(frozenset(diax.split(',')))
    if ((splitstr[0] == 'EQ') or (splitstr[1] == 'EQ')):
      tmpline[1] = 'EQ'
      eqstr = splitstr[len(splitstr)-1].split('},{')
      eqstr[0] = eqstr[0][2:len(eqstr[0])]
      eqstr[len(eqstr)-1] = eqstr[len(eqstr)-1][0:(eqstr[len(eqstr)-1].find('})'))]
      for eqx in eqstr:
        eq.append(frozenset(eqx.split(',')))
    ret.add( (tuple(eq),tuple(diag)) )
  f.close()
  return ret

reff = sys.argv[1]
outf = sys.argv[2]

ref = return_as_set(reff)
out = return_as_set(outf)

if ref == out:
  sys.exit(0) #true

print >>sys.stderr, "outputs differ:"
print >>sys.stderr, "reference="
print >>sys.stderr, ref
print >>sys.stderr, "out="
print >>sys.stderr, out

sys.exit(-1) #false
