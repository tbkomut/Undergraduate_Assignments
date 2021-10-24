package com.example.graduation_project;

public class APKPermissionFrequences {

    private String apk_name;
    private int frequence;

    public APKPermissionFrequences() {
        apk_name="";
        frequence = 0;
    }

    public APKPermissionFrequences(String name) {
        apk_name=name;
        frequence=0;
    }


    public void updateFrequence(int value){
        frequence = frequence + value;
    }

    public int getterFrequence(){
        return frequence;
    }

    public String getterPermissionName(){
        return apk_name;
    }

    public void setterFrequence(int val){
        frequence = val;
    }

    public void setterPermissionName(String val){
        apk_name = val;
    }

    public String toString(){
        return apk_name + " dosyası şüphe değeri => " + frequence;
    }

}
