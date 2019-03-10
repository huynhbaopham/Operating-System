#############################################################
#
# Bao Pham
# Operating System
# Project #4: Banker
#
##############################################################

#function.....................................................

#print vector
def printVector (mylist):
    for val in mylist:
        print (' {:3}'.format(val), end="")
    print()
#print matrix
def printMatrice (mylist, row):
    for r in range (row):
        print ('{:3}:'.format(r), end="")
        printVector(mylist[r])
    print()
#print resource type
def printResourceType (col):
    print ("      ", end="")
    for c in range (col):
        print (' {:3}'.format(chr(ord('A')+c)), end="")
    print ()

#for taking argument
import sys
#check number of arguments
if len(sys.argv)!=2:
    print ("Error: This program can only take 1 agrument!")
    exit()

#read data from file..........................................

#open file
try:
    ifile = open(sys.argv[1], "r")
except IOError:
    print (sys.argv[1], ": no such file or directory!")
    exit()
#read all data into data
data = ifile.read().split()
p = 0
#number of processes
n = int(data[p])
p += 1
#number of resources
m = int(data[p])
p += 1
#Allocation Matrices
allocation = []
for r in range (n):
    allocation.append([int(data[p+c]) for c in range(m)])
    p += m
#Max Matrices
max = []
for r in range (n):
    max.append([int(data[p+c]) for c in range(m)])
    p += m
#Available Vector
available = []
for c in range (m):
    available.append(int(data[p+c]))
p += m
#i
i = int(data[p])
p += 2
#Request Vector
request = []
for c in range (m):
    request.append(int(data[p+c]))
#close file
ifile.close()

#Calculating and initializing variable..........................................

#Compute Need
need = []
for r in range (n):
    need.append ([max[r][c] - allocation[r][c] for c in range (m)])

#Finished Vector
finished = []
for r in range (n):
    finished.append(0)

#Work Vector
work = []
for val in available:
    work.append(val)

undone = 0
update = n

#Evaluating.....................................................................

while undone!=update:
    #update number of undone
    undone = update
    #for loop
    for r in range (n):
        #looking for qualified undone process
        if not [c for c, cj in zip(work, need[r]) if c < cj] and finished[r]==0:
            #update work
            for c in range (m): work[c] = work[c] + allocation[r][c]
            #update finished
            finished[r] = 1
            #update update
            update -= 1

#Print report...................................................................
print ("\nTHE REPORT STARTS HERE.................................")
#number of processes and resource types
print ("\nThere are ", n, " processes in the system.\n")
print ("There are ", m, " resource types.\n")
#allocation matrix
print ("The Allocation Matrix is...")
printResourceType(m)
printMatrice (allocation, n)
#max matrix
print ("The Max Matrix is...")
printResourceType(m)
printMatrice (max, n)
#need matrix
print ("The Need Matrix is...")
printResourceType(m)
printMatrice (need, n)
#available vector
print ("The Available Vector is...")
printResourceType(m)
print ("    ", end="")
printVector (available)
#state status
if undone == 0:
    print ("\nTHE SYSTEM IS IN A SAFE STATE!\n")
else:
    print ("\nTHE SYSTEM IS NOT SAFE!\n")
#request vector
print ("The Request Vector is...")
printResourceType(m)
print ('{:3}:'.format(i), end="")
printVector (request)

#evaluating the request
if not [c for c, cj in zip(need[i], request) if c < cj] and not [c for c, cj in zip(available, request) if c < cj]:
    print ("\nTHE REQUEST CAN BE GRANTED!\n")
    #update available
    for c in range (m): available[c] = available[c] - request[c]
    #reprint available vector
    print ("The Available Vector is...")
    printResourceType(m)
    print ("    ", end="")
    printVector (available)
else:
    print ("\nTHE REQUEST CANNOT BE GRANTED!")
print ("\nEND REPORT...............................................\n")







