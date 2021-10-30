#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>

#include "plot.h"
#include "dbot.h"


using namespace std;



int main ( int argc, char** argv )
{
  
//     vector<double> x_data = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
//     vector<double> y_data = {2,5,3,6,5,7.5,8,11,11,12,10,11,14,13.5,16,13,15,19,22};
//     int N = x_data.size();
    
    
    double a=0.5, b=1.0;
    int N=100;                          // 数据点
    
    // 噪声Sigma值
    double w_sigma=6.0;   
    
    if(argc == 3){ 
      N = atoi(argv[1]);
      w_sigma = atof(argv[2]);
    }
    
    cv::RNG rng;                        // OpenCV随机数产生器

    vector<double> x_data, y_data;      // 数据

    cout<<"generating data: "<<endl;
    for ( int i=0; i<N; i++ )
    {
        double x = i;
        x_data.push_back ( x );
        y_data.push_back (
             a*x + b + rng.gaussian ( w_sigma )
        );
    }


    double ab[2] = {0,0}; 

    LineFitting lf(x_data,y_data);
    ceres::Solver::Options options;     
    options.linear_solver_type = ceres::DENSE_QR;  // 增量方程
    options.minimizer_progress_to_stdout = true;   
    lf.ceresFitting(ab,options);
    
    
    
    double ab2[2] = {0,0};
    lf.lesqFitting(ab2);
    
    double ab3[2] = {0,0};
    lf.SVDFitting(ab3);
    
    
    
    ////////////////////
    //  Validation and Plot ////
    ////////////////////
    
    const int Cnt = N;
    double X[Cnt] = {0};
    double Y[Cnt] = {0};
    cvNamedWindow("scatter point and line",1);
    CPlot plot;
    
    for(int i = 0; i < Cnt; i++)
    {
	    X[i] = (double)x_data[i];
	    Y[i] = (double)y_data[i];
    }
    plot.plot(X, Y, N, CV_RGB(0,255, 0), '*',false);//依次传入的参数是 X轴数据； Y轴数据； 数据长度； 线条颜色；点描绘类型（默认是'*'）；点与点之间是否需要连接（默认连接） 
//     cvShowImage("hello", plot.Figure);
//     cvWaitKey(0);
    
    for(int i = 0; i < Cnt; i++)
    {
	    X[i] = (double)i;
	    Y[i] = (double)(ab[0]*i - ab[1]);
    }
    plot.plot(X, Y, N, CV_RGB(0,255, 0), 'l');
    
    double X2[Cnt] = {0};
    double Y2[Cnt] = {0};
    
    for(int i = 0; i < Cnt; i++)
    {
	    X2[i] = (double)i;
	    Y2[i] = (double)(ab2[0]*i - ab2[1]);
    }
    plot.plot(X2, Y2, N, CV_RGB(0,255, 180), 'l');
    
    double X3[Cnt] = {0};
    double Y3[Cnt] = {0};
    
    for(int i = 0; i < Cnt; i++)
    {
	    X3[i] = (double)i;
	    Y3[i] = (double)(ab3[0]*i - ab3[1]);
    }
    plot.plot(X3, Y3, N, CV_RGB(50, 255, 40), 'l');
    cvShowImage("scatter point and line", plot.Figure);
    cvWaitKey(0);


    return 0;
}


