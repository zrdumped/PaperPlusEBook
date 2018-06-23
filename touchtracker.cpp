#include "touchtracker.h"

using namespace std;

// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

// whether to save video
//#define SAVE_VIDEO
// whether to use init image
#define USE_DISK
// The path for init image
#define INIT_PATH string("E:/")
// The path for video input
#define VIDEO_IN string("E:/touch_test_realcut")
// The type of tracker to use (0~5)
#define TRACKER_TYPE 0
// define this to enable showing square and fps on ouput video
#define TT_DEBUG

// The slope of the line to detect shadow
const float slope = 200.0f/662.0f;
// The width of line expected to be black to return true for checkTouch
const int expect = 20;
static Ptr<Tracker> trackerp, trackers;
static int offpx, offpy, offsx, offsy;
static string handle = "default";

TouchTracker::TouchTracker()
{
}

/***************************************************************
 * TouchTracker
 * variable name: 'p' stands for pen, 's' stands for shadow
 * *************************************************************/
int TouchTracker::testTouchPlus()
{
    // #1 - open video
    VideoCapture video(0);
    if(!video.isOpened()) {
        cout << "TouchTracker: could not locate video file "
             << VIDEO_IN + ".mp4, check macro VIDEO_IN" << endl;
        return 1;
    }

#ifdef SAVE_VIDEO
    VideoWriter writer(VIDEO_IN + ".avi", CV_FOURCC('D', 'I', 'V', 'X'), 18.0,
                       Size(video.get(CV_CAP_PROP_FRAME_WIDTH),
                       video.get(CV_CAP_PROP_FRAME_HEIGHT)));
#endif

    // #2 - setup
    Mat frame;
    handle = "testplus";
#ifdef USE_DISK
    initTouchFromDisk();
    while (video.read(frame)) {
        int key = waitKey(1);
        if (key == 27)
            break;
        Rect2d boxp = getRectFromDisk();
        rectangle(frame, boxp, Scalar( 255, 0, 0 ), 2, 1 );
        imshow("Touch Tracking", frame);
    }
#else
    while (video.read(frame)) {
        int key = waitKey(1);
        if (key == 27)
            break;
        imshow("Touch Tracking", frame);
    }
    initTouchIntoDisk(, frame);
#endif

    // #3 - loop for each frame
    bool verbose = true;
    while (video.read(frame)) {
        int key = waitKey(1);
        if(key == 27)
            break;
        else if (key == 'd')
            verbose = !verbose;
        else if (key == 'f') {
            initTouch(frame);
            continue;
        }

        if (checkTouch(frame, verbose)) {
            putText(frame, "Touching", Point(50,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
        }
        imshow("Touch Tracking", frame);
#ifdef SAVE_VIDEO
        writer << frame;
#endif
    }

    destroyWindow("Touch Tracking");
    return 0;
}

int TouchTracker::testTouch()
{
    // #1 - open video
    VideoCapture video(VIDEO_IN + ".mp4");
    if(!video.isOpened()) {
        cout << "TouchTracker: could not locate video file "
             << VIDEO_IN + ".mp4, check macro VIDEO_IN" << endl;
        return 1;
    }
    Mat frame;
    video.read(frame);

#ifdef SAVE_VIDEO
    VideoWriter writer(VIDEO_IN + ".avi", CV_FOURCC('D', 'I', 'V', 'X'), 18.0,
                       Size(video.get(CV_CAP_PROP_FRAME_WIDTH),
                       video.get(CV_CAP_PROP_FRAME_HEIGHT)));
#endif

    // #2 - setup
    //Rect2d boxp(415, 80, 54, 49);
    //initTouch(boxp, frame);
    handle = "test";
#ifdef USE_DISK
    initTouchFromDisk();
#else
    initTouchIntoDisk(frame);
#endif

    // #3 - loop for each frame
    bool verbose = true;
    while (video.read(frame)) {
        int key = waitKey(1);
        if(key == 27)
            break;
        else if (key == 'd')
            verbose = !verbose;
        else if (key == 'f') {
            initTouch(frame);
            continue;
        }

        if (checkTouch(frame, verbose)) {
            putText(frame, "Touching", Point(50,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
        }
        imshow("Touch Tracking", frame);
#ifdef SAVE_VIDEO
        writer << frame;
#endif
    }

    destroyWindow("Touch Tracking");
    return 0;
}

/***************************************************************
 * API part
 * *************************************************************/
void TouchTracker::initTouch(Mat frame)
{
    Rect2d boxp;
    boxp = selectROI(frame, false);
    destroyWindow("ROI selector");
    initTouch(boxp, frame);
}

void TouchTracker::initTouch(Rect2d boxp, Mat frame)
{
    trackerp = getTracker(TRACKER_TYPE);
    trackerp->init(frame, boxp);

    Mat imgp = Mat::Mat(frame, boxp);
    cvtColor(imgp, imgp, CV_BGR2GRAY);
    threshold(imgp, imgp, 0, 255, CV_THRESH_OTSU);
    findNib(imgp, offpx, offpy);
}

Rect2d TouchTracker::getRectFromDisk()
{
    Rect2d boxp;
    QSettings *config = new QSettings(QString::fromStdString(INIT_PATH) + "ppeb_config.ini", QSettings::IniFormat);
    boxp.x = config->value(QString::fromStdString(handle + "/x")).toInt();
    boxp.y = config->value(QString::fromStdString(handle + "/y")).toInt();
    boxp.width = config->value(QString::fromStdString(handle + "/width")).toInt();
    boxp.height = config->value(QString::fromStdString(handle + "/height")).toInt();
    return boxp;
}

void TouchTracker::initTouchFromDisk()
{
    Mat frame = imread(INIT_PATH + "ppeb_track_" + handle + ".png");
    if (frame.empty()) {
        cout << "initTouchFromDisk: init image doesn't exist" << endl;
        exit(-1);
    }
    Rect2d boxp = getRectFromDisk();
    initTouch(boxp, frame);
}

void TouchTracker::initTouchIntoDisk(Mat frame)
{
    Rect2d boxp;
    boxp = selectROI(frame, false);
    destroyWindow("ROI selector");

    imwrite(INIT_PATH + "ppeb_track_" + handle + ".png", frame);
    QSettings *config = new QSettings(QString::fromStdString(INIT_PATH) + "ppeb_config.ini", QSettings::IniFormat);
    config->beginGroup(QString::fromStdString(handle));
    config->setValue("x", boxp.x);
    config->setValue("y", boxp.y);
    config->setValue("width", boxp.width);
    config->setValue("height", boxp.height);
    config->endGroup();

    initTouch(boxp, frame);
}

bool TouchTracker::checkTouch(Mat frame, bool verbose)
{
#ifdef TT_DEBUG
    double timer;
    if (verbose)
        timer = (double)getTickCount();
#endif

    Rect2d boxp;
    bool okp = trackerp->update(frame, boxp);

#ifdef TT_DEBUG
    float fps;
    if (verbose)
        fps = getTickFrequency() / ((double)getTickCount() - timer);
#endif

    if (okp) {
        // corner case: trackee get out of screen
        if (boxp.width + boxp.x >= frame.cols || boxp.height + boxp.y >= frame.rows)
            return false;

#ifdef TT_DEBUG
        if (verbose) {
            Point p1 = Point(boxp.x + boxp.width + offpx, boxp.y + boxp.height + offpy),
                  p2 = Point(boxp.x, p1.y - (boxp.width + offpx) * slope),
                  p3 = Point(boxp.x + expect, p2.y + expect * slope);
            rectangle(frame, boxp, Scalar( 255, 0, 0 ), 2, 1 );
            circle(frame, p1, 2, Scalar(0, 0, 255), 2);
            putText(frame, "FPS : " + SSTR(int(fps)), Point(50,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
            line(frame, p2, p3, CV_RGB(0, 255, 0), 2);
            line(frame, p3, p1, CV_RGB(255, 0, 0), 2);
        }
#endif
        Mat mat = Mat::Mat(frame, boxp);
        cvtColor(mat, mat, CV_BGR2GRAY);
        threshold(mat, mat, 0, 255, CV_THRESH_OTSU);
        float row = mat.rows + offpy - (mat.cols + offpx) * slope;

        for (int col = 0; col < expect; col++) {
            uchar *data = mat.ptr<uchar>((int)row);
            if (data[col] != 0)
                return false;
            row += slope;
        }
        return true;
    }

    return false;
}

/********************************************
 * Private part
 ********************************************/
Ptr<Tracker> TouchTracker::getTracker(int type)
{
    // Tracking pen                         |   Tracking shadow
    // #0 BOOSTING: 50fps and even better!  |   60fps and great!
    // #1 MIL: 10fps slow but good          |   10fps and might take the shadow away with pen
    // #2 KCF: 150fps but missing sometime  |   500fps and wrong
    // #3 TLD: 20fps and not so precise     |   50fps and a little inprecise
    // #4 MEDIANFLOW: 520fps and not good   |   fast but inprecise
    // #5 GOTURN : buggy and worthless

    // Create a tracker
    Ptr<Tracker> tracker;
    switch(type)
    {
    case 0:
        tracker = TrackerBoosting::create();
        break;
    case 1:
        tracker = TrackerMIL::create();
        break;
    case 2:
        tracker = TrackerKCF::create();
        break;
    case 3:
        tracker = TrackerTLD::create();
        break;
    case 4:
        tracker = TrackerMedianFlow::create();
        break;
    case 5:
        tracker = TrackerGOTURN::create();
        break;
    }
    return tracker;
}

void TouchTracker::findNib(Mat mat, int &x, int &y)
{
    for (int i = mat.cols - 1; i >= 0; i--)
    {
        for (int j = mat.rows - 1; j >= 0; j--)
        {
            if (mat.at<uchar>(j, i) == 0)
            {
                x = i - mat.cols;
                y = j - mat.rows;
                return;
            }
        }
    }
}

/********************************************
 * Deprecated part
 ********************************************/
#ifdef FF_DEPRECATED
void TouchTracker::initTouchOld(Mat frame)
{
    Rect2d boxp, boxs;
    Mat copy = frame.clone();
    boxp = selectROI(copy, false);
    rectangle(copy, boxp, Scalar(255, 0, 0), 2, 1 );
    boxs = selectROI(copy, false);
    rectangle(copy, boxs, Scalar(255, 0, 0), 2, 1 );
    destroyWindow("ROI selector");
    initTouchOld(boxp, boxs, frame);
}

void TouchTracker::initTouchOld(Rect2d boxp, Mat frame)
{
    Rect2d boxs;
    boxs = selectROI(frame, false);
    destroyWindow("ROI selector");
    initTouchOld(boxp, boxs, frame);
}

void TouchTracker::initTouchOld(Rect2d boxp, Rect2d boxs, Mat frame)
{
    trackerp = getTracker(TRACKER_TYPE);
    trackers = getTracker(TRACKER_TYPE);

    trackerp->init(frame, boxp);
    trackers->init(frame, boxs);

    Mat imgp = Mat::Mat(frame, boxp), imgs = Mat::Mat(frame, boxs);
    cvtColor(imgp, imgp, CV_BGR2GRAY);
    threshold(imgp, imgp, 0, 255, CV_THRESH_OTSU);
    findNib(imgp, offpx, offpy);
    //imwrite("E:/imgp.png", imgp);

    cvtColor(imgs, imgs, CV_BGR2GRAY);
    threshold(imgs, imgs, 0, 255, CV_THRESH_OTSU);
    findNib(imgs, offsx, offsy);
    //imwrite("E:/imgs.png", imgs);
}

bool TouchTracker::checkTouchOld(Mat frame, bool verbose)
{
#ifdef TT_DEBUG
    double timer;
    if (verbose)
        timer = (double)getTickCount();
#endif

    Rect2d boxp, boxs;
    bool okp = trackerp->update(frame, boxp),
         oks = trackers->update(frame, boxs);

#ifdef TT_DEBUG
    float fps;
    if (verbose)
        fps = getTickFrequency() / ((double)getTickCount() - timer);
#endif

    if (okp && oks) {
        Point p1 = Point(boxp.x + boxp.width + offpx, boxp.y + boxp.height + offpy),
              p2 = Point(boxs.x + boxs.width + offsx, boxs.y + boxs.height + offsy);

#ifdef TT_DEBUG
        if (verbose) {
            rectangle(frame, boxp, Scalar( 255, 0, 0 ), 2, 1 );
            rectangle(frame, boxs, Scalar( 255, 0, 0 ), 2, 1 );
            circle(frame, p1, 2, Scalar(0, 0, 255), 2);
            circle(frame, p2, 2, Scalar(0, 255, 0), 2);
            putText(frame, "FPS : " + SSTR(int(fps)), Point(50,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
        }
#endif

        if (p1.y - p2.y > DEVIATION)
            return true;
        else
            return false;
    }

    return false;
}

int TouchTracker::example()
{
    int type = TRACKER_TYPE;
    string trackerTypes[6] = {"BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN"};
    string trackerType = trackerTypes[type];
    Ptr<Tracker> tracker = getTracker(type);
#ifdef TRACK_TWO
    Ptr<Tracker> tracker1 = getTracker(type);
#endif
    // Read video
    VideoCapture video(VIDEO_IN + ".mp4");
    if(!video.isOpened()) {
        cout << "TouchTracker: could not locate video file "
             << VIDEO_IN + ".mp4"
             << ", check macro VIDEO_IN" << endl;
        return 1;
    }
#ifdef SAVE_VIDEO
    VideoWriter writer(VIDEO_IN + ".avi", CV_FOURCC('D', 'I', 'V', 'X'), 18.0,
                       Size(video.get(CV_CAP_PROP_FRAME_WIDTH), video.get(CV_CAP_PROP_FRAME_HEIGHT)));
#endif

    // Draw box
    Mat frame;
    bool ok = video.read(frame), ok1;

    Rect2d bbox0= selectROI(frame, false);
    rectangle(frame, bbox0, Scalar( 255, 0, 0 ), 2, 1 );
    if (bbox0.area() == 0)
        return 0;
    tracker->init(frame, bbox0);

#ifdef TRACK_TWO
    Rect2d bbox1(399, 125, 78, 32);// = selectROI(frame, false);
    rectangle(frame, bbox0, Scalar( 255, 0, 0 ), 2, 1 );
    if (bbox1.area() == 0)
        return 0;
    tracker1->init(frame, bbox1);
#endif

    int offset1x = -8, offset1y = -3,
        offset2x = -16, offset2y = -11;
    cout << endl;

    while(video.read(frame))
    {
        double timer = (double)getTickCount();
        ok = tracker->update(frame, bbox0);
#ifdef TRACK_TWO
        ok1 = tracker1->update(frame, bbox1);
#endif
        float fps = getTickFrequency() / ((double)getTickCount() - timer);

#ifdef TRACK_TWO
        if (ok && ok1) {
            rectangle(frame, bbox0, Scalar( 255, 0, 0 ), 2, 1 );
            rectangle(frame, bbox1, Scalar( 255, 0, 0 ), 2, 1 );

            Point p1 = Point(bbox0.x + bbox0.width + offset1x, bbox0.y + bbox0.height + offset1y),
                  p2 = Point(bbox1.x + bbox1.width + offset2x, bbox1.y + bbox1.height + offset2y);
            if (p1.y >= p2.y)
            {
                putText(frame, "Touching", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
            }
            else
            {
                putText(frame, QString::number(p1.y-p2.y).toStdString(), Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,255,0),2);
            }

            circle(frame, p1, 2, Scalar(0, 0, 255), 2);
            circle(frame, p2, 2, Scalar(0, 255, 0), 2);
        }
#else
        if (ok) {
            rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
        }
#endif
        else {
            putText(frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
        }

        putText(frame, trackerType + " Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
        putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
        imshow("Touch Tracking", frame);
#ifdef SAVE_VIDEO
        writer << frame;
#endif
        // Exit if ESC pressed.
        if(waitKey(1) == 27)
        {
            break;
        }
    }
    destroyWindow("Touch Tracking");
    return 0;
}
#endif
