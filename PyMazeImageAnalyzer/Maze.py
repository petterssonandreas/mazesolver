class Maze:
    def __init__(self, im):
        width = im.size[0]
        height = im.size[1]
        data = list(im.getdata(0))
        # data, pixels:
        # 0 1 2 ... n
        # n+1 n+2 ...
        # ...
