#include <mycv.h>
#define gray_scale 256

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
