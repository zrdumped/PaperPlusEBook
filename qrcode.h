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
inline int qrcode2int(QImage image, bool *ok);

/**
 * @brief qrcode2string - Translate QRCode into a string
 * @param image
 * @return
 *   - on error, return ""
 */
inline QString qrcode2string(QImage image);

/**
 * @brief int2qrcode - Wrapper function for QZXing::encodeData
 * @param value
 * @return
 */
inline QImage int2qrcode(int value);

/**
 * @brief testQRCode - test code for this module
 * @param label
 */
void testQRCode(QLabel *label);

/**
 * @brief generateQRCodes - generate QRCodes from 1 to 'end' at 'D:/qrcodes/'
 * @param end
 */
void generateQRCodes(int end);

/********************************************************
 * Implementation Part
 ********************************************************/
static QZXing decoder;

inline int qrcode2int(QImage image, bool *ok)
{
    /* This line should work, but somehow error, so comment it for now */
    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_EAN_13 );
    return decoder.decodeImage(image).toInt(ok, 10);
}

inline QString qrcode2string(QImage image)
{
    return decoder.decodeImage(image);
}

inline QImage int2qrcode(int value)
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
    QImage imageToDecode("E:/V-Codes/QRCodeModule/qrcode-test1.png");
    bool ok;
    qDebug() << "Web Address Test: " << qrcode2string(imageToDecode);

    QImage qrcode = int2qrcode(85);
    qDebug() << "Number Test: " << qrcode2int(qrcode, &ok);

    qrcode = qrcode.scaled(label->geometry().height(), label->geometry().height(),
                           Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(QPixmap::fromImage(qrcode));
}

#endif

