from PIL import Image
import os, math, time, sys

def main(path, numberOfTypes):
    frames = []

    files = os.listdir(path)
    for file in files:
        try:
            with Image.open(path+"/"+file) as image:
                frames.append(image.getdata())
        except:
            print('Error opening file:', path+"/"+file)

    tile_width = frames[0].size[0]
    tile_height = frames[0].size[0]

    total_width = tile_width * numberOfTypes
    total_height = tile_height * math.ceil(len(frames) // numberOfTypes)

    spritesheet = Image.new("RGBA", (total_width, total_height))
    x = y = 0
    for frame in frames:
        
        box = (x, y, x+tile_width, y+tile_height)
        cropped_frame = frame.crop(
            (0,0, int(tile_width),int(tile_height)))
        spritesheet.paste(cropped_frame, box)
        
        x += tile_width
        if x >= total_width:
            x = 0
            y += tile_height

    try:
        spritesheet.save(path+"/spritesheet.png", "PNG")
    except:
        print('Error saving file:',path+"/spritesheet.png")


if __name__ == '__main__':
    try:
        main(sys.argv[-2], int(sys.argv[-1]))
    except:
        try:
            main(input('Spritesheet directory (no trailing slash): '),
                 int(input('Number of sprite types: ')))
        except:
            print('Error in inputs.')
