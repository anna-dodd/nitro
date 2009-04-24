/* =========================================================================
 * This file is part of NITRO
 * =========================================================================
 *
 * (C) Copyright 2004 - 2008, General Dynamics - Advanced Information Systems
 *
 * NITRO is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

#include <import/nitf.h>
#include <stdio.h>
#include "nitf_IOInterface.h"
#include "nitf_JNI.h"


NITF_JNI_DECLARE_OBJ(nitf_IOInterface)


typedef struct _IOInterfaceImpl
{
    jobject self;
} IOInterfaceImpl;



NITFPRIV(NITF_BOOL) IOInterfaceImpl_read(NITF_DATA* data,
                                         char* buf,
                                         size_t size,
                                         nitf_Error* error)
{
    jclass  ioClass = NULL;
    jmethodID methodID = NULL;
    IOInterfaceImpl *impl = NULL;
    JNIEnv *env = NULL;
    JavaVM *vm = NULL;
    int detach;
    jbyteArray byteArray;

    /* cast it to the structure we know about */
    impl = (IOInterfaceImpl *) data;
    detach = _GetJNIEnv(&vm, &env);

    byteArray = (*env)->NewByteArray(env, size);
    (*env)->SetByteArrayRegion(env, byteArray, 0, size, buf);

    ioClass = (*env)->GetObjectClass(env, impl->self);
    methodID = (*env)->GetMethodID(env, ioClass, "read", "([BI)V");
    (*env)->CallVoidMethod(env, impl->self, methodID, byteArray, (jint)size);

    (*env)->ReleaseByteArrayElements(env, byteArray, buf, 0);

    if (detach)
        (*vm)->DetachCurrentThread(vm);
    return NITF_SUCCESS;
}

NITFPRIV(NITF_BOOL) IOInterfaceImpl_write(NITF_DATA* data,
                                          const char* buf,
                                          size_t size,
                                          nitf_Error* error)
{
    jclass  ioClass = NULL;
    jmethodID methodID = NULL;
    IOInterfaceImpl *impl = NULL;
    JNIEnv *env = NULL;
    JavaVM *vm = NULL;
    int detach;
    jbyteArray byteArray;

    /* cast it to the structure we know about */
    impl = (IOInterfaceImpl *) data;
    detach = _GetJNIEnv(&vm, &env);

    byteArray = (*env)->NewByteArray(env, size);
    (*env)->SetByteArrayRegion(env, byteArray, 0, size, buf);

    ioClass = (*env)->GetObjectClass(env, impl->self);
    methodID = (*env)->GetMethodID(env, ioClass, "write", "([BI)V");
    (*env)->CallVoidMethod(env, impl->self, methodID, byteArray, (jint)size);

    /*(*env)->ReleaseByteArrayElements(env, byteArray, buf, JNI_COMMIT);*/

    if (detach)
        (*vm)->DetachCurrentThread(vm);
    return NITF_SUCCESS;
}

NITFPRIV(NITF_BOOL) IOInterfaceImpl_seek(NITF_DATA* data,
                                         nitf_Off offset,
                                         int whence,
                                         nitf_Error* error)
{
    jclass  ioClass = NULL;
    jmethodID methodID = NULL;
    IOInterfaceImpl *impl = NULL;
    JNIEnv *env = NULL;
    JavaVM *vm = NULL;
    int detach;
    int jWhence;

    switch(whence)
    {
    case NITF_SEEK_CUR:
        jWhence = nitf_IOInterface_SEEK_CUR;
        break;
    case NITF_SEEK_END:
        jWhence = nitf_IOInterface_SEEK_END;
        break;
    case NITF_SEEK_SET:
        jWhence = nitf_IOInterface_SEEK_SET;
        break;
    default:
        jWhence = nitf_IOInterface_SEEK_SET;
        break;
    }

    /* cast it to the structure we know about */
    impl = (IOInterfaceImpl *) data;
    detach = _GetJNIEnv(&vm, &env);

    ioClass = (*env)->GetObjectClass(env, impl->self);
    methodID = (*env)->GetMethodID(env, ioClass, "seek", "(JI)J");
    (*env)->CallLongMethod(env, impl->self, methodID, offset, jWhence);

    /* TODO check for result ? */

    if (detach)
        (*vm)->DetachCurrentThread(vm);
    return NITF_SUCCESS;
}

NITFPRIV(nitf_Off) IOInterfaceImpl_tell(NITF_DATA* data,
                                     nitf_Error* error)
{
    jclass  ioClass = NULL;
    jmethodID methodID = NULL;
    IOInterfaceImpl *impl = NULL;
    JNIEnv *env = NULL;
    JavaVM *vm = NULL;
    int detach;
    nitf_Off tell;

    /* cast it to the structure we know about */
    impl = (IOInterfaceImpl *) data;
    detach = _GetJNIEnv(&vm, &env);

    ioClass = (*env)->GetObjectClass(env, impl->self);
    methodID = (*env)->GetMethodID(env, ioClass, "tell", "()J");
    tell = (*env)->CallLongMethod(env, impl->self, methodID);

    if (detach)
        (*vm)->DetachCurrentThread(vm);
    return tell;
}

NITFPRIV(nitf_Off) IOInterfaceImpl_getSize(NITF_DATA* data,
                                        nitf_Error* error)
{
    jclass  ioClass = NULL;
    jmethodID methodID = NULL;
    IOInterfaceImpl *impl = NULL;
    JNIEnv *env = NULL;
    JavaVM *vm = NULL;
    int detach;

    /* cast it to the structure we know about */
    impl = (IOInterfaceImpl *) data;
    detach = _GetJNIEnv(&vm, &env);

    ioClass = (*env)->GetObjectClass(env, impl->self);
    methodID = (*env)->GetMethodID(env, ioClass, "getSize", "()J");
    (*env)->CallLongMethod(env, impl->self, methodID);

    if (detach)
        (*vm)->DetachCurrentThread(vm);
    return NITF_SUCCESS;
}

NITFPRIV(NITF_BOOL) IOInterfaceImpl_close(NITF_DATA* data,
                                     nitf_Error* error)
{
    jclass  ioClass = NULL;
    jmethodID methodID = NULL;
    IOInterfaceImpl *impl = NULL;
    JNIEnv *env = NULL;
    JavaVM *vm = NULL;
    int detach;

    /* cast it to the structure we know about */
    impl = (IOInterfaceImpl *) data;
    detach = _GetJNIEnv(&vm, &env);

    ioClass = (*env)->GetObjectClass(env, impl->self);
    methodID = (*env)->GetMethodID(env, ioClass, "close", "()V");
    (*env)->CallVoidMethod(env, impl->self, methodID);

    if (detach)
        (*vm)->DetachCurrentThread(vm);
    return NITF_SUCCESS;
}

NITFPRIV(void) IOInterfaceImpl_destruct(NITF_DATA* data)
{
}

JNIEXPORT void JNICALL Java_nitf_IOInterface_construct
(JNIEnv *env, jobject self)
{
    static nitf_IIOInterface iIOHandle =
    {
        &IOInterfaceImpl_read,
        &IOInterfaceImpl_write,
        &IOInterfaceImpl_seek,
        &IOInterfaceImpl_tell,
        &IOInterfaceImpl_getSize,
        &IOInterfaceImpl_close,
        &IOInterfaceImpl_destruct,
    };
    IOInterfaceImpl* impl = NULL;
    nitf_IOInterface* interface = NULL;

    if (!(impl = (IOInterfaceImpl*)NITF_MALLOC(sizeof(IOInterfaceImpl))))
    {
        _ThrowNITFException(env, "Out of memory");
        return;
    }

    /**************************************************************/
    /* THIS IS VERY IMPORTANT... WE MUST MAKE A STRONG GLOBAL REF */
    /**************************************************************/
    impl->self = (*env)->NewGlobalRef(env, self);

    if (!(interface = ((nitf_IOInterface*)NITF_MALLOC(sizeof(nitf_IOInterface)))))
    {
        _ThrowNITFException(env, "Out of memory");
        return;
    }

    interface->data = (NITF_DATA*)impl;
    interface->iface = &iIOHandle;
    _SetObj(env, self, interface);

    /* Track the IOInterface ... */
    {
        /* Only register non-native, since they are handled differently */
        jclass nativeIOClass = (*env)->FindClass(env, "nitf/NativeIOInterface");
        if (!(*env)->IsInstanceOf(env, self, nativeIOClass))
        {
            jclass managerClass = (*env)->FindClass(env, "nitf/NITFResourceManager");
            jmethodID methodID = (*env)->GetStaticMethodID(env, managerClass,
                    "getInstance", "()Lnitf/NITFResourceManager;");
            jobject manager = (*env)->CallStaticObjectMethod(env, managerClass, methodID);

            methodID = (*env)->GetMethodID(env, managerClass,
                    "trackIOHandle", "(Lnitf/IOInterface;)V");
            (*env)->CallVoidMethod(env, manager, methodID, self);
        }
    }
}

JNIEXPORT void JNICALL Java_nitf_IOInterface_destructMemory
(JNIEnv *env, jobject self)
{
    nitf_IOInterface *interface = _GetObj(env, self);
    if (interface)
        nitf_IOInterface_destruct(&interface);
    _SetObj(env, self, NULL);
}