#include <stdio.h>
#include <iostream>
#include <vector>

#include "fssimplewindow.h"


const double YsPi=3.1415927;
GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[4] = { .4f, 0.0f, 0.0f, .1f };
GLfloat mat_ambient2[4] = { 1.0f, 1.0f, 1.0f, .1f };
GLfloat mat_ambient_color[4] = { 0.8f, 0.8f, 0.2f, .3f };
GLfloat mat_diffuse[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat no_shininess[1] = { 0.0f };
GLfloat low_shininess[1] = { 5.0f };
GLfloat high_shininess[1] = { 100.0f };
GLfloat mat_emission[4] = {0.3f, 0.2f, 0.2f, 0.0f};


GLfloat cubemat_ambient[4] = { 0.0f, 0.0f, .40f, 1.0f };
GLfloat cubemat_diffuse[4] = { 0.0f, 0.0f, .40f, 1.0f };
GLfloat cubemat_specular[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat cubemat_emission[4] = {0.0f, .0f, 0.0f, .2f};

GLfloat supmat_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat supmat_diffuse[4] = { 0.0f, 0.0f, .00f, 1.0f };
GLfloat supmat_specular[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat supmat_emission[4] =  {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat gridmat_ambient[4] = { .0f, .2f, 0.8f, .3f };
GLfloat gridmat_diffuse[4] = { .0f, 0.2f, 0.8f, 1.0f };
GLfloat gridmat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat gridmat_emission[4] = {0.0f, 1.0f, 1.0f, .5f};

GLfloat linemat_ambient[4] = { .0f, .2f, 0.8f, .3f };
GLfloat linemat_diffuse[4] = { .0f, 0.2f, 0.8f, 1.0f };
GLfloat linemat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat linemat_emission[4] = {1.0f, 0.0f, .7f, .5f};

GLfloat wallmat_ambient[4] = { 0.1f, 0.0f, 0.1f, 1.0f };
GLfloat wallmat_diffuse[4] = { 0.1f, 0.0f, 0.1f, 1.0f };
GLfloat wallmat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat wallmat_emission[4] = {0.0f, 0.0f, 0.0f, .5f};

GLfloat scoremat_ambient[4] = { 0.0f,0.0f, 0.0f, 1.0f };
GLfloat scoremat_diffuse[4] = { .0f, 0.0f, 0.0f, 1.0f };
GLfloat scoremat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat scoremat_emission[4] = {00.0f, 0.0f, 0.0f, .5f};

GLfloat textmat_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat textmat_diffuse[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat textmat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat textmat_emission[4] = {0.0f, 0.0f, 0.0f, .5f};

GLfloat floormat_ambient[4] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat floormat_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat floormat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat floormat_emission[4] = {0.0f, 0.0f, 0.0f, 1.0f};


GLfloat light_positionglobal[] = {0.0f, 5.0f, 0.0f,1.0f};
GLfloat light_ambient[] = { .1f, .1f, .1f, 1.0f};
GLfloat light_diffuse[] = { .5f, 0.5f, 0.5f, 1.0f};
GLfloat light_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat light_direction[] = { 0.0f, -1.0f, 0.0f};
GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };


class Lights
{
	public:
	GLfloat alight_position[4];
	GLfloat alight_ambient[4];
	GLfloat alight_diffuse[4];
	GLfloat alight_specular[4];
	GLfloat alight_direction[3];
	int lightnum = 0;
	//Lights();
	void Init(int lighter, GLfloat pos[], GLfloat amb[], GLfloat diffuse[], GLfloat spec[], GLfloat dir[]);
	void StartLight();
	void updateLightPosit();
	void ChangeLightPos(double x, double y, double z);
};

void Lights::Init(int lighter, GLfloat pos[], GLfloat amb[], GLfloat diffuse[], GLfloat spec[], GLfloat dir[]){
	lightnum = lighter;
	for(int i = 0; i < 4; i++){
		alight_position[i] = pos[i];
		alight_ambient[i] = amb[i];
		alight_diffuse[i] = diffuse[i];
		alight_specular[i] = spec[i];

	}
	for(int i = 0; i < 3; i++){
		light_direction[i] = dir[i];
	}
}

void Lights::StartLight(){
	glEnable(GL_LIGHT0+lightnum);
	glLightfv(GL_LIGHT0+lightnum, GL_AMBIENT, alight_ambient);
	glLightfv(GL_LIGHT0+lightnum, GL_DIFFUSE, alight_diffuse);
	glLightfv(GL_LIGHT0+lightnum, GL_SPECULAR, alight_specular);
	glLightfv(GL_LIGHT0+lightnum, GL_POSITION, alight_position);
	glLightf(GL_LIGHT0 + lightnum, GL_QUADRATIC_ATTENUATION, .01f);
	

}
void Lights::ChangeLightPos(double x, double y, double z){
	alight_position[0] = (GLfloat)(x);
	alight_position[1] = (GLfloat)(y);
	alight_position[2] = (GLfloat)(z);
}

void Lights::updateLightPosit(){
	glLightfv(GL_LIGHT0+lightnum, GL_POSITION, alight_position);
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
};


class matri4x4
{
public:
    double mat [4][4];
    matri4x4();
    matri4x4(double * input);
    matri4x4 mult(matri4x4 input);
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
    Vec tempVec;
    tempVec.x = p2.x - p1.x;
    tempVec.y = p2.y - p1.y;
    tempVec.z = p2.z - p1.z;
    Vec tempVec2;
    tempVec2.x = p3.x - p1.x;
    tempVec2.y = p3.y - p1.y;
    tempVec2.z = p3.z - p1.z;
    norm.x = (tempVec.y * tempVec2.z) - (tempVec.z * tempVec2.y);
    norm.y = (tempVec.z * tempVec2.x) - (tempVec.x * tempVec2.z);
    norm.z = (tempVec.x * tempVec2.y) - (tempVec.y * tempVec2.x);
    double total = sqrt(norm.x * norm.x + norm.y*norm.y + norm.z*norm.z);
    norm.x=norm.x/total;
    norm.y=norm.y/total;
    norm.z=norm.z/total;

}


class Robot
{
public:
    double x,y,z;
    double h,p,b;
    double wid,hei,len;
    matri4x4 matrix;
    Square osides[6];
    Square sides[6];
    Robot(double inw, double inh, double inl);
    void Draw();
    void UpdatePos(double x1, double y1, double z1);
    void UpdateRot(double h1, double p1, double b1);
    void Move(double x1, double y1, double z1);
    void Init();
    void MoveX(double x1);
    void MoveY(double y1);
    void MoveZ(double z1);
};
Robot::Robot(double inw, double inh, double inl){
    x = 0;
    y = 0;
    z = 0;
    h = 0;
    p = 0;
    b = 0;
    std::vector<Vec> newpoint;
	newpoint.push_back(Vec(inw/2,inh/2,inl/2)); //r t f 0
	newpoint.push_back(Vec(inw/2,inh/2,inl/-2)); // r t ba 1
	newpoint.push_back(Vec(inw/2,inh/-2,inl/-2)); // r bo ba 2
	newpoint.push_back(Vec(inw/2,inh/-2,inl/2)); // r bo f 3
	newpoint.push_back(Vec(inw/-2,inh/-2,inl/2)); // l bo f 4
	newpoint.push_back(Vec(inw/-2,inh/-2,inl/-2)); // l bo ba 5
	newpoint.push_back(Vec(inw/-2,inh/2,inl/-2)); // l t ba 6
	newpoint.push_back(Vec(inw/-2,inh/2,inl/2)); // l t f 7
	
	sides[0] = (Square(newpoint[0],newpoint[3], newpoint[4], newpoint[7]));
	sides[1] = (Square(newpoint[3],newpoint[2], newpoint[5], newpoint[4]));
	sides[2] = (Square(newpoint[0],newpoint[1], newpoint[2], newpoint[3]));
	sides[3] = (Square(newpoint[4],newpoint[5], newpoint[6], newpoint[7]));
	sides[4] = (Square(newpoint[0],newpoint[7], newpoint[6], newpoint[1]));
	sides[5] = (Square(newpoint[2],newpoint[1], newpoint[6], newpoint[5]));
	osides[0] = sides[0];
	osides[1] = sides[1];
	osides[2] = sides[2];
	osides[3] = sides[3];
	osides[4] = sides[4];
	osides[5] = sides[5];
    matri4x4 temp;
};

void Robot::Move(double x1,double y1, double z1){
	UpdatePos(x + x1, y +y1, z + z1);
}
void Robot::MoveX(double x1){
	UpdatePos(x+x1,y,z);
}
void Robot::MoveY(double y1){
	UpdatePos(x,y+y1,z);
}
void Robot::MoveZ(double z1){
	UpdatePos(x,y,z+z1);
}

void Robot::UpdateRot(double h1, double p1, double b1){
	h = h1;
	p = p1;
	b = b1;
	for(int i = 0; i < 6; i ++){
		for(int j = 0; j < 4; j ++){
			double newx;
			double newy;
			double newz;
			newx = osides[i].points[j].x;
			newy = cos(h)*osides[i].points[j].y - sin(h)*osides[i].points[j].z;
			newz = sin(h)*osides[i].points[j].y + cos(h)*osides[i].points[j].z;

			double newx1;
			double newy1;
			double newz1;
			newx1 = cos(p)*newx + sin(p)*newz;
			newy1 = newy;
			newz1 = -1*sin(p)*newx + cos(p)*newz;

			double newx2;
			double newy2;
			double newz2;
			newx2 = cos(b)*newx1 - sin(b)*newy1;
			newy2 = sin(b)*newx1 + cos(b)*newy1;
			newz2 = newz1;
			sides[i].points[j].x = newx2+x;
			sides[i].points[j].y = newy2+y;
			sides[i].points[j].z = newz2+z;
		}
	}
	for(int i = 0; i < 6; i++){
		Vec tempVec;
   		tempVec.x = sides[i].points[2].x - sides[i].points[0].x;
    	tempVec.y = sides[i].points[2].y - sides[i].points[0].y;
    	tempVec.z = sides[i].points[2].z - sides[i].points[0].z;
    	Vec tempVec2;
    	tempVec2.x = sides[i].points[1].x - sides[i].points[0].x;
    	tempVec2.y = sides[i].points[1].y - sides[i].points[0].y;
    	tempVec2.z = sides[i].points[1].z - sides[i].points[0].z;
    	sides[i].norm.x = (tempVec.y * tempVec2.z) - (tempVec.z * tempVec2.y);
    	sides[i].norm.y = (tempVec.z * tempVec2.x) - (tempVec.x * tempVec2.z);
    	sides[i].norm.z = (tempVec.x * tempVec2.y) - (tempVec.y * tempVec2.x);
    	double total = sqrt(sides[i].norm.x * sides[i].norm.x + sides[i].norm.y*sides[i].norm.y + sides[i].norm.z*sides[i].norm.z);
    	sides[i].norm.x=sides[i].norm.x/total;
    	sides[i].norm.y=sides[i].norm.y/total;
    	sides[i].norm.z=sides[i].norm.z/total;
	}

}
void Robot::UpdatePos(double x1, double y1, double z1){
	
	for(int i = 0; i < 6; i ++){
		for(int j = 0; j < 4; j ++){
			sides[i].points[j].x += x1 - x;
			sides[i].points[j].y += y1 - y;
			sides[i].points[j].z += z1 - z;
		}
	}
	x = x1;
	y = y1;
	z = z1;
}

void Robot::Draw(){
	glColor3f(0.0f,255.0f,0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f,255.0f,0.0f);
	for(int i = 0; i < 6; i++){
		glNormal3f(sides[i].norm.x,sides[i].norm.y,sides[i].norm.z);
		for(int j = 0; j < 4; j++){
			glVertex3f(sides[i].points[j].x,sides[i].points[j].y,sides[i].points[j].z);
			//printf("%d %d %f %f %f\n",i,j,sides[i].points[j].x,sides[i].points[j].y,sides[i].points[j].z);
			//printf("%f %f %f\n",sides[i].norm.x,sides[i].norm.y,sides[i].norm.z);
		}
	}
	glEnd();
}



class CameraObject{
public:
    double x,y,z;
    double h,p,b;

    double fov,nearZ,farZ;

    CameraObject();
    void Initialize(void);
    void SetUpCameraProjection(void);
    void SetUpCameraTransformation(void);
    void GetForwardVector(double &vx,double &vy,double &vz);
};

CameraObject::CameraObject()
{
    Initialize();
}

void CameraObject::Initialize(void)
{
    x=0;
    y=0;
    z=0;
    h=0;
    p=0;//YsPi;
    b=0;

    fov=2*YsPi*70/360;  // 30 degree
    nearZ=0.1;
    farZ=200.0;
}

void CameraObject::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)400/(double)300;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis
    glRotated(-h*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis
    glRotated(-p*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis
    
    glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}


int main(void)
{
	
    int terminate=0;
    CameraObject camera1;
    CameraObject camera2;
    CameraObject camera3;
    CameraObject camera4;
    camera1.z = -10;
    camera1.h = YsPi;
    camera2.y =  10;
    camera2.p = 1*YsPi/2;
    camera2.h = YsPi;
    camera3.x =  -10;
    camera3.h = -1*YsPi/2;
    camera4.x =  -5;
    camera4.z = -5;
    camera4.y = 5;
    camera4.p = YsPi/4;
    camera4.h = -3.2*YsPi/4;
   // camera4.p = -1*YsPi/1.4;
	int radius = 40;
	Robot rob(3,3,3);
	rob.UpdatePos(0,0,0);
	FsOpenWindow(16,16,800,600,1);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	FsPassedTime();
	
	double counter = 0;
    while(0==terminate)
    {	
    	counter += .4;
    	if(counter > 100){
    		counter = 0;
    	}
    	rob.UpdateRot(YsPi*counter/50,0,0);

    	double tx;
		double ty;
		double tz;
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
           	break;
        }
        if(key == FSKEY_A){
        	rob.Move(.1,0,0);
        }
        if(key == FSKEY_D){
        	rob.Move(-.1,0,0);
        }
        if(key == FSKEY_W){
        	rob.Move(0,0,.1);
        }
        if(key == FSKEY_S){
        	rob.Move(0,0,-.1);
        }
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_BLEND);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        

		glViewport(0,0,400,300);
        // Set up 3D drawing
        camera1.SetUpCameraProjection();
        camera1.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1,1);
        GLfloat lightDir[]={0,1.0f/(float)sqrt(1.0f),0.0f/(float)sqrt(2.0f),0};
		glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_COLOR_MATERIAL);
		rob.Draw();


		glViewport(0,300,400,300);
        // Set up 3D drawing
        camera2.SetUpCameraProjection();
        camera2.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1,1);
		glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_COLOR_MATERIAL);
		rob.Draw();


		glViewport(400,300,400,300);
        // Set up 3D drawing
        camera3.SetUpCameraProjection();
        camera3.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1,1);
		glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_COLOR_MATERIAL);
		rob.Draw();

		glViewport(400,0,400,300);
        // Set up 3D drawing
        camera4.SetUpCameraProjection();
        camera4.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonOffset(1,1);
		glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_COLOR_MATERIAL);
		rob.Draw();



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

        FsSwapBuffers();       

        // 2D drawing from here
        FsSleep(20);
        //printf("FramerateL %f\n",1/dt);
    }

    return 0;
    
}


