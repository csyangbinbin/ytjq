#include "stdafx.h"
#include "utility.h"

img_parse_result parseImg(const char* img_file)
{
#define TMP_IMG_FILE	"tmp_img.jpg"
	img_parse_result	ret ; 
	ret.parse_success  = false ; 

	Image image;
	try { 
		image.read( img_file );
		image.quantizeColorSpace( GRAYColorspace ); 
		image.quantizeColors( 256 ); 
		image.quantize( );
		image.compressType(NoCompression);
		image.write( TMP_IMG_FILE ); 
	} 
	catch( Exception &error_ ) 
	{ 
		printf("error");
		return ret; 
	} 
	char *outText;
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	if (api->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		return ret ;
	}

	Pix *imageP = pixRead(TMP_IMG_FILE);
	api->SetImage(imageP);
	outText = api->GetUTF8Text();
	printf("OCR output:\n%s", outText);

	int f = outText[0] -'0' ;
	int s = outText[2] - '0' ;
	ret.first_number = f ;
	ret.second_number = s ; 
	ret.parse_success = true ; 


	api->End();
	delete [] outText;
	pixDestroy(&imageP);

	return ret ; 
}


