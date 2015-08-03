/**
 * Copyright (C) 2012-2014 Laurent Zubiaur
 *
 * All Rights Reserved.
 *
 * @file:   UnityAdsProvider.java
 * @author: Laurent Zubiaur
 * @brief: 
 *
 */

package com.voodoocactus.games;

import android.app.Activity;
import android.util.Log;
import com.unity3d.ads.android.*;

public class UnityAdsProvider implements IUnityAdsListener, IAdProvider {

    private Activity activity = null;
    private AdController controller = null;

    public UnityAdsProvider(Activity activity, AdController controller) {
        this.activity = activity;
        this.controller = controller;
        UnityAds.init(activity, "19042", (IUnityAdsListener)this);
        if (BuildConfig.DEBUG) {
            UnityAds.setDebugMode(true);
            UnityAds.setTestMode(true);
        }
    }

    /// Implements IAdProvider
    public boolean show() {
        if(UnityAds.canShow() && UnityAds.canShowAds()) {
            UnityAds.show();
            return true;
        }
        if (BuildConfig.DEBUG) {
            Log.d("cocos2d-x","UnityAds not available");
        }
        return false;
    }

    public void onActivityResumed() {
        UnityAds.changeActivity(this.activity);
    }

    public void onActivityPaused() {
        /// NA
    }

    /// Implements IUnityAdsListener
    
    // Unity Ads video events
    public void onVideoStarted () {}
    public void onVideoCompleted (String rewardItemKey, boolean skipped) {}
    // Unity Ads campaign events
    public void onFetchCompleted () {}
    public void onFetchFailed() {
        if (BuildConfig.DEBUG) {
            Log.e("cocos2dx","UnityAds Error: fetch failed");
        }
    }
    // Unity Ads view events
    public void onShow() {
        this.controller.notifyAdEvent("adsWillShow");
    }

    public void onHide() {
        this.controller.notifyAdEvent("adsWillHide");
    }
}

