#/usr/bin/python
import allocate1
import libvirt
import os
import json
from flask import jsonify

def view(volumeid):
	status = allocate1.volumelist[int(volumeid)][2]
	vol_info = allocate1.volumelist[int(volumeid)]
	print vol_info
	if status is 'attached':
		return jsonify(volumeid=volumeid,name=vol_info[0],size=vol_info[1],status=vol_info[2],vmid=vol_info[3])
	elif status is "available": 
		return jsonify(volumeid=volumeid,name=vol_info[0],size=vol_info[1],status=vol_info[2])
	else:
		return jsonify({'error':'volumeid: ' + volumeid + 'does not exists'})
		
