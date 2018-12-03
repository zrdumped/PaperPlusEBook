#include <mycv.h>
#define gray_scale 256
#define pi CV_PI
#define Pi CV_PI

static void MatMinus(Mat src, Mat mask, Mat dst) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int a;
            if (src.at<Vec4b>(i, j)[0] == 0) a = 0;
            else if (src.at<Vec4b>(i, j)[0] == 255) {
                a = src.at<Vec4b>(i, j)[0] - mask.at<Vec4b>(i, j)[0];
            }

            dst.at<Vec4b>(i, j)[0] = a;
            dst.at<Vec4b>(i, j)[2] = a;
            dst.at<Vec4b>(i, j)[1] = a;
        }
    }
}

static void MatOr(Mat src, Mat mask, Mat dst) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int a;
            if (src.at<Vec4b>(i, j)[0] == 255 || mask.at<Vec4b>(i, j)[0] == 255) a = 255;
            else  a = 0;

            dst.at<Vec4b>(i, j)[0] = a;
            dst.at<Vec4b>(i, j)[1] = a;
            dst.at<Vec4b>(i, j)[2] = a;
        }
    }
}

static void MatAnd(Mat src, Mat mask, Mat dst) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int a;
            if (src.at<Vec4b>(i, j)[0] == 255 && mask.at<Vec4b>(i, j)[0] == 255) a = 255;
            else  a = 0;

            dst.at<Vec4b>(i, j)[0] = a;
            dst.at<Vec4b>(i, j)[1] = a;
            dst.at<Vec4b>(i, j)[2] = a;
        }
    }
}

static void MatComplement(Mat src, Mat dst) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int a;
            if (src.at<Vec4b>(i, j)[0] == 255) a = 0;
            else  a = 255;

            dst.at<Vec4b>(i, j)[0] = a;
            dst.at<Vec4b>(i, j)[1] = a;
            dst.at<Vec4b>(i, j)[2] = a;
        }
    }
}

static bool MatEqual(Mat src, Mat mask) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (src.at<Vec4b>(i, j)[0] != mask.at<Vec4b>(i, j)[0]) return false;
        }
    }
    return true;
}

void MyCvtRGB2GRAY(Mat src, Mat dst) {
    //遍历所有节点
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            Vec4b pt = src.at<Vec4b>(i, j);
            //opencv公式
            int gray = pt[2] * 0.299 + pt[1] * 0.587 + pt[0] * 0.114;
            dst.at<Vec4b>(i, j)[0] = gray;
            dst.at<Vec4b>(i, j)[1] = gray;
            dst.at<Vec4b>(i, j)[2] = gray;

        }
    }
}

//大津算法确定阈值
int MyOtusThreshold(Mat src) {
    int width = src.cols;
    int height = src.rows;
    int pixelCount[gray_scale];
    float pixelPro[gray_scale];
    int i, j, pixelSum = width * height, threshold = 0;
    for (i = 0; i < gray_scale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            Vec4b pt = src.at<Vec4b>(i, j);
            int gray = pt[2];
            pixelCount[gray] += 1;
        }
    }

    //计算每个像素在整幅图像中的比例
    float maxPro = 0.0;
    int kk = 0;
    for (i = 0; i < gray_scale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
            kk = i;
        }
    }

    //遍历灰度级[0,255]
    //w0 前景占比，w1 背景占比， u0 前景平均灰度， u1背景平均灰度， u 总平均灰度
    //delta（类间方差） = w0 (u0 - u) ^ 2 + w1 (u1- u) ^ 2
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < gray_scale; i++)     // i作为阈值
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < gray_scale; j++)
        {
            if (j <= i)   //背景部分
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //前景部分
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = i;
        }
    }

    return threshold;
}

void MyBinary(Mat src, Mat dst, int threshold) {
    //遍历所有节点，判断与阈值的关系
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            Vec4b pt = src.at<Vec4b>(i, j);
            int gray = pt[2];
            if (gray < threshold) {
                dst.at<Vec4b>(i, j)[0] = 0;
                dst.at<Vec4b>(i, j)[1] = 0;
                dst.at<Vec4b>(i, j)[2] = 0;
            }
            else {
                dst.at<Vec4b>(i, j)[0] = 255;
                dst.at<Vec4b>(i, j)[1] = 255;
                dst.at<Vec4b>(i, j)[2] = 255;
            }

        }
    }
}

void MyHitOrMiss(Mat src, int mask[], Mat dst, int SE_ROW, int SE_COL) {
    int mask_c[25];
    for (int i = 0; i < 25; i++) {
        if (mask[i] == 1) mask_c[i] = 0;
        else if (mask[i] == 0) mask_c[i] = 1;
        else mask_c[i] = mask[i];

        //cout << mask[i] << " " << mask_c[i] << endl;
    }
    Mat src_c = Mat(src.rows, src.cols, src.type(), Scalar(0, 0, 0, 0));
    MatComplement(src, src_c);
    //imwrite("src_c.jpg", src_c);

    Mat tmp1 = Mat(src.rows, src.cols, src.type(), Scalar(0, 0, 0, 0));
    //Mat tmp1 = src.clone();
    MyBinaryMorphologyErosion(src, tmp1, mask, SE_ROW, SE_COL);

    Mat tmp2 = Mat(src.rows, src.cols, src.type(), Scalar(0, 0, 0, 0));
    //Mat tmp2 = src.clone();
    //Mat src_c = src.clone();
    MyBinaryMorphologyErosion(src_c, tmp2, mask_c, SE_ROW, SE_COL);

/*	for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (tmp1.at<Vec4b>(i, j)[0] != tmp2.at<Vec4b>(i, j)[0]) cout << "diff" << endl;
        }
    }
    cout << "end" << endl;*/

    MatAnd(tmp1, tmp2, dst);
}

void MyBinaryMorphologyErosion(Mat src, Mat dst, int para[], int SE_ROW, int SE_COL) {
    Mat tmp = Mat(src.rows, src.cols, CV_32SC1, Scalar(0));
    bool chosen;
    for (int i = SE_ROW; i < src.rows - (4 - SE_ROW); i++) {
        for (int j = SE_COL; j < src.cols - (4 - SE_COL); j++) {
            chosen = true;
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 5; b++) {
                    if (para[a * 5 + b] == 1) {
                        if (src.at<Vec4b>(i - SE_ROW + a, j - SE_COL + b)[0] != 255) chosen = false;
                    }
                    else if (para[a * 5 + b] == 0) {
                        if (src.at<Vec4b>(i - SE_ROW + a, j - SE_COL + b)[0] != 0) chosen = false;
                    }
                }
            }
            if (chosen) tmp.at<int>(i, j) = 1;
            else tmp.at<int>(i, j) = 0;
        }
    }
    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            if (tmp.at<int>(i, j) == 1) {
                dst.at<Vec4b>(i, j)[0] = 255;
                dst.at<Vec4b>(i, j)[1] = 255;
                dst.at<Vec4b>(i, j)[2] = 255;
            }
            else {
                dst.at<Vec4b>(i, j)[0] = 0;
                dst.at<Vec4b>(i, j)[1] = 0;
                dst.at<Vec4b>(i, j)[2] = 0;
            }
        }
    }
}

void MyBinaryMorphologyRough(Mat src, Mat dst, int para[], int SE_ROW, int SE_COL) {
    //cout << "Rough" << endl;
    //Mat tmp = Mat(src.rows, src.cols, src.type(), Scalar(0, 0, 0, 0));
    Mat tmp = src.clone();
    for (int i = 0; i < 8; i++) {
        Mat tmp1 = tmp.clone();
        MyHitOrMiss(tmp, para, tmp1, SE_ROW, SE_COL);
        //MatComplement(tmp1, tmp1);
        //MatAnd(tmp, tmp1, tmp);
        MatOr(tmp, tmp1, tmp);

        int tmp_mask[25];
        tmp_mask[0] = para[10];
        tmp_mask[1] = para[5];
        tmp_mask[2] = para[0];
        tmp_mask[3] = para[1];
        tmp_mask[4] = para[2];
        tmp_mask[5] = para[15];
        tmp_mask[6] = para[11];
        tmp_mask[7] = para[6];
        tmp_mask[8] = para[7];
        tmp_mask[9] = para[3];
        tmp_mask[10] = para[20];
        tmp_mask[11] = para[16];
        tmp_mask[12] = para[12];
        tmp_mask[13] = para[8];
        tmp_mask[14] = para[4];
        tmp_mask[15] = para[21];
        tmp_mask[16] = para[17];
        tmp_mask[17] = para[18];
        tmp_mask[18] = para[13];
        tmp_mask[19] = para[9];
        tmp_mask[20] = para[22];
        tmp_mask[21] = para[23];
        tmp_mask[22] = para[24];
        tmp_mask[23] = para[19];
        tmp_mask[24] = para[14];
        for (int i = 0; i < 25; i++) {
            para[i] = tmp_mask[i];
        }
    }


    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            int a;
            if (tmp.at<Vec4b>(i, j)[0] == 255) a = 255;
            else  a = 0;

            dst.at<Vec4b>(i, j)[0] = a;
            dst.at<Vec4b>(i, j)[1] = a;
            dst.at<Vec4b>(i, j)[2] = a;
        }
    }
}

//void MyFilterGauss(Mat src, Mat dst, int size, int sigma) {
//    if (size == 3) {
//        double a = exp(-0 /(2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma* (double)sigma);
//        double b = exp(-1.0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma* (double)sigma);
//        double c = exp(-2.0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma* (double)sigma);
//        double total = a + b * 4.0 + c * 4.0;
//        //std::cout << a << " " << b << " " << c << std::endl;
//        for (int i = 1; i < src.rows - 1; i++) {
//            for (int j = 1; j < src.cols - 1; j++) {
//                double gray = (src.at<Vec4b>(i, j)[0] * a + src.at<Vec4b>(i + 1, j)[0] * b + src.at<Vec4b>(i, j + 1)[0] * b + src.at<Vec4b>(i + 1, j + 1)[0] * c
//                    + src.at<Vec4b>(i - 1, j)[0] * b + src.at<Vec4b>(i - 1, j - 1)[0] * c+ src.at<Vec4b>(i - 1, j + 1)[0] * c
//                    + src.at<Vec4b>(i, j - 1)[0] * b + src.at<Vec4b>(i + 1, j - 1)[0] * c)/total ;
//                //if(i == 200 && j == 300)
//                //std::cout << gray << std::endl;
//                dst.at<Vec4b>(i, j)[0] = gray;
//                dst.at<Vec4b>(i, j)[1] = gray;
//                dst.at<Vec4b>(i, j)[2] = gray;
//            }
//        }
//    }
//    else {
//        double a = exp(-0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma);
//        double b = exp(-1.0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma);
//        double c = exp(-2.0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma);
//        double d = exp(-4.0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma);
//        double e = exp(-5.0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma);
//        double f = exp(-8.0 / (2.0 * (double)sigma * (double)sigma)) / (2.0 * pi * (double)sigma);
//        double total = a + b * 4.0 + c * 4.0 + d * 4.0 + e * 8.0 + f * 4.0;
//        for (int i = 2; i < src.rows - 2; i++) {
//            for (int j = 2; j < src.cols - 2; j++) {
//                int gray = (src.at<Vec4b>(i - 2, j - 2)[0] * f + src.at<Vec4b>(i - 2, j - 1)[0] * e + src.at<Vec4b>(i - 2, j)[0] * d + src.at<Vec4b>(i - 2, j + 1)[0] * e + src.at<Vec4b>(i - 2, j + 2)[0] * f +
//                    src.at<Vec4b>(i - 1, j - 2)[0] * e + src.at<Vec4b>(i - 1, j - 1)[0] * c + src.at<Vec4b>(i - 1, j)[0] * b + src.at<Vec4b>(i - 1, j + 1)[0] * c + src.at<Vec4b>(i - 1, j + 2)[0] * e +
//                    src.at<Vec4b>(i, j - 2)[0] * d + src.at<Vec4b>(i, j - 1)[0] * b + src.at<Vec4b>(i, j)[0] * a + src.at<Vec4b>(i, j + 1)[0] * b + src.at<Vec4b>(i, j + 2)[0] * d +
//                    src.at<Vec4b>(i + 1, j - 2)[0] * e + src.at<Vec4b>(i + 1, j - 1)[0] * c + src.at<Vec4b>(i + 1, j)[0] * b + src.at<Vec4b>(i + 1, j + 1)[0] * c + src.at<Vec4b>(i + 1, j + 2)[0] * e +
//                    src.at<Vec4b>(i + 2, j - 2)[0] * f + src.at<Vec4b>(i + 2, j - 1)[0] * e + src.at<Vec4b>(i + 2, j)[0] * d + src.at<Vec4b>(i + 2, j + 1)[0] * e + src.at<Vec4b>(i + 2, j + 2)[0] * f) / total;
//                dst.at<Vec4b>(i, j)[0] = gray;
//                dst.at<Vec4b>(i, j)[1] = gray;
//                dst.at<Vec4b>(i, j)[2] = gray;
//            }
//        }
//    }
//    return;
//}

//void MyConvolution(Mat src, Mat dst, int para[]) {
//    int sum;
//    for (int i = 0; i < 9; i++) {
//        sum += para[i];
//    }
//    for (int i = 1; i < src.rows - 1; i++) {
//        for (int j = 1; j < src.cols - 1; j++) {
//            int gray = (src.at<Vec4b>(i, j)[0] * para[4] + src.at<Vec4b>(i + 1, j)[0] * para[7] + src.at<Vec4b>(i, j + 1)[0] * para[5] + src.at<Vec4b>(i + 1, j + 1)[0] * para[8]
//                + src.at<Vec4b>(i - 1, j)[0] * para[1] + src.at<Vec4b>(i - 1, j - 1)[0] * para[0] + src.at<Vec4b>(i - 1, j + 1)[0] * para[2]
//                + src.at<Vec4b>(i, j - 1)[0] * para[3] + src.at<Vec4b>(i + 1, j - 1)[0] * para[6]);
//            dst.at<int>(i, j) = gray;
//        }
//    }
//}

//void MyEdgeSobel(Mat src, Mat dst, Mat GX, Mat GY) {
//    int paraX[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
//    int paraY[9] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };

//    MyConvolution(src, GX, paraX);
//    MyConvolution(src, GY, paraY);

//    for (int i = 0; i < src.rows; i++) {
//        for (int j = 0; j < src.cols; j++) {
//            Vec4b pt = src.at<Vec4b>(i, j);
//            int res = sqrt(GX.at<int>(i, j) * GX.at<int>(i, j) + GY.at<int>(i, j) * GY.at<int>(i, j));
//            if (res > 255) res = 255;
//            dst.at<Vec4b>(i, j)[0] = res;
//            dst.at<Vec4b>(i, j)[1] = res;
//            dst.at<Vec4b>(i, j)[2] = res;
//        }
//    }
//}

//void MyEdgeCanny(Mat src, Mat dst,int high, int low, int sigma) {
//    Mat tmp = Mat(src.rows, src.cols, src.type(), Scalar(0, 0, 0, 0));
//    MyFilterGauss(src, tmp, 3, sigma);

//    Mat GX = Mat(src.rows, src.cols, CV_32SC4, Scalar(0, 0, 0, 0));
//    Mat GY = Mat(src.rows, src.cols, CV_32SC4, Scalar(0, 0, 0, 0));
//    MyEdgeSobel(tmp, tmp, GX, GY);
//    Mat temp = tmp.clone();
//    Mat mask = Mat(src.rows, src.cols, CV_32SC4, Scalar(0, 0, 0, 0));
//    std::vector<int> rootxs;
//    std::vector<int> rootys;
//    for (int i = 1; i < dst.rows - 1; i++) {
//        for (int j = 1; j < dst.cols - 1; j++) {
//            double angle = atan2(GY.at<int>(i, j), GX.at<int>(i, j));
//            if (angle <= 0) angle += pi;
//            //std::cout << angle << std::endl;
//            int gray = tmp.at<Vec4b>(i, j)[0];
//            int dir;
//            //竖着为0， 二四象限为1， 横为2， 一三象限为3
//            if (angle > pi  * 3.0 / 8.0 && angle < pi * 5.0 / 8.0) dir = 0;
//            else if (angle >= pi * 5.0 / 8.0 && angle < pi  * 7.0 / 8.0) dir = 1;
//            else if (angle >= pi / 8.0 && angle < pi * 3.0 / 8.0) dir = 3;
//            else dir = 2;
//            switch (dir) {
//            case 0:
//                if (tmp.at<Vec4b>(i - 1, j)[0] < gray && tmp.at<Vec4b>(i + 1, j)[0] < gray){
//                    temp.at<Vec4b>(i, j)[0] = tmp.at<Vec4b>(i, j)[0];
//                    temp.at<Vec4b>(i, j)[1] = tmp.at<Vec4b>(i, j)[1];
//                    temp.at<Vec4b>(i, j)[2] = tmp.at<Vec4b>(i, j)[2];
//                }
//                else {
//                    temp.at<Vec4b>(i, j)[0] = 0;
//                    temp.at<Vec4b>(i, j)[1] = 0;
//                    temp.at<Vec4b>(i, j)[2] = 0;
//                }
//                break;
//            case 1:
//                if (tmp.at<Vec4b>(i - 1, j - 1)[0] < gray && tmp.at<Vec4b>(i + 1, j + 1)[0] < gray)
//                {
//                    temp.at<Vec4b>(i, j)[0] = tmp.at<Vec4b>(i, j)[0];
//                    temp.at<Vec4b>(i, j)[1] = tmp.at<Vec4b>(i, j)[1];
//                    temp.at<Vec4b>(i, j)[2] = tmp.at<Vec4b>(i, j)[2];
//                }
//                else {
//                    temp.at<Vec4b>(i, j)[0] = 0;
//                    temp.at<Vec4b>(i, j)[1] = 0;
//                    temp.at<Vec4b>(i, j)[2] = 0;
//                }
//                break;
//            case 2:
//                if (tmp.at<Vec4b>(i, j + 1)[0] < gray && tmp.at<Vec4b>(i, j - 1)[0] < gray)
//                {
//                    temp.at<Vec4b>(i, j)[0] = tmp.at<Vec4b>(i, j)[0];
//                    temp.at<Vec4b>(i, j)[1] = tmp.at<Vec4b>(i, j)[1];
//                    temp.at<Vec4b>(i, j)[2] = tmp.at<Vec4b>(i, j)[2];
//                }
//                else {
//                    temp.at<Vec4b>(i, j)[0] = 0;
//                    temp.at<Vec4b>(i, j)[1] = 0;
//                    temp.at<Vec4b>(i, j)[2] = 0;
//                }
//                break;
//            case 3:
//                if (tmp.at<Vec4b>(i - 1, j + 1)[0] < gray && tmp.at<Vec4b>(i + 1, j - 1)[0] < gray)
//                {
//                    temp.at<Vec4b>(i, j)[0] = tmp.at<Vec4b>(i, j)[0];
//                    temp.at<Vec4b>(i, j)[1] = tmp.at<Vec4b>(i, j)[1];
//                    temp.at<Vec4b>(i, j)[2] = tmp.at<Vec4b>(i, j)[2];
//                }
//                else {
//                    temp.at<Vec4b>(i, j)[0] = 0;
//                    temp.at<Vec4b>(i, j)[1] = 0;
//                    temp.at<Vec4b>(i, j)[2] = 0;
//                }
//                break;
//            default:
//                break;
//            }
//            //0 no 1 weak 2 strong
//            if (temp.at<Vec4b>(i, j)[0] > high) {
//                mask.at<int>(i, j) = 2;
//                rootxs.push_back(i);
//                rootys.push_back(j);
//            }
//            else if (temp.at<Vec4b>(i, j)[0] < low)mask.at<int>(i, j) = 0;
//            else mask.at<int>(i, j) = 1;
//        }

//    }

///*	for (int i = 1; i < dst.rows - 1; i++) {
//        for (int j = 1; j < dst.cols - 1; j++) {
//                int gray = temp.at<Vec4b>(i, j)[0];
//                dst.at<Vec4b>(i, j)[0] = gray;
//                dst.at<Vec4b>(i, j)[1] = gray;
//                dst.at<Vec4b>(i, j)[2] = gray;

//        }
//    }
//    return;*/


//    for (int i = 0; i < rootxs.size(); i++) {
//    search(rootxs[i], rootys[i], mask);
//    }
//    for (int i = 1; i < dst.rows - 1; i++) {
//        for (int j = 1; j < dst.cols - 1; j++) {
//            if (mask.at<int>(i, j) == 2) {
//                int gray = temp.at<Vec4b>(i, j)[0];
//                dst.at<Vec4b>(i, j)[0] = gray;
//                dst.at<Vec4b>(i, j)[1] = gray;
//                dst.at<Vec4b>(i, j)[2] = gray;
//            }

//            else {
//                dst.at<Vec4b>(i, j)[0] = 0;
//                dst.at<Vec4b>(i, j)[1] = 0;
//                dst.at<Vec4b>(i, j)[2] = 0;
//            }
//        }
//    }



//}

//void MyHoughLine(Mat src, Mat dst, int high, int low, int sigma, int MinNum){
//    Mat tmp = Mat(src.rows, src.cols, src.type(), Scalar(0, 0, 0, 0));
//    MyEdgeCanny(src, tmp, high, low, sigma);
//    MyBinary(tmp, tmp, 1);

//    int width = tmp.cols;
//    int height = tmp.rows;
//    int iRMax = (int)sqrt(width*width + height*height) + 1;
//    int iThMax = 500;// theta0;
//    int *pArray;
//    pArray = new int[2 * iRMax*iThMax];
//    memset(pArray, 0, sizeof(int) * 2 * iRMax*iThMax);
//    float fRate = (float)(Pi / 180);
//    vector<Vec2f> lines;
//    for (int y = 0; y < height; y++)
//        for (int x = 0; x < width; x++)
//        {
//            if (tmp.at<Vec4b>(y, x)[0] == 255)
//            {
//                for (int iTh = 0; iTh < iThMax; iTh += 1)
//                {
//                    int iR = (int)(x*cos(iTh*fRate) + y*sin(iTh*fRate));
//                    //if (iR < 0)
//                    //    continue;
//                    iR = iR + iRMax;
//                    pArray[2 * iRMax*iTh + iR]++;
//                }
//            }
//        }
//    for (int theta = 0; theta < 500; theta++)
//    {
//        for (int r = 0; r < iRMax * 2; r++)
//        {
//            int thetaL = max(0, theta - 1);
//            int thetaR = min(359, theta + 1);
//            int rL = max(0, r - 1);
//            int rR = min(iRMax * 2 - 1, r + 1);
//            int tmp = pArray[theta*iRMax * 2 + r];
//            //if ((tmp>MinNum)
//            //    && tmp>pArray[thetaL*iRMax * 2 + rL] && tmp>pArray[thetaL*iRMax * 2 + r]
//            //    && (tmp>pArray[thetaL*iRMax * 2 + rR])&& (tmp > pArray[theta*iRMax * 2 + rL])
//            //    && (tmp > pArray[theta*iRMax * 2 + rR])&& (tmp > pArray[thetaR*iRMax * 2 + rL])
//            //    && (tmp > pArray[thetaR*iRMax * 2 + r]) && (tmp > pArray[thetaR*iRMax * 2 + rR])
//            if ((tmp>MinNum)
//                && tmp>pArray[thetaL*iRMax * 2 + r]
//                && (tmp >= pArray[theta*iRMax * 2 + rR]) && (tmp > pArray[theta*iRMax * 2 + rL])
//                && (tmp >= pArray[thetaR*iRMax * 2 + r]))
//            {
//                Vec2f t = Vec2f(float(r - iRMax), float(theta));
//                lines.push_back(t);
//            }
//        }
//    }
//}
