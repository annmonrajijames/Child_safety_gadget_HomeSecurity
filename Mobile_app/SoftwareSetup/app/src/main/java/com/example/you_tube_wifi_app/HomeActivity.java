package com.example.you_tube_wifi_app;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class HomeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);

        // Find the button by its ID
        Button doorLockButton = findViewById(R.id.buttonDoorLock);

        // Set a click listener on the button
        doorLockButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Intent to start OperatingPage activity
                Intent intent = new Intent(HomeActivity.this, OperatingPage.class);
                startActivity(intent);
            }
        });
    }
}