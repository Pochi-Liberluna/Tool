import socket

# 監視対象のIPアドレスを指定
target_ip = "targetIP"

# 監視するポート番号を指定（ここではすべてのポート）
sniffer = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_IP)
sniffer.bind((target_ip, 0))
sniffer.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)
sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)

try:
    # ファイルに出力するためのオブジェクトを作成
    with open("output.txt", "w") as f:
        while True:
            # パケットを受信する
            data, addr = sniffer.recvfrom(65535)
            # パケットの内容を表示する
            print(f"Packet from {addr}:")
            print(data)
            # ファイルに出力する
            f.write(f"Packet from {addr}:\n")
            f.write(str(data))
            f.write("\n\n")
except KeyboardInterrupt:
    pass

# rawソケットを閉じる
sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_OFF)
