import math,itertools,sys,os
from collections import deque

def operate(filename,k_max):
	f = open(filename)
	dictionary = {'A':0,'T':1,'C':2,'G':3}
	single = [0.0 for it in xrange(4)]
	mbuffer = deque()
	frequency_count = [[[0.0 for it in xrange(4)] for jt in xrange(4)] for kt in xrange(k_max)]
	k_max += 1
	#Ignore first line
	f.readline()
	while(True):
		genotype = f.read(1)
		if(not genotype):
			break
		if(genotype=='\n' or genotype=='N'):
			continue
		
		single[dictionary[genotype]]+=1
		if(len(mbuffer)<k_max):
			mbuffer.append(genotype)
		
		elif(len(mbuffer)==k_max):
			mbuffer.popleft()
			mbuffer.append(genotype)
		
		else:
			print len(mbuffer)
			print 'Something Terribly wrong'
			break
		
		for idx in xrange(len(mbuffer)-2,-1,-1):
			frequency_count[len(mbuffer)-2-idx][dictionary[mbuffer[idx]]][dictionary[genotype]] +=1

	f.close()
	total = sum(single)
	single = map(lambda x: x / total,single)
	result_vector = []
	for element in frequency_count:
		total = sum(map(lambda x:sum(x),element))
		I = 0.0
		collection = itertools.product('ATGC',repeat=2)
		for (i,j) in collection:
			p_i_j = (element[dictionary[i]][dictionary[j]]) / total
			p_i = single[dictionary[i]]
			p_j = single[dictionary[j]]
			I += (p_i_j * (math.log(p_i_j) - math.log(p_i) - math.log(p_j)) / math.log(4.0) )
		result_vector.append(I)
	return result_vector

for root,dirs,files in os.walk('.',topdown=False):
	for fil in files:
		if("NC_" in fil):
			result_vector = operate(fil,30)
			g = open('Result_' + fil,'w')
			for item in result_vector:
				g.write(str(item)+'\n')
			g.close()


