/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef SYSLOG_H_
#define SYSLOG_H_

#ifdef __ANDROID_TRACE__
#include <jni.h>
#include <android/log.h>
#define SYSLOG(...) __android_log_print(ANDROID_LOG_INFO, "MoSync Syscall", __VA_ARGS__)
#else
#define SYSLOG(...)
#endif

#endif /* SYSLOG_H_ */
