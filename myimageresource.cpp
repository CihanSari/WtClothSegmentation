#include "myimageresource.h"
#include <QFile>
#include <QByteArray>
#include <QBuffer>
#include <QImage>
MyImageResource::MyImageResource(Wt::WObject *parent)
    : Wt::WMemoryResource("image/jpg",parent)
{
}

void MyImageResource::load(const QString filepath) {
    load(filepath);
}

void MyImageResource::load(const QImage image)
{
    QByteArray jpgData;
    QBuffer buffer(&jpgData);
    buffer.open(QIODevice::WriteOnly);
    m_width = image.width();
    m_height = image.height();
    image.save(&buffer, "JPG");
    setMimeType("image/jpg");
    std::vector<unsigned char> bufferToCompress(
        jpgData.begin(), jpgData.end());
    setData(bufferToCompress);
}

void MyImageResource::loadSmall(const QString filepath, int height)
{
    load(QImage(filepath).scaledToHeight(height));
}

int MyImageResource::width() const
{
    return m_width;
}

int MyImageResource::height() const
{
    return m_height;
}
