package com.example.graduation_project;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;

public class EntryPage extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.giris_ekrani);
        passToMainScreen();
        if (getIntent().getBooleanExtra("EXIT", false)) {
            finish();
            System.exit(0);
        }
    }

    private void passToMainScreen(){
        Thread LogoAnimation = new Thread(){
            public void run(){
                ImageView entryLogo = (ImageView) findViewById(R.id.logo);
                Animation anim = AnimationUtils.loadAnimation(getApplicationContext(),R.anim.fade_in);
                anim.reset();
                entryLogo.clearAnimation();
                entryLogo.startAnimation(anim);
            }
        };
        LogoAnimation.start();

        Thread returnWork = new Thread(){
            public void run(){
                try {
                    sleep(5000);
                    Intent intent = new Intent(EntryPage.this,MainPage.class);
                    startActivity(intent);
                    super.run();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        returnWork.start();
    }


}