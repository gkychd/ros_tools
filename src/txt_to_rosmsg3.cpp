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

void extractOdo(string Path, vector<vector<string>> &result){
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
    delete []ch;
    ch = NULL;
    return d;
}

int main(int argc, char** argv){

    ros::init(argc, argv, "txt_to_rosmsg");
    ros::NodeHandle nh;
    ros::Publisher pubOdo = nh.advertise<nav_msgs::Odometry>("/wheel_odo", 1000);

    string odoDataPath = "/home/gky/odo1.txt";

    vector<vector<string>> result;

    extractOdo(odoDataPath, result);

    nav_msgs::Odometry odoData;
    for(int i = 0; i < result.size(); ++i){
        odoData.header.stamp.sec = strTodou(result[i][0]);
        odoData.header.stamp.nsec = (strTodou(result[i][0]) - odoData.header.stamp.sec) * 1e9;
        odoData.twist.twist.linear.x = strTodou(result[i][1]);
        odoData.twist.twist.linear.y = 0.0;
        odoData.twist.twist.linear.z = 0.0;
        odoData.twist.twist.angular.x = 0.0;
        odoData.twist.twist.angular.y = 0.0;
        odoData.twist.twist.angular.z = strTodou(result[i][2]);
        pubOdo.publish(odoData);
        ROS_INFO("odoData publish");
        clock_t last = clock();
        while(clock() - last < 0.1);
    }

    ros::spin();

    return 0;
}

