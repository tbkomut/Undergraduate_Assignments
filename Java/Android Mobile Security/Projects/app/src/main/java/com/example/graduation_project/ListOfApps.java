package com.example.graduation_project;
import android.app.ListFragment;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Toast;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class ListOfApps extends ListFragment implements AdapterView.OnItemClickListener {

    private ArrayList<String> apps= new ArrayList<>();
    private ArrayList<String> permissions= new ArrayList<>();

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View v= inflater.inflate(R.layout.listapps, container, false);
        return v;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        String[] apps_list_finally = apps.toArray(new String[0]);
        setListAdapter(new ArrayAdapter<String>(getActivity(),android.R.layout.simple_list_item_1, apps_list_finally));
        getListView().setOnItemClickListener(this);
    }


    public void setListApps(ArrayList<String> app_list){
        apps = app_list;
    }

    public void setListPermission(ArrayList<String> temp){
        permissions = temp;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position,long id) {
        Intent intent= new Intent();
        intent.setClass(getActivity(),AppContent.class);
        intent.putExtra("index22", permissions.get(position));
        startActivity(intent);
        // Toast.makeText(getActivity(), "Item: " + position, Toast.LENGTH_SHORT).show();
    }


}
