/**
 * Copyright (C) 2012-2014 Laurent Zubiaur
 *
 * All Rights Reserved.
 *
 * @file:   AdMobProvider.java
 * @author: Laurent Zubiaur
 * @brief: 
 *
 */

package com.voodoocactus.games;

import com.google.android.gms.ads.*;
import android.app.Activity;
import android.util.Log;
import android.os.Handler;

/// API Reference
/// http://developer.android.com/reference/com/google/android/gms/ads/InterstitialAd.html

public class AdMobProvider extends AdListener implements IAdProvider {

    private InterstitialAd interstitial = null;
    private Activity activity = null;
    private AdController controller = null;
    private Handler handler = null;

    public AdMobProvider(Activity activity,AdController controller) {
        this.activity = activity;
        this.controller = controller;
        this.handler = new Handler();
        createAndLoadInterstitial();
    }

    /// Create the interstitial.
    public void createAndLoadInterstitial() {
        interstitial = new InterstitialAd(activity);
        interstitial.setAdUnitId("ca-app-pub-2871585208249973/4724879247");
        interstitial.setAdListener(this);
        /// Create ad request.
        AdRequest adRequest = new AdRequest.Builder().build();
        /// Begin loading your interstitial.
        interstitial.loadAd(adRequest);
    }

    public void scheduleCreateAndLoadInterstitial() {
        handler.postDelayed(new Runnable(){
            @Override
            public void run() {
                createAndLoadInterstitial();
            }
        }, 5000);
    }

    /// implements IAdProvider
    public boolean show() {
        if (interstitial.isLoaded()) {
            interstitial.show();
            return true;
        }
        if (BuildConfig.DEBUG) {
            Log.d("cocos2d-x","AdMob not availalble");
        }
        return false;
    }

    public void onActivityResumed() {
        createAndLoadInterstitial();
    }

    public void onActivityPaused() {
        /// NA
    }

    /// AdListener
    @Override
    public void onAdFailedToLoad(int errorCode) {
        if (BuildConfig.DEBUG) {
            Log.d("cocos2d-x","adMob error: "+errorCode);
        }
        scheduleCreateAndLoadInterstitial();
    }

    @Override
    public void onAdOpened() {
        this.controller.notifyAdEvent("adsWillShow");
    }

    @Override
    public void onAdClosed () {
        this.controller.notifyAdEvent("adsWillHide");
        /// Since the interstitial can only be used once we have to create a new instance.
        createAndLoadInterstitial();
    }
}
