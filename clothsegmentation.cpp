#include "clothsegmentation.h"
#include <QHash>
#include <QFileInfoList>
#include <QDir>
#include <Wt/WFileUpload>
#include <Wt/Http/Request>
#include <QImage>
#include <QProcess>
#include "segmentationwidget.h"
#include <Wt/WProgressBar>
#include <Wt/WPushButton>
#include "backgroundmethodchecker.h"
#include <Wt/WCheckBox>

ClothSegmentation::ClothSegmentation(Wt::WContainerWidget *parent)
    : Wt::WContainerWidget(parent)
{
    Wt::WFileUpload *fu = new Wt::WFileUpload(this);
    fu->setFileTextSize(50); // Set the width of the widget to 50 characters
    fu->setProgressBar(new Wt::WProgressBar());
    fu->setMargin(10, Wt::Right);
    Wt::WPushButton *uploadButton = new Wt::WPushButton("Segment", this);
    uploadButton->setMargin(10, Wt::Left | Wt::Right);

    Wt::WText *out = new Wt::WText(this);

    Wt::WCheckBox *cbHideClothRectangle;

    cbHideClothRectangle = new Wt::WCheckBox("Hide cloth rectangle", this);
    cbHideClothRectangle->setChecked(true);


    BackgroundMethodChecker* bmc = new BackgroundMethodChecker(this);

    // Upload when the button is clicked.
    uploadButton->clicked().connect(std::bind([=] () {
        fu->upload();
        uploadButton->disable();
    }));

    // Upload automatically when the user entered a file.
    fu->changed().connect(std::bind([=] () {
        fu->upload();
        uploadButton->disable();
        out->setText("File upload is changed.");
    }));

    // React to a succesfull upload.
    fu->uploaded().connect(std::bind([=] () {
        QString errorString;
        QString filepath = QString::fromStdString(fu->spoolFileName());
//        if (callClothSegmentation(filepath, errorString))
            new SegmentationWidget(filepath, bmc->getIdx(), cbHideClothRectangle->isChecked(),this);


        out->setText("File upload is finished.");
        uploadButton->enable();
    }));

    // React to a file upload problem.
    fu->fileTooLarge().connect(std::bind([=] () {
        out->setText("File is too large.");
    }));

}
//void ClothSegmentation::registerPath(QString path)
//{
//    QDir pathDir(path);
//    pathHash.insert(path,pathDir.entryInfoList(QStringList() << ".png" << ".jpg" << ".bmp", QDir::Files | QDir::NoDotAndDotDot));
//}

//QString clothMetaKey;
//QString clothSegmentationPath;
//void ClothSegmentation::registerClothSegmentation(QString path)
//{
//    clothSegmentationPath = path;
//}
//void ClothSegmentation::registerClothMeta(QString metaKey)
//{
//    clothMetaKey = metaKey;
//}


//bool ClothSegmentation::callClothSegmentation(QString filepath, QString &errorString)
//{
////    QString command("%1 %2");
////    QProcess::start()
////    system(command.arg(clothSegmentationPath,filepath));
//    return true;

//}
