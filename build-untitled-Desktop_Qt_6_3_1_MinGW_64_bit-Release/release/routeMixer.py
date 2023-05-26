import random
import re

'''
n:生成的路线总数
CircleRate=:带环路线的比率
address:library地址

'''
def mixer(n,CircleRate,address):
    flag=0#全环为1，全非环为2
    num=0#已生成的路线数
    N=n#要生成的路线总数
    CircleAmount=round(n*CircleRate/100)#带环路线的总量
    NonCircleAmount=n-CircleAmount#不带环路线的总量
    fr0=open(address+".noncircle library.txt","r")
    fr1=open(address+".circle library.txt","r")
    fw=open(address+".rou.xml","w",encoding="UTF-8")
    fw.write("<!--\n")
    fw.write("<configuration>\n")
    fw.write("</configuration>\n")
    fw.write("-->\n")
    fw.write("<routes>\n")
    line=fr0.readline()
    NonCircle=[]
    Circle=[]
    LibraryLine=0#library的行数
    while line:
        LibraryLine=LibraryLine+1
        NonCircle.append(line)
        line=fr0.readline()
    NonCircleLibrary=LibraryLine#无环库总量
    if NonCircleLibrary==0:
        flag=1
        N=N-NonCircleAmount
        NonCircleAmount=0
        
    line=fr1.readline()
    LibraryLine=0#library的行数
    while line:
        LibraryLine=LibraryLine+1
        Circle.append(line)
        line=fr1.readline()
    CircleLibrary=LibraryLine#有环库总量
    if CircleLibrary==0:
        flag=2
        N=N-CircleAmount
        CircleAmount=0
 
    print(N)
    CircleNumber=0#带环路线的数量
    NonCircleNumber=0#不带环路线的数量

    CircleOutput=[]
    NonCircleOutput=[]
    while NonCircleNumber<NonCircleAmount:
        NonCircleNumber=NonCircleNumber+1
        rand=random.randint(1,NonCircleLibrary)
        NonCircleOutput.append(NonCircle[rand-1])

    while CircleNumber<CircleAmount:
        CircleNumber=CircleNumber+1
        rand=random.randint(1,CircleLibrary)
        CircleOutput.append(Circle[rand-1])

    CircleNumber=0#重置计数
    NonCircleNumber=0#重置计数
    while num<N:
        if flag==2 or (flag==0 and NonCircleNumber*CircleAmount/NonCircleAmount<=CircleNumber):
            NonCircleNumber=NonCircleNumber+1
            #print(str(NonCircleNumber)+"N")
            line=NonCircleOutput[NonCircleNumber-1]
            line=line.replace("\n","")
            edge=line.split()
            fw.write("\t")
            fw.write("<vehicle id=\""+str(num)+"\" depart=\""+str(num)+".00\">\n")
            fw.write("\t")
            fw.write("\t")
            num=num+1
            i=0
            fw.write("<route edges=\"")
            while i<len(edge):
                fw.write(" "+edge[i])
                i=i+1
            fw.write("\"/>")  
            fw.write("\n")
            fw.write("\t")
            fw.write("</vehicle>\n")
        else:
            CircleNumber=CircleNumber+1
            #print(str(CircleNumber)+"Y")
            line=CircleOutput[CircleNumber-1]
            line=line.replace("\n","")
            edge=line.split()
            fw.write("\t")
            fw.write("<vehicle id=\""+str(num)+"\" depart=\""+str(num)+".00\">\n")
            fw.write("\t")
            fw.write("\t")
            num=num+1
            i=0
            fw.write("<route edges=\"")
            while i<len(edge):
                fw.write(" "+edge[i])
                i=i+1
            fw.write("\"/>")  
            fw.write("\n")
            fw.write("\t")
            fw.write("</vehicle>\n")
    fw.write("</routes>\n")
    fr0.close()
    fr1.close()
    fw.close()
    return flag

#address="D:\\test3\\777"
#mixer(50,30,address)

