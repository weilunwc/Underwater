#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"


const double YsPi=3.1415927;
double aspect1 = 4/3;
double nscale = 2;




class matri4x4
{
public:
    double mat [4][4]; // row col
    matri4x4();
    matri4x4(double * input);
    matri4x4 mult(matri4x4 input);
    void matri4x4::printtmat();
};
matri4x4::matri4x4(){

}

matri4x4::matri4x4(double * input){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            mat[i][j] = input[i*4 + j];
        }
    }
}

void matri4x4::printtmat(){
	for (int i = 0; i < 4; i ++){
		//printf("%f %f %f %f\n",mat[i][0],mat[i][1],mat[i][2],mat[i][3]);
	}
	//printf("\n");
}

matri4x4 matri4x4::mult(matri4x4 input){
    matri4x4 temp;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            temp.mat[j][i] = mat[i][0]*input.mat[0][j] + mat[i][1]*input.mat[1][j] + mat[i][2]*input.mat[2][j] + mat[i][3]*input.mat[3][j];
        }
    }
    return temp;
}

matri4x4 getXRot(double p){
    double arrayt[] = {1,0,0,0,
                       0,cos(p),-1*sin(p),0,
                       0,sin(p),   cos(p),0,
                       0,0,0,1};
    matri4x4 temp(arrayt);
    return temp;
}

matri4x4 getYRot(double h){
    double arrayt[] = {cos(h),0,sin(h),0,
                       0,1,0,0,
                       -1*sin(h),0,cos(h),0,
                       0,0,0,1};
    matri4x4 temp(arrayt);
    return temp;
}

matri4x4 getZRot(double b){
    double arrayt[] = {cos(b),-1*sin(b),0,0,
                       1*sin(b),cos(b),0,0,
                       0,0,1,0,
                       0,0,0,1};
    matri4x4 temp(arrayt);
    return temp;
}

matri4x4 getTrans(double x, double y, double z){
    double arrayt[] = {1,0,0,x,
                       0,1,0,y,
                       0,0,1,z,
                       0,0,0,1};
    matri4x4 temp(arrayt);
    return temp;
}





class Vec
{

public:
    double x = 0;
    double y = 0;
    double z = 0;
    Vec(){};
    Vec(double initx, double inity, double initz){
        x = initx;
        y = inity;
        z = initz;  
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getZ(){
        return z;
    }
    Vec multMatr(matri4x4 inputmat){
    	double tx = inputmat.mat[0][0]*x + inputmat.mat[0][1]*y + inputmat.mat[0][2]*z + inputmat.mat[0][3];
    	double ty = inputmat.mat[1][0]*x + inputmat.mat[1][1]*y + inputmat.mat[1][2]*z + inputmat.mat[1][3];
    	double tz = inputmat.mat[2][0]*x + inputmat.mat[2][1]*y + inputmat.mat[2][2]*z + inputmat.mat[2][3];
    	Vec newVec(tx,ty,tz);
    	return newVec;
    }
    Vec add(Vec input){
    	double newx = x + input.x;
    	double newy = y + input.y;
    	double newz = z + input.z;
    	Vec newVec(newx,newy,newz);
    	return newVec;
    }

};

Vec calNormal(Vec p1, Vec p3, Vec p2){
	Vec tempVec;
    tempVec.x = p2.x - p1.x;
    tempVec.y = p2.y - p1.y;
    tempVec.z = p2.z - p1.z;
    Vec tempVec2;
    tempVec2.x = p3.x - p1.x;
    tempVec2.y = p3.y - p1.y;
    tempVec2.z = p3.z - p1.z;
    Vec norm;
    norm.x = (tempVec.y * tempVec2.z) - (tempVec.z * tempVec2.y);
    norm.y = (tempVec.z * tempVec2.x) - (tempVec.x * tempVec2.z);
    norm.z = (tempVec.x * tempVec2.y) - (tempVec.y * tempVec2.x);
    double total = sqrt(norm.x * norm.x + norm.y*norm.y + norm.z*norm.z);
	norm.x=norm.x/total;
	norm.y=norm.y/total;
	norm.z=norm.z/total;
	return norm;
}

class Triangle
{
public:
	Vec norm;
	Vec points[3];
	Triangle(){
		for(int i = 0; i < 3; i++){
			points[i] = Vec();
		}
	}
	Triangle(Vec p1, Vec p2, Vec p3){
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
		norm = calNormal(p1,p2,p3);
		
	}
	void updateNorm(){
		norm = calNormal(points[0],points[1],points[2]);
	}
};

class Square
{
    
public: 
	Vec norm;
    Vec points[4];
    Square(){
        for (int i = 0; i < 4; i++){
            points[i] = Vec();
        }
    }
    Square(Vec p1, Vec p2, Vec p3, Vec p4);

    void updatePoints(std::vector<Vec> inpoints){
        for (int i = 0; i < 4; i++){
            points[i] = inpoints[i];
        }
    }

};

Square::Square(Vec p1, Vec p2, Vec p3, Vec p4){
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    norm = calNormal(p1,p2,p3);

}

class Cylinder{
public:
	Vec Color;
	Triangle sides[120];
	double x,y,z;
	double rad, hei;
	double h,b,p;	
	Cylinder(){
		for(int i = 0; i < 120; i ++){
			sides[i] = Triangle();
		}
	}
	Cylinder(double inx, double iny, double inz, double inrad, double inhei, double inh, double inp, double inb,Vec incolor){
		Color = incolor;
		std::vector<Vec> np;
		for(int i = 0; i < 30; i++){
			np.push_back(Vec(inrad*cos(i*2*YsPi/30.0),inhei/2,inrad*sin(i*2*YsPi/30.0)));

		}
		for(int i = 0; i < 30; i++){
			np.push_back(Vec(inrad*cos(i*2*YsPi/30.0),inhei/-2,inrad*sin(i*2*YsPi/30.0)));
		}
		for(int i = 0; i < 30; i++){
			sides[i] = Triangle(Vec(0,inhei/2,0),np[i],np[(i+1)%30]);
			sides[i+30] = Triangle(Vec(0,inhei/-2,0),np[30+((i+1)%30)],np[i+30]);
			sides[i+60] = Triangle(np[i],np[30+i],np[30+(i+1)%30]);
			sides[i+90] = Triangle(np[i],np[30+(i+1)%30],np[(i+1)%30]);
		}
		matri4x4 getRoll = getZRot(inb);
		getRoll.printtmat();
		matri4x4 getYaw = getYRot(inp);
		getYaw.printtmat();
		matri4x4 getPitch = getXRot(inh);
		getPitch.printtmat();
		matri4x4 combine = (getRoll.mult(getYaw));
		combine = combine.mult(getPitch);
		combine.printtmat();

		for(int i = 0; i < 120; i++){
			for(int j = 0; j < 3; j++){
				sides[i].points[j] = sides[i].points[j].multMatr(combine);
			}
		}
		Vec addvec = Vec(inx,iny,inz);
		for(int i = 0; i < 120; i++){
			for(int j = 0; j < 3; j++){
				sides[i].points[j] = sides[i].points[j].add(addvec);
				sides[i].updateNorm();
			}
		}

	}
	void Cylinder::Draw(){
		glBegin(GL_TRIANGLES);
		glColor3f(Color.x,Color.y,Color.z);
		for(int i = 0; i < 120; i++){
			glNormal3f(sides[i].norm.x,sides[i].norm.y,sides[i].norm.z);
			for(int j = 0; j < 3; j++){
				glVertex3f(sides[i].points[j].x,sides[i].points[j].y,sides[i].points[j].z);
				//printf("%d %d %f %f %f\n",i,j,sides[i].points[j].x,sides[i].points[j].y,sides[i].points[j].z);
				//printf("%f %f %f\n",sides[i].norm.x,sides[i].norm.y,sides[i].norm.z);
			}
		}
		glEnd();
	}
};


class RecPrism{
public:
	Vec Color;
	Triangle sides[12];
	double x,y,z;
	double wid,len,hei;
	double h,b,p;
	RecPrism(){
		for(int i = 0; i < 12; i++){
			sides[i] = Triangle();
		}
	}
	RecPrism(double inx, double iny, double inz, double inwid, double inhei, double inlen, double inh, double inp, double inb, Vec incolor){
		Color = incolor;
		std::vector<Vec> np;
		np.push_back(Vec(inwid/2,inhei/-2,inlen/-2)); // r b ba  0
		np.push_back(Vec(inwid/2,inhei/-2,inlen/2)); // r b fr   1
		np.push_back(Vec(inwid/-2,inhei/-2,inlen/2)); // l b fr  2
		np.push_back(Vec(inwid/-2,inhei/-2,inlen/-2)); // l b ba 3
		np.push_back(Vec(inwid/2,inhei/2,inlen/-2));  // r t ba  4
		np.push_back(Vec(inwid/2,inhei/2,inlen/2));  // r t fr   5
		np.push_back(Vec(inwid/-2,inhei/2,inlen/2)); // l t fr   6
		np.push_back(Vec(inwid/-2,inhei/2,inlen/-2));  // l t ba 7
		sides[0] = Triangle(np[0],np[2],np[1]);
		sides[1] = Triangle(np[0],np[3],np[2]);
		sides[2] = Triangle(np[0],np[4],np[7]);
		sides[3] = Triangle(np[0],np[7],np[3]);
		sides[4] = Triangle(np[4],np[5],np[6]);
		sides[5] = Triangle(np[4],np[6],np[7]);
		sides[6] = Triangle(np[1],np[6],np[5]);
		sides[7] = Triangle(np[1],np[2],np[6]);
		sides[8] = Triangle(np[0],np[5],np[4]);
		sides[9] = Triangle(np[0],np[1],np[5]);
		sides[10] = Triangle(np[3],np[6],np[2]);
		sides[11] = Triangle(np[3],np[7],np[6]);
		matri4x4 getRoll = getZRot(inb);
		getRoll.printtmat();
		matri4x4 getYaw = getYRot(inp);
		getYaw.printtmat();
		matri4x4 getPitch = getXRot(inh);
		getPitch.printtmat();
		matri4x4 combine = (getRoll.mult(getYaw));
		combine = combine.mult(getPitch);
		combine.printtmat();

		for(int i = 0; i < 12; i++){
			for(int j = 0; j < 3; j++){
				sides[i].points[j] = sides[i].points[j].multMatr(combine);
			}
		}
		Vec addvec = Vec(inx,iny,inz);
		for(int i = 0; i < 12; i++){
			for(int j = 0; j < 3; j++){
				sides[i].points[j] = sides[i].points[j].add(addvec);
				sides[i].updateNorm();
			}
		}
	}
	void RecPrism::Draw(){
		glBegin(GL_TRIANGLES);
		glColor3f(Color.x,Color.y,Color.z);
		for(int i = 0; i < 12; i++){
			glNormal3f(sides[i].norm.x,sides[i].norm.y,sides[i].norm.z);
			for(int j = 0; j < 3; j++){
				glVertex3f(sides[i].points[j].x,sides[i].points[j].y,sides[i].points[j].z);
				//printf("%d %d %f %f %f\n",i,j,sides[i].points[j].x,sides[i].points[j].y,sides[i].points[j].z);
				//printf("%f %f %f\n",sides[i].norm.x,sides[i].norm.y,sides[i].norm.z);
			}
		}
		glEnd();
	}
};


class Robot
{

	class CameraObject{
	public:
    double x,y,z;
    double h,p,b;

    double fov,nearZ,farZ;

    CameraObject();
    void Initialize(void);
    void SetUpCameraProjection(void);
    void SetUpCameraProjectionOrtho(void);
    void SetUpCameraTransformation(void);
    void SetUpCameraTransformation3d(void);
    void Robot::CameraObject::EulertoRot(Robot rob);
    void SetUpObjectTransformation(Robot rob);
    void SetUpObjectTransformation3d(Robot rob);
    void GetForwardVector(double &vx,double &vy,double &vz);
	};

public:
    double x,y,z;
    double h,p,b;
    RecPrism box;
    Cylinder cyn;
    Cylinder jcyn[3];
    Cylinder mcyn[3];
    Cylinder wcyn[3];
    CameraObject camera1;
    CameraObject camera2;
    CameraObject camera3;
    CameraObject camera4;
    Robot();
    Robot(double inw, double inh, double inl);
    void Draw();
    void UpdatePos(double x1, double y1, double z1);
    void UpdateRot(double h1, double p1, double b1);
    void Move(double x1, double y1, double z1);
    void MoveTo(double x1, double y1, double z1);
    void Init();
    void MoveToX(double x1);
    void MoveToY(double y1);
    void MoveToZ(double z1);
    void Robot::Rot(double h1,double p1, double b1);
    void Robot::RotTo(double h1,double p1, double b1);
    void RotH(double h1);
    void RotP(double p1);
    void RotB(double b1);
    bool Run(double xx, double yy, double zz,double rr,double pp, double yawyaw);
};
Robot::Robot(){}
Robot::Robot(double inw, double inh, double inl){
    x = 0;
    y = 0;
    z = 0;
    h = 0;
    p = 0;
    b = 0;
    box = RecPrism(0,0,0,inw,inh,inl,0,0,0,Vec(0,1,0));
    cyn = Cylinder(0,0,0,.5,.02,0,0,0,Vec(0,1,0));


    mcyn[0] = Cylinder(.3*sin(YsPi/3),.05,.3*cos(YsPi/3),.05,.25,YsPi/2,0,YsPi/3,Vec(0,0,1));
    mcyn[1] = Cylinder(.3*sin(YsPi/-3),.05,.3*cos(YsPi/-3),.05,.25,YsPi/2,0,-1*YsPi/3,Vec(0,0,1));
    mcyn[2] = Cylinder(0,.05,-.3,.05,.25,YsPi/2,0,0,Vec(0,0,1));


    jcyn[0] = Cylinder(.3*sin(2*YsPi/3),.1,.3*cos(2*YsPi/3),.07,.2,0,0,0,Vec(1,0,0));
    jcyn[1] = Cylinder(.3*sin(-1*2*YsPi/3),.1,.3*cos(-1*2*YsPi/3),.07,.2,0,0,0,Vec(1,0,0));
    jcyn[2] = Cylinder(0,.1,.3,.07,.2,0,0,0,Vec(1,0,0));


    wcyn[0] = Cylinder(.6*sin(YsPi/3),.05,.6*cos(YsPi/3),.15,.02,YsPi/2,0,YsPi/3,Vec(0,0,1));
    wcyn[1] = Cylinder(.6*sin(YsPi/-3),.05,.6*cos(YsPi/-3),.15,.02,YsPi/2,0,-1*YsPi/3,Vec(0,0,1));
    wcyn[2] = Cylinder(0,.05,-.6,.15,.02,YsPi/2,0,0,Vec(0,0,1));

};

void Robot::Move(double x1,double y1, double z1){
	UpdatePos(x+x1,y+y1,z+z1);
}
void Robot::MoveTo(double x1,double y1, double z1){
	UpdatePos(x1,y1,z1);
}
void Robot::MoveToX(double x1){
	UpdatePos(x1,y,z);
}
void Robot::MoveToY(double y1){
	UpdatePos(x,y1,z);
}
void Robot::MoveToZ(double z1){
	UpdatePos(x,y,z1);
}
void Robot::Rot(double h1,double p1, double b1){
	UpdateRot(h+h1,p+p1,b+b1);
}
void Robot::RotTo(double h1,double p1, double b1){
	UpdateRot(h1,p1,b1);
}
void Robot::RotH(double h1){
	UpdatePos(h1,y,z);
}
void Robot::RotP(double p1){
	UpdatePos(x,p1,z);
}
void Robot::RotB(double b1){
	UpdatePos(x,y,b1);
}

void Robot::UpdateRot(double h1, double p1, double b1){
	h = h1;
	p = p1;
	b = b1;
}
void Robot::UpdatePos(double x1, double y1, double z1){
	x = x1;
	y = y1;
	z = z1;
}

void Robot::Draw(){
//	box.Draw();
	cyn.Draw();
	jcyn[0].Draw();
	jcyn[1].Draw();
	jcyn[2].Draw();
	mcyn[0].Draw();
	mcyn[1].Draw();
	mcyn[2].Draw();
	wcyn[0].Draw();
	wcyn[1].Draw();
	wcyn[2].Draw();
}





Robot::CameraObject::CameraObject()
{
    Initialize();
}

void Robot::CameraObject::Initialize(void)
{
    x=0;
    y=0;
    z=0;
    h=0; //x pitch
    p=0;//YsPi; //y yaw
    b=0; //z roll

    fov=2*YsPi*70/360;  // 30 degree
    nearZ=0.1;
    farZ=200.0;
}

void Robot::CameraObject::SetUpCameraProjectionOrtho(void)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)400/(double)300;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2*aspect,2*aspect,-2,2,0,50);

}

void Robot::CameraObject::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)400/(double)300;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);

}

void Robot::CameraObject::EulertoRot(Robot rob){
	
	glRotated(rob.p*180.0/YsPi,1.0,0.0,0.0);  
    glRotated(rob.h*180.0/YsPi,0.0,0.0,1.0);  
    glRotated(rob.b*180.0/YsPi,0.0,1.0,0.0);  

}

void Robot::CameraObject::SetUpObjectTransformation(Robot rob){
    glTranslated(rob.x,rob.y,rob.z);
    EulertoRot(rob);

}

void Robot::CameraObject::SetUpObjectTransformation3d(Robot rob){
    EulertoRot(rob);
}

void Robot::CameraObject::SetUpCameraTransformation()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis roll
    glRotated(-p*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis yaw
    glRotated(-h*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis pitch
    glTranslated(-x,-y,-z);

}

void Robot::CameraObject::SetUpCameraTransformation3d()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis roll
    glRotated(-h*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis pitch
    glRotated(-p*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis yaw
    glTranslated(-x,-y,-z);
}

void Robot::CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(b);
    vy= sin(p);
    vz=-cos(p)*cos(b);
}


void Robot::Init(){
    
    
    camera1.z = -2;
    camera1.x = -5;
    camera1.y = 1;
    camera1.p = YsPi;


    camera2.y =  3;
    camera2.h = 1*YsPi/2;
    camera2.p = YsPi;
    camera2.x = -5;


    camera3.x =  -10;
    camera3.z = 0;
    camera3.y = 1;
    camera3.p = -1*YsPi/2;


    camera4.x =  -1;
    camera4.z = -1;
    camera4.y = 1;
    camera4.p = -3*YsPi/4;
    camera4.h = -1*YsPi/4;

   // camera4.p = -1*YsPi/1.4;
	int radius = 40;
	int num = 1;
	UpdateRot(0,0,0);

	FsOpenWindow(16,16,800,600,1);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	FsPassedTime();
}

bool Robot::Run(double xx, double yy, double zz, double rr, double pp, double yawyaw){
		int num = 1;
		int terminate=0;
		double counter = 0;
    	counter += .001;
    	if(counter > 10){
    		counter = 0;
    	}
    	MoveTo(xx,yy,zz);
    	UpdateRot(rr,pp,yawyaw);

		//camera.GetForwardVector(tx,ty,tz);
		//printf("%f %f %f\n",tx,ty,tz);
        FsPollDevice();
        double dt=(double)FsPassedTime()/1000.0;
        //printf("%f\n",dt);

        int wid,hei;
        FsGetWindowSize(wid,hei);
        int key=FsInkey();
        
        switch(key)
        {
        case FSKEY_ESC:
           	terminate=1;
           	return false;
           	break;
        }
        if(key == FSKEY_A){ //h p b 
        	Move(.1,0,0);  // x y z
        }					//pitch yaw roll
        if(key == FSKEY_D){
        	Move(-.1,0,0);
        }
        if(key == FSKEY_W){
        	Move(0,0,.1);
        }
        if(key == FSKEY_S){
        	Move(0,0,-.1);
        }
        if(key == FSKEY_UP){
        	Rot(.1,0,0);
        }
        if(key == FSKEY_DOWN){
        	Rot(-.1,0,0);
        }
        if(key == FSKEY_O){
        	Rot(0,.1,0);
        }
        if(key == FSKEY_P){
        	Rot(0,-.1,0);
        }
        if(key == FSKEY_LEFT){
        	Rot(0,0,.1);
        }
        if(key == FSKEY_RIGHT){
        	Rot(0,0,-.1);
        }
        if(key == FSKEY_C){
        	Move(0,.1,0);
        }
        if(key == FSKEY_SPACE){
        	Move(0,-.1,0);
        }

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_BLEND);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_COLOR_MATERIAL);
		GLfloat lightDir[]={0,1.0f/(float)sqrt(1.0f),0.0f/(float)sqrt(2.0f),0};
        GLfloat lightAmb[]={.2,.2,.2,1};
		glViewport(0,0,400,300);
        // Set up 3D drawing
        camera1.SetUpCameraProjectionOrtho();
        camera1.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1,1);

       	for(int i = 0; i < num; i++){
       		
			glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
            glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmb);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			camera1.SetUpObjectTransformation(*this);
			//glEnable(GL_COLOR_MATERIAL);
			Draw();
			camera1.SetUpCameraTransformation();
		}


		glViewport(0,300,400,300);
        // Set up 3D drawing
        camera2.SetUpCameraProjectionOrtho();
        camera2.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1,1);
		glLightfv(GL_LIGHT0,GL_POSITION,lightDir);

        for(int i = 0; i < num; i++){
        	
			glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			camera2.SetUpObjectTransformation(*this);
			//glEnable(GL_COLOR_MATERIAL);
			Draw();
			camera2.SetUpCameraTransformation();
		}


		glViewport(400,300,400,300);
        // Set up 3D drawing
        camera3.SetUpCameraProjectionOrtho();
        camera3.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1,1);
		glLightfv(GL_LIGHT0,GL_POSITION,lightDir);

        for(int i = 0; i < num; i++){
        	
			glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			camera3.SetUpObjectTransformation(*this);
			//glEnable(GL_COLOR_MATERIAL);
			Draw();
            Draw();
            //yep
			camera3.SetUpCameraTransformation();
		}

		glViewport(400,0,400,300);
        // Set up 3D drawing
        camera4.SetUpCameraProjection();
        camera4.SetUpCameraTransformation3d();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1,1);
		glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
		
		for(int i = 0; i < num; i++){
        	
			glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			camera4.SetUpObjectTransformation3d(*this);
			//glEnable(GL_COLOR_MATERIAL);
			Draw();
			camera4.SetUpCameraTransformation3d();
		}



        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);

        glDisable(GL_LIGHTING);
        glViewport(0,0,wid,hei);
        glColor3f(1.0,255.0,0.0);
        glBegin(GL_LINES);
        glVertex2f(400,0);
        glVertex2f(400,600);
        glVertex2f(0,300);
        glVertex2f(800,300);
        glEnd();

        glViewport(0,0,wid/2,hei/2); //bot left
        glColor3f(0.0,0.0,0.0);
        glRasterPos2d(wid/2,50);
        YsGlDrawFontBitmap8x12("Front");
        glBegin(GL_LINES);
        for(int i = 0; i < 10; i++){
            glVertex2f(i*wid/10,hei);
            glVertex2f(i*wid/10, (hei)-20);
        }
        for(int i = 0; i < 10/aspect1; i++){
            glVertex2f(0,wid*i/10);
            glVertex2f(20, wid*i/10);
        }
        glEnd();
        glRasterPos2d(wid/2,hei - 50);
        YsGlDrawFontBitmap8x12("X");
        for(int i = 0; i < 10; i++){
            glRasterPos2d(i*wid/10 - 20,hei-20);
            auto str = std::to_string(camera1.x + nscale*(i-5)/5);
           
            YsGlDrawFontBitmap6x7(str.substr(0,4).c_str());
        }
        glRasterPos2d(80,hei/2);
        YsGlDrawFontBitmap8x12("Y");
        for(int i = 1; i < (10.0/aspect1); i++){
            glRasterPos2d(20, wid*i/10);
            auto str = std::to_string(camera1.y + nscale*(i-5)/5);
            
            YsGlDrawFontBitmap6x7(str.substr(0,4).c_str());
        }



        glViewport(0,hei/2,wid/2,hei/2); //top left
        glRasterPos2d(wid/2,50);
        YsGlDrawFontBitmap8x12("Top");
        glBegin(GL_LINES);
        for(int i = 0; i < 10; i++){
            glVertex2f(i*wid/10,hei);
            glVertex2f(i*wid/10, (hei)-20);
        }
        for(int i = 0; i < 10/aspect1; i++){
            glVertex2f(0,wid*i/10);
            glVertex2f(20, wid*i/10);
        }
        glEnd();
        glRasterPos2d(wid/2,hei - 50);
        YsGlDrawFontBitmap8x12("X");
        for(int i = 0; i < 10; i++){
            glRasterPos2d(i*wid/10 - 20,hei-20);
            auto str = std::to_string(camera2.x + nscale*(i-5)/5);
            
            YsGlDrawFontBitmap6x7(str.substr(0,4).c_str());
        }
        glRasterPos2d(80,hei/2);
        YsGlDrawFontBitmap8x12("Z");
        for(int i = 1; i < (10.0/aspect1); i++){
            glRasterPos2d(20, wid*i/10);
            auto str = std::to_string(camera2.z + nscale*(i-5)/5);
           
            YsGlDrawFontBitmap6x7(str.substr(0,4).c_str());
        }

        glViewport(wid/2,hei/2,wid/2,hei/2);
        glRasterPos2d(wid/2,50);
        YsGlDrawFontBitmap8x12("Side");
        glBegin(GL_LINES);
        for(int i = 0; i < 10; i++){
            glVertex2f(i*wid/10,hei);
            glVertex2f(i*wid/10, (hei)-20);
        }
        for(int i = 0; i < 10/aspect1; i++){
            glVertex2f(0,wid*i/10);
            glVertex2f(20, wid*i/10);
        }
        glEnd();
        glRasterPos2d(wid/2,hei - 50);
        YsGlDrawFontBitmap8x12("Z");
        for(int i = 0; i < 10; i++){
            glRasterPos2d(i*wid/10 - 20,hei-20);
            auto str = std::to_string(camera3.z + nscale*(i-5)/5);
            
            YsGlDrawFontBitmap6x7(str.substr(0,4).c_str());
        }
        glRasterPos2d(80,hei/2);
        YsGlDrawFontBitmap8x12("Y");
        for(int i = 1; i < (10.0/aspect1); i++){
            glRasterPos2d(20, wid*i/10);
            auto str = std::to_string(camera2.y + nscale*(i-5)/5);
            YsGlDrawFontBitmap6x7(str.substr(0,4).c_str());
        }


        FsSwapBuffers();       

        // 2D drawing from here
        FsSleep(10);
      //  printf("FramerateL %f\n",1/dt);
        return true;
    }

int main(){
	Robot rob(3,3,3);
	rob.Init();
	bool a = true;
	std::string line;
	std::ifstream myfile("testdata.txt");
	if(myfile){
		getline(myfile,line);
		getline(myfile,line);
		getline(myfile,line);
	}
	double time;
    double x = 0;
    double y = 0;
    double z = 0;
	double r = 0;
	double p = 0;
	double yaw = 0;
	std::string::size_type sz;
	std::string::size_type sz2;
	double first = FsSubSecondTimer();
    getline(myfile,line);

    time = std::stod(line);
    double oldtime = time;
    
	while(a == true){
        double newtime = ((double)FsSubSecondTimer() - first)/500.0;
        if(newtime > (time - oldtime)){
            oldtime = time;
        	time = std::stod(line);
		    getline(myfile,line);
		    x = std::stod(line,&sz);
		    y = std::stod(line.substr(sz),&sz2);
		    std::string line2 = line.substr((sz));
		    z = std::stod(line2.substr(sz2));
		    getline(myfile,line);
		    r = std::stod(line,&sz);
		    p = std::stod(line.substr(sz),&sz2);
		    line2 = line.substr((sz));
		    yaw = std::stod(line2.substr(sz2));
		    r = r*YsPi/180;
		    p = p*YsPi/180;
		    yaw = yaw*YsPi/180;
		    if(!getline(myfile,line)){
		      	return 0;
		    }
            first = FsSubSecondTimer();
        }
		a = rob.Run(x,y,z,r,p,yaw);
	}
    return 0;
}


