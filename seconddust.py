import cv2
import numpy as np

import copy
import collections


list2 = []

solution = []



graph = {}








def buildgraph(k,l,img):
	path1 = [(k+1,l),(k-1,l),(k,l+1),(k,l-1)]
	
	m = (20*(k+1))-10
	n = (20*(l+1))-10

	
	
		
	
	
	print k,l	
	for m in range(m,(m+21),1):
		
		list1 = img[m,n]
		
		if (list1[0]<15 and list1[1]<15 and list1[2]<15):
			 
			 path1.remove((k+1,l))
			
			 break	


	m = (20*(k+1))-10

			
	for m in range(m,(m-21),-1):
		list21 = img[m,n]
		
		if (list21[0]<15 and list21[1]<15 and list21[2]<15):
			 path1.remove((k-1,l))
			
			
			 break	

	m = (20*(k+1))-10
		
	

	for n in range(n,(n+21),1):
		list3 = img[m,n]
		
		if (list3[0]<15 and list3[1]<15 and list3[2]<15):
			 path1.remove((k,l+1))
			 
			
			 break	

	n = (20*(l+1))-10



	for n in range(n,(n-21),-1):
		list4 = img[m,n]
		
		if (list4[0]<15 and list4[1]<15 and list4[2]<15):
			 path1.remove((k,l-1))
			
			 break	

	n = (20*(l+1))-10



	graph[(k,l)] = path1;
	
	
	
	return graph
	











def find_path(graph, start, end, path=[]):
        path = path + [start]
        if start == end:
            return path
        if not graph.has_key(tuple(start)):
            return None
        for node in graph[start]:
            if node not in path:
                newpath = find_path(graph, (node), (end), path)
                if newpath: return newpath
        return None







def find_shortest_path(graph, start, end, path=[]):
	m1 = (20*(start[0]+1))-10
        n1 = (20*(start[1]+1))-10


        #img[m1,n1] = [255,0,0]

        ml = m1-5
        nl = n1-5                                  
        mh = m1+5
        nh = n1+5

       # print ml,nl,mh,nh


        #if(m1 == ((ml+mh)/2) and n1 == ((nl+nh)/2)):
	img2=copy.copy(img[ml:mh,nl:nh])
        img[ml:mh,nl:nh] = [0,0,211]
	cv2.imshow('img1',img)
	cv2.waitKey(200)
	img[ml:mh,nl:nh]=img2
	path = path + [start]
        if start == end:
            return path
        if not graph.has_key(tuple(start)):
            return None
        shortest = None
        for node in graph[start]:
            if node not in path:
                newpath = find_shortest_path(graph, (node), (end), path)
                if newpath:
                    if not shortest or len(newpath) < len(shortest):
                        shortest = newpath
        return shortest














def color(path,img):
	
	
	
	for j in range(0,len(path),1):
		m1 = (20*(path[j][0]+1))-10
		n1 = (20*(path[j][1]+1))-10


		img[m1,n1] = [255,0,0]

		ml = m1-10
		nl = n1-10
		mh = m1+10
		nh = n1+10
		
		#print ml,nl,mh,nh


		if(m1 == ((ml+mh)/2) and n1 == ((nl+nh)/2)):
			
			img[ml:mh,nl:nh] = [200,200,200]

	



		
	return img


img = cv2.imread('abc.jpg')
#ret,img = cv2.threshold(img3,127,255,cv2.THRESH_BINARY)
#img[:] = (200,200,200)
#print(img[100,100])




for k in range(0,10,1):
	for l in range(0,10,1):
		graph1 = buildgraph(k,l,img)
		if (k==9 and l==9):
			
			#print graph1
			break

#file_obj = open("xyz",'r')
#end = file_obj.read()
start  = (0,0)
end = (5,5)
end2 = (9,9)
#count = 0
#while(1):

#	end = file_obj.read()
#	print end
#	if(end == '(5,5)' ):
#		break

#end  = (5,5)

w = find_shortest_path(graph1,start,end)
w1 =  find_shortest_path(graph1,end,end2)
#print "w = ",w
img1 = color(w,img)
img2 = color(w1,img1)




img2[100:110,100:110] = [255,0,0]
img2[180:190,180:190] = [255,0,0]
cv2.imshow('img1',img2)



cv2.waitKey(10000) 



cv2.destroyAllWindows()



