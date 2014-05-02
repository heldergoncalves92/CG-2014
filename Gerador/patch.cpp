//
//  patch.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 28/04/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "patch.h"


float* getPoints(int *patchs, int n_patch, float *vertices, int n_vertices, int detail){
   
    float Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz,Dx,Dy,Dz,Ex,Ey,Ez,Fx,Fy,Fz,Gx,Gy,Gz,Hx,Hy,Hz,Ix,Iy,Iz,Jx,Jy,Jz,Kx,Ky,Kz,Lx,Ly,Lz,Mx,My,Mz,Nx,Ny,Nz,Ox,Oy,Oz,Px,Py,Pz;
	float change = 1.0 / detail, *points=(float*)malloc(n_patch*(3*(detail+1)*(detail+1))*sizeof(float));
	float a,b,c,d;
	int v=0,i,j,k;
    
	
                          
    for(k=0;k<n_patch;k++){
    
        // Variables
        a = 0.0;
        b = 1.0 - a;
        c = 0.0;
        d = 1.0 - c;
    
        //Atribuir valores das patches
        Ax = vertices[3*patchs[(16*k)]];         Ay = vertices[3*patchs[(16*k)]+1];     Az = vertices[3*patchs[(16*k)]+2];
        Bx = vertices[3*patchs[(16*k+1)]];       By = vertices[3*patchs[(16*k+1)]+1];   Bz = vertices[3*patchs[(16*k)+1]+2];
        Cx = vertices[3*patchs[(16*k+2)]];       Cy = vertices[3*patchs[(16*k+2)]+1];   Cz = vertices[3*patchs[(16*k)+2]+2];
        Dx = vertices[3*patchs[(16*k+3)]];       Dy = vertices[3*patchs[(16*k+3)]+1];   Dz = vertices[3*patchs[(16*k)+3]+2];
        Ex = vertices[3*patchs[(16*k+4)]];       Ey = vertices[3*patchs[(16*k+4)]+1];   Ez = vertices[3*patchs[(16*k)+4]+2];
        Fx = vertices[3*patchs[(16*k+5)]];       Fy = vertices[3*patchs[(16*k+5)]+1];   Fz = vertices[3*patchs[(16*k)+5]+2];
        Gx = vertices[3*patchs[(16*k+6)]];       Gy = vertices[3*patchs[(16*k+6)]+1];   Gz = vertices[3*patchs[(16*k)+6]+2];
        Hx = vertices[3*patchs[(16*k+7)]];       Hy = vertices[3*patchs[(16*k+7)]+1];   Hz = vertices[3*patchs[(16*k)+7]+2];
        Ix = vertices[3*patchs[(16*k+8)]];       Iy = vertices[3*patchs[(16*k+8)]+1];   Iz = vertices[3*patchs[(16*k)+8]+2];
        Jx = vertices[3*patchs[(16*k+9)]];       Jy = vertices[3*patchs[(16*k+9)]+1];   Jz = vertices[3*patchs[(16*k)+9]+2];
        Kx = vertices[3*patchs[(16*k+10)]];      Ky = vertices[3*patchs[(16*k+10)]+1];  Kz = vertices[3*patchs[(16*k)+10]+2];
        Lx = vertices[3*patchs[(16*k+11)]];      Ly = vertices[3*patchs[(16*k+11)]+1];  Lz = vertices[3*patchs[(16*k)+11]+2];
        Mx = vertices[3*patchs[(16*k+12)]];      My = vertices[3*patchs[(16*k+12)]+1];  Mz = vertices[3*patchs[(16*k)+12]+2];
        Nx = vertices[3*patchs[(16*k+13)]];      Ny = vertices[3*patchs[(16*k+13)]+1];  Nz = vertices[3*patchs[(16*k)+13]+2];
        Ox = vertices[3*patchs[(16*k+14)]];      Oy = vertices[3*patchs[(16*k+14)]+1];  Oz = vertices[3*patchs[(16*k)+14]+2];
        Px = vertices[3*patchs[(16*k+15)]];      Py = vertices[3*patchs[(16*k+15)]+1];  Pz = vertices[3*patchs[(16*k)+15]+2];
    
        for(i=0; i<=detail; i++){
            for(j=0; j<=detail; j++){
                
                // First get the vertices
                points[v++] = Ax*a*a*a*c*c*c   + Bx*3*a*a*a*c*c*d
                            + Cx*3*a*a*a*c*d*d + Dx*a*a*a*d*d*d
                            + Ex*3*a*a*b*c*c*c + Fx*9*a*a*b*c*c*d
                            + Gx*9*a*a*b*c*d*d + Hx*3*a*a*b*d*d*d
                            + Ix*3*a*b*b*c*c*c + Jx*9*a*b*b*c*c*d
                            + Kx*9*a*b*b*c*d*d + Lx*3*a*b*b*d*d*d
                            + Mx*b*b*b*c*c*c   + Nx*3*b*b*b*c*c*d
                            + Ox*3*b*b*b*c*d*d + Px*b*b*b*d*d*d;
                                      
                points[v++] = Ay*a*a*a*c*c*c   + By*3*a*a*a*c*c*d
                            + Cy*3*a*a*a*c*d*d + Dy*a*a*a*d*d*d
                            + Ey*3*a*a*b*c*c*c + Fy*9*a*a*b*c*c*d
                            + Gy*9*a*a*b*c*d*d + Hy*3*a*a*b*d*d*d
                            + Iy*3*a*b*b*c*c*c + Jy*9*a*b*b*c*c*d
                            + Ky*9*a*b*b*c*d*d + Ly*3*a*b*b*d*d*d
                            + My*b*b*b*c*c*c   + Ny*3*b*b*b*c*c*d
                            + Oy*3*b*b*b*c*d*d + Py*b*b*b*d*d*d;
            
                points[v++] = Az*a*a*a*c*c*c   + Bz*3*a*a*a*c*c*d
                            + Cz*3*a*a*a*c*d*d + Dz*a*a*a*d*d*d
                            + Ez*3*a*a*b*c*c*c + Fz*9*a*a*b*c*c*d
                            + Gz*9*a*a*b*c*d*d + Hz*3*a*a*b*d*d*d
                            + Iz*3*a*b*b*c*c*c + Jz*9*a*b*b*c*c*d
                            + Kz*9*a*b*b*c*d*d + Lz*3*a*b*b*d*d*d
                            + Mz*b*b*b*c*c*c   + Nz*3*b*b*b*c*c*d
                            + Oz*3*b*b*b*c*d*d + Pz*b*b*b*d*d*d;
                
                
                //change the c-variable within the inner loop
                c += change;
                d  = 1.0 - c;
            }
            //change the a-variable outside the inner loop
            a += change;
            b  = 1.0 - a;
                                  
            // Reset the c-variable to make it ready for the inner loop again
            c = 0.0;
            d = 1.0 - c;
        }
    }

	return points;
}



void read_Patch(FILE *f_patch, FILE *f, int detail){
    
	int i=0,j=0,v=0,avanco,k,n_patch,n_vertices, *patchs=NULL;
	float *vertices=NULL,*points=NULL,x,y,z;
    
    
	fscanf(f_patch,"%d\n",&n_patch);
	patchs=(int*)malloc(16*n_patch*sizeof(int));
    
	while(i<n_patch){
		for(j=0;j<15;j++){
			fscanf(f_patch,"%d, ",&k);
			patchs[v++]=k;
		}
		fscanf(f_patch,"%d\n",&k);
		patchs[v++]=k;
		i++;
	}
    
	fscanf(f_patch,"%d\n",&n_vertices);
	vertices=(float*)malloc(3*n_vertices*sizeof(float));
	v=0;
	while(fscanf(f_patch," %f, %f, %f\n",&x,&y,&z)!=EOF){
		vertices[v++]=x;
		vertices[v++]=y;
		vertices[v++]=z;
	}
	points=getPoints(patchs,n_patch,vertices,n_vertices,detail);
    
    
    
	//Imprimir Vertices
	n_vertices=n_patch*(3*(detail+1)*(detail+1));
	fprintf(f, "%d\n",n_vertices);
    for(i=0;i<n_vertices;i+=3)
        fprintf(f, "%f %f %f\n",points[i],points[i+1],points[i+2]);
    
    
    //Imprimir Indices
    n_vertices=n_patch * detail * detail *3*2;
    fprintf(f, "%d\n",n_vertices);
    
    avanco=(detail+1)*(detail+1);
    
    for(i=0;i<n_patch;i++){
        for (j=0; j<detail; j++) {
            for (v=0; v<detail; v++) {
                
                
                fprintf(f, "%d %d %d\n",i*avanco + j*(detail+1) + v, i*avanco + j*(detail+1) + v+1 ,i*avanco + (j+1)*(detail+1) + v );
                fprintf(f, "%d %d %d\n", i*avanco + j*(detail+1) + v+1 , i*avanco + (j+1)*(detail+1) + v+1 ,i*avanco + (j+1)*(detail+1) + v  );
              
            }
        }
        
    }
}




