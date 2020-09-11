import PIL 
import numpy as np
from os import listdir
from os.path import isfile, join
import random
from PIL import Image
TRAIN_PART = 0.7
BATCH_SIZE = 4
PHOTO_SIZE = 256
CHANNELS = 3

def load_photo(f, iscat):
    img = None
    if iscat:
        img = Image.open(join('cats', f))
    else:
        img = Image.open(join('notcats', f))
    data = np.asarray(img)
    return data


def load_data():
    photos = np.empty(0)
    cats = [(f, 1) for f in listdir('cats') if isfile(join('cats', f))]
    notcats = [(f, 0) for f in listdir('notcats') if isfile(join('notcats', f))]

    notcats = notcats[:2000]
    cats = cats[:2000]

    all = cats + notcats
    random.shuffle(all)

    all_x = np.empty(0)
    all_y = np.empty(0)

    temp_count = 0
    for a in all:
        all_x = np.append(all_x, load_photo(a[0], a[1]))
        all_y = np.append(all_y, a[1])
        if (temp_count % 100 == 0):
            print ('progress ... ' + str(temp_count) + ' from ' + str(len(all)))
        temp_count += 1

    current_len = len(all_y)
    train_len_y = (int)(current_len * TRAIN_PART)//BATCH_SIZE*BATCH_SIZE
    train_len_x = train_len_y*CHANNELS*PHOTO_SIZE**2 
    valid_len_y = (current_len - train_len_y)//BATCH_SIZE*BATCH_SIZE
    valid_len_x = valid_len_y*CHANNELS*PHOTO_SIZE**2
    train_x = all_x[:train_len_x]
    train_y = all_y[:train_len_y]
    valid_x = all_x[train_len_x:train_len_x + valid_len_x]
    valid_y = all_y[train_len_y:train_len_y + valid_len_y]
    return (train_x, train_y), (valid_x, valid_y)
