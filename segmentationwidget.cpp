#include "segmentationwidget.h"
#include "visionitem.h"
#include "myimageresource.h"
#include <Wt/WImage>
SegmentationWidget::SegmentationWidget(QString filepath, int bgMethod, bool hideRect,  Wt::WContainerWidget *parent)
        : Wt::WContainerWidget(parent),
          item(VisionItem::createVisionItem(filepath))
{
    item->setShowBGPixels(bgMethod);
    item->hideMaskRect(hideRect);
    item->prepareAndSetIcon();
    QImage image = item->getImage();

    MyImageResource* imageResource = new MyImageResource();
    imageResource->load(image);
    Wt::WImage * wt_image = new Wt::WImage(imageResource,this);
    wt_image->setHeight(imageResource->height());
    wt_image->setWidth(imageResource->width());
    wt_image->setToolTip(filepath.toLatin1().constData());

}

SegmentationWidget::~SegmentationWidget()
{
    delete item;
}
