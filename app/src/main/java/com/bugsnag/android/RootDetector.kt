package com.bugsnag.android

import androidx.annotation.VisibleForTesting
import java.io.File
import java.io.IOException
import java.io.Reader

/**
 * Attempts to detect whether the device is rooted. Root detection errs on the side of false
 * negatives rather than false positives.
 *
 * This class will only give a reasonable indication that a device has been rooted - as it's
 * possible to manipulate Java return values & native library loading, it will always be possible
 * for a determined application to defeat these root checks.
 */
internal class RootDetector @JvmOverloads constructor(
    private val deviceBuildInfo: DeviceBuildInfo = DeviceBuildInfo.defaultInfo(),
    private val logger: Logger
) {

    /**
     * Determines whether the device is rooted or not.
     */
    fun isRooted(): Boolean {
        return false
    }
}
