#include "Modifications.h"


using namespace std;
using namespace cv;




Modifications::Modifications()
{
}


Modifications::~Modifications()
{
}

void Modifications::LoadImage(Mat image)
{

	using namespace std;
	using namespace cv;


	int main()
	{
		Mat img = imread("lena.png");
		namedWindow("image", WINDOW_NORMAL);
		imshow("image", img);
		waitKey(0);
		return 0;


}

void FiltreMedian(Mat Image)
{
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		medianBlur(src, dst, i);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}
}

void FiltreGaussien(Mat Image)
{
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		if (display_dst(DELAY_BLUR) != 0) { return 0; }
	}
}

void GradientSobel(Mat Image)
{	//Variables à utiliser
	Mat src, src_gray;
	Mat grad;
	char* window_name = "Sobel Demo - Simple Edge Detector";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	//Charger l'image source
	src = imread(argv[1]);

	if (!src.data)
	{
		return -1;
	}

	//Filtre Gaussien pour reduire le bruit
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	//Conversion de l'image en échelle de gris
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//Calcul du Gradient
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	// Gradient X
	Sobel(, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	// Gradient Y
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);

	//Reconversion vers le CV_8U
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);


	//Approximation du Gradient en additionnant les deux Gradients directionnels
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	//Observation du résultat
	imshow(window_name, grad);


}

void Dilatation(Mat Image)
{
	int dilation_type;
	if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));

	dilate(src, dilation_dst, element);
	imshow("Dilation Demo", dilation_dst);
}

void Erosion(Mat Image)
{
	int erosion_type;
	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	erode(src, erosion_dst, element);
	imshow("Erosion Demo", erosion_dst);
}

void ContourCanny(Mat Image)
{
	Mat src, src_gray;
	Mat dst, detected_edges;

	int edgeThresh = 1;
	int lowThreshold;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	char* window_name = "Edge Map";

	//chargement de l'image source
	src = imread(argv[1]);

	if (!src.data)
	{
		return -1;
	}
	//Création d'une matrice
	dst.create(src.size(), src.type());

	//Conversion de l'image en échelle de gris
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//Fenêtre pour afficher les résultats
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	// entrée du seuil par l'utilisateur
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	//Observation de l'image
	CannyThreshold(0, 0);

	waitKey(0);
	return 0;




}

void Seuillage(Mat Image)
{	
	//Variables à utiliser

	int threshold_value = 0;
	int threshold_type = 3;;
	int const max_value = 255;
	int const max_type = 4;
	int const max_BINARY_value = 255;

	char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
	char* trackbar_value = "Value";

	//Chargement de l'image et conversion en échelle de gris
	src = imread(argv[1], 1);
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//Type de seuillage et valeur du seuillage
	createTrackbar(trackbar_type,
		window_name, &threshold_type,
		max_type,);
	createTrackbar(trackbar_value,
		window_name, &threshold_value,
		max_value,);

}

void Segmentation(Mat Image)
{
	using namespace std;
	using namespace cv;
	//Chargement de l'image
	CommandLineParser parser(argc, argv, "Image.png");
	Mat src = imread(parser.get<String>("Image.png"));
	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " Image.png" << endl;
		return -1;
	}


	//Le fond d'écran passe en noir pour une meilleure facilité d'extraction
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (src.at<Vec3b>(i, j) == Vec3b(255, 255, 255))
			{
				src.at<Vec3b>(i, j)[0] = 0;
				src.at<Vec3b>(i, j)[1] = 0;
				src.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	//On passe l'image en noir et blanc
	Mat bw;
	cvtColor(imgResult, bw, COLOR_BGR2GRAY);
	threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("Binary Image", bw);

	// Création de la version CV_8U pour l'image
	Mat dist_8u;
	dist.convertTo(dist_8u, CV_8U);

	// détection des marqueurs
	vector<vector<Point> > contours;
	findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// Création du marqueur pour l'utilisation du watershed
	Mat markers = Mat::zeros(dist.size(), CV_32S);

	// Dessine les marqueurs du premier plan
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
	}
	// Dessine le marqueur d'arrière-plan
	circle(markers, Point(5, 5), 3, Scalar(255), -1);
	imshow("Markers", markers * 10000);
}

void Modifications::notify()
{
}

void Modifications::display()
{
	int choix;

	cout << "1 - Filtre Médian" << endl;
	cout << "2 - Filtre Gaussien" << endl;
	cout << "3 - Calcul de Gradient" << endl;
	cout << "4 - Fonction Dilatation" << endl;
	cout << "5 - Fonction Erosion" << endl;
	cout << "6 - Détecteur de contours Canny" << endl;
	cout << "7 - Fonction Seuillage" << endl;
	cout << "8 - Fonction Segmentation par croissance de régions" << endl;

	cin >> choix;

	switch (choix) {
	case 1:
		FiltreMedian(Image);
	case 2:
		FiltreGaussien( Image);
	case 3:
		GradientSobel(Image);
	case 4:
		Dilatation(Image);
	case 5:
		Erosion(Image);
	case 6:
		ContourCanny(Image);
	case 7:
		Seuillage(Image);
	case 8:
		Segmentation(Image);
	}
}
