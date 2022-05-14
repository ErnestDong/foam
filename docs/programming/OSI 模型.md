---
tags: CS
---
# OSI 模型

## OSI model

上三层数据处理，下三层数据通信， Transport 层是接口

-   Application
    -   http/https、SMTP、FTP 协议等
-   Presentation
    -   translation, data compression, encryption/decryption
-   Session
    -   authentication 验证数据完整性, authorization 授权, session management
    -   建立同步，不一定进行了传输
-   Transport
    -   segmentation, flow control, error control
    -   send data
    -   include TCP(connection-oriented) and UDP(connection-less)
-   Network
    -   use &rsquo;Packet&rsquo;(source IP, Destination IP and Data), determine &rsquo;path&rsquo;
    -   logical addressing IP
-   Data Link
    -   use &rsquo;Frame&rsquo;(source MAC, Destination MAC, Packet and Error detection)
    -   physical addressing MAC
-   Physical
    -   From Bits to Signals

## TCP/IP 四层模型

-   应用层，如 HTTP 等
-   传输层，如 TCP 等
-   网际层，如 IP
-   网络接口层，如 Ethernet
