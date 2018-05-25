#include <Eigen/Dense>
#include <iostream>
using namespace std;
int main(){
    double l = 10.0;
    
    Eigen::MatrixXd m(3,3);
    

    m(0,0) = -2.0/3.0;
    m(0,1) = 0;
    m(0,2) = 1.0/(3.0*l);
    
    m(1,0) = 1.0/3.0;
    m(1,1) = -sqrt(3)/3.0;
    m(1,2) = 1.0/(3.0*l);

    m(2,0) = 1.0/3.0;
    m(2,1) = sqrt(3)/3.0;
    m(2,2) = 1.0/(3.0*l);
    cout << m << endl;

    Eigen::VectorXd v(3);
    double Fx, Fy, T;
    Fx = 0;
    Fy = 10.0;
    T = 0;
    v << Fx, Fy, T;
    cout << v << endl;

    cout << m*v << endl;

    return 0;
}
