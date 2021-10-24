package com.example.graduation_project;
import android.app.Activity;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Map;

public class ListsAppsFragment extends AppCompatActivity implements Serializable {

    ArrayList<String> malicious_pck= new ArrayList<>();
    ArrayList<String> malicious_apps= new ArrayList<>();
    ArrayList<String> all_apps= new ArrayList<>();
    ArrayList<String> benign_apps= new ArrayList<>();
    ArrayList<String> benign_pck= new ArrayList<>();
    ArrayList<String> permissions_lists_all= new ArrayList<>();
    private int numberOfRisk=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.listsofresults);
        RelativeLayout currentLayout = (RelativeLayout) findViewById(R.id.activity_main);
        currentLayout.setBackgroundResource(R.color.SkyBlue);

        Map<Map<String, Integer>,String> app_list = (Map<Map<String, Integer>,String>) getIntent().getSerializableExtra("app_list");
        permissions_lists_all = (ArrayList<String>) getIntent().getSerializableExtra("perm_list");
        for(Map.Entry<Map<String, Integer>, String> temp: app_list.entrySet() ) {
            String packet_names = temp.getValue();
            for (Map.Entry<String, Integer> entry : temp.getKey().entrySet()) {
                System.out.print(entry.getKey()+" ");
                System.out.println(entry.getValue());
                if (entry.getValue() > 0) {
                    malicious_apps.add(entry.getKey());
                    malicious_pck.add(packet_names);
                } else {
                    benign_apps.add(entry.getKey());
                    benign_pck.add(packet_names);
                }
                all_apps.add(entry.getKey());
            }
        }
        int c=0;
        for(String name:malicious_apps) {
            Intent intent = new Intent(Intent.ACTION_UNINSTALL_PACKAGE);
            intent.setData(Uri.parse("package:" + malicious_pck.get(c)));
            intent.putExtra(Intent.EXTRA_RETURN_RESULT, true);
            startActivityForResult(intent, 1);
            System.out.println(name);
            c++;
        }
        ListOfApps myListFragment=new ListOfApps();
        myListFragment.setListApps(all_apps);
        for(String perm:permissions_lists_all){
            System.out.println(perm);
        }
        myListFragment.setListPermission(permissions_lists_all);
        //FragmentManager manager=getFragmentManager();
        FragmentTransaction transaction=getFragmentManager().beginTransaction();
        transaction.add(R.id.container, myListFragment, "addFrag");
        transaction.commit();
        numberOfRisk = malicious_apps.size();
//        Intent intent = new Intent(ListsAppsFragment.this,CleanPage.class);
//        startActivity(intent);
    }

    public void QuitApp(View view) {
        if(numberOfRisk==0) {
            Intent intent = new Intent(ListsAppsFragment.this, ResultPage.class);
            startActivity(intent);
        }
        else{
            Intent intent = new Intent(ListsAppsFragment.this, NonClearPage.class);
            intent.putExtra("state_of_device", (Serializable) numberOfRisk);
            startActivity(intent);
        }
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        // get result
        if(resultCode == RESULT_OK){
            numberOfRisk--;
        }else if (resultCode == RESULT_CANCELED){
           ;
        }
    }

}