---
tags: cli
---
# docker

`dockerd` 运行在主机上，并通过 `socket` 从客户端访问

docker 有比虚拟机更少的抽象层、利用宿主机的内核，不用加载一个 Guest OS 所以更快

## docker 命令

<https://docs.docker.com/reference/>

有了 image 才可以使用 container

如果使用后台运行 `docker run -d` 时没有程序运行会停止

## docker image

轻量级、可执行的独立软件包

### 联合文件系统 UFS

docker image 实际上是一层层文件系统构成的，不同 image 可以共用相同的基础层

最底层是 bootfs ，包含 bootloader 和 kernel，所有 image 共用；而 rootfs 包含了典型 linux 系统中的其他文件。一个精简的 OS rootfs 可以非常小

### 分层

应用相同的 layer 也会复用

image 都是 read only 的，当容器启动时一个新的可写层被加载到镜像的顶部。 这层是容器层，容器层之下的都是镜像层。操作都在容器层

#### commit 镜像

```shell
docker commit -m="message" -a="ernest" container_id target:tag
```

## 容器数据卷

容器数据共享的技术，将容器内的目录挂载到本地

容器间也可以通过此数据共享，见[4.3]

### `-v` 命令

```shell
docker run -it -v localdir:containerdir ubuntu /bin/bash
```

### Dockerfile

通过 Dockerfile 可以生成镜像

```dockerfile
FROM centos

VOLUME ["volume01"] # 挂载数据卷（匿名挂载，需要 docker inspect 查看挂在哪里

CMD echo "done"

CMD /bin/bash
```

之后 `docker build -f dockerfile -t my/image:tag .`

### 数据卷容器

`docker run -it --name docker02 --volumes-from docker01 my/image:1.0`

docker02 和 docker01 之间容器间共享 volumn01 ，只要有一个容器存在，数据就不会丢失

## dockerfile

用来构建 image 的脚本，每行命令都是一层

### 指令

```dockerfile
FROM scratch
MAINTAINER name<email>
RUN echo "commands"
ADD "emacs.tar.xz"
WORKDIR "/home"
VOLUME []
EXPOSE <port> [<port> ...]
CMD /bin/bash
ENTRYPOINT /bin/bash # 类似 CMD ，但是是从命令行输入追加而非替换
ENV PASSWORD passwd
```