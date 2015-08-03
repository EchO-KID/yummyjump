#import <UnityAds/UnityAds.h>
#import <AdColony/AdColony.h>
#import <AmazonAd/AmazonAdInterstitial.h>
#import <GADInterstitialDelegate.h>

@interface BannerViewController : NSObject<UnityAdsDelegate, AdColonyAdDelegate, AdColonyDelegate, AmazonAdInterstitialDelegate, GADInterstitialDelegate>

@property(nonatomic, readonly, retain) AmazonAdInterstitial *amazonAd;

- (instancetype)initWithContentViewController:(UIViewController *)contentController;
- (bool) hideAd;
- (bool) showAd;
- (void) refreshAdMod;

@end