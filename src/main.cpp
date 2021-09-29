#include "CameraPerspective.h"
#include "CameraEnvironmental.h"

#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"
#include "PrimDisc.h"

Mat RenderFrame(ICamera& camera)
{
	// scene objects
	
//	CPrimSphere s1(Vec3f(-2, 1.7f, 0), 2);
	CPrimSphere s2(Vec3f(1, -1, 1), 2.2f);
	CPrimSphere s3(Vec3f(3, 0.8f, -2), 2);
	CPrimPlane p1(Vec3f(0, -1, 0), Vec3f(0, 1, 0));
	// Add disc primitive here
    CPrimDisc s1(Vec3f(-2, 1.7f, 0), Vec3f(0, 0, 1), 2);

	CPrimTriangle t1(Vec3f(-2, 3.7f, 0), Vec3f(1, 2, 1), Vec3f(3, 2.8f, -2));
	CPrimTriangle t2(Vec3f(3, 2, 3), Vec3f(3, 2, -3), Vec3f(-3, 2, -3));
	
	Mat img(camera.getResolution(), CV_32FC3); 	// image array
	Ray ray;                            		// primary ray
	
    const auto background = RGB(0, 0, 0);
    const auto red = RGB(1, 0, 0);
    const auto magenta = RGB(1, 0, 1);
    const auto green = RGB(0, 1, 0);
    const auto blue = RGB(0, 0, 1);
    const auto yellow = RGB(1, 1, 0);
    const auto cyan = RGB(0, 1, 1);
    const auto white = RGB(1, 1, 1);
    
	for(int y = 0; y< img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			
			// Initialize your ray here
			
			// --- PUT YOUR CODE HERE ---
            camera.InitRay(ray, x, y);
//			Vec3f col = RGB(0, 0, 0); // background color
			
			/*
			 * Find closest intersection with scene
			 * objetcs and calculate color
			 */
			
			 // --- PUT YOUR CODE HERE ---
			
//			img.at<Vec3f>(y, x) = col; // store pixel color
            img.at<Vec3f>(y, x) = background;
//            if (s1.intersect(ray)) img.at<Vec3f>(y, x) = red;
            
            if (s2.intersect(ray)) img.at<Vec3f>(y, x) = green;
            
            if (s3.intersect(ray)) img.at<Vec3f>(y, x) = blue;
            
            // s1.intersect(ray) with color(magenta) for the disc
            if (s1.intersect(ray)) img.at<Vec3f>(y, x) = magenta;
            
            if (p1.intersect(ray)) img.at<Vec3f>(y, x) = yellow;
            
            if (t1.intersect(ray)) img.at<Vec3f>(y, x) = cyan;
            
            if (t2.intersect(ray)) img.at<Vec3f>(y, x) = white;
		}
	
	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	const Size resolution(800, 600);
	// render three images with different camera settings
	
	CCameraPerspective cam1(resolution, Vec3f(0, 0, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60);
	Mat img1 = RenderFrame(cam1);
	imwrite("perspective1_withDisc.jpg", img1);
	
	CCameraPerspective cam2(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45);
	Mat img2 = RenderFrame(cam2);
	imwrite("perspective2_withDisc.jpg", img2);
	
	CCameraPerspective cam3(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(1, 1, 0), 45);
	Mat img3 = RenderFrame(cam3);
	imwrite("perspective3_withDisc.jpg", img3);

	// AddeEnvironmental camera here as cam4
    CCameraEnvironmental cam4(resolution, Vec3f(-8, 3, 8), 45);
    Mat img4 = RenderFrame(cam4);
    imwrite("environmental_withDisc.jpg", img4);

	return 0;
}
