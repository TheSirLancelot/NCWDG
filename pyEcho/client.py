#!/usr/bin/python

from sys import *
import socket

msgTo = ""
msgFrom = ""

if len(argv) != 3:
    print "Usage: ./client.py [ip] [port]"
else:
    try:
        socket.inet_aton(argv[1])
        ip = argv[1]
    except:
        print "Not a legitimate IP address"
        exit(0)
    if (argv[2].isdigit()) and (int(argv[2]) >= 1024 and int(argv[2]) <= 65535):
        port = int(argv[2])
    else:
        print "Please enter a number between 1024 and 65535"
        exit(0)

#create socket, make reusable, connect to server
mySock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mySock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
mySock.connect((ip, port))

#send messages until user quits
while (msgTo != 'quit') and (msgTo != 'Quit'):
    msgTo = raw_input("Enter your message: ")
    mySock.send(msgTo)
    msgFrom = mySock.recv(4096)
    print msgFrom

mySock.shutdown(1)
mySock.close()
