#include <jni.h>
#include <android/log.h>
#include <cstdio>

#include <errno.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <unistd.h>

#include "compact_enc_det/compact_enc_det.h"
#include "cld_3/src/nnet_language_identifier.h"

void log_android(int prio, const char *fmt, ...) {
    if (prio >= ANDROID_LOG_DEBUG) {
        char line[1024];
        va_list argptr;
        va_start(argptr, fmt);
        vsprintf(line, fmt, argptr);
        __android_log_print(prio, "fairemail.jni", "%s", line);
        va_end(argptr);
    }
}

extern "C"
JNIEXPORT jint JNICALL
Java_eu_faircode_email_Log_jni_1get_1int(JNIEnv *env, jclass clazz, jint value) {
    return value;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_eu_faircode_email_Log_jni_1get_1string(JNIEnv *env, jclass clazz, jstring value) {
    return value;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_Log_jni_1get_1object(JNIEnv *env, jclass clazz, jobject value) {
    return value;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_eu_faircode_email_Log_jni_1throwable_1get_1message(JNIEnv *env, jclass clazz,
                                                        jthrowable ex) {
    jclass cls = env->FindClass("java/lang/Throwable");
    jmethodID mid = env->GetMethodID(cls, "getMessage", "()Ljava/lang/String;");
    return (jstring) env->CallObjectMethod(ex, mid);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_eu_faircode_email_Log_jni_1throwable_1to_1string(JNIEnv *env, jclass clazz,
                                                      jthrowable ex) {
    jclass cls = env->FindClass("java/lang/Throwable");
    jmethodID mid = env->GetMethodID(cls, "toString", "()Ljava/lang/String;");
    return (jstring) env->CallObjectMethod(ex, mid);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_eu_faircode_email_Log_jni_1throwable_1get_1stack_1trace(JNIEnv *env, jclass clazz,
                                                             jthrowable ex) {
    jclass cls = env->FindClass("android/util/Log");
    jmethodID mid = env->GetStaticMethodID(cls, "getStackTraceString",
                                           "(Ljava/lang/Throwable;)Ljava/lang/String;");
    return (jstring) env->CallStaticObjectMethod(cls, mid, ex);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_eu_faircode_email_Log_jni_1uri_1to_1string(JNIEnv *env, jclass clazz,
                                                jobject uri) {
    jclass cls = env->FindClass("android/net/Uri");
    jmethodID mid = env->GetMethodID(cls, "toString", "()Ljava/lang/String;");
    return (jstring) env->CallObjectMethod(uri, mid);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_eu_faircode_email_Log_jni_1file_1mkdirs(JNIEnv *env, jclass clazz,
                                             jobject file) {
    jclass cls = env->FindClass("java/io/File");
    jmethodID mid = env->GetMethodID(cls, "mkdirs", "()Z");
    return (jboolean) env->CallBooleanMethod(file, mid);
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_Log_jni_1stream_1write(JNIEnv *env, jclass clazz,
                                              jobject os, jbyteArray data) {
    jclass cls = env->FindClass("java/io/OutputStream");
    jmethodID mid = env->GetMethodID(cls, "write", "([B)V");
    env->CallVoidMethod(os, mid, data);
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_Log_jni_1stream_1writer_1write_1char(JNIEnv *env, jclass clazz, jobject writer, jint data) {
    jclass cls = env->FindClass("java/io/OutputStreamWriter");
    jmethodID mid = env->GetMethodID(cls, "write", "(I)V");
    env->CallVoidMethod(writer, mid, data);
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_Log_jni_1char_1array_1writer_1write_1int(JNIEnv *env, jclass clazz, jobject writer, jint data) {
    jclass cls = env->FindClass("java/io/CharArrayWriter");
    jmethodID mid = env->GetMethodID(cls, "write", "(I)V");
    env->CallVoidMethod(writer, mid, data);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_Log_jni_1new_1xml_1transformer(JNIEnv *env, jclass clazz, jobject factory) {
    jclass cls = env->FindClass("javax/xml/transform/TransformerFactory");
    jmethodID mid = env->GetMethodID(cls, "newTransformer", "()Ljavax/xml/transform/Transformer;");
    return env->CallObjectMethod(factory, mid);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_Log_jni_1runtime_1exec(JNIEnv *env, jclass clazz,
                                              jobject runtime, jobjectArray cmd) {
    jclass cls = env->FindClass("java/lang/Runtime");
    jmethodID mid = env->GetMethodID(cls, "exec", "([Ljava/lang/String;)Ljava/lang/Process;");
    return env->CallObjectMethod(runtime, mid, cmd);
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_DB_jni_1db_1exec(JNIEnv *env, jclass clazz,
                                        jobject db,
                                        jstring sql) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "execSQL", "(Ljava/lang/String;)V");
    env->CallVoidMethod(db, mid, sql);
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_DB_jni_1db_1exec_1args(JNIEnv *env, jclass clazz,
                                              jobject db,
                                              jstring sql, jobjectArray args) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "execSQL", "(Ljava/lang/String;[Ljava/lang/Object;)V");
    env->CallVoidMethod(db, mid, sql, args);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_DB_jni_1db_1compile_1statement(JNIEnv *env, jclass clazz,
                                                      jobject db,
                                                      jstring sql) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "compileStatement",
                                     "(Ljava/lang/String;)Landroidx/sqlite/db/SupportSQLiteStatement;");
    return env->CallObjectMethod(db, mid, sql);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_DB_jni_1db_1query(JNIEnv *env, jclass clazz,
                                         jobject db,
                                         jstring sql) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "query", "(Ljava/lang/String;)Landroid/database/Cursor;");
    return env->CallObjectMethod(db, mid, sql);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_DB_jni_1db_1query_1args(JNIEnv *env, jclass clazz,
                                               jobject db,
                                               jstring sql, jobjectArray args) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "query", "(Ljava/lang/String;[Ljava/lang/Object;)Landroid/database/Cursor;");
    return env->CallObjectMethod(db, mid, sql, args);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_DB_jni_1db_1query_1query(JNIEnv *env, jclass clazz,
                                                jobject db, jobject query) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "query",
                                     "(Landroidx/sqlite/db/SupportSQLiteQuery;)Landroid/database/Cursor;");
    return env->CallObjectMethod(db, mid, query);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_DB_jni_1db_1query_1query_1signal(JNIEnv *env, jclass clazz,
                                                        jobject db,
                                                        jobject query, jobject signal) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "query",
                                     "(Landroidx/sqlite/db/SupportSQLiteQuery;Landroid/os/CancellationSignal;)Landroid/database/Cursor;");
    return env->CallObjectMethod(db, mid, query, signal);
}

extern "C"
JNIEXPORT jint JNICALL
Java_eu_faircode_email_DB_jni_1db_1update(JNIEnv *env, jclass clazz,
                                          jobject db, jstring table,
                                          jint conflict_algorithm, jobject cv,
                                          jstring where_clause, jobjectArray where_args) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "update",
                                     "(Ljava/lang/String;ILandroid/content/ContentValues;Ljava/lang/String;[Ljava/lang/Object;)I");
    return env->CallIntMethod(db, mid, table, conflict_algorithm, cv, where_clause, where_args);
}

extern "C"
JNIEXPORT jint JNICALL
Java_eu_faircode_email_DB_jni_1db_1delete(JNIEnv *env, jclass clazz,
                                          jobject db, jstring table,
                                          jstring where_clause, jobjectArray where_args) {
    jclass cls = env->FindClass("androidx/sqlite/db/SupportSQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "delete", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)I");
    return env->CallIntMethod(db, mid, table, where_clause, where_args);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_DB_jni_1db_1simple_1query_1ctor(JNIEnv *env, jclass clazz,
                                                       jstring sql, jobjectArray args) {
    jclass cls = env->FindClass("androidx/sqlite/db/SimpleSQLiteQuery");
    jmethodID ctor = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;[Ljava/lang/Object;)V");
    return env->NewObject(cls, ctor, sql, args);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_DB_jni_1sdb_1query(JNIEnv *env, jclass clazz, jobject db, jstring table, jobjectArray columns,
                                          jstring selection, jobjectArray selection_args, jstring group_by,
                                          jstring having, jstring order_by, jstring limit) {
    jclass cls = env->FindClass("android/database/sqlite/SQLiteDatabase");
    jmethodID mid = env->GetMethodID(cls, "query",
                                     "(Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;");
    return env->CallObjectMethod(db, mid, table, columns, selection, selection_args, group_by, having, order_by, limit);
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_MessageHelper_jni_1mime_1message_1write_1to(JNIEnv *env, jclass clazz,
                                                                   jobject message, jobject os,
                                                                   jobjectArray ignore) {
    jclass cls = env->FindClass("javax/mail/internet/MimeMessage");
    jmethodID mid = env->GetMethodID(cls, "writeTo", "(Ljava/io/OutputStream;[Ljava/lang/String;)V");
    env->CallVoidMethod(message, mid, os, ignore);
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_MessageHelper_jni_1mime_1body_1part_1write_1to(JNIEnv *env, jclass clazz,
                                                                      jobject message, jobject os,
                                                                      jobjectArray ignore_list, jboolean allowutf8) {
    jclass cls = env->FindClass("javax/mail/internet/MimeBodyPart");
    jmethodID mid = env->GetStaticMethodID(cls, "writeTo",
                                           "(Ljavax/mail/internet/MimePart;Ljava/io/OutputStream;[Ljava/lang/String;Z)V");
    env->CallStaticVoidMethod(cls, mid, message, os, ignore_list, allowutf8);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_MessageHelper_jni_1new_1imap_1message(JNIEnv *env, jclass clazz, jobject folder, jint msgnum) {
    jclass cls = env->FindClass("com/sun/mail/imap/IMAPMessage");
    jmethodID ctor = env->GetMethodID(cls, "<init>", "(Lcom/sun/mail/imap/IMAPFolder;I)V");
    return env->NewObject(cls, ctor, folder, msgnum);
}

// -------

extern "C"
JNIEXPORT jint JNICALL
Java_eu_faircode_email_Log_jni_1log(JNIEnv *env, jclass clazz, jint prio, jstring _tag, jstring _msg) {
    const char *tag = env->GetStringUTFChars(_tag, 0);
    const char *msg = env->GetStringUTFChars(_msg, 0);

    __android_log_print(prio, tag, "%s", msg);

    env->ReleaseStringUTFChars(_tag, tag);
    env->ReleaseStringUTFChars(_msg, msg);

    return 1;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_CharsetHelper_jni_1detect_1charset(
        JNIEnv *env, jclass type,
        jbyteArray _octets, jstring _ref, jstring _lang) {
    int len = env->GetArrayLength(_octets);
    jbyte *octets = env->GetByteArrayElements(_octets, nullptr);
    const char *ref = env->GetStringUTFChars(_ref, 0);
    const char *lang = env->GetStringUTFChars(_lang, 0);

    // ISO-8859-1 is unknown
    Encoding encoding_hint;
    EncodingFromName(ref, &encoding_hint);

    Language language_hint;
    LanguageFromCode(lang, &language_hint);

    // https://github.com/google/compact_enc_det

    bool is_reliable;
    int bytes_consumed;

    Encoding encoding = CompactEncDet::DetectEncoding(
            (const char *) octets, len,
            nullptr, nullptr, nullptr,
            encoding_hint,
            language_hint,
            CompactEncDet::EMAIL_CORPUS,
            false,
            &bytes_consumed,
            &is_reliable);
    // TODO: PreferredWebOutputEncoding?
    const char *name = MimeEncodingName(encoding);

    log_android(ANDROID_LOG_DEBUG,
                "detect=%d/%s bytes=%d reliable=%d"
                " ref=%s/%s lang=%s/%s",
                encoding, name, bytes_consumed, is_reliable,
                EncodingName(encoding_hint), ref, LanguageCode(language_hint), lang);

    // https://developer.android.com/training/articles/perf-jni#primitive-arrays
    env->ReleaseByteArrayElements(_octets, octets, JNI_ABORT);
    env->ReleaseStringUTFChars(_ref, ref);
    env->ReleaseStringUTFChars(_lang, lang);

    jclass cls = env->FindClass("eu/faircode/email/CharsetHelper$DetectResult");
    jmethodID ctor = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;IIZ)V");
    jstring jname = env->NewStringUTF(name);
    return env->NewObject(
            cls, ctor,
            jname,
            (jint) len,
            (jint) bytes_consumed,
            (jboolean) is_reliable);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_eu_faircode_email_TextHelper_jni_1detect_1language(
        JNIEnv *env, jclass clazz,
        jbyteArray _octets) {
    int len = env->GetArrayLength(_octets);
    jbyte *octets = env->GetByteArrayElements(_octets, nullptr);

    std::string text(reinterpret_cast<char const *>(octets), len);

    chrome_lang_id::NNetLanguageIdentifier lang_id(0, 1000);
    const chrome_lang_id::NNetLanguageIdentifier::Result result = lang_id.FindLanguage(text);

    env->ReleaseByteArrayElements(_octets, octets, JNI_ABORT);

    jclass cls = env->FindClass("eu/faircode/email/TextHelper$DetectResult");
    jmethodID ctor = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;FZF)V");
    jstring jlanguage = env->NewStringUTF(result.language.c_str());
    return env->NewObject(
            cls, ctor,
            jlanguage,
            (jfloat) result.probability,
            (jint) result.is_reliable,
            (jfloat) result.proportion);
}

extern "C"
JNIEXPORT jint JNICALL
Java_eu_faircode_email_ConnectionHelper_jni_1socket_1keep_1alive(
        JNIEnv *env, jclass clazz,
        jint fd, jint seconds) {
    // https://tldp.org/HOWTO/html_single/TCP-Keepalive-HOWTO/#setsockopt

    int optval;
    socklen_t optlen = sizeof(optval);

    if (getsockopt(fd, SOL_TCP, TCP_KEEPCNT, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Default TCP_KEEPCNT=%d", optval);
    if (getsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Default TCP_KEEPINTVL=%d", optval);
    if (getsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Default TCP_KEEPIDLE=%d", optval);
    if (getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Default SO_KEEPALIVE=%d", optval);

    int res;
    int on = 1;
    int tcp_keepalive_probes = 9;
    int tcp_keepalive_intvl = 75;
    int tcp_keepalive_time = seconds; // default 7200

    log_android(ANDROID_LOG_DEBUG, "Set TCP_KEEPCNT=%d", tcp_keepalive_probes);
    res = setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &tcp_keepalive_probes, sizeof(tcp_keepalive_probes));
    if (res < 0)
        return errno;

    log_android(ANDROID_LOG_DEBUG, "Set TCP_KEEPINTVL=%d", tcp_keepalive_intvl);
    res = setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &tcp_keepalive_intvl, sizeof(tcp_keepalive_intvl));
    if (res < 0)
        return errno;

    log_android(ANDROID_LOG_DEBUG, "Set TCP_KEEPIDLE=%d", tcp_keepalive_time);
    res = setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &tcp_keepalive_time, sizeof(tcp_keepalive_time));
    if (res < 0)
        return errno;

    log_android(ANDROID_LOG_DEBUG, "Set SO_KEEPALIVE=%d", on);
    res = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(on));
    if (res < 0)
        return errno;

    if (getsockopt(fd, SOL_TCP, TCP_KEEPCNT, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Check TCP_KEEPCNT=%d", optval);
    if (getsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Check TCP_KEEPINTVL=%d", optval);
    if (getsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Check TCP_KEEPIDLE=%d", optval);
    if (getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) == 0)
        log_android(ANDROID_LOG_DEBUG, "Check SO_KEEPALIVE=%d", optval);

    return res;
}

extern "C"
JNIEXPORT jint JNICALL
Java_eu_faircode_email_ConnectionHelper_jni_1socket_1get_1send_1buffer(
        JNIEnv *env, jclass clazz,
        jint fd) {
    int queued = 0;
    int res = ioctl(fd, TIOCOUTQ, &queued);
    if (res != 0)
        log_android(ANDROID_LOG_DEBUG, "ioctl(TIOCOUTQ) res=%d queued=%d", res, queued);
    return (res == 0 ? queued : 0);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_eu_faircode_email_ConnectionHelper_jni_1is_1numeric_1address(
        JNIEnv *env, jclass clazz,
        jstring _ip) {
    jboolean numeric = 0;
    const char *ip = env->GetStringUTFChars(_ip, 0);

    // https://linux.die.net/man/3/getaddrinfo
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_NUMERICHOST; // suppresses any potentially lengthy network host address lookups
    struct addrinfo *result;
    int err = getaddrinfo(ip, nullptr, &hints, &result);
    if (err)
        log_android(ANDROID_LOG_DEBUG, "getaddrinfo(%s) error %d: %s", ip, err, gai_strerror(err));
    else
        numeric = (jboolean) (result != nullptr);

    if (result != nullptr)
        freeaddrinfo(result);

    env->ReleaseStringUTFChars(_ip, ip);
    return numeric;
}

extern "C"
JNIEXPORT void JNICALL
Java_eu_faircode_email_Helper_sync(JNIEnv *env, jclass clazz) {
    log_android(ANDROID_LOG_DEBUG, "sync");
    sync();
    log_android(ANDROID_LOG_DEBUG, "synced");
}
