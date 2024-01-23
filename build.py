"""Compiles files in src and tests"""

import subprocess
import os
import sys

flags = "-std=c++23 -fdiagnostics-color -Wall -Wno-padded"
units = ["src/lib", "src/char", "test/main"]
names = [unit.split("/").pop() for unit in units]

if not os.path.exists("build"):
    os.makedirs("build")

error = False
for (unit, name) in zip(units, names):
    cmd = f"sccache g++ -c {flags} {unit}.cpp -o build/{name}.o"
    result = subprocess.call(cmd, shell = True)
    if result != 0:
        error = True

if not error:
    paths = " ".join([f"build/{name}.o" for name in names])
    cmd = f"sccache g++ {paths} -o build/test"
    subprocess.call(cmd, shell=True)
else:
    sys.exit(-1)
