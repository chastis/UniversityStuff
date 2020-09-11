from os import listdir
from os.path import isfile, join
import os
from PIL import Image
def get_cats():
    onlyfiles = [f for f in listdir('CAT_00') if isfile(join('CAT_00', f))]
    image_counter = 0
    for f in onlyfiles:
        if image_counter == 8001:
            break
        name, extension = os.path.splitext(join('CAT_00', f))
        if extension == '.jpg':
            img = Image.open(join('CAT_00', f))
            #resize
            # basewidth = 300
            # wpercent = (basewidth/float(img.size[0]))
            # hsize = int((float(img.size[1])*float(wpercent)))
            # img = img.resize((basewidth,hsize), Image.ANTIALIAS)
            width, height = img.size
            if height > width :
                tr = (height - width)/2.
                img = img.crop((0, tr, width, tr + width))
            else:
                tr = (width - height)/2.
                img = img.crop((tr, 0, tr + height, height))
            
            img = img.resize((256, 256), Image.ANTIALIAS)
            img.save('cats/' + 'cat_'+ str(image_counter) + '.jpg')
            image_counter += 1

def get_notcats():
    dirs0 = [ 'test', 'train']
    dirs1 = [ 'berry', 'bird', 'dog', 'flower', 'other']
    image_counter = 0
    for d0 in dirs0:
        for d1 in dirs1:
            path = 'notcats/' + d0 + '/' + d1
            onlyfiles = [f for f in listdir(path) if isfile(join(path, f))]
            for f in onlyfiles:
                img = Image.open(join(path, f))
                img.save('notcats/' + 'smth_'+ str(image_counter) + '.jpg')
                image_counter += 1
    

get_cats()
