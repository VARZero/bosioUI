import socket
UDP_IP = "127.0.0.1"
UDP_PORT = 22117
MESSAGE = "12345678SCCREATE00000000name: aaaaaa\nX: 0.5\nY: 0.2\nHeight:0.1"
 
print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)
 
sock = socket.socket(socket.AF_INET, # Internet
                        socket.SOCK_DGRAM) # UDP
sock.bind(('', 0))

sock.sendto(MESSAGE.encode(), (UDP_IP, UDP_PORT))

data, addr = sock.recvfrom(1024)

print(data)