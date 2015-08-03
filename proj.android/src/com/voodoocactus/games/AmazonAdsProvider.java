/**
 * Copyright (C) 2012-2014 Laurent Zubiaur
 *
 * All Rights Reserved.
 *
 * @file:   AmazonAdsProvider.java
 * @author: Laurent Zubiaur
 * @brief: 
 *
 */

package com.voodoocactus.games;

import com.amazon.device.ads.*;
import android.app.Activity;
import android.util.Log;
import android.os.Handler;

/// Amazon Ads API reference
/// https://developer.amazon.com/public/apis/earn/mobile-ads/javadocs/mobile-ads-api-reference

public class AmazonAdsProvider extends DefaultAdListener implements IAdProvider {

    private InterstitialAd interstitialAd = null;
    private Activity activity = null;
    private AdController controller = null;
    private Handler handler = null;
    private boolean isScheduled = false;

    public AmazonAdsProvider(Activity activity,AdController controller) {
        this.activity = activity;
        this.controller = controller;
        this.handler = new Handler();
        AdRegistration.setAppKey("bbc7d8a2817b433eb39b59e8651debae");
        if (BuildConfig.DEBUG) {
            AdRegistration.enableTesting(true);
            AdRegistration.enableLogging(true);
        }
        createAndLoadInterstitial();
    }

    public void createAndLoadInterstitial() {
        // Create the interstitial.
        this.interstitialAd = new InterstitialAd(this.activity);
        this.interstitialAd.setListener(this);
        this.interstitialAd.loadAd();
    }

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

    /// implements IAdProvider
    public boolean show() {
        if (interstitialAd.showAd()) {
            this.controller.notifyAdEvent("adsWillShow");
            return true;
        }
        if (BuildConfig.DEBUG) {
            Log.d("cocos2d-x","Amazon Ads NOT available...");
        }
        return false;
    }

    public void onActivityPaused() {
        // NA
    }

    public void onActivityResumed() {
        // NA
    }

    /// Implements AdListener
    @Override
    public void onAdFailedToLoad(Ad ad, AdError error) {
        if (BuildConfig.DEBUG) {
            Log.d("cocos2dx","Amazon error " + error.getCode() + ":" + error.getMessage());
        }
        scheduleCreateAndLoadInterstitial();
    }

    @Override
    public void onAdCollapsed(Ad ad) {
        this.controller.notifyAdEvent("adsWillHide");
        createAndLoadInterstitial();
    }

    @Override
    public void onAdDismissed(Ad ad) {
        this.controller.notifyAdEvent("adsWillHide");
        createAndLoadInterstitial();
    }
}
