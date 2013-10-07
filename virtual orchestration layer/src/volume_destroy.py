#/usr/bin/python
import allocate1
import libvirt
import os
import rados, rbd

def destroy(volumeid):
	try:
		name = allocate1.volumelist[int(volumeid)][0]
		size = allocate1.volumelist[int(volumeid)][1]
		try:	
			os.system("sudo rbd unmap /dev/rbd/rbd/"+ name)
			os.system("sudo rbd rm " + name)
		except:
			return 0
		status = 'deleted'
		allocate1.volumelist[int(volumeid)]=[name,size,status]
		return 1
	except:
		return 0
