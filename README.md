**[BUILD]**

```shell
First make please use sudo 
sudo make -j
```

**[RUN GMSL CAMREA DEMO]**

使用NV自带接口时，参考cameras_egl_demo
使用miivii提供的接口读取图像以及当前图像时间戳时，参考cameras_sdk_demo
使用opencv接口获取相机图像，同时调用miivii接口获取图像时间戳时，参考cameras_opencv_demo
使用miivii接口获取图像以及当前图像时间戳，并不进行opencv库调用时，参考cameras_sdk_noopencv_demo

```shell
./bin/cameras_opencv_demo -s 1280x720 -d /dev/video0 -n 4-4 -r 30-30 -b 0xf-0xf0 -p 0-0-0-0-1-2-3-4
./bin/cameras_sdk_demo -s 1280x720 -d /dev/video0 -n 4-4 -r 30-30 -b 0xf-0xf0 -p 0-0-0-0-1-2-3-4
./bin/cameras_egl_demo -d /dev/video0 -s 1280x720
```
parameter comment:
-d:Set output resolution of video device
-n:Set sync and async camera no. for example: [-n 2-4] the forward one is sync cameras no 2,the after one is async cameras no 4 (8 sync cameras is setted by default.like [-n 8-0])
-r:Set sync and async camera freq for example: [-r 30-20] the forward one is sync cameras freq 30,the after one is async cameras freq 20(sync freq 30 is setted by default.like [-r 30-0])
-b:Set which cameras you want to trigger.example: [-b 0x0f-0xf0] the forward one is sync cameras which you want trigger,the after one is async cameras which you want trigger(all 8 cameras is setted sync model by default.like[-b 0xff-0])
-p:Set async cameras is triggered at which angle in a circle,not set by default.
-h:show help.

同步相机开启方式（以三个摄像头为例）：
./bin/cameras_sdk_demo -d /dev/video0 -s 1280x720 -m 3 -r 30-0
-d：设置打开的第一个摄像头设备号。
-s：设置采集摄像头的分辨率，中间以小写x分隔。
-m：设置打开的摄像头个数。
-r：设置外部触发摄像头的采集频率，“-”前为同步频率，“-”后为异步频率。此例中只打开同步摄像头，所以只设置“-”前的频率为30。


**[SDK CAPACITY]**

GMSL-SDK support custom output image resolutions as well 
 as multiple formats.
 - UYVY
 - YUYV
 - YVYU
 - YUV420M
 - XBGR32
 - ARGB32

 The image format is set to ABGR32 by default.

 Notice that：
 > YUV color system images should only be obtained by method MVGmslGetImage() while RGB color 
 system images should only be obtained by method MVGmslGetCvMat();
