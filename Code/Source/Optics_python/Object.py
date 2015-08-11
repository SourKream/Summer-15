class Object:
	def __init__(self):
		self.index = -1;
		self.processed = False;
		self.coreDistance = pow(10,5);
		self.reachabilityDistance = pow(10,5);
		self.neighbors = []
		self.clusterID = 0
	
	def isProcessed(self):
		return self.processed;
	
	def getCoreDistance(self):
		return self.coreDistance;

	def getReachabilityDistance(self):
		return self.reachabilityDistance;

	def setCoreDistance(self,CD):
		self.coreDistance = CD;

	def setReachabilityDistance(self,RD):
		self.reachabilityDistance = RD;

	def setProcessed(self):
		self.processed = True;

	def setIndex(self,ind):
		self.index = ind;

	def getNeighbors(self):
		return self.neighbors

	def setNeighbors(self,x):
		self.neighbors = x

	def getIndex(self):
		return self.index

	def setClusterID(self,ID):
		self.clusterID = ID;

	def getClusterID(self):
		return self.clusterID
