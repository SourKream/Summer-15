import math
import cmath
import os

global windowsize
windowsize = 50000;
global subwindowsize 
subwindowsize = 200;

def cem(f):
    file = open(f,'r')
    file.readline()
    j=0
    window=[]
    auto=[]
    #Initializing Window
    while(j<windowsize):
        window.append(0)
        j=j+1
    #End of initialization
    #Variable Declaration
    start=0
    j=0
    j1 = 0
    shift = 0
    #End of Variable Declaration
    for line in file:
        s=line
        l=list(s)
        l = l[0:len(l)-1]
#        print l
        size=len(l) # #(characters in line)
        i=0
        while(i<size):
            if(j<windowsize):
                x=((j1+start)%windowsize)
                window[x]=l[i]
#                print window[x] + " " + l[i] + "\n"
                j=j+1
                j1 = j1 + 1
                i=i+1
            else:     
#                print window;
                auto.append(auto_en(window,start))
                j=shift
                j1 = 0
                start=(start+shift)%windowsize
    return auto

def auto_en(window,start):
    i=0
    j=0
    ent=[]
#    print window
    while(j<windowsize):
        subwin=[0 for wee in range(subwindowsize)]
        i=0
        while(i<subwindowsize and j<windowsize):
            subwin[i]=window[(j+start)%windowsize]
            i=i+1
            j=j+1
#        print subwin
        t=entrpy_d(subwin,start)
        ent.append(t)
 #   print ent


    i=1
    ck=0.0
    maxi=len(ent)
    while(i<maxi):
        ck=ck+(math.fabs(crltn(i,ent)))
#        print (crltn(i,ent))
        i=i+1
    cg=(ck)/(maxi-1)
#    print "finally:"
#    print cg
    return cg

def crltn(i,ent):
    size=len(ent)
    meanx=0.0
    devx=0.0
    sxy=0.0

    k=0
    while(k<(size)):
        meanx=ent[k]+meanx
        k=k+1
    meanx=meanx/(size)

    k=0
    while(k<(size-i)):
        sxy=(ent[k]-meanx)*(ent[k+i]-meanx)+sxy
        k=k+1

    k=0
    while(k<(size)):
        devx=math.pow((ent[k]-meanx),2)+devx
        k=k+1

    devx=devx/(size)
    sxy=sxy/(devx*(size - i))
    return sxy

def entrpy_d(window,start):
    pa=0.0
    pt=0.0
    pc=0.0
    pg=0.0
    l=window
    size=len(l)
    i=0
    msize = size;
    while(i<size):
        if(l[i]=='A'):
            pa=pa+1.0
        elif(l[i]=='T'):
            pt=pt+1.0
        elif(l[i]=='C'):
            pc=pc+1.0
        elif(l[i]=='G'):
            pg=pg+1.0
        else:
            msize = msize - 1;
        i=i+1
    pa=pa/msize
    pt=pt/msize
    pc=pc/msize
    pg=pg/msize
    entrpy=(-1)*((pa*log(pa))+(pt*log(pt))+(pc*log(pc))+(pg*log(pg)))
    return entrpy

def log(x):
    if(x==0):
        return 0
    else:
        return math.log(x)/math.log(2)

print cem("NC_013209.fna")
