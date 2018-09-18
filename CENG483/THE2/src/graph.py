from matplotlib import pyplot as plt


filename = "losnew.txt"

with open(filename) as f:
    images = f.readlines()


loss = []
loss_valid = []
i=0
for item in images:
	if i < 1000:
		x = item.split("loss: ",1)[1]
		loss.append(float(x))
		i+=1
	elif i == 1000:
		i+=1
	else:
		x = item.split("loss: ",1)[1]
		loss_valid.append(float(x))



fig = plt.figure()
ax = fig.add_subplot(111)

A = range(1001)
A = A[1:]
plt.plot(A,loss, label='Training loss')
plt.plot(A, loss_valid, label='Validation loss')
#plt.plot(A,C)
#for xy in zip(A, loss):                                       # <--
#    ax.annotate('(%s, %s)' % xy, xy=xy, textcoords='data') # <--
#for xy in zip(A, C):                                       # <--
#    ax.annotate('(%s, %s)' % xy, xy=xy, textcoords='data')

legend = ax.legend(loc='upper center', shadow=False, fontsize='large')

plt.ylabel('loss')
plt.xlabel('epoch number')
plt.grid()
plt.show()