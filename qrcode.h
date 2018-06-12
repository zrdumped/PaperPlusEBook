/********************************************************
 * file: qrcode.h
 * Author: Vital
 * brief: QRCode-related functions based on <QZXing>
 ********************************************************/
#ifndef PB_QRCODE
#define PB_QRCODE

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QDebug>
#include <QZXing.h>

#define PROJECT_DIR QString("E:/V-Codes/PaperPlusEBook/")
#define TRY_HARDER

/********************************************************
 * Defination Part
 ********************************************************/
/**
 * @brief qrcode2int - Translate QRCode into an integer
 * @param image
 * @param ok
 * @return
 *   - on error, set 'ok' false, and return 0
 */
int qrcode2int(QImage image, bool *ok);

/**
 * @brief qrcode2int2
 *   - divide the givin image into two image according to the ratio and parse them into value
 * @param image
 * @param val1 - parse result 1
 * @param val2 - parse result 2
 * @param ratio
 * @param ok
 */
void qrcode2int2(QImage image, int *val1, int *val2, float ratio = 0.5f, bool *ok = NULL);

/**
 * @brief qrcode2string - Translate QRCode into a string
 * @param image
 * @return
 *   - on error, return ""
 */
QString qrcode2string(QImage image);

/**
 * @brief int2qrcode - Wrapper function for QZXing::encodeData
 * @param value
 * @return
 */
QImage int2qrcode(int value);

/**
 * @brief generateQRCodes - generate QRCodes from 1 to 'end' at 'D:/qrcodes/'
 * @param end
 */
void generateQRCodes(int end);

/**
 * @brief testQRCode - test code for this module
 * @param label
 */
void testQRCode(QLabel *label);

/**
 * @brief testQRCode2 - test qrcode2int2
 */
void testQRCode2();

/**
 * @brief testQRCode3 - test low contrast image (failed)
 */
void testQRCode3();

/********************************************************
 * Implementation Part
 ********************************************************/

static QZXing decoder;
static bool firsttime = true;

int qrcode2int(QImage image, bool *ok)
{
    if (firsttime) {
#ifdef TRY_HARDER
        decoder.setTryHarder(true);
#endif
        decoder.setDecoder( QZXing::DecoderFormat_QR_CODE);
        firsttime = false;
    }
    return decoder.decodeImage(image).toInt(ok, 10);
}

void qrcode2int2(QImage image, int *val1, int *val2, float ratio, bool *ok)
{
    int dividePos = ratio * image.width();
    bool ok1, ok2;
    QImage image1 = image.copy(0, 0, dividePos, image.height());
    QImage image2 = image.copy(dividePos, 0, image.width() - dividePos, image.height());

    *val1 = qrcode2int(image1, &ok1);
    *val2 = qrcode2int(image2, &ok2);
    if (ok)
        *ok = ok1 & ok2;
}

QString qrcode2string(QImage image)
{
    if (firsttime) {
#ifdef TRY_HARDER
        decoder.setTryHarder(true);
#endif
        decoder.setDecoder( QZXing::DecoderFormat_QR_CODE);
        firsttime = false;
    }
    return decoder.decodeImage(image);
}

QImage int2qrcode(int value)
{
    return QZXing::encodeData(QString::number(value, 10),
                              QZXing::EncoderFormat_QR_CODE,
                              QSize(240, 240),
                              QZXing::EncodeErrorCorrectionLevel_H);
}

void generateQRCodes(int end)
{
    for (int i = 1; i <= end; i++) {
        QImage image = int2qrcode(i);
        if (!image.save(QString("D:/qrcodes/qrcode-%1.png").arg(i)))
            qDebug() << "Saving error when i =" << i;
    }
    qDebug()<<"Generating QRCodes Complete (pages 1-" << end << ")";
}

void testQRCode(QLabel *label)
{
    QImage imageToDecode(PROJECT_DIR + "resources/qrcode/easy.png");
    bool ok;
    qDebug() << "Web Address Test: " << qrcode2string(imageToDecode);

    QImage qrcode = int2qrcode(85);
    qDebug() << "Test basic: " << qrcode2int(qrcode, &ok);

    qrcode = qrcode.scaled(label->geometry().height(), label->geometry().height(),
                           Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(QPixmap::fromImage(qrcode));
}

void testQRCode2()
{
    QImage image(PROJECT_DIR + "resources/qrcode/2qrcodes.png");
    int val1, val2;
    int expect1 = 1, expect2 = 2;
    qrcode2int2(image, &val1, &val2, 0.5f);
    bool pass = val1==expect1 && val2==expect2;
    qDebug() << "Test qrcode2int2(): " << (pass?"pass":"fail");
    qDebug() << "\t[expect] " << expect1 << ", "<<expect2;
    qDebug() << "\t[get]    " << val1 << ", " << val2;
}

void testQRCode3()
{
    QImage image1(PROJECT_DIR + "resources/qrcode/blackAndWhite.png");
    QImage image2(PROJECT_DIR + "resources/qrcode/easy.png");
    qDebug() << "low-contrast test: " << qrcode2string(image1);
    qDebug() << "low-contrast test: " << qrcode2string(image2);
}
#endif
