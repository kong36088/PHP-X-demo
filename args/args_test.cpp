#include "args_test.h"

using namespace php;
using namespace std;

void printArgs(Args &args){
    cout << "Args: ";
    for (unsigned int i = 0; i <args.count(); i++)
    {
        if (args[i].type() == IS_ARRAY)
        {
            Array arr(args[i]);
            cout << '[';
            for (auto it = arr.begin(); it != arr.end(); it++)
            {
                cout << it.value().toString();
            }
            cout << ']' << ' ';
        }
        else
        {
            cout << args[i].toString() << ' ';
        }
    }
    cout << endl;
}

PHPX_METHOD(ArgsTest,noneArgs){
    printArgs(args);
    cout << "ArgsTest::noneArgs() called" << endl;
}

PHPX_METHOD(ArgsTest,oneArgs){
    printArgs(args);

    cout << "ArgsTest::oneArgs() called" << endl;
}

PHPX_METHOD(ArgsTest,twoArgs){
    printArgs(args);
    zval *v1, *v2;
    zend_execute_data *ex_data = EG(current_execute_data);
    if (zend_parse_parameters(ZEND_CALL_NUM_ARGS(ex_data), "zz", v1, v2) == FAILURE) {
        return;
	}

    cout << "ArgsTest::twoArgs() called" << endl;
}

PHPX_METHOD(ArgsTest,threeArgs){
    printArgs(args);

    cout << "ArgsTest::threeArgs() called" << endl;
}

PHPX_FUNCTION(fnTest1){
    printArgs(args);

    cout << "fnTest1() called" << endl;
}

PHPX_FUNCTION(fnTest2){
    printArgs(args);

    cout << "fnTest2() called" << endl;
}

PHPX_EXTENSION() {
    Extension *extension = new Extension("args_test", "0.0.1");

    extension->registerFunction(PHPX_FN(fnTest1));

    ArgInfo *fnt2argi = new ArgInfo(1);
    fnt2argi->add("para1");
    fnt2argi->add("para2");
    extension->registerFunction(PHPX_FN(fnTest2), fnt2argi);

    extension->onStart = [extension]() noexcept {
        Class *c = new Class("ArgsTest");
        ArgInfo *nargi = new ArgInfo(0);
        c->addMethod(PHPX_ME(ArgsTest, noneArgs), PUBLIC, nargi);

        ArgInfo *oargi = new ArgInfo(1);
        oargi->add("para1", nullptr, 0, false, false);
        c->addMethod(PHPX_ME(ArgsTest, oneArgs), PUBLIC, oargi);

        ArgInfo *targi = new ArgInfo(2);
        targi->add("para1", nullptr, 0, false, false);
        targi->add("para2", nullptr, 0, false, false);
        c->addMethod(PHPX_ME(ArgsTest, twoArgs), PUBLIC, targi);

        ArgInfo *thargi = new ArgInfo(2);
        thargi->add("para1");
        thargi->add("para2");
        thargi->add("para3");  //根据ArgInfo->required_num,会对参数是否允许为空进行自动标记
        c->addMethod(PHPX_ME(ArgsTest, threeArgs), PUBLIC, thargi);
        extension->registerClass(c);
    };

    //extension->onShutdown = [extension]() noexcept {
    //};

    //extension->onBeforeRequest = [extension]() noexcept {
    //    cout << extension->name << "beforeRequest" << endl;
    //};

    //extension->onAfterRequest = [extension]() noexcept {
    //    cout << extension->name << "afterRequest" << endl;
    //};

    extension->info({"args_test support", "enabled"},
                    {
                        {"author", "Jiang Weilong"},
                        {"version", extension->version},
                        {"date", "2017-11-26"},
                    });

    return extension;
}