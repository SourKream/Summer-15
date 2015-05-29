import math
import cmath
import os

def cem(f):
    file = open(f,'r')
    file.readline()
    j=0
    window=[]
    auto=[]
    #Initializing Window
    while(j<50000):
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
        size=len(l) # #(characters in line)
        i=0
        while(i<size):
            if(j<50000):
                x=((j1+start)%50000)
                window[x]=l[i]
                print window[x] + " " + l[i] + "\n"
                j=j+1
                j1 = j1 + 1
            '''else:     
                auto.append(auto_en(window,start))
                j=shift
                j1 = 0
                start=(start+shift)%50000'''
            i=i+1
    return auto

def auto_en(window,start):
    i=0
    j=0
    ent=[]
#    print window
    while(j<50000):
        subwin=[0 for wee in range(199)]
        i=0
        while(i<199 and j<50000):
            subwin[i]=window[(j+start)%50000]
            i=i+1
            j=j+1
#        print subwin
        t=entrpy_d(subwin,start)
        ent.append(t)
    i=0
    ck=0.0
    maxi=250
    while(i<maxi):
        alp = crltn(i,ent)
        if alp==-10:
#            print maxi
            maxi=maxi-1
            continue
        ck=ck+(crltn(i,ent))
        i=i+1
    cg=(ck*(1.0))/maxi
    return math.fabs(cg)

def crltn(i,ent):
    size=len(ent)
    meanx=0.0
    devx=0.0
    meany=0.0
    devy=0.0
    sxy=0.0
    k=0
    while(k<(size-i)):
        meanx=ent[k]+meanx
        k=k+1
    meanx=meanx/(size-i)
    k=i
    while(k<size):
        meany=ent[k]+meany
        k=k+1
    meany=meany/(size-i)
    k=0
    while(k<(size-i)):
        sxy=(ent[k]-meanx)*(ent[k+i]-meany)+sxy
        k=k+1
    k=0
    while(k<(size-i)):
        devx=math.pow((ent[k]-meanx),2)+devx
        devy=math.pow((ent[k+i]-meany),2)+devy
        k=k+1
    if devx and devy:
        sxy=sxy/math.sqrt(devx*devy)
    else:
        sxy=-10 
    return sxy

def entrpy_d(window,start):
    pa=0.0
    pt=0.0
    pc=0.0
    pg=0.0
    l=window
    size=len(l)
    i=0
    while(i<size):
        if(l[i]=='A'):
            pa=pa+1.0
        elif(l[i]=='T'):
            pt=pt+1.0
        elif(l[i]=='C'):
            pc=pc+1.0
        else:
            pg=pg+1.0
        i=i+1
    pa=pa/size
    pt=pt/size
    pc=pc/size
    pg=pg/size
    entrpy=(-1)*((pa*log(pa))+(pt*log(pt))+(pc*log(pc))+(pg*log(pg)))
    return entrpy

def log(x):
    if(x==0):
        return 0
    else:
        return math.log(x)

print cem("NC_023028.fna")
