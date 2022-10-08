//
// Created by alex on 18-12-8.
//
//
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <zconf.h>
#include <csignal>
#include <thread>
#include "MvGmslCamera.h"
#include <fstream>
#include <chrono>

using namespace std::chrono;

using std::string;
sig_atomic_t exitRequested = 0;
uint camera_num = 1;

struct sync_out_a_cfg_client_t stCameraCfgSend = {};

char dev_node[32] = "/dev/video0";/*不输入-d参数时，默认开启的第一个的设备*/
std::string camera_fmt_str = "UYVY";/*默认采集的图像格式*/
std::string output_fmt_str = "ABGR32";/*默认输出的图像格式，支持类型见README*/
uint cam_w = 1280;/*不输入-s参数时。默认采集摄像头的分辨率*/
uint cam_h = 720;/*不输入-s参数时。默认采集摄像头的分辨率*/
uint out_w = 320;/*屏幕输出的视频分辨率*/
uint out_h = 180;/*屏幕输出的视频分辨率*/
uint64_t timestampbefore[8] = {0};/*上一次采集图像时采集时间*/
uint64_t LinuxGetFrameTimeBefore[8] = {0};/*上一次采集图像时的系统时间*/

void handler(int) {
    std::cout << "will exit..." << std::endl;
    exitRequested = true;
}
/*图像采集时的时间戳记录，将时间戳间隔与帧数不相符的相关时间信息打印到/tmp/cameras_sdk_demo.log文件中，每个设备生成单独log文件*/
void CheckTimeStampLog(uint64_t timestamp,uint8_t camera_no)
{
    uint64_t FrameInterval = 0;
    char buffer[256] = {0};
    uint64_t LinuxFrameInterval{};
    struct timeval cur_time;
    uint64_t LinuxGetFrameTime{};
    uint64_t time_interval{};
    uint64_t FrameTransferDelay{};
    FILE * file_diff = NULL;
    char file_name[100] = {0};
    if(0 == timestamp)
    {
        /*camera Data is not available during camera preparation*/
        return;
    }
    FrameInterval = timestamp - timestampbefore[camera_no];
    timestampbefore[camera_no] = timestamp;
    gettimeofday(&cur_time, NULL);
    LinuxGetFrameTime = cur_time.tv_sec * 1000000000 + cur_time.tv_usec * 1000;
    LinuxFrameInterval = LinuxGetFrameTime - LinuxGetFrameTimeBefore[camera_no];
    LinuxGetFrameTimeBefore[camera_no] = LinuxGetFrameTime;
    FrameTransferDelay = LinuxGetFrameTime - timestamp;
    if(stCameraCfgSend.sync_freq != 0)
    time_interval = 1000000000 / stCameraCfgSend.sync_freq;
    else{
        time_interval = 1000000000 / stCameraCfgSend.async_freq;
    }
/*    if((FrameInterval > (time_interval + 15000000) || FrameInterval < (time_interval - 15000000)) 
        || (LinuxFrameInterval > (time_interval + 15000000) || LinuxFrameInterval < (time_interval - 15000000)) 
        || FrameTransferDelay < 70000000 || FrameTransferDelay > 90000000)
    {
        printf("camera_no==========%d\n",camera_no);
        printf("timestamp==========%ld\n",timestamp/1000000);
        printf("FrameInterva===-------------=======%ld\n",FrameInterval/1000000);
        printf("LinuxGetFrameTime======------------====%ld\n",LinuxGetFrameTime/1000000);
        printf("LinuxFrameInterval======---------------====%ld\n",LinuxFrameInterval/1000000);
        printf("FrameTransferDelay======-----------------------------------====%ld\n",FrameTransferDelay/1000000);
    }*/
    if(((FrameInterval > (time_interval + 12000000) || FrameInterval < (time_interval - 12000000))) && (FrameInterval != 0))
    {
        sprintf(file_name,"/tmp/cameras_sdk_demo_video%d.log",camera_no);
        file_diff = fopen(file_name,"a+");
        sprintf(buffer,"Timestamp : %ld FrameInterval  :  %ld FrameTransferDelay : %ld LinuxGetFrameTime : %ld LinuxFrameInterval : %ld\n"
                        ,timestamp,FrameInterval,FrameTransferDelay,LinuxGetFrameTime,LinuxFrameInterval);
        fwrite(buffer,sizeof(char),strlen(buffer),file_diff);
        fflush(file_diff);
        fclose(file_diff);
    }
    if(atoi(getenv("CHECK_TIME")))
    {
        printf("Timestamp : %ld FrameInterval : %ld FrameTransferDelay : %ld   LinuxGetFrameTime : %ld LinuxFrameInterval : %ld\n"
                        ,timestamp,FrameInterval,FrameTransferDelay,LinuxGetFrameTime,LinuxFrameInterval);
    }
}
/*demo程序命令相关参数介绍，详细解释见README*/
static void
print_usage(void) {
    printf("\n\tUsage: example [OPTIONS]\n\n"
           "\tExample: \n"
           "\t./cameras_sdk_demo -d /dev/video0 -s 1280x720\n\n"
           "\tSupported options:\n"
           "\t-d\t\tSet V4l2 video device node\n"
           "\t-m\t\tSet V4l2 video num\n"
           "\t-s\t\tSet output resolution of video device\n"
           "\t-n\t\tSet sync and async camera no. for example: [-n 2-4] the forward one is sync cameras no 2,the after one is async cameras no 4 (8 sync cameras is setted by default.like [-n 8-0])\n"
           "\t-r\t\tSet sync and async camera freq for example: [-r 30-20] the forward one is sync cameras freq 30,the after one is async cameras freq 20(sync freq 30 is setted by default.like [-r 30-0]) \n"
           "\t-b\t\tSet which cameras you want to trigger.example: [-b 0x0f-0xf0] the forward one is sync cameras which you want trigger,the after one is async cameras which you want trigger(all 8 cameras is setted sync model by default.like[-b 0xff-0])\n"
           "\t-p\t\tSet async cameras is triggered at which angle in a circle,not set by default.\n"
           "\t-h\t\tPrint this usage\n\n"
           "\tNOTE: It runs infinitely until you terminate it with <ctrl+c>\n");
}
/*demo程序命令相关参数设置接口，详细解释见README*/
static bool
parse_cmdline(int argc, char **argv) {
    int c;
    unsigned int tmp_w;
    unsigned int tmp_h;

    int sync_camera_bit_draw = 0,async_camera_bit_draw = 0;

    if (argc < 2) {
        print_usage();
        exit(EXIT_SUCCESS);
    }

    while ((c = getopt(argc, argv, "d:s:r:n:b:f:p:m:h")) != -1) {
        switch (c) {
            case 'd':
                strcpy(dev_node, optarg);
                break;
            case 's':
                if (sscanf(optarg, "%dx%d",
                           &tmp_w, &tmp_h) != 2) {
                    return false;
                }
                cam_w = tmp_w;
                cam_h = tmp_h;
                break;
                case 'f':
                camera_fmt_str = optarg;
                break;
            case 'm':
                camera_num = strtol(optarg, NULL, 10);
                break;
            case 'r':
                if (sscanf(optarg, "%hhu-%hhu",&stCameraCfgSend.sync_freq, &stCameraCfgSend.async_freq) != 2) {
                   print_usage();
                    return false;
                }
                printf("sync_freq : %d async_freq:%d\n",stCameraCfgSend.sync_freq,stCameraCfgSend.async_freq);
                break;
            case 'n':
                if (sscanf(optarg, "%hhu-%hhu",&stCameraCfgSend.sync_camera_num, &stCameraCfgSend.async_camera_num) != 2) {
                   print_usage();
                    return false;
                }
                           printf("sync_camera_num : %d async_camera_num:%d\n",(stCameraCfgSend.sync_camera_num),(stCameraCfgSend.async_camera_num));
                break;
            case 'b':
                if (sscanf(optarg, "%x-%x",&sync_camera_bit_draw, &async_camera_bit_draw) != 2) {
                   print_usage();
                   return false;
                }
                   stCameraCfgSend.sync_camera_bit_draw = (unsigned char)sync_camera_bit_draw;
                   stCameraCfgSend.async_camera_bit_draw = (unsigned char)async_camera_bit_draw;
                   printf("sync_camera_bit_draw : %d async_camera_bit_draw:%d\n",stCameraCfgSend.sync_camera_bit_draw,stCameraCfgSend.async_camera_bit_draw);
                break;
           case 'p':
               if (sscanf(optarg, "%hhu-%hhu-%hhu-%hhu-%hhu-%hhu-%hhu-%hhu",
                          &stCameraCfgSend.async_camera_pos[0], &stCameraCfgSend.async_camera_pos[1],&stCameraCfgSend.async_camera_pos[2],
                          &stCameraCfgSend.async_camera_pos[3],&stCameraCfgSend.async_camera_pos[4],&stCameraCfgSend.async_camera_pos[5]
                          ,&stCameraCfgSend.async_camera_pos[6],&stCameraCfgSend.async_camera_pos[7]) != 8) {
                   print_usage();
                   return false;
               }
                  printf("pos:[0]:%hhu [1]:%hhu [2]:%hhu [3]:%hhu [4]:%hhu [5]:%hhu [6]:%hhu [7]:%hhu \n",stCameraCfgSend.async_camera_pos[0],stCameraCfgSend.async_camera_pos[1],stCameraCfgSend.async_camera_pos[2],
                  stCameraCfgSend.async_camera_pos[3],stCameraCfgSend.async_camera_pos[4],stCameraCfgSend.async_camera_pos[5],stCameraCfgSend.async_camera_pos[6],stCameraCfgSend.async_camera_pos[7]);
               break;
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
                break;
            default:
                print_usage();
                return false;
        }
    }
    return true;
}
/*demo程序主函数，分别打开n个窗口，并通过反复分别调用GetImageCvMat和GetImagePtr接口获取图像和时间戳在窗口中显示*/
int main(int argc, char *argv[]) {

    camera_context_t ctx[8] = {};

    stCameraCfgSend.async_camera_num = 0;
    stCameraCfgSend.async_freq = 0;
    stCameraCfgSend.async_camera_bit_draw = 0;
    stCameraCfgSend.sync_camera_num = 8;
    stCameraCfgSend.sync_freq = 30;
    stCameraCfgSend.sync_camera_bit_draw = 0xff;

    if (!parse_cmdline(argc, argv)) {
        return -1;
    }
    setenv("CHECK_TIME","0",0);
    char dev_node_tmp = dev_node[10];
    for(int i = 0; i < camera_num; i++){
        dev_node[10] = dev_node_tmp + i;
        ctx[i].dev_node = dev_node;
        ctx[i].camera_fmt_str = camera_fmt_str;
        ctx[i].output_fmt_str = output_fmt_str;
        ctx[i].cam_w = cam_w;
        ctx[i].cam_h = cam_h;
        ctx[i].out_w = out_w;
        ctx[i].out_h = out_h;
    }
    miivii::MvGmslCamera mvcam(ctx, camera_num, stCameraCfgSend);

    std::string windowName("DisplayCamera ");
    for (uint32_t i = 0; i < camera_num; i++) {
        cv::namedWindow(windowName + std::to_string(i), cv::WindowFlags::WINDOW_AUTOSIZE);
        cv::moveWindow(windowName + std::to_string(i), 200 * i, 200 * i);
    }
    cv::Mat outMat[camera_num];
    uint8_t *outbuf[camera_num];
    cv::Mat imgbuf[camera_num];
    signal(SIGINT, &handler);
    bool quit = false;
    uint64_t timestamp;
    while (!quit) {
        if (exitRequested) {
            quit = true;
            break;
        }
        uint8_t camera_no = dev_node[10] - 0x30;
        /*use cv data to get image*/
        if (mvcam.GetImageCvMat(outMat, timestamp, camera_no)) {
            for (uint32_t i = 0; i < camera_num; i++) {
                if ( ctx[i].output_fmt_str == "UYVY") {
                    cv::cvtColor(outMat[i], outMat[i], cv::COLOR_YUV2BGR_UYVY);
                    cv::imshow(windowName + std::to_string(i), outMat[i]);
                } else if (ctx[i].output_fmt_str == "ABGR32") {
                    cv::cvtColor(outMat[i], outMat[i], cv::COLOR_RGBA2BGR);
                    cv::imshow(windowName + std::to_string(i), outMat[i]);
                }
                CheckTimeStampLog(timestamp,dev_node_tmp - 0x30 + i);
            }
        } else {
            std::cerr << "Can't get image form camera." << std::endl;
        }
        if (cv::waitKey(1) == 27) {// Wait for 'esc' key press to exit
            break;
        }
        /*use raw data to get image*/
        if (mvcam.GetImagePtr(outbuf, timestamp, camera_no)) {
            for (uint32_t i = 0; i < camera_num; i++) {
                if ( ctx[i].output_fmt_str == "UYVY") {
                    imgbuf[i] = cv::Mat(out_h, out_w, CV_8UC2, outbuf[i]);
                    cv::Mat mrgba(out_h, out_w, CV_8UC3);
                    cv::cvtColor(imgbuf[i], mrgba, cv::COLOR_YUV2BGR_UYVY);
                    cv::imshow(windowName + std::to_string(i), mrgba);
                } else if (ctx[i].output_fmt_str == "ABGR32") {
                    imgbuf[i] = cv::Mat(out_h, out_w , CV_8UC4, outbuf[i]);
                    cv::cvtColor(imgbuf[i], imgbuf[i], cv::COLOR_RGBA2BGR);
                    cv::imshow(windowName + std::to_string(i), imgbuf[i]);
                }
                CheckTimeStampLog(timestamp,dev_node_tmp - 0x30 + i);
            }
        } else {
            std::cerr << "Can't get image form camera." << std::endl;
        }
        if (cv::waitKey(1) == 27) {// Wait for 'esc' key press to exit
            break;
        }
    }
    return 0;
}
