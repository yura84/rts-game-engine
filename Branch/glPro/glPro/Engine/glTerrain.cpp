/*
 * openglWin.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#include "glTerrain.h"

glTerrain::glTerrain()
{
	for (int i=0; i<(MAP_SIZE*MAP_SIZE); i++)
	{
		pHeightMap[i] = rand()%30;
	}
	

}

glTerrain::~glTerrain()
{

}

void glTerrain::init(BYTE pHeightMap[])
{

}

void glTerrain::renderTerrain()
{

  int X = 0, Y = 0;    
  int x, y, z;        
  if(!pHeightMap) return;    
  bRender = true;
  if(bRender)            
    glBegin( GL_QUADS ); 
  else  
    glBegin( GL_LINES ); 
  
  for ( X = 0; X < MAP_SIZE; X += STEP_SIZE ) 
    for ( Y = 0; Y < MAP_SIZE; Y += STEP_SIZE ) 
    { 
      
      x = X;               
      y = Height(X, Y );   
      z = Y;               
       
      setVertexColor(x, z); 
      glVertex3i(x, y, z);      
      
      x = X;                     
      y = Height(X, Y + STEP_SIZE );   
      z = Y + STEP_SIZE ;               
       
     
      setVertexColor(x, z); 
      glVertex3i(x, y, z);      
   
    
      x = X + STEP_SIZE;  
      y = Height(X + STEP_SIZE, Y + STEP_SIZE );  
      z = Y + STEP_SIZE ; 
   
      
      setVertexColor(x, z); 
      glVertex3i(x, y, z);      
     
      x = X + STEP_SIZE;  
      y = Height(X + STEP_SIZE, Y );  
      z = Y; 
   
      
      setVertexColor(x, z); 
      glVertex3i(x, y, z);      
    } 
  glEnd(); 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

int glTerrain::Height(int X, int Y)      
{ 
  int x = X % MAP_SIZE;         
  int y = Y % MAP_SIZE;   
  if ((X>=MAP_SIZE)||(X<0)) return 0;
  if ((Y>=MAP_SIZE)||(Y<0)) return 0;

  if(!pHeightMap) return 0;      
  return pHeightMap[X + (Y * MAP_SIZE)]; 
}

void glTerrain::setVertexColor(int x, int y)
{
  if(!pHeightMap) return;         
  float fColor = -0.15f + (Height(x, y ) / 256.0f); 
  glColor3f(0.0f, 0.0f, fColor );
}


