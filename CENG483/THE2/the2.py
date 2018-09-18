import os 
import torch
import torchvision
import torch.optim as optim
import torch.nn as nn
import torch.nn.functional as F
import torch.utils.data as utils
import numpy as np
import pickle


train = torch.FloatTensor(np.load('train.npy'))
train_tensor = torch.stack([torch.Tensor(i) for i in train])

train_gt = torch.FloatTensor(np.load('train_gt.npy'))
train_gt_tensor = torch.stack([torch.Tensor(np.array(i)) for i in train_gt])

validation = torch.FloatTensor(np.load('valid.npy'))
validation_tensor = torch.stack([torch.Tensor(i) for i in validation])

photo = torch.FloatTensor(np.load('photo.npy'))
photo_tensor = torch.stack([torch.Tensor(i) for i in photo])

validation_gt = torch.FloatTensor(np.load('valid_gt.npy'))
validation_gt_tensor = torch.stack([torch.Tensor(np.array(i)) for i in validation_gt])

test = torch.FloatTensor(np.load('test.npy'))
test_tensor = torch.stack([torch.Tensor(i) for i in test])

test_dataset = utils.TensorDataset(test_tensor)
testloader = utils.DataLoader(test_dataset, batch_size=32)

train_dataset = utils.TensorDataset(train_tensor, train_gt_tensor)
trainloader = utils.DataLoader(train_dataset, batch_size=32)  

validation_dataset = utils.TensorDataset(validation_tensor, validation_gt_tensor)
validloader = utils.DataLoader(validation_dataset, batch_size=32)


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(512, 256)
        self.fc2 = nn.Linear(256, 128)
        self.fc3 = nn.Linear(128, 64)
        self.fc4 = nn.Linear(64, 1)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = self.fc4(x)
        return x



net = Net()

if os.path.isfile("net.pkl"): #Do not train if net exists
    net = pickle.load(open("net.pkl", "rb"))


criterion = nn.MSELoss()
optimizer = optim.RMSprop(net.parameters(), lr=1e-3, momentum=0.8)

for epoch in range(1000):  # loop over the dataset multiple times

    running_loss = 0.0
    for i, data in enumerate(trainloader, 0):
        # get the inputs
        inputs, labels = data
        
        labels = labels.view(-1,1)

        # zero the parameter gradients
        optimizer.zero_grad()

        # forward + backward + optimize
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        # print statistics
        running_loss += loss.item()
        if i % 100 == 99:    # print every 2500 mini-batches
            print('[%d, %5d] loss: %.3f' %
                  (epoch + 1, i + 1, running_loss / 100))
            running_loss = 0.0

    v_running_loss=0
    for j, v_data in enumerate(validloader, 0):
        v_inputs, v_labels = v_data
        v_labels = v_labels.view(-1,1)
        v_outputs = net(v_inputs)
        v_loss = criterion(v_outputs, v_labels)
        v_running_loss += v_loss.item()

    print(v_running_loss/100)



print('Finished Training')



correct = 0
total = 0
estimations_train = np.zeros([5000])
estimations_validation = np.zeros([2000])
estimations_test = np.zeros([2000])
i = 0
running_loss = 0



with torch.no_grad():
    for data in trainloader:
        images, labels = data
        outputs = net(images)
        predicted, _ = torch.max(outputs.data, 1)
        
        for prediction in predicted:
            estimations_train[i] = prediction 
            i+=1

correct = 0
total = 0
i = 0
running_loss = 0



with torch.no_grad():
    for data in validloader:
        images, labels = data
        outputs = net(images)
        predicted, _ = torch.max(outputs.data, 1)
        
        for prediction in predicted:
            estimations_validation[i] = prediction 
            i+=1

correct = 0
total = 0
i = 0
running_loss = 0


with torch.no_grad():
    for data in testloader:
        images = data[0]
        outputs = net(images)
        predicted, _ = torch.max(outputs.data, 1)
        
        for prediction in predicted:
            estimations_test[i] = prediction 
            i+=1

with torch.no_grad():
    output = net(photo_tensor)

    predicted, _ = torch.max(outputs.data, 1)

    total = 0
    for prediction in predicted:
        total += prediction

    print(total/50)

np.save('estimations_train.npy', estimations_train)
np.save('estimations_validation.npy', estimations_validation)
np.save('estimations_test.npy', estimations_test)
pickle.dump(net, open("net.pkl", "wb"))
