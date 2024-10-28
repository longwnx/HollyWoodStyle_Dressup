/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
package org.cocos2dx.cpp;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.os.Bundle;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.view.View;
import org.cocos2dx.lib.Cocos2dxActivity;


import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContextWrapper;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;

import android.util.Log;
import android.view.WindowManager;
import android.widget.Toast;


import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;
import org.cocos2dx.lib.Cocos2dxRenderer;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.ResourceBundle;



import com.congchuacuatoi.vn.R;           //add your package name after write .R


import android.content.SharedPreferences;


import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.ActivityCompat;
import androidx.core.content.FileProvider;
import androidx.lifecycle.LifecycleObserver;
import androidx.lifecycle.MutableLiveData;



public class AppActivity extends Cocos2dxActivity   {


    static final int RC_REQUEST = 10001;

    private static AdManager admanager =  null;

    private static AppActivity _this;
    public static boolean admobfullpageavailable =  false;

    public static Cocos2dxRenderer renderer;
    private static boolean isInAppRunning = false;

    public static final int WRITE_STORAGE_REQUEST_ID = 97483;
    String PhotoName = "ss.png";


    private static final String PREF_FILE  = "PREF_FILE";
    private static final String IS_PRODUCT_PURCHASE = "IS_PRODUCT_PURCHASE";
    private static final String BP1 = "com.yourcompany.toddlerpuzzlegame.unlock";


    private static final String TAG  = "LOGGER";

    private static final List<String> LIST_OF_SKUS = Collections.unmodifiableList(
            new ArrayList<String>() {{
                add(BP1);
            }});






    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.setEnableVirtualButton(false);

        super.onCreate(savedInstanceState);
        if (!isTaskRoot()) {
            return;
        }

        // Make sure we're running on Pie or higher to change cutout mode
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            // Enable rendering into the cutout area
            WindowManager.LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }
        // DO OTHER INITIALIZATION BELOW


        SharedPreferences preferences = getSharedPreferences(PREF_FILE, MODE_PRIVATE);
        boolean isPurchase = preferences.getBoolean(IS_PRODUCT_PURCHASE, false);
        if (isPurchase)
        {

        } else {
            AdManager.init(this);

        }



        _this = this;




    }

    static void shareGame(final String title) {
        ContextWrapper c = new ContextWrapper(_this);
        String path = c.getFilesDir().getPath() + "/" + title;
        File imgFile = new File(path);

        Uri pngUri = FileProvider.getUriForFile(_this, _this.getApplicationContext().getPackageName() + ".provider", imgFile);

        if (pngUri != null) {
            Intent intent = new Intent();
            intent.setAction(Intent.ACTION_SEND);
            intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
            intent.setDataAndType(pngUri, _this.getContentResolver().getType(pngUri));
            intent.putExtra(Intent.EXTRA_TEXT, R.string.app_name);
            intent.putExtra(Intent.EXTRA_STREAM, pngUri);
            intent.putExtra(Intent.EXTRA_TEXT, "https://play.google.com/store/apps/details?id=" + _this.getPackageName());

            _this.startActivity(Intent.createChooser(intent, "Choose an app"));
        }
    }

    static void saveImage(final String title) {
        if (isPermissionGranted(Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
            _this.saveImageToGallery(title);
        } else {
            requestPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE, WRITE_STORAGE_REQUEST_ID);
        }
    }

    void saveImageToGallery(final String title) {
        String dirName = getContext().getString(R.string.app_name);

        ContextWrapper c = new ContextWrapper(_this);
        String path = c.getFilesDir().getPath() + "/" + title;
        File imgFile = new File(path);

        System.out.println("Path to check : " + path);

        Bitmap myBitmap = BitmapFactory.decodeFile(imgFile.getAbsolutePath());

        // Create a new folder in SD Card
        File dir = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/Pictures/" + "/" + dirName + "/");
        dir.mkdirs();

        String timeStamp = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss", Locale.ENGLISH).format(new Date());

        File file = null;
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.Q) {
            file = new File(dir, dirName + " " + timeStamp + ".png");
        }

        try {
            ContentValues values = new ContentValues();
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                values.put(MediaStore.Images.Media.DATE_TAKEN, System.currentTimeMillis());
                values.put(MediaStore.MediaColumns.DISPLAY_NAME, dirName + " " + timeStamp + ".png");
            } else {
                values.put(MediaStore.MediaColumns.DATA, file.getAbsolutePath());
            }
            values.put(MediaStore.Images.Media.MIME_TYPE, "image/png");

            ContentResolver contentResolver = _this.getContentResolver();
            Uri uri = contentResolver.insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);
            OutputStream output;
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                output = contentResolver.openOutputStream(uri);
            } else {
                output = new FileOutputStream(file);
            }

            // Compress into png format image from 0% - 100%
            myBitmap.compress(Bitmap.CompressFormat.PNG, 100, output);
            output.flush();
            output.close();

            runOnUiThread(new Runnable() {
                public void run() {
                    Toast.makeText(_this, " Saved Successfully.", Toast.LENGTH_LONG).show();
                }
            });
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    static boolean isPermissionGranted(String permission) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            return _this.checkSelfPermission(permission) == PackageManager.PERMISSION_GRANTED;
        }
        return true;
    }

    static void requestPermission(String permission, int requestCode) {
        if (!isPermissionGranted(permission)) {
            ActivityCompat.requestPermissions(_this, new String[]{permission}, requestCode);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == WRITE_STORAGE_REQUEST_ID) {
            if (grantResults.length == 1 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                saveImageToGallery(PhotoName);
            } else {
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                    AlertDialog.Builder alert = new AlertDialog.Builder(this);
                    alert.setTitle("Permission needed");
                    if (shouldShowRequestPermissionRationale(Manifest.permission.READ_EXTERNAL_STORAGE)) {
                        alert.setMessage("Please grant permission to open gallery!");
                        alert.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                saveImage(PhotoName);
                            }
                        });
                        alert.setNegativeButton("No", null);
                    } else {
                        alert.setMessage("Please grant permission from settings.");
                        alert.setPositiveButton("OK", null);
                    }
                    alert.show();
                }
            }
        }
    }

    public static void vibrate() {
//        Vibrator v = (Vibrator) _this.getSystemService(Context.VIBRATOR_SERVICE);
//        Log.w("PTag", "check vibrate");
//        //if (vibrator != null) {
//        // Vibrate for 500 milliseconds
//        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
//            Log.w("PTag", "check vibrate 1");
//            v.vibrate(VibrationEffect.createOneShot(200, VibrationEffect.DEFAULT_AMPLITUDE));
//        } else {
//            Log.w("PTag", "check vibrate 2");
//            //deprecated in API 26
//            v.vibrate(200);
//        }
        //}
    }
    public static void VibrationLoad(){

        _this. runOnUiThread(new Runnable() {
            @Override
            public void run() {

                //vibrate();
            }
        });

    }
    public static void bannerEnabled(){

        _this. runOnUiThread(new Runnable() {
            @Override
            public void run() {

                AdManager.showBannerAd();
            }
        });

    }
    public static  void HideBanner(){

        _this. runOnUiThread(new Runnable() {

            @Override
            public void run() {

                AdManager.hideBannerAd();
                //AdManager.scaleView(0);
            }
        });

    }
    public static boolean isInterstitialAvailable(){

        return admobfullpageavailable;
    }
    public static void showInterstitial(){

        _this. runOnUiThread(new Runnable() {
            @Override
            public void run() {

                AdManager.showInterstitialAd();

            }
        });

    }
    public static void OpenMoreGame() {
        String url="";
        Intent storeintent=null;


        String moreURL = getContext().getApplicationContext().getString(R.string.more_game_url);
        url = moreURL;
        storeintent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
        storeintent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
        _this.startActivity(storeintent);

    }
    public static void openRateGame() {
        String url = "";
        Intent storeintent = null;

        String rateURL = getContext().getApplicationContext().getString(R.string.rate_game_url);
        url = rateURL;
        storeintent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
        storeintent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
        _this.startActivity(storeintent);
    }
    public static AppActivity getInstance() {
        Log.i("Call", "getInstance");
        return (AppActivity) _this;
    }


    public static void BackButtonClicked() {

        _this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AlertDialog.Builder builder = new AlertDialog.Builder(_this,
                        R.style.MyAlertDialogStyle);
                //builder.setTitle(_this.getResources().getString(R.string.app_name));
                builder.setCancelable(false);
                builder.setMessage("Are you sure you want to quit the game?");
                builder.setPositiveButton("Quit", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // I do not need any action here you might
                        dialog.dismiss();
                        _this.finish();
                    }
                });
                builder.setNeutralButton("MoreApps", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // I do not need any action here you might
                        OpenMoreGame();
                    }
                });
                builder.setNegativeButton("Resume", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                        dialog.dismiss();

                    }
                });

                //.setNegativeButton("No", null);


                builder.show();
            }
        });
    }




}
