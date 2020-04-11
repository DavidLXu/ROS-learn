# 解决ROS分布式通讯的问题

电脑ubuntu 192.168.3.23

树莓派 192.168.3.50

树莓派是主机

在电脑端

修改/etc/hosts，添加上master_ip

![分布式存储master_ip设置](/home/david/文档/分布式存储master_ip设置.png)

淘宝给的教程上，在电脑端就可以直接查看rostoopic list了

但是我的说 ERROR: Unable to communicate with master!

解决方案：在电脑中端输入：

```bash
david@david-HP:~$ export ROS_MASTER_URI=http://192.168.3.50:11311 # 树莓派是master
david@david-HP:~$ export ROS_HOSTNAME=192.168.3.23 # 电脑是其中的一个host
```

此方案只针对当前shell有效

写入到./.bashrc当中，一劳永逸

PS. 事实上，只要` export ROS_MASTER_URI=http://192.168.3.50:11311`就可以了

要不然电脑连不上master



当然，电脑这边连不上master的原因还可能是因为树莓派端没有启动roscore



## 附上一段很好的解释



https://blog.csdn.net/lisfaf/article/details/90444541

vim ~/.bashrc

在最后添加

```bash
export ROS_HOSTNAME=你的hostname

export ROS_MASTER_URI=http://(你想要设置为主机的IP):11311

export ROS_IP=192.168.3.10 (本机的IP)
```



ROS中的ROS_MASTER_URI环境变量解析
原创 单应矩阵 最后发布于2019-05-22 15:59:40 阅读数 2969 收藏
展开

ROS_MASTER_URI=http://localhost:11311中的ROS_MASTER_URI是什么呢？

URI是什么呢？查阅百度百科可知：

URI（Uniform Resource Identifier，统一资源标识符）就是在IMS网络中IMS用户的“名字”，也就是IMS用户的身份标识。别的不管，反正就是个标识。

查阅别人的博文如下：

如果需要远程链接，
需要在远程服务器将ROS_MASTER_URI变为启动roscore的地址，即master地址
比如export ROS_MASTER_URI=http://192.168.1.4:11311
设定master地址之后，启动服务的时候，发现在master服务器上执行rosnode list可见这个服务，但是调用其服务，不能链接。
所以在远程机器上的环境变量还需要添加远程服务器自己的IP（否则默认是主机名，但master根据主机名找不到远程服务器）

所以说，当用电脑A用ROS操作系统控制机器人（B，C，D）时，此时的ROS_MASTER_URI是主机地址，也就是电脑A，不是机器人B，机器人C，机器人D。

那么为什么有了IP地址还需要主机名呢？

查阅百度可知：

ip地址等于身份证号，主机名等于姓名，身份证号是独一无二的

就像身份证，主机名就是你的姓名，让别人可以看到并知道你是谁~~IP地址就像是身份证号，别人喊你不可能喊你的身份证号吧？其他电脑要识别你只能是通过IP地址。其实就是主机名是让其他用电脑的人能知道你是谁？IP地址是让其他的电脑知道你在哪里~~

实际上不管是IP地址还是主机名都是为了标识一台主机或者服务器。IP地址就是一台主机上网时网络给它的一个地址。主机名就相当于又给这台机器取了个名字。你可以取各种各样的名字，如果你要用这个名字去访问这台主机，系统怎么通过这个名字去识别一台主机呢？那么就需要我们配置他们之间的对应关系。配置对应关系在/etc/hosts中配置。在文件中按照对应格式添加IP地址和主机名：比如：192.168.74.134 hostname。

因为要实现各个机器都能够互相识别，所以就要在各个机器上都配置所有节点的主机名和IP之间的对应关系。主机名可以解析为IP地址，IP地址也可以解析为相应的主机名

 

下面将详述具体的配置过程：

首先在终端中查看本机的IP：

$ifconfig

 下拉显示的内容，找到Inet addr,如下图所示，我的ip地址为127.0.0.1

 

然后

vim ~/.bashrc

在最后添加

    export ROS_HOSTNAME=你的hostname
    
    export ROS_MASTER_URI=http://(你想要设置为主机的IP):11311
    
    export ROS_IP=192.168.3.10 (本机的IP)

 下面将解释上面三行代码：

 上面三行代码的export的作用是导入全局变量，因为ROS_HOSTNAME是ROS的全局环境变量，在脚本文件.bashrc中不能直接使用它们，必须得使用export将全局变量导入才能使用它们。

注意，在这里的ROS_MASTER_URI要设置为你想要当作主机的IP，主机从机这里要设置为一致的IP，另外最好加上ROS_IP。

那么对于主机的的.bashrc上面应该设置为：

export    ROS_HOSTNAME=主机的hostname

export    ROS_MASTER_URI=主机的IP：11311（也就是说11311是固定的）

export    ROS_IP=主机的IP地址

那么对于从机的.bashrc上面应该设置为：

export   ROS_HOSTNAME=从机的hostname

export   ROS_MASTER_URI=主机的IP：11311

export   ROS_IP=从机的IP地址

同样的，在主机上修改 /etc/hosts 文件，加入从机的ip及hostname。

第四步：告诉ROS系统，谁才是老大！
分别在主机和从机上使用vim或其他编辑器修改 ~/.bashrc 文件，在末尾加
上
export ROS_HOSTNAME=SLAM
exprot ROS_MASTER_URI=http://10.10.40.174:11311
————————————————
版权声明：本文为CSDN博主「单应矩阵」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/lisfaf/java/article/details/90444541