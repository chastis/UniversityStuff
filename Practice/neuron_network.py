from keras.datasets import fashion_mnist
from data_loader import *
(train_x,train_y), (test_x,test_y) = load_data()
import numpy as np
from keras.utils import to_categorical
import matplotlib.pyplot as plt


train_x = train_x.reshape(-1, PHOTO_SIZE, PHOTO_SIZE, CHANNELS)
test_x = test_x.reshape(-1, PHOTO_SIZE, PHOTO_SIZE, CHANNELS)
train_x = train_x.astype('float32')
test_x = test_x.astype('float32')
train_x = train_x / 255.
test_x = test_x / 255.

# Change the labels from categorical to one-hot encoding
train_y = to_categorical(train_y)
test_y = to_categorical(test_y)

print(train_x.shape, train_y.shape)
print(test_x.shape, test_y.shape)

import keras
from keras.models import Sequential,Input,Model
from keras.layers import Dense, Dropout, Flatten
from keras.layers import Conv2D, MaxPooling2D
from keras.layers.normalization import BatchNormalization
from keras.layers.advanced_activations import LeakyReLU
from keras.callbacks import ModelCheckpoint, EarlyStopping
epochs = 20
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

model.compile(loss=keras.losses.categorical_crossentropy, optimizer=keras.optimizers.Adam(),metrics=['accuracy'])

model.summary()


early_stopper = EarlyStopping(patience=5, verbose=1)
nn_save = 'model.h5'
check_pointer = ModelCheckpoint(nn_save, verbose=1, save_best_only=True)
train = model.fit(train_x, 
                  train_y, 
                  batch_size=BATCH_SIZE,
                  epochs=epochs,
                  verbose=1,
                  validation_data=(test_x, test_y),
                  callbacks=[check_pointer, early_stopper]
                  )



