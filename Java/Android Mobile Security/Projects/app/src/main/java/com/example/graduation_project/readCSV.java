package com.example.graduation_project;
import android.Manifest;
import androidx.annotation.NonNull;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class readCSV {
    public static final String delimiter = ";";

    public class PermissionFrequences{
        public int frequence=0;
        public String permission="";

        public PermissionFrequences(String permis_name){
            frequence=0;
            permission=permis_name;
        }

        public void updateFreq(){
            frequence = frequence+1;
        }

        @Override
        public String toString() {
            return permission + "    " + frequence ;
        }
    }

    public ArrayList<PermissionFrequences> read(String csvFile) {
        ArrayList<PermissionFrequences> permissions=null;
        try {
            File file = new File(csvFile);
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line = "";
            String[] tempArr;
            line = br.readLine();
            tempArr = line.split(delimiter);
            permissions = new ArrayList<>();
            int i=0;
            for(String tempStr : tempArr){
                permissions.add(new PermissionFrequences(tempStr));
                i++;
            }
            int count=0;
            while((line = br.readLine()) != null && count<199) {
                tempArr = line.split(delimiter);
                int c = 0;
                int CC=0;
                for (String tempStr : tempArr) {
                    if(c == i)
                        break;
                    if (tempStr.equals("1"))
                        CC++;
                    c++;
                }
                System.out.println(CC);
                count++;
            }
            br.close();
        } catch(IOException ioe) {
            ioe.printStackTrace();
        }
        return permissions;
    }

    public static void printFrequences(ArrayList<PermissionFrequences> items){
        for(PermissionFrequences item:items) {
            if(item.permission.contains("android.permission.") && !item.permission.contains("com") && item.frequence > 0) {
                System.out.println(item);
            }
        }
    }

    public static void main(String[] args) {
        // csv file to read
        String csvFile = "train.csv";
        readCSV example = new readCSV();
        ArrayList<PermissionFrequences> items=example.read(csvFile);
        printFrequences(items);
    }

}
