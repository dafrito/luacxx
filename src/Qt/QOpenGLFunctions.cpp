#include "QOpenGLFunctions.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QOpenGLFunctions>

void lua::QOpenGLFunctions_metatable(const lua::index& mt)
{
    mt["glActiveTexture"] = &QOpenGLFunctions::glActiveTexture;
    mt["glAttachShader"] = &QOpenGLFunctions::glAttachShader;
    mt["glBindAttribLocation"] = &QOpenGLFunctions::glBindAttribLocation;
    mt["glBindBuffer"] = &QOpenGLFunctions::glBindBuffer;
    mt["glBindFramebuffer"] = &QOpenGLFunctions::glBindFramebuffer;
    mt["glBindRenderbuffer"] = &QOpenGLFunctions::glBindRenderbuffer;
    mt["glBlendColor"] = &QOpenGLFunctions::glBlendColor;
    mt["glBlendEquation"] = &QOpenGLFunctions::glBlendEquation;
    mt["glBlendEquationSeparate"] = &QOpenGLFunctions::glBlendEquationSeparate;
    mt["glBlendFuncSeparate"] = &QOpenGLFunctions::glBlendFuncSeparate;
    mt["glBufferData"] = &QOpenGLFunctions::glBufferData;
    mt["glBufferSubData"] = &QOpenGLFunctions::glBufferSubData;
    mt["glCheckFramebufferStatus"] = &QOpenGLFunctions::glCheckFramebufferStatus;
    mt["glClearDepthf"] = &QOpenGLFunctions::glClearDepthf;
    mt["glCompileShader"] = &QOpenGLFunctions::glCompileShader;
    mt["glCompressedTexImage2D"] = &QOpenGLFunctions::glCompressedTexImage2D;
    mt["glCompressedTexSubImage2D"] = &QOpenGLFunctions::glCompressedTexSubImage2D;
    mt["glCreateProgram"] = &QOpenGLFunctions::glCreateProgram;
    mt["glCreateShader"] = &QOpenGLFunctions::glCreateShader;
    mt["glDeleteBuffers"] = &QOpenGLFunctions::glDeleteBuffers;
    mt["glDeleteFramebuffers"] = &QOpenGLFunctions::glDeleteFramebuffers;
    mt["glDeleteProgram"] = &QOpenGLFunctions::glDeleteProgram;
    mt["glDeleteRenderbuffers"] = &QOpenGLFunctions::glDeleteRenderbuffers;
    mt["glDeleteShader"] = &QOpenGLFunctions::glDeleteShader;
    mt["glDepthRangef"] = &QOpenGLFunctions::glDepthRangef;
    mt["glDetachShader"] = &QOpenGLFunctions::glDetachShader;
    mt["glDisableVertexAttribArray"] = &QOpenGLFunctions::glDisableVertexAttribArray;
    mt["glFramebufferRenderbuffer"] = &QOpenGLFunctions::glFramebufferRenderbuffer;
    mt["glFramebufferTexture2D"] = &QOpenGLFunctions::glFramebufferTexture2D;
    mt["glGenBuffers"] = &QOpenGLFunctions::glGenBuffers;
    mt["glGenFramebuffers"] = &QOpenGLFunctions::glGenFramebuffers;
    mt["glGenRenderbuffers"] = &QOpenGLFunctions::glGenRenderbuffers;
    mt["glGenerateMipmap"] = &QOpenGLFunctions::glGenerateMipmap;
    mt["glGetActiveAttrib"] = &QOpenGLFunctions::glGetActiveAttrib;
    mt["glGetActiveUniform"] = &QOpenGLFunctions::glGetActiveUniform;
    mt["glGetAttachedShaders"] = &QOpenGLFunctions::glGetAttachedShaders;
    mt["glGetAttribLocation"] = &QOpenGLFunctions::glGetAttribLocation;
    mt["glGetBufferParameteriv"] = &QOpenGLFunctions::glGetBufferParameteriv;
    mt["glGetFramebufferAttachmentParameteriv"] = &QOpenGLFunctions::glGetFramebufferAttachmentParameteriv;
    mt["glGetProgramInfoLog"] = &QOpenGLFunctions::glGetProgramInfoLog;
    mt["glGetProgramiv"] = &QOpenGLFunctions::glGetProgramiv;
    mt["glGetRenderbufferParameteriv"] = &QOpenGLFunctions::glGetRenderbufferParameteriv;
    mt["glGetShaderInfoLog"] = &QOpenGLFunctions::glGetShaderInfoLog;
    mt["glGetShaderPrecisionFormat"] = &QOpenGLFunctions::glGetShaderPrecisionFormat;
    mt["glGetShaderSource"] = &QOpenGLFunctions::glGetShaderSource;
    mt["glGetShaderiv"] = &QOpenGLFunctions::glGetShaderiv;
    mt["glGetUniformLocation"] = &QOpenGLFunctions::glGetUniformLocation;
    mt["glGetUniformfv"] = &QOpenGLFunctions::glGetUniformfv;
    mt["glGetUniformiv"] = &QOpenGLFunctions::glGetUniformiv;
    mt["glGetVertexAttribPointerv"] = &QOpenGLFunctions::glGetVertexAttribPointerv;
    mt["glGetVertexAttribfv"] = &QOpenGLFunctions::glGetVertexAttribfv;
    mt["glGetVertexAttribiv"] = &QOpenGLFunctions::glGetVertexAttribiv;
    mt["glIsBuffer"] = &QOpenGLFunctions::glIsBuffer;
    mt["glIsFramebuffer"] = &QOpenGLFunctions::glIsFramebuffer;
    mt["glIsProgram"] = &QOpenGLFunctions::glIsProgram;
    mt["glIsRenderbuffer"] = &QOpenGLFunctions::glIsRenderbuffer;
    mt["glIsShader"] = &QOpenGLFunctions::glIsShader;
    mt["glLinkProgram"] = &QOpenGLFunctions::glLinkProgram;
    mt["glReleaseShaderCompiler"] = &QOpenGLFunctions::glReleaseShaderCompiler;
    mt["glRenderbufferStorage"] = &QOpenGLFunctions::glRenderbufferStorage;
    mt["glSampleCoverage"] = &QOpenGLFunctions::glSampleCoverage;
    mt["glShaderBinary"] = &QOpenGLFunctions::glShaderBinary;
    mt["glShaderSource"] = &QOpenGLFunctions::glShaderSource;
    mt["glStencilFuncSeparate"] = &QOpenGLFunctions::glStencilFuncSeparate;
    mt["glStencilMaskSeparate"] = &QOpenGLFunctions::glStencilMaskSeparate;
    mt["glUniform1f"] = &QOpenGLFunctions::glUniform1f;
    mt["glUniform1fv"] = &QOpenGLFunctions::glUniform1fv;
    mt["glUniform1i"] = &QOpenGLFunctions::glUniform1i;
    mt["glUniform1iv"] = &QOpenGLFunctions::glUniform1iv;
    mt["glUniform2f"] = &QOpenGLFunctions::glUniform2f;
    mt["glUniform2fv"] = &QOpenGLFunctions::glUniform2fv;
    mt["glUniform2i"] = &QOpenGLFunctions::glUniform2i;
    mt["glUniform2iv"] = &QOpenGLFunctions::glUniform2iv;
    mt["glUniform3f"] = &QOpenGLFunctions::glUniform3f;
    mt["glUniform3fv"] = &QOpenGLFunctions::glUniform3fv;
    mt["glUniform3i"] = &QOpenGLFunctions::glUniform3i;
    mt["glUniform3iv"] = &QOpenGLFunctions::glUniform3iv;
    mt["glUniform4f"] = &QOpenGLFunctions::glUniform4f;
    mt["glUniform4fv"] = &QOpenGLFunctions::glUniform4fv;
    mt["glUniform4i"] = &QOpenGLFunctions::glUniform4i;
    mt["glUniform4iv"] = &QOpenGLFunctions::glUniform4iv;
    mt["glUniformMatrix2fv"] = &QOpenGLFunctions::glUniformMatrix2fv;
    mt["glUniformMatrix3fv"] = &QOpenGLFunctions::glUniformMatrix3fv;
    mt["glUniformMatrix4fv"] = &QOpenGLFunctions::glUniformMatrix4fv;
    mt["glUseProgram"] = &QOpenGLFunctions::glUseProgram;
    mt["glValidateProgram"] = &QOpenGLFunctions::glValidateProgram;
    mt["glVertexAttrib1f"] = &QOpenGLFunctions::glVertexAttrib1f;
    mt["glVertexAttrib1fv"] = &QOpenGLFunctions::glVertexAttrib1fv;
    mt["glVertexAttrib2f"] = &QOpenGLFunctions::glVertexAttrib2f;
    mt["glVertexAttrib2fv"] = &QOpenGLFunctions::glVertexAttrib2fv;
    mt["glVertexAttrib3f"] = &QOpenGLFunctions::glVertexAttrib3f;
    mt["glVertexAttrib3fv"] = &QOpenGLFunctions::glVertexAttrib3fv;
    mt["glVertexAttrib4f"] = &QOpenGLFunctions::glVertexAttrib4f;
    mt["glVertexAttrib4fv"] = &QOpenGLFunctions::glVertexAttrib4fv;
    mt["glVertexAttribPointer"] = &QOpenGLFunctions::glVertexAttribPointer;
    mt["hasOpenGLFeature"] = &QOpenGLFunctions::hasOpenGLFeature;
    mt["initializeOpenGLFunctions"] = &QOpenGLFunctions::initializeOpenGLFunctions;
    mt["openGLFeatures"] = &QOpenGLFunctions::openGLFeatures;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    mt["glBindTexture"] = &QOpenGLFunctions::glBindTexture;
    mt["glBlendFunc"] = &QOpenGLFunctions::glBlendFunc;
    mt["glClear"] = &QOpenGLFunctions::glClear;
    mt["glClearColor"] = &QOpenGLFunctions::glClearColor;
    mt["glClearStencil"] = &QOpenGLFunctions::glClearStencil;
    mt["glColorMask"] = &QOpenGLFunctions::glColorMask;
    mt["glCopyTexImage2D"] = &QOpenGLFunctions::glCopyTexImage2D;
    mt["glCopyTexSubImage2D"] = &QOpenGLFunctions::glCopyTexSubImage2D;
    mt["glCullFace"] = &QOpenGLFunctions::glCullFace;
    mt["glDeleteTextures"] = &QOpenGLFunctions::glDeleteTextures;
    mt["glDepthFunc"] = &QOpenGLFunctions::glDepthFunc;
    mt["glDepthMask"] = &QOpenGLFunctions::glDepthMask;
    mt["glDisable"] = &QOpenGLFunctions::glDisable;
    mt["glDrawArrays"] = &QOpenGLFunctions::glDrawArrays;
    mt["glDrawElements"] = &QOpenGLFunctions::glDrawElements;
    mt["glEnable"] = &QOpenGLFunctions::glEnable;
    mt["glEnableVertexAttribArray"] = &QOpenGLFunctions::glEnableVertexAttribArray;
    mt["glFinish"] = &QOpenGLFunctions::glFinish;
    mt["glFlush"] = &QOpenGLFunctions::glFlush;
    mt["glFrontFace"] = &QOpenGLFunctions::glFrontFace;
    mt["glGenTextures"] = &QOpenGLFunctions::glGenTextures;
    mt["glGetBooleanv"] = &QOpenGLFunctions::glGetBooleanv;
    mt["glGetError"] = &QOpenGLFunctions::glGetError;
    mt["glGetFloatv"] = &QOpenGLFunctions::glGetFloatv;
    mt["glGetIntegerv"] = &QOpenGLFunctions::glGetIntegerv;
    mt["glGetString"] = &QOpenGLFunctions::glGetString;
    mt["glGetTexParameterfv"] = &QOpenGLFunctions::glGetTexParameterfv;
    mt["glGetTexParameteriv"] = &QOpenGLFunctions::glGetTexParameteriv;
    mt["glHint"] = &QOpenGLFunctions::glHint;
    mt["glIsEnabled"] = &QOpenGLFunctions::glIsEnabled;
    mt["glIsTexture"] = &QOpenGLFunctions::glIsTexture;
    mt["glLineWidth"] = &QOpenGLFunctions::glLineWidth;
    mt["glPixelStorei"] = &QOpenGLFunctions::glPixelStorei;
    mt["glPolygonOffset"] = &QOpenGLFunctions::glPolygonOffset;
    mt["glReadPixels"] = &QOpenGLFunctions::glReadPixels;
    mt["glScissor"] = &QOpenGLFunctions::glScissor;
    mt["glStencilFunc"] = &QOpenGLFunctions::glStencilFunc;
    mt["glStencilOp"] = &QOpenGLFunctions::glStencilOp;
    mt["glStencilOpSeparate"] = &QOpenGLFunctions::glStencilOpSeparate;
    mt["glStencilMask"] = &QOpenGLFunctions::glStencilMask;
    mt["glTexImage2D"] = &QOpenGLFunctions::glTexImage2D;
    mt["glTexSubImage2D"] = &QOpenGLFunctions::glTexSubImage2D;
    mt["glTexParameterf"] = &QOpenGLFunctions::glTexParameterf;
    mt["glTexParameterfv"] = &QOpenGLFunctions::glTexParameterfv;
    mt["glTexParameteri"] = &QOpenGLFunctions::glTexParameteri;
    mt["glTexParameteriv"] = &QOpenGLFunctions::glTexParameteriv;
    mt["glViewport"] = &QOpenGLFunctions::glViewport;
    #endif
}

int QOpenGLFunctions_new(lua::state* const state)
{
    lua::make<QOpenGLFunctions>(state, lua::get<QOpenGLContext*>(state, 2));
    return 1;
}

int luaopen_luacxx_QOpenGLFunctions(lua::state* const state)
{
    lua::thread env(state);

    env["QOpenGLFunctions"] = lua::value::table;
    env["QOpenGLFunctions"]["new"] = QOpenGLFunctions_new;

    return 0;
}
