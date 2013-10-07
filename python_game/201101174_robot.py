from curses import initscr,curs_set,newwin,endwin,KEY_RIGHT,KEY_LEFT,KEY_DOWN,KEY_UP,color_pair
import random
import curses
class box():
	pass
def A():
	b=box()
	b.F1=70
	b.F2=35
	b.r=3
	b.d=3
	b.D=1
	b.count=0
	def getF1():
		return b.F1
	def getF2():
		return b.F2
	def getd():
		return b.d
	def getr():
		return b.r
	def getCount():
		return b.count
	a=box()
	a.getF1=getF1()
	a.getF2=getF2()
	a.getd=getd()
	a.getr=getr()
	a.getCount=getCount()
	return a
	
def put(i,r,d,F1,F2):
 for i in range(3,r+3):
	robot.append([i,3])
 for i in range(1,d+1):
	x=random.randrange(3,F1-2)
	y=random.randrange(3,F2-2)
	curses.init_pair(4,5,curses.COLOR_BLACK)
	s.addch(y,x,'D',color_pair(4))
	curses.init_pair(3,2,curses.COLOR_BLACK)
	curses.init_pair(2,1,curses.COLOR_BLACK)
 s.addch(random.randrange(5,F2-2),random.randrange(7,F1-2),'B',color_pair(2))

def enemy(F2):
	x=random.randrange(6,40)
	y=random.randrange(10,15)
	enem1=[[x,y],[x+1,y],[x+2,y],[x+1,y-1],[x+1,y+1]]
	curses.init_pair(5,3,curses.COLOR_BLACK)
	for i in enem1:
		s.addch(i[1],i[0],'*',color_pair(5))
	x=random.randrange(6,40)
	y=random.randrange(18,25)
	enem2=[[x,y],[x+1,y],[x+2,y],[x+1,y-1],[x+1,y+1]]
	for i in enem2:
		s.addch(i[1],i[0],'*',color_pair(5))



def displayScore(index):
	global count
	global flag1
	if flag1==1 and count==d*index:
#		curses.init_pair(4,4,curses.COLOR_BLACK)
		s.addstr(3,25,'YOU WIN.!!',curses.color_pair(4)|curses.A_BOLD)
	else:
		s.addstr(3,25,'YOU LOST.!!',curses.color_pair(3)|curses.A_BOLD)
	s.addstr(4,25,'Your score is:'+str(count*10))
	if index==2:
		s.addstr(5,25,'Press enter to exit')
	else:
		s.addstr(5,25,'Press enter to go to next level')
		s.addstr(6,25,'Press escape to exit')
	return -1
	
def moveRobot(robot,key,r):
	flag=0
	global flag1
	global count
	for j in range(0,r):
	   for i in robot:
	   	if i[1]+j==F2-1 or i[1]+j==1 or i[0]==F1-1 or i[0]==1:
	   		flag=1
#			display_score()
	   		break
		if s.inch(i[1]+j,i[0]) & 255 == ord('D'):
			count=count+1
		if s.inch(i[1]+j,i[0]) & 255 == ord('B'):
			flag=1
			flag1=1
			break
		if s.inch(i[1]+j,i[0]) & 255 == ord('*'):
			flag=1
			break
		if key==KEY_RIGHT:
		  	if i==robot[0]:
				s.addch(robot[0][1]+j,robot[0][0],' ')
			else:
				s.addch(i[1]+j,i[0],'x',color_pair(3))
		elif key==KEY_LEFT:
		  	if i==robot[len(robot)-1]:
				s.addch(robot[len(robot)-1][1]+j,robot[len(robot)-1][0],' ')
			else:
				s.addch(i[1]+j,i[0],'x',color_pair(3))
		else:
		  	s.addch(i[1]+j,i[0],'x',color_pair(3))
	   if flag==1: break
	if flag==1: return -1
	if key==KEY_RIGHT:
	 	robot.pop(0)
	if key==KEY_LEFT:
		robot.pop()
def escapeKey(char,s):
#	if char == 27:
		global flag2
		s.erase()
		while True:
			s = newwin(F2,F1,0,40)
			s.timeout(-1)
			curses.init_pair(4,4,curses.COLOR_BLACK)
			s.addstr(4,20,'your score is:'+str(count*10),color_pair(4))
			s.addstr(5,20,'Press enter to exit the game',color_pair(4))
			key=s.getch()
			if key==10:
				flag2=1
	 			break
#				return 
			else:
				continue
for index in range(1,3):	
 inst=A()
 F1=inst.getF1
 F2=inst.getF2
 d=inst.getd
 r=inst.getr
 count=inst.getCount
 initscr()
 curses.start_color()
 curs_set(0)
 s = newwin(F2,F1,0,40)
 s.keypad(1)
 s.nodelay(1)
 curses.noecho()
 s.border('[',']','=','=','*','*','*','*')
#d = random.randrange(1,4)
 robot=[]
 put(index,r,d*index,F1,F2)
 key=KEY_RIGHT
 if index!=1:
 	for i in range(1,index):
		enemy(F2)
 flag1=0
 flag2=0
 flag3=0
 flag4=0
 while True:
	flag2=0
	s.addstr(0,2,'DEFUSE CODES:'+ str(count))
	s.timeout(180)
	char = s.getch()
	if char ==27:
		escapeKey(char,s)
	if char==ord('p') or char==ord('P'):
	     while(1):
		s.timeout(-1)
		curses.init_pair(6,curses.COLOR_CYAN,curses.COLOR_BLACK)
		s.addstr(33,10,'Toggle to continue and ESCAPE to exit',color_pair(6))
		key1=s.getch()
		if key1==ord('p') or key1==ord('P'):
			key=key
			for i in range(10,47):
				s.addch(33,i,' ')
			break
		elif key1==27:
		 	escapeKey(key1,s)
		 	break
	if char==-1 or char!=KEY_UP and char!=KEY_DOWN and char!=KEY_RIGHT and char!=KEY_LEFT:
		key=key
	else:
	 	key=char
	if key==KEY_RIGHT:
		robot.insert(len(robot),[robot[r-1][0]+(key==KEY_RIGHT and 1),robot[r-1][1]])
	elif key==KEY_LEFT:
		robot.insert(0,[robot[0][0]+(key==KEY_LEFT and -1),robot[0][1]])
	if key==KEY_UP:
		for i in robot:
			i[1]=i[1]-1
			s.addch(i[1]+r,i[0],' ')
	if key==KEY_DOWN:
		for i in robot:
			i[1]=i[1]+1
			s.addch(i[1]-1,i[0],' ')
	a=moveRobot(robot,key,r)
	if a==-1:
		s.erase()
		while True:
			s = newwin(F2,F1,0,40)
			s.timeout(-1)
			curses.init_pair(4,curses.COLOR_GREEN,curses.COLOR_BLACK)
			curses.init_pair(3,curses.COLOR_RED,curses.COLOR_BLACK)
			l=displayScore(index)
			key1=s.getch()
			if key1==10:
				flag3=1
				break
			elif key1==27:
				escapeKey(key1,s)
				break
	if flag2==1 or flag3==1: break
#if flag3==1:
#	s.timeout(-1)
	
 if flag2==1: break

endwin()

	
