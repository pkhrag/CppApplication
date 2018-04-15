package com.example.prakhar.cppapplication;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by prakhar on 4/15/18.
 */

public class ResponseReciever extends BroadcastReceiver {

    public static final String BROAD_INT = "com.mamlambo.intent.action.MESSAGE_PROCESSED";
    @Override
    public void onReceive(Context context, Intent intent) {
        final String outdata = "OUT_DATA";
        String data = intent.getStringExtra(outdata);
        Toast.makeText(context, data, Toast.LENGTH_SHORT).show();
        Log.d("---------BROADCAST-----------", "yaha aya");
        final String indata = "IN_DATA";
        Intent mServiceIntent = new Intent(context, MyService.class);
        mServiceIntent.putExtra(indata, "this is a service string");
//        context.startService(mServiceIntent);
        return;
    }
}
