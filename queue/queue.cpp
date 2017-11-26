#include "queue.h"

using namespace php;
using namespace std;

#define DEFAULT_QUEUE_SIZE 64
struct QueueObject{
    int start;
    int last;
    int size;
    int eleNum;
    Variant *storage;
};

PHPX_METHOD(Queue,__construct){
    QueueObject *queue = (QueueObject *)emalloc(sizeof(QueueObject));

    queue->storage = (Variant *)ecalloc(DEFAULT_QUEUE_SIZE, sizeof(Variant));
    queue->start = 0;
    queue->last = 0;
    queue->size = DEFAULT_QUEUE_SIZE;
    queue->eleNum = 0;

    _this.oSet("queue_ptr", "QueueResource", queue);
}

void queueDtor(zend_resource *res){
    //QueueObject * qo = static_cast<QueueObject *>(res->ptr);
    //delete qo;
}

PHPX_METHOD(Queue,count){
    QueueObject *queue = _this.oGet<QueueObject>("queue_ptr", "QueueResource");

    retval = queue->eleNum;
}

PHPX_METHOD(Queue,isEmpty){
    QueueObject *queue = _this.oGet <QueueObject>("queue_ptr", "QueueResource");

    retval = queue->eleNum == 0;
}

PHPX_METHOD(Queue,isFull){
    QueueObject *queue = _this.oGet <QueueObject>("queue_ptr", "QueueResource");

    retval = queue->eleNum == queue->size - 1;
}

PHPX_METHOD(Queue,push){
    QueueObject *queue = _this.oGet <QueueObject>("queue_ptr", "QueueResource");

    //队列满
    if((queue->last+1)%queue->size == queue->start){
        retval = false;
        return;
    }
    queue->storage[queue->last] = args[0];
    queue->last = queue->last % (queue->size - 1) + 1;
    queue->eleNum += 1;

    retval = true;
}

PHPX_METHOD(Queue,pull){
    QueueObject *queue = _this.oGet <QueueObject>("queue_ptr", "QueueResource");

    if(queue->eleNum<=0){
        retval = false;
        return;
    }
    queue->start = (queue->start + 1) % (queue->size - 1);
    queue->eleNum -= 1;

    retval = true;
}

PHPX_METHOD(Queue,first){
    QueueObject *queue = _this.oGet <QueueObject>("queue_ptr", "QueueResource");

    if(queue->eleNum <= 0){
        retval = nullptr;
        return;
    }
    retval = queue->storage[queue->start];
}

PHPX_EXTENSION() {
    Extension *extension = new Extension("queue", "0.0.1");

    extension->onStart = [extension]() noexcept {
        extension->registerConstant("QUEUE_VERSION", 1001);

        Class *c = new Class("Queue");
        c->addMethod(PHPX_ME(Queue, __construct), CONSTRUCT);
        c->addMethod(PHPX_ME(Queue, count));
        c->addMethod(PHPX_ME(Queue, isEmpty));
        ArgInfo *pushArgi = new ArgInfo(1);
        pushArgi->add("value","Variant");
        c->addMethod(PHPX_ME(Queue, push), PUBLIC, pushArgi);
        c->addMethod(PHPX_ME(Queue, pull));
        c->addMethod(PHPX_ME(Queue, first));

        extension->registerClass(c);

        extension->registerResource("QueueResource", queueDtor);
    };

    //extension->onShutdown = [extension]() noexcept {
    //    cout << extension->name << "shutdown" << endl;
    //};

    //extension->onBeforeRequest = [extension]() noexcept {
    //    cout << extension->name << "beforeRequest" << endl;
    //};

    //extension->onAfterRequest = [extension]() noexcept {
    //    cout << extension->name << "afterRequest" << endl;
    //};

    extension->info({"cpp_ext support", "enabled"},
                    {
                        {"author", "Jiang Weilong"},
                        {"version", extension->version},
                        {"date", "2017-11-26"},
                    });

    return extension;
}