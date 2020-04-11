# 查看机器人的topic 信息

可以在机器人端执行，也可以在建立分布式之后的电脑上运行

## 查看电池信息

在树莓派端

```bash
roslaunch base_control base_control.launch # 先把底层一些功能启动起来，才能有电池之类的topic

# 启动另一个shell
rostopic list 							# 看看有哪些topic
rostopic echo /battery		# 查看电池信息
rostopic echo /odom			# 查看位置传感器信息
rostopic echo /tf

```

