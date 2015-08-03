/**
 * Copyright (C) 2012-2014 Laurent Zubiaur
 *
 * All Rights Reserved.
 *
 * @file:   AdColonyProvider.java
 * @author: Laurent Zubiaur
 * @brief: 
 *
 */

package com.voodoocactus.games;

import com.jirbo.adcolony.*;
import android.app.Activity;
import android.util.Log;
import android.os.Handler;

/// Amazon Ads API reference
/// https://developer.amazon.com/public/apis/earn/mobile-ads/javadocs/mobile-ads-api-reference

public class AdColonyProvider implements IAdProvider, AdColonyAdListener {

    private Activity activity = null;
    private AdController controller = null;
    private Handler handler = null;
    /// private boolean isScheduled = false;
    private AdColonyVideoAd interstitial = null;
    private static final String app_id = "app717706b82b784200a4";
    private static final String zone_id = "vzd529db2e4d0d462493";
    private static final String client_options = "version:1.1,store:google";

    public AdColonyProvider(Activity activity,AdController controller) {
        this.activity = activity;
        this.controller = controller;
        this.handler = new Handler();
        AdColony.configure(this.activity, client_options, app_id, zone_id);
        createAndLoadInterstitial();
    }

    public void createAndLoadInterstitial() {
        interstitial = new AdColonyVideoAd(zone_id);
        interstitial.withListener(this);
    }

    /*
    public void scheduleCreateAndLoadInterstitial() {
        if (this.isScheduled == false) {
            this.isScheduled = true;
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    isScheduled = false;
                    createAndLoadInterstitial();
                }
            }, 10000);
        }
    }
    */

    /// implements IAdProvider
    public boolean show() {
        if (interstitial.isReady()) {
            interstitial.show();
            return true;
        }
        if (BuildConfig.DEBUG) {
            Log.d("cocos2d-x","AdColony Ads NOT available.");
        }
        return false;
    }

    public void onActivityResumed() {
        AdColony.resume(this.activity); 
    }

    public void onActivityPaused() {
        AdColony.pause();
    }

    /// implements AdColonyAdListener
    public void onAdColonyAdStarted(AdColonyAd ad) {
        this.controller.notifyAdEvent("adsWillShow");
    }

    public void onAdColonyAdAttemptFinished(AdColonyAd ad) {
        this.controller.notifyAdEvent("adsWillHide");
    }
}
