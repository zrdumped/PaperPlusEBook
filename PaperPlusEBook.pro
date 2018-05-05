#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T18:43:03
#
#-------------------------------------------------
#DEFINES += CWTWINDOWS
#DEFINES += ZRWINDOWS
DEFINES += TZYMACOSX
include(qzxing/QZXing.pri)

QT       += core gui

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
#    poppler-qt5/cpp/poppler-document.cpp \
#    poppler-qt5/cpp/poppler-embedded-file.cpp \
#    poppler-qt5/cpp/poppler-font.cpp \
#    poppler-qt5/cpp/poppler-global.cpp \
#    poppler-qt5/cpp/poppler-image.cpp \
#    poppler-qt5/cpp/poppler-page-renderer.cpp \
#    poppler-qt5/cpp/poppler-page-transition.cpp \
#    poppler-qt5/cpp/poppler-page.cpp \
#    poppler-qt5/cpp/poppler-private.cpp \
#    poppler-qt5/cpp/poppler-rectangle.cpp \
#    poppler-qt5/cpp/poppler-toc.cpp \
#    poppler-qt5/cpp/poppler-version.cpp \
#    poppler-qt5/fofi/FoFiBase.cc \
#    poppler-qt5/fofi/FoFiEncodings.cc \
#    poppler-qt5/fofi/FoFiIdentifier.cc \
#    poppler-qt5/fofi/FoFiTrueType.cc \
#    poppler-qt5/fofi/FoFiType1.cc \
#    poppler-qt5/fofi/FoFiType1C.cc \
#    poppler-qt5/glib/poppler-action.cc \
#    poppler-qt5/glib/poppler-annot.cc \
#    poppler-qt5/glib/poppler-attachment.cc \
#    poppler-qt5/glib/poppler-cached-file-loader.cc \
#    poppler-qt5/glib/poppler-date.cc \
#    poppler-qt5/glib/poppler-document.cc \
#    poppler-qt5/glib/poppler-form-field.cc \
#    poppler-qt5/glib/poppler-input-stream.cc \
#    poppler-qt5/glib/poppler-layer.cc \
#    poppler-qt5/glib/poppler-media.cc \
#    poppler-qt5/glib/poppler-movie.cc \
#    poppler-qt5/glib/poppler-page.cc \
#    poppler-qt5/glib/poppler-structure-element.cc \
#    poppler-qt5/glib/poppler.cc \
#    poppler-qt5/goo/FixedPoint.cc \
#    poppler-qt5/goo/gfile.cc \
#    poppler-qt5/goo/glibc.cc \
#    poppler-qt5/goo/glibc_strtok_r.cc \
#    poppler-qt5/goo/gmem.cc \
#    poppler-qt5/goo/gmempp.cc \
#    poppler-qt5/goo/GooHash.cc \
#    poppler-qt5/goo/GooList.cc \
#    poppler-qt5/goo/GooString.cc \
#    poppler-qt5/goo/GooTimer.cc \
#    poppler-qt5/goo/grandom.cc \
#    poppler-qt5/goo/gstrtod.cc \
#    poppler-qt5/goo/ImgWriter.cc \
#    poppler-qt5/goo/JpegWriter.cc \
#    poppler-qt5/goo/NetPBMWriter.cc \
#    poppler-qt5/goo/PNGWriter.cc \
#    poppler-qt5/goo/TiffWriter.cc \
#    poppler-qt5/poppler/Annot.cc \
#    poppler-qt5/poppler/Array.cc \
#    poppler-qt5/poppler/BuiltinFont.cc \
#    poppler-qt5/poppler/BuiltinFontTables.cc \
#    poppler-qt5/poppler/CachedFile.cc \
#    poppler-qt5/poppler/CairoFontEngine.cc \
#    poppler-qt5/poppler/CairoOutputDev.cc \
#    poppler-qt5/poppler/CairoRescaleBox.cc \
#    poppler-qt5/poppler/Catalog.cc \
#    poppler-qt5/poppler/CharCodeToUnicode.cc \
#    poppler-qt5/poppler/CMap.cc \
#    poppler-qt5/poppler/CurlCachedFile.cc \
#    poppler-qt5/poppler/CurlPDFDocBuilder.cc \
#    poppler-qt5/poppler/DateInfo.cc \
#    poppler-qt5/poppler/DCTStream.cc \
#    poppler-qt5/poppler/Decrypt.cc \
#    poppler-qt5/poppler/Dict.cc \
#    poppler-qt5/poppler/Error.cc \
#    poppler-qt5/poppler/FileSpec.cc \
#    poppler-qt5/poppler/FlateEncoder.cc \
#    poppler-qt5/poppler/FlateStream.cc \
#    poppler-qt5/poppler/FontEncodingTables.cc \
#    poppler-qt5/poppler/FontInfo.cc \
#    poppler-qt5/poppler/Form.cc \
#    poppler-qt5/poppler/Function.cc \
#    poppler-qt5/poppler/Gfx.cc \
#    poppler-qt5/poppler/GfxFont.cc \
#    poppler-qt5/poppler/GfxState.cc \
#    poppler-qt5/poppler/GlobalParams.cc \
#    poppler-qt5/poppler/GlobalParamsWin.cc \
#    poppler-qt5/poppler/Hints.cc \
#    poppler-qt5/poppler/JArithmeticDecoder.cc \
#    poppler-qt5/poppler/JBIG2Stream.cc \
#    poppler-qt5/poppler/JPEG2000Stream.cc \
#    poppler-qt5/poppler/JPXStream.cc \
#    poppler-qt5/poppler/Lexer.cc \
#    poppler-qt5/poppler/Linearization.cc \
#    poppler-qt5/poppler/Link.cc \
#    poppler-qt5/poppler/LocalPDFDocBuilder.cc \
#    poppler-qt5/poppler/MarkedContentOutputDev.cc \
#    poppler-qt5/poppler/Movie.cc \
#    poppler-qt5/poppler/NameToCharCode.cc \
#    poppler-qt5/poppler/Object.cc \
#    poppler-qt5/poppler/OptionalContent.cc \
#    poppler-qt5/poppler/Outline.cc \
#    poppler-qt5/poppler/OutputDev.cc \
#    poppler-qt5/poppler/Page.cc \
#    poppler-qt5/poppler/PageLabelInfo.cc \
#    poppler-qt5/poppler/PageTransition.cc \
#    poppler-qt5/poppler/Parser.cc \
#    poppler-qt5/poppler/PDFDoc.cc \
#    poppler-qt5/poppler/PDFDocEncoding.cc \
#    poppler-qt5/poppler/PDFDocFactory.cc \
#    poppler-qt5/poppler/PopplerCache.cc \
#    poppler-qt5/poppler/PreScanOutputDev.cc \
#    poppler-qt5/poppler/ProfileData.cc \
#    poppler-qt5/poppler/PSOutputDev.cc \
#    poppler-qt5/poppler/PSTokenizer.cc \
#    poppler-qt5/poppler/Rendition.cc \
#    poppler-qt5/poppler/SecurityHandler.cc \
#    poppler-qt5/poppler/SignatureHandler.cc \
#    poppler-qt5/poppler/SignatureInfo.cc \
#    poppler-qt5/poppler/Sound.cc \
#    poppler-qt5/poppler/SplashOutputDev.cc \
#    poppler-qt5/poppler/StdinCachedFile.cc \
#    poppler-qt5/poppler/StdinPDFDocBuilder.cc \
#    poppler-qt5/poppler/Stream.cc \
#    poppler-qt5/poppler/StructElement.cc \
#    poppler-qt5/poppler/StructTreeRoot.cc \
#    poppler-qt5/poppler/TextOutputDev.cc \
#    poppler-qt5/poppler/UnicodeMap.cc \
#    poppler-qt5/poppler/UnicodeMapFuncs.cc \
#    poppler-qt5/poppler/UnicodeTypeTable.cc \
#    poppler-qt5/poppler/UTF.cc \
#    poppler-qt5/poppler/ViewerPreferences.cc \
#    poppler-qt5/poppler/XpdfPluginAPI.cc \
#    poppler-qt5/poppler/XRef.cc \
#    poppler-qt5/qt5/src/ArthurOutputDev.cc \
#    poppler-qt5/qt5/src/poppler-annotation.cc \
#    poppler-qt5/qt5/src/poppler-base-converter.cc \
#    poppler-qt5/qt5/src/poppler-document.cc \
#    poppler-qt5/qt5/src/poppler-embeddedfile.cc \
#    poppler-qt5/qt5/src/poppler-fontinfo.cc \
#    poppler-qt5/qt5/src/poppler-form.cc \
#    poppler-qt5/qt5/src/poppler-link-extractor.cc \
#    poppler-qt5/qt5/src/poppler-link.cc \
#    poppler-qt5/qt5/src/poppler-media.cc \
#    poppler-qt5/qt5/src/poppler-movie.cc \
#    poppler-qt5/qt5/src/poppler-optcontent.cc \
#    poppler-qt5/qt5/src/poppler-page-transition.cc \
#    poppler-qt5/qt5/src/poppler-page.cc \
#    poppler-qt5/qt5/src/poppler-pdf-converter.cc \
#    poppler-qt5/qt5/src/poppler-private.cc \
#    poppler-qt5/qt5/src/poppler-ps-converter.cc \
#    poppler-qt5/qt5/src/poppler-qiodeviceoutstream.cc \
#    poppler-qt5/qt5/src/poppler-sound.cc \
#    poppler-qt5/qt5/src/poppler-textbox.cc \
#    poppler-qt5/qt5/src/SignatureHandler.cc \
#    poppler-qt5/qt5/src/SignatureInfo.cc
#    poppler-qt5/splash/Splash.cc \
#    poppler-qt5/splash/SplashBitmap.cc \
#    poppler-qt5/splash/SplashClip.cc \
#    poppler-qt5/splash/SplashFont.cc \
#    poppler-qt5/splash/SplashFontEngine.cc \
#    poppler-qt5/splash/SplashFontFile.cc \
#    poppler-qt5/splash/SplashFontFileID.cc \
#    poppler-qt5/splash/SplashFTFont.cc \
#    poppler-qt5/splash/SplashFTFontEngine.cc \
#    poppler-qt5/splash/SplashFTFontFile.cc \
#    poppler-qt5/splash/SplashPath.cc \
#    poppler-qt5/splash/SplashPattern.cc \
#    poppler-qt5/splash/SplashScreen.cc \
#    poppler-qt5/splash/SplashState.cc \
#    poppler-qt5/splash/SplashXPath.cc \
#    poppler-qt5/splash/SplashXPathScanner.cc \
#    poppler-qt5/utils/HtmlFonts.cc \
#    poppler-qt5/utils/HtmlLinks.cc \
#    poppler-qt5/utils/HtmlOutputDev.cc \
#    poppler-qt5/utils/ImageOutputDev.cc \
#    poppler-qt5/utils/JSInfo.cc \
#    poppler-qt5/utils/parseargs.cc \
#    poppler-qt5/utils/pdfdetach.cc \
#    poppler-qt5/utils/pdffonts.cc \
#    poppler-qt5/utils/pdfimages.cc \
#    poppler-qt5/utils/pdfinfo.cc \
#    poppler-qt5/utils/pdfseparate.cc \
#    poppler-qt5/utils/pdfsig.cc \
#    poppler-qt5/utils/pdftocairo-win32.cc \
#    poppler-qt5/utils/pdftocairo.cc \
#    poppler-qt5/utils/pdftohtml.cc \
#    poppler-qt5/utils/pdftoppm.cc \
#    poppler-qt5/utils/pdftops.cc \
#    poppler-qt5/utils/pdftotext.cc \
#    poppler-qt5/utils/pdfunite.cc \
#    poppler-qt5/utils/printencodings.cc \
#    poppler-qt5/utils/Win32Console.cc


HEADERS += \
        mainwindow.h \
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
#    poppler-qt5/cpp/poppler-document-private.h \
#    poppler-qt5/cpp/poppler-document.h \
#    poppler-qt5/cpp/poppler-embedded-file-private.h \
#    poppler-qt5/cpp/poppler-embedded-file.h \
#    poppler-qt5/cpp/poppler-font.h \
#    poppler-qt5/cpp/poppler-global.h \
#    poppler-qt5/cpp/poppler-image-private.h \
#    poppler-qt5/cpp/poppler-image.h \
#    poppler-qt5/cpp/poppler-page-private.h \
#    poppler-qt5/cpp/poppler-page-renderer.h \
#    poppler-qt5/cpp/poppler-page-transition.h \
#    poppler-qt5/cpp/poppler-page.h \
#    poppler-qt5/cpp/poppler-private.h \
#    poppler-qt5/cpp/poppler-rectangle.h \
#    poppler-qt5/cpp/poppler-toc-private.h \
#    poppler-qt5/cpp/poppler-toc.h \
#    poppler-qt5/cpp/poppler-version.h.in \
#    poppler-qt5/fofi/FoFiBase.h \
#    poppler-qt5/fofi/FoFiEncodings.h \
#    poppler-qt5/fofi/FoFiIdentifier.h \
#    poppler-qt5/fofi/FoFiTrueType.h \
#    poppler-qt5/fofi/FoFiType1.h \
#    poppler-qt5/fofi/FoFiType1C.h \
#    poppler-qt5/glib/poppler-action.h \
#    poppler-qt5/glib/poppler-annot.h \
#    poppler-qt5/glib/poppler-attachment.h \
#    poppler-qt5/glib/poppler-cached-file-loader.h \
#    poppler-qt5/glib/poppler-date.h \
#    poppler-qt5/glib/poppler-document.h \
#    poppler-qt5/glib/poppler-enums.c.template \
#    poppler-qt5/glib/poppler-enums.h.template \
#    poppler-qt5/glib/poppler-form-field.h \
#    poppler-qt5/glib/poppler-input-stream.h \
#    poppler-qt5/glib/poppler-layer.h \
#    poppler-qt5/glib/poppler-media.h \
#    poppler-qt5/glib/poppler-movie.h \
#    poppler-qt5/glib/poppler-page.h \
#    poppler-qt5/glib/poppler-private.h \
#    poppler-qt5/glib/poppler-structure-element.h \
#    poppler-qt5/glib/poppler.h \
#    poppler-qt5/goo/FixedPoint.h \
#    poppler-qt5/goo/gfile.h \
#    poppler-qt5/goo/glibc.h \
#    poppler-qt5/goo/gmem.h \
#    poppler-qt5/goo/GooHash.h \
#    poppler-qt5/goo/GooLikely.h \
#    poppler-qt5/goo/GooList.h \
#    poppler-qt5/goo/GooMutex.h \
#    poppler-qt5/goo/GooString.h \
#    poppler-qt5/goo/GooTimer.h \
#    poppler-qt5/goo/grandom.h \
#    poppler-qt5/goo/gstrtod.h \
#    poppler-qt5/goo/gtypes.h \
#    poppler-qt5/goo/ImgWriter.h \
#    poppler-qt5/goo/JpegWriter.h \
#    poppler-qt5/goo/NetPBMWriter.h \
#    poppler-qt5/goo/PNGWriter.h \
#    poppler-qt5/goo/TiffWriter.h \
#    poppler-qt5/poppler/Annot.h \
#    poppler-qt5/poppler/Array.h \
#    poppler-qt5/poppler/BuiltinFont.h \
#    poppler-qt5/poppler/BuiltinFontTables.h \
#    poppler-qt5/poppler/CachedFile.h \
#    poppler-qt5/poppler/CairoFontEngine.h \
#    poppler-qt5/poppler/CairoOutputDev.h \
#    poppler-qt5/poppler/CairoRescaleBox.h \
#    poppler-qt5/poppler/Catalog.h \
#    poppler-qt5/poppler/CharCodeToUnicode.h \
#    poppler-qt5/poppler/CharTypes.h \
#    poppler-qt5/poppler/CMap.h \
#    poppler-qt5/poppler/CompactFontTables.h \
#    poppler-qt5/poppler/CurlCachedFile.h \
#    poppler-qt5/poppler/CurlPDFDocBuilder.h \
#    poppler-qt5/poppler/DateInfo.h \
#    poppler-qt5/poppler/DCTStream.h \
#    poppler-qt5/poppler/Decrypt.h \
#    poppler-qt5/poppler/Dict.h \
#    poppler-qt5/poppler/Error.h \
#    poppler-qt5/poppler/ErrorCodes.h \
#    poppler-qt5/poppler/FileSpec.h \
#    poppler-qt5/poppler/FlateEncoder.h \
#    poppler-qt5/poppler/FlateStream.h \
#    poppler-qt5/poppler/FontEncodingTables.h \
#    poppler-qt5/poppler/FontInfo.h \
#    poppler-qt5/poppler/Form.h \
#    poppler-qt5/poppler/Function.h \
#    poppler-qt5/poppler/Gfx.h \
#    poppler-qt5/poppler/GfxFont.h \
#    poppler-qt5/poppler/GfxState.h \
#    poppler-qt5/poppler/GfxState_helpers.h \
#    poppler-qt5/poppler/GlobalParams.h \
#    poppler-qt5/poppler/Hints.h \
#    poppler-qt5/poppler/JArithmeticDecoder.h \
#    poppler-qt5/poppler/JBIG2Stream.h \
#    poppler-qt5/poppler/JPEG2000Stream.h \
#    poppler-qt5/poppler/JPXStream.h \
#    poppler-qt5/poppler/Lexer.h \
#    poppler-qt5/poppler/Linearization.h \
#    poppler-qt5/poppler/Link.h \
#    poppler-qt5/poppler/LocalPDFDocBuilder.h \
#    poppler-qt5/poppler/MarkedContentOutputDev.h \
#    poppler-qt5/poppler/Movie.h \
#    poppler-qt5/poppler/NameToCharCode.h \
#    poppler-qt5/poppler/NameToUnicodeTable.h \
#    poppler-qt5/poppler/Object.h \
#    poppler-qt5/poppler/OptionalContent.h \
#    poppler-qt5/poppler/Outline.h \
#    poppler-qt5/poppler/OutputDev.h \
#    poppler-qt5/poppler/Page.h \
#    poppler-qt5/poppler/PageLabelInfo.h \
#    poppler-qt5/poppler/PageLabelInfo_p.h \
#    poppler-qt5/poppler/PageTransition.h \
#    poppler-qt5/poppler/Parser.h \
#    poppler-qt5/poppler/PDFDoc.h \
#    poppler-qt5/poppler/PDFDocBuilder.h \
#    poppler-qt5/poppler/PDFDocEncoding.h \
#    poppler-qt5/poppler/PDFDocFactory.h \
#    poppler-qt5/poppler/PopplerCache.h \
#    poppler-qt5/poppler/PreScanOutputDev.h \
#    poppler-qt5/poppler/ProfileData.h \
#    poppler-qt5/poppler/PSOutputDev.h \
#    poppler-qt5/poppler/PSTokenizer.h \
#    poppler-qt5/poppler/Rendition.h \
#    poppler-qt5/poppler/SecurityHandler.h \
#    poppler-qt5/poppler/SignatureHandler.h \
#    poppler-qt5/poppler/SignatureInfo.h \
#    poppler-qt5/poppler/Sound.h \
#    poppler-qt5/poppler/SplashOutputDev.h \
#    poppler-qt5/poppler/StdinCachedFile.h \
#    poppler-qt5/poppler/StdinPDFDocBuilder.h \
#    poppler-qt5/poppler/Stream-CCITT.h \
#    poppler-qt5/poppler/Stream.h \
#    poppler-qt5/poppler/StructElement.h \
#    poppler-qt5/poppler/StructTreeRoot.h \
#    poppler-qt5/poppler/TextOutputDev.h \
#    poppler-qt5/poppler/UnicodeCClassTables.h \
#    poppler-qt5/poppler/UnicodeCompTables.h \
#    poppler-qt5/poppler/UnicodeDecompTables.h \
#    poppler-qt5/poppler/UnicodeMap.h \
#    poppler-qt5/poppler/UnicodeMapFuncs.h \
#    poppler-qt5/poppler/UnicodeMapTables.h \
#    poppler-qt5/poppler/UnicodeTypeTable.h \
#    poppler-qt5/poppler/UTF.h \
#    poppler-qt5/poppler/ViewerPreferences.h \
#    poppler-qt5/poppler/XpdfPluginAPI.h \
#    poppler-qt5/poppler/XRef.h \
#    poppler-qt5/qt5/src/ArthurOutputDev.h \
#    poppler-qt5/qt5/src/Mainpage.dox \
#    poppler-qt5/qt5/src/poppler-annotation-helper.h \
#    poppler-qt5/qt5/src/poppler-annotation-private.h \
#    poppler-qt5/qt5/src/poppler-annotation.h \
#    poppler-qt5/qt5/src/poppler-converter-private.h \
#    poppler-qt5/qt5/src/poppler-embeddedfile-private.h \
#    poppler-qt5/qt5/src/poppler-export.h \
#    poppler-qt5/qt5/src/poppler-form.h \
#    poppler-qt5/qt5/src/poppler-link-extractor-private.h \
#    poppler-qt5/qt5/src/poppler-link-private.h \
#    poppler-qt5/qt5/src/poppler-link.h \
#    poppler-qt5/qt5/src/poppler-media.h \
#    poppler-qt5/qt5/src/poppler-optcontent-private.h \
#    poppler-qt5/qt5/src/poppler-optcontent.h \
#    poppler-qt5/qt5/src/poppler-page-private.h \
#    poppler-qt5/qt5/src/poppler-page-transition-private.h \
#    poppler-qt5/qt5/src/poppler-page-transition.h \
#    poppler-qt5/qt5/src/poppler-private.h \
#    poppler-qt5/qt5/src/poppler-qiodeviceoutstream-private.h \
#    poppler-qt5/qt5/src/poppler-qt5.h \
#    poppler-qt5/splash/Splash.h \
#    poppler-qt5/splash/SplashBitmap.h \
#    poppler-qt5/splash/SplashClip.h \
#    poppler-qt5/splash/SplashErrorCodes.h \
#    poppler-qt5/splash/SplashFont.h \
#    poppler-qt5/splash/SplashFontEngine.h \
#    poppler-qt5/splash/SplashFontFile.h \
#    poppler-qt5/splash/SplashFontFileID.h \
#    poppler-qt5/splash/SplashFTFont.h \
#    poppler-qt5/splash/SplashFTFontEngine.h \
#    poppler-qt5/splash/SplashFTFontFile.h \
#    poppler-qt5/splash/SplashGlyphBitmap.h \
#    poppler-qt5/splash/SplashMath.h \
#    poppler-qt5/splash/SplashPath.h \
#    poppler-qt5/splash/SplashPattern.h \
#    poppler-qt5/splash/SplashScreen.h \
#    poppler-qt5/splash/SplashState.h \
#    poppler-qt5/splash/SplashTypes.h \
#    poppler-qt5/splash/SplashXPath.h \
#    poppler-qt5/splash/SplashXPathScanner.h \
#    poppler-qt5/utils/HtmlFonts.h \
#    poppler-qt5/utils/HtmlLinks.h \
#    poppler-qt5/utils/HtmlOutputDev.h \
#    poppler-qt5/utils/HtmlUtils.h \
#    poppler-qt5/utils/ImageOutputDev.h \
#    poppler-qt5/utils/JSInfo.h \
#    poppler-qt5/utils/numberofcharacters.h \
#    poppler-qt5/utils/parseargs.h \
#    poppler-qt5/utils/pdftocairo-win32.h \
#    poppler-qt5/utils/printencodings.h \
#    poppler-qt5/utils/Win32Console.h \
#    poppler-qt5/config.h
#    poppler-qt5/qt5/src/SignatureHandler.h \
#    poppler-qt5/qt5/src/SignatureInfo.h


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
INCLUDEPATH += \
            /usr/local/include \
             /usr/local/include/opencv2 \
#            /usr/local/include/poppler  \
#            poppler-qt5/qt5/src \
#            /usr/local/Cellar/glib/2.56.1/include/glib-2.0  \
#            /usr/local/Cellar/glib/2.56.1/lib/glib-2.0/include  \
#            /usr/local/Cellar/cairo/1.14.12/include/cairo   \
#            /usr/local/Cellar/nspr/4.19/include/nspr    \
#            /usr/local/Cellar/nspr/4.19/include/nspr/md    \
#            /usr/local/Cellar/nspr/4.19/include/nspr/obsolete    \
#            /usr/local/Cellar/nss/3.36.1/include/nss

LIBS +=         \
            -L/usr/local/lib -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs \
            -L/System/Library/Frameworks/ImageIO.framework/Versions/A/Resources -lJPEG \
#            -L/usr/local/lib -lpoppler.75.0.0 -lpoppler-glib.8.9.0 -lpoppler-cpp.0.4.0 \
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



