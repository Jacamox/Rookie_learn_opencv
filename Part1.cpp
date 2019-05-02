#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
//#define fliter
//#define morph
//#define resize
//#define edge_detect

//you just need to uncomment the definition above

using namespace std;
using namespace cv;

int main()
{
	Mat imgin = imread("D:\\1.jpg");//Remember to change your location
	namedWindow("Original", WINDOW_NORMAL); //In this way you can change the window with your mouse, simple and easy
	imshow("Original", imgin);

#ifdef fliter

	Mat imgout;
	GaussianBlur(imgin, imgout, Size(3, 3), 0, 0);//Size means the size of kernel, the next two zeros means the param will be calced by the third one
	boxFilter(imgin, imgout, -1, Size(5, 5));//the third param means the depth of the pic, -1 means it will call imgout.depth()
	blur(imgin, imgout, Size(5, 5));
	medianBlur(imgin, imgout, 7);//the third param means the linear dimension of flitering aparture, >1 and must be odd(3, 5, ...)
	bilateralFilter(imgin, imgout, 25, 25 * 2, 25 / 2);//if the third param is not positive, it will be calced by the next two params(sigmaplace)
	imshow("Fliter", imgout);
	waitKey(0);

#endif // fliter

#ifdef morph

	Mat imgout;
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//size means the size of each processing unit, either too big or too small will make the pic lose details
	morphologyEx(imgin, imgout, MORPH_GRADIENT, element);
	namedWindow("morphology", WINDOW_NORMAL);
	imshow("morphology", imgout);
	waitKey(0);

#endif // morph

#ifdef resize

	Mat rsimg = Mat::zeros(512, 512, CV_8UC3);//8bits undesigned should be 8U, 3 channels rgb should be C3

	//resize(imgin, rsimg, rsimg.size, (0, 0), (0, 0), INTER_LINEAR);
	resize(imgin, rsimg, Size(), 0.5, 0.5);//change to 0.5 times of the original one

	//pyrUp(imgin, rsimg, Size(imgin.cols * 2, imgin.rows * 2));//These two are right
	//pyrDown(imgin, rsimg, Size(imgin.cols * 0.5, imgin.rows * 0.5)); 

	//cout << rsimg << endl; //all the element in it is zero

	namedWindow("BeforeAdjust", WINDOW_NORMAL);
	imshow("BeforeAdjust", rsimg);//something wrong happened, it seems the resize() function is not implemented.
	waitKey(0);

#endif // resize

#ifdef edge_detect

	//use Ctrl+k+c & Ctrl+k+u to make a multiline comment

	//CANNY
	Mat edge, grayimage;
	cvtColor(imgin, grayimage, COLOR_BGR2GRAY); //change to gray image
	bilateralFilter(grayimage, edge, 25, 25 * 2, 25 / 2); //fliter
	Canny(edge, edge, 10, 10, 3); //use Canny, the third and forth param control the precision, the bigger the more accurate, the fifth is the size of aperture which can be ignored
	imshow("Canny on edge", edge);
	waitKey(0);


	////SOBEL
	//Mat grad_x, grad_y;
	//Mat abs_grad_x, abs_grad_y, dst;
	////gradient on axis x
	//Sobel(imgin, grad_x, CV_8U, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	//convertScaleAbs(grad_x, abs_grad_x);
	//imshow("sobel on x", abs_grad_x);
	////gradient on axis y
	//Sobel(imgin, grad_y, CV_8U, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	//convertScaleAbs(grad_y, abs_grad_y);
	//imshow("sobel on y", abs_grad_y);
	////combined gradient on x & y
	//addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);//the first and third param are the two gradients, the second and fourth are the weight, the fifth is gamma
	//imshow("sobel on whole", dst);
	//waitKey(0);

	
	////LAPLACIAN
	//Mat grayImage, dst, abs_dst;
	//GaussianBlur(imgin, imgin, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//cvtColor(imgin, grayImage, COLOR_RGB2GRAY);
	//Laplacian(grayImage, dst, CV_8U, 3, 1, 0, BORDER_DEFAULT);
	//convertScaleAbs(dst, abs_dst);
	//imshow("laplacian", abs_dst);
	//waitKey(0);

#endif // edge_detect

}
