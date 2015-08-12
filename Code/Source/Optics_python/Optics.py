import Object as Obj
import scipy.io as sio
import numpy as np 
import priorityQueue as pq
import math 

class optics:
	def __init__(self,epsilon,minPts):
		self.self.ansSet = []
		self.epsilon = epsilon
		self.minPts = minPts

	def setData(self,shape_tuple,dist,ind):
		#self.data = data
		(m,n) = shape_tuple
		self.distance = dist
		self.ind = ind
		self.listOfObjects = []
		self.queue = pq.PriorityQueue()
		for i in range(0,m):
			x = Obj.Object();
			x.setIndex(i)
			core = -1;
			neighbors = []
			counter = 0 
			for dist in self.distance[i]:
				if(dist > self.epsilon):
					break;
				if(len(neighbors) <= self.minPts):
					core = dist
				neighbors.append((self.ind[counter],dist))
				counter = counter + 1

			if(core != -1):
				if(len(neighbors) >= self.minPts):
					x.setCoreDistance(core)
				x.setNeighbors(neighbors)
			self.listOfObjects.append(x)

	def operate(self):
		self.ansSet = []
		for object in self.listOfObjects:
			if(object.isProcessed()):
				continue
			else:
				object.setProcessed(True)
				self.ansSet.append(object)
				if (object.getCoreDistance() < pow(10,10)):
					#UPDATE QUEUE
					updateQueue(object.getIndex())
					visited = set()
					while(not self.queue.isEmpty()):
						objind = queue.pop()
						if(objind in visited):
							continue
						visited.add(objind)
						self.listOfObjects[objind].setProcessed(True)
						self.ansSet.append(self.listOfObjects[objind])
						if(self.listOfObjects[objind].getCoreDistance() < pow(10,10)):
							#UPDATE QUEUE
							updateQueue(objind)

		
	def getAnsSet(self):
		return self.ansSet


	def updateQueue(objInd): 
		neighbors = self.listOfObjects[objInd].getNeighbors()
		c_dist = self.listOfObjects[objInd].getCoreDistance()
		for (objind,dist) in neighbors:
			if( not self.listOfObjects[objind].isProcessed() ):
				new_r_distance = max(c_dist,dist)
				if(new_r_distance < self.listOfObjects[objind].getReachabilityDistance()):
					self.listOfObjects[objind].setReachabilityDistance(new_r_distance)
					self.queue.push(objind,new_r_distance)

	def extractClusters(self,epsilon_prime,minPts):
		clusterID = 0 # NOISE
		for obj in self.ansSet:
			if(obj.getReachabilityDistance() > epsilon_prime ):
				if(obj.getCoreDistance() <= epsilon_prime):
					clusterID = clusterID + 1
					obj.setClusterID(clusterID)
				else:
					obj.setClusterID(0)
			else:
				obj.setClusterID(clusterID)













