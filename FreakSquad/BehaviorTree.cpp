//#include "pch.h"
#include "BehaviorTree.h"

NodeComponent::NodeComponent()
{
	m_result = SLEEPING;
}

NodeComponent::NodeComponent(std::weak_ptr<GameObject> _GC)
{
	this->sp_parentGameObject = _GC;
	m_result = SLEEPING;
}

NodeComponent::~NodeComponent()
{
}
void NodeComponent::setChildrenSleeping()
{
}

void NodeComponent::setParent(NodeComponent* _p)
{
	sp_parent = _p->weak_from_this();
}

void NodeComponent::setParentGameObject(NodeComponent* _p)
{
	this->sp_parentGameObject = _p->getParentGameObject();
}

std::weak_ptr<NodeComponent> NodeComponent::getParent()
{
	return sp_parent;
}

std::weak_ptr<GameObject> NodeComponent::getParentGameObject()
{
	return sp_parentGameObject;
}

RESULT NodeComponent::getResult()
{
	return m_result;
}

void NodeComponent::setResult(RESULT _result)
{
	m_result = _result;
}

NodeComposite::NodeComposite()
{
}

NodeComposite::NodeComposite(std::weak_ptr<GameObject> _GC, COMPOSITE _composite)
{
	this->sp_parentGameObject = _GC;
	m_result = SLEEPING;
	m_composite = _composite;
}

NodeComposite::~NodeComposite()
{
}

void NodeComposite::add(std::shared_ptr<NodeComponent> _node)
{
	l_children.push_back(_node);
	_node->setParentGameObject(this);
	_node->setParent(this);
}

void NodeComposite::addDecorator(std::shared_ptr<NodeDecorator> _decorator)
{
	l_decorator.push_back(_decorator);
	_decorator->setParentGameObject(this);
	_decorator->setParent(this);
}

void NodeComposite::setChildrenSleeping()
{
	for (auto child : l_children)
	{
		child->setResult(SLEEPING);
		child->setChildrenSleeping();
	}
}
void NodeComposite::update()
{
	/*if (m_result == SUCCEEDED)
	{
		for (auto it : l_children)
			it->setResult(SLEEPING);
	}*/

	for (auto condition : l_decorator)
	{
		if (!(condition->getConditionFunction()))
		{
			if (sp_parent.lock())
			{
				sp_parent.lock()->setResult(SUCCEEDED );
				sp_parent.lock()->setChildrenSleeping();
			}
			return;
		}
	}

	auto it = l_children.begin();
	if (m_composite == SEQUENCE)
	{
		while (it != l_children.end())
		{
			this;
			RESULT test = (*it)->getResult();
			if ((*it)->getResult() == SUCCEEDED)
			{
				it++;
				if (it == l_children.end()) {
					setChildrenSleeping();
					m_result = SUCCEEDED;
					return;
				}
			}
			else if ((*it)->getResult() == IN_PROGRESS)
			{
				(*it)->update();
				return;
			}
			else if ((*it)->getResult() == FAILED)
			{
				if (sp_parent.lock())
				{
					sp_parent.lock()->setResult(SLEEPING);
					sp_parent.lock()->setChildrenSleeping();
				}
				m_result = FAILED;
				return;
			}
			else if ((*it)->getResult() == SLEEPING)
			{
				(*it)->setResult(IN_PROGRESS);
				return;
			}
		}
	}
	else if (m_composite == SELECTOR)
	{
		this;
		while (it != l_children.end())
		{
			if ((*it)->getResult() == SUCCEEDED)
			{
				it++;
				if (it == l_children.end())
				{
					setChildrenSleeping();
					m_result = SUCCEEDED;
				}
			}
			else if ((*it)->getResult() == IN_PROGRESS)
			{
				(*it)->update();
				return;
			}
			else if ((*it)->getResult() == FAILED)
			{
				//if ((*it)->)
				//setChildrenSleeping();
				if (sp_parent.lock())
					m_result = FAILED;

				it++;
			}
			else if ((*it)->getResult() == SLEEPING)
			{
				(*it)->setResult(IN_PROGRESS);
				return;
			}
		}
	}
}

NodeDecorator::NodeDecorator()
{
}

NodeDecorator::NodeDecorator(std::weak_ptr<GameObject> _GC, std::function<const bool()> _condition)
{
	this->sp_parentGameObject = _GC;
	condition = _condition;
}

NodeDecorator::~NodeDecorator()
{
}

void NodeDecorator::update()
{
}

void NodeDecorator::add(std::shared_ptr<NodeComponent> _node)
{
}

bool NodeDecorator::getConditionFunction()
{
	return condition();
}

NodeTask::NodeTask()
{
}

NodeTask::NodeTask(std::weak_ptr<GameObject> _GC)
{
	this->sp_parentGameObject = _GC;
}

NodeTask::~NodeTask()
{
}

void NodeTask::setFunction(std::function<const void()> _task)
{
	task = _task;
}

void NodeTask::update()
{
	task();
}

void NodeTask::add(std::shared_ptr<NodeComponent> _node)
{
}
