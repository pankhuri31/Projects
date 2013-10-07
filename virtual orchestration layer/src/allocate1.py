#!/usr/bin/python
from flask import jsonify
from uuid import uuid4
import json
machinelist = []
imagelist = []
vmtype = []
vmlist = {}
volumelist = {}

def create_machine(filename):
	global machinelist
	f = open(filename)
	i=0
	for line in f.readlines():
		line = line[:-1]
		if line:
#			ssh_cmd = "ssh" + ' ' + line
#os.system(ssh_cmd)
			machine = line.split('@')
			machinelist.append(machine + [str(uuid4())])
			machinelist[i].append(i+1)
			

		i = i + 1
#	print machinelist

def create_type(filename):
	global vmtype
	f = open(filename)
	vmtype = json.load(f)
#	print vmtype

def view_type():
	global vmtype
	return jsonify(vmtype)

def view_image():
	global imagelist
	dd={}
	l=[]
	for i in imagelist:
		d={}
		d['id']=i[2]
		tmp=str(i[1]).split('.')
		d['name']=tmp[0]
		l.append(d)
	dd['images']=l
	return jsonify(dd)
			
		
def create_image(filename):
	global imagelist
	f = open(filename)
	i=0
	for line in f.readlines():
		line = line[:-1]
		if line:
			im = line.split(':')
			imagelist.append(im)
			imagelist[i].append(i+1)
		i = i+1
#	print imagelist
	
pmid=0
def get_pmid():
	global pmid
	pmid=pmid+1
	pmid = pmid%len(machinelist)
	if pmid is 0:
		return 3
	return pmid

vmid=0
def get_vmid():
	global vmid
	vmid = vmid + 1 
	return vmid

volumeid=0
def get_volumeid():
	global volumeid
	volumeid = volumeid + 1
	return volumeid

def path(user,ip):
	path = 'remote+ssh://' + user + '@' + ip + '/'
#	path = 'qemu:///system'
	return path
#create_machine()



#def create_imagelist(filename):
#	f = open('Images')
#	for line in f.readlines():

			
