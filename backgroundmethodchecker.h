#ifndef BACKGROUNDMETHODCHECKER_H
#define BACKGROUNDMETHODCHECKER_H

#include <Wt/WContainerWidget>

class BackgroundMethodChecker : public Wt::WContainerWidget
{
public:
    BackgroundMethodChecker(Wt::WContainerWidget *parent=0);
    int getIdx() const;
    void checkChanged();
private:
    int _selected;
     Wt::WButtonGroup *group;
};

#endif // BACKGROUNDMETHODCHECKER_H
