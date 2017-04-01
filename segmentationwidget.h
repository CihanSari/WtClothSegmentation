#ifndef SEGMENTATIONWIDGET_H
#define SEGMENTATIONWIDGET_H
#include <Wt/WContainerWidget>
#include <QString>
class VisionItem;
class SegmentationWidget : public Wt::WContainerWidget
{
public:
    SegmentationWidget(QString filepath, int bgMethod, bool hideRect, Wt::WContainerWidget *parent=0);
    virtual ~SegmentationWidget();
private:
    VisionItem* item;
};

#endif // SEGMENTATIONWIDGET_H
