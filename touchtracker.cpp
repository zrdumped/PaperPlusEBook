#include "touchtracker.h"

using namespace cv;
using namespace std;

#define VIDEO_IN string("E:/touch_test_realcut")
#define TRACKER_TYPE 0
#define TRACK_TWO
#define SAVE_VIDEO

// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

TouchTracker::TouchTracker()
{
}

Ptr<Tracker> TouchTracker::getTracker(int type)
{
    // Tracking pen                         |   Tracking shadow
    // #0 BOOSTING: 50fps and even better!  |   60fps and great!
    // #1 MIL: 10fps slow but good          |   10fps and might take the shadow away with pen
    // #2 KCF: 150fps but missing sometime  |   500fps and wrong
    // #3 TLD: 20fps and not so precise     |   50fps and a little inprecise
    // #4 MEDIANFLOW: 520fps and so great   |   fast but inprecise
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
        cout << "Could not read video file" << endl;
        return 1;
    }
#ifdef SAVE_VIDEO
    VideoWriter writer(VIDEO_IN + ".avi", CV_FOURCC('D', 'I', 'V', 'X'), 18.0,
                       Size(video.get(CV_CAP_PROP_FRAME_WIDTH), video.get(CV_CAP_PROP_FRAME_HEIGHT)));
#endif

    // Draw box
    Mat frame;
    bool ok = video.read(frame), ok1;

    //Rect2d bbox(415, 80, 54, 49);
    //Rect2d bbox1(399, 125, 78, 32);

    Rect2d bbox0(415, 80, 54, 49);// = selectROI(frame, false);
    rectangle(frame, bbox0, Scalar( 255, 0, 0 ), 2, 1 );
    std::cout << bbox0;
    if (bbox0.area() == 0)
        return 0;
    tracker->init(frame, bbox0);

#ifdef TRACK_TWO
    Rect2d bbox1(399, 125, 78, 32);// = selectROI(frame, false);
    rectangle(frame, bbox0, Scalar( 255, 0, 0 ), 2, 1 );
    std::cout << ", " << bbox1;
    if (bbox1.area() == 0)
        return 0;
    tracker1->init(frame, bbox1);
#endif

    int offset1x = -8, offset1y = -3,
        offset2x = -16, offset2y = -11;
    imshow("Tracking", frame);
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
        imshow("Tracking", frame);
#ifdef SAVE_VIDEO
        writer << frame;
#endif
        // Exit if ESC pressed.
        if(waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
