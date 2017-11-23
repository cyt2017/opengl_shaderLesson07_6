#include "myshaderbillboard.h"

MyShaderBillboard::MyShaderBillboard()
{
    _pos        =   -1;
    _uv         =   -1;
    _normal     =   -1;
    _tagenl     =   -1;
    _biTagenl   =   -1;

    _MVP        =   -1;
    _matModel   =   -1;
    _texture    =   -1;
    _texture1   =   -1;
    _cameraPos  =   -1;
}

MyShaderBillboard::~MyShaderBillboard()
{

}

void MyShaderBillboard::initialize()
{
    const char* vs =
    {
       "uniform     mat4    _mvp; \n\
        uniform     mat4    _model;\n\
        uniform     mat4    _matNormal;\n\
        uniform     vec3    _cameraPos;\n\
        attribute   vec3    _position;\n\
        attribute   vec2    _uv;\n\
        attribute   vec3    _normal;\n\
        attribute   vec3    _biTagent;\n\
        attribute   vec3    _tagent;\n\
        varying     vec2    _outUV;\n\
        varying     vec3    _eyeDir;\n\
        varying     mat3    _tbn;\n\
        void main(void) \n\
        {\n\
          vec3    pos     =   (_model * vec4(_position, 0.0)).xyz;\n\
          vec3    invEye  =   (_matNormal * vec4(_cameraPos, 0.0)).xyz;\n\
          vec3    eye     =   invEye - pos;\n\
          vec3    n       =   normalize(_normal);\n\
          vec3    t       =   normalize(_tagent);\n\
          vec3    b       =   normalize(_biTagent);\n\
          _tbn        =   mat3(t,b,n);\n\
          _eyeDir.x   =   dot(t, eye);\n\
          _eyeDir.y   =   dot(b, eye);\n\
          _eyeDir.z   =   dot(n, eye);\n\
          _eyeDir     =   normalize(_eyeDir);\n\
          _outUV      =   _uv;\n\
          gl_Position =   _mvp * vec4(_position, 1.0);\n\
        }"
    };
    const char* ps =
    {
       "precision   lowp        float;\n\
        uniform     samplerCube _texture;\n\
        uniform     sampler2D   _texture1;\n\
        varying     vec2        _outUV;\n\
        varying     vec3        _eyeDir;\n\
        varying     mat3        _tbn;\n\
        void main(void)\n\
        {\n\
          vec3    normal      =   _tbn * (texture2D(_texture1, _outUV) * 2.0 - 1.0).rgb;\n\
          vec3    ref         =   reflect(_eyeDir, normal);\n\
          vec4    envColor    =   textureCube(_texture, ref);\n\
          gl_FragColor        =   envColor;\n\
        }"
    };

    bool    res =   createProgram(vs, ps);
    if(res)
    {
        _pos        =   glGetAttribLocation(_programId, "_position");
        _uv         =   glGetAttribLocation(_programId, "_uv");
        _normal     =   glGetAttribLocation(_programId, "_normal");
        _tagenl     =   glGetAttribLocation(_programId, "_tagenl");
        _biTagenl   =   glGetAttribLocation(_programId, "_biTagenl");

        _MVP        =   glGetUniformLocation(_programId, "_mvp");
        _matModel   =   glGetUniformLocation(_programId, "_model");
        _matNormal  =   glGetUniformLocation(_programId, "_invModel");
//        _lightDir   =   glGetUniformLocation(_programId, "_lightPos");
        _cameraPos  =   glGetUniformLocation(_programId, "_cameraPos");
        _texture    =   glGetUniformLocation(_programId, "_texture");
        _texture1   =   glGetUniformLocation(_programId, "_texture1");
//        _height     =   glGetUniformLocation(_programId, "_height");
    }

}

void MyShaderBillboard::begin()
{
    glUseProgram(_programId);
    glEnableVertexAttribArray(_pos);
    glEnableVertexAttribArray(_uv);
    glEnableVertexAttribArray(_normal);
    glEnableVertexAttribArray(_tagenl);
    glEnableVertexAttribArray(_biTagenl);
}

void MyShaderBillboard::end()
{
    glDisableVertexAttribArray(_pos);
    glDisableVertexAttribArray(_uv);
    glDisableVertexAttribArray(_normal);
    glDisableVertexAttribArray(_tagenl);
    glDisableVertexAttribArray(_biTagenl);
    glUseProgram(0);
}
