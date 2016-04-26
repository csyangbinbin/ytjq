#ifndef __YTJQ_INCLUDE__
#define __YTJQ_INCLUDE__
#include "ocrinc/tesseract/baseapi.h"
#include "ocrinc/leptonica/allheaders.h"
#include <Magick++.h>
#include <iostream>
using namespace std; 
using namespace Magick; 

/*
识别验证码图片 ?+?=?
*/
typedef struct img_parse_result_tag
{
	int first_number ; //第一个数字
	int second_number ;  //第二个数字
	bool parse_success ;  //验证码识别是否成功
}img_parse_result ; 


/*
识别验证码图片内容
*/
img_parse_result parseImg(const char* img_file) ; 


#endif