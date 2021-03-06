#include "phpx.h"

#include <iostream>

using namespace php;
using namespace std;

PHPX_FUNCTION(cpp_ext_test) {
    for (int i = 0; i < args.count(); i++) {
        cout << "值：" << args[i].toString() << endl;
        // cout << args[i].type() << endl;
    }
    retval = nullptr;
}

PHPX_FUNCTION(cpp_ext_test2) {
    for (int i = 0; i < args.count(); i++) {
        cout << args[i].type() << endl;
    }
    auto v1 = args[0];
    Array arr(v1);
    arr.set(1, "efg");
    arr.set(2, 123.11);

    retval = arr;
    // php::echo("argc=%d\n", args.count());
    // php::error(E_WARNING, "extension warning.");
}

PHPX_METHOD(myClass, test) {
    cout << "myClass::test" << endl;
    retval = 1234.56;
}

PHPX_METHOD(myClass, pget) {
    String *str = _this.oGet<String>("resource", "ResourceString");
    cout << "ResourceString: " << str->c_str() << "Length:" << str->length() << endl;
}
PHPX_METHOD(myClass, pset) {
    _this.oSet("resource", "ResourceString", new String("hello world"));
}

PHPX_METHOD(myClass,argTest) {
    for (int i = 0; i < args.count();i++){
        cout << "para:" << args[i].toString() << endl;
    }
    retval = "argTest called";
}

//resource的ptr内容强转为stirng，然后删除
//这里应该对resouce进行操作转换
void string_dtor(zend_resource *res) {
    String *s = static_cast<String *>(res->ptr);
    delete s;
}

PHPX_METHOD(myClass, getClassName) {
    retval = Variant(_this.getClassName().c_str());
}

PHPX_EXTENSION() {
    Extension *extension = new Extension("cpp_ext", "0.0.1");

    extension->onStart = [extension]() noexcept {
        extension->registerConstant("CPP_EXT_VERSION", 1002);

        Class *c = new Class("myClass");
        c->addMethod(PHPX_ME(myClass, test), STATIC);

        c->addMethod(PHPX_ME(myClass, pget));
        c->addMethod(PHPX_ME(myClass, pset));
        c->addMethod(PHPX_ME(myClass, getClassName), PUBLIC);
        //argTest
        c->addMethod(PHPX_ME(myClass, argTest));

        extension->registerClass(c);

        extension->registerResource("ResourceString", string_dtor);
    };

    extension->onShutdown = [extension]() noexcept {
        cout << extension->name << "shutdown" << endl;
    };

    extension->onBeforeRequest = [extension]() noexcept {
        cout << extension->name << "beforeRequest" << endl;
    };

    extension->onAfterRequest = [extension]() noexcept {
        cout << extension->name << "afterRequest" << endl;
    };

    ArgInfo *argInfo = new ArgInfo(2);
    argInfo->add("v1", nullptr, IS_ARRAY);
    argInfo->add("v2");
    extension->registerFunction(PHPX_FN(cpp_ext_test), argInfo);
    extension->registerFunction(PHPX_FN(cpp_ext_test2));

    extension->info({"cpp_ext support", "enabled"},
                    {
                        {"author", "Jiang Weilong"},
                        {"version", extension->version},
                        {"date", "2017-11-23"},
                    });

    return extension;
}
