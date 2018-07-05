#include <texture.h>
#include <stdlib.h>
#include <stdio.h>

#include "opencv2/opencv.hpp"
//#include "ofMain.h" 

    void loadTexture (const char * filename,GLuint *texture){
		
		//GLuint texture = 0;

		printf("procurando o arquivo...\n");

		//ofDisableArbTex(); 
		cv::Mat img = cv::imread(filename);
		cv::flip(img, img, 0);

		if(img.empty())
			printf("IMAGEM VAZIA!!!\n");

		printf("Inicializando espaco para textura...\n");
		
		// gerando um bjeto de textura vazio, indicando o numero de objetos e os identificadores dos mesmos
		glGenTextures( 1, texture );
		// falando para o opengl que iremos trabalhar com esse objeto 
		glBindTexture( GL_TEXTURE_3D, *texture ); 
		
		//glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

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
		
	void FreeTexture( GLuint texture ){
		glDeleteTextures( 1, &texture );
	}



// Fun��o para ler um arquivo JPEG e criar uma textura
/*TEX *CarregaTextura(char *arquivo, bool mipmap)
{
	GLenum formato;

	if(!arquivo)	
		return NULL;

	int indice = _procuraTextura(arquivo);
	if(indice!=-1)
		return _texturas[indice];

	TEX *pImage = CarregaJPG(arquivo);	// carrega o arquivo JPEG

	if(pImage == NULL)
		exit(0);

	strcpy(pImage->nome,arquivo);
	// Gera uma identifica��o para a nova textura
	glGenTextures(1, &pImage->texid);

	// alinhamento da textura na mem�ria
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// textura corrente
	glBindTexture(GL_TEXTURE_2D, pImage->texid);

	if(pImage->ncomp==1) formato = GL_LUMINANCE;
	else formato = GL_RGB;

	if(mipmap)
	{
		// Cria mipmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, pImage->dimx, pImage->dimy,
			formato, GL_UNSIGNED_BYTE, pImage->data);
		// Ajusta os filtros iniciais para a textura
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		// Envia a textura para OpenGl
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, pImage->dimx, pImage->dimx,
			0, formato, GL_UNSIGNED_BYTE, pImage->data);
		// Ajusta os filtros iniciais para a textura
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	free(pImage->data); 	// libera a mem�ria ocupada pela imagem

	// Inclui textura na lista
	_texturas.push_back(pImage);
	return pImage;
}


// Carrega o arquivo JPG e retorna seus dados em uma estrutura tImageJPG.
TEX *CarregaJPG(const char *filename, bool inverte)
{
	struct jpeg_decompress_struct cinfo;
	TEX *pImageData = NULL;
	FILE *pFile;
	
	// verifica se n�o aconteceu um problema na abertura
	if((pFile = fopen(filename, "rb")) == NULL) 
	{
		printf("Imposs�vel carregar arquivo JPG: %s\n",filename);
		return NULL;
	}
	
	// Cria um gerenciado de erro
	jpeg_error_mgr jerr;

	// Objeto com informa��es de compacta��o para o endere�o do gerenciador de erro
	cinfo.err = jpeg_std_error(&jerr);
	
	// Inicializa o objeto de decompacta��o
	jpeg_create_decompress(&cinfo);
	
	// Especifica a origem dos dados (apontador para o arquivo)	
	jpeg_stdio_src(&cinfo, pFile);
	
	// Aloca a estrutura que conter� os dados jpeg
	pImageData = (TEX*)malloc(sizeof(TEX));

	// Decodifica o arquivo JPG e preenche a estrutura de dados da imagem
	DecodificaJPG(&cinfo, pImageData, inverte);
	
	// Libera a mem�ria alocada para leitura e decodifica��o do arquivo JPG
	jpeg_destroy_decompress(&cinfo);
	
	fclose(pFile);

	// Retorna os dados JPG (esta mem�ria deve ser liberada depois de usada)
	return pImageData;
}*/