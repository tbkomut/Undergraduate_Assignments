package com.example.graduation_project;

import java.util.ArrayList;

public class ThresholdValue {

    public int malwarePermissionCheck(ArrayList<String> suspecios,String apks){
        APKPermissionFrequences item= new APKPermissionFrequences(apks);
        for(String permissions:suspecios){
            if(permissions.contains("permission.ACCESS_COARSE_LOCATION"))
                item.updateFrequence(80);
            if(permissions.contains("permission.ACCESS_FINE_LOCATION"))
                item.updateFrequence(74);
            if(permissions.contains("permission.ACCESS_LOCATION_EXTRA_COMMANDS"))
                item.updateFrequence(31);
            if(permissions.contains(".permission.ACCESS_NETWORK_STATE"))
                item.updateFrequence(167);
            if(permissions.contains("permission.BLUETOOTH"))
                item.updateFrequence(2);
            if(permissions.contains("permission.BLUETOOTH_ADMIN"))
                item.updateFrequence(2);
            if(permissions.contains("permission.BROADCAST_PACKAGE_REMOVED"))
                item.updateFrequence(1);
            if(permissions.contains("permission.BROADCAST_STICKY"))
                item.updateFrequence(1);
            if(permissions.contains("permission.CALL_PHONE"))
                item.updateFrequence(58);
            if(permissions.contains("permission.CAMERA"))
                item.updateFrequence(4);
            if(permissions.contains("permission.CHANGE_CONFIGURATION"))
                item.updateFrequence(6);
            if(permissions.contains("permission.CHANGE_NETWORK_STATE" ))
                item.updateFrequence(7);
            if(permissions.contains("permission.CHANGE_WIFI_STATE"))
                item.updateFrequence(75);
            if(permissions.contains("permission.CLEAR_APP_CACHE"))
                item.updateFrequence(1);
            if(permissions.contains("permission.DELETE_CACHE_FILES"))
                item.updateFrequence(1);
            if(permissions.contains("permission.DELETE_PACKAGES" ))
                item.updateFrequence(11);
            if(permissions.contains("permission.DISABLE_KEYGUARD" ))
                item.updateFrequence(35);
            if(permissions.contains("permission.DUMP"))
                item.updateFrequence(1);
            if(permissions.contains("permission.EXPAND_STATUS_BAR"))
                item.updateFrequence(8);
            if(permissions.contains("permission.GET_ACCOUNTS"))
                item.updateFrequence(11);
            if(permissions.contains("permission.GET_PACKAGE_SIZE"))
                item.updateFrequence(4);
            if(permissions.contains("permission.GET_TASKS"))
                item.updateFrequence(45);
            if(permissions.contains("permission.INSTALL_PACKAGES"))
                item.updateFrequence(47);
            if(permissions.contains("permission.INTERNET"))
                item.updateFrequence(195);
            if(permissions.contains("permission.KILL_BACKGROUND_PROCESSES"))
                item.updateFrequence(1);
            if(permissions.contains("permission.MODIFY_AUDIO_SETTINGS"))
                item.updateFrequence(1);
            if(permissions.contains("permission.MODIFY_PHONE_STATE"))
                item.updateFrequence(3);
            if(permissions.contains("permission.MOUNT_UNMOUNT_FILESYSTEMS" ))
                item.updateFrequence(18);
            if(permissions.contains("permission.PERSISTENT_ACTIVITY"))
                item.updateFrequence(1);
            if(permissions.contains("permission.PROCESS_OUTGOING_CALLS"))
                item.updateFrequence(10);
            if(permissions.contains("permission.READ_CONTACTS"))
                item.updateFrequence(71);
            if(permissions.contains("permission.READ_EXTERNAL_STORAGE"))
                item.updateFrequence(30);
            if(permissions.contains("permission.READ_LOGS"))
                item.updateFrequence(40);
            if(permissions.contains("permission.READ_PHONE_STATE"))
                item.updateFrequence(190);
            if(permissions.contains("permission.READ_SMS"))
                item.updateFrequence(124);
            if(permissions.contains("permission.READ_SYNC_SETTINGS"))
                item.updateFrequence(2);
            if(permissions.contains("permission.RECEIVE_BOOT_COMPLETED"))
                item.updateFrequence(102);
            if(permissions.contains("permission.RECEIVE_MMS"))
                item.updateFrequence(13);
            if(permissions.contains("permission.RECEIVE_SMS"))
                item.updateFrequence(65);
            if(permissions.contains("permission.RECEIVE_WAP_PUSH"))
                item.updateFrequence(11);
            if(permissions.contains("permission.RECORD_AUDIO"))
                item.updateFrequence(5);
            if(permissions.contains("permission.RESTART_PACKAGES"))
                item.updateFrequence(42);
            if(permissions.contains("permission.SEND_SMS"))
                item.updateFrequence(70);
            if(permissions.contains("permission.SET_PREFERRED_APPLICATIONS"))
                item.updateFrequence(1);
            if(permissions.contains("permission.SET_WALLPAPER"))
                item.updateFrequence(28);
            if(permissions.contains("permission.SET_WALLPAPER_HINTS"))
                item.updateFrequence(8);
            if(permissions.contains("permission.VIBRATE"))
                item.updateFrequence(68);
            if(permissions.contains("permission.WAKE_LOCK"))
                item.updateFrequence(65);
            if(permissions.contains("permission.WRITE_APN_SETTINGS"))
                item.updateFrequence(52);
            if(permissions.contains("permission.WRITE_CONTACTS"))
                item.updateFrequence(51);
            if(permissions.contains("permission.WRITE_EXTERNAL_STORAGE"))
                item.updateFrequence(136);
            if(permissions.contains("permission.WRITE_SECURE_SETTINGS"))
                item.updateFrequence(3);
            if(permissions.contains("permission.WRITE_SETTINGS"))
                item.updateFrequence(14);
            if(permissions.contains("permission.WRITE_SYNC_SETTINGS"))
                item.updateFrequence(2);
            if(permissions.contains("permission.READ_CALENDAR"))
                item.updateFrequence(25);
            if(permissions.contains("permission.WRITE_CALENDAR"))
                item.updateFrequence(25);
            if(permissions.contains("permission.WRITE_CALENDAR"))
                item.updateFrequence(25);
            if(permissions.contains("permission.USE_SIP"))
                item.updateFrequence(25);
            if(permissions.contains("permission.BODY_SENSORS"))
                item.updateFrequence(25);
            if(permissions.contains("permission.RECEIVER_WAP_PUSH"))
                item.updateFrequence(25);
            if(permissions.contains("permission.READ_CALL_LOG"))
                item.updateFrequence(25);
        }
        return item.getterFrequence();
    }

}
