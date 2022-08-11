#include<iostream>
#include<ros/ros.h>
#include<nav_msgs/Odometry.h>
#include<math.h>
#include<fstream>
#include<sstream>
#include<memory>
#include<vector>
#include<climits>
#include<thread>
#include<ctime>

#include<txt_to_rosmsg/cam_data.h>
#define debug

using namespace std;

void extractCam(string Path, vector<vector<string>> &result){
    txt_to_rosmsg::cam_data camData;
    ifstream File(Path);
    string temp;
    vector<string> res;
    while (getline(File, temp))
    {
        stringstream input(temp);
        string out;
        while(input >> out){
            res.push_back(out);
        }
        result.push_back(res);
        res.clear();
    }
    #ifdef debug
    for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++) {
			cout << result[i][j]<<"\t";
			if (j == result[i].size() - 1) cout << endl;
		}
	}
    #endif
    return;
}

double strTodou(string str){  //将string类型转化为double类型       atof(指针)  括号内必须为指针才能使用
    char* ch = new char[0];
    double d;
    for(int i = 0; i < str.length(); ++i){
        ch[i] = str[i];
    }
    d = atof(ch);
    ch = NULL;
    return d;
    return d;
}

int main(int argc, char** argv){

    ros::init(argc, argv, "txt_to_rosmsg");
    ros::NodeHandle nh;
    ros::Publisher pubCam = nh.advertise<txt_to_rosmsg::cam_data>("/cam_data", 1000);

    string camDataPath = "/home/gky/cam1.txt";

    vector<vector<string>> result;

    extractCam(camDataPath, result);
    txt_to_rosmsg::cam_data camData;

    camData.qcl.assign(4, 0);        //对于数组类型的需要先预设大小，否则会越界
    camData.tlc.assign(3, 0);
    camData.q_x.assign(4, 0);

    for(int i = 0; i < result.size(); ++i){
        camData.start_t = strTodou(result[i][0]);
        camData.end_t = strTodou(result[i][1]);
        camData.tcl_length = strTodou(result[i][2]);
        camData.theta_yaw = strTodou(result[i][3]);
        camData.deltaTheta = strTodou(result[i][4]);
        camData.qcl[0] = strTodou(result[i][5]);
        camData.qcl[1] = strTodou(result[i][6]);
        camData.qcl[2] = strTodou(result[i][7]);
        camData.qcl[3] = strTodou(result[i][8]);
        camData.tlc[0] = strTodou(result[i][9]);
        camData.tlc[1] = strTodou(result[i][10]);
       camData.tlc[2] = strTodou(result[i][11]);
        camData.q_x[0] = strTodou(result[i][12]);
        camData.q_x[1] = strTodou(result[i][13]);
        camData.q_x[2] = strTodou(result[i][14]);
        camData.q_x[3] = strTodou(result[i][15]);
        pubCam.publish(camData);
        cout << "camData publish" << endl;
        clock_t last = clock();
        while(clock() - last < 0.05){};
    }

    ros::spin();

    return 0;
}

