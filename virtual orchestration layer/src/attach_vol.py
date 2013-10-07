from xml.etree import ElementTree as ET
 
import libvirt,os
import rbd
import allocate1
import subprocess

def creat_xml(vol_name,hostname):
	xml=r"<disk type='network' device='disk'> 
        	<source protocol='rbd' name='rbd/ "+ vol_name + r"'>
                	<host name="+ hostname + r" port='6789'/>
        	</source>
        	<target dev='hdb' bus='scsi'/>
		</disk>" 
	return xml


 
def attach(attr):
	vmid = attr['vmid']
	volid = attr['volumeid']
	pmid = allocate1.vmlist[int(vmid)][3]
	name = allocate1.vmlist[int(vmid)][0]
	vol_name = allocate1.volumelist[int(volid)][0]
	pmachine = allocate1.machinelist[pmid-1]
        user = pmachine[0]
        ip = pmachine[1]
	f = open("/etc/ceph/ceph.conf",'r') 
	l = f.readlines() 
	l1 = f.split("\n") 
	hostname =l1[2].split('=')[1]
	try:
		conn = libvirt.open(allocate1.path(user,ip))
	except:
		print 'Error: connection not found'
	
	dom = conn.lookupByName(name)
#	template = DISK_TEMPLATE.format(path=path, dev=dev)
	dom.attachDevice(create_xml(vol_name,hostname))
 
#attach_disk('somia', '/mnt/check-disk', 'hdb')
