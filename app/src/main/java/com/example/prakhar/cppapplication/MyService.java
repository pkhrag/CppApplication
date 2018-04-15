package com.example.prakhar.cppapplication;

import android.app.IntentService;
import android.content.Intent;
import android.media.projection.MediaProjection;
import android.support.annotation.Nullable;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by prakhar on 4/15/18.
 */

public class MyService extends IntentService {
    private static final String TAG = "MyService";
    public MyService() {
        super(TAG);
    }

    @Override
    protected void onHandleIntent(@Nullable Intent intent) {
        final String indata = "IN_DATA";
        final String outdata = "OUT_DATA";
        String ds = intent.getStringExtra(indata);
        Toast.makeText(getBaseContext(), ds, Toast.LENGTH_SHORT).show();
        Log.d("MERATAG------------------------------", "mera LOGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
        Intent localintent = new Intent(ResponseReciever.BROAD_INT);
//        localintent.setAction(ResponseReciever.BROAD_INT);
//        localintent.addCategory(Intent.CATEGORY_DEFAULT);
        localintent.putExtra(outdata, "Response of the service");
        LocalBroadcastManager.getInstance(this).sendBroadcast(localintent);5
        return;
    }
}
