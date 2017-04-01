#include "backgroundmethodchecker.h"
#include <Wt/WButtonGroup>
#include <Wt/WRadioButton>
#include <Wt/WString>
#include <Wt/WText>

BackgroundMethodChecker::BackgroundMethodChecker(Wt::WContainerWidget* parent):
    Wt::WContainerWidget(parent)
{
    BackgroundMethodChecker* container = this;
    group = new Wt::WButtonGroup(container);

    Wt::WRadioButton *rb;

    rb = new Wt::WRadioButton("Mono", container);
    rb->setInline(false);
    group->addButton(rb, 1);

    rb = new Wt::WRadioButton("Color", container);
    rb->setInline(false);
    group->addButton(rb, 2);

    rb = new Wt::WRadioButton("Black", container);
    rb->setInline(false);
    group->addButton(rb, 3);

    rb = new Wt::WRadioButton("White", container);
    rb->setInline(false);
    group->addButton(rb, 4);

    _selected=1;
    group->setSelectedButtonIndex(0); // Select the first button by default.

//    group->checkedChanged().connect(&BackgroundMethodChecker::checkChanged);
}

int BackgroundMethodChecker::getIdx() const
{
    return group->checkedId();
}

void BackgroundMethodChecker::checkChanged()
{
    _selected = group->checkedId();
}
