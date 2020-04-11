# 免密码登录到nanorobot

如果每次懒得输入` ssh nanorobot@192.168.3.50`

就在.bashrc里面添加 `alias pi="ssh nanorobot@192.168.3.50"`

这样每次新建shell，输入pi即可连接到树莓派

下面介绍免密码登录的方法

## 方法一

在电脑 ubuntu 上

```bash
ssh-keygen -t rsa -P ""
```

```bash
linyk3@ThinkPad-S5:~/.ssh$ pwd
/home/linyk3/.ssh
linyk3@ThinkPad-S5:~/.ssh$ ll
总用量 20
-rw-r--r--  1 linyk3 linyk3  397 4月  12  2018 id_rsa.pub     # 把这里的内容全部复制出来
-rw-------  1 linyk3 linyk3 1679 4月  12  2018 id_rsa
-rw-r--r--  1 linyk3 linyk3 3760 11月 13 11:08 known_hosts
drwx------  2 linyk3 linyk3 4096 11月 17 23:36 ./
drwxr-xr-x 38 linyk3 linyk3 4096 11月 17 23:37 ../
```

登录到树莓派上

```bash
cd ~/.ssh/
vi authorized_keys
# 然后将Client (电脑ubuntu) 中 id_rsa.pub 中的公钥复制到Service(树莓派)端的authorized_keys文件中即可
```

## 方法二

简洁操作步骤

摘录一 ：使用ssh-copy-id
在192.168.3.23(电脑ubuntu)机器上

1)运行：ssh-keygen -t rsa

2)然后拍两下回车（均选择默认）

3)运行： 
ssh-copy-id -i ~/.ssh/id_rsa.pub nanorobot@192.168.3.50

4)再输入192.168.3.50(树莓派)机器上的root密码

此时，再ssh 到树莓派，则不需要密码了。相互之间scp，也不需要密码
