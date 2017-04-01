#ifndef VISIONITEM_H
#define VISIONITEM_H
#include <QColor>
#include <QIcon>
#include <QFileInfo>


class VisionItemPrivate;
class VisionItem
{
    VisionItemPrivate*d;
    VisionItem(QFileInfo fileInfo);
public:
    static VisionItem* createVisionItem(QFileInfo fileInfo);
    ~VisionItem();
//    void edit();
    QImage getImage() const;
    QString getName() const;
    QFileInfo getFileInfo() const;
    void hideMaskRect(bool isHidden);
    void setShowBGPixels(int showBGPixels);
    void prepareAndSetIcon();
    void setMeta(QString metaKey, QString value);
    QString getMeta(QString metaKey) const;
};

#endif // VISIONITEM_H
