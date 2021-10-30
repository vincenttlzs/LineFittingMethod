#ifndef _DBOT_H
#define _DBOT_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SVD>
#include <ceres/ceres.h>
#include <chrono>

#include <iostream>
#include <vector>

using namespace std;

struct CURVE_FITTING_COST
{
    CURVE_FITTING_COST ( double x, double y ) : _x ( x ), _y ( y ) {}
    // 残差的计算
    template <typename T>
    bool operator() (
        const T* const ab,     // 模型参数，有2维
        T* residual ) const     // 残差
    {
        residual[0] = T ( _y ) - ab[0]*T(_x) + ab[1]; //ceres::exp ( abc[0]*T ( _x ) *T ( _x ) + abc[1]*T ( _x ) + abc[2] ); // y-exp(ax^2+bx+c)
        return true;
    }
    const double _x, _y;    // x,y数据
};



class LineFitting{
public:
  LineFitting();
  LineFitting(vector<double> x_d, vector<double> y_d);
  
  void ceresFitting(double * const ab, ceres::Solver::Options& op);
  void lesqFitting(double * const ab);
  void SVDFitting(double*const ab);
  
  
private:
  vector<double> x_data;
  vector<double> y_data;
  int N = 0;
  
};


void LineFitting::ceresFitting(double * const ab, ceres::Solver::Options& op)
{
//   double ab[2] = {0,0}; 
  ab[0] = 0;
  ab[1] = 1;
  // 构建最小二乘问题
  ceres::Problem problem;
  for ( int i=0; i<N; i++ )
  {
      problem.AddResidualBlock (     
	  new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 2> ( 
	      new CURVE_FITTING_COST ( x_data[i], y_data[i] )
	  ),
	  nullptr,            // 核函数，这里不使用，为空
	  ab                 // 待估计参数
      );
  }

  // 配置求解器
  ceres::Solver::Options options;     
  options = op;
  ceres::Solver::Summary summary;               
  
  
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  ceres::Solve ( options, &problem, &summary );  // 开始优化
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
  

  // 输出结果
  cout<<summary.BriefReport() <<endl;
  cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<endl;
  cout<<"Ceres method estimated a,b = ";
  cout << ab[0]<< " " << ab[1];
  cout<<endl<<endl;
  
}







#endif