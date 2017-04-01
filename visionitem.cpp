#include "visionitem.h"
#include <QDir>
#include "opencv2/opencv.hpp"
#include "grabcutapplication.h"
#include <QHash>
#include <QCoreApplication>

#define GrabcutDataKey "GrabCutData"
QImage mat2Q(cv::Mat inMat);
class VisionItemPrivate
{
public:
    bool loadImage(){
        QFileInfo fileInfo = __fileInfo;
        QImage qimage(fileInfo.filePath());
        if (qimage.isNull()) {
            return false;
        }

        Q_FOREACH (QString key, qimage.textKeys()) {
            imageMeta.insert(key, qimage.text(key));
        }
        __name = qimage.text("Year");

        QString baseString = imageMeta.value(GrabcutDataKey);

        qimage = qimage.convertToFormat(QImage::Format_ARGB32);
        cv::Mat cvImage(qimage.height(),qimage.width(),CV_8UC4,const_cast<uchar*>(qimage.bits()),
                        static_cast<size_t>(qimage.bytesPerLine()));

        if (cvImage.empty())
            return false;

        qDebug(baseString.toLatin1());
        gca = new GCApplication(cvImage, fileInfo.baseName().toStdString(),baseString.toStdString());
        p->prepareAndSetIcon();
        return true;
    }

    void pushChanges() {
        cv::Mat originalMat = gca->image().clone();
        QImage originalIm = mat2Q(originalMat);
        Q_FOREACH (QString key, imageMeta.keys()) {
            originalIm.setText(key, imageMeta.value(key));
        }
        qApp->processEvents();
        originalIm.save(__fileInfo.filePath());
    }

    VisionItem* p;
    GCApplication* gca;
    QHash<QString,QString> imageMeta;
    int __showBGPixels;
    QImage __image;
    QString __name;
    QFileInfo __fileInfo;
};

VisionItem::VisionItem(QFileInfo fileInfo):
    d(new VisionItemPrivate)
{
    d->p = this;
    d->gca=0;
    d->__fileInfo=fileInfo;
    d->__name=fileInfo.baseName();
}

VisionItem *VisionItem::createVisionItem(QFileInfo fileInfo)
{
    VisionItem* res = new VisionItem(fileInfo);
    if (res->d->loadImage()) {
        return res;
    } else {
        qWarning("Cannot read: %s",fileInfo.filePath().toLatin1().constData());
        delete res;
    }
    return 0;
}

VisionItem::~VisionItem()
{
    if (d->gca) {
        d->gca->closeWindow();
        delete d->gca;
        d->gca=0;
    }
    delete d;
}

//void VisionItem::edit()
//{
//    d->gca->showImage();
//    int garbageKeyLimit=99;
//    for (int i=0;i<garbageKeyLimit;++i)
//    {
//        qApp->processEvents();
//        int c = cv::waitKey(0); // when window is closed, garbageKeyLimit expires in an instant

//        switch( (char) c )
//        {
//        case '1':
//        case '2':
//        case '3':
//        case '4':
//            d->gca->showBGPixels(QString(c).toInt());
//            i=0;
//            d->gca->showImage();
//            break;
//        case '\x1b':
//            std::cout << "Next ..." << std::endl;
//            i=garbageKeyLimit; //terminate
//            break;
//        case 'f':
//            std::cout << std::endl;
//            d->gca->resetFromFace();
//            d->gca->showImage();
//            i=0; // termination is garbageKeyLimit stupid presses away
//            break;
//        case 'r':
//            std::cout << std::endl;
//            d->gca->reset();
//            d->gca->showImage();
//            i=0; // termination is garbageKeyLimit stupid presses away
//            break;
//        case 'n':
//            int iterCount = d->gca->getIterCount();
//            std::cout << "<" << iterCount << "... ";
//            int newIterCount = d->gca->nextIter();
//            if( newIterCount > iterCount )
//            {
//                d->gca->showImage();
//                std::cout << iterCount << ">" << std::endl;
//            }
//            else
//                std::cout << "rect must be determined>" << std::endl;
//            i=0; // termination is garbageKeyLimit stupid presses away
//            break;
//        }
//    }
//    d->gca->closeWindow();
//    qApp->processEvents();
//    prepareAndSetIcon();
//    qApp->processEvents();
//    d->imageMeta.insert(GrabcutDataKey, QString::fromStdString(d->gca->toString()));
//    d->pushChanges();
//}

QImage VisionItem::getImage() const
{
    return d->__image;
}

QString VisionItem::getName() const
{
    return d->__name;
}

QFileInfo VisionItem::getFileInfo() const
{
    return d->__fileInfo;
}

void VisionItem::hideMaskRect(bool isHidden)
{
    d->gca->hideMaskRect(isHidden);
    prepareAndSetIcon();
}

void VisionItem::setShowBGPixels(int showBGPixels)
{
    d->__showBGPixels = showBGPixels;
    d->gca->showBGPixels(showBGPixels);
    prepareAndSetIcon();
}

void VisionItem::prepareAndSetIcon()
{
    cv::Mat processedMat = d->gca->visualizeImage();
    QImage processedQImage = mat2Q(processedMat);
    d->__image = processedQImage.copy();
}

void VisionItem::setMeta(QString metaKey, QString value)
{
    d->imageMeta.insert(metaKey, value);
    d->pushChanges();
}

QString VisionItem::getMeta(QString metaKey) const
{
    return d->imageMeta.value(metaKey);
}

QImage mat2Q(cv::Mat inMat) {
    cv::cvtColor(inMat, inMat, CV_BGR2RGB);
    QImage qImage(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
    return qImage;
}
