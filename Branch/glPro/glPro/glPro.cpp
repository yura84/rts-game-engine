//============================================================================
// Name        : glPro.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <windows.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>

#include "Camera/glFirstPersonCamera.h"
#include "Camera/glFpsManager.h"

#include "Engine/glWindow.h"
#include "Engine/glObjectBase.h"
#include "Engine/glObjectBot.h"
#include "Engine/glTerrain.h"
#include "Engine/glRenderManager.h"
#include "Engine/glAi.h"
#include "Network/Network.h"

#include "Gui\Gui.h"
#include "glTexture.h"

using namespace std;
int posx,posy;
typedef struct DataTransfer {
	float x;
	float y;
	float z;

	int shot;
};

glWindow glwindow(0,300,WIDTH,HEIGHT);
glRenderManager glrendermanager(WIDTH, HEIGHT);
glFirstPersonCamera glfirstpersoncamera;
glTerrain glterrain;

glObjectBase globjects;
glObjectBot globjectbot;
glAi glai(globjectbot);
glObjectBot globjectPlayer;
glFpsManager glfpsmanager;
Network nettrans("106.125.36.140", 5050);
bool buttd;
bool rotateBut;
std::string botposition;
GLuint	texture[1];
glTexture *gltexture;

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(L"Data/NeHe.bmp");//Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture
	
	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL
	C_Bitmap *cb = new C_Bitmap("Data/kru.bmp");
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	//if (TextureImage[0]=LoadBMP("Data/NeHe.bmp"))
	if (cb)
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture[0]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, cb->getWidth(), cb->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, cb->data);
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 10, 10, 0, GL_RGBA, GL_UNSIGNED_BYTE, mt);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	return Status;										// Return The Status
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
	std::ostringstream  str; 
	
	glfpsmanager.update();
	globjects.update();
	globjectbot.update(0.01f);
	glai.update(0.01f);
	glrendermanager.beginScene();
	glfirstpersoncamera.Update(glfpsmanager.getDT());
	
	globjectPlayer.x = glfirstpersoncamera.position.x;
	globjectPlayer.y = glfirstpersoncamera.position.y;
	globjectPlayer.z = glfirstpersoncamera.position.z;

	glrendermanager.renderScene();
	if (globjectbot.getLife()>0) globjectbot.render();

	if (globjects.dist>0) {
		if (globjects.checkCollision(globjectbot.x, globjectbot.y, globjectbot.z, 0.5)) {
			std::cout << "COLISION"<< std::endl;
			globjectbot.getShot();
			if (globjectbot.getLife()<=0) globjectPlayer.addKill();
		}

		globjects.render();
	}

	

	//glrendermanager.renderPlane(glfirstpersoncamera.position.x+((posx-WIDTH/2)*glfirstpersoncamera.l.x),glfirstpersoncamera.position.z+((HEIGHT/2-posy)*glfirstpersoncamera.l.z),1.0f);

	glBegin(GL_TRIANGLES);
	for (int i=0; i< globjects.numberOfVertex; i++) {
		glVertex3f(globjects.vertex[i].x, globjects.vertex[i].y, globjects.vertex[i].z);
	}
	glEnd();
	
	//********************************
	/**/
	glDisable(GL_COLOR_MATERIAL);
	glDisable( GL_DEPTH_TEST );
   // glDisable( GL_LIGHTING );
	glEnable(GL_TEXTURE_2D);

	int cx = 400;
	int cy = 300;
	int sizex = 10;
	int sizey = 10;
	glrendermanager.setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D, gltexture->texture[0]); //texture[0]);
	//gltexture->BindTexture();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(cx,cy);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(cx+100.0f,cy);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(cx+100.0f,cy+100.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(cx, cy+100.0f);
	glEnd();
	glPopMatrix();	
	
	glrendermanager.restorePerspectiveProjection();
	glDisable(GL_TEXTURE_2D);
	glEnable( GL_DEPTH_TEST );
   // glEnable( GL_LIGHTING );
	glEnable(GL_COLOR_MATERIAL);/**/
	//*******************************
	//glrendermanager.drawAim();

	str << globjectPlayer.x << ":" <<globjectPlayer.y << ":" << globjectPlayer.z << " Life: " << globjectPlayer.getLife() << "Kill: " << globjectPlayer.getKill();
	glrendermanager.drawText(10,40,str.str());
	
	str.str("");
	str << globjectbot.x << ":" <<globjectbot.y << ":" << globjectbot.z << " Life: " << globjectbot.getLife();
	glrendermanager.drawText(10,20,str.str());
	
	/*str << glfirstpersoncamera.viewx << " : " << glfirstpersoncamera.viewy << " : " << glfirstpersoncamera.viewz << std::endl;
	glrendermanager.drawText(10,20, str.str());
	*/
	//glEnable(GL_LIGHTING);
	str.str("");
	str << globjectbot.x << ":" << globjectbot.y << ":" << globjectbot.z << ";" << globjectbot.fx << ":" << globjectbot.fy << ":" << globjectbot.fz << std::endl;
	glrendermanager.drawText(10,60, str.str());
	glrendermanager.drawText(10,80, botposition);
	glrendermanager.endScene();
	globjectbot.restart();
	if (globjectPlayer.restart()) {
		glfirstpersoncamera.position.x = globjectPlayer.x;
		glfirstpersoncamera.position.y = globjectPlayer.y;
		glfirstpersoncamera.position.z = globjectPlayer.z;
	}

}

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);
}

/*
void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}
*/
void keyDown(unsigned char key, int x, int y)
{
	 switch (key)
	 {
		 case 'W' :	
		 case 'w' : glfirstpersoncamera.setMove(0,1); break;
		 case 'S' :
	 	 case 's' : glfirstpersoncamera.setMove(1,1); break;
		 case 'A' :
		 case 'a' : glfirstpersoncamera.setMove(2,1); break;
		 case 'D' :
	 	 case 'd' : glfirstpersoncamera.setMove(3,1); break;

		 case 32 : 	glfirstpersoncamera.jump(); break;
		 case 27  : exit(0);
	 }

}

void keyUp(unsigned char key, int x, int y)
{
	  switch (key)
	 {
		 case 'W' :	
		 case 'w' : glfirstpersoncamera.setMove(0,0); break;
		 case 'S' :
	 	 case 's' : glfirstpersoncamera.setMove(1,0); break;
		 case 'A' :
		 case 'a' : glfirstpersoncamera.setMove(2,0); break;
		 case 'D' :
	 	 case 'd' : glfirstpersoncamera.setMove(3,0); break;
	 }
}

void mouseMove(int x, int y) 
{
//	cout <<"Roo"<<rotateBut << ";";
	
	posx = x;
	posy = y;
	if (rotateBut) 	glfirstpersoncamera.mouseNavigate(x, y);
}

void mouseButton(int button, int state, int x, int y) {

	//cout << rotateBut << ";";
	// only start motion if the left button is pressed
		if ((button == 2)&&(state==0)) rotateBut = !rotateBut;
		
		
	if ((button == GLUT_LEFT_BUTTON)&&(state==0)) 
	{
		if (buttd==false) {
			buttd=true;
			//globjects.beginTriangle(x,y);
		}

		globjects.init(glfirstpersoncamera.position.x, glfirstpersoncamera.position.y, glfirstpersoncamera.position.z, glfirstpersoncamera.l.x, glfirstpersoncamera.view.y, glfirstpersoncamera.l.z);			
	}

	if ((button == GLUT_LEFT_BUTTON)&&(state==1)) {
		if (buttd==true) {
			buttd=false;
			//globjects.endTriangle(x,y);
		}
	}
	
}

DataTransfer strToVertex(char *src) {
	DataTransfer vertex;
	std::string str;
	int lenSrc;
	int lenX, lenY, lenZ, lenS;
	int posX = 0,posY = 0,posZ = 0, posS = 0;
	
	str.append(src);
	vertex.x = 0.0f;
	vertex.y = 0.0f;
	vertex.z = 0.0f;
	vertex.shot = 0;

	lenSrc = strlen(src);
	for (int i=0; i<lenSrc-2; i++)
	{
		if (src[i]=='x') posX=i+2;
		if (src[i]=='y') posY=i+2;
		if (src[i]=='z') posZ=i+2;
		if (src[i]=='s') posS=i+2;
	}
	lenX = posY-posX-3;
	lenY = posZ-(posY+3);
	lenZ = posS-(posZ+3);
	lenS = lenSrc-(posZ+2);
	
	vertex.x = atof(str.substr(posX, lenX).c_str());
	vertex.y = atof(str.substr(posY, lenY).c_str());
	vertex.z = atof(str.substr(posZ, lenZ).c_str());
	vertex.shot = atof(str.substr(posS, lenS).c_str());

	//std::cout << str.substr(posX,lenX) << ":" << str.substr(posY,lenY).c_str() << ":" << str.substr(posZ,lenZ).c_str() << std::endl;

	//std::cout << posX << ":" << posY << ":" << posZ << std::endl; 
	return vertex;
}



DWORD WINAPI serverThread(LPVOID network)
  {
	//Network netw = ((Network *) network)[0];
	
    SOCKET my_sock;
   // my_sock=((SOCKET *) client_socket)[0];
    char buff[128];
	DataTransfer vertex;
	int bytes_recv;
    #define sHELLO "Hello, Sailor\r\n"

    // отправляем клиенту приветствие 
    //send(my_sock,sHELLO,sizeof(sHELLO),0);
	//std::cout << "Send hello\n";
    // цикл эхо-сервера: прием строки от клиента и
    // возвращение ее клиенту
	std::cout << "Begin serverThread\n";
  //  while(1) {
		////std::cout << "Client cout" << nettrans.client_socket.size() << "\n"; 
		//if (nettrans.coutClientConnect()>0) {
		//	std::cout << "Client cout>0\n";
		//	my_sock = nettrans.getClientSocket();
		//	//std::cout << "[Server] Begin while\n";
		//	bytes_recv= recv(my_sock,&buff[0],sizeof(buff),0);
		//	//std::cout << "[Server] Recive data \n";
		//	if (bytes_recv !=SOCKET_ERROR) {
		//		botposition.clear();
		//		botposition.append(buff);
		//		vertex = strToVertex(buff);
		//		globjectbot.fx = vertex.x;
		//		globjectbot.fy = vertex.y;
		//		globjectbot.fz = vertex.z;

		//		globjectbot.x = vertex.x;
		//		globjectbot.y = vertex.y;
		//		globjectbot.z = vertex.z;
		//		globjectPlayer.setLife(vertex.shot);
		//	
		//		//std::cout << posx << ":" << posy << std::endl;
		//		//std::cout << atoi(posx) << ":" << atoi(posy) << std::endl;
		//		std::cout << buff <<std::endl;
		//		sprintf(buff,"<x=%f;y=%f;z=%f;s=%d>",glfirstpersoncamera.position.x, glfirstpersoncamera.position.y, glfirstpersoncamera.position.z, globjectbot.getLife());
		//		send(my_sock,&buff[0],bytes_recv,0);
		//		//std::cout << "[Server] Send data \n";
		//	}
		//}
	//}
	

    // если мы здесь, то произошел выход из цикла по
    // причине возращения функцией recv ошибки –
    // соединение клиентом разорвано
  //  nclients--; // уменьшаем счетчик активных клиентов
    printf("-disconnect\n"); //PRINTNUSERS

    // закрываем сокет
	nettrans.closeClientSocket();
	

	return 0;
}


DWORD WINAPI clientThread(LPVOID client_socket)
  {
	  char buff[128];
	SOCKET my_sock;
	DataTransfer vertex;
    my_sock=((SOCKET *) client_socket)[0];
    int nsize;
	/*nsize=recv(my_sock,&buff[0], sizeof(buff)-1,0);
	//if ((buff[0]=='H')&&(buff[1]=='e')) {}
	send(my_sock,&buff[0],nsize,0);
	std::cout << "Begin buffer=" << buff << std::endl;
    */
	while(1) {
		 // передаем строку клиента серверу
		//sprintf(buff,"<1.0;1.0>");
		//sprintf(buff,"<x=%f;y=%f;z=%f;s=%d>",glfirstpersoncamera.position.x, glfirstpersoncamera.position.y, glfirstpersoncamera.position.z, globjectbot.getLife());
		nsize = sizeof(buff);
		send(my_sock,&buff[0],nsize,0);
		//std::cout << "[Client] Recive data \n";
		memset(buff,0,sizeof(buff));
		nsize=recv(my_sock,&buff[0], sizeof(buff),0);
		botposition.clear();
		botposition.append(buff);
		vertex = strToVertex(buff);
			globjectbot.fx = vertex.x;
			globjectbot.fy = vertex.y;
			globjectbot.fz = vertex.z;

			globjectbot.x = vertex.x;
			globjectbot.y = vertex.y;
			globjectbot.z = vertex.z;
			globjectPlayer.setLife(vertex.shot);
			
      //    std::cout << "[Client] Sent data \n";
		//std::cout << nsize<< " - "<< buff << std::endl;
      // ставим завершающий ноль в конце строки 
      buff[nsize]=0;

     

      // проверка на "quit"
      if (!strcmp(&buff[0],"quit\n"))
      {
        // Корректный выход
        printf("Exit...");
        closesocket(my_sock);
        WSACleanup();
        return -1;
      }

     
    }

  //  printf("Recv error %d\n",WSAGetLastError());
    closesocket(my_sock);
    WSACleanup();
    return 0;
  }


/**/
int main(int argc, char **argv) {

	//strToVertex("<x=1032.1321323200;y=2321.333123232312;z=3322.2312;>");
	glwindow.init(argc, argv, renderScene, renderScene);
//	glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();

	// register callbacks
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	
	//glutSpecialFunc(pressKey);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouseMove);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);  // Очистка экрана черным цветом
  glClearDepth(1.0f);        // Установка буфера глубины
  glEnable(GL_DEPTH_TEST);   // Включить буфер глубины
  glShadeModel(GL_SMOOTH);   // Включить сглаживание
 // glEnable(GL_LIGHTING);
 // glEnable(GL_LIGHT0);
  glDepthFunc(GL_LEQUAL);    // Тип теста глубины
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Улучшенные вычисления перспективы
	//glutKeyboardFunc(processNormalKeys);
	//glutEnterGameMode();
//	glutMouseFunc(mouseMove);
	// here are the new entries
/*W	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
*/
 // globjects.save("model.mya");
 // globjects.load("model.mya");
	// OpenGL init
//	glEnable(GL_DEPTH_TEST);
  int servclient = 2;
  std::cout << "Server, Client, single 0/1/2 \n";
  //std::cin >> servclient;
  if (servclient==0) {
	DWORD thID;
	nettrans.sockServerConnect("127.0.0.1", 5050);
	CreateThread(NULL, NULL, serverThread, &nettrans, NULL, &thID);
	std::string sstr;
	send(1,&sstr[0],sstr.size(),0);
  }
  else if (servclient==1){
	  char *servadress;
	  servadress = new char[16];
	  std::cout << "server adress\n";
	  std::cin >> servadress;
	  nettrans.sockClientConnect(servadress, 5050);//"106.125.36.140", 5050);
	 DWORD thID;
	 CreateThread(NULL, NULL, clientThread, &nettrans.getSocket(), NULL, &thID); 
  }
  
  if (LoadGLTextures()) 
  {
	  cout<< "Texture Loaded";
	  cin.get();
  }

  gltexture = new glTexture();
  gltexture->CreateTexture("Data/kru.PNG");
  
// Create light components
GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = {1.0f, 1.0f, 1.0f, 0.0f };

// Assign created components to GL_LIGHT0
glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
glLightfv(GL_LIGHT0, GL_POSITION, position);
 //glEnable(GL_LIGHTING);
//glEnable(GL_LIGHT0);
//glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA );//GL_SRC_ONE_MINUS_ALPHA);
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
glEnable(GL_BLEND);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
