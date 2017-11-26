#include "queue.h"

#define DEFAULT_QUEUE_SIZE 64
typedef struct QueueObject{
    int start;
    int end;
    int maxSize;
    int eleNum;
    Variant *storage;
}

PHPX_METHOD(queueInit){
    QueueObject *queue = emalloc(sizeof(QueueObject));

    queue->storage = ecalloc(DEFAULT_QUEUE_SIZE, sizeof(Variant));

    _this->oSet("queue_ptr", "queue_ptr_resource", queue);
}

PHPX_EXTENSION() {
    Extension *extension = new Extension("queue", "0.0.1");

    extension->onStart = [extension]() noexcept {
        extension->registerConstant("QUEUE_VERSION", 1001);

        Class *c = new Class("Queue");
        c->addMethod(PHPX_ME(Queue, queueInit), CONSTRUCT);

        extension->registerClass(c);
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