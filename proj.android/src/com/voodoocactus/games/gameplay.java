/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.voodoocactus.games;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Context;
import android.os.Bundle;
import android.view.KeyEvent;

import android.app.Activity;
import android.net.Uri;
import android.content.Intent;
import android.util.Log;

import com.voodoocactus.games.AdController;
import com.google.android.gms.analytics.*;

/// import android.content.pm.ApplicationInfo;

/// Google Analytics API reference
/// https://developer.android.com/reference/com/google/android/gms/analytics/GoogleAnalytics.html

public class gameplay extends Cocos2dxActivity {
    private static Activity me = null; /// This activity singleton instance
    private AdController adController = null;
    private static final String appId = "UA-55239048-2"; /// Analytics App ID
    private GoogleAnalytics analyticsInstance; /// Analytics instance 
    private Tracker tracker; /// Analytics tracker instance

    /// public static boolean isDebuggable = false;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (BuildConfig.DEBUG) {
            Log.i("cocos2d-x","Running in DEBUG build mode...");
        }
        if (me == null) {
            adController = new AdController(this);
            /// Get the singleton analytics and tracker instance
            analyticsInstance = GoogleAnalytics.getInstance(getApplicationContext());
            tracker = analyticsInstance.newTracker(appId);
            analyticsInstance.setLocalDispatchPeriod(30);
            /// track the page view for this activity
            tracker.setScreenName("/MainActivity");
            tracker.send(new HitBuilders.AppViewBuilder().build());
            me = this;
        } else {
            if (BuildConfig.DEBUG) {
                Log.e("cocos2d-x","Create multiple main activity");
            }
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        adController.onActivityResumed();
    }

    @Override
    protected void onPause() {
        super.onPause();
        adController.onActivityPaused();
    }

    public Tracker getTracker() {
        return tracker;
    }

    public Cocos2dxGLSurfaceView onCreateGLSurfaceView() {
        /// Not working
        /// isDebuggable =  (0 != (getApplicationInfo().flags & ApplicationInfo.FLAG_DEBUGGABLE));
        LuaGLSurfaceView glSurfaceView = new LuaGLSurfaceView(this);
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8); /// Enable OpenGL stencil
        return glSurfaceView;
    }

    /// See Classes/platform/android/native.cpp
    public static void openURL(String url) { 
        Intent i = new Intent(Intent.ACTION_VIEW);  
        i.setData(Uri.parse(url));
        me.startActivity(i);
    }

    public static boolean hideAd() {
        /// Nothing to do because we use interstitial ads
        return true;
    }

    public static boolean showAd() {
        return ((gameplay)me).adController.showAd();
    }

    static {
        System.loadLibrary("cocos2dlua");
    }
}

class LuaGLSurfaceView extends Cocos2dxGLSurfaceView{
	
	public LuaGLSurfaceView(Context context){
		super(context);
	}
	
        public boolean onKeyDown(int keyCode, KeyEvent event) {
            // exit program when key back is entered
            if (keyCode == KeyEvent.KEYCODE_BACK) {
                android.os.Process.killProcess(android.os.Process.myPid());
            }
            return super.onKeyDown(keyCode, event);
    }
}
