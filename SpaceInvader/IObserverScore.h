#pragma once
#include <iostream>
#include <list>
class IObserverScore
{
public:
	virtual ~IObserverScore() {};
	virtual void Update(const std::string& message_from_subject) = 0;


};

class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserverScore* observer) = 0;
	virtual void Detach(IObserverScore* observer) = 0;
	virtual void Notify() = 0;
};

class Subject : public ISubject {
public:

    /**
  * The subscription management methods.
  */
    void Attach(IObserverScore* observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserverScore* observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        std::list<IObserverScore*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }
    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

private:
    std::list<IObserverScore*> list_observer_;
    std::string message_;
};

class Observer : public IObserverScore {
public:
    Observer(Subject& subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }
    void Update(const std::string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
   void PrintInfo() {
       std::cout << "le score est de : ";
   }

private:
    std::string message_from_subject_;
    Subject& subject_;
    static int static_number_;
    int number_;
};