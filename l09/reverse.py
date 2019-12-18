import sys

with open(sys.argv[1], 'rb') as f:
    with open(sys.argv[2], 'wb') as ff:
        ff.write(bytes(reversed(f.read())))
