import sys
import os
import cv2
import numpy as np
import pickle
from sklearn.cluster import *
from scipy.spatial import distance
from cyvlfeat.sift import *

class image:


    def __init__(self, name, descriptor, histogram):
        self.name = name
        self.descriptor = descriptor
        self.histogram = histogram
        


    def vision(feature_des, k):

        filename = "images.dat"

        with open(filename) as f:
            images = f.readlines()           #Read the name of each image 

        images = [x.strip() for x in images]

        descriptors = np.ndarray(shape=(0,128))

        imagelist = []

        for item in images:

            img = cv2.imread('dataset/' + item)
            gray= cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
            
            if(feature_des == "SIFT"):
                sift = cv2.xfeatures2d.SIFT_create(1000) 
            
                keypoints = sift.detect(gray,None)
            
                cv2.drawKeypoints(gray,keypoints,img)
            
                keypoints, des = sift.detectAndCompute(gray,None)

            else:
                keypoints, des = dsift(gray,step=10) 

            
            if(len(keypoints) == 0):
                tmp = np.zeros(128, "float32")
                des = np.reshape(tmp, (1,128))

            image_obj = image(item, des, [])
            imagelist.append(image_obj)
        
            descriptors = np.concatenate((descriptors,des))


        # K-means Clustering
        #clusters = KMeans(k, random_state=0).fit(descriptors)  # Perform K means using default values
        clusters = MiniBatchKMeans(k, random_state=0).fit(descriptors)

        pickle.dump(clusters, open("clusters.pkl", "wb"))

        # Calculate histogram of features
        for i in range(len(images)):
            features = np.zeros(k, "float32")
            words = clusters.predict(imagelist[i].descriptor)

            for word in words:
                features[word] += 1
            
            # Normalize 
            occurrences = np.sum(features)
            features = features/occurrences;
            imagelist[i].histogram = features


        pickle.dump(imagelist, open("imagelist.pkl", "wb"))

    def query(feature_des, k):
        
        imagelist = pickle.load(open("imagelist.pkl", "rb"))
        
        filename = "test_queries.dat"

        with open(filename) as f:
            queries = f.readlines()                 #Read the name of each query image 

        queries = [x.strip() for x in queries]

        for item in queries:
            img = cv2.imread('dataset/' + item)
            gray= cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
            
            if(feature_des == "SIFT"):
                sift = cv2.xfeatures2d.SIFT_create(1000)  

                keypoints = sift.detect(gray,None)
            
                cv2.drawKeypoints(gray,keypoints,img)
            
                keypoints, des = sift.detectAndCompute(gray,None)

            else:
                keypoints, des = dsift(gray,step=100) 
            
            if(len(keypoints) == 0):
                tmp = np.zeros(128, "float32")
                des = np.reshape(tmp, (1,128))

            image_obj = image(item, des, [])
            querylist.append(image_obj)

        clusters = pickle.load(open("clusters.pkl", "rb"))

        for i in range(len(queries)):
            features = np.zeros(k, "float32")

            words = clusters.predict(querylist[i].descriptor)

            for word in words:
                features[word] += 1

            # Normalize 
            occurrences = np.sum(features)
            features = features/occurrences;
            querylist[i].histogram = features


class result:
    def __init__(self, name, distance):
        self.name = name
        self.distance = distance

    def euclidean():
        imagelist = pickle.load(open("imagelist.pkl", "rb"))

        for i in range(len(querylist)):
            resultlist = []
            for j in range(len(imagelist)):
                res = result(imagelist[j].name, distance.euclidean(querylist[i].histogram, imagelist[j].histogram))
                resultlist.append(res)

            resultlist.sort(key=lambda x: x.distance, reverse=False)
            string = querylist[i].name + ":"
            for res in resultlist:
                if(res.name == querylist[i].name):
                    continue
                else:
                    string += (" " + str(res.distance) + " " + res.name)

            print(string)

def main(feature_des, k):

    
    image.vision(feature_des, int(k))
    
    image.query(feature_des, int(k))
    result.euclidean()
    
querylist = []

if __name__ == "__main__":
    # Execute only if the program is run as a script
    if (len(sys.argv) > 2):
        # Execute only if feature_des and k arguments are given as parameter
        main(sys.argv[1], sys.argv[2])
    else:
        print()
        print("Please give one of the feature descriptors 'SIFT' or 'DENSE'")
        print(" and one of the k values: 32, 64, 128 or 256 as parameter")


