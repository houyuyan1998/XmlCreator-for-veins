import random
import re
import datetime

def filter(route):
    i=0
    junction=[]
    junction.append(junction_edge[route[i]][0])
    while i<len(route):
        next=junction_edge[route[i]][1]
        if next in junction:
            return 1
        junction.append(next)
        i=i+1
    return 0

def library():
    waytype={}
    waytype["highway.bridleway"]=0
    waytype["highway.bus_guideway"]=0
    waytype["highway.cycleway"]=0
    waytype["highway.footway"]=0
    waytype["highway.ford"]=1
    waytype["highway.living_street"]=1
    waytype["highway.motorway"]=1
    waytype["highway.motorway_link"]=1
    waytype["highway.path"]=0
    waytype["highway.pedestrian"]=0
    waytype["highway.primary"]=1
    waytype["highway.primary_link"]=1
    waytype["highway.raceway"]=0
    waytype["highway.residential"]=1
    waytype["highway.secondary"]=1
    waytype["highway.secondary_link"]=1
    waytype["highway.service"]=0
    waytype["highway.stairs"]=0
    waytype["highway.step"]=0
    waytype["highway.steps"]=0
    waytype["highway.tertiary"]=1
    waytype["highway.tertiary_link"]=1
    waytype["highway.track"]=0
    waytype["highway.trunk"]=1
    waytype["highway.trunk_link"]=1
    waytype["highway.unclassified"]=1
    waytype["highway.unsurfaced"]=1
    waytype["railway.highspeed"]=0
    waytype["railway.light_rail"]=0
    waytype["railway.preserved"]=0
    waytype["railway.rail"]=0
    waytype["railway.subway"]=0
    waytype["railway.tram"]=0


    fr=open("osm.net.xml","r",encoding="UTF-8")
    edgetype={}
    line=fr.readline()
    while line:
        line=fr.readline()
        if re.match("    <edge id=\"\S*\" from",line):
            ID=re.findall("    <edge id=\"(\S*)\"",line)
            ID=ID[0]
            #print(ID)
            Type=re.findall(".*type=\"(\S*)\"",line)
            Type=Type[0]
            edgetype[ID]=waytype[Type]
    fr.close()

    fr=open("osm.net.xml","r",encoding="UTF-8")
    connection={}
    line=fr.readline()
    while line:
        line=fr.readline()
        if re.match("    <connection from=",line):
            ID=re.findall("    <connection from=\"(\S*)\"",line)
            ID=ID[0].replace(":","")
            if "_" in ID:
                continue
            if edgetype[ID]==0:
                continue
            Target=re.findall("    <connection from=\"\S*\" to=\"(\S*)\"",line)
            Target=Target[0]
            if "_" in Target:
                continue
            if edgetype[Target]==0:
                continue
            if ID not in connection:
                connection[ID]=[]
                connection[ID].append(Target)
            else:
                connection[ID].append(Target)
            if Target not in connection:
                connection[Target]=[]
    fr.close()

    step=100
    fw=open("random.rou.xml","w",encoding="UTF-8")
    n=10000
    fw.write("<routes>\n")
    m=0
    t=step
    edge=len(connection)
    while m<10000:
        t=step
        fw.write("\t")
        fw.write("<vehicle id=\""+str(m)+"\" depart=\""+str(m)+".00\">\n")
        m=m+1
        fw.write("\t")
        fw.write("\t")
        start=random.sample(connection.keys(),1)
        start=start[0]
        fw.write("<route edges=\""+start)
        t=t-1
        target=start
        while t>0:
            if len(connection[target])==0:
                break
            else:
                target=random.sample(connection[target],1)
                target=target[0]
                fw.write(" "+target)
            t=t-1
        fw.write("\"/>")  
        fw.write("\n")
        fw.write("\t")
        fw.write("</vehicle>\n")
        n=n-1
        if n==0:
            break
    fw.write("</routes>\n")
    fw.close()
    time=datetime.datetime.now()
    print(time)

    fr=open("osm.net.xml","r",encoding="UTF-8")
    junction_edge={}
    line=fr.readline()
    while line:
        line=fr.readline()
        if re.match("    <edge id=\"\S*\" from=\"\S*\" to=\"\S*\"",line):
            ID=re.findall("    <edge id=\"(\S*)\"",line)
            ID=ID[0].replace(":","")
            start=re.findall("    <edge id=\"\S*\" from=\"(\S*)\" to=\"\S*\"",line)
            start=start[0]
            if "_" in start:
                start=re.findall("(\S*)_\S",start)
            end=re.findall("    <edge id=\"\S*\" from=\"\S*\" to=\"(\S*)\"",line)
            end=end[0]
            if "_" in end:
                end=re.findall("(\S*)_\S",end)
            junction_edge[ID]=[]
            junction_edge[ID].append(start)
            junction_edge[ID].append(end)
    fr.close()

    fr=open("random.rou.xml","r")
    fw1=open("circle library.txt","w",encoding="UTF-8")
    fw0=open("noncircle library.txt","w",encoding="UTF-8")
    circle=0
    line=fr.readline()
    while line:
        route=[]
        line=fr.readline()
        if re.match("		<route edges=",line):
            #print(line)
            route=re.findall("		<route edges=\"(.*)\"/>",line)
            #print(route)
            route=route[0].split()
            #print(route)
            circle=filter(route)
            j=0
            if circle==0:
                while j<len(route):
                    fw0.write(route[j])
                    fw0.write(" ")
                    j=j+1
                fw0.write("\n")
            elif circle==1:
                while j<len(route):
                    fw1.write(route[j])
                    fw1.write(" ")
                    j=j+1
                fw1.write("\n")
    fr.close()
    fw1.close()
    fw0.close()

