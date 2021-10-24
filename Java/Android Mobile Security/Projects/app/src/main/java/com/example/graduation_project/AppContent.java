package com.example.graduation_project;

import android.app.Activity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.annotation.Nullable;

public class AppContent extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.content);
        RelativeLayout currentLayout = (RelativeLayout) findViewById(R.id.back_color2);
        currentLayout.setBackgroundResource(R.color.SkyBlue);
        String permissions_content = (String) getIntent().getSerializableExtra("index22");
        TextView item = findViewById(R.id.ContenTextView);
        item.setText(permissions_content);
    }
}
