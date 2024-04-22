import socket

(HOST,PORT) = ('',19126)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT)); s.listen(1); conn, addr = s.accept()

with open('output1.txt','wb') as f:
  while True:
    l = conn.recv(1024)

    if not l:

      break
    print("Données reçues:", l.decode('utf-8'))

    f.write(l)
s.close()