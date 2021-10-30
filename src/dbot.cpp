#include "dbot.h"


using namespace std;

LineFitting::LineFitting(vector<double> x_d, vector<double> y_d){
  x_data = x_d;
  y_data = y_d;
  N = x_data.size();
  
}


//最小二乘求解
void LineFitting::lesqFitting(double*const ab)
{
  int size = N;
  
  Eigen::Matrix<double,Eigen::Dynamic,1> a(size,1);
  for(int i = 0; i < size; ++i) a(i,0) = x_data[i];
  
  Eigen::Matrix<double,Eigen::Dynamic,1> b(size,1);
  for(int i = 0; i < size; ++i) b(i,0) = y_data[i];

  Eigen::Matrix<double, Eigen::Dynamic, 1> tem1(size,1);
  for(int i = 0; i < size; ++i) tem1(i,0) = 1;
// //   Eigen::Matrix<double, Eigen::Dynamic, 1> tem1 = Eigen::DenseBase<double>::Constant(size,1,1);
  Eigen::Matrix<double, Eigen::Dynamic, 2> A(size,2);
  A << a , tem1;  
//   cout << A;  

  Eigen::MatrixXd f(2, 1);
  
  //输出时间
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  f = (A.transpose() *A).inverse() * A.transpose() *b;
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
  cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<endl;
  
//   cout << "Matrix f" << endl;  
  ab[0] = f(0,0);
  ab[1] = -f(1,0);
  
  cout<<"Least squares method estimated a,b = ";
  cout << ab[0]<< " " << ab[1];
  cout<<endl<<endl;

  return;    
}


//SVD分解
void LineFitting::SVDFitting(double*const ab)
{
  int size = N;
  
  Eigen::Matrix<double,Eigen::Dynamic,1> a(size,1);
  for(int i = 0; i < size; ++i) a(i,0) = x_data[i];
  
  Eigen::Matrix<double,Eigen::Dynamic,1> b(size,1);
  for(int i = 0; i < size; ++i) b(i,0) = y_data[i];

  Eigen::Matrix<double, Eigen::Dynamic, 1> tem1(size,1);
  for(int i = 0; i < size; ++i) tem1(i,0) = 1;
// //   Eigen::Matrix<double, Eigen::Dynamic, 1> tem1 = Eigen::DenseBase<double>::Constant(size,1,1);
  Eigen::Matrix<double, Eigen::Dynamic, 2> A(size,2);
  A << a , tem1; 
  
//   cout << A;  
//   Eigen::JacobiSVD<Eigen::Matrix<double, Eigen::Dynamic, 2>> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV );
//   Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> V(svd.matrixV());
//   Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> U(svd.matrixU());
//   Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> S = U.inverse() * A * V.transpose().inverse(); // S = U^-1 * A * VT * -1
//   std::cout<<"A :\n"<<A<<std::endl;
//   std::cout<<"U :\n"<<U<<std::endl;
//   std::cout<<"S :\n"<<S<<std::endl;
//   std::cout<<"V :\n"<<V<<std::endl;
//   std::cout<<"U * S * VT :\n"<<U * S * V.transpose()<<std::endl;
//   cout<<"The least-squares solution is:\n" <<A.bdcSvd(Eigen::ComputeThinU|Eigen::ComputeThinV).solve(b)<<endl;
  
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> f(A.bdcSvd(Eigen::ComputeThinU|Eigen::ComputeThinV).solve(b));
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
  cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<endl;
  
  ab[0] = f(0,0);
  ab[1] = -f(1,0);
  
  cout<<"SVD method estimated a,b = ";
  cout << ab[0]<< " " << ab[1];
  cout<<endl<<endl;

  return;    
}
