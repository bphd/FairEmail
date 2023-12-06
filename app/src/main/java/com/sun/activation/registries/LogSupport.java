/*
 * Copyright (c) 1997, 2018 Oracle and/or its affiliates. All rights reserved.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Distribution License v. 1.0, which is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

package com.sun.activation.registries;

import java.io.*;
import java.util.logging.*;

/**
 * Logging related methods.
 */
public class LogSupport {
    private static boolean debug = false;
    private static Logger logger;
    private static final Level level = Level.FINE;

    static {
	try {
	    debug = Boolean.getBoolean("javax.activation.debug");
	} catch (Throwable t) {
	    // ignore any errors
	}
	logger = Logger.getLogger("javax.activation");
    }

    /**
     * Constructor.
     */
    private LogSupport() {
	// private constructor, can't create instances
    }

    private static void logRedirect(Level level, String clazz, String method, String msg, Object... params) {
        if (Level.OFF.equals(level))
            return;

        StringBuilder sb = new StringBuilder();
        sb.append("JavaMail: ")
                .append(clazz == null ? "*" : clazz).append(':').append(method == null ? "*" : method)
                .append(' ').append(msg);

        for (Object param : params)
            sb.append(' ').append(param == null ? "<null>" : param.toString());

        int l = (level == null ? 800 : level.intValue());
        if (l >= 1000) // severe
            eu.faircode.email.Log.e(sb.toString());
        else if (l >= 900) // warning
            eu.faircode.email.Log.w(sb.toString());
        else if (l >= 800 || l < 0) // info/all
            eu.faircode.email.Log.i(sb.toString());
        else
            eu.faircode.email.Log.d(sb.toString());
    }

    public static void log(String msg) {
	if (debug)
	    ; //System.out.println(msg);
        logRedirect(level, null, null, msg);
    }

    public static void log(String msg, Throwable t) {
	if (debug)
	    ; //System.out.println(msg + "; Exception: " + t);
        logRedirect(level, null, null, msg, t);
    }

    public static boolean isLoggable() {
	return debug || logger.isLoggable(level);
    }
}
