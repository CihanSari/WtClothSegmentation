#ifndef CLOTHSEGMENTATION_H
#define CLOTHSEGMENTATION_H
#include <Wt/WContainerWidget>
#include <QString>
class ClothSegmentation : public Wt::WContainerWidget
{
public:
    ClothSegmentation(Wt::WContainerWidget *parent=0);
    static void registerSVM(QString svmModelPath);
    static void registerGoldenLandmarks(QString goldenLandmarksPath);
};

#endif // CLOTHSEGMENTATION_H
