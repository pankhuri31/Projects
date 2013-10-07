#!/usr/bin/python

import allocate1

def view(vmid):
	a=[]
	a.append(vmid)
	a.append(allocate1.vmlist[int(vmid)][0])
	a.append(allocate1.vmlist[int(vmid)][1])
	a.append(allocate1.vmlist[int(vmid)][3])
	print a

	return a
