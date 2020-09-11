import PIL 
import numpy as np
from os import listdir
from os import path
from os.path import isfile, join
from PIL import Image
from data_loader import *

def load_photo_from_file(filepath):
    try:
        img = None
        try:
            img = Image.open(filepath)
        except Exception:
            img = Image.open('cat.jpg')
        
        width, height = img.size
        if height > width :
            tr = (height - width)/2.
            img = img.crop((0, tr, width, tr + width))
        else:
            tr = (width - height)/2.
            img = img.crop((tr, 0, tr + height, height))
        
        img = img.resize((256, 256), Image.ANTIALIAS)
        return np.asarray(img).reshape(1, PHOTO_SIZE, PHOTO_SIZE, CHANNELS)
    except Exception:
        return np.empty(0)

import keras
from keras.models import Sequential,Input,Model
from keras.layers import Dense, Dropout, Flatten
from keras.layers import Conv2D, MaxPooling2D
from keras.layers.normalization import BatchNormalization
from keras.layers.advanced_activations import LeakyReLU
from keras.callbacks import ModelCheckpoint, EarlyStopping

def predict(path):
    num_classes = 2
    model = Sequential()
    model.add(Conv2D(32, kernel_size=(3, 3),activation='linear',input_shape=(PHOTO_SIZE, PHOTO_SIZE, CHANNELS),padding='same'))
    model.add(LeakyReLU(alpha=0.1))
    model.add(MaxPooling2D((2, 2),padding='same'))
    model.add(Conv2D(64, (3, 3), activation='linear',padding='same'))
    model.add(LeakyReLU(alpha=0.1))
    model.add(MaxPooling2D(pool_size=(2, 2),padding='same'))
    model.add(Conv2D(128, (3, 3), activation='linear',padding='same'))
    model.add(LeakyReLU(alpha=0.1))                  
    model.add(MaxPooling2D(pool_size=(2, 2),padding='same'))
    model.add(Conv2D(256, (5, 5), activation='linear',padding='same'))
    model.add(LeakyReLU(alpha=0.1))                  
    model.add(MaxPooling2D(pool_size=(4, 4),padding='same'))
    model.add(Flatten())
    model.add(Dense(256, activation='linear'))
    model.add(LeakyReLU(alpha=0.1))                  
    model.add(Dense(num_classes, activation='softmax'))
    nn_save = 'model.h5'
    model.load_weights(nn_save)
    model.compile(loss=keras.losses.categorical_crossentropy, optimizer=keras.optimizers.Adam(),metrics=['accuracy'])
    data = load_photo_from_file(path)
    if (not data.size):
        return False
    results = model.predict(data, batch_size=1, verbose=0)

    return results[0, 1] > 0.5
