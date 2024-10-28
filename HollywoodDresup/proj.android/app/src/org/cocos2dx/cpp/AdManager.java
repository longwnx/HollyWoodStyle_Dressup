package org.cocos2dx.cpp;

import android.content.Context;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.google.ads.mediation.admob.AdMobAdapter;
import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.FullScreenContentCallback;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.android.ump.ConsentDebugSettings;
import com.google.android.ump.ConsentForm;
import com.google.android.ump.ConsentInformation;
import com.google.android.ump.ConsentRequestParameters;
import com.google.android.ump.FormError;
import com.google.android.ump.UserMessagingPlatform;
import com.congchuacuatoi.vn.R;

public class AdManager {

    private static final boolean IS_TESTING = false;
    private static AppActivity activity;
    private static AdView bannerAdView;
    private static InterstitialAd mInterstitialAd;
    private static RewardedAd mRewardedAd;


    private static ConsentInformation consentInformation;
    private static ConsentForm consentForm;

    //public static native void scaleView(float adHeight);

    static void init(Context context) {
        activity = (AppActivity) context;
        checkConsentStatus();
    }

    private static void checkConsentStatus() {

        ConsentRequestParameters params;
        if(IS_TESTING){

            ConsentDebugSettings debugSettings = new ConsentDebugSettings.Builder(activity)
                    .setDebugGeography(ConsentDebugSettings
                            .DebugGeography
                            .DEBUG_GEOGRAPHY_EEA)
                    .addTestDeviceHashedId("420905B55DC0F7FBB79BF68D3F5F6C5B")
                    .build();


            params = new ConsentRequestParameters
                    .Builder()
                    .setConsentDebugSettings(debugSettings)
                    .build();

        }else{

            // Set tag for underage of consent. false means users are not underage.
            params = new ConsentRequestParameters
                    .Builder()
                    .setTagForUnderAgeOfConsent(true) /// this is the line for chi
                    .build();


        }



        consentInformation = UserMessagingPlatform.getConsentInformation(activity);

        consentInformation.requestConsentInfoUpdate(
                activity,
                params,
                new ConsentInformation.OnConsentInfoUpdateSuccessListener() {
                    @Override
                    public void onConsentInfoUpdateSuccess() {

                        if (consentInformation.isConsentFormAvailable()) {

                            Log.w("PTag", "Ram 1");
                            loadForm();
                        }else{
                            Log.w("PTag", "Ram 2");
                            initializeAds();
                        }
                    }
                },
                new ConsentInformation.OnConsentInfoUpdateFailureListener() {
                    @Override
                    public void onConsentInfoUpdateFailure(FormError formError) {
                        Log.w("PTag", "Ram 3");
                        loadForm();
                        // initializeAds();
                    }
                });
    }


    public static  void loadForm() {
        UserMessagingPlatform.loadConsentForm(
                activity,
                new UserMessagingPlatform.OnConsentFormLoadSuccessListener() {
                    @Override
                    public void onConsentFormLoadSuccess(ConsentForm consentForm1) {
                        consentForm = consentForm1;
                        if(consentInformation.getConsentStatus() == ConsentInformation.ConsentStatus.REQUIRED) {
                            consentForm.show(
                                    activity,
                                    new ConsentForm.OnConsentFormDismissedListener() {
                                        @Override
                                        public void onConsentFormDismissed(@Nullable FormError formError) {
                                            // Handle dismissal by reloading form.
                                            Log.w("PTag", "Ram 4");
                                            loadForm();
                                            // initializeAds();
                                        }
                                    });

                        }else{
                            Log.w("PTag", "Ram 5");
                            initializeAds();
                        }
                    }
                },
                new UserMessagingPlatform.OnConsentFormLoadFailureListener() {
                    @Override
                    public void onConsentFormLoadFailure(FormError formError) {
                        Log.w("PTag", "Ram 6");
                        initializeAds();
                    }
                }
        );
    }



    private static void initializeAds() {
        MobileAds.initialize(activity,
                new OnInitializationCompleteListener() {
                    @Override
                    public void onInitializationComplete(InitializationStatus initializationStatus) {
                    }
                });

        bannerAdView = new AdView(activity);
        bannerAdView.setAdSize(getBannerAdSize());
        bannerAdView.setAdUnitId(activity.getString(R.string.admob_banner_id));
        loadBannerAd();

        //m_interstitialAd = new InterstitialAd(activity);
        //m_interstitialAd.setAdUnitId(activity.getString(R.string.admob_interstitial_id));
        loadInterstitialAd();


    }

    private static AdSize getBannerAdSize() {
        DisplayMetrics outMetrics = new DisplayMetrics();
        activity.getWindowManager().getDefaultDisplay().getMetrics(outMetrics);

        int adWidth = (int) (outMetrics.widthPixels / outMetrics.density);

        return AdSize.getCurrentOrientationAnchoredAdaptiveBannerAdSize(activity, adWidth);
    }

    private static void loadBannerAd() {
        final AdRequest.Builder builder = new AdRequest.Builder();
        if (consentInformation.getConsentStatus() == ConsentInformation.ConsentStatus.NOT_REQUIRED) {
            Bundle extras = new Bundle();
            extras.putString("npa", "1");

            builder.addNetworkExtrasBundle(AdMobAdapter.class, extras);
        }
//        bannerAdView.loadAd(builder.build());
        bannerAdView.setAdListener(new AdListener() {
            @Override
            public void onAdLoaded() {
                // Code to be executed when an ad finishes loading.
                if (bannerAdView.getParent() == null) {
                    LinearLayout layout = new LinearLayout(activity);
                    layout.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM);
                    activity.addContentView(layout, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
                    LinearLayout.LayoutParams adLayoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                    layout.addView(bannerAdView, adLayoutParams);
                }
                //scaleView(bannerAdView.getAdSize().getHeightInPixels(activity));
                bannerAdView.setVisibility(View.VISIBLE);

                showBannerAd();

            }
        });
        bannerAdView.loadAd(builder.build());
    }

    static void showBannerAd() {
        if (bannerAdView!=null)
        loadBannerAd();

    }

    static void hideBannerAd() {
        bannerAdView.setVisibility(View.GONE);
    }


    private static void loadInterstitialAd() {
        final AdRequest.Builder builder = new AdRequest.Builder();
        if (consentInformation.getConsentStatus() == ConsentInformation.ConsentStatus.NOT_REQUIRED) {
            Bundle extras = new Bundle();
            extras.putString("npa", "1");

            builder.addNetworkExtrasBundle(AdMobAdapter.class, extras);
        }

        InterstitialAd.load(activity, activity.getString(R.string.admob_interstitial_id), builder.build(), new InterstitialAdLoadCallback() {
            @Override
            public void onAdLoaded(@NonNull InterstitialAd interstitialAd) {
                // The mInterstitialAd reference will be null until
                // an ad is loaded.
                mInterstitialAd = interstitialAd;
                AppActivity.admobfullpageavailable = true;
            }

            @Override
            public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                // Handle the error
                mInterstitialAd = null;
                AppActivity.admobfullpageavailable = false;
                loadInterstitialAd();
            }
        });
    }

    static void showInterstitialAd() {
        if (mInterstitialAd != null) {
            mInterstitialAd.setFullScreenContentCallback(new FullScreenContentCallback(){
                @Override
                public void onAdDismissedFullScreenContent() {
                    // Called when fullscreen content is dismissed.
                    AppActivity.admobfullpageavailable = false;
                    loadInterstitialAd();
                }

                @Override
                public void onAdFailedToShowFullScreenContent(AdError adError) {
                    // Called when fullscreen content failed to show.
                }

                @Override
                public void onAdShowedFullScreenContent() {
                    // Called when fullscreen content is shown.
                    // Make sure to set your reference to null so you don't
                    // show it a second time.
                    mInterstitialAd = null;
                }
            });

            mInterstitialAd.show(activity);
        } else {
            loadInterstitialAd();
        }
    }



}
