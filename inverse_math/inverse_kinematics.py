import numpy as np

if __name__ == '__main__':
    l = 10.0
    
    A = np.array([[-2.0/3.0, 0, 1.0/(3.0*l)],[1.0/3.0, -np.sqrt(3)/3.0, 1.0/(3.0*l)],[1.0/3.0, np.sqrt(3)/3.0, 1.0/(3.0*l)]])
    print(A)

    Fx = 0
    Fy = 10
    T = 0

    X = np.array([Fx, Fy, T]).reshape(3,1)
    print(X)

    Force = np.matmul(A ,X)
    print(Force)
