#!/usr/bin/python
import libvirt
import allocate1
import json
from flask import jsonify
from random import random
import os
import subprocess
from uuid import uuid4

'''def create_xml(vm_name,instance_type,uuid,image_path,cpu,mem,emu_path,domain,arch):
	xml=r"<domain type='" + instance_type + r"'> \
  	      <name>" + vm_name + r"</name> \
	      <memory>" + str((mem*100000)/1024) + r"</memory>					\
	      <uuid>" + uuid + r"</uuid> \
	      <vcpu>" + str(cpu) + r"</vcpu>						\
	      <os>							\
	        <type arch='" + arch + r"' machine='pc'>hvm</type>		\
		<boot dev='hd'/>					\
	      </os>							\
	      <features>						\
	        <acpi/>							\
          	<apic/>							\
	      	<pae/>							\
	      </features>						\
	      <on_poweroff>destroy</on_poweroff>			\
  	      <on_reboot>restart</on_reboot>				\
	      <on_crash>restart</on_crash>				\
	      <devices>							\
	        <emulator>" + emu_path + r"</emulator>	\
	        <disk type='file' device='disk'>			\
  	        <driver name=" + domain + r" type='raw'/>			\
		<source file='" + image_path + r"'/>		\
		<target dev='hda' bus='ide'/>				\
		<address type='drive' controller='0' bus='0' unit='0'/>	\
		</disk>							\
	      </devices>						\
   	      </domain>"
 	return xml'''

def create_xml(vm_name,instance_type,uuid,image_path,cpu,mem,emu_path,domain,arch):
			

        xml=r"<domain type='" + instance_type +r"'>	\
      <name>"+ vm_name +r"</name>	\
      <memory>" + str((mem*100000)/1024) +r"</memory>\
	<uuid>" + uuid + r"</uuid> \
      <vcpu>"+ str(cpu) +r"</vcpu>\
      <os>\
        <type arch='" + arch + r"' machine='pc-1.0'>hvm</type>\
        <boot dev='hd'/>\
      </os>\
      <features>\
        <acpi/>\
        <apic/>\
        <pae/>\
      </features>\
      <clock offset='utc'/>\
      <on_poweroff>destroy</on_poweroff>\
      <on_reboot>restart</on_reboot>\
      <on_crash>restart</on_crash>\
      <devices>\
        <emulator>" + emu_path + r"</emulator>\
        <disk type='file' device='disk'>\
          <driver name=" + domain + r" type='qcow2'/>\
          <source file='" + image_path + r"'/>\
          <target dev='hda' bus='ide'/>\
          <alias name='ide0-0-0'/>\
          <address type='drive' controller='0' bus='0' unit='0'/>\
        </disk>\
        <controller type='ide' index='0'>\
          <alias name='ide0'/>\
          <address type='pci' domain='0x0000' bus='0x00' slot='0x01' function='0x1'/>\
        </controller>\
        <serial type='pty'>\
          <source path='/dev/pts/2'/>\
          <target port='0'/>\
          <alias name='serial0'/>\
        </serial>\
        <console type='pty' tty='/dev/pts/2'>\
          <source path='/dev/pts/2'/>\
          <target type='serial' port='0'/>\
          <alias name='serial0'/>\
        </console>\
        <input type='mouse' bus='ps2'/>\
        <graphics type='vnc' port='5900' autoport='yes'/>\
        <sound model='ich6'>\
          <alias name='sound0'/>\
          <address type='pci' domain='0x0000' bus='0x00' slot='0x04' function='0x0'/>\
        </sound>\
        <video>\
          <model type='cirrus' vram='9216' heads='1'/>\
          <alias name='video0'/>\
          <address type='pci' domain='0x0000' bus='0x00' slot='0x02' function='0x0'/>\
        </video>\
        <memballoon model='virtio'>\
          <alias name='balloon0'/>\
          <address type='pci' domain='0x0000' bus='0x00' slot='0x05' function='0x0'/>\
        </memballoon>\
      </devices>\
      <seclabel type='dynamic' model='apparmor' relabel='yes'>\
        <label>libvirt-10a963ef-9458-c30d-eca3-891efd2d5817</label>\
        <imagelabel>libvirt-10a963ef-9458-c30d-eca3-891efd2d5817</imagelabel>\
      </seclabel>\
    </domain>"

		
	return xml 


def get_instance_type(tid):
	print allocate1.vmtype
	type_list=allocate1.vmtype['types']
	t=[]
	for d in type_list:
		if int(d['tid']) is tid:
			t.append(int(d['cpu']))
			t.append(int(d['ram']))
#	print t
	return t

def pm_number(typelist,cpu_type):
	machine_num = len(allocate1.machinelist)
	while(machine_num > 0):
		pmid = allocate1.get_pmid()
		pmachine = allocate1.machinelist[pmid-1]
		user = pmachine[0]
		ip = pmachine[1]
		try:
			ssh_cmd0 = "ssh " + user+'@'+ip + ' ' + 'cat /proc/cpuinfo | grep lm'
			res = subprocess.check_output(ssh_cmd0,shell='True')
			result = 64
		except:
			result = 32
		ssh_cmd1 = "ssh" +' '+ user+'@'+ip +' '+'nproc'
		try:
			cpu_count = subprocess.check_output(ssh_cmd1,shell='True')
			cpu_count = int(cpu_count[:-1])
		except:
			print 'error'
		ssh_cmd2 = "ssh" +' '+ user+'@'+ip +' '+ 'free -m'
		try:
			free_mem = subprocess.check_output(ssh_cmd2,shell='True')
			free_mem=free_mem.split('\n')
			free_mem=free_mem[1]
			free_mem=free_mem.split()
			free_mem=free_mem[3]
		except:
			print "error"
#	print free_mem,cpu_count
#		print typelist[1],typelist[0]
		if int(free_mem) >= int(typelist[1]) and int(cpu_count) >= int(typelist[0]) and int(result)>= int(cpu_type):
			return pmid
		machine_num = machine_num -1
	return -1
			



def create(attr_vm):
	
	try:
		name = attr_vm['name']
		instance_type = int(attr_vm['instance_type'])
		image_id = int(attr_vm['image_id'])
		machine_from = allocate1.imagelist[image_id-1][0]
		iso_file_path = allocate1.imagelist[image_id-1][1]
		cpu_type = iso_file_path
		cpu_type=cpu_type.split(".") 
		cpu_type=str(cpu_type[0]).split("-")
		print cpu_type
		cpu_type = cpu_type[1]
		cpu_type = cpu_type[3:]
		print cpu_type
		typelist=get_instance_type(instance_type)
		pmid = pm_number(typelist,cpu_type)
		if int(pmid) is int(-1):
			return 0
			
		pmachine = allocate1.machinelist[pmid-1]
		user = pmachine[0]
		ip = pmachine[1]
		uuid = pmachine[2]
		pmid = pmachine[3]
		string_uuid = str(uuid4())
		try:
			conn = libvirt.open(allocate1.path(user,ip))
		except:
			print 'connection not found'

		sys_info = conn.getCapabilities()
		emulator_path = sys_info.split("emulator>")
		emulator_path = emulator_path[1].split("<")[0] #location of xen/qemu
		domain = sys_info.split("<domain type=")
		domain = domain[1].split(">")[0] #type of emulator present on given machine xen/qemu
		arch_type = sys_info.split("<arch>")
		arch_type = arch_type[1].split("<")[0] #archituctue of machine print arch_type
		local_copy = '~/' + 'image'+str(image_id)+'.img'
		if os.path.exists(local_copy) is False:
			scp_command = "scp" + ' ' + machine_from+':'+iso_file_path + ' ' + local_copy + ' 2> /dev/null' 
			os.system(scp_command)
		
		new_iso_path = '/home/'+ user + '/' + 'image'+str(image_id)+'.img'
		scp_command = "scp" + ' ' + local_copy + ' ' + user + '@' + ip + ':' + new_iso_path + ' 2> /dev/null'
		os.system(scp_command)
		try:
			req = conn.defineXML(create_xml(name, conn.getType().lower(),string_uuid,new_iso_path,int(typelist[0]),int(typelist[1]),emulator_path,domain,arch_type))
			vmid = allocate1.get_vmid()
#print req
		except:
			print 'Error: Virtual Machine not defined'
		try:
			req.create()
			print 'Request Completed'
		except:
			print 'Error: Virtual Machine not created'
		#	return jsonify({"vmid":0})
		allocate1.vmlist[vmid] = [name, instance_type, image_id, pmid]
		return vmid
	except:
		print 'Error: Virtual Machine not allocated!'
		return 0
