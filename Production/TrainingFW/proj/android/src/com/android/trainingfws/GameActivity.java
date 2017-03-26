/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.trainingfws;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.WindowManager;
import android.widget.Toast;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorManager;
import java.io.File;
import android.util.DisplayMetrics;

public class GameActivity extends Activity {

	static GameActivity		mInstance = null;
	
    static GameSurfaceView 	mView = null;	
    private SensorManager mSensorManager; 
	private Sensor mAccelerometer;
	boolean isResume=false;	
	public static native void nativeOnResume(boolean isResume);
		
    @Override protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        mInstance = this;
        Log.i("Created","Created");
        mView = new GameSurfaceView(getApplication());
        setContentView(mView);  		
        MusicSer.Load(this, R.raw.track2);
        MusicSer.Play();
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        mSensorManager.registerListener( mView, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }

    @SuppressWarnings("deprecation")
	@Override 
	protected void onPause() {
        super.onPause();
		Log.i("Paused","Paused");
		MusicSer.Pause();
		isResume=false;
        mView.onPause();
        mSensorManager.unregisterListener( mView);
    }
	
    @Override 
    protected void onResume() {
        super.onResume();
		Log.i("Resumed","Resumed");
		if(!isResume)
			isResume=true;
		if(isResume)
			nativeOnResume(isResume);		
        mView.onResume();	
		
        MusicSer.Play();
        mSensorManager.registerListener( mView, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }
    
    public void exitGame(String strexit,String exit,Context context){
		AlertDialog.Builder alert=new AlertDialog.Builder(context);
		alert.setTitle(exit+"...");
		alert.setMessage(strexit);
		alert.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				Toast.makeText(getApplicationContext(), "Quit", Toast.LENGTH_SHORT).show();					
				/*finish();*/
				MusicSer.Stop();
				System.exit(0);
			}
		});
		alert.setNegativeButton("No", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				Toast.makeText(getApplicationContext(), "Cancel", Toast.LENGTH_SHORT).show();
				dialog.cancel();
			}
		});
		alert.show();
	}
            
	@Override
	public boolean onKeyDown(int keyCode,KeyEvent event){
		switch(keyCode){
			case KeyEvent.KEYCODE_BACK:
				exitGame("Do you want to exit game?", "Exit", this);
				break;
			case KeyEvent.KEYCODE_HOME:
				//if(!isResume)
				//	isResume=true;
				//MusicSer.Stop();
				//System.exit(1);
				break;
		}
		return super.onKeyDown(keyCode, event);	
	}
	
	@Override
	protected void onUserLeaveHint(){
		System.exit(0);
	} 
	
    static {
        System.loadLibrary("trainingfw");
    }
}
