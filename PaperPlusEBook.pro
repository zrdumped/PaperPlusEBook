#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T18:43:03
#
#-------------------------------------------------
#DEFINES += CWTWINDOWS
#DEFINES += ZRWINDOWS
DEFINES += TZYMACOSX
include(qzxing/QZXing.pri)

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaperPlusEBook
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
#    qzxing/zxing/bigint/BigInteger.cc \
#    qzxing/zxing/bigint/BigIntegerAlgorithms.cc \
#    qzxing/zxing/bigint/BigIntegerUtils.cc \
#    qzxing/zxing/bigint/BigUnsigned.cc \
#    qzxing/zxing/bigint/BigUnsignedInABase.cc \
#    qzxing/zxing/zxing/aztec/decoder/AztecDecoder.cpp \
#    qzxing/zxing/zxing/aztec/detector/AztecDetector.cpp \
#    qzxing/zxing/zxing/aztec/AztecDetectorResult.cpp \
#    qzxing/zxing/zxing/aztec/AztecReader.cpp \
#    qzxing/zxing/zxing/common/detector/MonochromeRectangleDetector.cpp \
#    qzxing/zxing/zxing/common/detector/WhiteRectangleDetector.cpp \
#    qzxing/zxing/zxing/common/reedsolomon/GenericGF.cpp \
#    qzxing/zxing/zxing/common/reedsolomon/GenericGFPoly.cpp \
#    qzxing/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
#    qzxing/zxing/zxing/common/reedsolomon/ReedSolomonEncoder.cpp \
#    qzxing/zxing/zxing/common/reedsolomon/ReedSolomonException.cpp \
#    qzxing/zxing/zxing/common/BitArray.cpp \
#    qzxing/zxing/zxing/common/BitArrayIO.cpp \
#    qzxing/zxing/zxing/common/BitMatrix.cpp \
#    qzxing/zxing/zxing/common/BitSource.cpp \
#    qzxing/zxing/zxing/common/CharacterSetECI.cpp \
#    qzxing/zxing/zxing/common/DecoderResult.cpp \
#    qzxing/zxing/zxing/common/DetectorResult.cpp \
#    qzxing/zxing/zxing/common/GlobalHistogramBinarizer.cpp \
#    qzxing/zxing/zxing/common/GreyscaleLuminanceSource.cpp \
#    qzxing/zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
#    qzxing/zxing/zxing/common/GridSampler.cpp \
#    qzxing/zxing/zxing/common/HybridBinarizer.cpp \
#    qzxing/zxing/zxing/common/IllegalArgumentException.cpp \
#    qzxing/zxing/zxing/common/PerspectiveTransform.cpp \
#    qzxing/zxing/zxing/common/Str.cpp \
#    qzxing/zxing/zxing/common/StringUtils.cpp \
#    qzxing/zxing/zxing/datamatrix/decoder/DataMatrixBitMatrixParser.cpp \
#    qzxing/zxing/zxing/datamatrix/decoder/DataMatrixDataBlock.cpp \
#    qzxing/zxing/zxing/datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp \
#    qzxing/zxing/zxing/datamatrix/decoder/DataMatrixDecoder.cpp \
#    qzxing/zxing/zxing/datamatrix/detector/DataMatrixCornerPoint.cpp \
#    qzxing/zxing/zxing/datamatrix/detector/DataMatrixDetector.cpp \
#    qzxing/zxing/zxing/datamatrix/detector/DataMatrixDetectorException.cpp \
#    qzxing/zxing/zxing/datamatrix/DataMatrixReader.cpp \
#    qzxing/zxing/zxing/datamatrix/DataMatrixVersion.cpp \
#    qzxing/zxing/zxing/multi/qrcode/detector/MultiDetector.cpp \
#    qzxing/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp \
#    qzxing/zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp \
#    qzxing/zxing/zxing/multi/ByQuadrantReader.cpp \
#    qzxing/zxing/zxing/multi/GenericMultipleBarcodeReader.cpp \
#    qzxing/zxing/zxing/multi/MultipleBarcodeReader.cpp \
#    qzxing/zxing/zxing/oned/CodaBarReader.cpp \
#    qzxing/zxing/zxing/oned/Code128Reader.cpp \
#    qzxing/zxing/zxing/oned/Code39Reader.cpp \
#    qzxing/zxing/zxing/oned/Code93Reader.cpp \
#    qzxing/zxing/zxing/oned/EAN13Reader.cpp \
#    qzxing/zxing/zxing/oned/EAN8Reader.cpp \
#    qzxing/zxing/zxing/oned/ITFReader.cpp \
#    qzxing/zxing/zxing/oned/MultiFormatOneDReader.cpp \
#    qzxing/zxing/zxing/oned/MultiFormatUPCEANReader.cpp \
#    qzxing/zxing/zxing/oned/OneDReader.cpp \
#    qzxing/zxing/zxing/oned/OneDResultPoint.cpp \
#    qzxing/zxing/zxing/oned/UPCAReader.cpp \
#    qzxing/zxing/zxing/oned/UPCEANReader.cpp \
#    qzxing/zxing/zxing/oned/UPCEReader.cpp \
#    qzxing/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.cpp \
#    qzxing/zxing/zxing/pdf417/decoder/ec/ModulusGF.cpp \
#    qzxing/zxing/zxing/pdf417/decoder/ec/ModulusPoly.cpp \
#    qzxing/zxing/zxing/pdf417/decoder/PDF417BitMatrixParser.cpp \
#    qzxing/zxing/zxing/pdf417/decoder/PDF417DecodedBitStreamParser.cpp \
#    qzxing/zxing/zxing/pdf417/decoder/PDF417Decoder.cpp \
#    qzxing/zxing/zxing/pdf417/detector/LinesSampler.cpp \
#    qzxing/zxing/zxing/pdf417/detector/PDF417Detector.cpp \
#    qzxing/zxing/zxing/pdf417/PDF417Reader.cpp \
#    qzxing/zxing/zxing/qrcode/decoder/QRBitMatrixParser.cpp \
#    qzxing/zxing/zxing/qrcode/decoder/QRDataBlock.cpp \
#    qzxing/zxing/zxing/qrcode/decoder/QRDataMask.cpp \
#    qzxing/zxing/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp \
#    qzxing/zxing/zxing/qrcode/decoder/QRDecoder.cpp \
#    qzxing/zxing/zxing/qrcode/decoder/QRMode.cpp \
#    qzxing/zxing/zxing/qrcode/detector/QRAlignmentPattern.cpp \
#    qzxing/zxing/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp \
#    qzxing/zxing/zxing/qrcode/detector/QRDetector.cpp \
#    qzxing/zxing/zxing/qrcode/detector/QRFinderPattern.cpp \
#    qzxing/zxing/zxing/qrcode/detector/QRFinderPatternFinder.cpp \
#    qzxing/zxing/zxing/qrcode/detector/QRFinderPatternInfo.cpp \
#    qzxing/zxing/zxing/qrcode/encoder/ByteMatrix.cpp \
#    qzxing/zxing/zxing/qrcode/encoder/MaskUtil.cpp \
#    qzxing/zxing/zxing/qrcode/encoder/MatrixUtil.cpp \
#    qzxing/zxing/zxing/qrcode/encoder/QRCode.cpp \
#    qzxing/zxing/zxing/qrcode/encoder/QREncoder.cpp \
#    qzxing/zxing/zxing/qrcode/QRCodeReader.cpp \
#    qzxing/zxing/zxing/qrcode/QRErrorCorrectionLevel.cpp \
#    qzxing/zxing/zxing/qrcode/QRFormatInformation.cpp \
#    qzxing/zxing/zxing/qrcode/QRVersion.cpp \
#    qzxing/zxing/zxing/BarcodeFormat.cpp \
#    qzxing/zxing/zxing/Binarizer.cpp \
#    qzxing/zxing/zxing/BinaryBitmap.cpp \
#    qzxing/zxing/zxing/ChecksumException.cpp \
#    qzxing/zxing/zxing/DecodeHints.cpp \
#    qzxing/zxing/zxing/EncodeHint.cpp \
#    qzxing/zxing/zxing/Exception.cpp \
#    qzxing/zxing/zxing/FormatException.cpp \
#    qzxing/zxing/zxing/InvertedLuminanceSource.cpp \
#    qzxing/zxing/zxing/LuminanceSource.cpp \
#    qzxing/zxing/zxing/MultiFormatReader.cpp \
#    qzxing/zxing/zxing/Reader.cpp \
#    qzxing/zxing/zxing/Result.cpp \
#    qzxing/zxing/zxing/ResultIO.cpp \
#    qzxing/zxing/zxing/ResultPoint.cpp \
#    qzxing/zxing/zxing/ResultPointCallback.cpp \
#    qzxing/CameraImageWrapper.cpp \
#    qzxing/ImageHandler.cpp \
#    qzxing/QZXing.cpp \
#    qzxing/QZXingFilter.cpp \
#    qzxing/QZXingImageProvider.cpp \
#    qzxing/zxing/win32/zxing/win_iconv.c \



HEADERS += \
        mainwindow.h    \
#    qrcode.h \
#    qzxing/zxing/bigint/BigInteger.hh \
#    qzxing/zxing/bigint/BigIntegerAlgorithms.hh \
#    qzxing/zxing/bigint/BigIntegerLibrary.hh \
#    qzxing/zxing/bigint/BigIntegerUtils.hh \
#    qzxing/zxing/bigint/BigUnsigned.hh \
#    qzxing/zxing/bigint/BigUnsignedInABase.hh \
#    qzxing/zxing/bigint/NumberlikeArray.hh \
#    qzxing/zxing/win32/zxing/msvc/stdint.h \
#    qzxing/zxing/win32/zxing/iconv.h \
#    qzxing/zxing/zxing/aztec/decoder/Decoder.h \
#    qzxing/zxing/zxing/aztec/detector/Detector.h \
#    qzxing/zxing/zxing/aztec/AztecDetectorResult.h \
#    qzxing/zxing/zxing/aztec/AztecReader.h \
#    qzxing/zxing/zxing/common/detector/JavaMath.h \
#    qzxing/zxing/zxing/common/detector/MathUtils.h \
#    qzxing/zxing/zxing/common/detector/MonochromeRectangleDetector.h \
#    qzxing/zxing/zxing/common/detector/WhiteRectangleDetector.h \
#    qzxing/zxing/zxing/common/reedsolomon/GenericGF.h \
#    qzxing/zxing/zxing/common/reedsolomon/GenericGFPoly.h \
#    qzxing/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.h \
#    qzxing/zxing/zxing/common/reedsolomon/ReedSolomonEncoder.h \
#    qzxing/zxing/zxing/common/reedsolomon/ReedSolomonException.h \
#    qzxing/zxing/zxing/common/Array.h \
#    qzxing/zxing/zxing/common/BitArray.h \
#    qzxing/zxing/zxing/common/BitMatrix.h \
#    qzxing/zxing/zxing/common/BitSource.h \
#    qzxing/zxing/zxing/common/CharacterSetECI.h \
#    qzxing/zxing/zxing/common/Counted.h \
#    qzxing/zxing/zxing/common/DecoderResult.h \
#    qzxing/zxing/zxing/common/DetectorResult.h \
#    qzxing/zxing/zxing/common/GlobalHistogramBinarizer.h \
#    qzxing/zxing/zxing/common/GreyscaleLuminanceSource.h \
#    qzxing/zxing/zxing/common/GreyscaleRotatedLuminanceSource.h \
#    qzxing/zxing/zxing/common/GridSampler.h \
#    qzxing/zxing/zxing/common/HybridBinarizer.h \
#    qzxing/zxing/zxing/common/IllegalArgumentException.h \
#    qzxing/zxing/zxing/common/PerspectiveTransform.h \
#    qzxing/zxing/zxing/common/Point.h \
#    qzxing/zxing/zxing/common/Str.h \
#    qzxing/zxing/zxing/common/StringUtils.h \
#    qzxing/zxing/zxing/common/Types.h \
#    qzxing/zxing/zxing/datamatrix/decoder/BitMatrixParser.h \
#    qzxing/zxing/zxing/datamatrix/decoder/DataBlock.h \
#    qzxing/zxing/zxing/datamatrix/decoder/DecodedBitStreamParser.h \
#    qzxing/zxing/zxing/datamatrix/decoder/Decoder.h \
#    qzxing/zxing/zxing/datamatrix/detector/CornerPoint.h \
#    qzxing/zxing/zxing/datamatrix/detector/Detector.h \
#    qzxing/zxing/zxing/datamatrix/detector/DetectorException.h \
#    qzxing/zxing/zxing/datamatrix/DataMatrixReader.h \
#    qzxing/zxing/zxing/datamatrix/Version.h \
#    qzxing/zxing/zxing/multi/qrcode/detector/MultiDetector.h \
#    qzxing/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h \
#    qzxing/zxing/zxing/multi/qrcode/QRCodeMultiReader.h \
#    qzxing/zxing/zxing/multi/ByQuadrantReader.h \
#    qzxing/zxing/zxing/multi/GenericMultipleBarcodeReader.h \
#    qzxing/zxing/zxing/multi/MultipleBarcodeReader.h \
#    qzxing/zxing/zxing/oned/CodaBarReader.h \
#    qzxing/zxing/zxing/oned/Code128Reader.h \
#    qzxing/zxing/zxing/oned/Code39Reader.h \
#    qzxing/zxing/zxing/oned/Code93Reader.h \
#    qzxing/zxing/zxing/oned/EAN13Reader.h \
#    qzxing/zxing/zxing/oned/EAN8Reader.h \
#    qzxing/zxing/zxing/oned/ITFReader.h \
#    qzxing/zxing/zxing/oned/MultiFormatOneDReader.h \
#    qzxing/zxing/zxing/oned/MultiFormatUPCEANReader.h \
#    qzxing/zxing/zxing/oned/OneDReader.h \
#    qzxing/zxing/zxing/oned/OneDResultPoint.h \
#    qzxing/zxing/zxing/oned/UPCAReader.h \
#    qzxing/zxing/zxing/oned/UPCEANReader.h \
#    qzxing/zxing/zxing/oned/UPCEReader.h \
#    qzxing/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.h \
#    qzxing/zxing/zxing/pdf417/decoder/ec/ModulusGF.h \
#    qzxing/zxing/zxing/pdf417/decoder/ec/ModulusPoly.h \
#    qzxing/zxing/zxing/pdf417/decoder/BitMatrixParser.h \
#    qzxing/zxing/zxing/pdf417/decoder/DecodedBitStreamParser.h \
#    qzxing/zxing/zxing/pdf417/decoder/Decoder.h \
#    qzxing/zxing/zxing/pdf417/detector/Detector.h \
#    qzxing/zxing/zxing/pdf417/detector/LinesSampler.h \
#    qzxing/zxing/zxing/pdf417/PDF417Reader.h \
#    qzxing/zxing/zxing/qrcode/decoder/BitMatrixParser.h \
#    qzxing/zxing/zxing/qrcode/decoder/DataBlock.h \
#    qzxing/zxing/zxing/qrcode/decoder/DataMask.h \
#    qzxing/zxing/zxing/qrcode/decoder/DecodedBitStreamParser.h \
#    qzxing/zxing/zxing/qrcode/decoder/Decoder.h \
#    qzxing/zxing/zxing/qrcode/decoder/Mode.h \
#    qzxing/zxing/zxing/qrcode/detector/AlignmentPattern.h \
#    qzxing/zxing/zxing/qrcode/detector/AlignmentPatternFinder.h \
#    qzxing/zxing/zxing/qrcode/detector/Detector.h \
#    qzxing/zxing/zxing/qrcode/detector/FinderPattern.h \
#    qzxing/zxing/zxing/qrcode/detector/FinderPatternFinder.h \
#    qzxing/zxing/zxing/qrcode/detector/FinderPatternInfo.h \
#    qzxing/zxing/zxing/qrcode/encoder/BlockPair.h \
#    qzxing/zxing/zxing/qrcode/encoder/ByteMatrix.h \
#    qzxing/zxing/zxing/qrcode/encoder/Encoder.h \
#    qzxing/zxing/zxing/qrcode/encoder/MaskUtil.h \
#    qzxing/zxing/zxing/qrcode/encoder/MatrixUtil.h \
#    qzxing/zxing/zxing/qrcode/encoder/QRCode.h \
#    qzxing/zxing/zxing/qrcode/ErrorCorrectionLevel.h \
#    qzxing/zxing/zxing/qrcode/FormatInformation.h \
#    qzxing/zxing/zxing/qrcode/QRCodeReader.h \
#    qzxing/zxing/zxing/qrcode/Version.h \
#    qzxing/zxing/zxing/BarcodeFormat.h \
#    qzxing/zxing/zxing/Binarizer.h \
#    qzxing/zxing/zxing/BinaryBitmap.h \
#    qzxing/zxing/zxing/ChecksumException.h \
#    qzxing/zxing/zxing/DecodeHints.h \
#    qzxing/zxing/zxing/EncodeHint.h \
#    qzxing/zxing/zxing/Exception.h \
#    qzxing/zxing/zxing/FormatException.h \
#    qzxing/zxing/zxing/IllegalStateException.h \
#    qzxing/zxing/zxing/InvertedLuminanceSource.h \
#    qzxing/zxing/zxing/LuminanceSource.h \
#    qzxing/zxing/zxing/MultiFormatReader.h \
#    qzxing/zxing/zxing/NotFoundException.h \
#    qzxing/zxing/zxing/Reader.h \
#    qzxing/zxing/zxing/ReaderException.h \
#    qzxing/zxing/zxing/Result.h \
#    qzxing/zxing/zxing/ResultPoint.h \
#    qzxing/zxing/zxing/ResultPointCallback.h \
#    qzxing/zxing/zxing/UnsupportedEncodingException.h \
#    qzxing/zxing/zxing/WriterException.h \
#    qzxing/zxing/zxing/ZXing.h \
#    qzxing/CameraImageWrapper.h \
#    qzxing/ImageHandler.h \
#    qzxing/QZXing.h \
#    qzxing/QZXing_global.h \
#    qzxing/QZXingFilter.h \
#    qzxing/QZXingImageProvider.h \
    poppler-qt5/qt5/src/ArthurOutputDev.h \
    poppler-qt5/qt5/src/poppler-annotation-helper.h \
    poppler-qt5/qt5/src/poppler-annotation-private.h \
    poppler-qt5/qt5/src/poppler-annotation.h \
    poppler-qt5/qt5/src/poppler-converter-private.h \
    poppler-qt5/qt5/src/poppler-embeddedfile-private.h \
    poppler-qt5/qt5/src/poppler-export.h \
    poppler-qt5/qt5/src/poppler-form.h \
    poppler-qt5/qt5/src/poppler-link-extractor-private.h \
    poppler-qt5/qt5/src/poppler-link-private.h \
    poppler-qt5/qt5/src/poppler-link.h \
    poppler-qt5/qt5/src/poppler-media.h \
    poppler-qt5/qt5/src/poppler-optcontent-private.h \
    poppler-qt5/qt5/src/poppler-optcontent.h \
    poppler-qt5/qt5/src/poppler-page-private.h \
    poppler-qt5/qt5/src/poppler-page-transition-private.h \
    poppler-qt5/qt5/src/poppler-page-transition.h \
    poppler-qt5/qt5/src/poppler-private.h \
    poppler-qt5/qt5/src/poppler-qiodeviceoutstream-private.h \
    poppler-qt5/qt5/src/poppler-qt5.h \
    poppler-qt5/qt5/src/config.h

FORMS += \
        mainwindow.ui
if(contains(DEFINES, CWTWINDOWS)){
INCLUDEPATH += \
        E:/develop/opencv/build/include \
        E:/develop/opencv/build/include\opencv  \
        E:/develop/opencv/build/include\opencv2

LIBS += E:/develop/opencv/build/x64/vc15/lib/opencv_world341.lib \
        E:/develop/opencv/build/x64/vc15/lib/opencv_world341d.lib
}
else{
if(contains(DEFINES, ZRWINDOWS)){

}
else{
if(contains(DEFINES, TZYMACOSX)){
SOURCES +=     \
    poppler-qt5/qt5/src/ArthurOutputDev.cc \
    poppler-qt5/qt5/src/poppler-annotation.cc \
    poppler-qt5/qt5/src/poppler-base-converter.cc \
    poppler-qt5/qt5/src/poppler-document.cc \
    poppler-qt5/qt5/src/poppler-embeddedfile.cc \
    poppler-qt5/qt5/src/poppler-fontinfo.cc \
    poppler-qt5/qt5/src/poppler-form.cc \
    poppler-qt5/qt5/src/poppler-link-extractor.cc \
    poppler-qt5/qt5/src/poppler-link.cc \
    poppler-qt5/qt5/src/poppler-media.cc \
    poppler-qt5/qt5/src/poppler-movie.cc \
    poppler-qt5/qt5/src/poppler-optcontent.cc \
    poppler-qt5/qt5/src/poppler-page-transition.cc \
    poppler-qt5/qt5/src/poppler-page.cc \
    poppler-qt5/qt5/src/poppler-pdf-converter.cc \
    poppler-qt5/qt5/src/poppler-private.cc \
    poppler-qt5/qt5/src/poppler-ps-converter.cc \
    poppler-qt5/qt5/src/poppler-qiodeviceoutstream.cc \
    poppler-qt5/qt5/src/poppler-sound.cc \
    poppler-qt5/qt5/src/poppler-textbox.cc



INCLUDEPATH += \
            /usr/local/include \
             /usr/local/include/opencv2 \
            /usr/local/include/poppler  \
            poppler-qt5/qt5/src
#            /usr/local/Cellar/glib/2.56.1/include/glib-2.0  \
#            /usr/local/Cellar/glib/2.56.1/lib/glib-2.0/include  \
#            /usr/local/Cellar/cairo/1.14.12/include/cairo   \
#            /usr/local/Cellar/nspr/4.19/include/nspr    \
#            /usr/local/Cellar/nspr/4.19/include/nspr/md    \
#            /usr/local/Cellar/nspr/4.19/include/nspr/obsolete    \
#            /usr/local/Cellar/nss/3.36.1/include/nss

LIBS +=         \
            -L/usr/local/lib -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs \
            -L /usr/local/Cellar/little-cms2/2.9/lib -llcms2.2  \
            -L/usr/local/lib -lpoppler -lpoppler-cpp -lpoppler-glib  \
            -L/System/Library/Frameworks/ImageIO.framework/Versions/A/Resources -lJPEG \

#            -L/usr/local/Cellar/nspr/4.19/lib -lnspr4   \
#            -L/usr/local/Cellar/nss/3.36.1/lib -lnss3



}

}
}

DISTFILES += \
    poppler-qt5/glib/poppler.gidl \
    poppler-qt5/utils/pdf2xml.dtd \
    poppler-qt5/cpp/Doxyfile \
    poppler-qt5/cpp/Mainpage.dox \
    poppler-qt5/qt5/src/Doxyfile \
    poppler-qt5/utils/pdftocairo.1 \
    poppler-qt5/utils/pdftohtml.1 \
    poppler-qt5/utils/pdfdetach.1 \
    poppler-qt5/utils/pdffonts.1 \
    poppler-qt5/utils/pdfimages.1 \
    poppler-qt5/utils/pdfinfo.1 \
    poppler-qt5/utils/pdfseparate.1 \
    poppler-qt5/utils/pdfsig.1 \
    poppler-qt5/utils/pdftoppm.1 \
    poppler-qt5/utils/pdftops.1 \
    poppler-qt5/utils/pdftotext.1 \
    poppler-qt5/utils/pdfunite.1 \
    poppler-qt5/glib/poppler-features.h.cmake \
    poppler-qt5/poppler/poppler-config.h.cmake \
    poppler-qt5/cpp/CMakeLists.txt \
    poppler-qt5/glib/CMakeLists.txt \
    poppler-qt5/qt5/src/CMakeLists.txt \
    poppler-qt5/utils/CMakeLists.txt \
    poppler-qt5/poppler/gen-unicode-tables.py



