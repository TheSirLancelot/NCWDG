#!/usr/bin/python

from sys import *
import socket

if len(argv) != 3:
    print "Usage: ./server.py [ip] [port]"
else:
    try:
        socket.inet_aton(argv[1]) #Error checking on IP
        ip = argv[1]
    except:
        print "Not a legitimate IP address"
        exit(0)
    #check to see if legit port
    if (argv[2].isdigit()) and (int(argv[2]) >= 1024 and int(argv[2]) <= 65535):
        port = int(argv[2])
    else:
        print "Please enter a number between 1024 and 65535"
        exit(0)

def listen():
    #create socket
    listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #set socket to reusable
    listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    #bind to ip and port
    listener.bind((ip, port));
    #listen for connections (up to 10 in the queue)
    listener.listen(10)
    while True:
        print "Listening for connections..."
        #accept incoming connection
        client, addr = listener.accept()
        #open log file
        FILE = open("log.txt", "w+")
        print "Received connection from ", addr
        while True:
            #receive data
            data = client.recv(4096)
            print "Message received."

            #user wants to quit
            if data == 'quit' or data == 'Quit':
                client.shutdown(1)
                client.close()
                FILE.close()
                print "Connection closed by client"
                exit()
            else:
                #send the message back
                client.send(data)
                FILE.write(data + "\n")
                print "Message sent"

if __name__ == '__main__':
    listen()
