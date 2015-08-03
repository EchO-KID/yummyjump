#import "BannerViewController.h"
#include "native.h"

#import <GADInterstitial.h>

#import <AmazonAd/AmazonAdRegistration.h>
#import <AmazonAd/AmazonAdInterstitial.h>
#import <AmazonAd/AmazonAdOptions.h>

/* InMobi Now included as a google adMob mediation
#import "IMInterstitial.h"
#import "IMError.h"
*/

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

@interface BannerViewController ()

@end

@implementation BannerViewController {

    /// GADBannerView *_bannerView;
    UIViewController *_contentController;

    /// IMInterstitial *inMobiAd;
    GADInterstitial *adMobAd;
}

@synthesize amazonAd;

- (instancetype)initWithContentViewController:(UIViewController *)contentController
{
    self = [super init];
    if (self != nil) {
        _contentController = contentController;

        //////////////////////////// AdColony ////////////////////////////

        [AdColony configureWithAppID:@"appd5013b5a0699433e88"
                             zoneIDs:@[@"vz160b599e916443ab8e"]
                            delegate:nil
                             logging:YES];

        //////////////////////////// AdMob ////////////////////////////
        self->adMobAd = [self createAndLoadInterstitial];

        //////////////////////////// InMobi ////////////////////////////
        /*
        self->inMobiAd = [[IMInterstitial alloc] initWithAppId:@"e0dec157829e47429bcddb789a748b93"];
        self->inMobiAd.delegate = self;
        [self->inMobiAd loadInterstitial];
        */

        //////////////////////////// UnityAds ////////////////////////////
        [[UnityAds sharedInstance] setDelegate:self];
#ifdef DEBUG
        // TEST MODE: Do not use in production apps
        [[UnityAds sharedInstance] setTestMode:YES];
        [[UnityAds sharedInstance] setDebugMode:YES];
#endif
        [[UnityAds sharedInstance] startWithGameId:@"18143" andViewController:_contentController];

        //////////////////////////// Amazon ////////////////////////////
        if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"6.0")) {
            [[AmazonAdRegistration sharedRegistration] setAppKey:@"572132e7061b4c9180353c737c207e0b"];
            amazonAd = [AmazonAdInterstitial amazonAdInterstitial];
            [amazonAd retain];
#ifdef DEBUG
            AmazonAdOptions *options = [AmazonAdOptions options];
            options.isTestRequest = YES;
            [self.amazonAd load:options];
#endif
        }
    }
    return self;
}

- (GADInterstitial *)createAndLoadInterstitial {
    GADInterstitial *interstitial = [[GADInterstitial alloc] init];
    interstitial.adUnitID = @"ca-app-pub-2871585208249973/8380656441";
    interstitial.delegate = self;
    [interstitial loadRequest:[GADRequest request]];
    return interstitial;
}

//////////////////////////// AdMob Delegate ////////////////////////////
- (void)interstitialWillPresentScreen:(GADInterstitial *)ad {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillShow");
}

- (void)interstitialWillDismissScreen:(GADInterstitial *)ad {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillHide");
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)interstitial {
    self->adMobAd = [self createAndLoadInterstitial];
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad {
    NSLog(@"GADInterstial: Received ads");
}

-(void)refreshAdMod {
    self->adMobAd = [self createAndLoadInterstitial];
}

- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"GADInterstial: Error: %@",error);
    /// TODO Check error code before creating the timer
    [NSTimer scheduledTimerWithTimeInterval:5.0
                                     target:self
                                   selector:@selector(refreshAdMod)
                                   userInfo:nil
                                    repeats:NO];
}

//////////////////////////// UnityAds Delegate ////////////////////////////

- (void)unityAdsWillShow {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillShow");
}

- (void)unityAdsWillHide {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillHide");
}

- (void)unityAdsVideoCompleted:(NSString *)rewardItemKey skipped:(BOOL)skipped {
	// NSLog(@"unityAdsVideoCompleted:rewardItemKey:skipped -- key: %@ -- skipped: %@", rewardItemKey, skipped ? @"true" : @"false");
}

//////////////////////////// AmazonAd Delegate ////////////////////////////

- (void)interstitialWillPresent:(AmazonAdInterstitial *)interstitial {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillShow");
}

- (void)interstitialWillDismiss:(AmazonAdInterstitial *)interstitial {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillHide");
}

//////////////////////////// AdColony Delegate ////////////////////////////

- ( void ) onAdColonyAdAvailabilityChange:(BOOL)available inZone:(NSString*) zoneID {
    pix2d::Native::getInstance()->notifyAdEvent("adsAvailable");
}

- ( void ) onAdColonyV4VCReward:(BOOL)success currencyName:(NSString*)currencyName currencyAmount:(int)amount inZone:(NSString*)zoneID {
}

- ( void ) onAdColonyAdStartedInZone:( NSString * )zoneID {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillShow");
}

- ( void ) onAdColonyAdAttemptFinished:(BOOL)shown inZone:( NSString * )zoneID {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillHide");
}

//////////////////////////// InMobi Delegate ////////////////////////////

/*
- (void)interstitialWillPresentScreen:(IMInterstitial *)ad {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillShow");
}
- (void)interstitialWillDismissScreen:(IMInterstitial *)ad {
    pix2d::Native::getInstance()->notifyAdEvent("adsWillHide");
}
*/

- (bool) hideAd {
    /// DO Nothing
    /// return [[UnityAds sharedInstance] hide];
    return false;
}

- (bool) showAd {
    /// Ad SDK failover
    if ([AdColony zoneStatusForZone:@"vz160b599e916443ab8e"] == ADCOLONY_ZONE_STATUS_ACTIVE) {
        [AdColony playVideoAdForZone:@"vz160b599e916443ab8e" withDelegate:self];
        return true;
    } else if ([[UnityAds sharedInstance] canShowAds]) {
        // Show an offer somewhere in the game UI
        // [[UnityAds sharedInstance] setZone:@"1104-987423907423"];
        return [[UnityAds sharedInstance] show];
    } else if (self->adMobAd.isReady) {
        [self->adMobAd presentFromRootViewController:self->_contentController];
        return true;
    } else if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"6.0") and [self.amazonAd isReady]) {
        [self.amazonAd presentFromViewController:self->_contentController];
        return true;
    }

    NSLog(@"Warning: No advertising availables");
    return false;
}

- (void)dealloc {
    /// self->inMobiAd.delegate = nil;
    [self.amazonAd release];
    [super dealloc];
}

@end
