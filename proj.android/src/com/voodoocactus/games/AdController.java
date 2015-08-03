/**
 * Copyright (C) 2012-2014 Laurent Zubiaur
 *
 * All Rights Reserved.
 *
 * @file:   AdController.java
 * @author: Laurent Zubiaur
 * @brief: 
 *
 */

package com.voodoocactus.games;

import java.lang.Runnable;
import android.app.Activity;
import android.util.Log;
import java.util.Vector;

/// Test network connectivity
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.io.UnsupportedEncodingException;
import java.io.InputStreamReader;
import java.io.Reader;

public class AdController {

    private Activity activity = null;
    private Vector<IAdProvider> providers = new Vector<IAdProvider>();

    public AdController(Activity activity) {
        this.activity = activity;
        try {
            providers.add(new AdColonyProvider(activity,this));
            providers.add(new UnityAdsProvider(activity,this));
            providers.add(new AmazonAdsProvider(activity,this));
            providers.add(new AdMobProvider(activity,this));
            /// Test internet connectivity
            /// downloadUrl("http://www.google.com/");
        } catch (Throwable e) {
            if (BuildConfig.DEBUG) {
                Log.e("cocos2d-x","AdController Error",e);
            }
        }
    }

    /// Native C++ method implemented in platform/android/native.cpp
    public static native void notifyAdEvent(String event);

    /// Activity resumed
    public void onActivityResumed() {
        for (IAdProvider ad : providers) 
            ad.onActivityResumed();
    }

    /// Activity paused
    public void onActivityPaused() {
        for (IAdProvider ad : providers) 
            ad.onActivityPaused();
    }

    public boolean showAd() {
        try {
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    for (IAdProvider ad : providers)
                        if (ad.show()) break;
                }
            });
        } catch(Throwable t) {
            if (BuildConfig.DEBUG) {
                Log.e("cocos2d-x","AdController showAd Error",t);
            }
        }
        return true;
    }

    private String downloadUrl(String myurl) throws IOException {
        InputStream is = null;
        // Only display the first 500 characters of the retrieved
        // web page content.
        int len = 500;

        try {
            URL url = new URL(myurl);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setReadTimeout(10000 /* milliseconds */);
            conn.setConnectTimeout(15000 /* milliseconds */);
            conn.setRequestMethod("GET");
            conn.setDoInput(true);
            // Starts the query
            conn.connect();
            int response = conn.getResponseCode();
            if (BuildConfig.DEBUG) {
                Log.d("cocos2d-x", "The response is: " + response);
            }
            is = conn.getInputStream();

            // Convert the InputStream into a string
            String contentAsString = readIt(is, len);
            return contentAsString;

            // Makes sure that the InputStream is closed after the app is
            // finished using it.
        } finally {
            if (is != null) {
                is.close();
            } 
        }
    }

    // Reads an InputStream and converts it to a String.
    public String readIt(InputStream stream, int len) throws IOException, UnsupportedEncodingException {
        Reader reader = null;
        reader = new InputStreamReader(stream, "UTF-8");        
        char[] buffer = new char[len];
        reader.read(buffer);
        return new String(buffer);
    }
}
