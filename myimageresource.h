#ifndef MYIMAGERESOURCE_H
#define MYIMAGERESOURCE_H
#include <QString>
#include <Wt/WMemoryResource>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
class QImage;

class MyImageResource : public Wt::WMemoryResource
{
public:
    MyImageResource(Wt::WObject *parent = 0);

    void load(const QString filepath);
    void load(const QImage image);
    void loadSmall(const QString filepath, int height=100);

    int width() const;
    int height() const;
private:
    int m_width;
    int m_height;
};

#endif // MYIMAGERESOURCE_H
