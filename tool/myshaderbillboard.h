#ifndef MYSHADERBILLBOARD_H
#define MYSHADERBILLBOARD_H

#include "tool/programid.h"

class MyShaderBillboard : public ProgramId
{
public:
    MyShaderBillboard();
    ~MyShaderBillboard();

public:
    typedef int attribute;
    typedef int uniform;
public:
    attribute   _pos;
    attribute   _uv;
    attribute   _normal;
    attribute   _tagenl;
    attribute   _biTagenl;

    uniform     _MVP;
    uniform     _matModel;
    uniform     _matNormal;
//    uniform     _lightDir;
    uniform     _cameraPos;
    uniform     _texture;
    uniform     _texture1;
//    uniform     _height;

    /// 初始化函数
    virtual void    initialize();

    /**
    *   使用程序
    */
    virtual void    begin();
    /**
    *   使用完成
    */
    virtual void    end();
};

#endif // MYSHADERBILLBOARD_H
