#!/usr/bin/python

def generate_sdf(filename, old_string, new_string):
        s = open(filename).read()
        if old_string in s:
                s = s.replace(old_string, new_string);
                f = open(filename, 'w')
                f.write(s)
                f.flush()
                f.close()
        else:
                print('No ocurrences of "{old_string}" found.').format(**locals())

from subprocess import call
call(["./build/Release/tests"])
d = 0
for i in range(0, 360):
        for j in range(0,2):
                d += 1
                generate_sdf('sdfdatei.sdf', 'transform rsphere rotate ' + i, 'transform rsphere rotate ' + (i + 1))
                call(["./build/Release/tests"])
                call(["sips"], ["-s format png image.ppm --out anim/" + d ".png"])
                call(["rm"], ["image.ppm"])