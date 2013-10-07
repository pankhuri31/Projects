#/usr/bin/python
from flask import Flask,request,jsonify
import vm_create1
import libvirt
import allocate1
import sys
import vm_delete
import vm_query
import os
import volume_create
import volume_destroy
import vol_query

app = Flask(__name__)

@app.route('/server/vm/create', methods=['GET'])
def index():
#print "Hello, World!"
	a={}
	a['name']=request.args.get('name') 
	a['instance_type']=request.args.get('instance_type')
	a['image_id']=request.args.get('image_id')
	p=vm_create1.create(a)
	return jsonify({'vmid':int(p)})
#	return jsonify(a)
	
@app.route('/server/vm/destroy', methods=['GET'])
def delete():
	vmid = request.args.get('vmid')
	status = vm_delete.delete(vmid)
	return jsonify({'status': status})

	
@app.route('/server/vm/query', methods=['GET'])
def query():
	vmid = request.args.get('vmid')
	d = []
	d = vm_query.view(vmid)
	return jsonify({'vmid':int(d[0]),'name':d[1],'instance_type':d[2],'pmid':d[3]})

@app.route('/server/vm/types')
def types():
	types = allocate1.view_type()
	return types

@app.route('/server/vm/image/list')
def images():
	images = allocate1.view_image()
	return images

@app.route('/server/volume/create')
def create_volume():
	b = {}
	b['name'] = request.args.get('name')
	b['size'] = request.args.get('size')
	p = volume_create.create(b)
	return jsonify({'volumeid':int(p)})

@app.route('/server/volume/destroy')
def destroy_volume():
	volumeid = request.args.get('volumeid')
	status = volume_destroy.destroy(volumeid)
	return jsonify({'status': status})

@app.route('/server/volume/query')
def query_vol():
	volumeid = request.args.get('volumeid')
	d = vol_query.view(volumeid)
	return d

@app.route('/server/volume/attach')
def attach():
	c = {}
	c['vmid'] = request.args.get('vmid')
	c['volumeid'] = request.args.get('volumeid')
	p = attach_vol.attach(c)
	return jsonify({'status':int(p)})


if __name__ == '__main__':
#if len(sys.argv < 2):
#		print "Wrong Format\n"
#		exit(1)
	allocate1.create_machine(sys.argv[1])
	allocate1.create_image(sys.argv[2])
	allocate1.create_type(sys.argv[3])
	
	app.run(debug = True)
