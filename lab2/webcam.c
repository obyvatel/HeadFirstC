#include <stdio.h>
#include "c:\opencv\modules\highgui\include\opencv2\highgui\highgui_c.h"

int main()
{
	CvCapture* webcam = cvCreateCameraCapture(0);
	if (!webcam)
	{	// проверка на ошибки
		return 1;
	}
	
	do
	{
		IplImage* image = cvQueryFrame(webcam);
		if (image)
		{ // обработать олученное изображение
			cvSaveImage("somefile.jpg", image, 0);
		}
	}
	while (0);
	
	return 0;
}