#include <QCoreApplication>
#include <QCommandLineParser>
#include <Wt/WApplication>
#include "clothsegmentation.h"
Wt::WApplication *createApplication(const Wt::WEnvironment& env);
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("WtClothSegmentation");
    QCoreApplication::setApplicationVersion("00.01");
    QCoreApplication::setOrganizationName("cihansari");
    QCoreApplication::setOrganizationDomain("www.cihansari.com");

    QCommandLineParser parser;
    parser.setApplicationDescription("Perform cloth segmentation and see results.");
    parser.addHelpOption();
    parser.addPositionalArgument("source", "Source directory to look for images.");

    QCommandLineOption portOption("http-port", "Network port to run web interface.", "Port", "9083");
    parser.addOption(portOption);

    QCommandLineOption modelOption("s", "File path for svm model.", "file");
    parser.addOption(modelOption);

    QCommandLineOption goldenLandmarksOption("g", "File path for golden landmarks.", "file");
    parser.addOption(goldenLandmarksOption);

    parser.process(a);

    const QStringList args = parser.positionalArguments();
    if (args.isEmpty()) {
        parser.showHelp(0);
    }

    ClothSegmentation::registerSVM(parser.value(modelOption));
    ClothSegmentation::registerGoldenLandmarks(parser.value(goldenLandmarksOption));

    QString httpport = parser.value(portOption);

    QStringList wt_arguments;
    wt_arguments << argv[0] << "--docroot" << "." << "--http-address" << "0.0.0.0" << "--http-port" << httpport << "--config" << "wt_config.xml";
    int wt_argc = wt_arguments.count();
    char **wt_argv = new char*[wt_argc];

    for (int i=0; i<wt_argc; ++i) {
        QString argStr = wt_arguments.value(i);
        wt_argv[i] = new char[argStr.length()];
        std::strcpy(wt_argv[i], argStr.toLatin1().constData());
    }
    return WRun(wt_argc, wt_argv, &createApplication);
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
    Wt::WApplication *app = new Wt::WApplication(env);
    app->setTitle("Cloth Segmentation");
    app->root()->addWidget(new ClothSegmentation());
    return app;
}
