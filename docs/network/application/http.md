---
tags: network
---
# http

http 分为持续连接和非持续连接，在 [[#http 报文]] 中采用`Connection: keep-alive/close`区分

建立在[[TCP]]之上(http3 则是 [[UDP]] 之上的)，常用端口为 80

## http 报文

- 每一行采用 `CRLF` 结尾
- 客户端的 request
  - 第一行 request line 为 `METHOD /dir/file HTTP/x` 的格式，声明 http 方法、版本等
  - 第二行为 `Host: www.xxx.com`，提供给[[#web cache]]
  - 其他均为 `key: value` 对，如 `Connection` 来确定是否为持久链接
  - body 为所发送的文档
- 服务器返回的 response
  - 第一行为 `http/x status_code status_msg` 的格式
  - 可以使用 `Set-cookie` 来设置 cookie，cookie 不可跨域

### 状态码

常见的状态码有：

- 1XX Informational（请求正在处理）
- 2XX Success（请求成功）
- 3XX Redirection（重定向） 需要进行附加操作以完成请求
- 4XX Client Error（客户端错误）
- 5XX Server Error（服务器错误）

具体地：

- 101 Switching Protocols：从 http 转化为 websocket 协议等
- 200 OK：请求已成功
- 204 No Content：服务器成功处理了请求，没有返回任何内容
- 301 Moved Permanently：被请求的资源已永久移动到新位置，并且将来任何对此资源的引用都应该使用本响应返回的若干个URI之一
- 302 Found：要求客户端执行临时重定向，客户端应当继续向原有地址发送以后的请求
- 304 Not Modified：表示资源在由请求头中的If-Modified-Since或If-None-Match参数指定的这一版本之后，未曾被修改
- 400 Bad Request：由于明显的客户端错误（例如，格式错误的请求语法，太大的大小，无效的请求消息或欺骗性路由请求），服务器不能或不会处理该请求
- 401 Unauthorized：表示当前请求需要用户验证
- 403 Forbidden：服务器已经理解请求，但是拒绝执行它。与401响应不同的是，身份验证并不能提供任何帮助，而且这个请求也不应该被重复提交
- 404 Not Found：请求失败，请求所希望得到的资源未被在服务器上发现，但允许用户的后续请求
- 405 Method Not Allowed：请求行中指定的请求方法不能被用于请求相应的资源
- 418 I'm a teapot
- 500 Internal Server Error：通用错误消息
- 501 Not Implemented：服务器不支持当前请求所需要的某个功能
- 502 Bad Gateway：作为网关或者代理工作的服务器尝试执行请求时，从上游服务器接收到无效的响应
- 504 Gateway Timeout：作为网关或者代理工作的服务器尝试执行请求时，未能及时从上游收到响应

## https

使用 SSL/TLS 加密，传输过程中不暴露敏感信息的明文

## web cache

也叫 proxy server，加快访问速度。也可以使用 [[#CDN]]加速。
通过条件 GET 来保证获得的内容不是非常陈旧的，如：
web cache 的 request 发送报文增加 `if-modified-since`，得到服务器返回 `Date` 没有超过则 body 为空 status code 为 `304 Not Modified`，否则把新的内容发到 cache 服务器上，最后 cache 再发送给客户端

## CDN

传输视频采用 DASH 协议。基于 http 协议，使用 manifest 文件告知视频块的信息。客户端先请求 manifest，再根据自身情况来流化播放

通过 CDN 内容分发网络来给大规模用户提供服务

[//begin]: # "Autogenerated link references for markdown compatibility"
[#http 报文]: http.md "http"
[#web cache]: http.md "http"
[#CDN]: http.md "http"
[//end]: # "Autogenerated link references"