#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <csignal>
#include <fstream>
#include <zconf.h>
#include <string>
#include <chrono>

#include "MvGmslCamera.h"

#include "sensor/image.pb.h"
#include <ecal/ecal.h>
#include <ecal/ecal_core.h>
#include <ecal/msg/protobuf/publisher.h>
#include <ecal/msg/protobuf/subscriber.h>

using namespace cv;using std::string;
using std::cout; using std::cerr; using std::endl;



struct sample_context{
    string cam_devname;
    string pix_fmt;
    unsigned int cam_w{1280};
    unsigned int cam_h{720};
    unsigned char camera_no;
    struct sync_out_a_cfg_client_t stCameraCfgSend{};
};

static void
print_usage(void) {
    printf("\n\tUsage: example [OPTIONS]\n\n"
           "\tExample: \n"
           "\t./cameras_opencv_demo -d /dev/video0 -s 1280x720\n\n"
           "\tSupported options:\n"
           "\t-d\t\tSet V4l2 video device node\n"
           "\t-s\t\tSet output resolution of video device\n"
           "\t-n\t\tSet sync and async camera no. for example: [-n 2-4] the forward one is sync cameras no 2,the after one is async cameras no 4 (8 sync cameras is setted by default.like [-n 8-0])\n"
           "\t-r\t\tSet sync and async camera freq for example: [-r 30-20] the forward one is sync cameras freq 30,the after one is async cameras freq 20(sync freq 30 is setted by default.like [-r 30-0]) \n"
           "\t-b\t\tSet which cameras you want to trigger.example: [-b 0x0f-0xf0] the forward one is sync cameras which you want trigger,the after one is async cameras which you want trigger(all 8 cameras is setted sync model by default.like[-b 0xff-0])\n"
           "\t-p\t\tSet async cameras is triggered at which angle in a circle,not set by default.\n"
           "\t-h\t\tPrint this usage\n\n"
           "\tNOTE: It runs infinitely until you terminate it with <ctrl+c>\n");
}

static bool
parse_cmdline(struct sample_context *ctx, int argc, char **argv) {
    int c;
    int sync_camera_bit_draw = 0,async_camera_bit_draw = 0;

    if (argc < 2) {
        print_usage();
        exit(EXIT_SUCCESS);
    }

    while ((c = getopt(argc, argv, "d:s:r:n:b:f:p:h")) != -1) {
        switch (c) {
            case 'd':
                ctx->cam_devname = optarg;
        sscanf(ctx->cam_devname.c_str(),"/dev/video%hhu",&ctx->camera_no);
                break;
            case 's':
                if (sscanf(optarg, "%ux%u",&ctx->cam_w, &ctx->cam_h) != 2) {
                    print_usage();
                    return false;
                }
                break;
            case 'r':
                if (sscanf(optarg, "%hhu-%hhu",&ctx->stCameraCfgSend.sync_freq, &ctx->stCameraCfgSend.async_freq) != 2) {
                   print_usage();
                    return false;
                }
                           printf("sync_freq : %d async_freq:%d\n",ctx->stCameraCfgSend.sync_freq,ctx->stCameraCfgSend.async_freq);
                break;
            case 'n':
                if (sscanf(optarg, "%hhu-%hhu",&ctx->stCameraCfgSend.sync_camera_num, &ctx->stCameraCfgSend.async_camera_num) != 2) {
                   print_usage();
                    return false;
                }
                           printf("sync_camera_num : %d async_camera_num:%d\n",(ctx->stCameraCfgSend.sync_camera_num),(ctx->stCameraCfgSend.async_camera_num));
                break;
            case 'b':
                if (sscanf(optarg, "%x-%x",&sync_camera_bit_draw, &async_camera_bit_draw) != 2) {
                   print_usage();
                   return false;
                }
                   ctx->stCameraCfgSend.sync_camera_bit_draw = (unsigned char)sync_camera_bit_draw;
                   ctx->stCameraCfgSend.async_camera_bit_draw = (unsigned char)async_camera_bit_draw;
                   printf("sync_camera_bit_draw : %d async_camera_bit_draw:%d\n",ctx->stCameraCfgSend.sync_camera_bit_draw,ctx->stCameraCfgSend.async_camera_bit_draw);
                break;
           case 'p':
               if (sscanf(optarg, "%hhu-%hhu-%hhu-%hhu-%hhu-%hhu-%hhu-%hhu",
                          &ctx->stCameraCfgSend.async_camera_pos[0], &ctx->stCameraCfgSend.async_camera_pos[1],&ctx->stCameraCfgSend.async_camera_pos[2],
                          &ctx->stCameraCfgSend.async_camera_pos[3],&ctx->stCameraCfgSend.async_camera_pos[4],&ctx->stCameraCfgSend.async_camera_pos[5]
                          ,&ctx->stCameraCfgSend.async_camera_pos[6],&ctx->stCameraCfgSend.async_camera_pos[7]) != 8) {
                   print_usage();
                   return false;
               }
                  printf("pos:[0]:%hhu [1]:%hhu [2]:%hhu [3]:%hhu [4]:%hhu [5]:%hhu [6]:%hhu [7]:%hhu \n",ctx->stCameraCfgSend.async_camera_pos[0],ctx->stCameraCfgSend.async_camera_pos[1],ctx->stCameraCfgSend.async_camera_pos[2],
                  ctx->stCameraCfgSend.async_camera_pos[3],ctx->stCameraCfgSend.async_camera_pos[4],ctx->stCameraCfgSend.async_camera_pos[5],ctx->stCameraCfgSend.async_camera_pos[6],ctx->stCameraCfgSend.async_camera_pos[7]);
               break;
            case 'f':
                ctx->pix_fmt = optarg;
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

int main(int argc, char *argv[])
{
    eCAL::Initialize(argc, argv, "miivii");
    eCAL::Util::EnableLoopback(true);
    eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good!");
    eCAL::protobuf::CPublisher<proto_messages::OpencvImage> pub("miivii");
    proto_messages::OpencvImage pub_data;

    struct sample_context ctx = {};
    ctx.stCameraCfgSend.async_camera_num = 0;
    ctx.stCameraCfgSend.async_freq = 0;
    ctx.stCameraCfgSend.async_camera_bit_draw = 0;
    ctx.stCameraCfgSend.sync_camera_num = 8;
    ctx.stCameraCfgSend.sync_freq = 30;
    ctx.stCameraCfgSend.sync_camera_bit_draw = 0xff;
    ctx.cam_devname = "/dev/video0";
    ctx.cam_w = 1280;
    ctx.cam_h = 720;
    ctx.pix_fmt = "UYVY";
    
    if (!parse_cmdline(&ctx, argc, argv)) {
            return -1;
    }

    char Gstring[256];
    sprintf(Gstring,"v4l2src device=%s ! video/x-raw, width=%d, height=%d, format=UYVY ! appsink",ctx.cam_devname.c_str(),ctx.cam_w,ctx.cam_h);
    miivii::MvGmslCamera mvcam(ctx.stCameraCfgSend);
    cout << "Opening camera..." << endl;
    VideoCapture capture(Gstring, CAP_GSTREAMER);
    if (!capture.isOpened())
    {
        cerr << "ERROR: Can't initialize camera capture" << endl;
        return 1;
    }
    Mat frame;
    Mat frameRaw;
    bool stop = false;
    uint64_t timestamp = 0;
    unsigned int colorConvert;
    if(ctx.pix_fmt == "YUYV")
    {
        colorConvert = COLOR_YUV2BGR_YUYV;
    }
    else
    {
        colorConvert = COLOR_YUV2BGR_UYVY;
    }

    while(eCAL::Ok())
    {
        mvcam.GetGmslTimeStamp(ctx.camera_no,timestamp);
        capture.read(frameRaw);
        cvtColor(frameRaw,frame,colorConvert);
        namedWindow("Video" + std::to_string(ctx.camera_no), 0);
        resizeWindow("Video" + std::to_string(ctx.camera_no), 320, 180);
        imshow("Video" + std::to_string(ctx.camera_no),frame);
        std::cout << "Timestamp from MIIVII  :  " << timestamp << std::endl;

        pub_data.set_rows(frame.rows);
        pub_data.set_cols(frame.cols);
        pub_data.set_elt_type(frame.type());
        pub_data.set_mat_data((char*)frame.data, frame.cols * frame.rows * frame.elemSize());
        pub.Send(pub_data);
        
        eCAL::Process::SleepMS(30);

        //if(waitKey(1)==27)
        //{
        //    stop = true;
        //}
    }
}
