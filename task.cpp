/*2) Реализовать иерархию классов Widget, где Widget - это базовый класс,
 	а TabWidget и CalendarWidget - это конкретные реализации базового класса.
  	Каждый виджет может хранить сколько угодно дочерних виджетов. 
  	Каждый виджет хранит указатель на родительский виджет, родительских виджетов не может быть несколько, только один.
   	Так же необходимо реализовать метод, позволяющий идентифицировать тип конкретного виджета.
	В реализации использовать умные указатели.*/

#include <iostream>
#include <memory>
#include <list>

using std::cin; using std::cout; using std::endl;

class Widget
{
public:
	Widget() :parent(nullptr){}

	virtual ~Widget(){}

	void setParent(std::shared_ptr<Widget> parent)
	{
		this->parent = std::move(parent);
	}

	std::shared_ptr<Widget> getParent() const
	{
		return parent;
	}

	void addChild(std::shared_ptr<Widget> child)
	{
		children.push_back(std::move(child));
	}

	std::list<std::shared_ptr<Widget>> getChildren()
	{
		return children;
	}

	virtual void identify() const
	{
		cout << "Widget\n";
	}

private:
	std::shared_ptr<Widget> parent;
	std::list<std::shared_ptr<Widget>> children;
};

class TabWidget : public Widget
{
public:
	void identify() const override
	{
		cout << "TabWidget\n";
	}
};

class CalendarWidget : public Widget
{
public:
	void identify() const override
	{
		cout << "CalendarWidget\n";
	}
};

int main(int argc, char** argv)
{
    std::shared_ptr<Widget> widget1 = std::make_shared<Widget>();
    std::shared_ptr<Widget> widget2 = std::make_shared<TabWidget>();
    std::shared_ptr<Widget> widget3 = std::make_shared<CalendarWidget>();

    widget2->setParent(widget1);
    widget3->setParent(widget1);
    widget1->addChild(widget2);
    widget1->addChild(widget3);

    widget1->identify();
    widget2->identify();
    widget3->identify();

    std::list<std::shared_ptr<Widget>> children = widget1->getChildren();
    for (const auto& child : children)
    {
        child->identify();
    }

    return 0;
}