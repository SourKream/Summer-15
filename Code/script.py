import urllib2
import threading
fileList =[] 
numThreads=10;

src_root = "http://www.scfbio-iitd.res.in/chemgenome/genomedataset/";

def downloadFile(url): 
    localFileName = url.split('/')[-1];
    localFileName = "Genome/"+ localFileName.rstrip(".fna\n") + ".txt"
    handle = urllib2.urlopen(url)
    CHUNK = 16 * 1024;
    with open(localFileName,'w') as fp:
        while True:
            chunk = handle.read(CHUNK);
            if not chunk: break
            fp.write(chunk)
    return localFileName

class mThread (threading.Thread):
    def __init__(self,threadID,start,end):
        threading.Thread.__init__(self)
        self.threadID=threadID;
        self.startList = start;
        self.end = end;
    def run(self):  
        for i in range(self.startList,self.end):
            print fileList[i] + "starting...."
            print downloadFile(src_root + fileList[i]) + " done"
        donelist[self.threadID] = True

#Change Here .......
f = open("Genome/GenomeList.txt",'r')
for line in f:
    fileList.append(line)

stepSize = len(fileList) / numThreads;
threads = []
#Initializing the Children Threads.
donelist = [False for x in range(0,numThreads)]
for i in range(0,numThreads):
    start = i * stepSize;
    end = (i+1) * stepSize;
    threads.append(mThread(i,start,end));
    threads[i].start();

#Main Thread Takes care of the remaining files, if they exist.
for i in range(numThreads*stepSize,len(fileList)):
    print fileList[i] + "starting..."
    print downloadFile(src_root + fileList[i]) + "done";

Flag = False
while (not Flag):
    Flag = True
    for x in donelist:
        if (x==False):
            Flag = False
            break
    
    


