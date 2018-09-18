import os 
import torch
import torchvision
import torch.optim as optim
import torch.nn as nn
import torch.nn.functional as F
import torch.utils.data as utils
import torchvision.transforms as transforms
import numpy as np
from skimage import io, color
from skimage.transform import rescale
import pickle

batchsize = 32

filename = "train.txt"

with open(filename) as f:
    train_imagenames = f.readlines()

train_imagenames = [x.strip() for x in train_imagenames]

train_L_images = np.ndarray(shape=(800, 1, 256, 256))
train_ab_images = np.ndarray(shape=(800, 256, 256, 2))

i=0

for file in train_imagenames:
    img = io.imread("gray/" + file)
    if len(img.shape) == 2:
        img = np.stack([img, img, img], 2)
        Lab = color.rgb2lab(img)
        L = Lab[:, :, 0]
        train_L_images[i][0] = np.stack(L)
        ab = Lab[:, :, 1:]
        train_ab_images[i] = np.stack(ab)
        i+=1


train64_L_images = np.ndarray(shape=(800, 1, 64, 64))
train64_ab_images = np.ndarray(shape=(800, 64, 64, 2))

i=0

for file in train_imagenames:
    img = io.imread("color_64/" + file)
    color.rgb2lab(img)
    Lab = color.rgb2lab(img)
    L = Lab[:, :, 0]
    train64_L_images[i][0] = np.stack(L)
    ab = Lab[:, :, 1:]
    train64_ab_images[i] = np.stack(ab)
    i+=1


filename = "valid.txt"
with open(filename) as f:
    validation_imagenames = f.readlines();

validation_imagenames = [x.strip() for x in validation_imagenames]

validation_L_images = np.ndarray(shape=(100, 1, 256, 256))
validation_ab_images = np.ndarray(shape=(100, 256, 256, 2))

i = 0

for file in validation_imagenames:
    img = io.imread("gray/" + file)
    if len(img.shape) == 2:
        img = np.stack([img, img, img], 2)
        Lab = color.rgb2lab(img)
        L = Lab[:, :, 0]
        validation_L_images[i][0] = np.stack(L)
        ab = Lab[:, :, 1:]
        validation_ab_images[i] = np.stack(ab)
        i+=1


validation64_L_images = np.ndarray(shape=(100, 1, 64, 64))
validation64_ab_images = np.ndarray(shape=(100, 64, 64, 2))

i = 0

for file in validation_imagenames:
    img = io.imread("color_64/" + file)
    Lab = color.rgb2lab(img)
    L = Lab[:, :, 0]
    validation64_L_images[i][0] = np.stack(L)
    ab = Lab[:, :, 1:]
    validation64_ab_images[i] = np.stack(ab)
    i+=1

validation256_L_images = np.ndarray(shape=(100, 1, 256, 256))
validation256_ab_images = np.ndarray(shape=(100, 256,256,2))

i = 0

for file in validation_imagenames:
    img = io.imread("color_256/" + file)
    Lab = color.rgb2lab(img)
    L = Lab[:, :, 0]
    validation256_L_images[i][0] = np.stack(L)
    ab = Lab[:, :, 1:]
    validation256_ab_images[i] = np.stack(ab)
    i+=1


filename = "test.txt"
with open(filename) as f:
    test_imagenames = f.readlines();

test_imagenames = [x.strip() for x in test_imagenames]

test_L_images = np.ndarray(shape=(100, 1, 256, 256))
test_ab_images = np.ndarray(shape=(100, 256, 256, 2))

i = 0

for file in test_imagenames:
    img = io.imread("test_gray/" + file)
    if len(img.shape) == 2:
        img = np.stack([img, img, img], 2)
        Lab = color.rgb2lab(img)
        L = Lab[:, :, 0]
        test_L_images[i][0] = np.stack(L)
        ab = Lab[:, :, 1:]
        test_ab_images[i] = np.stack(ab)
        i+=1



train_tensor = torch.FloatTensor(train_L_images)
train_gt_tensor = torch.FloatTensor(train64_ab_images)


validation_tensor = torch.FloatTensor(validation_L_images)
validation_gt_tensor = torch.FloatTensor(validation64_ab_images)

test_tensor = torch.FloatTensor(test_L_images)

train_dataset = utils.TensorDataset(train_tensor, train_gt_tensor)
trainloader = utils.DataLoader(train_dataset, batch_size=batchsize)

validation_dataset = utils.TensorDataset(validation_tensor, validation_gt_tensor)
validloader = utils.DataLoader(validation_dataset, batch_size=batchsize)

test_dataset = utils.TensorDataset(test_tensor)
testloader = utils.DataLoader(test_dataset, batch_size=batchsize)

print("Started Training")

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1, 16, 5, padding=2)
        self.pool = nn.MaxPool2d(2, 2)
        self.bn = nn.BatchNorm2d(16)
        self.conv2 = nn.Conv2d(16, 24, 3, padding=1)
        self.bn2 = nn.BatchNorm2d(24)
        self.conv3 = nn.Conv2d(24, 2, 3, padding=1)

    def forward(self, x):
        x = self.conv1(x)
        x = self.pool(x)
        x = self.bn(x)
        x = F.relu(x)
        x = self.conv2(x)
        x = self.pool(x)
        x = self.bn2(x)
        x = F.relu(x)
        x = self.conv3(x)
        #x = x.view(1, 64, 64 , 2)
        return x


net = Net()

if os.path.isfile("net.pkl"): # Load net if it exists in the same directory
    net = pickle.load(open("net.pkl", "rb"))

criterion = nn.MSELoss()
optimizer = optim.RMSprop(net.parameters(), lr=1e-5, momentum=0.9)

for epoch in range(1):  # loop over the dataset multiple times

    running_loss = 0.0
    for i, data in enumerate(trainloader, 0):
        # get the inputs
        inputs, labels = data

        # zero the parameter gradients
        optimizer.zero_grad()

        # forward + backward + optimize
        outputs = net(inputs)
        labels = labels.view(batchsize, 2, 64, 64)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        # print statistics
        running_loss += loss.item()

    print(running_loss/25)
    
    v_running_loss=0
    for j, v_data in enumerate(validloader, 0):
        v_inputs, v_labels = v_data
        v_outputs = net(v_inputs)
        shape = v_labels.shape
        v_labels = v_labels.view(shape[0], 2, 64, 64)
        v_loss = criterion(v_outputs, v_labels)
        v_running_loss += v_loss.item()
    
    print(v_running_loss/3)
    
print("Finished Training")

correct = 0
total = 0
estimations_validation = np.zeros(shape=(100, 256, 256, 3))
estimations_test = np.zeros(shape=(100, 256, 256, 3))
i = 0



with torch.no_grad():
    for data in validloader:
        images, labels = data
        outputs = net(images)

        for prediction in outputs.data:
            prediction = prediction.double()
            prediction = prediction.view(64, 64, 2)
            ab = rescale(prediction, 4, mode='constant', order=3)
            Lab = np.zeros(shape=(256,256,3))
            Lab[:,:,0] = validation_L_images[i]
            Lab[:,:,1:] = ab
            colored_img = color.lab2rgb(Lab)
            estimations_validation[i] = colored_img*255 
            i+=1


i = 0

with torch.no_grad():
    for data in testloader:
        images = data[0]
        outputs = net(images)

        for prediction in outputs.data:
            prediction = prediction.double()
            prediction = prediction.view(64, 64, 2)
            ab = rescale(prediction, 4, mode='constant', order=3)
            Lab = np.zeros(shape=(256,256,3))
            Lab[:,:,0] = test_L_images[i]
            Lab[:,:,1:] = ab
            colored_img = color.lab2rgb(Lab)
            estimations_test[i] = colored_img*255 
            i+=1

np.save('estimations_test.npy', estimations_test)

np.save('estimations_validation.npy', estimations_validation)

pickle.dump(net, open("net.pkl", "wb"))

