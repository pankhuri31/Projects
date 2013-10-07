#/usr/bin/python
import libvirt
import allocate1
import rados, rbd
import os

#radosConn=rados.Rados(conffile='/etc/ceph/ceph.conf')
#radosConn.connect()
#POOL_NAME="rbd"
#if POOL_NAME not in radosConn.list_pools():
#	radosConn.create_pool(POOL_NAME)
#	ioctx = radosConn.open_ioctx(POOL_NAME)
#	rbdInstance = rbd.RBD()


def create(attrs):
	try:
		name = attrs['name']
		size = attrs['size']
		print name,size
		actual_size = int(float(size)*(1024**3))
		print actual_size
		create_cmd = 'sudo rbd create ' + name + ' --size ' + str(actual_size)
		print create_cmd
		c = os.system(create_cmd)
		print c
		a = os.system("sudo modprobe rbd")
		print a
		b = os.system('sudo rbd map %s --pool rbd --name client.admin'%(str(name)))
		print b
		volumeid = allocate1.get_volumeid()
		status = 'available'
		allocate1.volumelist[volumeid] = [name, size, status]
		return volumeid
	except:
		print 'Error: Volume not available'
		return 0

		






