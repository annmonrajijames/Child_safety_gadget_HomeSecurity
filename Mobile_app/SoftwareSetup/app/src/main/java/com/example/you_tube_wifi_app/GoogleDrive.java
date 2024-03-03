package com.example.you_tube_wifi_app;

import android.app.DownloadManager;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import android.webkit.DownloadListener;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;

public class GoogleDrive extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_google_drive);
        WebView wv = (WebView)findViewById(R.id.wv);
        wv.loadUrl("https://drive.google.com/drive/folders/126TKtbRmXRUtDm5shlgYZakWSCkLFFL-?usp=sharing");// Gdrive folder link
        wv.setWebViewClient(new Client());
        WebSettings ws = wv.getSettings();
        ws.setJavaScriptEnabled(true);
        wv.getSettings().setJavaScriptCanOpenWindowsAutomatically(true);
        wv.clearCache(true);
        wv.clearHistory();

        wv.setDownloadListener(new DownloadListener() {
            @Override
            public void onDownloadStart(String url, String s1, String s2, String s3, long l) {
                DownloadManager.Request req= new DownloadManager.Request(Uri.parse(url));
                req.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
                DownloadManager dm = (DownloadManager)getSystemService(DOWNLOAD_SERVICE);
                dm.enqueue(req);

                Toast.makeText(GoogleDrive.this,"Downloading....",Toast.LENGTH_SHORT).show();
            }
        });
    }

    private class Client extends WebViewClient {
        @Override
        public void onPageStarted(WebView view, String url, Bitmap favicon) {
            super.onPageStarted(view, url, favicon);
        }

        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            view.loadUrl(url);
            return true;
        }

        @Override
        public void onPageFinished(WebView view, String url) {
            super.onPageFinished(view, url);
        }

        public void onReceivedError(WebView webView, int errorCode, String description, String failingUrl) {
            try {
                webView.stopLoading();
            } catch (Exception e) {
            }

            if (webView.canGoBack()) {
                webView.goBack();
            }

            webView.loadUrl("about:blank");
            AlertDialog alertDialog = new AlertDialog.Builder(GoogleDrive.this).create();
            alertDialog.setTitle("Error");
            alertDialog.setMessage("Check your internet connection and try again.");
            alertDialog.setButton(DialogInterface.BUTTON_POSITIVE, "Try Again", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int which) {
                    finish();
                    startActivity(getIntent());
                }
            });

            alertDialog.show();
            super.onReceivedError(webView, errorCode, description, failingUrl);
        }

    }
}