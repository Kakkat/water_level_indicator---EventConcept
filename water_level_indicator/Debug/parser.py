
import sys

filepath = 'water_level_indicator.map'
outfilepath='debug.txt'
infile = open(filepath)
intext = infile.readlines()
infile.close
cnt=0
line2=[]
address=[]
dataset={}
common=[]
linecount=0
done=0
commoncount=0
commonAdd=[]
commoncountadd=0
for line in intext:
 linecount=linecount+1
 if line.find("0x0080") >= 0 and line.find(".bss.")>=0 :
    cnt=cnt+1
    dataset={}
    dataset["address"]=line.split("0x0080")[1].split(" ")[0].upper()
    dataset["name"]=line.split("0x0080")[0].split(".bss.")[1].strip()
    dataset["size"]=line.split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
    if int(line.split("0x0080")[1].split("0x")[1].split(" ")[0],16)<16:
      dataset["size"]="0"+line.split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
    address.append(dataset)
 elif line.find("0x0080") >= 0 and line.find(".data.")>=0 :
    cnt=cnt+1
    dataset={}
    dataset["address"]=line.split("0x0080")[1].split(" ")[0].upper()
    dataset["name"]=line.split("0x0080")[0].split(".data.")[1].strip()
    dataset["size"]=line.split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
    if int(line.split("0x0080")[1].split("0x")[1].split(" ")[0],16)<16:
      dataset["size"]="0"+line.split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
    address.append(dataset)
 elif line.find("0x0080") >= 0 and line.find(".rodata.")>=0 :
    cnt=cnt+1
    dataset={}
    dataset["address"]=line.split("0x0080")[1].split(" ")[0].upper()
    dataset["name"]=line.split("0x0080")[0].split(".rodata.")[1].strip()
    dataset["size"]=line.split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
    if int(line.split("0x0080")[1].split("0x")[1].split(" ")[0],16)<16:
      dataset["size"]="0"+line.split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
    address.append(dataset)
 elif line.find(".bss.") >= 0 and line.find("0x") < 0 and line.find("rel") < 0:
    dataset={}
    if intext[linecount].find("0x0080")>=0:
      dataset["address"]=intext[linecount].split("0x0080")[1].split(" ")[0].upper()
      dataset["name"]=line.split(".bss.")[1].strip()
      dataset["size"]=intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
      if int(intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0],16)<16:
        dataset["size"]="0"+intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
      address.append(dataset)
      cnt=cnt+1
 elif line.find(".data.") >= 0 and line.find("0x") < 0 and line.find("rel") < 0:
    dataset={}
    if intext[linecount].find("0x0080")>=0:
      dataset["address"]=intext[linecount].split("0x0080")[1].split(" ")[0].upper()
      dataset["name"]=line.split(".data.")[1].strip()
      dataset["size"]=intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
      if int(intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0],16)<16:
        dataset["size"]="0"+intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
      address.append(dataset)
      cnt=cnt+1
 elif line.find(".rodata.") >= 0 and line.find("0x") < 0 and line.find("rel") < 0:
    dataset={}
    if intext[linecount].find("0x0080")>=0:
      dataset["address"]=intext[linecount].split("0x0080")[1].split(" ")[0].upper()
      dataset["name"]=line.split(".rodata.")[1].strip()
      dataset["size"]=intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
      if int(intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0],16)<16:
        dataset["size"]="0"+intext[linecount].split("0x0080")[1].split("0x")[1].split(" ")[0].upper()
      address.append(dataset)
      cnt=cnt+1
 elif  line.find("Allocating common symbols") >= 0 and commoncount<=0:
    commoncount=linecount+2
    while intext[commoncount].find("Discarded input sections"):
     if intext[commoncount].find("0x")>0:
      common.append(intext[commoncount])
     commoncount=commoncount+1
 elif line.find("*(COMMON)")>=0 and done==0:
   commonstartaddress=intext[linecount].split("0x0080")[1].split(" ")[0].upper()
   print ((int(commonstartaddress,16)))
   done=1
   commoncountadd=linecount
   while intext[commoncountadd].find("PROVIDE (__bss_end, .)")<0:
     if intext[commoncountadd].find("0x")>0:
      commonAdd.append(intext[commoncountadd])
     commoncountadd=commoncountadd+1
   size=0
   for com in common:
    for comadd in commonAdd:
        if comadd.split("0x0080")[1].split(" ")[len(comadd.split("0x0080")[1].split(" "))-1].strip().find(com.split(" ")[0].strip())==0 and com.split(" ")[0].strip().find(comadd.split("0x0080")[1].split(" ")[len(comadd.split("0x0080")[1].split(" "))-1].strip())==0:
          print (comadd.split("0x0080")[1].split(" ")[len(comadd.split("0x0080")[1].split(" "))-1].strip())
          print (com.split(" ")[0].strip())
          dataset={}
          dataset["address"]=comadd.split("0x0080")[1].split(" ")[0].strip().upper()
          dataset["name"]=com.split(" ")[0].strip()
          if int(com.split("0x")[1].split(" ")[0],16)<16:
            dataset["size"]="0"+ com.split("0x")[1].split(" ")[0].upper()
          else:
            dataset["size"]=com.split("0x")[1].split(" ")[0].upper()
          size=int(com.split("0x")[1].split(" ")[0],16)
          address.append(dataset)
autocode=""
for add in address:
  autocode=autocode+add["name"]+" "+add["address"]+" "+add["size"]+"\n"
  print (add)
outfile=open(outfilepath,'w')
outfile.writelines(autocode)
#for add in address:
 #for line in intext:
   #if line.find(add)>=0:
    #print(line)