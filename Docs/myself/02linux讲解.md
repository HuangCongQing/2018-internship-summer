看网上针对*linux基本文件操作文章参差不齐。本文根据个人项目开发经验，主要介绍**linux目录结构，及其文件和文件夹的创建，删除，移动，拷贝**，望初学者少走弯路。

在正式说linux文件操作命令之前，先有人问的一个问题：**为什么现在大多数开发都喜欢用Linux，而不是比如windows等其他操作系统？**
（个人见解非官方）答：
主要说下vxWorks，linux，windows之间的。
* vxWorks
首先vxWorks是美国风河公司推出实时操作系统开发环境，开发推行之后，其性能使其迅速火热起来，曾一度占领嵌入式80%的时长份额，美国的 F-16，爱国者导弹，以及火星探测器都是用的vxWorks。后来，由于vxWorks**开始收费（也不算很贵，1$,大概7￥）**，好多厂家用不起了（想想国内，一个摄像头净利润15块，但要从中再掏出7块给风河公司，这利润差距就大了）。所以现在很多用vxWorks都是国家高精尖的一些产业在用，因为其安全性很高，其他企业就很少用了。
* linux: 
  再说下linux，2008年取代vxworks占领了嵌入式系统，主要其**开源，免费** ，赢得了市场的极大欢迎。而且用Linux的开发成本将远低于vxWorks，所以在市场上迅速普及开来，形成了今天这个局面。

* windows： 
最后说下windows
  * windows主要PC市场 ，而且开发领域很少
  * 经常出现问题，比如**蓝屏，重启**。而且企业中要求**电信级安全性**（出现问题2个小时，恢复一个小时内），windows显然达不到要求！！！

----
好了，下面进入正题了！！！



### linux目录结构：
	windows： 多棵树组成，每个磁盘都是树根
			D:/xxx/yyy/mmm/
	linux：    只有一棵树 ，只有一个树根  "/"
			/xxx/yyy/zzzz/ttt
### 切换目录：cd
	cd   /   :change dir
	cd /home/lsf   切换到个人的桌面
	cd .. 切换到?上一级目录
	cd ../..  切换到上上级
	cd xxxx	  切换到当前目录的xxx目录下
### 显示命令：ls
	ls  是list的缩写
### 创建文件：touch
	touch xxx.c 在当前目录下创建xxx.c
	touch /home/lsf/xxx.c 在/home/lsf/创建

### 目录的创建：mkdir
	mkdir   testdir 在当前目录下创建testdir目录
	mkdir   /home/lsf/ttdir  在其他目录创建ttdir
### 文件的删除：rm
	rm hello.c 删除的是当前目录下文件
	rm  /xxx/yyy/xxx.c 删除其他目录下文件
### 目录的删除：
	rm   testdir  -r  删除当前目录下testdir
	rm   /xx/yy/ttdir 删除其他目录下ttdir

### 文件的拷贝：cp
	cp   xxx.c  目录  : 当前目录下拷贝
	cp   /xxx/yyy/mm.c  /home/lsf/testdir
### 文件的移动：mv
	mv    xxx.c   testdir   当前目录下移动
	mv    /xxx/yy/xx.c  /home/lsf/testdir
### 目录的拷贝：cp
	cp   testdir  dir ： 当前目录下拷贝
	cp    /home/xxx/testdir  /yyy/mmm/dir  
### 目录的剪切：mv
	mv   testdir  dir
	mv   /home/xxx/testdir   /home/lsf/dir

好了，大概linux常用的操作，我都在这一一列举啦，有问题欢迎问我。

![panda.jpg](https://upload-images.jianshu.io/upload_images/4340772-25430ad39314687e.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)