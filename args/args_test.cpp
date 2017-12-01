using namespace php;
using namespace std;

//其实就是执行ArgInfo做的事情。给zend_internal_arg_info赋值
//ZEND_BEGIN_ARG_INFO_EX(arginfo_args_test, 0, 0, 1)
//	ZEND_ARG_INFO(0, value)
//ZEND_END_ARG_INFO()

PHPX_METHOD(ArgsTest,noneArgs){
    cout << "noneArgs() called" << endl;
}


PHPX_METHOD(ArgsTest,oneArgs){
    //这样去解析参数，如果参数不正确会得到一个warning错误
    //if (zend_parse_parameters(ZEND_CALL_NUM_ARGS(EG(current_execute_data)), "z", &value) == FAILURE) {
	//	return;
	//}
    //TODO 搞清楚args传入的方式

    cout << "oneArgs() called" << endl;
}

PHPX_METHOD(ArgsTest,twoArgs){
    cout << "twoArgs() called" << endl;
}

PHPX_METHOD(ArgsTest,threeArgs){
    cout << "threeArgs() called" << endl;
}

PHPX_EXTENSION() {
    Extension *extension = new Extension("args_test", "0.0.1");

    extension->onStart = [extension]() noexcept {
        Class *c = new Class("ArgsTest");
        c->addMethod(PHPX_ME(ArgsTest, noneArgs), PUBLIC);

        ArgInfo *oargi = new ArgInfo(1);
        oargi->add("para1");
        c->addMethod(PHPX_ME(ArgsTest, oneArgs), PUBLIC, oargi);

        ArgInfo *targi = new ArgInfo(1);
        targi->add("para1");
        targi->add("para2", nullptr, 0, false, true);
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