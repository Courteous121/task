#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Vec4i> hierarchy;
Mat imghsv, mask;
vector<vector<Point>> t1;

string conver2string(double d)
{
    ostringstream os;
    if (os << d)
        return os.str();
    return "invalid conversion";
}

class light
{
private:
    vector<vector<Point>> t0;
    RotatedRect rect1;
    Point2f vertices3[4];
    Rect brect;
    vector<RotatedRect> rectbox0;

public:
    light(vector<vector<Point>> t)
    {
        t0 = t;
    }
    vector<RotatedRect> getrectbox();
};
vector<RotatedRect> light::getrectbox()
{
    for (int i = 0; i < t0.size(); i++)
    {
        rect1 = minAreaRect(t0[i]);

        rect1.points(vertices3);
        brect = rect1.boundingRect();
        double m5 = rect1.size.width > rect1.size.height ? rect1.size.width : rect1.size.height;
        double n5 = rect1.size.width < rect1.size.height ? rect1.size.width : rect1.size.height;
        double m = m5 / n5;
        double n = brect.height / brect.width;
        if (m > 3 && m < 8 && n > 0 && n < 6 && brect.area() > 50 && rect1.size.area() > 50)
        {

            rectbox0.push_back(rect1);
        }
    }
    return rectbox0;
}

class zjb
{
private:
    Mat img0;
    vector<RotatedRect> rectbox2;
    Point2f vertices1[4];
    Point2f vertices2[4];

public:
    zjb(vector<RotatedRect> rectbox, Mat img1)
    {
        rectbox2 = rectbox;
        img0 = img1;
    }
    void drawline();
};

void zjb::drawline()
{
    for (int i = 0; i < static_cast<int>(rectbox2.size()) - 1; i++)
    {

        rectbox2[i].points(vertices1);
        rectbox2[i + 1].points(vertices2);

        double x1 = (vertices1[1].x + vertices1[2].x) / 2;
        double y1 = (vertices1[1].y + vertices1[2].y) / 2;
        double x2 = (vertices2[0].x + vertices2[3].x) / 2;
        double y2 = (vertices2[0].y + vertices2[3].y) / 2;
        double x3 = (vertices1[0].x + vertices1[3].x) / 2;
        double y3 = (vertices1[0].y + vertices1[3].y) / 2;
        double x4 = (vertices2[1].x + vertices2[2].x) / 2;
        double y4 = (vertices2[1].y + vertices2[2].y) / 2;

        float m1 = rectbox2[i].size.height > rectbox2[i].size.width ? rectbox2[i].size.height : rectbox2[i].size.width;
        float n1 = sqrt(pow((vertices1[3].x - vertices2[3].x), 2) + pow((vertices1[3].y - vertices2[3].y), 2));
        float m = n1 / m1;
        float n = n1 * m1;
        double m2 = abs(vertices2[3].x - vertices1[1].x);
        double n2 = abs(vertices2[3].y - vertices1[1].y);
        double m0 = m2 / n2;
        if (m > 2 && m < 5 && n < 150000 && n > 200 && m0 < 10)
        {

            line(img0, vertices1[1], vertices2[3], Scalar(0, 0, 255), 1);
            line(img0, vertices1[3], vertices2[1], Scalar(0, 0, 255), 1);
            double x1 = (vertices1[1].x + vertices2[3].x) / 2;
            double y1 = (vertices1[1].y + vertices2[3].y) / 2;
            circle(img0, Point(x1, y1), 5, Scalar(0, 255, 255), -1);
        }
    }
}
int main()
{
    VideoCapture cap;
    cap.open("1920_1.avi");
    Mat img;
    while (true)
    {
        cap.read(img);
        cvtColor(img, imghsv, COLOR_BGR2HSV);

        Scalar lower(0, 0, 87);
        Scalar upper(126, 182, 255);
        inRange(imghsv, lower, upper, mask);
        findContours(mask, t1, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
        vector<RotatedRect> rectbox;

        light s1(t1);
        rectbox = s1.getrectbox();
        zjb s2(rectbox,img);
        s2.drawline();

        namedWindow("image", (640, 560));
        namedWindow("imghsv", (640, 560));
        namedWindow("img mask", (640, 560));

        imshow("image", img);
        imshow("imghsv", imghsv);
        imshow("img mask", mask);
        if (waitKey(10) == 27)
            if (waitKey(0) == 27)
                break;
    }
}
