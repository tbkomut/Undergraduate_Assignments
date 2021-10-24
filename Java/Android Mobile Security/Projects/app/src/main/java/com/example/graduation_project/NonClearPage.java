package com.example.graduation_project;

import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import org.w3c.dom.Text;

import java.io.Serializable;
import java.util.Map;

public class NonClearPage extends AppCompatActivity implements Serializable {

    static final int progress_bar_type=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.result_text2);
        RelativeLayout currentLayout = (RelativeLayout) findViewById(R.id.back_color);
        TextView text_result = (TextView) findViewById(R.id.result_text2);
        int app_list = (int) getIntent().getSerializableExtra("state_of_device");
        text_result.setText("Cihazda " + app_list + " adet zararlı uygulama var!");
        Handler hand = new Handler();
        hand.postDelayed(new Runnable() {
            public void run() {

            }
        }, 4000);
        new closingApp().execute();
        Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            public void run() {
                Intent intent = new Intent(getApplicationContext(), EntryPage.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                intent.putExtra("EXIT", true);
                startActivity(intent);
            }
        }, 8000);
    }

    @Override
    protected Dialog onCreateDialog(int id) {
        switch (id){
            case progress_bar_type:
                ProgressDialog dialog = new ProgressDialog(NonClearPage.this);
                dialog.setIndeterminate(true);
                dialog.setMessage("Uygulama sonlanıyor...");
                dialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
                dialog.setCancelable(false);
                dialog.show();
                return dialog;
            default:
                return null;
        }
    }

    public class closingApp extends AsyncTask<Object, Object, Object> {

        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected Object doInBackground(Object... objects) {
            try {
                Thread.sleep(6000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return null;
        }


        @Override
        protected void onPostExecute(Object item) {
            super.onPostExecute(item);
            showDialog(progress_bar_type);
        }

    }

}
