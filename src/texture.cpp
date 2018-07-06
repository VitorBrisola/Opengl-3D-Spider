#include <texture.h>
#include <stdlib.h>
#include <stdio.h>

#include "opencv2/opencv.hpp"


    void loadTexture (const char * filename,GLuint *texture){
		
		printf("procurando o arquivo...\n");

		cv::Mat img = cv::imread(filename);
		cv::flip(img, img, 0);

		if(img.empty())
			printf("IMAGEM VAZIA!!!\n");

		printf("Inicializando espaco para textura...\n");
		
		// gerando um bjeto de textura vazio, indicando o numero de objetos e os identificadores dos mesmos
		glGenTextures( 1, texture );
		// falando para o opengl que iremos trabalhar com esse objeto 
		glBindTexture( GL_TEXTURE_3D, *texture ); 
		
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

        printf("parametrizando textura...[%d]\n",*texture);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		printf("armazenando imagem como textura...\n");

		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, img.cols, img.rows, 1, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());
    
        printf("textura carregada!\n");		
	}

	void loadTexture2d (const char * filename,GLuint *texture){

		printf("procurando o arquivo...\n");

		cv::Mat img = cv::imread(filename);
		cv::flip(img, img, 0);

		if(img.empty())
			printf("IMAGEM VAZIA!!!\n");

		printf("Inicializando espaco para textura...\n");
		
		// gerando um bjeto de textura vazio, indicando o numero de objetos e os identificadores dos mesmos
		glGenTextures( 1, texture );
		// falando para o opengl que iremos trabalhar com esse objeto 
		glBindTexture( GL_TEXTURE_2D, *texture ); 

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    	
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());

	};

	void loadTextureCubeMap(const char * filename,GLuint *texture){

		printf("procurando o arquivo cube...\n");

		cv::Mat img = cv::imread(filename);
		cv::flip(img, img, 0);

		if(img.empty())
			printf("IMAGEM VAZIA!!!\n");

		printf("Inicializando espaco para textura...\n");
		
		// gerando um bjeto de textura vazio, indicando o numero de objetos e os identificadores dos mesmos
		glGenTextures( 1, texture );
		// falando para o opengl que iremos trabalhar com esse objeto 
		glBindTexture( GL_TEXTURE_CUBE_MAP, *texture ); 
		
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

        printf("parametrizando textura...[%d]\n",*texture);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, 
					GL_UNSIGNED_BYTE, img.ptr());

	}
		
	void FreeTexture( GLuint texture ){
		glDeleteTextures( 1, &texture );
	}



