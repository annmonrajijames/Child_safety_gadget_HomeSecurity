package com.example.child_safety_app;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.widget.Button;

public class HomeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);

        // Find the button by its ID
        Button doorLockButton = findViewById(R.id.door_lock_button);

        // Set a click listener on the button
        doorLockButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create an Intent to start the OperatingPage activity
                Intent intent = new Intent(HomeActivity.this, OperatingPage.class);
                startActivity(intent);
            }
        });
    }
}
