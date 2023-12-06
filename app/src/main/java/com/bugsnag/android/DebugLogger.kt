package com.bugsnag.android

import android.util.Log

internal object DebugLogger : Logger {

    private const val TAG = "Bugsnag"

    override fun e(msg: String) {
        eu.faircode.email.Log.e(TAG + ": " + msg)
    }

    override fun e(msg: String, throwable: Throwable) {
        eu.faircode.email.Log.e(TAG + ": " + msg, throwable)
    }

    override fun w(msg: String) {
        eu.faircode.email.Log.w(TAG + ": " + msg)
    }

    override fun w(msg: String, throwable: Throwable) {
        eu.faircode.email.Log.w(TAG + ": " + msg, throwable)
    }

    override fun i(msg: String) {
        eu.faircode.email.Log.i(TAG, msg)
    }

    override fun i(msg: String, throwable: Throwable) {
        eu.faircode.email.Log.i(TAG + ": " + msg, throwable)
    }

    override fun d(msg: String) {
        eu.faircode.email.Log.d(TAG + ": " + msg)
    }

    override fun d(msg: String, throwable: Throwable) {
        eu.faircode.email.Log.d(TAG + ": " + msg, throwable)
    }
}
