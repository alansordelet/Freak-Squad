#pragma once
#include "CoffeeCore.hpp"
#include <functional>

enum RESULT
{
	SUCCEEDED = 1, FAILED, IN_PROGRESS, SLEEPING
};
enum COMPOSITE
{
	SELECTOR = 1, SEQUENCE
};

class NodeComponent : public std::enable_shared_from_this<NodeComponent> //root
{
protected:
	std::weak_ptr<NodeComponent> sp_parent;
	std::weak_ptr<GameObject> sp_parentGameObject;
	RESULT m_result;
public:
	NodeComponent();
	NodeComponent(std::weak_ptr<GameObject> _GC);
	~NodeComponent();
	void setParent(NodeComponent* _p);
	void setParentGameObject(NodeComponent* _p);
	std::weak_ptr<NodeComponent> getParent();
	std::weak_ptr<GameObject> getParentGameObject();
	RESULT getResult();
	void setResult(RESULT _result);
	virtual	void add(std::shared_ptr<NodeComponent> _node) = 0;
	virtual void update() = 0;
	virtual void setChildrenSleeping();
};

class NodeTask : public NodeComponent // Leaf
{
private:
	std::function<const void()> task;
public:
	NodeTask();
	NodeTask(std::weak_ptr<GameObject> _GC);
	~NodeTask();

	void setFunction(std::function<const void()> _task);
	void update();
	virtual	void add(std::shared_ptr<NodeComponent> _node);
};

class NodeDecorator : public NodeComponent // Condition/BlackBoard
{
private:
	std::function<const bool()> condition;
public:
	NodeDecorator();
	NodeDecorator(std::weak_ptr<GameObject> _GC, std::function<const bool()> _condition);
	~NodeDecorator();

	void update();
	virtual void add(std::shared_ptr<NodeComponent> _node);
	bool getConditionFunction();
};

class NodeComposite : public NodeComponent // Selector/Sequence
{
private:
	std::list<std::shared_ptr<NodeComponent>> l_children;
	std::list<std::shared_ptr<NodeDecorator>> l_decorator;

	COMPOSITE m_composite;
public:
	NodeComposite();
	NodeComposite(std::weak_ptr<GameObject> _GC, COMPOSITE _composite);
	~NodeComposite();

	virtual	void add(std::shared_ptr<NodeComponent> _node);
	virtual void addDecorator(std::shared_ptr<NodeDecorator> _decorator);
	virtual void update();

	void setChildrenSleeping();
};