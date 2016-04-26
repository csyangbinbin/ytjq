#ifndef __YTJQ_INCLUDE__
#define __YTJQ_INCLUDE__
#include "ocrinc/tesseract/baseapi.h"
#include "ocrinc/leptonica/allheaders.h"
#include <Magick++.h>
#include <iostream>
using namespace std; 
using namespace Magick; 

/*
ʶ����֤��ͼƬ ?+?=?
*/
typedef struct img_parse_result_tag
{
	int first_number ; //��һ������
	int second_number ;  //�ڶ�������
	bool parse_success ;  //��֤��ʶ���Ƿ�ɹ�
}img_parse_result ; 


/*
ʶ����֤��ͼƬ����
*/
img_parse_result parseImg(const char* img_file) ; 


#endif