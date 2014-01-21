#!/usr/bin/python

import re,os,sys

def validate(filename):
    if not os.path.exists(filename):
	print 'file not exists'
        return False
    linenum=0
    fp=open(filename,'r')
    line=fp.readline()
    linenum+=1
    if not re.match('^\d+\s+\d+\s*$',line):
	    print 'row and column number not valid at line ',linenum
	    return False
    row,col=re.findall('\d+',line)
    for i in range(int(row)):
        line=fp.readline()
        linenum+=1
        if not re.match('^[A-Z]{%d}\s*$'%int(col),line):
		print 'board not valid at line ',linenum
		return False
    line=fp.readline()
    linenum+=1
    if not re.match('^NO_WRAP|WRAP\s*$',line):
	    print 'mode not valid at line ',linenum
	    return False
    line=fp.readline()
    linenum+=1
    if not re.match('^\d+\s*$',line):
	    print 'word number not valid at line ',linenum
	    return False
    n=int(line)
    for i in range(n):
        line=fp.readline()
        linenum+=1
        if not re.match('^[A-Z]+\s*$',line):
		print 'word not valid at line ',linenum
		return False
    print 'valid input'
    return True

if __name__ == '__main__':
    if len(sys.argv) == 2:
        validate(sys.argv[1])
    else:
        print 'Usage: validate.py filename'
        sys.exit()
        
        
            
