#!/usr/bin/python

from __future__ import print_function
import sys, re

def     sys_error(s):
    print ("Error: " + s)
    exit(1)

def     print_help():
    print('''Useage: check.py d [ex1] [ex2] [ex3]

d is a positive number
ex1, ex2 or ex3 is the question number. The default value is ex1.''')
    sys.exit()


if len(sys.argv) <= 1:
    print_help()

max_d = 2
question = 1
for a in sys.argv[1:]:
    if a == 'ex2':
        question = 2
    elif a == 'ex3':
        question = 3
    elif a == 'ex1':
        question = 1
    elif a == 'help' or a == '-h':
        print_help()
    else:
        max_d = int(a)

assert(max_d > 0)

pattern = re.compile('^(readjob|writejob)\s+#\s*(\d+)\s+(waits|enters|exits)')

n_lines = 0
q_readjob_wait = []
q_readjob_active = []
q_writejob_wait = []
q_writejob_active = []

n_readjob_waiting = 0
n_writejob_waiting = 0
n_readjob_active = 0
n_writejob_active = 0

n_session_jobs= 0
session_type = ''

for line in sys.stdin:
    n_lines += 1
    m = re.search(pattern, line)
    if (m):
        print(line, end='')
        # in the pattern, each set of parentheses represents a "group"
        job_number= int(m.group(2), 0)
        # print(m.group(1), m.group(3))

        if m.group(1) == 'readjob':
            if m.group(3) == 'waits':
                if job_number not in q_readjob_wait:
                    q_readjob_wait.append(job_number)
            elif m.group(3) == 'enters':
                if n_writejob_active:
                    sys_error("Line {}: readjob {} starts when there are active writejobs.".format(
                        n_lines, job_number))
                if question == 2 and n_writejob_waiting > 0:
                    sys_error("Line {}: readjob {} starts when there are pending writejobs.".format(
                        n_lines, job_number))
                if session_type != 'r':
                    session_type = 'r'
                    n_session_jobs = 0
                n_session_jobs += 1
                if question == 3 and n_writejob_waiting > 0 and n_session_jobs > max_d: 
                    sys_error("Line {}: more than {} readjobs have started when there are pending writejobs.".format(
                        n_lines, max_d, job_number))
                if job_number in q_readjob_wait:
                    q_readjob_wait.remove(job_number)
                q_readjob_active.append(job_number)
            elif m.group(3) == 'exits':
                q_readjob_active.remove(job_number)
        else:
            if m.group(3) == 'waits':
                if job_number not in q_writejob_wait:
                    q_writejob_wait.append(job_number)
            elif m.group(3) == 'enters':
                if n_readjob_active:
                    sys_error("Line {}: writejob {} starts when there are active readjobs.".format(
                        n_lines, job_number))
                if session_type != 'w':
                    session_type = 'w'
                    n_session_jobs = 0
                n_session_jobs += 1
                if question == 3 and n_readjob_waiting > 0 and n_session_jobs > max_d: 
                    sys_error("Line {}: more than {} writejobs have started when there are pending readjobs.".format(
                        n_lines, max_d, job_number))
                if job_number in q_writejob_wait:
                    q_writejob_wait.remove(job_number)
                q_writejob_active.append(job_number)
            elif m.group(3) == 'exits':
                q_writejob_active.remove(job_number)

        n_readjob_waiting = len(q_readjob_wait)
        n_writejob_waiting = len(q_writejob_wait)
        n_readjob_active = len(q_readjob_active)
        n_writejob_active = len(q_writejob_active)
        if n_readjob_active > max_d:
            sys_error("Line {}: readjob {}. Too many active readjobs.".format(
                n_lines, job_number))
        if n_writejob_active > max_d:
            sys_error("Line {}: readjob {}. Too many active writejobs.".format(
                n_lines, job_number))

        print("RW={} WW={} RA={} WA={}".format(
            n_readjob_waiting, 
            n_writejob_waiting, 
            n_readjob_active, 
            n_writejob_active
            ))

