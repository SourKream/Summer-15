import math
import cmath
import os
import numpy as np

def cem(f):
    file = open(f,'r')
    file.readline()
    j=0
    window=[]
    auto=[]
    while(j<50000):
        window.append(0)
        j=j+1
    start=0
    j=0
    j1 = 0
    shift = 48993
    for line in file:
        s=line
        l=list(s)
        size=len(l)
        i=0
        while(i<size):
            if(j<50000):
                x=((j1+start)%50000)
                window[x]=l[i]
                j=j+1
                j1 = j1 + 1
                i=i+1
            else:     
                auto.append(auto_en(window,start))
                j=shift
                j1 = 0
                start=(start+shift)%50000
    return auto

#bound on subwindow size
#bound on window size
#how to optimally chose a subwindow size and window size?
#can use ML or Signal Processing Logics

def auto_en(window,start):
    i=0
    j=0
    ent=[]
    while(j<50000):
        subwin=[0 for wee in range(125)]
        i=0
        while(i<125 and j<50000):
            subwin[i]=window[(j+start)%50000]
            i=i+1
            j=j+1
        t=entrpy_d(subwin,start)
        ent.append(t)
    i=0
    ck=0.0
    maxi=len(ent)
    while(i<maxi):
        alp = crltn(i,ent)
        if alp==-10:
            #print maxi
            maxi=maxi-1
            continue
        ck=ck+math.fabs(crltn(i,ent))
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
        elif(l[i]=='G'):
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

def multi_enauto( farray , limit=None ):
    a=[]
    if not limit:
        n=len(farray)
    else:
        n= np.minimum(limit,len(farray))
    i=0
    while(i<n):
        print i, farray[i]
        a.append(cem('fna/'+farray[i]))
        i=i+1
    return a

def decide_enauto(outputArray, sigma):
    a = np.array(outputArray)
    b = []
    variance = a.var()
    mean = a.mean()
    std = math.sqrt(variance)
    l = a.size
    i = 0
    while( i < l ):
        if( a[i] > sigma*std + mean ):
            b.append(a[i])
        i = i + 1
    #print b
    #print (len(b)*1.0/l)
    if ( (len(b) >= 1 ) and ( len(b)*1.0 < l*0.150 ) ):
        return 1
    else:
        return 0

def oracle_enauto( fileArray, sigma, limit=None ):
    a = multi_enauto( fileArray, limit )
    b = []
    i = 0
    if not limit:
        l = len(a)
    else:
        l = np.minimum( len(a), limit )
    print l
    while( i < l ):
        b.append( decide_enauto(a[i],sigma) )
        i=i+1
    return b

fileArray = [  'NC_000117.fna',  'NC_000853.fna',  'NC_000854.fna',  'NC_000868.fna',  'NC_000907.fna',  'NC_000908.fna',  'NC_000909.fna',  'NC_000911.fna',  'NC_000912.fna',  'NC_000913.fna',  'NC_000915.fna',  'NC_000916.fna',  'NC_000917.fna',  'NC_000918.fna',  'NC_000919.fna',  'NC_000921.fna',  'NC_000922.fna',  'NC_000961.fna',  'NC_000962.fna',  'NC_000963.fna',  'NC_000964.fna',  'NC_001263.fna',  'NC_001264.fna',  'NC_001318.fna',  'NC_002162.fna',  'NC_002163.fna',  'NC_002179.fna',  'NC_002488.fna',  'NC_002491.fna',  'NC_002505.fna',  'NC_002506.fna',  'NC_002516.fna',  'NC_002528.fna',  'NC_002570.fna',  'NC_002578.fna',  'NC_002607.fna',  'NC_002620.fna',  'NC_002655.fna',  'NC_002662.fna',  'NC_002663.fna',  'NC_002677.fna',  'NC_002678.fna',  'NC_002689.fna',  'NC_002695.fna',  'NC_002696.fna',  'NC_002737.fna',  'NC_002745.fna',  'NC_002754.fna',  'NC_002755.fna',  'NC_002758.fna',  'NC_002771.fna',  'NC_002927.fna',  'NC_002928.fna',  'NC_002929.fna',  'NC_002932.fna',  'NC_002935.fna',  'NC_002936.fna',  'NC_002937.fna',  'NC_002939.fna',  'NC_002940.fna',  'NC_002942.fna',  'NC_002944.fna',  'NC_002945.fna',  'NC_002946.fna',  'NC_002947.fna',  'NC_002950.fna',  'NC_002951.fna',  'NC_002952.fna',  'NC_002953.fna',  'NC_002967.fna',  'NC_002971.fna',  'NC_002973.fna',  'NC_002976.fna',  'NC_002977.fna',  'NC_002978.fna',  'NC_003028.fna',  'NC_003030.fna',  'NC_003047.fna',  'NC_003062.fna',  'NC_003063.fna',  'NC_003098.fna',  'NC_003103.fna',  'NC_003106.fna',  'NC_003112.fna',  'NC_003116.fna',  'NC_003143.fna',  'NC_003155.fna',  'NC_003197.fna',  'NC_003198.fna',  'NC_003210.fna',  'NC_003212.fna',  'NC_003228.fna',  'NC_003272.fna',  'NC_003295.fna',  'NC_003317.fna',  'NC_003318.fna',  'NC_003361.fna',  'NC_003364.fna',  'NC_003366.fna',  'NC_003413.fna',  'NC_003450.fna',  'NC_003454.fna',  'NC_003485.fna',  'NC_003551.fna',  'NC_003552.fna',  'NC_003869.fna',  'NC_003888.fna',  'NC_003901.fna',  'NC_003902.fna',  'NC_003909.fna',  'NC_003910.fna',  'NC_003911.fna',  'NC_003912.fna',  'NC_003919.fna',  'NC_003923.fna',  'NC_003997.fna',  'NC_004061.fna',  'NC_004070.fna',  'NC_004088.fna',  'NC_004113.fna',  'NC_004116.fna',  'NC_004129.fna',  'NC_004193.fna',  'NC_004307.fna',  'NC_004310.fna',  'NC_004311.fna',  'NC_004337.fna',  'NC_004342.fna',  'NC_004343.fna',  'NC_004344.fna',  'NC_004347.fna',  'NC_004350.fna',  'NC_004368.fna',  'NC_004369.fna',  'NC_004431.fna',  'NC_004432.fna',  'NC_004459.fna',  'NC_004460.fna',  'NC_004461.fna',  'NC_004463.fna',  'NC_004545.fna',  'NC_004547.fna',  'NC_004551.fna',  'NC_004552.fna',  'NC_004556.fna',  'NC_004557.fna',  'NC_004567.fna',  'NC_004572.fna',  'NC_004578.fna',  'NC_004603.fna',  'NC_004605.fna',  'NC_004606.fna',  'NC_004631.fna',  'NC_004663.fna',  'NC_004668.fna',  'NC_004722.fna',  'NC_004741.fna',  'NC_004757.fna',  'NC_004829.fna',  'NC_004842.fna',  'NC_004917.fna',  'NC_005027.fna',  'NC_005042.fna',  'NC_005043.fna',  'NC_005061.fna',  'NC_005070.fna',  'NC_005071.fna',  'NC_005072.fna',  'NC_005085.fna',  'NC_005090.fna',  'NC_005125.fna',  'NC_005126.fna',  'NC_005139.fna',  'NC_005140.fna',  'NC_005213.fna',  'NC_005241.fna',  'NC_005295.fna',  'NC_005296.fna',  'NC_005303.fna',  'NC_005362.fna',  'NC_005363.fna',  'NC_005364.fna',  'NC_005773.fna',  'NC_005791.fna',  'NC_005810.fna',  'NC_005823.fna',  'NC_005824.fna',  'NC_005835.fna',  'NC_005861.fna',  'NC_005877.fna',  'NC_005945.fna',  'NC_005955.fna',  'NC_005956.fna',  'NC_005957.fna',  'NC_005966.fna',  'NC_006055.fna',  'NC_006085.fna',  'NC_006086.fna',  'NC_006087.fna',  'NC_006138.fna',  'NC_006142.fna',  'NC_006155.fna',  'NC_006156.fna',  'NC_006177.fna',  'NC_006270.fna',  'NC_006274.fna',  'NC_006300.fna',  'NC_006322.fna',  'NC_006347.fna',  'NC_006348.fna',  'NC_006349.fna',  'NC_006350.fna',  'NC_006351.fna',  'NC_006360.fna',  'NC_006361.fna',  'NC_006368.fna',  'NC_006369.fna',  'NC_006370.fna',  'NC_006371.fna',  'NC_006396.fna',  'NC_006397.fna',  'NC_006448.fna',  'NC_006449.fna',  'NC_006461.fna',  'NC_006510.fna',  'NC_006511.fna',  'NC_006512.fna',  'NC_006513.fna',  'NC_006526.fna',  'NC_006569.fna',  'NC_006570.fna',  'NC_006576.fna',  'NC_006582.fna',  'NC_006624.fna',  'NC_006677.fna',  'NC_006814.fna',  'NC_006831.fna',  'NC_006832.fna',  'NC_006833.fna',  'NC_006834.fna',  'NC_006840.fna',  'NC_006841.fna',  'NC_006905.fna',  'NC_006908.fna',  'NC_006932.fna',  'NC_006933.fna',  'NC_006958.fna',  'NC_007005.fna',  'NC_007086.fna',  'NC_007109.fna',  'NC_007146.fna',  'NC_007164.fna',  'NC_007168.fna',  'NC_007181.fna',  'NC_007204.fna',  'NC_007205.fna',  'NC_007292.fna',  'NC_007294.fna',  'NC_007295.fna',  'NC_007296.fna',  'NC_007297.fna',  'NC_007298.fna',  'NC_007332.fna',  'NC_007333.fna',  'NC_007335.fna',  'NC_007336.fna',  'NC_007347.fna',  'NC_007348.fna',  'NC_007350.fna',  'NC_007354.fna',  'NC_007355.fna',  'NC_007356.fna',  'NC_007384.fna',  'NC_007404.fna',  'NC_007406.fna',  'NC_007413.fna',  'NC_007426.fna',  'NC_007429.fna',  'NC_007432.fna',  'NC_007434.fna',  'NC_007435.fna',  'NC_007481.fna',  'NC_007482.fna',  'NC_007484.fna',  'NC_007492.fna',  'NC_007493.fna',  'NC_007494.fna',  'NC_007498.fna',  'NC_007503.fna',  'NC_007508.fna',  'NC_007509.fna',  'NC_007510.fna',  'NC_007511.fna',  'NC_007512.fna',  'NC_007513.fna',  'NC_007514.fna',  'NC_007516.fna',  'NC_007517.fna',  'NC_007519.fna',  'NC_007520.fna',  'NC_007530.fna',  'NC_007575.fna',  'NC_007576.fna',  'NC_007577.fna',  'NC_007604.fna',  'NC_007606.fna',  'NC_007613.fna',  'NC_007614.fna',  'NC_007618.fna',  'NC_007622.fna',  'NC_007624.fna',  'NC_007626.fna',  'NC_007633.fna',  'NC_007643.fna',  'NC_007644.fna',  'NC_007645.fna',  'NC_007650.fna',  'NC_007651.fna',  'NC_007677.fna',  'NC_007681.fna',  'NC_007705.fna',  'NC_007712.fna',  'NC_007716.fna',  'NC_007722.fna',  'NC_007759.fna',  'NC_007760.fna',  'NC_007761.fna',  'NC_007775.fna',  'NC_007776.fna',  'NC_007777.fna',  'NC_007778.fna',  'NC_007779.fna',  'NC_007793.fna',  'NC_007794.fna',  'NC_007795.fna',  'NC_007796.fna',  'NC_007797.fna',  'NC_007798.fna',  'NC_007799.fna',  'NC_007802.fna',  'NC_007880.fna',  'NC_007899.fna',  'NC_007901.fna',  'NC_007907.fna',  'NC_007908.fna',  'NC_007912.fna',  'NC_007925.fna',  'NC_007929.fna',  'NC_007940.fna',  'NC_007946.fna',  'NC_007947.fna',  'NC_007948.fna',  'NC_007951.fna',  'NC_007952.fna',  'NC_007953.fna',  'NC_007954.fna',  'NC_007955.fna',  'NC_007958.fna',  'NC_007963.fna',  'NC_007964.fna',  'NC_007969.fna',  'NC_007973.fna',  'NC_007974.fna',  'NC_007984.fna',  'NC_008009.fna',  'NC_008011.fna',  'NC_008021.fna',  'NC_008022.fna',  'NC_008023.fna',  'NC_008024.fna',  'NC_008025.fna',  'NC_008027.fna',  'NC_008044.fna',  'NC_008048.fna',  'NC_008054.fna',  'NC_008060.fna',  'NC_008061.fna',  'NC_008062.fna',  'NC_008086.fna',  'NC_008095.fna',  'NC_008146.fna',  'NC_008147.fna',  'NC_008148.fna',  'NC_008149.fna',  'NC_008150.fna',  'NC_008209.fna',  'NC_008212.fna',  'NC_008228.fna',  'NC_008229.fna',  'NC_008245.fna',  'NC_008253.fna',  'NC_008254.fna',  'NC_008255.fna',  'NC_008258.fna',  'NC_008260.fna',  'NC_008261.fna',  'NC_008268.fna',  'NC_008277.fna',  'NC_008278.fna',  'NC_008309.fna',  'NC_008312.fna',  'NC_008313.fna',  'NC_008314.fna',  'NC_008319.fna',  'NC_008321.fna',  'NC_008322.fna',  'NC_008340.fna',  'NC_008343.fna',  'NC_008344.fna',  'NC_008345.fna',  'NC_008346.fna',  'NC_008347.fna',  'NC_008358.fna',  'NC_008369.fna',  'NC_008380.fna',  'NC_008390.fna',  'NC_008391.fna',  'NC_008392.fna',  'NC_008435.fna',  'NC_008463.fna',  'NC_008497.fna',  'NC_008508.fna',  'NC_008509.fna',  'NC_008510.fna',  'NC_008511.fna',  'NC_008512.fna',  'NC_008513.fna',  'NC_008525.fna',  'NC_008526.fna',  'NC_008527.fna',  'NC_008528.fna',  'NC_008529.fna',  'NC_008530.fna',  'NC_008531.fna',  'NC_008532.fna',  'NC_008533.fna',  'NC_008536.fna',  'NC_008541.fna',  'NC_008542.fna',  'NC_008543.fna',  'NC_008544.fna',  'NC_008553.fna',  'NC_008554.fna',  'NC_008555.fna',  'NC_008563.fna',  'NC_008570.fna',  'NC_008571.fna',  'NC_008576.fna',  'NC_008577.fna',  'NC_008578.fna',  'NC_008593.fna',  'NC_008595.fna',  'NC_008596.fna',  'NC_008599.fna',  'NC_008600.fna',  'NC_008601.fna',  'NC_008609.fna',  'NC_008610.fna',  'NC_008611.fna',  'NC_008618.fna',  'NC_008639.fna',  'NC_008686.fna',  'NC_008687.fna',  'NC_008698.fna',  'NC_008699.fna',  'NC_008700.fna',  'NC_008701.fna',  'NC_008702.fna',  'NC_008705.fna',  'NC_008709.fna',  'NC_008710.fna',  'NC_008711.fna',  'NC_008726.fna',  'NC_008740.fna',  'NC_008750.fna',  'NC_008751.fna',  'NC_008752.fna',  'NC_008767.fna',  'NC_008769.fna',  'NC_008781.fna',  'NC_008782.fna',  'NC_008783.fna',  'NC_008784.fna',  'NC_008785.fna',  'NC_008786.fna',  'NC_008787.fna',  'NC_008789.fna',  'NC_008800.fna',  'NC_008816.fna',  'NC_008817.fna',  'NC_008818.fna',  'NC_008819.fna',  'NC_008820.fna',  'NC_008825.fna',  'NC_008835.fna',  'NC_008836.fna',  'NC_008942.fna',  'NC_009004.fna',  'NC_009009.fna',  'NC_009012.fna' ]
print oracle_enauto( fileArray, 2.5, 500)