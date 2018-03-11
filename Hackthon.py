from flask import Flask
from flask import request
import cv2
import numpy as np
import copy
import collections
import time
import os
 
app = Flask(__name__)
 
#file_obj = open('xyz','w')
#y = input("Enter status of Trash Bin at (9,9)| 1/0 : ")
#print y





@app.route('/postjson', methods = ['POST'])
	

def postJsonHandler():
	
	
	
	
	c = 0
	#print (request.is_json)
	content = request.get_json()
	#print (content)
	#print (content['Ping'])
	x = (content['Ping'])
	#print x
	
	
	#y = (content['Ping2'])
	#print(y)
	if(x == "F" ):
		print("Waste bin at (5,5) is 100% full") 
		os.system('python HT_maze.py')
		
		
		
		#file_obj.write('(5,5)')
		#file_obj.truncate(0)

		#file_obj.close()
		
		
	if(x == "H"):
		print("Waste bin at (5,5) is 50% full") 
		
		
		#file_obj.write('0')
		#file_obj.truncate(0)

		#file_obj.close()
		
	if(x == "L"):
		print("Waste bin at (5,5) is 0% full") 
		
		#file_obj.write('0')
		#file_obj.truncate(0)

		#file_obj.close()
	if(x == "M"):
		print("Rain Started at location (5,5)") 

		#file_obj.write('0')
		#file_obj.truncate(0)

		#file_obj.close()
	if(x == "T"):
		print("Garbage out at location (5,5)") 

		#file_obj.write('0')
		#file_obj.truncate(0)

		#file_obj.close()

	if(c == 1 and x=='F'):
		print("Waste bin at (5,5) and (9,9) are 100% Full")
		os.system('python seconddust.py')
		c = 0

	#if(count == 0):
	#	print(count)
	#	print("Waste bin at (9,9) is 100% full")
	#	os.system('python onlysecond.py')
	#	count = 1
		

	
	
	
	 
		
	return 'JSON posted'
	

app.run(host='0.0.0.0', port= 8090)



