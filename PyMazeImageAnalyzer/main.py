from PIL import Image
from Maze import Maze

def blackWhiteData(data):
    for i in range(0, len(data)):
        if data[i] != 0:
            data[i] = 1
    return data


im = Image.open("test.bmp")
width = im.size[0]
height = im.size[1]
data = list(im.getdata(0))
# data, pixels:
# 0 1 2 ... n
# n+1 n+2 ...
# ...
data = blackWhiteData(data)

print(width)
print(height)
print(data)

f = open('mazelist', 'w')
for i in range(0, height):
    for j in range(0, width):
        c = str(data[i*width + j])
        f.write(c)
    if (i != height-1):
        f.write(',')
f.close()
