# LineFittingMethod

All contributions by zisheng liu
email: lzs_vincent@foxmail.com, and CPLOT

构建依赖
程序通过 Cmake 进行构建与编译，头文件文件夹 include，库文件文件夹 src，生成静态
库链接，实例执行文件 Example.cpp。
所依赖的库为 Opencv3.3.4，Eigen3.3.9，Ceres, STL。


通过用Ceres库，可建立代价函数和残差模型
数据由验证变量和高斯随机数生成，在执行文件时可传入数据点的数量大小和高斯随机的
sigma 方差来确定。
三种方法包装成一个类 LineFitting， 其构造函数为接口，接受数据类型为
vector<double>的待验证数据。
三种方法的接口为 ceresFitting， lesFitting, SVDFitting. 通过数组指针进行传参，输出计
算后的估计参数。其中，ceresFittinbg 还需要传入迭代求解器的相关配置。

此外，还定义了一个基于 opencv 与 c++的坐标系与直线绘制 Cplot 类，可以方便地对数
据与拟合想过进行验证（参考 Github，Cplot）
Cplot 中的 plot 方法作为接口，传入数据点的坐标值，数量和直线的颜色，
Cplot 中的 Figure 方法可传入图像给 opencv 的 cvshowImage 类显示图像。

