# cpp_ext
根据官方提供的example进行进一步的修改测试，写出了这个demo

新增支持Cmake

## Require

`SWOOLE`
`PHP-X`
`PHP >= 7.0`

## 安装使用

```bash
mkdir build
cd build
cmake ..
make && make install
```
or 

```bash
make && make install
```

到`php.ini`添加`extension=cpp_ext.so`