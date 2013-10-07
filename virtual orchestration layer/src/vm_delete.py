#/usr/bin/python
import libvirt
import allocate1



def delete(vmid):
	pmid = allocate1.vmlist[int(vmid)][3]
	user = allocate1.machinelist[int(pmid)-1][0]
	ip = allocate1.machinelist[int(pmid)-1][1]
	conn = libvirt.open(allocate1.path(user,ip))
	try:
		vm_id = conn.lookupByName(allocate1.vmlist[int(vmid)][0])
		if vm_id.isActive():
			vm_id.destroy()
		vm_id.undefine()
		del allocate1.vmlist[int(vmid)]
		return 1
	except:
	  	return 0

